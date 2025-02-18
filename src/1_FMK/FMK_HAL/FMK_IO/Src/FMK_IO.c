/**
 * @file        FMKIO.c
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
#include "./FMK_IO.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKIO_ConfigPrivate.h"
#include "FMK_HAL/FMK_CDA/Src/FMK_CDA.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"

// ********************************************************************
// *                      Defines
// ********************************************************************
#define FMKIO_AF_UNUSED ((t_uint8)0xFF) /**< Flag to say that the alternate function is not used in Signal Init */
// ********************************************************************
// *                      Types
// ********************************************************************
//-----------------------------ENUM TYPES-----------------------------//
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */

//-----------------------------TYPEDEF TYPES---------------------------//
//-----------------------------STRUCT TYPES---------------------------//
/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
/**< Structure common to all digital signal to repertory signal information */
typedef struct __t_sFMKIO_DigSigInfo
{
    t_bool IsSigConfigured_b;               /**< Flag which indicate wether or not the signal has been configured */

} t_sFMKIO_DigSigInfo;

/**< Structure common to all analog  signal to repertory signal information */
typedef struct __t_sFMKIO_AnaigInfo
{
    t_bool IsSigConfigured_b;                   /**< Flag which indicate wether or not the signal has been configured */
    t_cbFMKIO_SigErrorMngmt * sigError_cb;      /**< callback function if an error occured  */

} t_sFMKIO_AnaSigInfo;
/**< Structure common to all Pwm signal to repertory signal information */
typedef struct __t_sFMKIO_AnaPwmSigInfo
{
    t_bool IsSigConfigured_b;                   /**< Flag which indicate wether or not the signal has been configured */
    t_uint16 dutyCycleApplied_u16;
    t_uint32 frequencyApplied_u32;
    t_cbFMKIO_PulseEvent    * pulseEvnt_pcb;      /**< callback function when a pulse is finihed if pwm pulse is set  */
    t_cbFMKIO_SigErrorMngmt * sigError_cb;      /**< callback function if an error occured  */

} t_sFMKIO_PwmSigInfo;

/**< Structure common to frequency signal information */
typedef struct __t_sFMKIO_InFreqSigInfo
{
    t_bool IsSigConfigured_b;       /**< @ref  IsSigConfigured_b*/
    t_bool isSigCalib_b;            /**< Flag to know if the frequency of the Input Compare is well calibrate  */
    t_eFMKIO_FreqMeas meas_e;       /**< Frequency measuremnt mode (counter/ freq/Period) */
    t_uint32 value_u32;             /**< the difference between the last and current capture on channel */
    t_uint32 savedValue_32;         /**< last value saved of diffValue_u32 */
    t_uint32 TimFreqValue_u32;
    t_uint32 TimARRValue_u32;         /**<  */
    t_bool FlagValueWriting_b;      /**< Flag indicate that an interruption is in progress */
    t_cbFMKIO_SigErrorMngmt * sigError_cb;    /**< callback function if an error occured  */

} t_sFMKIO_InFreqSigInfo;

/**< Structure common to Event signal information */
typedef struct __t_sFMKIO_InEvntSigInfo
{
    t_bool IsSigConfigured_b;               /**< @ref  IsSigConfigured_b*/
    t_uint32 debcDelay_u32;                 /**< Debouncer delay to ignore fluctuation when a interruption happen */
    t_cbFMKIO_EventFunc * EvntFunc_cb;       /**< Store the callback function*/
    t_cbFMKIO_SigErrorMngmt * sigError_cb;    /**< callback function if an error occured  */
   
} t_sFMKIO_InEvntSigInfo;

/**< Structure common to Encoder Signal Information */
typedef struct __t_sFMKIO_InEcdrSigInfo
{
    t_bool isEcdrConfigured_b; 
    t_eFMKIO_EcdrStartOpe EcdrOpe;
} t_sFMKIO_InEcdrSigInfo;
// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
//--------IO Managment--------//
t_sFMKIO_InFreqSigInfo      g_InFreqSigInfo_as[FMKIO_INPUT_SIGFREQ_NB];        /**< Signal information for input frequency */
t_sFMKIO_AnaSigInfo         g_InAnaSigInfo_as[FMKIO_INPUT_SIGANA_NB];          /**< Signal information for input Analog */
t_sFMKIO_DigSigInfo         g_InDigSigInfo_as[FMKIO_INPUT_SIGDIG_NB];          /**< Signal information for input Digital */
t_sFMKIO_InEvntSigInfo      g_InEvntSigInfo_as[FMKIO_INPUT_SIGEVNT_NB];        /**< Signal information for input Event */
t_sFMKIO_InEcdrSigInfo      g_InEcdrSigInfo_as[FMKIO_INPUT_ENCODER_NB];        /**< Signal information for inout Digital */
t_sFMKIO_PwmSigInfo         g_OutPwmSigInfo_as[FMKIO_OUTPUT_SIGPWM_NB];        /**< Signal information for output PWM */
t_sFMKIO_DigSigInfo         g_OutDigSigInfo_as[FMKIO_OUTPUT_SIGDIG_NB];        /**< Signal information for output Digital */
//--------Communication Managment--------//
t_bool g_IsIOComCanConfigured_ab[FMKIO_COM_SIGNAL_CAN_NB];
t_bool g_IsIOComSerialConConfigured_ab[FMKIO_COM_SIGNAL_SERIAL_NB];

t_uint32 g_InFreqLastCapture_ua32[FMKIO_INPUT_SIGFREQ_NB];                      /**< Storage for Last Capture value for freqency pins */

/* CAUTION : Automatic generated code section for Variable: Start */
/**< Variable to store the state of GPIO Clock */
t_eFMKCPU_ClockPortOpe g_IsGpioClockEnable_ae[FMKIO_GPIO_PORT_NB];
/* CAUTION : Automatic generated code section for Variable: End */

/**< Module state */
static t_eCyclicModState g_FmkIO_ModState_e = STATE_CYCLIC_CFG;
t_uint32 g_lastTick_ua32[FMKIO_INPUT_SIGEVNT_NB];
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
 *
 *	@brief      Get the Bsp Pull Mode 
 *	@note       Using the enum f_pull_e and switch case, this function 
                return the right uint32 hal pull for a pin.\n
 *
 *
 *	@param[in]  f_pull_e       : the enum that says the pull mode, value from @ref t_eFMKIO_PullMode
 *	@param[in]  f_bspPull_pu32 : the Hal value correponding the enum
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 * @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKIO_Get_BspPullMode(t_eFMKIO_PullMode f_pull_e, t_uint32 *f_bspPull_pu32);
/**
 *
 *	@brief      Get the Bsp speed Mode 
 *	@note       Using the enum f_spd_e and switch case, this function 
                return the right uint32 hal speed for a pin.\n
 *
 *
 *	@param[in]  f_spd_e       : the enum that says the speed mode, value from @ref t_eFMKIO_SpdMode
 *	@param[in]  f_bspSpd_pu32 : the Hal value correponding the enum
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 * @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKIO_Get_BspSpdMode(t_eFMKIO_SpdMode f_spd_e, t_uint32 *f_bspSpd_pu32);

/**
 *
 *	@brief      Get the Bsp trigger Mode for signal event
 *	@note       Using the enum f_trigger_e and switch case, this function 
                return the right uint32 hal trigger for a pin.\n
 *
 *
 *	@param[in]  f_trigger_e           : the enum that says the trigger mode, value from @ref t_eFMKIO_SigTrigCptr
 *	@param[in]  f_bspTrigger_pu32     : the Hal value correponding the enum
 *
 * @retval RC_OK                             @ref RC_OK
 *
 */
static t_eReturnCode s_FMKIO_Get_BspTriggerMode(t_eFMKIO_SigTrigCptr f_trigger_e, t_uint32 *f_bspTrigger_pu32);
/**
 *
 *	@brief      Get the Time Operation base on IO Encoder Ope.
 *
 *
 *	@param[in]  f_trigger_e           : the enum that says the trigger mode, value from @ref t_eFMKIO_SigTrigCptr
 *	@param[in]  f_bspTrigger_pu32     : the Hal value correponding the enum
 *
 * @retval RC_OK                             @ref RC_OK
 *
 */
static t_eReturnCode s_FMKIO_Get_EcdrTimerMode(t_eFMKIO_EcdrStartOpe f_StartOpeMode_e, t_eFMKTIM_EcdrOpe * f_EdrTimerOpe_pe);
/**
 *
 *	@brief      This function set the Init of a pin on a GPIO
 *
 *	@param[in]  f_GpioPort_e     : GPIOPort enum from @ref t_eFMKIO_GpioPort
 *	@param[in]  f_pin_e          : pin enum from @ref t_eFMKIO_BspGpioPin
 *	@param[in]  f_mode_u32       : Pin Mode from HAL_GPIO.h
 *	@param[in]  f_pull_e         : the enum that says the pull mode, value from @ref t_eFMKIO_PullMode
 *	@param[in]  f_spd_e          : the enum that says the speed mode, value from @ref t_eFMKIO_SpdMode
 *	@param[in]  f_AltFunc_u8     : the alternate function, FMKIO_AF_UNUSED if not used
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static t_eReturnCode s_FMKIO_Set_BspSigCfg(t_eFMKIO_GpioPort f_gpioPort_e,
                                            t_eFMKIO_BspGpioPin f_pin_e,
                                            t_uint32 f_mode_u32,
                                            t_eFMKIO_PullMode f_pull_e,
                                            t_eFMKIO_SpdMode f_spd_e,
                                            t_uint8 f_AltFunc_u8);
/**
 *
 *	@brief      FMKTIM callback function to determine signal frequency value
 *
 *	@param[in]  f_InterruptType_e        : Interrupt Type from  @ref t_eFMKTIM_InterruptLineType
 *	@param[in]  f_InterruptLine_u8       : Interrupt Line
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static t_eReturnCode s_FMKIO_MngSigFrequency(t_eFMKTIM_InterruptLineType f_InterruptType_e, t_uint8 f_InterruptLine_u8);
/**
 *
 *	@brief      FMKTIM callback function to determine signal frequency value
 *
 *	@param[in]  f_InterruptType_e        : Interrupt Type from  @ref t_eFMKTIM_InterruptLineType
 *	@param[in]  f_InterruptLine_u8       : Interrupt Line
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static void s_FMKIO_MngSigPwm(t_eFMKTIM_InterruptLineType f_InterruptType_e, t_uint8 f_InterruptLine_u8);
/**
 *
 *	@brief      Function to set HAL_RCC clock state : Enable/Disable
 *
 *	@param[in]  f_GpioPort_e     : GPIOPort enum, value from @ref t_eFMKIO_GpioPort
 *	@param[in]  f_ope_e          : Enable or Diable RCC clock, value from @ref t_eFMKTIM_ClockPortOpe
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static t_eReturnCode s_FMKIO_Set_GpioClkState(t_eFMKIO_GpioPort f_gpioPort_e, t_eFMKCPU_ClockPortOpe f_ope_e);
/**
 *
 *	@brief      Function to centralized GPIO interruption management
 *  @note       Called user function and reset flag 
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static void s_FMKIO_BspRqst_InterruptMngmt(void);

/**
 *
 *	@brief      Function to perform diag on siganl used 
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static t_eReturnCode s_FMKIO_Operational(void);
/**
 *
 *	@brief      Function to perform diag on siganl used 
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static t_eReturnCode s_FMKIO_PreOperational(void);
/**
 *
 *	@brief      Perform diagnostic cyclic on signal configured.\n 
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static t_eReturnCode s_FMKIO_PerformDiagnostic(void);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * FMKTIM_Init
 *********************************/
t_eReturnCode FMKIO_Init(void)
{
    t_uint8 LLI_u8;
    
    //--------- Gpio clock port status ---------//
    for(LLI_u8 = (t_uint8)0; LLI_u8 < FMKIO_GPIO_PORT_NB ; LLI_u8++)
    {
        g_IsGpioClockEnable_ae[LLI_u8] = FMKCPU_CLOCKPORT_OPE_DISABLE;
    }

    //---------Set Frequency Input Default Value---------//
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_INPUT_SIGFREQ_NB ; LLI_u8++)
    {
        g_InFreqSigInfo_as[LLI_u8].meas_e = FMKIO_FREQ_MEAS_NB;
        g_InFreqSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
        g_InFreqSigInfo_as[LLI_u8].isSigCalib_b        = False;
        g_InFreqSigInfo_as[LLI_u8].FlagValueWriting_b  = False;
        g_InFreqSigInfo_as[LLI_u8].value_u32           = (t_uint32)0;
        g_InFreqSigInfo_as[LLI_u8].savedValue_32      = (t_uint32)0;
        g_InFreqSigInfo_as[LLI_u8].sigError_cb = (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION;

        g_InFreqLastCapture_ua32[LLI_u8] = (t_uint32)0;
    }

    //---------Set Analogic Input Default Value---------//
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_INPUT_SIGANA_NB ; LLI_u8++)
    {
        g_InAnaSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
        g_InAnaSigInfo_as[LLI_u8].sigError_cb = (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION;
    }

    //---------Set Digital Input Default Value---------//
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_INPUT_SIGDIG_NB ; LLI_u8++)
    {
        g_InDigSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
    }

    //---------Set Event Input Default Value---------//
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_INPUT_SIGEVNT_NB ; LLI_u8++)
    {
        g_InEvntSigInfo_as[LLI_u8].EvntFunc_cb = (t_cbFMKIO_EventFunc *)NULL_FONCTION;
        g_InEvntSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
        g_InEvntSigInfo_as[LLI_u8].debcDelay_u32 = (t_uint32)0;
        g_InEvntSigInfo_as[LLI_u8].sigError_cb = (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION;

        g_lastTick_ua32[LLI_u8] = (t_uint32)0;
    }

    //---------Set Pwm Output Default Value---------//
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_OUTPUT_SIGPWM_NB ; LLI_u8++)
    {
        g_OutPwmSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
        g_OutPwmSigInfo_as[LLI_u8].dutyCycleApplied_u16   = (t_uint16)0;
        g_OutPwmSigInfo_as[LLI_u8].frequencyApplied_u32   = (t_uint16)0;
        g_OutPwmSigInfo_as[LLI_u8].sigError_cb = (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION;
        g_OutPwmSigInfo_as[LLI_u8].pulseEvnt_pcb = (t_cbFMKIO_PulseEvent *)NULL_FONCTION;
    }

    //---------Set Digital Output Default Value---------//
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_OUTPUT_SIGDIG_NB ; LLI_u8++)
    {
        g_OutDigSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
    }

    //---------Set Signal Com CAN Default Value---------//
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < FMKIO_COM_SIGNAL_CAN_NB ; LLI_u8++)
    {
        g_IsIOComCanConfigured_ab[LLI_u8] = (t_bool)False;
    }

    //---------Set Signal Com CAN Default Value---------//
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < FMKIO_COM_SIGNAL_SERIAL_NB ; LLI_u8++)
    {
        g_IsIOComSerialConConfigured_ab[LLI_u8] = (t_bool)False;
    }

    return RC_OK;
}
/*********************************
 * FMKIO_Cyclic
 *********************************/
t_eReturnCode FMKIO_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch (g_FmkIO_ModState_e)
    {
        case STATE_CYCLIC_CFG:
        {
            g_FmkIO_ModState_e = STATE_CYCLIC_WAITING;
            break;
        }
        case STATE_CYCLIC_WAITING:
        {
            // nothing to do, just wait all module are Ope
            break;
        }
        case STATE_CYCLIC_PREOPE:
        {
            Ret_e = s_FMKIO_PreOperational();
            if(Ret_e == RC_OK)
            {
                g_FmkIO_ModState_e = STATE_CYCLIC_OPE;
            }
            // nothing to do, just wait all module are Ope
            break;
        }
        case STATE_CYCLIC_OPE:
        {
            Ret_e = s_FMKIO_Operational();
            if(Ret_e < RC_OK)
            {
                g_FmkIO_ModState_e = STATE_CYCLIC_ERROR;
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
 * FMKIO_GetState
 *********************************/
t_eReturnCode FMKIO_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    
    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_FmkIO_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * FMKIO_SetState
 *********************************/
t_eReturnCode FMKIO_SetState(t_eCyclicModState f_State_e)
{
    g_FmkIO_ModState_e = f_State_e;
    return RC_OK;
}
/*********************************
 * s_FMKIO_Get_BspPullMode
 *********************************/
t_eReturnCode FMKIO_Set_InDigSigCfg(t_eFMKIO_InDigSig f_signal_e, t_eFMKIO_PullMode f_pull_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKIO_GpioPort gpioPort_e;

    if (f_signal_e >= FMKIO_INPUT_SIGDIG_NB || f_pull_e >= FMKIO_PULL_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_InDigSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        gpioPort_e = c_InDigSigBspMap_as[f_signal_e].HwGpio_e;
        Ret_e = s_FMKIO_Set_BspSigCfg(gpioPort_e,
                                      c_InDigSigBspMap_as[f_signal_e].HwPin_e,
                                      (t_uint32)FMKIO_BSP_MODE_INPUT,
                                      f_pull_e,
                                      FMKIO_SPD_MODE_LOW, // irrevelent for a input sig dig
                                      FMKIO_AF_UNUSED);
        if (Ret_e == RC_OK)
        {
            g_InDigSigInfo_as[f_signal_e].IsSigConfigured_b = (t_bool)True;
        }
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Set_InAnaSigCfg
 *********************************/
t_eReturnCode FMKIO_Set_InAnaSigCfg(t_eFMKIO_InAnaSig f_signal_e, 
                                        t_eFMKIO_PullMode f_pull_e,
                                        t_cbFMKIO_SigErrorMngmt *f_sigErr_cb)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_signal_e >= FMKIO_INPUT_SIGANA_NB || f_pull_e >= FMKIO_PULL_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_InAnaSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKIO_Set_BspSigCfg(c_InAnaSigBspMap_as[f_signal_e].BasicCfg_s.HwGpio_e,
                                      c_InAnaSigBspMap_as[f_signal_e].BasicCfg_s.HwPin_e,
                                      (t_uint32)FMKIO_BSP_MODE_ANALOG,
                                      f_pull_e,
                                      FMKIO_SPD_MODE_LOW, // irrevelent for a input sig dig
                                      FMKIO_AF_UNUSED);
        if (Ret_e == RC_OK)
        { // configure the adc
            Ret_e = FMKCDA_Set_AdcChannelCfg(c_InAnaSigBspMap_as[f_signal_e].adc_e,
                                             c_InAnaSigBspMap_as[f_signal_e].adcChannel_e,
                                             FMKCDA_ADC_CFG_SCAN_DMA);

            if (Ret_e == RC_OK)
            { // update info
                g_InAnaSigInfo_as[f_signal_e].IsSigConfigured_b = (t_bool)True;
                g_InAnaSigInfo_as[f_signal_e].sigError_cb = f_sigErr_cb;
            }
        }
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Set_InFreqSigCfg
 *********************************/
t_eReturnCode FMKIO_Set_InFreqSigCfg(   t_eFMKIO_InFreqSig f_signal_e, 
                                        t_eFMKIO_SigTrigCptr f_trigger_e,
                                        t_eFMKIO_FreqMeas f_freqMeas_e,
                                        t_cbFMKIO_SigErrorMngmt *f_sigErr_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_ChnlMeasTrigger cpu_trigger_e = FMKTIM_LINE_MEAS_NB;
    t_eFMKTIM_InterruptLineIO ITLineIO_e;

    if (f_signal_e >= FMKIO_INPUT_SIGFREQ_NB 
    || f_trigger_e >= FMKIO_STC_NB 
    || f_freqMeas_e >= FMKIO_FREQ_MEAS_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_InFreqSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKIO_Set_BspSigCfg(c_InFreqSigBspMap_as[f_signal_e].BasicCfg_s.HwGpio_e,
                                      c_InFreqSigBspMap_as[f_signal_e].BasicCfg_s.HwPin_e,
                                      (t_uint32)GPIO_MODE_AF_PP,
                                      FMKIO_PULL_MODE_UP,
                                      FMKIO_SPD_MODE_HIGH, 
                                      c_InFreqSigBspMap_as[f_signal_e].BspAlternateFunc_u8);
        if (Ret_e == RC_OK)
        {
            switch (f_trigger_e)
            {
                case FMKIO_STC_RISING_EDGE:
                    cpu_trigger_e = FMKTIM_LINE_MEAS_RISING_EDGE;
                    break;
                case FMKIO_STC_FALLING_EDGE:
                    cpu_trigger_e = FMKTIM_LINE_MEAS_FALLING_EDGE;
                    break;
                case FMKIO_STC_BOTH_EDGE:
                    cpu_trigger_e = FMKTIM_LINE_MEAS_BOTH_EDGE;
                    break;
                case FMKIO_STC_NB:
                default:
                    Ret_e = RC_ERROR_WRONG_CONFIG;
                    break;
            }
        }
        if(Ret_e == RC_OK)
        {
            ITLineIO_e = c_InFreqSigBspMap_as[f_signal_e].ITLine_e;
            // get the FMKTIM channel meas corresponding to f_trigger_e
            Ret_e = FMKTIM_Set_ICLineCfg(ITLineIO_e,
                                        cpu_trigger_e,
                                        (t_cbFMKTIM_InterruptLine *)s_FMKIO_MngSigFrequency);
        }
        if (Ret_e == RC_OK)
        { // update info
            g_InFreqSigInfo_as[f_signal_e].IsSigConfigured_b = (t_bool)True;
            g_InFreqSigInfo_as[f_signal_e].meas_e = f_freqMeas_e;
            g_InFreqSigInfo_as[f_signal_e].sigError_cb = f_sigErr_cb;
        }
        
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Set_InEncoderSigCfg
 *********************************/
t_eReturnCode FMKIO_Set_InEncoderSigCfg(t_eFMKIO_InEcdrSignals f_InEncdr_e,
                                        t_uint32 f_PulsePerRevolution_u32,
                                        t_sFMKTIM_EcdrCfg f_HwEcdrCfg_s,
                                        t_eFMKIO_PullMode f_pull_e,
                                        t_eFMKIO_SpdMode f_spd_e,
                                        t_eFMKIO_EcdrStartOpe f_startOpe)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKIO_GpioPort gpioPort_e;
    t_eFMKIO_BspGpioPin gpioPin_e;
    t_uint8 bspAF_u8;

    if(f_InEncdr_e >= FMKIO_INPUT_ENCODER_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_InEcdrSigInfo_as[f_InEncdr_e].isEcdrConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if(Ret_e == RC_OK)
    {
        //---- reach Information & Initialize Pin -----//
        gpioPort_e = c_FmkIo_InEcdrSigBspCfg_as[f_InEncdr_e].SigDir_s.HwGpio_e;
        gpioPin_e = c_FmkIo_InEcdrSigBspCfg_as[f_InEncdr_e].SigDir_s.HwPin_e;
        bspAF_u8 = c_FmkIo_InEcdrSigBspCfg_as[f_InEncdr_e].BspAlternateFunc_u8;

        Ret_e = s_FMKIO_Set_BspSigCfg(  gpioPort_e,
                                        gpioPin_e,
                                        GPIO_MODE_AF_PP,
                                        f_pull_e,
                                        f_spd_e,
                                        bspAF_u8);
        if(Ret_e == RC_OK)
        {
            gpioPort_e = c_FmkIo_InEcdrSigBspCfg_as[f_InEncdr_e].SigPos_s.HwGpio_e;
            gpioPin_e = c_FmkIo_InEcdrSigBspCfg_as[f_InEncdr_e].SigPos_s.HwPin_e;

            Ret_e = s_FMKIO_Set_BspSigCfg(  gpioPort_e,
                                            gpioPin_e,
                                            GPIO_MODE_AF_PP,
                                            f_pull_e,
                                            f_spd_e,
                                            bspAF_u8);
        }
        if(Ret_e == RC_OK)
        {

            //----- Call FMKTIM Timer Encoder Configuration -----//
            Ret_e = FMKTIM_Set_EcdrLineCfg(  c_FmkIo_InEcdrSigBspCfg_as[f_InEncdr_e].ITLine_e,
                                                f_HwEcdrCfg_s,
                                                f_PulsePerRevolution_u32);

            if(Ret_e == RC_OK)
            {
                g_InEcdrSigInfo_as[f_InEncdr_e].isEcdrConfigured_b = (t_bool)True;
                g_InEcdrSigInfo_as[f_InEncdr_e].EcdrOpe = f_startOpe;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * FMKIO_Set_InEvntSigCfg
 *********************************/
t_eReturnCode FMKIO_Set_InEvntSigCfg(t_eFMKIO_InEvntSig f_signal_e, 
                                          t_eFMKIO_PullMode f_pull_e,
                                          t_eFMKIO_SigTrigCptr f_trigger_e,
                                          t_uint32 f_debouncerDelay_u32,
                                          t_cbFMKIO_EventFunc * f_Evnt_cb,
                                          t_cbFMKIO_SigErrorMngmt *f_sigErr_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKIO_GpioPort gpioPort_e;
    t_uint32 bspTrigger_u32;

    if ((f_signal_e >= FMKIO_INPUT_SIGEVNT_NB)
    ||  (f_pull_e >= FMKIO_PULL_MODE_NB) 
    ||  (f_trigger_e >= FMKIO_STC_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_Evnt_cb == (t_cbFMKIO_EventFunc *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_InEvntSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        gpioPort_e = c_InEvntSigBspMap_as[f_signal_e].BasicCfg_s.HwGpio_e;
        Ret_e = s_FMKIO_Get_BspTriggerMode(f_trigger_e, &bspTrigger_u32);
        if (Ret_e == RC_OK)
        {
            Ret_e = s_FMKIO_Set_BspSigCfg(gpioPort_e,
                                          c_InEvntSigBspMap_as[f_signal_e].BasicCfg_s.HwPin_e,
                                          (t_uint32)bspTrigger_u32,
                                          FMKIO_PULL_MODE_DISABLE,
                                          FMKIO_SPD_MODE_LOW, // irrevelent for a input sig dig
                                          FMKIO_AF_UNUSED);
            if (Ret_e == RC_OK)
            {

                Ret_e = FMKCPU_Set_NVICState(c_InEvntSigBspMap_as[f_signal_e].ExtiIRQN_e,
                                             FMKCPU_NVIC_OPE_ENABLE);
                if (Ret_e == RC_OK)
                { // update info
                    g_InEvntSigInfo_as[f_signal_e].IsSigConfigured_b = (t_bool)True;
                    g_InEvntSigInfo_as[f_signal_e].debcDelay_u32 = f_debouncerDelay_u32;
                    g_InEvntSigInfo_as[f_signal_e].EvntFunc_cb = f_Evnt_cb;
                    g_InEvntSigInfo_as[f_signal_e].sigError_cb = f_sigErr_cb;
                }
            }
        }
    }
    return Ret_e;
}
/*********************************
 * FMKIO_Set_OutPwmSigCfg
 *********************************/
t_eReturnCode FMKIO_Set_OutPwmSigCfg(t_eFMKIO_OutPwmSig       f_signal_e, 
                                     t_eFMKIO_PullMode        f_pull_e,
                                     t_uint32                 f_frequency_u32,
                                     t_eFMKTIM_PwmMode        f_PwmMode_e,
                                     t_cbFMKIO_PulseEvent     * f_pulseEvnt_pcb,
                                     t_cbFMKIO_SigErrorMngmt  * f_sigErr_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKIO_GpioPort gpioPort_e = FMKIO_GPIO_PORT_NB;
    t_eFMKTIM_InterruptLineIO ITLineIO_e;

    if (f_signal_e >= FMKIO_OUTPUT_SIGPWM_NB 
    || f_pull_e >= FMKIO_PULL_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_OutPwmSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        ITLineIO_e = c_OutPwmSigBspMap_as[f_signal_e].ITLine_e;    

        Ret_e = FMKTIM_Set_PWMLineCfg(  ITLineIO_e, 
                                        f_frequency_u32,
                                        f_PwmMode_e,
                                        s_FMKIO_MngSigPwm);
        
        if (Ret_e == RC_OK)
        {
            gpioPort_e = c_OutPwmSigBspMap_as[f_signal_e].BasicCfg_s.HwGpio_e;
            Ret_e = s_FMKIO_Set_BspSigCfg(gpioPort_e,
                                      c_OutPwmSigBspMap_as[f_signal_e].BasicCfg_s.HwPin_e,
                                      (t_uint32)GPIO_MODE_AF_PP,
                                      f_pull_e,
                                      FMKIO_SPD_MODE_LOW, // irrevelent for a input sig dig
                                      c_OutPwmSigBspMap_as[f_signal_e].BspAlternateFunc_u8);
            
            if (Ret_e == RC_OK)
            { 
                // update info
                g_OutPwmSigInfo_as[f_signal_e].IsSigConfigured_b = (t_bool)True;
                g_OutPwmSigInfo_as[f_signal_e].sigError_cb = f_sigErr_cb;
                g_OutPwmSigInfo_as[f_signal_e].pulseEvnt_pcb = f_pulseEvnt_pcb;
                g_OutPwmSigInfo_as[f_signal_e].frequencyApplied_u32 = (t_uint32)f_frequency_u32;
            }
        }
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Set_OutDigSigCfg
 *********************************/
t_eReturnCode FMKIO_Set_OutDigSigCfg(t_eFMKIO_OutDigSig f_signal_e,
                                      t_eFMKIO_PullMode f_pull_e,
                                      t_eFMKIO_SpdMode f_spd_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKIO_GpioPort gpioPort_e;

    if ((f_signal_e >= FMKIO_OUTPUT_SIGDIG_NB )
    ||  (f_pull_e >= FMKIO_PULL_MODE_NB) 
    ||  (f_spd_e >= FMKIO_SPD_MODE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_OutDigSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        gpioPort_e = c_OutDigSigBspMap_as[f_signal_e].HwGpio_e;

        Ret_e = s_FMKIO_Set_BspSigCfg(gpioPort_e,
                                      c_OutDigSigBspMap_as[f_signal_e].HwPin_e,
                                      (t_uint32)GPIO_MODE_OUTPUT_PP,
                                      f_pull_e,
                                      f_spd_e,
                                      FMKIO_AF_UNUSED);
        if (Ret_e == RC_OK)
        {
            g_OutDigSigInfo_as[f_signal_e].IsSigConfigured_b = (t_bool)True;
        }
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Set_ComCanCfg
 *********************************/
t_eReturnCode FMKIO_Set_ComCanCfg(t_eFMKIO_ComSigCan f_SigCan_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sFMKIO_RxTxComCfg *bspSigCanCfg_ps;

    if(f_SigCan_e >= FMKIO_COM_SIGNAL_CAN_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }

    if(g_IsIOComCanConfigured_ab[f_SigCan_e] == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    
    if(Ret_e == RC_OK)
    {
        //---------------Set Tx Configuration---------------//
        bspSigCanCfg_ps = (t_sFMKIO_RxTxComCfg *)&c_FmkIo_CanSigCfg_as[f_SigCan_e];

        Ret_e = s_FMKIO_Set_BspSigCfg(bspSigCanCfg_ps->TxPin_s.HwGpio_e,
                                      bspSigCanCfg_ps->TxPin_s.HwPin_e,
                                      GPIO_MODE_AF_PP,
                                      FMKIO_PULL_MODE_DISABLE,
                                      FMKIO_SPD_MODE_HIGH,
                                      bspSigCanCfg_ps->BspAlternateFunc_u8);

        if(Ret_e == RC_OK)
        {
            //---------------Set Rx Configuration---------------//
            Ret_e = s_FMKIO_Set_BspSigCfg(bspSigCanCfg_ps->RxPin_s.HwGpio_e,
                                      bspSigCanCfg_ps->RxPin_s.HwPin_e,
                                      GPIO_MODE_AF_PP,
                                      FMKIO_PULL_MODE_DISABLE,
                                      FMKIO_SPD_MODE_HIGH,
                                      bspSigCanCfg_ps->BspAlternateFunc_u8);
        }
    }

    return Ret_e;
}

/*********************************
 * FMKIO_Set_ComCanCfg
 *********************************/
t_eReturnCode FMKIO_Set_ComSerialCfg(t_eFMKIO_ComSigSerial f_SigSerial_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sFMKIO_RxTxComCfg *bspSigSerialCfg_ps;

    if(f_SigSerial_e >= FMKIO_COM_SIGNAL_SERIAL_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }

    if( g_IsIOComSerialConConfigured_ab[f_SigSerial_e] == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    
    if(Ret_e == RC_OK)
    {
        //---------------Set Tx Configuration---------------//
        bspSigSerialCfg_ps = (t_sFMKIO_RxTxComCfg *)&c_FmkIo_SerialSigCfg_as[f_SigSerial_e];

        Ret_e = s_FMKIO_Set_BspSigCfg(bspSigSerialCfg_ps->TxPin_s.HwGpio_e,
                                      bspSigSerialCfg_ps->TxPin_s.HwPin_e,
                                      GPIO_MODE_AF_PP,
                                      FMKIO_PULL_MODE_DISABLE,
                                      FMKIO_SPD_MODE_LOW,
                                      bspSigSerialCfg_ps->BspAlternateFunc_u8);

        if(Ret_e == RC_OK)
        {
            //---------------Set Rx Configuration---------------//
            Ret_e = s_FMKIO_Set_BspSigCfg(bspSigSerialCfg_ps->RxPin_s.HwGpio_e,
                                      bspSigSerialCfg_ps->RxPin_s.HwPin_e,
                                      GPIO_MODE_AF_PP,
                                      FMKIO_PULL_MODE_DISABLE,
                                      FMKIO_SPD_MODE_LOW,
                                      bspSigSerialCfg_ps->BspAlternateFunc_u8);
        }
    }

    return Ret_e;
}
/*********************************
 * FMKIO_Set_OutDigSigValue
 *********************************/
t_eReturnCode FMKIO_Set_OutDigSigValue(t_eFMKIO_OutDigSig f_signal_e, t_eFMKIO_DigValue f_value_e)
{
    t_eReturnCode Ret_e = RC_OK;
    GPIO_TypeDef *bspGpio_ps = (GPIO_TypeDef *)NULL;
    GPIO_PinState bspSigValue_e;

    if (f_signal_e >= FMKIO_OUTPUT_SIGDIG_NB || f_value_e >= FMKIO_DIG_VALUE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_OutDigSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = FMKIO_Get_BspGpioPort(c_OutDigSigBspMap_as[f_signal_e].HwGpio_e, &bspGpio_ps);
        if (Ret_e == RC_OK)
        {
            switch (f_value_e)
            {
            case FMKIO_DIG_VALUE_LOW:
                bspSigValue_e = GPIO_PIN_RESET;
                break;
            case FMKIO_DIG_VALUE_HIGH:
                bspSigValue_e = GPIO_PIN_SET;
                break;
            case FMKIO_DIG_VALUE_NB:
            default:
                Ret_e = RC_WARNING_WRONG_RESULT;
                break;
            }
            if (Ret_e == RC_OK)
            {
                HAL_GPIO_WritePin(bspGpio_ps,
                                  c_BspPinMapping_ua16[c_OutDigSigBspMap_as[f_signal_e].HwPin_e],
                                  bspSigValue_e);
            }
        }
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Set_OutPwmSigDutyCycle
 *********************************/
t_eReturnCode FMKIO_Set_OutPwmSigDutyCycle(t_eFMKIO_OutPwmSig f_signal_e, t_uint16 f_dutyCycle_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uFMKTIM_ITLineOpe pwmOpe_u;
    t_eFMKTIM_InterruptLineIO ITLineIO_e;
    t_uint8 maskUpdate_u8 = (t_uint8)0;

    if (f_signal_e >= FMKIO_OUTPUT_SIGPWM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_OutPwmSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        ITLineIO_e = c_OutPwmSigBspMap_as[f_signal_e].ITLine_e;
        pwmOpe_u.PwmOpe_s.dutyCycle_u16 = f_dutyCycle_u16;
        SETBIT_8B(maskUpdate_u8, FMKTIM_BIT_PWM_DUTYCYCLE);

        Ret_e = FMKTIM_Set_InterruptLineOpe(FMKTIM_INTERRUPT_LINE_TYPE_IO,
                                            (t_uint8)ITLineIO_e,
                                            pwmOpe_u,
                                            maskUpdate_u8);
        if(Ret_e == RC_OK)
        {
            g_OutPwmSigInfo_as[f_signal_e].dutyCycleApplied_u16 = f_dutyCycle_u16;
        }
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Set_OutPwmSigFrequency
 *********************************/
t_eReturnCode FMKIO_Set_OutPwmSigFrequency(t_eFMKIO_OutPwmSig f_signal_e, t_uint32 f_frequency_u32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uFMKTIM_ITLineOpe pwmOpe_u;
    t_eFMKTIM_InterruptLineIO ITLineIO_e;
    t_uint8 maskUpdate_u8 = (t_uint8)0;

    if (f_signal_e >= FMKIO_OUTPUT_SIGPWM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_OutPwmSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(g_OutPwmSigInfo_as[f_signal_e].frequencyApplied_u32 == f_frequency_u32)
    {
        Ret_e = RC_WARNING_NO_OPERATION;
    }

    if (Ret_e == RC_OK)
    {
        ITLineIO_e = c_OutPwmSigBspMap_as[f_signal_e].ITLine_e;
        pwmOpe_u.PwmOpe_s.frequency_u32 = f_frequency_u32;
        pwmOpe_u.PwmOpe_s.dutyCycle_u16 = g_OutPwmSigInfo_as[f_signal_e].dutyCycleApplied_u16;
        SETBIT_8B(maskUpdate_u8, FMKTIM_BIT_PWM_DUTYCYCLE);
        SETBIT_8B(maskUpdate_u8, FMKTIM_BIT_PWM_FREQUENCY);

        Ret_e = FMKTIM_Set_InterruptLineOpe(FMKTIM_INTERRUPT_LINE_TYPE_IO,
                                            (t_uint8)ITLineIO_e,
                                            pwmOpe_u,
                                            maskUpdate_u8);
    }
    if(Ret_e == RC_WARNING_NO_OPERATION)
    {
        Ret_e = RC_OK;
    }

    return Ret_e;
}

/*********************************
 * FMKIO_Set_OutPwmSigPulses
 *********************************/
t_eReturnCode FMKIO_Set_OutPwmSigPulses(t_eFMKIO_OutPwmSig f_signal_e, 
                                        t_uint16 f_dutyCycle_u16,
                                        t_uint16 f_pulses_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uFMKTIM_ITLineOpe pwmOpe_u;
    t_eFMKTIM_InterruptLineIO ITLineIO_e;
    t_uint8 maskUpdate_u8 = (t_uint8)0; 

    if ((f_signal_e >= FMKIO_OUTPUT_SIGPWM_NB)
    ||  (f_dutyCycle_u16 > FMKTIM_PWM_MAX_DUTY_CYLCE)
    ||  (f_pulses_u16 > (t_uint16)0xFFFF))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_OutPwmSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        ITLineIO_e = c_OutPwmSigBspMap_as[f_signal_e].ITLine_e;
        pwmOpe_u.PwmOpe_s.nbPulses_u16 = f_pulses_u16;

        SETBIT_8B(maskUpdate_u8, FMKTIM_BIT_PWM_NB_PULSES);

        if(g_OutPwmSigInfo_as[f_signal_e].dutyCycleApplied_u16 != f_dutyCycle_u16)
        {
            pwmOpe_u.PwmOpe_s.dutyCycle_u16 = f_dutyCycle_u16;
            SETBIT_8B(maskUpdate_u8, FMKTIM_BIT_PWM_DUTYCYCLE);
        }
        

        Ret_e = FMKTIM_Set_InterruptLineOpe(FMKTIM_INTERRUPT_LINE_TYPE_IO,
                                            (t_uint8)ITLineIO_e,
                                            pwmOpe_u,
                                            maskUpdate_u8);

        if(Ret_e == RC_OK)
        {
            g_OutPwmSigInfo_as[f_signal_e].dutyCycleApplied_u16 = f_dutyCycle_u16;
        }
    }

    return Ret_e;
}

/*********************************
 * FMKIO_Get_OutPwmSigFrequency
 *********************************/
t_eReturnCode FMKIO_Get_OutPwmSigFrequency(t_eFMKIO_OutPwmSig f_signal_e, t_uint32 * f_frequency_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uFMKTIM_ITLineValue pwmValue_u;
    t_eFMKTIM_InterruptLineIO ITLineIO_e;
    t_uint8 maskValue_u8 = (t_uint8)0; 

    if (f_signal_e >= FMKIO_OUTPUT_SIGPWM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_OutPwmSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        ITLineIO_e = c_OutPwmSigBspMap_as[f_signal_e].ITLine_e;
        SETBIT_8B(maskValue_u8, FMKTIM_BIT_PWM_FREQUENCY);

        Ret_e = FMKTIM_Get_InterruptLineValue(  FMKTIM_INTERRUPT_LINE_TYPE_IO,
                                                ITLineIO_e,
                                                &pwmValue_u,
                                                maskValue_u8);

        if(Ret_e == RC_OK)
        {
            *f_frequency_pu32 = (t_uint32)pwmValue_u.PwmValue_s.frequency_u32;
        }
        else if (Ret_e == RC_WARNING_BUSY)
        {
            *f_frequency_pu32 = (t_uint32)0;
            //----- don't block the application, busy 'cause it line son't start yet -----//
            Ret_e = RC_OK;
        }
    }

    return Ret_e;
}

/*********************************
 * FMKIO_Get_OutPwmSigDutyCycle
 *********************************/
t_eReturnCode FMKIO_Get_OutPwmSigDutyCycle(t_eFMKIO_OutPwmSig f_signal_e, t_uint16 * f_dutyCycle_pu16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uFMKTIM_ITLineValue pwmValue_u;
    t_eFMKTIM_InterruptLineIO ITLineIO_e;
    t_uint8 maskValue_u8 = (t_uint8)0; 

    if (f_signal_e >= FMKIO_OUTPUT_SIGPWM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_OutPwmSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        ITLineIO_e = c_OutPwmSigBspMap_as[f_signal_e].ITLine_e;
        SETBIT_8B(maskValue_u8, FMKTIM_BIT_PWM_DUTYCYCLE);

        Ret_e = FMKTIM_Get_InterruptLineValue(  FMKTIM_INTERRUPT_LINE_TYPE_IO,
                                                ITLineIO_e,
                                                &pwmValue_u,
                                                maskValue_u8);

        if(Ret_e == RC_OK)
        {
            *f_dutyCycle_pu16 = (t_uint16)pwmValue_u.PwmValue_s.dutyCycle_u16;
        }
        else if (Ret_e == RC_WARNING_BUSY)
        {
            *f_dutyCycle_pu16 = (t_uint32)0;
            //----- don't block the application, busy 'cause it line son't start yet -----//
            Ret_e = RC_OK;
        }
    }

    return Ret_e;
}

/*********************************
 * FMKIO_Get_InDigSigValue
 *********************************/
t_eReturnCode FMKIO_Get_InEcdrPositionValue(t_eFMKIO_InEcdrSignals f_signal_e, t_uint32 *f_value_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uFMKTIM_ITLineValue ecdrValue_u;
    t_eFMKTIM_InterruptLineIO ITLineIO_e;
    t_uint8 maskValue_u8 = (t_uint8)0;

    if(f_signal_e >= FMKIO_INPUT_ENCODER_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_InEcdrSigInfo_as[f_signal_e].EcdrOpe == FMKIO_ENCODER_START_DIR)
    {
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    if(g_InEcdrSigInfo_as[f_signal_e].isEcdrConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }
    if(g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(f_value_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        maskValue_u8 = (t_uint8)0;
        SETBIT_8B(maskValue_u8, FMKTIM_BIT_ECDR_POSTION);
        ITLineIO_e = c_FmkIo_InEcdrSigBspCfg_as[f_signal_e].ITLine_e;

        Ret_e = FMKTIM_Get_InterruptLineValue(  FMKTIM_INTERRUPT_LINE_TYPE_IO,
                                                ITLineIO_e,
                                                &ecdrValue_u,
                                                maskValue_u8);
        if(Ret_e == RC_OK)
        {
            *f_value_pu32 = (t_uint32)ecdrValue_u.EncoderValue_s.position_u32;
        }
        else
        {
            *f_value_pu32 = (t_uint32)0;
        }
    }

    return Ret_e;
}

/*********************************
 * FMKIO_Get_InDigSigValue
 *********************************/
t_eReturnCode FMKIO_Get_InEcdrDirectionValue(t_eFMKIO_InEcdrSignals f_signal_e, t_eFMKIO_EcdrDir *f_Dirvalue_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uFMKTIM_ITLineValue ecdrValue_u;
    t_eFMKTIM_InterruptLineIO ITLineIO_e;
    t_eFMKIO_EcdrDir direction_e;
    t_uint8 maskvalue_u8 = (t_uint8)0;

    if(f_signal_e >= FMKIO_INPUT_ENCODER_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_InEcdrSigInfo_as[f_signal_e].EcdrOpe == FMKIO_ENCODER_START_POS)
    {
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    if(g_InEcdrSigInfo_as[f_signal_e].isEcdrConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }
    if(g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(f_Dirvalue_pe == (t_eFMKIO_EcdrDir *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        SETBIT_8B(maskvalue_u8, FMKTIM_BIT_ECDR_DIRECTION);
        ITLineIO_e = c_FmkIo_InEcdrSigBspCfg_as[f_signal_e].ITLine_e;

        Ret_e = FMKTIM_Get_InterruptLineValue(  FMKTIM_INTERRUPT_LINE_TYPE_IO,
                                                ITLineIO_e,
                                                &ecdrValue_u,
                                                maskvalue_u8);
        if(Ret_e == RC_OK)
        {
            switch(ecdrValue_u.EncoderValue_s.direction_u8)
            {
                case 0:
                    direction_e = FMKIO_ENCODER_DIR_BACKWARD;
                    break;
                case 1:
                    direction_e = FMKIO_ENCODER_DIR_BACKWARD;
                    break;
                default: 
                    Ret_e = RC_WARNING_NO_OPERATION;
                    break;
            }

            *f_Dirvalue_pe = direction_e;
        }
    }

    return Ret_e;
}
/*********************************
 * FMKIO_Get_InDigSigValue
 *********************************/
t_eReturnCode FMKIO_Get_InDigSigValue(t_eFMKIO_InDigSig f_signal_e, t_eFMKIO_DigValue *f_value_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    GPIO_TypeDef *bspGpio_ps = (GPIO_TypeDef *)NULL;
    GPIO_PinState bspSigValue_e;

    if (f_signal_e >= FMKIO_INPUT_SIGDIG_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_value_pe == (t_eFMKIO_DigValue *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_InDigSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = FMKIO_Get_BspGpioPort(c_InDigSigBspMap_as[f_signal_e].HwGpio_e, &bspGpio_ps);
        if (Ret_e == RC_OK)
        {
            bspSigValue_e = HAL_GPIO_ReadPin(bspGpio_ps, c_BspPinMapping_ua16[c_InDigSigBspMap_as[f_signal_e].HwPin_e]);
             switch (bspSigValue_e)
            {
            case GPIO_PIN_RESET:
                *f_value_pe = FMKIO_DIG_VALUE_LOW;
                break;
            case GPIO_PIN_SET:
                *f_value_pe = FMKIO_DIG_VALUE_HIGH;
                break;
            default:
                *f_value_pe = FMKIO_DIG_VALUE_LOW;
                Ret_e = RC_WARNING_WRONG_RESULT;
                break;
            }
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKIO_Get_BspPullMode
 *********************************/
t_eReturnCode FMKIO_Get_InAnaSigValue(t_eFMKIO_InAnaSig f_signal_e, t_uint16 *f_value_pu16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint16 anaValue_16 = 0;

    if (f_signal_e >= FMKIO_INPUT_SIGANA_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_value_pu16 == (t_uint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_InAnaSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = FMKCDA_Get_AnaChannelMeasure(c_InAnaSigBspMap_as[f_signal_e].adc_e,
                                             c_InAnaSigBspMap_as[f_signal_e].adcChannel_e,
                                             &anaValue_16);
        if(Ret_e == RC_OK)
        {
            *f_value_pu16 = (t_uint16)anaValue_16;
        }
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Get_InFreqSigValue
 *********************************/
t_eReturnCode FMKIO_Get_InFreqSigValue(t_eFMKIO_InFreqSig f_signal_e, t_uint32 *f_value_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 value_f32 = 0;
    t_uint32 arrTim_u32 = 0;

    if (f_signal_e >= FMKIO_INPUT_SIGFREQ_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_InFreqSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if (f_value_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        if((g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
        || g_InFreqSigInfo_as[f_signal_e].isSigCalib_b == (t_bool)False)
        {
            Ret_e = RC_WARNING_BUSY;
        }
    }
    if (Ret_e == RC_OK)
    {
        // if flag writing value is False, make calcul on value, else make calcul on saved value
        if( g_InFreqSigInfo_as[f_signal_e].FlagValueWriting_b == (t_bool)False)
        {
            value_f32 = (t_float32)g_InFreqSigInfo_as[f_signal_e].value_u32;
        }
        else
        {
            value_f32 = (t_float32)g_InFreqSigInfo_as[f_signal_e].savedValue_32;
            Ret_e = RC_WARNING_BUSY;
        }

        arrTim_u32 = g_InFreqSigInfo_as[f_signal_e].TimARRValue_u32;

        switch(g_InFreqSigInfo_as[f_signal_e].meas_e)
        {
            case FMKIO_FREQ_MEAS_COUNT:
                *f_value_pu32 = (t_uint32)value_f32;
                g_InFreqSigInfo_as[f_signal_e].value_u32 = (t_uint32)0;
                g_InFreqSigInfo_as[f_signal_e].savedValue_32 = (t_uint32)0;
                break;

            case FMKIO_FREQ_MEAS_PERIOD:
                if(arrTim_u32 > (t_uint32)0)
                {
                    *f_value_pu32 = (t_uint32)((t_float32)((t_float32)2 * value_f32) / (t_float32)arrTim_u32);
                }
                else 
                {
                    *f_value_pu32 = 0;
                    Ret_e = RC_WARNING_NOT_ALLOWED;
                }
                break;

            case FMKIO_FREQ_MEAS_FREQ:
                if(value_f32 > (t_float32)0.0f)
                {
                    *f_value_pu32 = (t_uint32)((t_float32)arrTim_u32 / (t_float32)((t_float32)2 * value_f32));
                }
                else    
                {
                    *f_value_pu32 = 0;
                    Ret_e = RC_WARNING_NOT_ALLOWED;
                }
                
                break;
            case FMKIO_FREQ_MEAS_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Get_OutDigSigValue
 *********************************/
t_eReturnCode FMKIO_Get_OutDigSigValue(t_eFMKIO_OutDigSig f_signal_e, t_eFMKIO_DigValue *f_value_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    GPIO_TypeDef *bspGpio_ps = (GPIO_TypeDef *)NULL;
    GPIO_PinState bspSigValue_e;

    if (f_signal_e >= FMKIO_OUTPUT_SIGDIG_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_value_pe == (t_eFMKIO_DigValue *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_OutDigSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_FmkIO_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = FMKIO_Get_BspGpioPort(c_OutDigSigBspMap_as[f_signal_e].HwGpio_e, &bspGpio_ps);
        if (Ret_e == RC_OK)
        {
            bspSigValue_e = HAL_GPIO_ReadPin(bspGpio_ps, c_BspPinMapping_ua16[c_OutDigSigBspMap_as[f_signal_e].HwPin_e]);
            switch (bspSigValue_e)
            {
            case GPIO_PIN_RESET:
                *f_value_pe = FMKIO_DIG_VALUE_LOW;
                break;
            case GPIO_PIN_SET:
                *f_value_pe = FMKIO_DIG_VALUE_HIGH;
                break;
            default:
                *f_value_pe = FMKIO_DIG_VALUE_LOW;
                Ret_e = RC_WARNING_WRONG_RESULT;
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
 * s_FMKIO_PreOperational
 *********************************/
static t_eReturnCode s_FMKIO_PreOperational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxSigFreq_u8 = 0;
    t_uint8 idxEcdr_u8 = 0;
    t_eFMKTIM_InterruptLineIO IOLine_e;
    t_eFMKTIM_EcdrOpe EncoderTimerOpe_e;
    t_uFMKTIM_ITLineOpe LineOpe_u;
    t_uFMKTIM_ITLineValue LineValue_u;
    t_uint8 maskUpdate_u8 = (t_uint8)0;

    //----- Start Frequency Measurement -----//
    for(idxSigFreq_u8 = (t_uint8)0 ;
        (idxSigFreq_u8 < FMKIO_INPUT_SIGFREQ_NB)
    &&  (g_InFreqSigInfo_as[idxSigFreq_u8].IsSigConfigured_b == (t_bool)True)
    &&  (Ret_e == RC_OK); 
        idxSigFreq_u8++)
    {
        SETBIT_8B(maskUpdate_u8, FMKTIM_BIT_IC_STATE);
        LineOpe_u.ICOpe_s.IcState_e = FMKTIM_IC_STATE_ENABLE;
        IOLine_e = c_InFreqSigBspMap_as[idxSigFreq_u8].ITLine_e;
        Ret_e = FMKTIM_Set_InterruptLineOpe(    FMKTIM_INTERRUPT_LINE_TYPE_IO,
                                                (t_uint8)IOLine_e,
                                                LineOpe_u,
                                                maskUpdate_u8);

        //---- get ARR &Frequency value to calculate the input frequency -----//
        maskUpdate_u8 = (t_uint8)0;
        SETBIT_8B(maskUpdate_u8, FMKTIM_BIT_IC_ARR_REGISTER);
        SETBIT_8B(maskUpdate_u8, FMKTIM_BIT_IC_FREQUENCY);

        Ret_e = FMKTIM_Get_InterruptLineValue(  FMKTIM_INTERRUPT_LINE_TYPE_IO,
                                                (t_uint8)IOLine_e,
                                                &LineValue_u,
                                                maskUpdate_u8);

        if(Ret_e == RC_OK)
        {
            g_InFreqSigInfo_as[idxSigFreq_u8].TimARRValue_u32 = LineValue_u.ICValue_s.ARR_Register_u32;
            g_InFreqSigInfo_as[idxSigFreq_u8].TimFreqValue_u32 = LineValue_u.ICValue_s.frequency_u32;
        }
    }

    //----- Start Encoder Measurement -----//
    for(idxEcdr_u8 = (t_uint8)0 ;
        (idxEcdr_u8 < FMKIO_INPUT_ENCODER_NB)
    &&  (g_InEcdrSigInfo_as[idxEcdr_u8].isEcdrConfigured_b == (t_bool)True)
    &&  (Ret_e == RC_OK); 
        idxEcdr_u8++)
    {
        Ret_e = s_FMKIO_Get_EcdrTimerMode(g_InEcdrSigInfo_as[idxEcdr_u8].EcdrOpe,
                                          &EncoderTimerOpe_e);
        if(Ret_e == RC_OK)
        {
            maskUpdate_u8 = (t_uint8)0;
            IOLine_e = c_FmkIo_InEcdrSigBspCfg_as[idxEcdr_u8].ITLine_e;
            LineOpe_u.EncoderOpe_e = EncoderTimerOpe_e;
            Ret_e = FMKTIM_Set_InterruptLineOpe(  FMKTIM_INTERRUPT_LINE_TYPE_IO,
                                                    (t_uint8)IOLine_e,
                                                    LineOpe_u,
                                                    maskUpdate_u8);
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKIO_Operational
 *********************************/
static t_eReturnCode s_FMKIO_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_uint32 s_SavedTime_u32 = 0;
    static t_bool s_performFreqLogic_b = False;
    t_uint32 currentTime_u32 = 0;
    t_uint8 idxFreq_u8;
    t_uint32 multiplierFreq_u32;
    t_eFMKTIM_InterruptLineIO freqLine_e;
    t_uFMKTIM_ITLineOpe freqOpe_u;
    t_uint8 maskOpe_u8 = (t_uint8)0;

    FMKCPU_Get_Tick(&currentTime_u32);
    if((currentTime_u32 - s_SavedTime_u32) > (t_uint32)FMKIO_TIME_BTWN_DIAG_MS)
    {//perform diag on timer / chnl used
        s_SavedTime_u32 = currentTime_u32;
        Ret_e = s_FMKIO_PerformDiagnostic();
    }
    if(s_performFreqLogic_b == (t_bool)False)
    {
        for(idxFreq_u8 = (t_uint8)0 ; idxFreq_u8 < FMKIO_INPUT_SIGFREQ_NB ; idxFreq_u8 ++)
        {
            if(g_InFreqSigInfo_as[idxFreq_u8].IsSigConfigured_b == (t_bool)True)
            {
                s_performFreqLogic_b = (t_bool)True;
                //---- check frequency Input Compare validity -----//
                switch (g_InFreqSigInfo_as[idxFreq_u8].meas_e)
                {
                    case FMKIO_FREQ_MEAS_FREQ:
                    case FMKIO_FREQ_MEAS_PERIOD:
                    {
                        if((g_InFreqSigInfo_as[idxFreq_u8].value_u32 < (t_uint32)FMKIO_FREQ_MIN_CC_VALUE)
                        && (g_InFreqSigInfo_as[idxFreq_u8].value_u32 > (t_uint32)0))
                        {
                            multiplierFreq_u32 = (t_uint32)((t_float32)(FMKIO_FREQ_MIN_CC_VALUE / 
                                                                (t_float32)g_InFreqSigInfo_as[idxFreq_u8].value_u32));

                            if(multiplierFreq_u32 < (t_uint32)2)
                            {
                                multiplierFreq_u32 = (t_uint32)2;
                            }
                            //----- Set Information for frequency -----//
                            freqLine_e = c_InFreqSigBspMap_as[idxFreq_u8].ITLine_e;
                            SETBIT_8B(maskOpe_u8, FMKTIM_BIT_IC_FREQUENCY);

                            freqOpe_u.ICOpe_s.frequency_u32 = (t_uint32)(g_InFreqSigInfo_as[idxFreq_u8].TimFreqValue_u32 *
                                                                    multiplierFreq_u32);
                            //---- Set new frequency ----//
                            Ret_e = FMKTIM_Set_InterruptLineOpe(FMKTIM_INTERRUPT_LINE_TYPE_IO,
                                                                freqLine_e,
                                                                freqOpe_u,
                                                                maskOpe_u8);
                            if(Ret_e == RC_OK)
                            {
                                g_InFreqSigInfo_as[idxFreq_u8].TimFreqValue_u32 = freqOpe_u.ICOpe_s.frequency_u32;
                            }
                        }
                        else 
                        {
                            if(g_InFreqSigInfo_as[idxFreq_u8].isSigCalib_b == (t_bool)False)
                            {
                                g_InFreqSigInfo_as[idxFreq_u8].isSigCalib_b = (t_bool)True;
                            }   
                        }
                    }
                    case FMKIO_FREQ_MEAS_COUNT:
                    {
                        if(g_InFreqSigInfo_as[idxFreq_u8].isSigCalib_b == (t_bool)False)
                        {
                            g_InFreqSigInfo_as[idxFreq_u8].isSigCalib_b = (t_bool)True;
                        }
                        break;
                    }
                    case FMKIO_FREQ_MEAS_NB:
                    default:
                    {
                        Ret_e = RC_WARNING_NO_OPERATION;
                    }
                }
            }
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKIO_PerformDiagnostic
 *********************************/
static t_eReturnCode s_FMKIO_PerformDiagnostic(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LLI_u8;
    t_uint16 cpuChnlStatus_u16;
    t_uint16 adcChnlStatus_u16;
    t_uint8 ITLineVal_u8;
    t_eFMKTIM_InterruptLineType ITLineType_e;

    //------perform diag for PWM signal configuration------//
    for(LLI_u8 = (t_uint8)0 ; (LLI_u8 < FMKIO_OUTPUT_SIGPWM_NB) ; LLI_u8++)
    {
        if(g_OutPwmSigInfo_as[LLI_u8].IsSigConfigured_b == (t_bool)True)
        {

            //------update Information------//
           ITLineVal_u8 = (t_uint8)c_OutPwmSigBspMap_as[LLI_u8].ITLine_e;
            ITLineType_e = FMKTIM_INTERRUPT_LINE_TYPE_IO;
            //------Get Error Status------//
            Ret_e = FMKTIM_Get_LineErrorStatus(ITLineType_e, 
                                                  ITLineVal_u8,
                                                  &cpuChnlStatus_u16);
            if((Ret_e == RC_OK)
            && (GETBIT(cpuChnlStatus_u16, FMKTIM_ERRSTATE_OK) != BIT_IS_SET_16B)
            && (g_OutPwmSigInfo_as[LLI_u8].sigError_cb != (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION))
            {
                g_OutPwmSigInfo_as[LLI_u8].sigError_cb( FMKIO_SIGTYPE_OUTPUT_PWM, 
                                                        LLI_u8,
                                                        cpuChnlStatus_u16, 
                                                        0);
            }
        }
    }
    // perform diag for Freqency signal configuration 
    for(LLI_u8 = (t_uint8)0 ; (LLI_u8 < FMKIO_INPUT_SIGFREQ_NB) ; LLI_u8++)
    {
        if(g_InFreqSigInfo_as[LLI_u8].IsSigConfigured_b == (t_bool)True)
        {
            //------update Information------//
            ITLineVal_u8 = (t_uint8)c_InFreqSigBspMap_as[LLI_u8].ITLine_e;
            ITLineType_e = FMKTIM_INTERRUPT_LINE_TYPE_IO;
            //------Get Error Status------//
            Ret_e = FMKTIM_Get_LineErrorStatus(  ITLineType_e, 
                                                    ITLineVal_u8,
                                                    &cpuChnlStatus_u16);

            if((Ret_e == RC_OK)
            && (GETBIT(cpuChnlStatus_u16, FMKTIM_ERRSTATE_OK) !=  BIT_IS_SET_16B)
            && (g_InFreqSigInfo_as[LLI_u8].sigError_cb != (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION))
            {
                g_InFreqSigInfo_as[LLI_u8].sigError_cb( FMKIO_SIGTYPE_INPUT_FREQ,
                                                        LLI_u8,
                                                        cpuChnlStatus_u16,
                                                        0);
            }
        }
    } 
    //------perform diag for Analog signal configuration ------//
    for(LLI_u8 = (t_uint8)0 ; (LLI_u8 < FMKIO_INPUT_SIGANA_NB) ; LLI_u8++)
    {
        if(g_InAnaSigInfo_as[LLI_u8].IsSigConfigured_b == (t_bool)True)
        {
            Ret_e = FMKCDA_Get_AdcError(    c_InAnaSigBspMap_as[LLI_u8].adc_e,
                                            &adcChnlStatus_u16);

            if((Ret_e == RC_OK)
            && (GETBIT(adcChnlStatus_u16, FMKCDA_ERRSTATE_OK) == BIT_IS_RESET_16B)
            && (g_InAnaSigInfo_as[LLI_u8].sigError_cb != (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION))
            {
                g_InAnaSigInfo_as[LLI_u8].sigError_cb(  FMKIO_SIGTYPE_INPUT_ANA,
                                                        LLI_u8,
                                                        adcChnlStatus_u16,
                                                        0);
            }
        }
    }
    
    return Ret_e;
}

/*********************************
 * s_FMKIO_Get_EcdrTimerMode
 *********************************/
static t_eReturnCode s_FMKIO_Get_EcdrTimerMode(t_eFMKIO_EcdrStartOpe f_StartOpeMode_e, t_eFMKTIM_EcdrOpe * f_EdrTimerOpe_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_StartOpeMode_e >= FMKIO_ENCODER_START_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_EdrTimerOpe_pe == (t_eFMKTIM_EcdrOpe *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_StartOpeMode_e)
        {
            case FMKIO_ENCODER_START_POS:
                *f_EdrTimerOpe_pe = FMKTIM_ECDR_OPE_START_TI1;
                break;
            case FMKIO_ENCODER_START_DIR:
                *f_EdrTimerOpe_pe = FMKTIM_ECDR_OPE_START_TI2;
                break;
            case FMKIO_ENCODER_START_BOTH:
                *f_EdrTimerOpe_pe = FMKTIM_ECDR_OPE_START_BOTH;
                break;
            case FMKIO_ENCODER_START_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }   

    return Ret_e;
}

/*********************************
 * s_FMKIO_MngSigFrequency
 *********************************/
static t_eReturnCode s_FMKIO_MngSigFrequency(t_eFMKTIM_InterruptLineType f_InterruptType_e, t_uint8 f_InterruptLine_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uFMKTIM_ITLineValue IcLine_u;
    t_uint32 currentCapture_u32 = 0;
    t_uint32 lastCapture_u32 = 0;
    t_uint32 captureDifference_u32 = 0;
    t_uint8 maskEvnt_u8 = 0;
    t_uint8 LLI_u8 = 0;
    t_eFMKIO_InFreqSig freqSig_e = FMKIO_INPUT_SIGFREQ_NB;
    t_uint8 ItLine_u8;

    if (f_InterruptType_e != FMKTIM_INTERRUPT_LINE_TYPE_IO)
    { 
        Ret_e = RC_ERROR_PARAM_INVALID;
    }

    if (Ret_e == RC_OK)
    {
        //-------------Know which signal made the interruption -------------//
        for (LLI_u8 = (t_uint8)0; LLI_u8 < FMKIO_INPUT_SIGFREQ_NB; LLI_u8++)
        {
            if (f_InterruptLine_u8 == (t_uint8)c_InFreqSigBspMap_as[LLI_u8].ITLine_e)
            {
                freqSig_e = (t_eFMKIO_InFreqSig)LLI_u8;
                break;
            }
        }

        if (freqSig_e != FMKIO_INPUT_SIGFREQ_NB)
        {
            g_InFreqSigInfo_as[freqSig_e].savedValue_32 = g_InFreqSigInfo_as[freqSig_e].value_u32;

            switch (g_InFreqSigInfo_as[freqSig_e].meas_e)
            {
                case FMKIO_FREQ_MEAS_COUNT:
                    g_InFreqSigInfo_as[freqSig_e].value_u32 += (t_uint32)1;
                    break;

                case FMKIO_FREQ_MEAS_PERIOD:
                case FMKIO_FREQ_MEAS_FREQ:
                    //-------------Read value for channel linked to the signal-------------//
                    ItLine_u8 = (t_uint8)f_InterruptLine_u8;
                    SETBIT_8B(maskEvnt_u8, FMKTIM_BIT_IC_CCRX_REGISTER);
                    Ret_e = FMKTIM_Get_InterruptLineValue(  f_InterruptType_e, 
                                                            ItLine_u8,
                                                            &IcLine_u,
                                                            maskEvnt_u8);

                    if (Ret_e == RC_OK)
                    {
                        currentCapture_u32 = IcLine_u.ICValue_s.CCRxRegister_u16;
                        lastCapture_u32 = g_InFreqLastCapture_ua32[freqSig_e];

                        // Check for overflow and calculate capture difference
                        if (IcLine_u.ICValue_s.CCRxRegister_u16 < lastCapture_u32)
                        {
                            // Timer has overflowed, calculate the correct difference
                            //overflowCount_u32 = 1; // Increment overflow count (1 overflow)
                            captureDifference_u32 = ((g_InFreqSigInfo_as[freqSig_e].TimARRValue_u32 
                                                        - lastCapture_u32) + currentCapture_u32 + 1);
                        }
                        else
                        {
                            //overflowCount_u32 = 0; // No overflow
                            captureDifference_u32 = currentCapture_u32 - lastCapture_u32;
                        }

                        //-------------set flag to writing equals true-------------//
                        g_InFreqSigInfo_as[freqSig_e].FlagValueWriting_b = (t_bool)True;

                        //-------------saved difference in freq sig structure, calculation will not be made in interruption-------------//
                        g_InFreqSigInfo_as[freqSig_e].value_u32 = captureDifference_u32;

                        //-------------reset flag-------------//
                        g_InFreqSigInfo_as[freqSig_e].FlagValueWriting_b = (t_bool)False;

                        //-------------saved last capture value-------------//
                        g_InFreqLastCapture_ua32[freqSig_e] = currentCapture_u32;

                        // Optionally: Account for overflow in frequency calculation
                        //g_InFreqSigInfo_as[freqSig_e].overflowCount_u32 = overflowCount_u32; // Store overflow count if needed
                    }
                    break;

                case FMKIO_FREQ_MEAS_NB:
                default:
                    Ret_e = RC_WARNING_NO_OPERATION;
                    break;
            }
        }
        else
        {
            Ret_e = RC_ERROR_LIMIT_REACHED;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKIO_MngSigPwm
 *********************************/
static void s_FMKIO_MngSigPwm(t_eFMKTIM_InterruptLineType f_InterruptType_e, t_uint8 f_InterruptLine_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 LLI_u8= 0;
    t_eFMKIO_OutPwmSig PwmSig_e = FMKIO_OUTPUT_SIGPWM_NB;

    if (f_InterruptType_e != FMKTIM_INTERRUPT_LINE_TYPE_IO)
    { 
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //-------------Know wich signal made the interruption -------------//
        for(LLI_u8 = (t_uint8)0 ; LLI_u8 < FMKIO_OUTPUT_SIGPWM_NB ; LLI_u8++)
        {
            if(f_InterruptLine_u8 == (t_uint8)c_OutPwmSigBspMap_as[LLI_u8].ITLine_e)
            {
                PwmSig_e = (t_eFMKIO_OutPwmSig)LLI_u8;
                break;
            }
        }
        if(PwmSig_e != FMKIO_OUTPUT_SIGPWM_NB)
        {
            if(g_OutPwmSigInfo_as[PwmSig_e].pulseEvnt_pcb != NULL_FONCTION)
            {
                g_OutPwmSigInfo_as[PwmSig_e].pulseEvnt_pcb(PwmSig_e);
            }
        }
    }

    return;
}
/*********************************
 * s_FMKIO_Get_BspPullMode
 *********************************/
static t_eReturnCode s_FMKIO_Get_BspPullMode(t_eFMKIO_PullMode f_pull_e, t_uint32 *f_bspPull_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_pull_e >= FMKIO_PULL_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_bspPull_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_pull_e)
        {
        case FMKIO_PULL_MODE_DISABLE:
            *f_bspPull_pu32 = GPIO_NOPULL;
            break;
        case FMKIO_PULL_MODE_DOWN:
            *f_bspPull_pu32 = GPIO_PULLDOWN;
            break;
        case FMKIO_PULL_MODE_UP:
            *f_bspPull_pu32 = GPIO_PULLUP;
            break;
        case FMKIO_PULL_MODE_NB:
        default:
            Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
            break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKIO_Get_BspPullMode
 *********************************/
static t_eReturnCode s_FMKIO_Get_BspSpdMode(t_eFMKIO_SpdMode f_spd_e, t_uint32 *f_bspSpd_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_spd_e >= FMKIO_SPD_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_bspSpd_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_spd_e)
        {
        case FMKIO_SPD_MODE_LOW:
            *f_bspSpd_pu32 = GPIO_SPEED_FREQ_LOW;
            break;
        case FMKIO_SPD_MODE_MEDIUM:
            *f_bspSpd_pu32 = GPIO_SPEED_FREQ_MEDIUM;
            break;
        case FMKIO_SPD_MODE_HIGH:
            *f_bspSpd_pu32 = GPIO_SPEED_FREQ_HIGH;
            break;
        case FMKIO_SPD_MODE_NB:
        default:
            Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
            break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKIO_Get_BspTriggerMode
 *********************************/
static t_eReturnCode s_FMKIO_Get_BspTriggerMode(t_eFMKIO_SigTrigCptr f_trigger_e, t_uint32 *f_bspTrigger_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_trigger_e >= FMKIO_STC_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_bspTrigger_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_trigger_e)
        {
        case FMKIO_STC_RISING_EDGE:
            *f_bspTrigger_pu32 = GPIO_MODE_IT_RISING;
            break;
        case FMKIO_STC_FALLING_EDGE:
            *f_bspTrigger_pu32 = GPIO_MODE_IT_FALLING;
            break;
        case FMKIO_STC_BOTH_EDGE:
            *f_bspTrigger_pu32 = GPIO_MODE_IT_RISING_FALLING;
            break;
        case FMKIO_STC_NB:
        default:
            Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
            break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKIO_Set_BspSigCfg
 *********************************/
static t_eReturnCode s_FMKIO_Set_BspSigCfg(t_eFMKIO_GpioPort f_gpioPort_e,
                                            t_eFMKIO_BspGpioPin f_pin_e,
                                            t_uint32 f_mode_u32,
                                            t_eFMKIO_PullMode f_pull_e,
                                            t_eFMKIO_SpdMode f_spd_e,
                                            t_uint8 f_AltFunc_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    GPIO_TypeDef *bspGpio_ps = (GPIO_TypeDef *)NULL;
    GPIO_InitTypeDef bspInit_s;
    t_uint32 bspPull_32 = 0;
    t_uint32 bspSpd_u32 = 0;
 
    if ((f_gpioPort_e >= FMKIO_GPIO_PORT_NB)
    ||  (f_pin_e >= FMKIO_GPIO_PIN_NB)
    ||  (f_pull_e >= FMKIO_PULL_MODE_NB)
    ||  (f_spd_e >= FMKIO_SPD_MODE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = FMKIO_Get_BspGpioPort(f_gpioPort_e, &bspGpio_ps);
        if (Ret_e == RC_OK)
        {
            Ret_e = s_FMKIO_Get_BspPullMode(f_pull_e, &bspPull_32);
        }
        if (Ret_e == RC_OK)
        {
            Ret_e = s_FMKIO_Get_BspSpdMode(f_spd_e, &bspSpd_u32);
        }
        if (g_IsGpioClockEnable_ae[f_gpioPort_e] == FMKCPU_CLOCKPORT_OPE_DISABLE)
        {
            Ret_e = s_FMKIO_Set_GpioClkState(f_gpioPort_e, FMKCPU_CLOCKPORT_OPE_ENABLE);
        }
        if (Ret_e == RC_OK)
        {
            bspInit_s.Mode = (t_uint32)f_mode_u32;
            bspInit_s.Pin = (t_uint32)c_BspPinMapping_ua16[f_pin_e];
            bspInit_s.Pull = (t_uint32)bspPull_32;
            bspInit_s.Speed = (t_uint32)bspSpd_u32;
            if (f_AltFunc_u8 != (t_uint8)FMKIO_AF_UNUSED)
            {
                bspInit_s.Alternate = (t_uint32)f_AltFunc_u8;
            }
            HAL_GPIO_Init(bspGpio_ps, &bspInit_s);
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKIO_Set_GpioClkState
 *********************************/
static t_eReturnCode s_FMKIO_Set_GpioClkState(t_eFMKIO_GpioPort f_gpioPort_e, t_eFMKCPU_ClockPortOpe f_ope_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_ClockPort gpioClkPort_e;

    if (f_gpioPort_e >= FMKIO_GPIO_PORT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        //----- Get Rcc Clock For the GPIO Port -----//
        Ret_e = FMKIO_GetGpioRccClock(f_gpioPort_e, &gpioClkPort_e);

        if (Ret_e == RC_OK)
        {
            //----- Enable/Disable HArdware Clock -----//
            Ret_e = FMKCPU_Set_HwClock(gpioClkPort_e, f_ope_e);
        }
        if (Ret_e == RC_OK)
        {
            //----- Update Information -----//
            g_IsGpioClockEnable_ae[f_gpioPort_e] = f_ope_e;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKIO_BspRqst_InterruptMngmt
 *********************************/
static void s_FMKIO_BspRqst_InterruptMngmt(void)
{
    t_uint8 LLI_u8;
    t_eFMKIO_BspGpioPin pin_e;
    t_uint16 bspPin_u16;
    t_uint32 currentTick_u32 = 0;


    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < FMKIO_INPUT_SIGEVNT_NB ; LLI_u8++)
    {
        pin_e = c_InEvntSigBspMap_as[LLI_u8].BasicCfg_s.HwPin_e;

        if(g_InEvntSigInfo_as[LLI_u8].IsSigConfigured_b == (t_bool)True)
        {
            bspPin_u16 = c_BspPinMapping_ua16[pin_e];

            if(__HAL_GPIO_EXTI_GET_IT(bspPin_u16) != 0x00u)
            { 
                //call user function if debouncer counter is passed
                FMKCPU_Get_Tick(&currentTick_u32);
                if((currentTick_u32 - g_lastTick_ua32[LLI_u8]) > g_InEvntSigInfo_as[LLI_u8].debcDelay_u32)
                {
                    g_lastTick_ua32[LLI_u8] = currentTick_u32;
                    __HAL_GPIO_EXTI_CLEAR_IT(bspPin_u16);
                    g_InEvntSigInfo_as[LLI_u8].EvntFunc_cb();
                }
            }
        }
    }

    return;
}
//********************************************************************************
//                      HAL_Callback Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Exti IRQN_Handler: Start */
/*********************************
 * EXTI0_IRQHandler
*********************************/
void EXTI0_IRQHandler(void)               {return s_FMKIO_BspRqst_InterruptMngmt();}

/*********************************
 * EXTI1_IRQHandler
*********************************/
void EXTI1_IRQHandler(void)               {return s_FMKIO_BspRqst_InterruptMngmt();}

/*********************************
 * EXTI2_IRQHandler
*********************************/
void EXTI2_IRQHandler(void)               {return s_FMKIO_BspRqst_InterruptMngmt();}

/*********************************
 * EXTI3_IRQHandler
*********************************/
void EXTI3_IRQHandler(void)               {return s_FMKIO_BspRqst_InterruptMngmt();}

/*********************************
 * EXTI4_IRQHandler
*********************************/
void EXTI4_IRQHandler(void)               {return s_FMKIO_BspRqst_InterruptMngmt();}

/*********************************
 * EXTI9_5_IRQHandler
*********************************/
void EXTI9_5_IRQHandler(void)             {return s_FMKIO_BspRqst_InterruptMngmt();}

/*********************************
 * EXTI15_10_IRQHandler
*********************************/
void EXTI15_10_IRQHandler(void)           {return s_FMKIO_BspRqst_InterruptMngmt();}

/* CAUTION : Automatic generated code section for Exti IRQN_Handler: End */

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
 *	@params[in]
 *
 *
 *
 */
