/*********************************************************************
 * @file        APP_SYS.c
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
#include "./APP_CFG/ConfigFiles/APPSYS_ConfigPrivate.h"
#include "./APP_SYS.h"
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
t_eCyclicFuncState g_ModuleState_ae[APPSYS_MODULE_NB];
static t_eCyclicFuncState g_AppSysModuleState_e = STATE_CYCLIC_PREOPE;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
*
*	@brief  Call driver cyclic function
*
*/
static t_eReturnState s_APPSYS_PreOperational();
/**
*
*	@brief  Call driver cyclic function
*
*/
static t_eReturnState s_APPSYS_Operational();
/**
*
*	@brief  Call driver cyclic function
*
*/
static t_eReturnState s_APPSYS_Set_ModulesCyclic();
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * APPSYS_Init
 *********************************/
void APPSYS_Init(void)
{
    t_eReturnState Ret_e = RC_OK;
    static t_bool s_IsSysCfgDone_b = False;
    t_uint8 LLI_u8 = 0;
    // set sys confgiguration 
    if( s_IsSysCfgDone_b == (t_bool)False)
    {
        Ret_e = FMKCPU_Set_HardwareInit();
        if(Ret_e == RC_OK)
        {
            Ret_e = FMKCPU_Set_SysClockCfg();
        }
        if(Ret_e == RC_OK)
        {
            //Ret_e = FMKCPU_Set_WwdgCfg((t_eFMKCPu_WwdgResetPeriod)FMKCPU_WWDG_RESET_CFG);
        }
        if(Ret_e == RC_OK)
        {
            s_IsSysCfgDone_b = (t_bool)True;
        }
    }
    if(Ret_e == RC_OK)
    {
        for(LLI_u8 = (t_uint8)0 ; (LLI_u8 < APPSYS_MODULE_NB) && (Ret_e == RC_OK) ; LLI_u8++)
        {
            Ret_e = c_AppSys_ModuleFunc_apf[LLI_u8].Init_pcb();
        }
    }
    else
    {
        g_AppSysModuleState_e = STATE_CYCLIC_ERROR;
    }
    return;
}
/*********************************
 * APPSYS_Init
 *********************************/
void APPSYS_Cyclic(void)
{
    t_eReturnState Ret_e = RC_OK;
     
    switch(g_AppSysModuleState_e)
    {
        case STATE_CYCLIC_PREOPE:
        {/* In Preope Mode AppSys called every cycle and wait every module are ready for Ope Mode*/
            Ret_e = s_APPSYS_PreOperational();
            if(Ret_e == RC_OK)
            {
                g_AppSysModuleState_e = STATE_CYCLIC_OPE;
            }
            break;
        }
        case STATE_CYCLIC_OPE:
        {
            Ret_e = s_APPSYS_Operational();
            break;
        }
        case STATE_CYCLIC_BUSY:
        {
            break;
        }
        case STATE_CYCLIC_WAITING:
        case STATE_CYCLIC_ERROR:
        default:
        {
            // Nothing to do infinite loop
            break;
        }
    }

    return;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_APPSYS_Set_ModulesCyclic
 *********************************/
static t_eReturnState s_APPSYS_Set_ModulesCyclic(void)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint8 LLI_u8;

    for(LLI_u8 = (t_uint8)0 ; (LLI_u8 < (t_uint8)APPSYS_MODULE_NB) && (Ret_e >= RC_OK) ; LLI_u8++)
    {
        if(c_AppSys_ModuleFunc_apf[LLI_u8].Cyclic_pcb != NULL_FONCTION)
        {
            Ret_e = c_AppSys_ModuleFunc_apf[LLI_u8].Cyclic_pcb();  
        }
    }
    return Ret_e;
}

/*********************************
 * s_APPSYS_PreOperational
 *********************************/
static t_eReturnState s_APPSYS_PreOperational(void)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint8 LLI_u8;
    t_uint8 ModuleInitCnt_u8 = 0;

    Ret_e = s_APPSYS_Set_ModulesCyclic();
    if(Ret_e == RC_OK)
    {//  get the state of all modules
        for(LLI_u8 = (t_uint8)0 ; (LLI_u8 <  (t_uint8)APPSYS_MODULE_NB) && (Ret_e == RC_OK) ; LLI_u8++)
        {
            Ret_e = c_AppSys_ModuleFunc_apf[LLI_u8].GetState_pcb(&g_ModuleState_ae[LLI_u8]);
            if(g_ModuleState_ae[LLI_u8] == STATE_CYCLIC_WAITING)
            {
                ModuleInitCnt_u8 += 1;
            }
        }
    }
    if(ModuleInitCnt_u8 >= (t_uint8)APPSYS_MODULE_NB)
    {// set the all state module to ope
        for(LLI_u8 = (t_uint8)0 ; (LLI_u8 <  (t_uint8)APPSYS_MODULE_NB) && (Ret_e == RC_OK) ; LLI_u8++)
        {
            if(g_ModuleState_ae[LLI_u8] == STATE_CYCLIC_WAITING)
            {
                Ret_e = c_AppSys_ModuleFunc_apf[LLI_u8].SetState_pcb(STATE_CYCLIC_OPE);
            }
        }
    }
    else 
    {
        Ret_e = RC_WARNING_BUSY;
    }
    return Ret_e;
}

/*********************************
 * s_APPSYS_Operational
 *********************************/
static t_eReturnState s_APPSYS_Operational(void)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint32 currentCnt_u32 = 0;
    static t_uint32 s_previousCnt_u32 = 0;
    t_uint32 elapsedTime_u32 =  0;

    FMKCPU_Get_Tick(&currentCnt_u32);

    //Ret_e = FMKCPU_ResetWwdg();
    
    if(Ret_e == RC_OK)
    {
        elapsedTime_u32 = (t_uint32)(currentCnt_u32 - s_previousCnt_u32);
        if((elapsedTime_u32) > APPSYS_ELAPSED_TIME_CYCLIC)
        {
            // reset whatchdog for fmk/app cycle
            s_previousCnt_u32 = currentCnt_u32;
            Ret_e = s_APPSYS_Set_ModulesCyclic();
        
            if(Ret_e == RC_OK)
            {
                // reset watchdog for logic cycle
                //Ret_e = FMKCPU_ResetWwdg();
                Ret_e = APPLGC_Cyclic();
            }
            if(Ret_e < RC_OK)
            {
                // deal with error
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