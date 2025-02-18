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
#include "Motor/CL42T/Src/CL42T.h"
#include "APP_LGC/Src/Agents/Gantry/Src/Gantry.h"


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
/**
* @brief App Logic Module State
*/
static t_eCyclicModState g_AppLgc_ModState_e = STATE_CYCLIC_CFG;
/**
* @brief Structure for Service Information 
*/
static t_sAPPLGC_ServiceInfo g_srvFuncInfo_as[APPLGC_SRV_NB];
/**
* @brief Container for Sensors Values
*/
static t_float32 g_snsValues_af32[APPSNS_SENSOR_NB];
/**
* @brief Container for all command Info
*/
static t_sAPPLGC_AppCmdInfo g_CmdInfo_as[APPLGC_RCV_CMD_ID_NB];
/**
* @brief Container to send a Msg for application
*/
static t_uint8 g_sendAppData_ua8[APPLGC_APP_PROTOCOL_LEN_DATA];
/**
* @brief Flag to Reset Service State
*/
static t_bool  g_resetSrvState_b = (t_bool)False; 
/* CAUTION : Automatic generated code section for Variable: Start */
/**
* @brief Actuators Values Containers for Gtry_X
*/
static t_uAPPACT_SetValue g_ActContainerGtry_X_au[APPLGC_GTRY_X_ACT_NB];

/**
* @brief Actuators Values Containers for Gtry_Y
*/
static t_uAPPACT_SetValue g_ActContainerGtry_Y_au[APPLGC_GTRY_Y_ACT_NB];

/**
* @brief Actuators Values Containers for Gtry_Z
*/
static t_uAPPACT_SetValue g_ActContainerGtry_Z_au[APPLGC_GTRY_Z_ACT_NB];

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
*
*/
static t_eReturnCode s_APPLGC_ConfigurationState(void);
/**
*
*	@brief      Get Sensors Values.\n
*
*/

static t_eReturnCode s_APPLGC_GetSnsValues(void);
/**
*
*	@brief      Set Actuators Values Depending on g_srvFuncInfo_as
*/
static t_eReturnCode s_APPLGC_SetActValues(void);
/**
*
*	@brief      Verify that Application still send his bit alive,
*               and send ours.\n
*
*/
static t_eReturnCode s_APPLGC_AppComStateMngmt(void);
/**
*
*	@brief
*	@note   
*
*
*/
static t_eReturnCode s_APPLGC_ResetSrvState(void);
/**
*
*	@brief
*	@note   
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
static void s_APPLGC_DiagnosticEvent(   t_eAPPSDM_DiagnosticItem f_item_e,
                                        t_eAPPSDM_DiagnosticReport f_reportState_e,
                                        t_uint16 f_debugInfo1_u16,
                                        t_uint16 f_debugInfo2_u16);
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
    t_uint8 idxCmd_u8;

    /* CAUTION : Automatic generated code section for Actuators Containers/Service: Start */
    g_srvFuncInfo_as[APPLGC_SRV_GTRY_X].actVal_pau = (t_uAPPACT_SetValue *)(&g_ActContainerGtry_X_au);
    g_srvFuncInfo_as[APPLGC_SRV_GTRY_Y].actVal_pau = (t_uAPPACT_SetValue *)(&g_ActContainerGtry_Y_au);
    g_srvFuncInfo_as[APPLGC_SRV_GTRY_Z].actVal_pau = (t_uAPPACT_SetValue *)(&g_ActContainerGtry_Z_au);
    /* CAUTION : Automatic generated code section for Actuators Containers/Service: End */

    //----- Set Service Init -----//
    for(idxSrv_u8 = (t_uint8)0 ; idxSrv_u8 < APPLGC_SRV_NB ; idxSrv_u8++)
    {

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

    Ret_e = APPSDM_AddCallbackEvnt(s_APPLGC_DiagnosticEvent);

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

    if((f_service_e >= APPLGC_SRV_NB)
    || (f_srvHealth_e >= APPLGC_SRV_HEALTH_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //----- set Health state -----//
        g_srvFuncInfo_as[f_service_e].health_e = f_srvHealth_e; 
    }

    return Ret_e;
}

/*********************************
 * APPLGC_SetServiceHealth
 *********************************/
t_eReturnCode APPLGC_GetServiceHealth(t_eAPPLGC_SrvList f_service_e, t_eAPPLGC_SrvHealth * f_srvHealth_pe)
{
    t_eReturnCode Ret_e = RC_OK;

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
    t_eReturnCode subRet_e = RC_OK;
    t_eReturnCode Ret_e = RC_OK;
    t_sAPPLGC_AppCmdInfo * appCmdInfo_ps;
    t_uint8 checksum_u8;
    t_bool copyCmd_b = False;

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

        if((GETBIT(appCmdInfo_ps->maskEvnt_u8, APPLGC_APP_CMD_BIT_NEW_DATA) == BIT_IS_RESET_8B)
        || (GETBIT(appCmdInfo_ps->maskEvnt_u8, APPLGC_APP_CMD_BIT_WRITE) == BIT_IS_SET_8B))
        {
            //---- defualt value everything will be 0 -----//
            Ret_e = RC_WARNING_NO_OPERATION;
        }
        else 
        {
            //----- Update Flag -----//
            RESETBIT_8B(appCmdInfo_ps->maskEvnt_u8, APPLGC_APP_CMD_BIT_NEW_DATA);

            //----- Do Check Sum ------//
            APPLGC_ComputeCheckSum((appCmdInfo_ps->appData_ua8), 
                                    (APPLGC_APP_PROTOCOL_LEN_DATA - (t_uint8)1),
                                    &checksum_u8);

            if(checksum_u8 != (t_uint8)appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_7])
            {
                Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_APPUSER_COM_CHECKSUM_FAILED,
                                                APPSDM_DIAG_ITEM_REPORT_FAIL,
                                                f_cmdId_e,
                                                checksum_u8);
            }
            else 
            {
                copyCmd_b = (t_bool)False;

                Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_APPUSER_COM_CHECKSUM_FAILED,
                                                APPSDM_DIAG_ITEM_REPORT_PASS,
                                                (t_uint16)0,
                                                (t_uint16)0);
            }
        }
        if(copyCmd_b == (t_bool)True)
        {
            SETBIT_8B(appCmdInfo_ps->maskEvnt_u8, APPLGC_APP_CMD_BIT_READ);
            //----- Switch case on the command wanted -----//
            switch (f_cmdId_e)
            {
                
                case APPLGC_RCV_CMD_ID_DATA_MODE:
                {
                    
                    f_cmdValues_pu->SFMModeInfo_s.mainMode_u8 = appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_1];
                    f_cmdValues_pu->SFMModeInfo_s.prodMode_u8 = appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_2];
                    break;
                }
                case APPLGC_RCV_CMD_ID_GTRY_Z:
                case APPLGC_RCV_CMD_ID_GTRY_Y:
                case APPLGC_RCV_CMD_ID_GTRY_X:
                {
                    

                    f_cmdValues_pu->axe_s.pulse_s32 = Ms32BuildFromByte(   appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_1],
                                                                            appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_2],
                                                                            appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_3],
                                                                            appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_4]);
                    
                    f_cmdValues_pu->axe_s.speed_u16 = Mu16BuildFromByte(   appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_5],
                                                                            appCmdInfo_ps->appData_ua8[APPLGC_CMD_BYTE_6]);
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
            RESETBIT_8B(appCmdInfo_ps->maskEvnt_u8, APPLGC_APP_CMD_BIT_READ);
        }
        else 
        {
            subRet_e = SafeMem_memclear((void *)f_cmdValues_pu, sizeof(t_uAPPLGC_CmdValues));

            if(subRet_e != RC_OK)
            {
                Ret_e = subRet_e;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * APPLGC_ComputeCheckSum
 *********************************/
void APPLGC_ComputeCheckSum(t_uint8 * f_startData_pu8, 
                            t_uint8 f_dataLen_u8,
                            t_uint8 * f_cheksum_pu8)
{
    t_uint32 checksum_u32 = (t_uint32)0;
    t_uint8 idxData_u8;

    for(idxData_u8 = (t_uint8)0; idxData_u8 < f_dataLen_u8 ; idxData_u8++)
    {
        checksum_u32 += f_startData_pu8[idxData_u8];
    }
    
    *f_cheksum_pu8 = (t_uint8)(checksum_u32 & 0xFF); // modulo 256
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
    t_sFMKSRL_DrvSerialCfg SrlCfg_s;
    SrlCfg_s.runMode_e = FMKSRL_LINE_RUNMODE_DMA;
    SrlCfg_s.hwProtType_e = FMKSRL_HW_PROTOCOL_UART;

    SrlCfg_s.hwCfg_s.Baudrate_e = FMKSRL_LINE_BAUDRATE_115200,
    SrlCfg_s.hwCfg_s.Mode_e = FMKSRL_LINE_MODE_RX_TX;
    SrlCfg_s.hwCfg_s.Parity_e = FMKSRL_LINE_PARITY_NONE,
    SrlCfg_s.hwCfg_s.Stopbit_e = FMKSRL_LINE_STOPBIT_1,
    SrlCfg_s.hwCfg_s.wordLenght_e = FMKSRL_LINE_WORDLEN_8BITS,

    SrlCfg_s.CfgSpec_u.uartCfg_s.hwFlowCtrl_e = FMKSRL_UART_HW_FLOW_CTRL_NONE;
    SrlCfg_s.CfgSpec_u.uartCfg_s.Type_e = FMKSRL_UART_TYPECFG_UART,

    Ret_e = FMKSRL_InitDrv( APPLGC_SERIAL_LINE_APP, 
                            SrlCfg_s,
                            s_APPLGC_AppEvntCallback,
                            (t_cbFMKSRL_TransmitMsgEvent *)NULL_FONCTION);
    
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKSRL_ConfigureReception(  APPLGC_SERIAL_LINE_APP,
                                            FMKSRL_OPE_RX_CYCLIC_SIZE,
                                            (t_uint16)APPLGC_APP_PROTOCOL_LEN_DATA);
    }

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
    t_uint8 idxAgent_u8;
    
    if(g_resetSrvState_b == (t_bool)True)
    {
        Ret_e = s_APPLGC_ResetSrvState();
        if(Ret_e == RC_OK)
        {
            g_resetSrvState_b = (t_bool)True;
        }
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_APPLGC_AppComStateMngmt();
    }
    if(Ret_e == RC_OK)
    {
        //------ Get Sensors Values for this cyclic -----//
        Ret_e = s_APPLGC_GetSnsValues();
    }

    //----- Call Agent Periodic Task Depending on Coordinator -----//
    if(Ret_e == RC_OK)
    {   
        for(idxAgent_u8 = (t_uint8)0 ; (idxAgent_u8 < APPLGC_AGENT_NB) &&  (Ret_e >= RC_OK) ; idxAgent_u8++)
        {
            Ret_e = c_AppLGc_AgentFunc_apf[idxAgent_u8].PeriodTask_pcb( (t_float32 *)g_snsValues_af32,
                                                                        (t_sAPPLGC_ServiceInfo *)g_srvFuncInfo_as);
        }
    }

    if(Ret_e >= RC_OK)
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
        snsInfo_s.isValueOK_b = (t_bool)False;
        snsInfo_s.rawValue_f32 = (t_float32)0.0;
        snsInfo_s.SnsValue_f32 = (t_float32)0.0;

        Ret_e = APPSNS_Get_SnsValue((t_eAPPSNS_Sensors)idxSns_u8, &snsInfo_s);

        if((Ret_e == RC_OK)
        && (snsInfo_s.isValueOK_b == (t_bool)true))
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
    t_uint8 idxAct_u8 = (t_uint8)0;
    t_eAPPACT_Actuators actuatorLabel_e;

    //----- Loop on every Service -----//
    for(idxSrv_u8 = (t_uint8)0 ; (idxSrv_u8 < APPLGC_SRV_NB) && (Ret_e == RC_OK) ; idxSrv_u8++)
    {
        //----- Loop on every Actuators For this Service -----//
        for(idxAct_u8 = (t_uint8)0 ; idxAct_u8 < c_AppLGc_SrvActuatorsMax_ua8[idxSrv_u8] ; idxAct_u8++)
        {
            actuatorLabel_e = c_AppLGc_SrvDepedencies_pae[idxSrv_u8][idxAct_u8];

            Ret_e = APPACT_Set_ActValue(actuatorLabel_e, (t_uAPPACT_SetValue)g_srvFuncInfo_as[idxSrv_u8].actVal_pau[idxAct_u8]);

        }
    }

    return Ret_e;
}

/*********************************
 * s_APPLGC_AppEvntCallback
 *********************************/
static void s_APPLGC_AppEvntCallback(   t_uint8 * f_rxData_pu8, 
                                        t_uint16 f_dataSize_u16, 
                                        t_eFMKSRL_RxCallbackInfo f_InfoCb_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_bool receptionComplete_b = False;
    t_uint8 idxCmd_u8;
    static t_uint8 s_idxWrite_u8 = (t_uint8)0;
    static t_uint8 s_appCmd_ua8[APPLGC_CMD_BYTE_NB];

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

            Ret_e = Gantry_RqstSFMState(GTRY_SFM_GANTRY_DEFAULT);
            
        }
        else if (idxCmd_u8 == APPLGC_RCV_CMD_ID_RESET_GTRY_STATE)
        {
            g_resetSrvState_b = (t_bool)True;
        }
        //----- see if someone is reading it -----//
        else if(GETBIT(g_CmdInfo_as[idxCmd_u8].maskEvnt_u8, APPLGC_APP_CMD_BIT_READ) == BIT_IS_SET_8B)
        {
            //----- Send Message with WARNING BUSY -----//
            Ret_e = SafeMem_memclear((void *)g_sendAppData_ua8, APPLGC_APP_PROTOCOL_LEN_DATA);

            if(Ret_e == RC_OK)
            {
                g_sendAppData_ua8[APPLGC_CMD_BYTE_0] = APPLGC_SEND_CMD_ID_GTRY_INFO;
                g_sendAppData_ua8[APPLGC_CMD_BYTE_1] = GTRY_MISSION_BUSY;

                Ret_e = APPLGC_APP_COM_SEND(g_sendAppData_ua8);
            }
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
 * s_APPLGC_DiagnosticEvent
 *********************************/
static void s_APPLGC_DiagnosticEvent(   t_eAPPSDM_DiagnosticItem f_item_e,
                                        t_eAPPSDM_DiagnosticReport f_reportState_e,
                                        t_uint16 f_debugInfo1_u16,
                                        t_uint16 f_debugInfo2_u16)
{
    t_eReturnCode Ret_e = RC_OK;

    Ret_e = SafeMem_memclear((void *)g_sendAppData_ua8, APPLGC_APP_PROTOCOL_LEN_DATA);

    if(Ret_e == RC_OK)
    {
        g_sendAppData_ua8[APPLGC_CMD_BYTE_0] = (t_uint8)APPLGC_SEND_CMD_ID_ERROR_STATUS;
        g_sendAppData_ua8[APPLGC_CMD_BYTE_1] = (t_uint8)f_item_e;
        g_sendAppData_ua8[APPLGC_CMD_BYTE_2] = (t_uint8)f_reportState_e;
        g_sendAppData_ua8[APPLGC_CMD_BYTE_3] = (t_uint8)Mu8ExtractByte1fromU16(f_debugInfo1_u16);
        g_sendAppData_ua8[APPLGC_CMD_BYTE_4] = (t_uint8)Mu8ExtractByte0fromU16(f_debugInfo1_u16);
        g_sendAppData_ua8[APPLGC_CMD_BYTE_5] = (t_uint8)Mu8ExtractByte1fromU16(f_debugInfo2_u16);
        g_sendAppData_ua8[APPLGC_CMD_BYTE_6] = (t_uint8)Mu8ExtractByte0fromU16(f_debugInfo2_u16);

        APPLGC_ComputeCheckSum( g_sendAppData_ua8,
                                (APPLGC_APP_PROTOCOL_LEN_DATA - (t_uint8)1),
                                &g_sendAppData_ua8[APPLGC_CMD_BYTE_7]);
        
        Ret_e = APPLGC_APP_COM_SEND(g_sendAppData_ua8);
    }

    return;
}

/*********************************
 * s_APPLGC_AppComStateMngmt
 *********************************/
static t_eReturnCode s_APPLGC_AppComStateMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_uint32 s_bitAliveRcv_u32 = (t_uint32)0;
    t_uint32 currentTime_u32 = (t_uint32)0;
    t_eGTRY_FSMGantry fsmGTRY_e;

    FMKCPU_Get_Tick(&currentTime_u32);

    //------ Verify AppData Bit Alive  -----//
    if(GETBIT(g_CmdInfo_as[APPLGC_RCV_CMD_ID_BIT_ALIVE].maskEvnt_u8, APPLGC_APP_CMD_BIT_NEW_DATA) == BIT_IS_SET_8B)
    {
        FMKCPU_Get_Tick(&s_bitAliveRcv_u32);
    }

    if((currentTime_u32 - s_bitAliveRcv_u32) > APPLGC_APPUSER_COM_TIMEOUT)
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

    //------ Send Ours  Bit Alive -----//
    Ret_e = SafeMem_memclear((void *)g_sendAppData_ua8, APPLGC_APP_PROTOCOL_LEN_DATA);

    if(Ret_e == RC_OK)
    {
        Ret_e = Gantry_GetFSMState(&fsmGTRY_e);

        if(Ret_e == RC_OK)
        {
            g_sendAppData_ua8[APPLGC_CMD_BYTE_0] = APPLGC_SEND_CMD_ID_ROBOT_INFO;
            g_sendAppData_ua8[APPLGC_CMD_BYTE_1] = g_AppLgc_ModState_e;
            g_sendAppData_ua8[APPLGC_CMD_BYTE_2] = fsmGTRY_e;
            //---- the rest to 0 -----//
            Ret_e = APPLGC_APP_COM_SEND(g_sendAppData_ua8);
        }
    }

    return Ret_e;
}

/*********************************
 * s_APPLGC_ResetSrvState
 *********************************/
static t_eReturnCode s_APPLGC_ResetSrvState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxSrv_u8;

    Ret_e = APPSDM_ResetDiagEvnt();

    if(Ret_e == RC_OK)
    {
        for(idxSrv_u8 = (t_uint8)0 ; 
            (idxSrv_u8 < APPLGC_SRV_NB)
        &&  (Ret_e == RC_OK) ; 
        idxSrv_u8++)
        {
            Ret_e = APPLGC_SetServiceHealth((t_eAPPLGC_SrvList)idxSrv_u8, 
                                            APPLGC_SRV_HEALTH_OK);
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

