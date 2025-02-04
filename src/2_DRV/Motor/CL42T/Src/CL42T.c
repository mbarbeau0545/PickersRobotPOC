/**
 * @file        CL42T.c
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      sde
 * @date        23/01/2025
 * @version     1.0
 */
// ********************************************************************
// *                      Includes
// ********************************************************************
#include "TypeCommon.h"
#include "APP_CFG/ConfigFiles/CL42T_ConfigPrivate.h"
#include "./CL42T.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
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
    CL42T_PULSE_BIT_STATE_ON,
    CL42T_PULSE_BIT_DEAD_TIME,
    CL42T_PULSE_BIT_RQST_CMD,
    CL42T_PULSE_BIT_NB

};
/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
typedef struct 
{
    t_uint8 signal_u8;
    t_uint32 value_u32;
    t_bool isConfigured_b;
} t_sCL42T_MotorSignalInfo;

typedef struct 
{
    t_sCL42T_MotorSignalInfo SigInfo_as[CL42T_SIGTYPE_NB];
    t_cbCL42T_Diagnostic *diagCallback_pcb;
    t_eFMKTIM_InterruptLineIO pulseITLine_e;
    t_eCL42T_DiagError Health_e;
    t_uint32 InhibTime_u32;
    t_uint32 PulseRunMaxCnt_u32;
    t_bool isConfigured_b;
    t_uint8 pulseMask_u8;
    t_bool flagErrorDetected_b;

} t_sCL42T_MotorInfo;

/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */

//-----------------------------TYPEDEF TYPES---------------------------//

// ********************************************************************
// *                      Variables
// ********************************************************************
static t_sCL42T_MotorInfo g_MotorInfo_as[CL42T_MOTOR_NB];

static t_bool g_IsRsqstInit_ab[CL42T_MOTOR_NB];

static t_eCyclicModState g_CL42T_ModState_e = STATE_CYCLIC_CFG;


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
static t_eReturnCode s_CL42T_ConfigurationState(void);

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
static t_eReturnCode s_CL42T_OperationalState(void);

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
static void s_CL42T_SigErrorMngmt(t_eFMKIO_SigType f_type_e, 
                                t_uint8 f_signalId_u8, 
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
static t_eReturnCode s_CL42T_PerformDiagnostic( t_eCL42T_MotorId f_idMotor_e, 
                                                t_uint16 f_cntDiag_u16);
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
static t_eReturnCode s_CL42T_GetDiagErrorFromCnt(t_uint16 f_counter_u8, t_eCL42T_DiagError * f_diagErr_pe);

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
static t_eReturnCode s_CL42T_SetSignalsValue(t_sCL42T_MotorInfo * f_motorInfo_ps);

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
static t_eReturnCode s_CL42T_PulseOpeMngmt( t_sCL42T_MotorInfo * f_motorInfo_ps, 
                                            t_bool * f_setAcutation_pb);

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
static void s_CL42T_PulseEventMngmt(t_eFMKIO_OutPwmSig f_signal_e);

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
static void s_CL42T_SigErrorMngmt(  t_eFMKIO_SigType f_typeSig_e, 
                                    t_uint8 f_sigID_u8, 
                                    t_uint16 f_debugInfo1, 
                                    t_uint16 f_debugInfo2);
/**
 *
 *	@brief
 *	@note   faire un switchcase avec wise (low) et clockwise (high)
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */

static t_eReturnCode s_CL42T_AddPulseSignal(t_sCL42T_MotorInfo * f_motorInfo_ps,
                                            t_sCL42T_PwmSignalCfg * f_pulseCfg_ps);
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
static t_eReturnCode s_CL42T_AddDirSignal(  t_sCL42T_MotorInfo * f_motorInfo_ps,
                                            t_sCL42T_DigitalSignalCfg * f_DirSigCfg_s_ps);

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
static t_eReturnCode s_CL42T_AddStateSignal(t_sCL42T_MotorInfo * f_motorInfo_ps,
                                            t_sCL42T_DigitalSignalCfg * f_StateSigCfg_ps);

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
static t_eReturnCode s_CL42T_AddDiagSignal( t_sCL42T_MotorInfo * f_motorInfo_ps,
                                            t_sCL42T_FreqSignalCfg * f_DiagSigCfg_ps);
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
static t_eReturnCode s_CL42T_SetPulseSignal( t_sCL42T_MotorInfo * f_motorInfo_ps,
                                    t_uint16 f_nbPulses_u16);

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
static t_eReturnCode s_CL42T_SetDirSignal(   t_sCL42T_MotorInfo * f_motorInfo_ps,
                                    t_eCL42T_MotorDirection f_direction_e);    

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
static t_eReturnCode s_CL42T_SetStateSignal( t_sCL42T_MotorInfo * f_motorInfo_ps,
                                    t_eCL42T_MotorState f_state_e);

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
static t_eReturnCode s_CL42T_SetSpeedSignal( t_sCL42T_MotorInfo * f_motorInfo_ps,
                                    t_uint32 f_speed_u32);


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
*
*/
static t_eReturnCode s_CL42T_GetPulseSignal(    t_sCL42T_MotorInfo * f_motorInfo_ps,
                                                t_uint16 * f_nbPulses_pu16);

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
*
*/
static t_eReturnCode s_CL42T_GetDirSignal(  t_sCL42T_MotorInfo * f_motorInfo_ps,
                                            t_eCL42T_MotorDirection *f_direction_pe);

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
static t_eReturnCode s_CL42T_GetStateSignal(    t_sCL42T_MotorInfo * f_motorInfo_ps,
                                                t_eCL42T_MotorState *f_state_pe);   

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
static t_eReturnCode s_CL42T_GetDiagError(      t_sCL42T_MotorInfo * f_motorInfo_ps,
                                                t_eCL42T_DiagError * f_infoErr_pe);

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
static t_eReturnCode s_CL42T_GetSpeedSignal(    t_sCL42T_MotorInfo * f_motorInfo_ps,
                                                t_uint32 *f_speed_pu32);
//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * CL42T_Init
 *********************************/
t_eReturnCode CL42T_Init(void)
{
    t_uint8 idxMotor_u8;
    t_uint8 idxSignal_u8;

    for(idxMotor_u8 = (t_uint8)0 ; idxMotor_u8 < CL42T_MOTOR_NB ; idxMotor_u8++)
    {
        g_IsRsqstInit_ab[idxMotor_u8] = (t_bool)false;

        g_MotorInfo_as[idxMotor_u8].diagCallback_pcb = NULL_FONCTION;
        g_MotorInfo_as[idxMotor_u8].flagErrorDetected_b = (t_bool)False;
        g_MotorInfo_as[idxMotor_u8].Health_e = CL42T_DIAGNOSTIC_OK;
        g_MotorInfo_as[idxMotor_u8].InhibTime_u32 = (t_uint32)0;
        g_MotorInfo_as[idxMotor_u8].isConfigured_b = (t_bool)False;
        g_MotorInfo_as[idxMotor_u8].pulseITLine_e = FMKTIM_INTERRUPT_LINE_IO_NB;
        g_MotorInfo_as[idxMotor_u8].pulseMask_u8 = (t_uint8)0;
        g_MotorInfo_as[idxMotor_u8].PulseRunMaxCnt_u32 = (t_uint32)0;
        
        for(idxSignal_u8 = (t_uint8)0 ; idxSignal_u8 < CL42T_MOTOR_NB ; idxSignal_u8++)
        {
            g_MotorInfo_as[idxMotor_u8].SigInfo_as[idxSignal_u8].isConfigured_b = (t_bool)False;
            g_MotorInfo_as[idxMotor_u8].SigInfo_as[idxSignal_u8].signal_u8 = (t_uint8)0;
            g_MotorInfo_as[idxMotor_u8].SigInfo_as[idxSignal_u8].value_u32 = (t_uint32)0;
        }
    }
    return RC_OK;
}
/*********************************
 * CL42T_Cyclic
 *********************************/
t_eReturnCode CL42T_Cyclic(void)
{
        t_eReturnCode Ret_e = RC_OK;

    switch (g_CL42T_ModState_e)
    {
        case STATE_CYCLIC_CFG:
        {
            Ret_e = s_CL42T_ConfigurationState();
            if(Ret_e == RC_OK)
            {
                g_CL42T_ModState_e = STATE_CYCLIC_WAITING;
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
            g_CL42T_ModState_e = STATE_CYCLIC_OPE;
            break; 
        }
        case STATE_CYCLIC_OPE:
        {
            Ret_e = s_CL42T_OperationalState();
            if(Ret_e < RC_OK)
            {
                g_CL42T_ModState_e = STATE_CYCLIC_ERROR;
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
 * CL42T_GetState
 *********************************/
t_eReturnCode CL42T_GetState(   t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_CL42T_ModState_e;
    }

    return Ret_e;
}
/*********************************
 * CL42T_SetState
 *********************************/
t_eReturnCode CL42T_SetState(   t_eCyclicModState f_State_e)
{
    g_CL42T_ModState_e = f_State_e;   
    return RC_OK;
}

/*********************************
 * s_CL42T_AddPulseSignal
 *********************************/
t_eReturnCode CL42T_AddMotorConfiguration(  t_eCL42T_MotorId f_motorId_e,
                                            t_sCL42T_MotorSigCfg f_MotorCfg_s,
                                            t_cbCL42T_Diagnostic *f_diagEvnt_pcb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorInfo * motorInfo_ps;

    if(f_motorId_e >= CL42T_MOTOR_NB) 
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        g_IsRsqstInit_ab[f_motorId_e] = (t_bool)True;
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_motorId_e]);
        motorInfo_ps->diagCallback_pcb = f_diagEvnt_pcb;

        Ret_e = s_CL42T_AddPulseSignal(motorInfo_ps, &f_MotorCfg_s.PulseSigCfg_s);

        if(Ret_e == RC_OK)
        {
            Ret_e = s_CL42T_AddDirSignal(motorInfo_ps, &f_MotorCfg_s.DirSigCfg_s);
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_CL42T_AddStateSignal(motorInfo_ps, &f_MotorCfg_s.StateSigCfg);
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_CL42T_AddDiagSignal(motorInfo_ps, &f_MotorCfg_s.DiagSigCfg_s);
        }
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_SetPulseSignal
 *********************************/
t_eReturnCode CL42T_SetMotorSigValue(   t_eCL42T_MotorId f_motorId_e,
                                        t_eCL42T_MotorSignalType f_sigType_e,
                                        t_uCL42T_MotorValue f_MotorValue_u)
{
    t_eReturnCode Ret_e = RC_OK;

    t_sCL42T_MotorInfo * motorInfo_ps;

    if(f_motorId_e >= CL42T_MOTOR_NB
    || f_sigType_e >= CL42T_SIGTYPE_NB) 
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_MotorInfo_as[f_motorId_e].isConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(g_MotorInfo_as[f_motorId_e].Health_e != CL42T_DIAGNOSTIC_OK)
    {
        Ret_e = RC_WARNING_BUSY;
    }

    if(Ret_e == RC_OK)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_motorId_e]);

        switch (f_sigType_e)
        {
            case CL42T_SIGTYPE_PULSE:
            {
                Ret_e = s_CL42T_SetPulseSignal(motorInfo_ps, f_MotorValue_u.nbPulses_u16);
                break;
            }
            case CL42T_SIGTYPE_SPEED:
            {
                Ret_e = s_CL42T_SetSpeedSignal(motorInfo_ps, f_MotorValue_u.frequency_u32);
                break;
            }
            case CL42T_SIGTYPE_DIR:
            {
                Ret_e = s_CL42T_SetDirSignal(motorInfo_ps, f_MotorValue_u.dir_e);
                break;
            }
            case CL42T_SIGTYPE_STATE:
            {
                Ret_e = s_CL42T_SetStateSignal(motorInfo_ps, f_MotorValue_u.state_e);
                break;
            }
            case CL42T_SIGTYPE_DIAG:
            case CL42T_SIGTYPE_NB:
            default:
            {
                Ret_e = RC_WARNING_NO_OPERATION;
                break;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_SetPulseSignal
 *********************************/
t_eReturnCode CL42T_GetMotorSigValue(   t_eCL42T_MotorId f_motorId_e,
                                        t_eCL42T_MotorSignalType f_sigType_e,
                                        t_uCL42T_MotorValue * f_MotorValue_pu)
{
    t_eReturnCode Ret_e = RC_OK;

    t_sCL42T_MotorInfo * motorInfo_ps;

    if(f_motorId_e >= CL42T_MOTOR_NB
    || f_sigType_e >= CL42T_SIGTYPE_NB) 
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_MotorValue_pu == (t_uCL42T_MotorValue *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_MotorInfo_as[f_motorId_e].isConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(g_MotorInfo_as[f_motorId_e].Health_e != CL42T_DIAGNOSTIC_OK)
    {
        Ret_e = RC_WARNING_BUSY;
    }

    if(Ret_e == RC_OK)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_motorId_e]);

        switch (f_sigType_e)
        {
            case CL42T_SIGTYPE_PULSE:
            {
                Ret_e = s_CL42T_GetPulseSignal(motorInfo_ps, &f_MotorValue_pu->nbPulses_u16);
                break;
            }
            case CL42T_SIGTYPE_SPEED:
            {
                Ret_e = s_CL42T_GetSpeedSignal(motorInfo_ps, &f_MotorValue_pu->frequency_u32);
                break;
            }
            case CL42T_SIGTYPE_DIR:
            {
                Ret_e = s_CL42T_GetDirSignal(motorInfo_ps, &f_MotorValue_pu->dir_e);
                break;
            }
            case CL42T_SIGTYPE_STATE:
            {
                Ret_e = s_CL42T_GetStateSignal(motorInfo_ps, &f_MotorValue_pu->state_e);
                break;
            }
            case CL42T_SIGTYPE_DIAG:
            {
                Ret_e = s_CL42T_GetDiagError(motorInfo_ps, &f_MotorValue_pu->diagError_e);
            }
            case CL42T_SIGTYPE_NB:
            default:
            {
                Ret_e = RC_WARNING_NO_OPERATION;
                break;
            }
        }
    }

    return Ret_e;
}

//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_CL42T_ConfigurationState
 *********************************/
static t_eReturnCode s_CL42T_ConfigurationState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorInfo * motorInfo_ps;
    t_uint8 idxMotor_u8 = (t_uint8)0;
    t_uint8 idxSignal_u8 = (t_uint8)0;

    for(idxMotor_u8 = (t_uint8)0 ; (idxMotor_u8 < CL42T_MOTOR_NB) && (Ret_e == RC_OK) ; idxMotor_u8++)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[idxMotor_u8]);

        //---- Check if a Request for Init has been made for a motor ----//
        if(g_IsRsqstInit_ab[idxMotor_u8] == (t_bool)True)
        {
            for(idxSignal_u8 = (t_uint8)0; 
                (idxSignal_u8 < CL42T_SIGTYPE_NB)
                && (Ret_e == RC_OK) ; 
                idxSignal_u8++)
            {
                //---- Verify Configuration Has been Made Correctly ----//
                if(motorInfo_ps->SigInfo_as[idxSignal_u8].isConfigured_b == (t_bool)False)
                {
                    Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
                }
                //---- Initialize Container ----//
                else 
                {
                    motorInfo_ps->SigInfo_as[idxSignal_u8].value_u32 = (t_uint32)0;
                }   
            }
        }
    }

    return Ret_e;
}

/*********************************
 * CL42T_OperationnalState
 *********************************/
static t_eReturnCode s_CL42T_OperationalState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 counter_u32 = 0;
    t_sCL42T_MotorInfo * motorInfo_ps;
    t_uint8 idxMotor_u8 = (t_uint8)0;

    for(idxMotor_u8 = (t_uint8)0 ; (idxMotor_u8 < CL42T_MOTOR_NB) && (Ret_e == RC_OK) ; idxMotor_u8++)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[idxMotor_u8]);

        //---- Check Diagnostic Value ----//
        Ret_e = FMKIO_Get_InFreqSigValue((t_eFMKIO_InFreqSig)motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_DIAG].signal_u8,
                                        &counter_u32);

        //---- If return code not ok, perform diagnostic anyway ----//
        if(Ret_e != RC_OK)
        {
            counter_u32 = (t_uint32)0;
        }
        if((motorInfo_ps->flagErrorDetected_b == (t_bool)True)
        || (counter_u32 > (t_uint32)0))
        {
            Ret_e = s_CL42T_PerformDiagnostic((t_eCL42T_MotorId)idxMotor_u8, counter_u32);
        }
        //---- Set Signal even if RetCode is a WARNING ----//
        if(Ret_e > RC_OK)
        {
            Ret_e = s_CL42T_SetSignalsValue(motorInfo_ps);
        }
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_SetSignalsValue
 *********************************/
static t_eReturnCode s_CL42T_SetSignalsValue(t_sCL42T_MotorInfo * f_motorInfo_ps)
{
    t_eReturnCode Ret_e = RC_OK; 
    t_bool setActuation_b = (t_bool)False;
    t_sCL42T_MotorSignalInfo * sigInfo_ps;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        sigInfo_ps = (t_sCL42T_MotorSignalInfo *)(&f_motorInfo_ps->SigInfo_as);
        //---- Always set Driver State----//
        Ret_e = FMKIO_Set_OutDigSigValue(   sigInfo_ps[CL42T_SIGTYPE_STATE].signal_u8,
                                            (t_eFMKIO_DigValue)sigInfo_ps[CL42T_SIGTYPE_STATE].value_u32);

        //---- Pulse Mngmt ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_CL42T_PulseOpeMngmt(  f_motorInfo_ps,
                                            &setActuation_b);
        }
        if((Ret_e == RC_OK)
        && (setActuation_b == (t_bool)True))
        {
            Ret_e = FMKIO_Set_OutPwmSigFrequency(   sigInfo_ps[CL42T_SIGTYPE_SPEED].signal_u8,
                                                    (t_uint32)sigInfo_ps[CL42T_SIGTYPE_SPEED].value_u32);

            if(Ret_e == RC_OK)
            {
                Ret_e = FMKIO_Set_OutDigSigValue(   sigInfo_ps[CL42T_SIGTYPE_DIR].signal_u8,
                                                    (t_eFMKIO_DigValue)sigInfo_ps[CL42T_SIGTYPE_DIR].value_u32);
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = FMKIO_Set_OutPwmSigPulses(  sigInfo_ps[CL42T_SIGTYPE_PULSE].signal_u8,
                                                    CL42T_NOMINATIVE_DUTYCYCLE,
                                                    sigInfo_ps[CL42T_SIGTYPE_PULSE].value_u32);
            }
            if(Ret_e == RC_OK)
            {
                //---- Reset Value for Security Purpose ----//
                sigInfo_ps[CL42T_SIGTYPE_PULSE].value_u32 = (t_uint32)0;
                RESETBIT_8B(f_motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_RQST_CMD);
                SETBIT_8B(f_motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_STATE_ON);
            }
        }
    }

    return Ret_e;

}
/*********************************
 * s_CL42T_PerformDiagnostic
 *********************************/
static t_eReturnCode s_CL42T_PerformDiagnostic( t_eCL42T_MotorId f_idMotor_e, 
                                                t_uint16 f_cntDiag_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorInfo * motorInfo_ps;

    if(f_idMotor_e >= CL42T_MOTOR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_idMotor_e]);

        if(f_cntDiag_u16 > (t_uint16)0)
        {
            Ret_e = s_CL42T_GetDiagErrorFromCnt(f_cntDiag_u16, &motorInfo_ps->Health_e);

            //---- Call User with error ----//
            if(Ret_e == RC_OK)
            {
                motorInfo_ps->diagCallback_pcb(f_idMotor_e, motorInfo_ps->Health_e);
            }
        }
        //---- If it's not countor error it is signal error or infinite pulse, already set in health variable ----//
        else 
        {
            motorInfo_ps->diagCallback_pcb(f_idMotor_e, motorInfo_ps->Health_e);
        }
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_PulseOpeMngmt
 *********************************/
static t_eReturnCode s_CL42T_PulseOpeMngmt( t_sCL42T_MotorInfo * f_motorInfo_ps, 
                                            t_bool * f_setAcutation_pb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 currentTime_u32 = (t_uint32)0;

    if( (f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL)
    || (f_setAcutation_pb == (t_bool *)NULL))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        FMKCPU_Get_Tick(&currentTime_u32);

        //---- No Pulse On Going ----//
        if(GETBIT(f_motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_STATE_ON) == BIT_IS_RESET_8B)
        {
            if(GETBIT(f_motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_DEAD_TIME) == BIT_IS_SET_8B)
            {
                if((currentTime_u32 - f_motorInfo_ps->InhibTime_u32) > CL42T_DEAD_TIME_TRANSITION)
                {
                    RESETBIT_8B(f_motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_DEAD_TIME);
                }
            }

            //---- Check is Pulse Has Been Rqst ----//
            if((GETBIT(f_motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_RQST_CMD) == BIT_IS_SET_8B)
            && (GETBIT(f_motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_DEAD_TIME) == BIT_IS_RESET_8B))
            {
                FMKCPU_Get_Tick(&f_motorInfo_ps->PulseRunMaxCnt_u32);
                *f_setAcutation_pb = (t_bool)True;
            }
        }

        //---- Pulse On Going ----//
        else 
        {
            *f_setAcutation_pb = (t_bool)False;
            //----- check pulse time -----//
            if((currentTime_u32 - f_motorInfo_ps->PulseRunMaxCnt_u32) > CL42T_PULSE_RUN_TIME_MAX)
            {
                SETBIT_8B(f_motorInfo_ps->Health_e, CL42T_DIAGNOSTIC_PULSE_INFINITE);
                f_motorInfo_ps->flagErrorDetected_b = (t_bool)True;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_GetDiagErrorFromCnt
 *********************************/
static void s_CL42T_PulseEventMngmt(t_eFMKIO_OutPwmSig f_signal_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxMotor_u8 = (t_uint8)0;
    t_sCL42T_MotorInfo * motorInfo_ps = NULL;

    //---- Find Id Motor ----//
    for(idxMotor_u8 = (t_uint8)0 ; idxMotor_u8 < CL42T_MOTOR_NB ; idxMotor_u8++)
    {
        if(g_MotorInfo_as[idxMotor_u8].SigInfo_as[CL42T_SIGTYPE_PULSE].signal_u8 == (t_uint8)f_signal_e)
        {
            motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[idxMotor_u8]);
            break;
        }
    }
    if(motorInfo_ps != (t_sCL42T_MotorInfo *) NULL)
    {
        FMKCPU_Get_Tick(&motorInfo_ps->InhibTime_u32);

        //---- Set motor Actuators if user needed ----//
        if((GETBIT(motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_RQST_CMD) == BIT_IS_SET_8B))
        {
            Ret_e = s_CL42T_SetSignalsValue(motorInfo_ps);

            if(Ret_e != RC_OK)
            {
                // do something ??
            }
        }
        else
        {
            RESETBIT_8B(motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_STATE_ON);
        }
    }

    return;
}

/*********************************
 * s_CL42T_GetDiagErrorFromCnt
 *********************************/
static void s_CL42T_SigErrorMngmt(t_eFMKIO_SigType f_type_e, 
                                t_uint8 f_signalId_u8, 
                                t_uint16 f_debugInfo1_u16,
                                t_uint16 f_debugInfo2_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxMotor_u8;
    t_uint8 idxSignal_u8;

    if((f_type_e != FMKIO_SIGTYPE_OUTPUT_PWM)
    || (f_type_e != FMKIO_SIGTYPE_INPUT_FREQ))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_type_e)
        {
            case FMKIO_SIGTYPE_OUTPUT_PWM:
            {
                for(idxMotor_u8 = (t_uint8)0 ; idxMotor_u8 < CL42T_MOTOR_NB ; idxMotor_u8++)
                {
                    for(idxSignal_u8 = (t_uint8)0 ; idxSignal_u8 < CL42T_SIGTYPE_NB ; idxSignal_u8++)
                    {
                        if(g_MotorInfo_as->SigInfo_as[idxSignal_u8].signal_u8 == f_signalId_u8)
                        {
                            g_MotorInfo_as[idxMotor_u8].Health_e = CL42T_DIAGNOSTIC_SIGNAL_PULSE;
                            break;
                        }
                    }
                }
                break;
            }
            case FMKIO_SIGTYPE_INPUT_FREQ:
            {
                for(idxMotor_u8 = (t_uint8)0 ; idxMotor_u8 < CL42T_MOTOR_NB ; idxMotor_u8++)
                {
                    for(idxSignal_u8 = (t_uint8)0 ; idxSignal_u8 < CL42T_SIGTYPE_NB ; idxSignal_u8++)
                    {
                        if(g_MotorInfo_as->SigInfo_as[idxSignal_u8].signal_u8 == f_signalId_u8)
                        {
                            g_MotorInfo_as[idxMotor_u8].Health_e = CL42T_DIAGNOSTIC_SIGNAL_PULSE;
                            break;
                        }
                    }
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return;
}

/*********************************
 * s_CL42T_GetDiagErrorFromCnt
 *********************************/
static t_eReturnCode s_CL42T_GetDiagErrorFromCnt(t_uint16 f_counter_u8, t_eCL42T_DiagError * f_diagErr_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_diagErr_pe == (t_eCL42T_DiagError *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_counter_u8)
        {
            case CL42T_ONE_PULSE:
            {
                *f_diagErr_pe = CL42T_DIAGNOSTIC_OVER_CURRENT;
                break;
            }
            case CL42T_TWO_PULSE:
            {
                *f_diagErr_pe = CL42T_DIAGNOSTIC_OVER_VOLTAGE;
                break;
            }
            case CL42T_THREE_PULSE:
            {
                *f_diagErr_pe = CL42T_DIAGNOSTIC_CHIP_ERROR;
                break;
            }
            case CL42T_FOUR_PULSE:
            {
                *f_diagErr_pe = CL42T_DIAGNOSTIC_LOCK_MOTOR_SHAFT;
                break;
            }
            case CL42T_FIVE_PULSE:
            {
                *f_diagErr_pe = CL42T_DIAGNOSTIC_EEPROM;
                break;
            }
            case CL42T_SIX_PULSE:
            {
                *f_diagErr_pe = CL42T_DIAGNOSTIC_AUTO_TUNNING;
                break;
            }
            case CL42T_SEVEN_PULSE: 
            {
                *f_diagErr_pe = CL42T_DIAGNOSTIC_POSITION;
                break;
            }
            default:
            {
                *f_diagErr_pe = CL42T_DIAGNOSTIC_OK;
                break;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_AddPulseSignal
 *********************************/
static t_eReturnCode s_CL42T_AddPulseSignal(t_sCL42T_MotorInfo * f_motorInfo_ps,
                                            t_sCL42T_PwmSignalCfg * f_pulseCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorSignalInfo * SignalInfo_ps;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL
    || f_pulseCfg_ps == (t_sCL42T_PwmSignalCfg *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    
    if(Ret_e == RC_OK)
    {
        SignalInfo_ps = (t_sCL42T_MotorSignalInfo *)(&f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_PULSE]);

        if(f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_PULSE].isConfigured_b == True)
        {
            Ret_e = RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = FMKIO_Set_OutPwmSigCfg( f_pulseCfg_ps->PulseSignal_e, 
                                            f_pulseCfg_ps->PullMode_e, 
                                            f_pulseCfg_ps->f_PulseInitFreq_u32,
                                            FMKTIM_PWM_MODE_FINITE_PULSE,
                                            s_CL42T_PulseEventMngmt,
                                            s_CL42T_SigErrorMngmt);
           

            if(Ret_e == RC_OK)
            {
                SignalInfo_ps->signal_u8 = f_pulseCfg_ps->PulseSignal_e;
                SignalInfo_ps->isConfigured_b = True;
                
                f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_SPEED].signal_u8 =  f_pulseCfg_ps->PulseSignal_e;
                f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_SPEED].isConfigured_b = True;
                f_motorInfo_ps->isConfigured_b = True;
            }
        }
    }
    return Ret_e;
}
/*********************************
 * CL42T_AddDirPulseSignal
 *********************************/
static t_eReturnCode s_CL42T_AddDirSignal(   t_sCL42T_MotorInfo * f_motorInfo_ps,
                                    t_sCL42T_DigitalSignalCfg * f_DirSigCfg_s_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorSignalInfo * SignalInfo_ps;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL
    || f_DirSigCfg_s_ps == (t_sCL42T_DigitalSignalCfg *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    
    if(Ret_e == RC_OK)
    {
        SignalInfo_ps = (t_sCL42T_MotorSignalInfo *)(&f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_DIR]);

        if(f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_DIR].isConfigured_b == True)
        {
            Ret_e = RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = FMKIO_Set_OutDigSigCfg( f_DirSigCfg_s_ps->DigitalSignal_e, 
                                            f_DirSigCfg_s_ps->PullMode_e,
                                            FMKIO_SPD_MODE_MEDIUM);

            if(Ret_e == RC_OK)
            {
                SignalInfo_ps->signal_u8 = f_DirSigCfg_s_ps->DigitalSignal_e;
                SignalInfo_ps->isConfigured_b = True;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * s_CL42T_AddStateSignal
 *********************************/
static t_eReturnCode s_CL42T_AddStateSignal( t_sCL42T_MotorInfo * f_motorInfo_ps,
                                    t_sCL42T_DigitalSignalCfg * f_StateSigCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorSignalInfo * SignalInfo_ps;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL
    || f_StateSigCfg_ps == (t_sCL42T_DigitalSignalCfg *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    
    if(Ret_e == RC_OK)
    {
        SignalInfo_ps = (t_sCL42T_MotorSignalInfo *)(&f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_STATE]);

        if(f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_STATE].isConfigured_b == True)
        {
            Ret_e = RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = FMKIO_Set_OutDigSigCfg( f_StateSigCfg_ps->DigitalSignal_e, 
                                            f_StateSigCfg_ps->PullMode_e,
                                            FMKIO_SPD_MODE_MEDIUM);

            if(Ret_e == RC_OK)
            {
                SignalInfo_ps->signal_u8 = f_StateSigCfg_ps->DigitalSignal_e;
                SignalInfo_ps->isConfigured_b = True;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * s_CL42T_AddDiagSignal
 *********************************/
static t_eReturnCode s_CL42T_AddDiagSignal(  t_sCL42T_MotorInfo * f_motorInfo_ps,
                                    t_sCL42T_FreqSignalCfg * f_DiagSigCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorSignalInfo * SignalInfo_ps;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL
    || f_DiagSigCfg_ps == (t_sCL42T_FreqSignalCfg *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    
    if(Ret_e == RC_OK)
    {
        SignalInfo_ps = (t_sCL42T_MotorSignalInfo *)(&f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_DIAG]);

        if(f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_DIAG].isConfigured_b == True)
        {
            Ret_e = RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = FMKIO_Set_InFreqSigCfg( f_DiagSigCfg_ps->FreqSignal_e, 
                                            FMKIO_STC_RISING_EDGE,
                                            FMKIO_FREQ_MEAS_COUNT, 
                                            s_CL42T_SigErrorMngmt);

            if(Ret_e == RC_OK)
            {
                SignalInfo_ps->signal_u8 = f_DiagSigCfg_ps->FreqSignal_e;
                SignalInfo_ps->isConfigured_b = True;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_SetPulseSignal
 *********************************/
static t_eReturnCode s_CL42T_SetPulseSignal(   t_sCL42T_MotorInfo * f_motorInfo_ps,
                                        t_uint16 f_nbPulses_u16)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        if( f_nbPulses_u16 > (t_uint16)0)
        {
            f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_PULSE].value_u32= f_nbPulses_u16;
            SETBIT_8B(f_motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_RQST_CMD);
        }
    }

    return Ret_e;
}
/*********************************
 * s_CL42T_SetDirSignal
 *********************************/
static t_eReturnCode s_CL42T_SetDirSignal(  t_sCL42T_MotorInfo * f_motorInfo_ps,
                                            t_eCL42T_MotorDirection f_direction_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKIO_DigValue digValue_e;
    t_uint32 currentTime_u32 = (t_uint32)0;

    if(f_direction_e >= CL42T_MOTOR_DIRECTION_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_direction_e)
        {
            case CL42T_MOTOR_DIRECTION_CLOCKWISE:
                digValue_e = FMKIO_DIG_VALUE_HIGH;
                break;
            case CL42T_MOTOR_DIRECTION_WISE:
                digValue_e = FMKIO_DIG_VALUE_LOW;
                break;
            case CL42T_MOTOR_DIRECTION_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }
    if(Ret_e == RC_OK)
    {
        FMKCPU_Get_Tick(&currentTime_u32);

        if( (digValue_e != f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_DIR].value_u32) 
        && ((currentTime_u32 - f_motorInfo_ps->InhibTime_u32) < CL42T_PULSE_BIT_DEAD_TIME))
        {
            SETBIT_8B(f_motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_DEAD_TIME);
        }

        f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_DIR].value_u32 = digValue_e;
    }

    return Ret_e;
}
/*********************************
 * s_CL42T_SetStateSignal
 *********************************/
static t_eReturnCode s_CL42T_SetStateSignal(t_sCL42T_MotorInfo * f_motorInfo_ps,
                                            t_eCL42T_MotorState f_state_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKIO_DigValue digValue_e;

    if(f_state_e >= CL42T_MOTOR_STATE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_state_e)
        {
            case CL42T_MOTOR_STATE_ON:
                digValue_e = FMKIO_DIG_VALUE_HIGH;
                break;
            case CL42T_MOTOR_STATE_OFF:
                digValue_e = FMKIO_DIG_VALUE_LOW;
                break;
            case CL42T_MOTOR_STATE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKIO_Set_OutDigSigValue(   f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_STATE].signal_u8,
                                            digValue_e);

        if(Ret_e == RC_OK)
        {
            f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_STATE].value_u32 = digValue_e;
        }

    }
        
    

    return Ret_e;
}
/*********************************
 * s_CL42T_SetSpeedSignal
 *********************************/
static t_eReturnCode s_CL42T_SetSpeedSignal( t_sCL42T_MotorInfo * f_motorInfo_ps,
                                    t_uint32 f_speed_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_SPEED].value_u32 = f_speed_u32; 
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_GetPulseSignal
 *********************************/
static t_eReturnCode s_CL42T_GetPulseSignal( t_sCL42T_MotorInfo * f_motorInfo_ps,
                                    t_uint16 * f_nbPulses_pu16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorSignalInfo * SigInfo_ps;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        SigInfo_ps = (t_sCL42T_MotorSignalInfo *)(&f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_PULSE]);

        Ret_e = FMKIO_Get_OutPwmSigPulsesLeft(  (t_eFMKIO_OutPwmSig)SigInfo_ps->signal_u8,
                                                f_nbPulses_pu16);
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_GetDirSignal
 *********************************/
static t_eReturnCode s_CL42T_GetDirSignal(   t_sCL42T_MotorInfo * f_motorInfo_ps,
                                    t_eCL42T_MotorDirection *f_direction_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorSignalInfo * SigInfo_ps;
    t_eFMKIO_DigValue digValue_e;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        SigInfo_ps = (t_sCL42T_MotorSignalInfo *)(&f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_DIR]);

        Ret_e = FMKIO_Get_OutDigSigValue(SigInfo_ps->signal_u8, &digValue_e);

        if(Ret_e == RC_OK)
        {
            switch(digValue_e)
            {
                case FMKIO_DIG_VALUE_LOW:
                    *f_direction_pe = CL42T_MOTOR_DIRECTION_CLOCKWISE;
                    break;
                case FMKIO_DIG_VALUE_HIGH:
                    *f_direction_pe = CL42T_MOTOR_DIRECTION_WISE;
                    break;
                case FMKIO_DIG_VALUE_NB:
                default:
                    *f_direction_pe = CL42T_MOTOR_DIRECTION_CLOCKWISE;
                    Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
                    break;

            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_GetStateSignal
 *********************************/
static t_eReturnCode s_CL42T_GetStateSignal(   t_sCL42T_MotorInfo * f_motorInfo_ps,
                                        t_eCL42T_MotorState *f_state_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorSignalInfo * SigInfo_ps;
    t_eFMKIO_DigValue digValue_e;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        SigInfo_ps = (t_sCL42T_MotorSignalInfo *)(&f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_STATE]);

        Ret_e = FMKIO_Get_OutDigSigValue(SigInfo_ps->signal_u8, &digValue_e);

        if(Ret_e == RC_OK)
        {
            switch(digValue_e)
            {
                case FMKIO_DIG_VALUE_LOW:
                    *f_state_pe = CL42T_MOTOR_STATE_OFF;
                    break;
                case FMKIO_DIG_VALUE_HIGH:
                    *f_state_pe = CL42T_MOTOR_STATE_ON;
                    break;
                case FMKIO_DIG_VALUE_NB:
                default:
                    *f_state_pe = CL42T_MOTOR_STATE_OFF;
                    Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
                    break;

            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_GetDiagError
 *********************************/
static t_eReturnCode s_CL42T_GetDiagError(   t_sCL42T_MotorInfo * f_motorInfo_ps,
                                        t_eCL42T_DiagError * f_infoErr_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_infoErr_pe = f_motorInfo_ps->Health_e;
    }

    return Ret_e;
}

/*********************************
 * s_CL42T_GetSpeedSignal
 *********************************/
static t_eReturnCode s_CL42T_GetSpeedSignal( t_sCL42T_MotorInfo * f_motorInfo_ps,
                                    t_uint32 *f_speed_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorSignalInfo * SigInfo_ps;
    t_uint32 frequency_u32;

    if(f_motorInfo_ps == (t_sCL42T_MotorInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        SigInfo_ps = (t_sCL42T_MotorSignalInfo *)(&f_motorInfo_ps->SigInfo_as[CL42T_SIGTYPE_SPEED]);

        Ret_e = FMKIO_Get_OutPwmSigFrequency(   (t_eFMKIO_OutPwmSig)SigInfo_ps->signal_u8,
                                                &frequency_u32);

        if(Ret_e == RC_OK)
        {
            *f_speed_pu32 = frequency_u32;
        }
        else 
        {
            *f_speed_pu32 = (t_uint32)0;
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
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
