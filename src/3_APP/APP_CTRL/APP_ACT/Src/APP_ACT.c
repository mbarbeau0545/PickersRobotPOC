/*********************************************************************
 * @file        APP_ACT.c
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************

#include "./APP_ACT.h"
#include "APP_CFG/ConfigFiles/APPACT_ConfigPrivate.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//


/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
/* CAUTION : Automatic generated code section for Variable: Start */
/**< Variable for Actuators Drivers State*/
t_eAPPACT_ActuatorState g_actState_ae[APPACT_ACTUATOR_NB] = {
    APPACT_ACTUATOR_STATE_ENABLE, // APPACT_ACTUATOR_MTR_X_L
    APPACT_ACTUATOR_STATE_ENABLE, // APPACT_ACTUATOR_MTR_X_R
    APPACT_ACTUATOR_STATE_ENABLE, // APPACT_ACTUATOR_MTR_Y
    APPACT_ACTUATOR_STATE_ENABLE, // APPACT_ACTUATOR_MTR_Z
};

/**< Variable for Actuators Drivers State*/
t_eAPPACT_DriverState g_ActDrvState_ae[APPACT_DRIVER_NB] = {
        APPACT_DRIVER_STATE_ENABLE, // APPACT_DRIVER_CL42T
};

/* CAUTION : Automatic generated code section for Variable: End */
static t_eCyclicModState g_AppAct_ModState_e = STATE_CYCLIC_CFG;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
 *
 *	@brief      Perform preOperationnal action.\n
 *  @note       Call driver init function.\n
 *              Set the actuator configuration (5 per cycle).\n
 *              If one of the configuration is not set the Module Cyclic 
 *              retry indefinitely.\n
 *              
 * 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE

 */
static t_eReturnCode s_APPACT_ConfigurationState(void);
/**
*
*	@brief  Call driver cyclic function
*
*/
static t_eReturnCode s_APPACT_Operational(void);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * APPACT_Init
 *********************************/
t_eReturnCode APPACT_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_uint8 s_LLDRV_u8 = (t_uint8)0;
    
    for(; (s_LLDRV_u8 < APPACT_DRIVER_NB) && (Ret_e == RC_OK) ; s_LLDRV_u8++)
    {
        if(g_ActDrvState_ae[s_LLDRV_u8] == APPACT_DRIVER_STATE_ENABLE
        && c_AppAct_SysDrv_apf[s_LLDRV_u8].Init_pcb != (t_cbAppAct_DrvInit *)NULL_FONCTION)
        {
            Ret_e = (c_AppAct_SysDrv_apf[s_LLDRV_u8].Init_pcb)();
            
        }
    }

    return Ret_e;
}

/*********************************
 * APPACT_Cyclic
 *********************************/
t_eReturnCode APPACT_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch (g_AppAct_ModState_e)
    {
    case STATE_CYCLIC_CFG:
    {
        Ret_e = s_APPACT_ConfigurationState();
        if(Ret_e == RC_OK)
        {
            g_AppAct_ModState_e = STATE_CYCLIC_WAITING;
        }   
        break;
    }
    case STATE_CYCLIC_WAITING:
    {
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_PREOPE:
    {
        g_AppAct_ModState_e = STATE_CYCLIC_OPE;
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_OPE:
    {
        Ret_e = s_APPACT_Operational();
        break;
    }
    case STATE_CYCLIC_ERROR:
    {
        break;
    }
    case STATE_CYCLIC_BUSY:
    default:
        Ret_e = RC_OK;
        break;
    }
    return Ret_e;
}

/*********************************
 * APPACT_GetState
 *********************************/
t_eReturnCode APPACT_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_AppAct_ModState_e;
    }
    return Ret_e;
}

/*********************************
 * APPACT_SetState
 *********************************/
t_eReturnCode APPACT_SetState(t_eCyclicModState f_State_e)
{
    g_AppAct_ModState_e = f_State_e;
    return RC_OK;
}

/*********************************
 * APPACT_Get_ActValue
 *********************************/
t_eReturnCode APPACT_Get_ActValue(t_eAPPACT_Actuators f_actuator_e, t_uAPPACT_GetValue * f_actValue_pu)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_actuator_e > APPACT_ACTUATOR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_actValue_pu == (t_sint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_AppAct_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        // call specFunc 
        Ret_e = (c_AppAct_SysAct_apf[f_actuator_e].GetValue_pcb)(&f_actValue_pu);
    }
    
    return Ret_e;
}

/*********************************
 * APPACT_Set_ActValue
 *********************************/
t_eReturnCode APPACT_Set_ActValue(t_eAPPACT_Actuators f_actuator_e, t_uAPPACT_SetValue  f_actValue_u)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_actuator_e > APPACT_ACTUATOR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_AppAct_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        // call specFunc 
        Ret_e = (c_AppAct_SysAct_apf[f_actuator_e].SetValue_pcb)(f_actValue_u);
    }

    return Ret_e;    
}

/*********************************
 * APPACT_Get_ActuatorState
 *********************************/
t_eReturnCode APPACT_Set_ActuatorState(t_eAPPACT_Actuators f_Actuator_e, t_eAPPACT_ActuatorState f_ActState_e)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_Actuator_e > APPACT_ACTUATOR_NB
    || f_ActState_e > APPACT_ACTUATOR_STATE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        g_actState_ae[f_Actuator_e] = f_ActState_e;
    }
    return Ret_e;
}

/*********************************
 * APPSNS_Get_SensorState
 *********************************/
t_eReturnCode APPACT_Get_ActuatorState(t_eAPPACT_Actuators f_Actuator_e, t_eAPPACT_ActuatorState *f_ActState_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_Actuator_e > APPACT_ACTUATOR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_ActState_pe == (t_eAPPACT_ActuatorState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_ActState_pe =  g_actState_ae[f_Actuator_e];
    }
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_APPACT_ConfigurationState
 *********************************/
static t_eReturnCode s_APPACT_ConfigurationState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_uint8 s_LLACT_u8 = 0;
    // first call drv init function 
    // actuators configuration call
        
    for (; (s_LLACT_u8 < APPACT_ACTUATOR_NB) && (Ret_e == RC_OK) ; s_LLACT_u8++)  
    {
        if(g_actState_ae[s_LLACT_u8] == APPACT_ACTUATOR_STATE_ENABLE
        && c_AppAct_SysAct_apf[s_LLACT_u8].SetCfg_pcb != (t_cbAppAct_SetActCfg *)NULL_FONCTION)
        {
             Ret_e = (c_AppAct_SysAct_apf[s_LLACT_u8].SetCfg_pcb)();                 
        }
    }

    if(Ret_e == RC_OK
    && s_LLACT_u8 < APPACT_ACTUATOR_NB)
    {
        Ret_e = RC_WARNING_BUSY;
    }

    return Ret_e;
}
/*********************************
 * s_APPACT_Operational
 *********************************/
static t_eReturnCode s_APPACT_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LLI_u8; 

    for(LLI_u8 = (t_uint8)0 ; (LLI_u8 < APPACT_DRIVER_NB) && (Ret_e == RC_OK); LLI_u8++)
    {
        if(g_ActDrvState_ae[LLI_u8] == APPACT_DRIVER_STATE_ENABLE)
        {
            if(c_AppAct_SysDrv_apf[LLI_u8].Cyclic_pcb != (t_cbAppAct_DrvCyclic *)NULL_FONCTION)
            {
                Ret_e = (c_AppAct_SysDrv_apf[LLI_u8].Cyclic_pcb)();
            }
        }
    }

    

    return Ret_e;
}
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@note   
 *
 *
 *	@params[in] 
 *	@params[out]
 *	 
 *
 *
 */

