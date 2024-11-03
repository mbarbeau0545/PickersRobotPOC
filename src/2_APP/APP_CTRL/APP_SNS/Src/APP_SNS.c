/*********************************************************************
 * @file        APP_SNS.c
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

#include "./APP_SNS.h"
#include "APP_CFG/ConfigFiles/APPSNS_ConfigPrivate.h"
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

/* CAUTION : Automatic generated code section for Variable: End */
static t_eCyclicFuncState g_state_e = STATE_CYCLIC_PREOPE;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/*****************************************************************************
*
*	@brief
*	@note   
*
*
*	@param[in] 
*	@param[out]
*	 
*
*
*/
static t_eReturnState s_APPSNS_PreOperational(void);
/**
 *
 *	@brief      Perform preOperationnal action.\n
 *  @note       Set the sensor configuration.\n
 *              Call driver init function.\n
 *              If one of the configuration is not set the Module Cyclic 
 *              retry indefinitely.\n
 *              
 * 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE

 */
static t_eReturnState s_APPSNS_Operational(void);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * APPSNS_Init
 *********************************/
t_eReturnState APPSNS_Init(void)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint8 idxSns_u8;

    // check sensors cfg
    for(idxSns_u8 = (t_uint8)0 ; (idxSns_u8 < APPSNS_SENSOR_NB) && (Ret_e == RC_OK) ; idxSns_u8++)
    {   
        if(c_AppSns_SysSns_apf[idxSns_u8].GetValue_pcb == (t_cbAppSns_GetSnsValue *)NULL_FONCTION
        || c_AppSns_SysSns_apf[idxSns_u8].SetCfg_pcb == (t_cbAppSns_SetSnsCfg *)NULL_FONCTION
        || c_AppSns_SysSns_apf[idxSns_u8].measTyp_e > APPSNS_MEASTYPE_NB)
        {
            Ret_e = RC_ERROR_PARAM_INVALID;
        }
    }
    // check configuration validity 

    return Ret_e;
}
/*********************************
 * APPSNS_Init
 *********************************/
t_eReturnState APPSNS_Cyclic(void)
{
    t_eReturnState Ret_e = RC_OK;

    switch (g_state_e)
    {
    case STATE_CYCLIC_PREOPE:
    {
        Ret_e = s_APPSNS_PreOperational();
        if(Ret_e == RC_OK)
        {
            g_state_e = STATE_CYCLIC_WAITING;
        }
        break;
    }
    case STATE_CYCLIC_WAITING:
    {
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_OPE:
    {
        Ret_e = s_APPSNS_Operational();
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
 * APPSNS_GetState
 *********************************/
t_eReturnState APPSNS_GetState(t_eCyclicFuncState *f_State_pe)
{
    t_eReturnState Ret_e = RC_OK;
    
    if(f_State_pe == (t_eCyclicFuncState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_state_e;
    }
    return Ret_e;
}
/*********************************
 * APPSNS_GetState
 *********************************/
t_eReturnState APPSNS_SetState(t_eCyclicFuncState f_State_e)
{
    g_state_e = f_State_e;
    return RC_OK;
}

/*********************************
 * APPSNS_Get_SnsValue
 *********************************/
t_eReturnState APPSNS_Get_SnsValue(t_eAPPSNS_Sensors f_Sns_e, t_sint16 *f_SnsValue_ps16)
{
    t_eReturnState Ret_e = RC_OK;
    t_sAPPSNS_ValueInfo valInfo_s = {0};

    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(f_SnsValue_ps16 == (t_sint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(f_Sns_e > APPSNS_SENSOR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        // call specific function to get value
        if(c_AppSns_SysSns_apf[f_Sns_e].GetValue_pcb != (t_cbAppSns_GetSnsValue *)NULL_FONCTION)
        {
            Ret_e = (c_AppSns_SysSns_apf[f_Sns_e].GetValue_pcb)(&valInfo_s);
            if(Ret_e == RC_OK)
            {
                // TO DO
            }
        }
        else 
        {
            Ret_e = RC_ERROR_PTR_NULL;
        }
    }

    return Ret_e;
}

//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_APPSNS_PreOperational
 *********************************/
static t_eReturnState s_APPSNS_PreOperational(void)
{
    t_eReturnState Ret_e = RC_OK;
    static t_uint8 s_LLDRV_u8 = 0;
    static t_uint8 s_LLSNS_u8 = 0;
    // driver init
    for(; (s_LLDRV_u8 < APPSNS_DRIVER_NB) && (Ret_e == RC_OK) ; s_LLDRV_u8++)
    {
        if(c_AppSns_SysDrv_apf[s_LLDRV_u8].Init_pcb != (t_cbAppSns_DrvInit *)NULL_FONCTION)
        {
            Ret_e = (c_AppSns_SysDrv_apf[s_LLDRV_u8].Init_pcb)();
        }
        else
        {
            Ret_e = RC_ERROR_PTR_NULL;
        }
    }
    // sensors configuration call
    for(; (s_LLSNS_u8 < APPSNS_SENSOR_NB) && (Ret_e == RC_OK) ; s_LLSNS_u8++)
    {
        if(c_AppSns_SysSns_apf[s_LLDRV_u8].SetCfg_pcb != (t_cbAppSns_SetSnsCfg *)NULL_FONCTION)
        {
            Ret_e = (c_AppSns_SysSns_apf[s_LLSNS_u8].SetCfg_pcb)();
        }
        else
        {
            Ret_e = RC_ERROR_PTR_NULL;
        }
    }
    if( s_LLDRV_u8 < APPSNS_DRIVER_NB
    &&  s_LLSNS_u8 < APPSNS_SENSOR_NB
    && Ret_e == RC_OK) // only if problem has not been captured yet
    {// problem or waiting on init or sensors config just waiting for next cycle
        Ret_e = RC_WARNING_BUSY;
    }

    return Ret_e;
}
/*********************************
 * s_APPSNS_Operational
 *********************************/
static t_eReturnState s_APPSNS_Operational(void)
{
    t_eReturnState Ret_e = RC_OK;
    static t_bool s_IsDrvCylic_b = True;
    t_uint8 DrvCyclicCnt_u8 = 0;
    t_uint8 LLI_u8; 

    if(s_IsDrvCylic_b == (t_bool)True)
    {
        for(LLI_u8 = (t_uint8)0 ; (LLI_u8 < APPSNS_DRIVER_NB) && (Ret_e == RC_OK); LLI_u8++)
        {

            if(c_AppSns_SysDrv_apf[LLI_u8].Cyclic_pcb != (t_cbAppSns_DrvCyclic *)NULL_FONCTION)
            {
                Ret_e = (c_AppSns_SysDrv_apf[LLI_u8].Cyclic_pcb)();
            }
            
            else
            {
                DrvCyclicCnt_u8 += (t_uint8)1;
            }
        }
        if(DrvCyclicCnt_u8 == (t_uint8)0)
        {
            s_IsDrvCylic_b = (t_bool)False;
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

