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
#include "APP_CFG/ConfigFiles/CL42T_ConfigPublic.h"
#include "./CL42T.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKIO_ConfigPrivate.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************

/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */

//-----------------------------ENUM TYPES-----------------------------//
enum t_eCL42T_PulseFLag
{
    CL42T_PULSE_BIT_STATE,
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
}t_sCL42T_MotorSignalInfo;

typedef struct 
{
    t_sCL42T_MotorSignalInfo SigInfo_as[CL42T_MOTOR_SIGTYPE_NB];
    t_cdCL42T_Diagnostic *diagCallback_pcb;
    t_eFMKCPU_InterruptLineIO pulseITLine_e;
    t_eCL42T_DiagError Health_e;
    t_uint32 InhibTime_u32;
    t_uint32 PulseRunMaxCnt_u32;
    t_bool isConfigured_b;
    t_uint8 pulseMask_u8;
    t_bool flagErrorDetected_b;

}t_sCL42T_MotorInfo;

/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */

//-----------------------------TYPEDEF TYPES---------------------------//

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
static t_eReturnCode s_CL42T_SigErrMngmt();

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
static t_eReturnCode s_CL42T_OperationalState();

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
static t_eReturnCode s_CL42T_PulseOpeMngmt( t_uint8 *f_pulseMask_pu8, 
                                            t_bool *f_setAcutation_pb);

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
static t_eReturnCode s_CL42T_PulseEventMngmt(   t_eFMKCPU_InterruptLineType f_type_e, 
                                                t_eFMKCPU_InterruptLineIO f_InterruptLineIO_e);

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
static t_eReturnCode s_CL42T_SigErrorMngmt( t_eFMKIO_SigType f_typeSig_e, 
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
static t_eReturnCode s_CL42T_GetDigValueFromDir(    t_eCL42T_MotorDirection f_motorDir_e,
                                                    t_eFMKIO_DigValue * f_digValue_pe);
// ********************************************************************
// *                      Variables
// ********************************************************************
static t_sCL42T_MotorInfo;

t_sCL42T_MotorInfo g_MotorInfo_as[CL42T_MOTOR_NB];

static t_bool g_IsRsqstInit_ab[CL42T_MOTOR_NB];

static t_eCyclicModState g_CL42T_ModState_e = STATE_CYCLIC_CFG;

//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * CL42T_Init
 *********************************/
t_eReturnCode CL42T_Init(void)
{



    return RC_OK;
}
/*********************************
 * CL42T_Cyclic
 *********************************/
t_eReturnCode CL42T_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;



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
    if(Ret_e = RC_OK)
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
 * CL42T_AddPulseSignal
 *********************************/
t_eReturnCode CL42T_AddPulseSignal( t_eCL42T_MotorId f_motorId_e,
                                    t_eFMKIO_OutPwmSig f_pulseSignal_e,
                                    t_eFMKIO_PullMode f_pullMode_e,
                                    t_uint32 f_frequency_u32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorInfo * motorInfo_ps;
    t_sCL42T_MotorSignalInfo * SignalInfo_ps;

    if((f_motorId_e >= CL42T_MOTOR_NB) 
    || (f_pulseSignal_e >= FMKIO_OUTPUT_SIGPWM_NB) 
    || (f_pulseSignal_e >=FMKIO_PULL_MODE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_motorId_e]);
        SignalInfo_ps = (t_sCL42T_MotorSignalInfo *)(&motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_PULSE]);

        if(motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_PULSE].isConfigured_b == True)
        {
            Ret_e == RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            #warning("FMKIO has been redefined")
            //Ret_e = FMKIO_SetOutPwmCfg(f_pulseSignal_e, f_pull_e, f_frequency_u32, s_CL42T_SignalErrMngmt);

            if(Ret_e == RC_OK)
            {   
                SignalInfo_ps->signal_u8 = f_pulseSignal_e;
                SignalInfo_ps->isConfigured_b = True;
                motorInfo_ps->pulseITLine_e = c_OutPwmSigBspMap_as[f_pulseSignal_e].ITLine_e;
                g_IsRsqstInit_ab[f_motorId_e]= True;
                motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_SPEED].signal_u8 = f_pulseSignal_e;
                motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_SPEED].isConfigured_b = True;
                motorInfo_ps->isConfigured_b = True;
            }
        }
    }
    return Ret_e;
}
/*********************************
 * CL42T_AddDirPulseSignal
 *********************************/
t_eReturnCode CL42T_AddDirSignal(   t_eCL42T_MotorId f_motorId_e,
                                    t_eFMKIO_OutDigSig f_dirSignal_e,
                                    t_eFMKIO_PullMode f_pullMode_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorInfo * motorInfo_ps;
    t_sCL42T_MotorSignalInfo * SignalInfo_ps;

    if(f_motorId_e >= CL42T_MOTOR_NB 
    || f_dirSignal_e >= FMKIO_OUTPUT_SIGDIG_NB
    || f_pullMode_e >= FMKIO_PULL_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_motorId_e]);
        SignalInfo_ps = (t_sCL42T_MotorSignalInfo *)(&motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_DIR]);

        if(motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_DIR].isConfigured_b == True)
        {
            Ret_e == RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = FMKIO_Set_OutDigSigCfg(f_dirSignal_e, f_pullMode_e,FMKIO_SPD_MODE_MEDIUM);

            if(Ret_e == RC_OK)
            {
                SignalInfo_ps->signal_u8 = f_dirSignal_e;
                SignalInfo_ps->isConfigured_b = True;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * CL42T_AddStateSignal
 *********************************/
t_eReturnCode CL42T_AddStateSignal( t_eCL42T_MotorId f_motorId_e,
                                    t_eFMKIO_OutDigSig f_stateSignal_e,
                                    t_eFMKIO_PullMode f_pullMode_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorInfo * motorInfo_ps;
    t_sCL42T_MotorSignalInfo * SignalInfo_ps;

    if(f_motorId_e >= CL42T_MOTOR_NB 
    || f_stateSignal_e >= FMKIO_OUTPUT_SIGDIG_NB
    || f_pullMode_e >= FMKIO_PULL_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_motorId_e]);
        SignalInfo_ps = (t_sCL42T_MotorSignalInfo *)(&motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_STATE]);

        if(motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_STATE].isConfigured_b == True)
        {
            Ret_e == RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = FMKIO_Set_OutDigSigCfg(f_stateSignal_e, f_pullMode_e,FMKIO_SPD_MODE_MEDIUM);

            if(Ret_e == RC_OK)
            {
                SignalInfo_ps->signal_u8 = f_stateSignal_e;
                SignalInfo_ps->isConfigured_b = True;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * CL42T_DiagStateSignal
 *********************************/
    t_eReturnCode CL42_AddDiagSignal(   t_eCL42T_MotorId f_motorId_e,
                                        t_eFMKIO_InFreqSig f_diagSignal_e,
                                        t_eFMKIO_PullMode f_pullMode_e,
                                        t_cdCL42T_Diagnostic *f_diagnostic_pcb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorInfo * motorInfo_ps;
    t_sCL42T_MotorSignalInfo * SignalInfo_ps;

    if(f_motorId_e >= CL42T_MOTOR_NB 
    || f_diagSignal_e >= FMKIO_INPUT_SIGFREQ_NB
    || f_pullMode_e >= FMKIO_PULL_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_diagnostic_pcb == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_motorId_e]);
        SignalInfo_ps = (t_sCL42T_MotorSignalInfo *)(&motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_DIR]);

        if(motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_STATE].isConfigured_b == True)
        {
            Ret_e == RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            #warning("FMKIO has been redefined")
            //Ret_e = FMKIO_SetInFreqCfg(f_diagSignal_e, FMKIO_STC_RISING_EDGE,FMKIO_FREQ_MEAS_COUNT, s_CL42T_SignalErrMngmt);

            if(Ret_e == RC_OK)
            {
                SignalInfo_ps->signal_u8 = f_diagSignal_e;
                SignalInfo_ps->isConfigured_b = True;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * CL42T_SetPulseSignal
 *********************************/
t_eReturnCode CL42T_SetPulseSignal( t_eCL42T_MotorId f_motorId_e,
                                    t_uint32 f_frequency_u32,
                                    t_uint16 f_nbPulses_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorInfo * motorInfo_ps;

    if(f_motorId_e >= CL42T_MOTOR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_motorId_e]);

        if(motorInfo_ps->isConfigured_b == True)
        {
            Ret_e == RC_ERROR_ALREADY_CONFIGURED;
        }
        if(motorInfo_ps->Health_e == CL42T_DIAGNOSTIC_OK)
        {
            Ret_e = RC_WARNING_BUSY;
        }      
        if(Ret_e == RC_OK)
        {
            if( f_nbPulses_u16 > (t_uint16)0)              //la condition if peut etre enlever a voir avec un mécanicien
            {
                motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_PULSE].value_u32= f_nbPulses_u16;
                SETBIT_8B(motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_RQST_CMD);
            }
        }
    }
    
    return Ret_e;
}
/*********************************
 * CL42T_SetDirSignal
 *********************************/
t_eReturnCode CL42T_SetDirSignal(   t_eCL42T_MotorId f_motorId_e,
                                    t_eCL42T_MotorDirection f_direction_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorInfo * motorInfo_ps;
    t_eFMKIO_DigValue digValue_e;
    t_uint32 currentTime_u32 = 0;

    if(f_motorId_e >= CL42T_MOTOR_NB 
    || f_direction_e >= CL42T_MOTOR_DIRECTION_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_motorId_e]);

        if(motorInfo_ps->isConfigured_b == True)
        {
            Ret_e == RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            FMKCPU_Get_Tick(&currentTime_u32);

            if(motorInfo_ps->Health_e == CL42T_DIAGNOSTIC_OK)
            {
                Ret_e = s_CL42T_GetDigValueFromDir(f_direction_e, &digValue_e);

                if(Ret_e == RC_OK)
                {
                    if( (digValue_e != motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_PULSE].value_u32) 
                    && ((currentTime_u32 - motorInfo_ps->InhibTime_u32)< CL42T_PULSE_BIT_DEAD_TIME))
                    {
                        SETBIT_8B(motorInfo_ps->pulseMask_u8, CL42T_PULSE_BIT_DEAD_TIME);
                    }

                    motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_PULSE].value_u32= digValue_e;
                }
            }
        }
    }

    return Ret_e;
}
/*********************************
 * CL42T_SetStateSignal
 *********************************/
t_eReturnCode CL42T_SetStateSignal( t_eCL42T_MotorId f_motorId_e,
                                    t_eCL42T_MotorState f_state_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorInfo * motorInfo_ps;
    t_eFMKIO_DigValue digValue_e;
    t_uint32 currentTime_u32 = 0;

    if(f_motorId_e >= CL42T_MOTOR_NB 
    || f_state_e >= CL42T_MOTOR_STATE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_motorId_e]);

        if(motorInfo_ps->isConfigured_b == True)
        {
            Ret_e == RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_CL42T_GetDigValueFromState(f_state_e, &digValue_e);

            if(Ret_e == RC_OK)
            {
                motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_PULSE].value_u32 = digValue_e;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * CL42T_SetSpeedSignal
 *********************************/
t_eReturnCode CL42T_SetSpeedSignal( t_eCL42T_MotorId f_motorId_e,
                                    t_uint32 f_speed_u32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sCL42T_MotorInfo * motorInfo_ps;
    t_eFMKIO_DigValue digValue_e;
    t_uint32 currentTime_u32 = 0;

    if(f_motorId_e >= CL42T_MOTOR_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        motorInfo_ps = (t_sCL42T_MotorInfo *)(&g_MotorInfo_as[f_motorId_e]);

        if(motorInfo_ps->isConfigured_b == True)
        {
            Ret_e == RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            if(motorInfo_ps->Health_e == CL42T_DIAGNOSTIC_OK)
            {
                motorInfo_ps->SigInfo_as[CL42T_MOTOR_SIGTYPE_SPEED].value_u32 = f_speed_u32;
            }
        }
    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * CL42T_OperationnalState
 *********************************/
static t_eReturnCode s_CL42T_OperationalState()
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
