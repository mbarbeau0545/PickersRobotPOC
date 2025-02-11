/*********************************************************************
 * @file        APP_LGC.c
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
#include "stdio.h"
#include "string.h"

#include "./APP_LGC.h"
#include "APP_CFG/ConfigFiles/APPLGC_ConfigPrivate.h"
#include "APP_CTRL/APP_ACT/Src/APP_ACT.h"
#include "APP_CTRL/APP_SNS/Src/APP_SNS.h"
#include "APP_CTRL/APP_SDM/Src/APP_SDM.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"

#include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"
#include "Library/SafeMem/SafeMem.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//
enum 
{
    APPLGC_APP_CMD_BIT_WRITE = 0x00,
    APPLGC_APP_CMD_BIT_READ,
    APPLGC_APP_CMD_BIT_NEW_DATA,
};

enum 
{
    APPLGC_CMD_BYTE_0 = 0x00,
    APPLGC_CMD_BYTE_1,
    APPLGC_CMD_BYTE_2,
    APPLGC_CMD_BYTE_3,
    APPLGC_CMD_BYTE_4,
    APPLGC_CMD_BYTE_5,
    APPLGC_CMD_BYTE_6,
    APPLGC_CMD_BYTE_7,

    APPLGC_CMD_BYTE_NB,
};
// Flag Automatic Generated Code 
typedef enum 
{
    APPLGC_RCV_CMD_ID_DATA_MODE = 0x00,
    APPLGC_RCV_CMD_ID_DATA_SPEED_XYZ,
    APPLGC_RCV_CMD_ID_DATA_DIR_XYZ,
    APPLGC_RCV_CMD_ID_DATA_PULSE_XYZ,
    APPLGC_RCV_CMD_ID_EMERGENCY_STOP,
    APPLGC_RCV_CMD_ID_BIT_ALIVE,

    APPLGC_RCV_CMD_ID_NB,
} t_eAPPGC_AppRcvCmdId;

typedef enum 
{
    APPMGC_SND_CMD_ID_GTRY_STATE_XYZ = 0x00,
    APPMGC_SND_CMD_ID_GTRY_MISSION_INFO,
    APPMGC_SND_CMD_ID_GTRY_ROBOT_INFO,

    APPLGC_SND_CMD_ID_NB
} t_eAPPLGC_AppSndCmdId;

/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
typedef struct 
{
    t_uint8 appData_ua8[APPLGC_CMD_BYTE_NB];
    t_uint8 maskEvnt_u8;
} t_sAPPLGC_AppCmdInfo;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
static t_eCyclicModState g_AppLgc_ModState_e = STATE_CYCLIC_CFG;

static t_sAPPLGC_AgentFunc g_AgentInfo_as[APPLGC_AGENT_NB];

static t_sAPPLGC_ServiceInfo g_srvFuncInfo_as[APPLGC_SRV_NB];

static t_float32 g_snsValues_af32[APPSNS_SENSOR_NB];

static t_sAPPLGC_AppCmdInfo g_CmdInfo_as[APPLGC_RCV_CMD_ID_NB];

static t_uint32 g_lastBitAlive_u32 = (t_uint32)0;
/* CAUTION : Automatic generated code section for Variable: Start */
/**
* @brief Actuators Values Containers for Gtry_X
*/
static t_float32 g_ActContainerGtry_X_af32[APPLGC_SRV_GTRY_X_ACT_NB];

/**
* @brief Actuators Values Containers for Gtry_Y
*/
static t_float32 g_ActContainerGtry_Y_af32[APPLGC_SRV_GTRY_Y_ACT_NB];

/**
* @brief Actuators Values Containers for Gtry_Z
*/
static t_float32 g_ActContainerGtry_Z_af32[APPLGC_SRV_GTRY_Z_ACT_NB];

/* CAUTION : Automatic generated code section for Variable: End */
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
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
static t_eReturnCode s_APPLGC_PreOperational(void);
/**
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
static t_eReturnCode s_APPLGC_Operational(void);
/**
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
static t_eReturnCode s_APPLGC_ConfigurationState(void);
/**
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
static t_eReturnCode s_APPLGC_GetSnsValues(void);
/**
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
static t_eReturnCode s_APPLGC_SetActValues(void);
/**
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
static void s_APPLGC_AppEvntCallback(  t_uint8 * f_rxData_pu8, 
                                    t_uint16 f_dataSize_u16, 
                                    t_eFMKSRL_RxCallbackInfo f_InfoCb_e);
/**
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
static void s_APPLGC_TranmistEvnt(t_bool f_isMsgTransmit_b, t_eFMKSRL_TxCallbackInfo f_InfoCb_e);

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * APPLGC_Init
 *********************************/
t_eReturnCode APPLGC_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxAgent_u8 = (t_uint8)0; 
    t_uint8 idxSrv_u8 = (t_uint8)0;
    t_uint8 idxAct_u8 = (t_uint8)0;
    t_uint8 idxAppData_u8;
    t_uint8 idxCmd_u8;

    /* CAUTION : Automatic generated code section for Actuators Containers/Service: Start */
   g_srvFuncInfo_as[APPLGC_SRV_GTRY_X].actValues_paf32 = (t_float32 *)(&g_ActContainerGtry_X_af32);
   g_srvFuncInfo_as[APPLGC_SRV_GTRY_Y].actValues_paf32 = (t_float32 *)(&g_ActContainerGtry_Y_af32);
   g_srvFuncInfo_as[APPLGC_SRV_GTRY_Z].actValues_paf32 = (t_float32 *)(&g_ActContainerGtry_Z_af32);
    /* CAUTION : Automatic generated code section for Actuators Containers/Service: End */

    //----- Set Service Init -----//
    for(idxSrv_u8 = (t_uint8)0 ; idxSrv_u8 < APPLGC_SRV_NB ; idxSrv_u8++)
    {
        for(idxAct_u8 = (t_uint8)0; idxAct_u8 < c_AppLGc_SrvActuatorsMax_ua8[idxAct_u8] ; idxAct_u8++)
        {
            g_srvFuncInfo_as[idxSrv_u8].actValues_paf32[idxAct_u8] = (t_float32)0.0;
        }
        
        g_srvFuncInfo_as[idxSrv_u8].health_e = APPLGC_SRV_HEALTH_OK;
        g_srvFuncInfo_as[idxSrv_u8].state_e = APPLGC_SRV_STATE_NB;
        
    }

    //---- Set Agent Init -----//
    for(idxAgent_u8 = (t_uint8)0 ; (idxAgent_u8 < APPLGC_AGENT_NB) && (Ret_e == RC_OK) ; idxAgent_u8++)
    {
        Ret_e = c_AppLGc_AgentFunc_apf[idxAgent_u8].init_pcb();
    }

    //---- Set Command Init -----//
    for(idxCmd_u8 = (t_uint8)0 ; (idxCmd_u8 < APPLGC_RCV_CMD_ID_NB) && (Ret_e == RC_OK) ; idxCmd_u8++)
    {
        Ret_e = SafeMem_memclear((void *)g_CmdInfo_as[idxCmd_u8].appData_ua8, APPLGC_CMD_BYTE_NB);
        g_CmdInfo_as[idxCmd_u8].maskEvnt_u8 = (t_uint8)0;
    }
    return Ret_e;


}

/*********************************
 * APPLGC_Cyclic
 *********************************/
t_eReturnCode APPLGC_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;
    // code to run every x milliseconds, config in APPSYS_ConfigPrivate.h

    switch (g_AppLgc_ModState_e)
    {
    case STATE_CYCLIC_CFG:
    {
        Ret_e = s_APPLGC_ConfigurationState();
        if(Ret_e == RC_OK)
        {
            g_AppLgc_ModState_e = STATE_CYCLIC_WAITING;
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
        Ret_e = s_APPLGC_PreOperational();

        if(Ret_e == RC_OK)
        {
            g_AppLgc_ModState_e = STATE_CYCLIC_OPE;
        }
    
        break;
    }
    case STATE_CYCLIC_OPE:
    {
        Ret_e = s_APPLGC_Operational();
        if(Ret_e < RC_OK)
        {
            g_AppLgc_ModState_e = STATE_CYCLIC_ERROR;
        }
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
 * APPLGC_GetState
 *********************************/
t_eReturnCode APPLGC_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_AppLgc_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * APPLGC_SetState
 *********************************/
t_eReturnCode APPLGC_SetState(t_eCyclicModState f_State_e)
{

    g_AppLgc_ModState_e = f_State_e;

    return RC_OK;
}

/*********************************
 * APPLGC_SetServiceHealth
 *********************************/
t_eReturnCode APPLGC_SetServiceHealth(t_eAPPLGC_SrvList f_service_e, t_eAPPLGC_SrvHealth f_srvHealth_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxAct_u8 = (t_uint8)0;
    t_eAPPACT_Actuators actuator_e;

    if((f_service_e >= APPLGC_SRV_NB)
    || (f_srvHealth_e >= APPLGC_SRV_HEALTH_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //----- set Health state -----//
        g_srvFuncInfo_as[f_service_e].health_e = f_srvHealth_e; 

        //----- if state is OFF, disable all act value instantly -----//
        if(f_srvHealth_e == APPLGC_SRV_HEALTH_ERROR)
        {
            for(idxAct_u8 = (t_uint8)0 ; idxAct_u8 < c_AppLGc_SrvActuatorsMax_ua8[idxAct_u8] ; idxAct_u8++)
            {
                g_srvFuncInfo_as[f_service_e].actValues_paf32[idxAct_u8] = (t_float32)0.0;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * APPLGC_SetServiceHealth
 *********************************/
t_eReturnCode APPLGC_GetServiceHealth(t_eAPPLGC_SrvList f_service_e, t_eAPPLGC_SrvHealth * f_srvHealth_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxAct_u8 = (t_uint8)0;
    t_eAPPACT_Actuators actuator_e;

    if(f_service_e >= APPLGC_SRV_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_srvHealth_pe == (t_eAPPLGC_SrvHealth *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        *f_srvHealth_pe = g_srvFuncInfo_as[f_service_e].health_e;
    }

    return Ret_e;
}

/*********************************
 * APPLGC_GetAppCmd
 *********************************/
t_eReturnCode APPLGC_GetAppCmd(t_eAPPGC_AppRcvCmdId f_cmdId_e, t_uAPPLGC_CmdValues * f_cmdValues_pu)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sAPPLGC_AppCmdInfo * appCmdInfo_ps;
    if(f_cmdId_e >= APPLGC_RCV_CMD_ID_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_cmdValues_pu == (t_uAPPLGC_CmdValues *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_AppLgc_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(Ret_e == RC_OK)
    {
        appCmdInfo_ps = (t_sAPPLGC_AppCmdInfo *)(&g_CmdInfo_as[f_cmdId_e]);
        switch (f_cmdId_e)
        {
            
            case APPLGC_RCV_CMD_ID_DATA_MODE:
            {
                if(GETBIT(appCmdInfo_ps->maskEvnt_u8, APPLGC_APP_CMD_BIT_NEW_DATA) == BIT_IS_SET_8B)
                {
                    f_cmdValues_pu->SFMModeInfo_s.mainMode_u8 = appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_1];
                    f_cmdValues_pu->SFMModeInfo_s.prodMode_u8 = appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_2];

                    RESETBIT_8B(appCmdInfo_ps->maskEvnt_u8, APPLGC_APP_CMD_BIT_NEW_DATA);
                }
                else
                {
                    f_cmdValues_pu->SFMModeInfo_s.mainMode_u8 = (t_uint8)0;
                    f_cmdValues_pu->SFMModeInfo_s.prodMode_u8 = (t_uint8)0;
                    Ret_e = RC_WARNING_NO_OPERATION;
                } 
                break;
            }
            case APPLGC_RCV_CMD_ID_DATA_SPEED_XYZ:
            {
                f_cmdValues_pu->speedInfo_s.speedX_u16 = Mu16BuildFromByte( appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_1],
                                                                            appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_2]);
                
                f_cmdValues_pu->speedInfo_s.speedY_u16 = Mu16BuildFromByte( appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_3],
                                                                            appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_4]);

                f_cmdValues_pu->speedInfo_s.speedZ_u16 = Mu16BuildFromByte( appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_5],
                                                                            appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_6]);
                break;
            }
            case APPLGC_RCV_CMD_ID_DATA_DIR_XYZ:
            {
                f_cmdValues_pu->dirInfo_s.DirX_u16 = Mu16BuildFromByte( appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_1],
                                                                            appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_2]);
                
                f_cmdValues_pu->dirInfo_s.DirY_u16 = Mu16BuildFromByte( appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_3],
                                                                        appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_4]);

                f_cmdValues_pu->dirInfo_s.DirZ_u16 = Mu16BuildFromByte( appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_5],
                                                                        appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_6]);
                break;
            }
            case APPLGC_RCV_CMD_ID_DATA_PULSE_XYZ:
            {
                if(GETBIT(appCmdInfo_ps->maskEvnt_u8, APPLGC_APP_CMD_BIT_NEW_DATA) == BIT_IS_SET_8B)
                {
                    f_cmdValues_pu->pulseInfo_s.nbPulseX_u16 = Mu16BuildFromByte(   appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_1],
                        appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_2]);

                    f_cmdValues_pu->pulseInfo_s.nbPulseY_u16 = Mu16BuildFromByte(   appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_3],
                                            appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_4]);

                    f_cmdValues_pu->pulseInfo_s.nbPulseZ_u16 = Mu16BuildFromByte(   appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_5],
                                            appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_6]);
                    
                    RESETBIT_8B(appCmdInfo_ps->maskEvnt_u8, APPLGC_APP_CMD_BIT_NEW_DATA);
                }
                else 
                {
                    f_cmdValues_pu->pulseInfo_s.nbPulseX_u16 = (t_uint16)0;
                    f_cmdValues_pu->pulseInfo_s.nbPulseY_u16 = (t_uint16)0;
                    f_cmdValues_pu->pulseInfo_s.nbPulseZ_u16 = (t_uint16)0;
                }
                break;
            }
            case APPLGC_RCV_CMD_ID_EMERGENCY_STOP:
            case APPLGC_RCV_CMD_ID_BIT_ALIVE:
            case APPLGC_RCV_CMD_ID_NB:
            default:
            {
                Ret_e = RC_WARNING_NO_OPERATION;
            }

        }
    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************

/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_ConfigurationState(void)
{
    t_eReturnCode Ret_e = RC_OK;

    return Ret_e;
}

/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_PreOperational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    Ret_e = APPSDM_ResetDiagEvnt();
    return Ret_e;
}

/*********************************
 * s_APPLGC_Operational
 *********************************/
static t_eReturnCode s_APPLGC_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxAgent_u8 = (t_uint8)0;
    t_uint32 currentTime_u32 = (t_uint32)0;
    
    FMKCPU_Get_Tick(&currentTime_u32);

    //------ Verify AppData Bit Alive  -----//
    if(GETBIT(g_CmdInfo_as[APPLGC_RCV_CMD_ID_BIT_ALIVE].maskEvnt_u8, APPLGC_APP_CMD_BIT_NEW_DATA) == BIT_IS_SET_8B)
    {
        FMKCPU_Get_Tick(&g_lastBitAlive_u32);
    }
    else 
    {
        if((currentTime_u32 - g_lastBitAlive_u32) > APPLGC_APPUSER_COM_TIMEOUT)
        {
            g_AppLgc_ModState_e = STATE_CYCLIC_ERROR;
            Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_APPUSER_COMMUNICATION_FAILED,
                                            APPSDM_DIAG_ITEM_REPORT_FAIL,
                                            APPLGC_APPUSER_ERR_RX,
                                            (t_uint16)0);
        }
        else 
        {
            Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_APPUSER_COMMUNICATION_FAILED,
                                            APPSDM_DIAG_ITEM_REPORT_PASS,
                                            APPLGC_APPUSER_ERR_RX,
                                            (t_uint16)0);
        }
    }
    if(Ret_e == RC_OK)
    {
        //------ Get Sensors Values for this cyclic -----//
        Ret_e = s_APPLGC_GetSnsValues();
    }

    //----- Call Agent Periodic Task Depending on Coordinator -----//
    if(Ret_e == RC_OK)
    {   
        for(idxAgent_u8 = (t_uint8)0 ; (idxAgent_u8 < APPLGC_AGENT_NB) &&  (Ret_e == RC_OK) ; idxAgent_u8)
        {
            Ret_e = c_AppLGc_AgentFunc_apf[idxAgent_u8].PeriodTask_pcb((t_float32 *)g_snsValues_af32,
                                                                        (t_sAPPLGC_ServiceInfo *)g_srvFuncInfo_as);
        }
    }

    //----- Set Actuators values -----//
    if(Ret_e == RC_OK)
    {
        Ret_e = s_APPLGC_SetActValues();
    }
    return Ret_e;
}

/*********************************
 * s_APPLGC_GetSnsValues
 *********************************/
static t_eReturnCode s_APPLGC_GetSnsValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sAPPSNS_SnsInfo snsInfo_s;
    t_uint8 idxSns_u8 = (t_uint8)0;

    for(idxSns_u8 = (t_uint8)0 ; (idxSns_u8 < APPSNS_SENSOR_NB) && (Ret_e == RC_OK) ; idxSns_u8++)
    {
        //----- Reset Container values -----//
        snsInfo_s.IsValueOK_b = (t_bool)False;
        snsInfo_s.rawValue_f32 = (t_float32)0.0;
        snsInfo_s.SnsValue_f32 = (t_float32)0.0;

        Ret_e = APPSNS_Get_SnsValue((t_eAPPSNS_Sensors)idxSns_u8, &snsInfo_s);

        if((Ret_e == RC_OK)
        && (snsInfo_s.IsValueOK_b == (t_bool)true))
        {
            g_snsValues_af32[idxSns_u8] = snsInfo_s.SnsValue_f32;
        }
    }
    
    return Ret_e;
}

/*********************************
 * s_APPLGC_SetActValues
 *********************************/
static t_eReturnCode s_APPLGC_SetActValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxSrv_u8 = (t_uint8)0;
    t_uint8 idxSrvAct_u8 = (t_uint8)0;
    t_eAPPACT_Actuators srvActuator_e;
    t_sAPPLGC_ServiceInfo * srvInfo_ps;

    //----- Loop on every Service -----//
    for(idxSrv_u8 = (t_uint8)0 ; (idxSrv_u8 < APPLGC_SRV_NB) && (Ret_e == RC_OK) ; idxSrv_u8++)
    {
        srvInfo_ps = (t_sAPPLGC_ServiceInfo *)(&g_srvFuncInfo_as[idxSrv_u8]);
        //----- Loop on every Actuators on that service 
        for(idxSrvAct_u8 = (t_uint8)0 ; 
            (idxSrvAct_u8 < c_AppLGc_SrvActuatorsMax_ua8[idxSrv_u8]) 
        &&  (Ret_e == RC_OK) ; 
        idxSrvAct_u8++)
        {
            srvActuator_e = c_AppLGc_SrvDepedencies_pae[idxSrv_u8][idxSrvAct_u8];
            Ret_e = APPACT_Set_ActValue(srvActuator_e, srvInfo_ps->actValues_paf32[idxSrvAct_u8]);
        }
    }

    return Ret_e;
}
/*********************************
 * s_MotorCallback
 *********************************/
static void s_APPLGC_AppEvntCallback(   t_uint8 * f_rxData_pu8, 
                                        t_uint16 f_dataSize_u16, 
                                        t_eFMKSRL_RxCallbackInfo f_InfoCb_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_bool receptionComplete_b = False;
    t_uint8 idxCmd_u8;
    static t_uint8 s_idxWrite_u8 = (t_uint8)0;
    static s_appCmd_ua8[APPLGC_CMD_BYTE_NB];

    if(f_dataSize_u16 > APPLGC_CMD_BYTE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(s_idxWrite_u8 >= APPLGC_CMD_BYTE_NB)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_InfoCb_e)
        {
            case FMKSRL_CB_INFO_RECEIVE_PENDING:
            {
                Ret_e = SafeMem_memcpy( (void *)(&s_appCmd_ua8[s_idxWrite_u8]),
                                        (const void *)f_rxData_pu8,
                                        f_dataSize_u16);
                break;
            }
            case FMKSRL_CB_INFO_RECEIVE_ENDING:
            {
                Ret_e = SafeMem_memcpy( (void *)(&s_appCmd_ua8[s_idxWrite_u8]),
                                        (const void *)f_rxData_pu8,
                                        f_dataSize_u16);
                if(Ret_e == RC_OK)
                {
                    s_idxWrite_u8 = (t_uint8)0;
                    receptionComplete_b = (t_bool)True;
                }
                break;
            }
            case FMKSRL_CB_INFO_RECEIVE_ERR:
            case FMKSRL_CB_INFO_RECEIVE_OVERFLOW:
            {
                //----- Report Diagnostic Evnt -----//
                Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_APPUSER_COMMUNICATION_FAILED,
                                                APPSDM_DIAG_ITEM_REPORT_FAIL,
                                                APPLGC_APPUSER_ERR_RX,
                                                f_InfoCb_e);
                break;
            }
        }
    }
    if((receptionComplete_b == (t_bool)True)
    && (Ret_e == RC_OK))
    {
        //----- Diagnostic Passed -----//
        Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_APPUSER_COMMUNICATION_FAILED,
                                        APPSDM_DIAG_ITEM_REPORT_PASS,
                                        0,
                                        0);
        
        //------ Retrieve idx command from appCmd -----//
        idxCmd_u8 = s_appCmd_ua8[APPLGC_CMD_BYTE_0];

        //----- Check now for Emergency Stop -----//
        if(idxCmd_u8 == APPLGC_RCV_CMD_ID_EMERGENCY_STOP)
        {
            Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_GANTRY_MVMT_ERROR,
                                            APPSDM_DIAG_ITEM_REPORT_FAIL,
                                            0,
                                            0);
        }
        //----- see if someone is reading it -----//
        if(GETBIT(g_CmdInfo_as[idxCmd_u8].maskEvnt_u8, APPLGC_APP_CMD_BIT_READ) == BIT_IS_SET_8B)
        {
            //----- Send Message with WARNING BUSY -----//
        }
        else 
        {
            SETBIT_8B(g_CmdInfo_as[idxCmd_u8].maskEvnt_u8, APPLGC_APP_CMD_BIT_WRITE);

            //----- copy data -----//
            Ret_e = SafeMem_memcpy( (void *)(g_CmdInfo_as[idxCmd_u8].appData_ua8),
                                    (const void *)(s_appCmd_ua8),
                                    f_dataSize_u16);
            
            RESETBIT_8B(g_CmdInfo_as[idxCmd_u8].maskEvnt_u8, APPLGC_APP_CMD_BIT_WRITE);
            SETBIT_8B(g_CmdInfo_as[idxCmd_u8].maskEvnt_u8, APPLGC_APP_CMD_BIT_NEW_DATA);
            Ret_e = SafeMem_memclear((void *)s_appCmd_ua8, APPLGC_CMD_BYTE_NB);
        }
    }
    return;
}

/*********************************
 * s_APPLGC_TranmistEvnt
 *********************************/
static void s_APPLGC_TranmistEvnt(t_bool f_isMsgTransmit_b, t_eFMKSRL_TxCallbackInfo f_InfoCb_e)
{
    return;
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

