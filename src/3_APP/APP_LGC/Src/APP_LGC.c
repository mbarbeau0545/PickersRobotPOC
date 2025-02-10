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
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
#include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
#include "FMK_HAL/FMK_CAN/Src/FMK_FDCAN.h"
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

 const t_sCL42T_MotorSigCfg c_CL42T_MotorConfig_as[CL42T_MOTOR_NB] = {
        [CL42T_MOTOR_AXE_X_1] = {
            .PulseSigCfg_s = {
                .PulseSignal_e = FMKIO_OUTPUT_SIGPWM_3, //PA10 GREEN WIRE
                .PullMode_e =  FMKIO_PULL_MODE_DISABLE,
                .f_PulseInitFreq_u32 = 2
            },
            .StateSigCfg = {
                .DigitalSignal_e = FMKIO_OUTPUT_SIGDIG_2, //PB13 BROWN WIRE
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
            .DirSigCfg_s = {
                .DigitalSignal_e = FMKIO_OUTPUT_SIGDIG_1, //PB12 RED WIRE
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
            .DiagSigCfg_s = {
                .FreqSignal_e = FMKIO_INPUT_SIGFREQ_1, //PC8 WHITE WIRE
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
        },

        [CL42T_MOTOR_AXE_X_2] = {
            .PulseSigCfg_s = {
                .PulseSignal_e = FMKIO_OUTPUT_SIGPWM_4,
                .PullMode_e =  FMKIO_PULL_MODE_DISABLE,
                .f_PulseInitFreq_u32 = 2
            },
            .StateSigCfg = {
                .DigitalSignal_e = FMKIO_OUTPUT_SIGDIG_4,
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
            .DirSigCfg_s = {
                .DigitalSignal_e = FMKIO_OUTPUT_SIGDIG_5,
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
            .DiagSigCfg_s = {
                .FreqSignal_e = FMKIO_INPUT_SIGFREQ_2,
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
        },
    };
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
static t_eReturnCode s_APPLGC_PreOperational(void);
static t_eReturnCode s_APPLGC_Operational(void);
static t_eReturnCode s_APPLGC_ConfigurationState(void);
static void s_MotorCallback(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_DefeultInfo_e);
static void s_APPLGC_RcvSrlEvent(  t_uint8 * f_rxData_pu8, 
                                    t_uint16 f_dataSize_u16, 
                                    t_eFMKSRL_RxCallbackInfo f_InfoCb_e);

static void s_APPLGC_TranmistEvnt(t_bool f_isMsgTransmit_b, t_eFMKSRL_TxCallbackInfo f_InfoCb_e);
static void s_PulseCallback(t_eFMKIO_OutPwmSig f_signal_e);

static void s_CL42T_Diag(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_DefeultInfo_e);

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * APPLGC_Init
 *********************************/
t_eReturnCode APPLGC_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    Ret_e = CL42T_Init();
    Ret_e = CL42T_AddMotorConfiguration(    CL42T_MOTOR_AXE_X_1,
                                            c_CL42T_MotorConfig_as[CL42T_MOTOR_AXE_X_1],
                                            s_CL42T_Diag);
    
    return Ret_e;
}

/*********************************
 * APPLGC_Init
 *********************************/
t_eReturnCode APPLGC_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;
    // code to run every x milliseconds, config in APPSYS_ConfigPrivate.h
    Ret_e = CL42T_Cyclic();
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
    CL42T_SetState(f_State_e);

    return RC_OK;
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

   /*Ret_e = FMKIO_Set_OutPwmSigCfg( FMKIO_OUTPUT_SIGPWM_3,
                                    FMKIO_PULL_MODE_DISABLE,
                                    26000,
                                    FMKTIM_PWM_MODE_FINITE_PULSE,
                                    s_PulseCallback,
                                    NULL_FONCTION);
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKIO_Set_InFreqSigCfg( FMKIO_INPUT_SIGFREQ_1,
                                        FMKIO_STC_RISING_EDGE,
                                        FMKIO_FREQ_MEAS_FREQ,
                                        NULL_FONCTION);
    }
    if(Ret_e == RC_OK)
    {

        SrlCfg_s.runMode_e = FMKSRL_LINE_RUNMODE_IT;
        SrlCfg_s.hwProtType_e = FMKSRL_HW_PROTOCOL_UART;

        SrlCfg_s.hwCfg_s.Baudrate_e = FMKSRL_LINE_BAUDRATE_9600,
        SrlCfg_s.hwCfg_s.Mode_e = FMKSRL_LINE_MODE_RX_TX;
        SrlCfg_s.hwCfg_s.Parity_e = FMKSRL_LINE_PARITY_NONE,
        SrlCfg_s.hwCfg_s.Stopbit_e = FMKSRL_LINE_STOPBIT_1,
        SrlCfg_s.hwCfg_s.wordLenght_e = FMKSRL_LINE_WORDLEN_8BITS,

        SrlCfg_s.CfgSpec_u.uartCfg_s.hwFlowCtrl_e = FMKSRL_UART_HW_FLOW_CTRL_NONE;
        SrlCfg_s.CfgSpec_u.uartCfg_s.Type_e = FMKSRL_UART_TYPECFG_UART,

        Ret_e = FMKSRL_InitDrv( FMKSRL_SERIAL_LINE_2, 
                                SrlCfg_s,
                                s_APPLGC_RcvSrlEvent,
                                s_APPLGC_TranmistEvnt);
    }  */  

    return Ret_e;
}

/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_PreOperational(void)
{
    t_eReturnCode Ret_e = RC_OK;

/*Ret_e = FMKIO_Set_OutPwmSigPulses(  FMKIO_OUTPUT_SIGPWM_3,
                                        (t_uint16)500,
                                        (t_uint16)12000);*/    

    
    t_uCL42T_SetMotorValue u_SetMotorValue;

    u_SetMotorValue.state_e = CL42T_MOTOR_STATE_ON;

    Ret_e = CL42T_SetMotorSigValue( CL42T_MOTOR_AXE_X_1,
                                CL42T_SIGTYPE_STATE,
                                u_SetMotorValue);
    
    u_SetMotorValue.dir_e = CL42T_MOTOR_DIRECTION_CLOCKWISE;

    Ret_e = CL42T_SetMotorSigValue( CL42T_MOTOR_AXE_X_1,
                                CL42T_SIGTYPE_DIR,
                                u_SetMotorValue);


    u_SetMotorValue.nbPulses_u16 = 200;

    Ret_e = CL42T_SetMotorSigValue( CL42T_MOTOR_AXE_X_1,
                                CL42T_SIGTYPE_PULSE,
                                u_SetMotorValue);
 

    return Ret_e;
}

/*********************************
 * s_APPLGC_Operational
 *********************************/
static t_eReturnCode s_APPLGC_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_bool s_logicdone_b = (t_bool)False;
    /*t_uCL42T_SetMotorValue u_SetMotorValue;
    u_SetMotorValue.dir_e = CL42T_MOTOR_DIRECTION_WISE;
    if(s_logicdone_b == False)
    {
        
        Ret_e = CL42T_SetMotorSigValue( CL42T_MOTOR_AXE_X_1,
                                CL42T_SIGTYPE_DIR,
                                u_SetMotorValue);

        u_SetMotorValue.nbPulses_u16 = 10;

        Ret_e = CL42T_SetMotorSigValue( CL42T_MOTOR_AXE_X_1,
                                CL42T_SIGTYPE_PULSE,
                                u_SetMotorValue);

        s_logicdone_b = true;
    }*/
    /*t_uint32 measCount_u32 = 0;
    char msgbuffer[40];
    Ret_e = FMKIO_Get_InFreqSigValue(FMKIO_INPUT_SIGFREQ_1, &measCount_u32);

    if(Ret_e == RC_OK)
    {
        sprintf(msgbuffer, "frequency : %d\r\n", (int)measCount_u32);    
        Ret_e = FMKSRL_Transmit(FMKSRL_SERIAL_LINE_2,
                                FMKSRL_TX_ONESHOT, 
                                (t_uint8 *)msgbuffer,
                                (t_uint16)strlen(msgbuffer),
                                0,
                                False);
    }*/


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

/*********************************
 * s_MotorCallback
 *********************************/
static void s_CL42T_Diag(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_DefeultInfo_e){


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

