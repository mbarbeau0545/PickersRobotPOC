/*********************************************************************
 * @file        Gantry.c
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
#include "Library/SafeMem/SafeMem.h"

#include "./Gantry.h"
#include "APP_CFG/ConfigFiles/Gantry_ConfigPrivate.h"
#include "APP_LGC/Src/APP_LGC.h"
#include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define GTRY_PULSES_NB ((t_sint32)6400)
#define GTRY_SPEED ((t_uint32)6000)
// ********************************************************************
// *                      Types
// ********************************************************************
typedef enum 
{
    GTRY_GO_FORWARD = 0x00,
    GTRY_GO_BACKWARD,
} t_eGTRY_TestState;
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//

/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
typedef struct 
{
    t_uint32 axeX_u32;
    t_uint32 axeY_u32;
    t_uint32 axeZ_u32;
} t_sGTRY_Axe;

/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//

// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
static t_eGTRY_FSMProduction g_FSM_ProdMode_e = GTRY_FSM_PROD_SEO;
static t_eGTRY_FSMProduction g_FSM_RsqtProdMode_e = GTRY_FSM_PROD_SEO;
static t_eGTRY_FSMGantry g_FSM_GtryMode_e = GTRY_SFM_GANTRY_PAUSE;
static t_eGTRY_FSMGantry g_FSM_RqstGtryMode_e = GTRY_SFM_GANTRY_PAUSE;

static t_float32 * g_snsValues_paf32;
static t_sAPPLGC_ServiceInfo * g_SrvInfo_pas;
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
static t_eReturnCode s_GTRY_StateMachineMngmt(void);
/**
*
*	@brief      Check Limit switch Status, and check movement of the Gantry.\n
*	@note   
*
*
*	@param[in] 
*	@param[out]
*	 
*
*
*/
static t_eReturnCode s_GTRY_SafetyMngmt(void);
/**
*
*	@brief      Check Limit switch Status, and check movement of the Gantry.\n
*	@note   
*
*
*	@param[in] 
*	@param[out]
*	 
*
*
*/
static void s_GTRY_SetGantryOff(t_eGTRY_FSMGantry f_GtryState_e);
/**
*
*	@brief      Update Service Status and Actuators Values.\n
*
*
*/
static t_eReturnCode s_GTRY_UpdateSrvState(void);
/**
*
*	@brief      Reset Each Actuators Value that need to be reset 
*               for safety purpose.\n
*
*
*/
static void s_GTRY_ResetActuatorState(void);

static t_eReturnCode s_GTRY_TestMovement(void);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * Gantry_Init
 *********************************/
t_eReturnCode Gantry_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    return Ret_e;
}

/*********************************
 * APPLGC_Init
 *********************************/
t_eReturnCode Gantry_Cyclic(t_float32 *f_snsValues_paf32, 
                            t_sAPPLGC_ServiceInfo *f_SrvInfo_pas)
{
    t_eReturnCode Ret_e = RC_OK;

    //----- Initialize Pointor to data -----//
    g_snsValues_paf32 = (t_float32 *)f_snsValues_paf32;
    g_SrvInfo_pas = (t_sAPPLGC_ServiceInfo *)f_SrvInfo_pas;

    //----- Check Gantry Mvmt Security and Update State-----//
    Ret_e = s_GTRY_SafetyMngmt();
    /*if(Ret_e == RC_OK)
    {
        //----- Get New Mode from Application -----//
        Ret_e = s_GTRY_StateMachineMngmt();    
    }*/

    if(Ret_e >= RC_OK)
    {
        Ret_e = s_GTRY_UpdateSrvState();
    }
    if(Ret_e >= RC_OK)
    {
        s_GTRY_ResetActuatorState();
    }
    if(Ret_e >= RC_OK)
    {
        s_GTRY_TestMovement();
    }
    /*if(Ret_e == RC_OK)
    {
        switch (g_FSM_GtryMode_e)
        {
            case GTRY_SFM_GANTRY_PRODUCTION:
            {
                if(Ret_e == RC_OK)
                {
                    //----- Update Service & Reset Actuators Value -----//
                    s_GTRY_ResetActuatorState();
                }
                if(Ret_e == RC_OK)
                {
                    if(g_FSM_RsqtProdMode_e != g_FSM_ProdMode_e)
                    {
                        Ret_e = c_Gtry_SFMProdFunc_as[g_FSM_ProdMode_e].Exit_pcb();

                        if(Ret_e == RC_OK)
                        {
                            Ret_e = c_Gtry_SFMProdFunc_as[g_FSM_RsqtProdMode_e].Enter_pcb();

                            if(Ret_e == RC_OK)
                            {
                                g_FSM_ProdMode_e = g_FSM_RsqtProdMode_e;
                            }
                        }
                    }
                }
                
                if(Ret_e == RC_OK)
                {
                    Ret_e = c_Gtry_SFMProdFunc_as[g_FSM_ProdMode_e].Cyclic_pcb( g_snsValues_paf32,
                                                                                g_SrvInfo_pas);
                }
                
                if(Ret_e < RC_OK)
                {
                    g_FSM_GtryMode_e = GTRY_SFM_GANTRY_DEFAULT;
                }
                break;
            }
            case GTRY_SFM_GANTRY_PAUSE:
            {
                //----- The transition of the state to anothter one 
                //      is made in StateMachineMngmt or with public information ----//
                s_GTRY_SetGantryOff(g_FSM_GtryMode_e);
                break;
            }
            case GTRY_SFM_GANTRY_DEFAULT:
            {
                s_GTRY_SetGantryOff(g_FSM_GtryMode_e);
                break;
            }
            case GTRY_SFM_GANTRY_NB:
            default:
            {
                break;
            }
        }
    }*/
    return Ret_e;
}

/*********************************
 * Gantry_RqstSFMState
 *********************************/
t_eReturnCode Gantry_RqstSFMState(t_eGTRY_FSMGantry f_rqstGtryMode_e)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_rqstGtryMode_e >= GTRY_SFM_GANTRY_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        g_FSM_RqstGtryMode_e = f_rqstGtryMode_e;
    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_GTRY_StateMachineMngmt
 *********************************/
static t_eReturnCode s_GTRY_StateMachineMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uAPPLGC_CmdValues appCmd_u;

    Ret_e = APPLGC_GetAppCmd(APPLGC_RCV_CMD_ID_DATA_MODE, &appCmd_u);

    //----- if Ret_e = WARNING_NO_OPE it means not new mode 
    //      has been set by application else new mode -----//
    if(Ret_e == RC_OK)
    {
        g_FSM_RqstGtryMode_e = appCmd_u.SFMModeInfo_s.mainMode_u8;
        g_FSM_RsqtProdMode_e = appCmd_u.SFMModeInfo_s.prodMode_u8;
    }

    //----- Gantry Mode Change from App or From RqstSFMState public API -----//
    if(g_FSM_RqstGtryMode_e != g_FSM_GtryMode_e)
    {
        //----- If we change Gantry Mode ensure to quit properly the Production mode -----//
        if(g_FSM_GtryMode_e == GTRY_SFM_GANTRY_PRODUCTION)
        {
            Ret_e = c_Gtry_SFMProdFunc_as[g_FSM_ProdMode_e].Exit_pcb();
        }

        //----- Change Mode only if exit ok -----//
        if(Ret_e == RC_OK)
        {
            g_FSM_GtryMode_e = g_FSM_RqstGtryMode_e;
        }
    }
    
    if(Ret_e == RC_WARNING_NO_OPERATION)
    {
        Ret_e = RC_OK;
    }
    
    return Ret_e;
}

/*********************************
 * s_GTRY_SafetyMngmt
 *********************************/
static t_eReturnCode s_GTRY_SafetyMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxLimSw_u8;
    t_uint8 idxSnsLimSw_u8 = 0;
    t_bool reportDiag_b = False;

    //----- check limit switch -----//
    //----- In GMCR (Referencment) let this mode deal with
    //      limit switch -----//
    if(g_FSM_ProdMode_e != GTRY_FSM_PROD_SEO)
    {
        for(idxLimSw_u8 = (t_uint8)0 ; idxLimSw_u8 < GTRY_SNS_LIMSWITCH_NB ; idxLimSw_u8++)
        {
            idxSnsLimSw_u8 = (t_uint8)c_Gtry_LimSwitchIdx_ae[idxLimSw_u8];
            if(g_snsValues_paf32[idxSnsLimSw_u8] == APPSNS_LIM_SWCH_NC_CONTACT)
            {
                //---- Problem, call APPSDM -----//
                Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_GANTRY_SWITCH_LIMIT,
                                                APPSDM_DIAG_ITEM_REPORT_FAIL,
                                                (t_uint16)idxSnsLimSw_u8,
                                                (t_uint16)0);

                g_FSM_GtryMode_e = GTRY_SFM_GANTRY_DEFAULT;
                reportDiag_b = (t_bool)True;
                break;
            }
        }   
    }
    if(reportDiag_b == False)
    {
        Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_GANTRY_SWITCH_LIMIT,
                                        APPSDM_DIAG_ITEM_REPORT_PASS,
                                        (t_uint16)idxSnsLimSw_u8,
                                        (t_uint16)0);
    }

    return Ret_e;
}

/*********************************
 * s_GTR_SetGantryOff
 *********************************/
static void s_GTRY_SetGantryOff(t_eGTRY_FSMGantry f_GtryState_e)
{
    t_uAPPACT_SetValue * actgtrXL_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_X].actVal_pau[APPLGC_ACT_MTR_X_L]);
    t_uAPPACT_SetValue * actgtrXR_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_X].actVal_pau[APPLGC_ACT_MTR_X_R]);
    t_uAPPACT_SetValue * actgtrY_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].actVal_pau[APPLGC_ACT_MTR_Y]);
    t_uAPPACT_SetValue * actgtrZ_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].actVal_pau[APPLGC_ACT_MTR_Z]);

    switch (f_GtryState_e)
    {
        case GTRY_SFM_GANTRY_PAUSE:
        {
            actgtrXL_u->Motor_s.nbPulses_s32 = (t_uint32)0;
            actgtrXL_u->Motor_s.stopPulse_b = (t_bool)True;

            actgtrXR_u->Motor_s.nbPulses_s32 = (t_uint32)0;
            actgtrXR_u->Motor_s.stopPulse_b = (t_bool)True;

            actgtrY_u->Motor_s.nbPulses_s32 = (t_uint32)0;
            actgtrY_u->Motor_s.stopPulse_b = (t_bool)True;

            actgtrZ_u->Motor_s.nbPulses_s32 = (t_uint32)0;
            actgtrZ_u->Motor_s.stopPulse_b = (t_bool)True;
            break;
        }
        case GTRY_SFM_GANTRY_DEFAULT:
        {
            actgtrXL_u->Motor_s.nbPulses_s32 = (t_uint32)0;
            actgtrXL_u->Motor_s.stopPulse_b = (t_bool)True;
            actgtrXL_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;

            actgtrXR_u->Motor_s.nbPulses_s32 = (t_uint32)0;
            actgtrXR_u->Motor_s.stopPulse_b = (t_bool)True;
            actgtrXR_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;

            actgtrY_u->Motor_s.nbPulses_s32 = (t_uint32)0;
            actgtrY_u->Motor_s.stopPulse_b = (t_bool)True;
            actgtrY_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;

            actgtrZ_u->Motor_s.nbPulses_s32 = (t_uint32)0;
            actgtrZ_u->Motor_s.stopPulse_b = (t_bool)True;
            actgtrZ_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
            break;
        }
        case GTRY_SFM_GANTRY_PRODUCTION:
        case GTRY_SFM_GANTRY_NB:
        {
            break;
        }
    }

    return;
}

/*********************************
 * Gantry_GetFFMState
 *********************************/
t_eReturnCode Gantry_GetFSMState(t_eGTRY_FSMGantry *f_rqstGtryMode_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_rqstGtryMode_pe == (t_eGTRY_FSMGantry *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_rqstGtryMode_pe = g_FSM_GtryMode_e;
    }

    return Ret_e;
}

/*********************************
 * s_GTRY_UpdateSrvState
 *********************************/
static t_eReturnCode s_GTRY_UpdateSrvState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uAPPACT_GetValue actMotorXLVal_u;
    t_uAPPACT_GetValue actMotorXRVal_u;
    t_uAPPACT_GetValue actMotorYVal_u;
    t_uAPPACT_GetValue actMotorZVal_u;
    t_sGTRY_Axe gtryAxeSpeed_s;
    t_uint8 appCmd_ua8[APPLGC_APP_PROTOCOL_LEN_DATA];


    //----- update Gantry Service X -----//
    Ret_e = APPACT_Get_ActValue(APPACT_ACTUATOR_MTR_X_L, &actMotorXLVal_u);
    if(Ret_e == RC_OK)
    {   
        Ret_e = APPACT_Get_ActValue(APPACT_ACTUATOR_MTR_X_R, &actMotorXRVal_u);
    }
    if(Ret_e == RC_OK)
    {   
        Ret_e = APPACT_Get_ActValue(APPACT_ACTUATOR_MTR_Y, &actMotorYVal_u);
    }
    if(Ret_e == RC_OK)
    {   
        Ret_e = APPACT_Get_ActValue(APPACT_ACTUATOR_MTR_Z, &actMotorZVal_u);
    }
    if(Ret_e == RC_OK)
    {
        //----- update actuators state, what need to be reset in each cyclic -----//

        //----- update service State -----//
        if((actMotorXLVal_u.Motor_s.pulseState_e == CL42T_MOTOR_PULSE_ON)
        || (actMotorXRVal_u.Motor_s.pulseState_e == CL42T_MOTOR_PULSE_ON))
        {
            gtryAxeSpeed_s.axeX_u32 = ((actMotorXLVal_u.Motor_s.frequency_u32 + 
                                            actMotorXRVal_u.Motor_s.frequency_u32) / (t_uint32)2);
            g_SrvInfo_pas[APPLGC_SRV_GTRY_X].state_e = APPLGC_SRV_STATE_MOVING;
        }
        else 
        {
            gtryAxeSpeed_s.axeX_u32 = (t_uint32)0;
            g_SrvInfo_pas[APPLGC_SRV_GTRY_X].state_e = APPLGC_SRV_STATE_STOPPED;
        }

        if(actMotorYVal_u.Motor_s.pulseState_e == CL42T_MOTOR_PULSE_ON)
        {
            gtryAxeSpeed_s.axeY_u32 = actMotorYVal_u.Motor_s.frequency_u32;
            g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].state_e = APPLGC_SRV_STATE_MOVING;
        }
        else 
        {
            gtryAxeSpeed_s.axeY_u32 = (t_uint32)0;
            g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].state_e = APPLGC_SRV_STATE_STOPPED;
        }

        if(actMotorZVal_u.Motor_s.pulseState_e == CL42T_MOTOR_PULSE_ON)
        {
            gtryAxeSpeed_s.axeZ_u32 = actMotorZVal_u.Motor_s.frequency_u32;
            g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].state_e = APPLGC_SRV_STATE_MOVING;
        }
        else 
        {
            gtryAxeSpeed_s.axeZ_u32 = (t_uint32)0;
            g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].state_e = APPLGC_SRV_STATE_STOPPED;
        }
    }
    /*if(Ret_e == RC_OK)
    {
        //----- send msg for application ------//
        Ret_e = SafeMem_memclear((void *)appCmd_ua8, APPLGC_APP_PROTOCOL_LEN_DATA);
        if(Ret_e == RC_OK)
        {
            appCmd_ua8[APPLGC_CMD_BYTE_0] = APPLGC_SEND_CMD_ID_GTRY_STATE_XYZ;
            appCmd_ua8[APPLGC_CMD_BYTE_1] = (t_uint8)g_SrvInfo_pas[APPLGC_SRV_GTRY_X].state_e;
            appCmd_ua8[APPLGC_CMD_BYTE_2] = (t_uint8)g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].state_e;
            appCmd_ua8[APPLGC_CMD_BYTE_3] = (t_uint8)g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].state_e;

            Ret_e = APPLGC_APP_COM_SEND(appCmd_ua8);
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = SafeMem_memclear((void *)appCmd_ua8, APPLGC_APP_PROTOCOL_LEN_DATA);

            if(Ret_e == RC_OK)
            {
                appCmd_ua8[APPLGC_CMD_BYTE_0] = APPLGC_SEND_CMD_ID_GTRY_SPEED_XYZ;
                appCmd_ua8[APPLGC_CMD_BYTE_1] = (t_uint8)Ms8ExtractByte1fromU16((t_uint16)gtryAxeSpeed_s.axeX_u32);
                appCmd_ua8[APPLGC_CMD_BYTE_2] = (t_uint8)Ms8ExtractByte0fromU16((t_uint16)gtryAxeSpeed_s.axeX_u32);
                appCmd_ua8[APPLGC_CMD_BYTE_3] = (t_uint8)Ms8ExtractByte1fromU16((t_uint16)gtryAxeSpeed_s.axeY_u32);
                appCmd_ua8[APPLGC_CMD_BYTE_4] = (t_uint8)Ms8ExtractByte0fromU16((t_uint16)gtryAxeSpeed_s.axeY_u32);
                appCmd_ua8[APPLGC_CMD_BYTE_5] = (t_uint8)Ms8ExtractByte1fromU16((t_uint16)gtryAxeSpeed_s.axeZ_u32);
                appCmd_ua8[APPLGC_CMD_BYTE_6] = (t_uint8)Ms8ExtractByte0fromU16((t_uint16)gtryAxeSpeed_s.axeZ_u32);

                Ret_e = APPLGC_APP_COM_SEND(appCmd_ua8);
            }
        }
    }*/

    return Ret_e;
}

/*********************************
 * s_GTRY_ResetActuatorState
 *********************************/
static void s_GTRY_ResetActuatorState(void)
{
    t_uAPPACT_SetValue * actgtrXL_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_X].actVal_pau[APPLGC_ACT_MTR_X_L]);
    t_uAPPACT_SetValue * actgtrXR_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_X].actVal_pau[APPLGC_ACT_MTR_X_R]);
    t_uAPPACT_SetValue * actgtrY_u  = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].actVal_pau[APPLGC_ACT_MTR_Y]);
    t_uAPPACT_SetValue * actgtrZ_u  = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].actVal_pau[APPLGC_ACT_MTR_Z]);

    //---- reset pulses and stopPulse variable -----//
    actgtrXL_u->Motor_s.nbPulses_s32 = (t_sint32)0;
    actgtrXR_u->Motor_s.nbPulses_s32 = (t_sint32)0;
    actgtrY_u->Motor_s.nbPulses_s32  = (t_sint32)0;
    actgtrZ_u->Motor_s.nbPulses_s32  = (t_sint32)0;

    actgtrXL_u->Motor_s.stopPulse_b = (t_bool)False;
    actgtrXR_u->Motor_s.stopPulse_b = (t_bool)False;
    actgtrY_u->Motor_s.stopPulse_b  = (t_bool)False;
    actgtrZ_u->Motor_s.stopPulse_b  = (t_bool)False;

    //----- by default we set motor state to ON 
    //      if someone has to set Motor Off it will 
    //      if not, it means the motor has to be ON ----//
    actgtrXL_u->Motor_s.state_e = (t_bool)CL42T_MOTOR_STATE_ON;
    actgtrXR_u->Motor_s.state_e = (t_bool)CL42T_MOTOR_STATE_ON;
    actgtrY_u->Motor_s.state_e  = (t_bool)CL42T_MOTOR_STATE_ON;
    actgtrZ_u->Motor_s.state_e  = (t_bool)CL42T_MOTOR_STATE_ON;
}

/*********************************
 * Gantry_InformAppMissionState
 *********************************/
t_eReturnCode Gantry_InformAppMissionState(t_eGTRY_MissionStatus f_missionStatue_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 appCmd_ua8[APPLGC_APP_PROTOCOL_LEN_DATA];

    Ret_e = SafeMem_memclear((void *)appCmd_ua8, APPLGC_APP_PROTOCOL_LEN_DATA);

    if(Ret_e == RC_OK)
    {
        appCmd_ua8[APPLGC_CMD_BYTE_0] = (t_uint8)APPLGC_SEND_CMD_ID_GTRY_INFO;
        appCmd_ua8[APPLGC_CMD_BYTE_1] = (t_uint8)f_missionStatue_e;

        Ret_e = APPLGC_APP_COM_SEND(appCmd_ua8);
    }

    return Ret_e;
}

static t_eReturnCode s_GTRY_TestMovement(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_eGTRY_TestState s_State = GTRY_GO_FORWARD; 
    t_uAPPACT_SetValue * actgtrXL_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_X].actVal_pau[APPLGC_ACT_MTR_X_L]);
    t_uAPPACT_SetValue * actgtrXR_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_X].actVal_pau[APPLGC_ACT_MTR_X_R]);
    t_uAPPACT_SetValue * actgtrY_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].actVal_pau[APPLGC_ACT_MTR_Y]);
    t_uAPPACT_SetValue * actgtrZ_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].actVal_pau[APPLGC_ACT_MTR_Z]);
    static t_bool s_setActuation_b = False;
    static t_uint32 s_actTime_u32 = 0; 
    t_uint32 currentTime_u32;
    FMKCPU_Get_Tick(&currentTime_u32);

    //---- check state -----//
    if((g_SrvInfo_pas[APPLGC_SRV_GTRY_X].state_e == APPLGC_SRV_STATE_STOPPED)
    && (g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].state_e == APPLGC_SRV_STATE_STOPPED)
    && (g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].state_e == APPLGC_SRV_STATE_STOPPED)
    && ((currentTime_u32 - s_actTime_u32) > 1000))
    {
        FMKCPU_Get_Tick(&s_actTime_u32);
        s_setActuation_b = True;
    }
    if(s_setActuation_b == (t_bool)True)
    {
        s_setActuation_b = False;
        switch(s_State)
        {
            case GTRY_GO_FORWARD:
            {
                if(g_SrvInfo_pas[APPLGC_SRV_GTRY_X].health_e == APPLGC_SRV_HEALTH_OK)
                {
                    actgtrXL_u->Motor_s.frequency_u32 = (t_uint32)GTRY_SPEED;
                    actgtrXL_u->Motor_s.nbPulses_s32  = (t_sint32)(GTRY_MTR_X_L_DIR * GTRY_PULSES_NB);

                    actgtrXR_u->Motor_s.frequency_u32 = (t_uint32)GTRY_SPEED;
                    actgtrXR_u->Motor_s.nbPulses_s32  = (t_sint32)(GTRY_MTR_X_R_DIR * GTRY_PULSES_NB);
                }
                else 
                {
                    actgtrXL_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                    actgtrXL_u->Motor_s.stopPulse_b = (t_bool)True;
                    actgtrXL_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
                    
                    actgtrXR_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                    actgtrXR_u->Motor_s.stopPulse_b = (t_bool)True;
                    actgtrXR_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
                }
            
                if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].health_e == APPLGC_SRV_HEALTH_OK)
                {
                    actgtrY_u->Motor_s.frequency_u32 = (t_uint32)GTRY_SPEED;
                    actgtrY_u->Motor_s.nbPulses_s32  = (t_sint32)GTRY_PULSES_NB;    
                }
                else 
                {
                    actgtrY_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                    actgtrY_u->Motor_s.stopPulse_b = (t_bool)True;
                    actgtrY_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
                }
            

                if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].health_e == APPLGC_SRV_HEALTH_OK)
                {
                    actgtrZ_u->Motor_s.frequency_u32 = (t_uint32)GTRY_SPEED;
                    actgtrZ_u->Motor_s.nbPulses_s32  = (t_sint32)GTRY_PULSES_NB;
                }
                else 
                {
                    actgtrZ_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                    actgtrZ_u->Motor_s.stopPulse_b = (t_bool)True;
                    actgtrZ_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
                }  
                s_State = GTRY_GO_BACKWARD;
                break;
            }
            case GTRY_GO_BACKWARD:
            {
                if(g_SrvInfo_pas[APPLGC_SRV_GTRY_X].health_e == APPLGC_SRV_HEALTH_OK)
                {
                    actgtrXL_u->Motor_s.frequency_u32 = (t_uint32)GTRY_SPEED;
                    actgtrXL_u->Motor_s.nbPulses_s32  = (t_sint32)(-(GTRY_MTR_X_L_DIR * GTRY_PULSES_NB));

                    actgtrXR_u->Motor_s.frequency_u32 = (t_uint32)GTRY_SPEED;
                    actgtrXR_u->Motor_s.nbPulses_s32  = (t_sint32)(-(GTRY_MTR_X_R_DIR * GTRY_PULSES_NB));
                }
                else 
                {
                    actgtrXL_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                    actgtrXL_u->Motor_s.stopPulse_b = (t_bool)True;
                    actgtrXL_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
                    
                    actgtrXR_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                    actgtrXR_u->Motor_s.stopPulse_b = (t_bool)True;
                    actgtrXR_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
                }
            
                if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].health_e == APPLGC_SRV_HEALTH_OK)
                {
                    actgtrY_u->Motor_s.frequency_u32 = (t_uint32)GTRY_SPEED;
                    actgtrY_u->Motor_s.nbPulses_s32  = (t_sint32)(-GTRY_PULSES_NB);  
                }
                else 
                {
                    actgtrY_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                    actgtrY_u->Motor_s.stopPulse_b = (t_bool)True;
                    actgtrY_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
                }
            

                if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].health_e == APPLGC_SRV_HEALTH_OK)
                {
                    actgtrZ_u->Motor_s.frequency_u32 = (t_uint32)GTRY_SPEED;
                    actgtrZ_u->Motor_s.nbPulses_s32  = (t_sint32)(-GTRY_PULSES_NB);
                }
                else 
                {
                    actgtrZ_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                    actgtrZ_u->Motor_s.stopPulse_b = (t_bool)True;
                    actgtrZ_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
                } 
                s_State = GTRY_GO_FORWARD;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    
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

