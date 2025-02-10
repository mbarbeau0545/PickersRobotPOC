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
#include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"
#include "Motor/CL42T/Src/CL42T.h"
#include "APP_CFG/ConfigFiles/CL42T_ConfigPublic.h"
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
} t_eAPPGC_AppSendCmdId;

typedef enum 
{
    APPMGC_SND_CMD_ID_GTRY_STATE_XYZ = 0x00,
    APPMGC_SND_CMD_ID_GTRY_MISSION_INFO,
    APPMGC_SND_CMD_ID_GTRY_ROBOT_INFO,

    APPLGC_SND_CMD_ID_NB
};

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
static t_eCyclicModState g_AppLgc_ModState_e = STATE_CYCLIC_CFG;

static t_sAPPLGC_AgentFunc g_AgentInfo_as[APPLGC_AGENT_NB];

static t_sAPPLGC_ServiceInfo g_srvFuncInfo_as[APPLGC_SRV_NB];

static t_float32 g_snsValues_af32[APPSNS_SENSOR_NB];
/* CAUTION : Automatic generated code section for Variable: Start */
/**
* @brief Actuators Values Containers for Gantry_X
*/
static t_float32 g_ActContainerGantry_X_af32[APPLGC_SRV_GANTRY_X_ACT_NB];

/**
* @brief Actuators Values Containers for Gantry_Y
*/
static t_float32 g_ActContainerGantry_Y_af32[APPLGC_SRV_GANTRY_Y_ACT_NB];

/**
* @brief Actuators Values Containers for Gantry_Z
*/
static t_float32 g_ActContainerGantry_Z_af32[APPLGC_SRV_GANTRY_Z_ACT_NB];

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


static void s_MotorCallback(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_DefeultInfo_e);
static void s_APPLGC_RcvSrlEvent(  t_uint8 * f_rxData_pu8, 
                                    t_uint16 f_dataSize_u16, 
                                    t_eFMKSRL_RxCallbackInfo f_InfoCb_e);

static void s_APPLGC_TranmistEvnt(t_bool f_isMsgTransmit_b, t_eFMKSRL_TxCallbackInfo f_InfoCb_e);
static void s_PulseCallback(t_eFMKIO_OutPwmSig f_signal_e);
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
    t_uint8 idxSrv_u8 = (t_uint8)0;;
    t_uint8 idxAct_u8 = (t_uint8)0;;

    /* CAUTION : Automatic generated code section for Actuators Containers/Service: Start */
   g_srvFuncInfo_as[APPLGC_SRV_GANTRY_X].actValues_paf32 = (t_float32 *)(&g_ActContainerGantry_X_af32);
   g_srvFuncInfo_as[APPLGC_SRV_GANTRY_Y].actValues_paf32 = (t_float32 *)(&g_ActContainerGantry_Y_af32);
   g_srvFuncInfo_as[APPLGC_SRV_GANTRY_Z].actValues_paf32 = (t_float32 *)(&g_ActContainerGantry_Z_af32);
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
    return Ret_e;
}

/*********************************
 * APPLGC_Init
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

    return Ret_e;
}

/*********************************
 * s_APPLGC_Operational
 *********************************/
static t_eReturnCode s_APPLGC_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxAgent_u8 = (t_uint8)0;
    
    //------ Get Sensors Values for this cyclic -----//
    Ret_e = s_APPLGC_GetSnsValues();

    //----- Call Agent Periodic Task Depending on Coordinator -----//
    if(Ret_e == RC_OK)
    {   
        for(idxAgent_u8 = (t_uint8)0 ; (idxAgent_u8 < APPLGC_AGENT_NB) &&  (Ret_e == RC_OK) ; idxAgent_u8)
        {
            Ret_e = c_AppLGc_AgentFunc_apf[idxAgent_u8].PeriodiTask_pcb((t_float32 *)g_snsValues_af32,
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
static void s_MotorCallback(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_DefeultInfo_e)
{
    return;
}

static void s_APPLGC_RcvSrlEvent(   t_uint8 * f_rxData_pu8, 
                                    t_uint16 f_dataSize_u16, 
                                    t_eFMKSRL_RxCallbackInfo f_InfoCb_e)
{
    t_eReturnCode Ret_e = RC_OK;
    char msgbuffer[20];
    sprintf(msgbuffer, "Got It\r\n");


    if(f_InfoCb_e == FMKSRL_CB_INFO_RECEIVE_ENDING)
    {
    }
    return;
}

static void s_APPLGC_TranmistEvnt(t_bool f_isMsgTransmit_b, t_eFMKSRL_TxCallbackInfo f_InfoCb_e)
{
    return;
}

/*********************************
 * s_MotorCallback
 *********************************/
static void s_PulseCallback(t_eFMKIO_OutPwmSig f_signal_e)
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

