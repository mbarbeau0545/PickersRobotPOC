/*********************************************************************
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

#include "stm32f0xx_hal.h"
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
typedef struct
{
    t_bool IsSigConfigured_b;               /**< Flag which indicate wether or not the signal has been configured */
    t_bool IsInterruptEnable_b;             /**< Flag which indicate if the interruption is enable or not for tthe signal */

} t_sFMKIO_DigSigInfo;

/**< Structure common to all analog and Pwm signal to repertory signal information */
typedef struct
{
    t_bool IsSigConfigured_b;                   /**< Flag which indicate wether or not the signal has been configured */
    t_bool IsInterruptEnable_b;                 /**< Flag which indicate if the interruption is enable or not for tthe signal */
    t_cbFMKIO_SigErrorMngmt * sigError_cb;      /**< callback function if an error occured  */

} t_sFMKIO_AnaPwmSigInfo;

/**< Structure common to frequency signal information */
typedef struct
{
    t_bool IsSigConfigured_b;       /**< @ref  IsSigConfigured_b*/
    t_bool IsInterruptEnable_b;     /**< @ref  IsInterruptEnable_b*/
    t_eFMKIO_FreqMeas meas_e;       /**< Frequency measuremnt mode (counter/ freq/Period) */
    t_uint32 value_u32;              /**< the difference between the last and current capture on channel */
    t_uint32 savedValue_32;         /**< last value saved of diffValue_u32 */
    t_bool FlagValueWriting_b;      /**< Flag indicate that an interruption is in progress */
    t_cbFMKIO_SigErrorMngmt * sigError_cb;    /**< callback function if an error occured  */

} t_sFMKIO_InFreqSigInfo;

/**< Structure common to Event signal information */
typedef struct
{
    t_bool IsSigConfigured_b;               /**< @ref  IsSigConfigured_b*/
    t_bool IsInterruptEnabl;                /**< @ref  IsInterruptEnable_b*/
    t_cbFMKIO_EventFunc *EvntFunc_cb;       /**< Store the callback function*/
    t_cbFMKIO_SigErrorMngmt * sigError_cb;    /**< callback function if an error occured  */
   
} t_sFMKIO_InEvntSigInfo;
// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
t_sFMKIO_InFreqSigInfo     g_InFreqSigInfo_as[FMKIO_INPUT_SIGFREQ_NB];        /**< Signal information for input frequency */
t_sFMKIO_AnaPwmSigInfo     g_InAnaSigInfo_as[FMKIO_INPUT_SIGANA_NB];          /**< Signal information for input Analog */
t_sFMKIO_DigSigInfo        g_InDigSigInfo_as[FMKIO_INPUT_SIGDIG_NB];          /**< Signal information for input Digital */
t_sFMKIO_InEvntSigInfo     g_InEvntSigInfo_as[FMKIO_INPUT_SIGEVNT_NB];        /**< Signal information for input Event */
t_sFMKIO_AnaPwmSigInfo     g_OutPwmSigInfo_as[FMKIO_OUTPUT_SIGPWM_NB];        /**< Signal information for output PWM */
t_sFMKIO_DigSigInfo        g_OutDigSigInfo_as[FMKIO_OUTPUT_SIGDIG_NB];        /**< Signal information for output Digital */
    
/* CAUTION : Automatic generated code section for Variable: Start */
/**< Variable to store the state of GPIO Clock */
t_eFMKCPU_ClockPortOpe g_IsGpioClockEnable_ae[FMKIO_GPIO_PORT_NB] = {
    FMKCPU_CLOCKPORT_OPE_DISABLE, // FMKIO_GPIO_PORT_A
    FMKCPU_CLOCKPORT_OPE_DISABLE, // FMKIO_GPIO_PORT_B
    FMKCPU_CLOCKPORT_OPE_DISABLE, // FMKIO_GPIO_PORT_C
    FMKCPU_CLOCKPORT_OPE_DISABLE, // FMKIO_GPIO_PORT_D
    FMKCPU_CLOCKPORT_OPE_DISABLE, // FMKIO_GPIO_PORT_F
};

/* CAUTION : Automatic generated code section for Variable: End */

/**< Module state */
static t_eCyclicFuncState g_state_e = STATE_CYCLIC_WAITING;
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
static t_eReturnState s_FMKIO_Get_BspPullMode(t_eFMKIO_PullMode f_pull_e, t_uint32 *f_bspPull_pu32);
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
static t_eReturnState s_FMKIO_Get_BspSpdMode(t_eFMKIO_SpdMode f_spd_e, t_uint32 *f_bspSpd_pu32);
/**
 *
 *	@brief      Get the Bsp Gpio Port Instance 
 *	@note       Using the enum f_spd_e and switch case, this function 
                return the right GPIOPort Instance.\n
 *
 *
 *	@param[in]  f_GpioPort_e       : GPIOPort enum from @ref t_eFMKIO_GpioPort
 *	@param[in]  f_BspGpio_ps       : pointor to pointor to change the direction a the pointer
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 * @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *
 */
static t_eReturnState s_FMKIO_Get_BspGpioPort(t_eFMKIO_GpioPort f_GpioPort_e, GPIO_TypeDef **f_BspGpio_ps);
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
 * @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 * @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *
 */
static t_eReturnState s_FMKIO_Get_BspTriggerMode(t_eFMKIO_SigTrigCptr f_trigger_e, t_uint32 *f_bspTrigger_pu32);
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
static t_eReturnState s_FMKIO_Set_BspSigCfg(t_eFMKIO_GpioPort f_gpioPort_e,
                                            t_eFMKIO_BspGpioPin f_pin_e,
                                            t_uint32 f_mode_u32,
                                            t_eFMKIO_PullMode f_pull_e,
                                            t_eFMKIO_SpdMode f_spd_e,
                                            t_uint8 f_AltFunc_u8);
/**
 *
 *	@brief      FMKCPU callback function to determine signal frequency value
 *
 *	@param[in]  f_timer_e        : timer from  @ref t_eFMKCPU_Timer
 *	@param[in]  f_channel_e      : timer channel  from @ref t_eFMKCPU_InterruptChnl
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static t_eReturnState s_FMKIO_MngSigFrequency(t_eFMKCPU_Timer f_timer_e, t_eFMKCPU_InterruptChnl f_channel_e);
/**
 *
 *	@brief      Function to set HAL_RCC clock state : Enable/Disable
 *
 *	@param[in]  f_GpioPort_e     : GPIOPort enum, value from @ref t_eFMKIO_GpioPort
 *	@param[in]  f_ope_e          : Enable or Diable RCC clock, value from @ref t_eFMKCPU_ClockPortOpe
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static t_eReturnState s_FMKIO_Set_GpioClkState(t_eFMKIO_GpioPort f_gpioPort_e, t_eFMKCPU_ClockPortOpe f_ope_e);
/**
 *
 *	@brief      Function to perform diag on siganl used 
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static t_eReturnState s_FMKIO_Operational(void);
/**
 *
 *	@brief      Perform diagnostic cyclic on signal configured.\n 
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *
 */
static t_eReturnState s_FMKIO_PerformDiagnostic(void);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * FMKCPU_Init
 *********************************/
t_eReturnState FMKIO_Init(void)
{
    t_uint8 LLI_u8;
    
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_INPUT_SIGFREQ_NB ; LLI_u8++)
    {
        g_InFreqSigInfo_as[LLI_u8].meas_e = FMKIO_FREQ_MEAS_NB;
        g_InFreqSigInfo_as[LLI_u8].IsInterruptEnable_b = False;
        g_InFreqSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
        g_InFreqSigInfo_as[LLI_u8].FlagValueWriting_b  = False;
        g_InFreqSigInfo_as[LLI_u8].value_u32           = (t_uint32)0;
        g_InFreqSigInfo_as[LLI_u8].savedValue_32      = (t_uint32)0;
        g_InFreqSigInfo_as[LLI_u8].sigError_cb = (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION;
    }
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_INPUT_SIGANA_NB ; LLI_u8++)
    {
        g_InAnaSigInfo_as[LLI_u8].IsInterruptEnable_b = False;
        g_InAnaSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
        g_InAnaSigInfo_as[LLI_u8].sigError_cb = (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION;
    }
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_INPUT_SIGDIG_NB ; LLI_u8++)
    {
        g_InDigSigInfo_as[LLI_u8].IsInterruptEnable_b = False;
        g_InDigSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
    }
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_INPUT_SIGEVNT_NB ; LLI_u8++)
    {
        g_InEvntSigInfo_as[LLI_u8].EvntFunc_cb = (t_cbFMKIO_EventFunc *)NULL_FONCTION;
        g_InEvntSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
        g_InEvntSigInfo_as[LLI_u8].sigError_cb = (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION;
    }
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_OUTPUT_SIGPWM_NB ; LLI_u8++)
    {
        g_OutPwmSigInfo_as[LLI_u8].IsInterruptEnable_b = False;
        g_OutPwmSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
        g_OutPwmSigInfo_as[LLI_u8].sigError_cb = (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION;
    }
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKIO_OUTPUT_SIGDIG_NB ; LLI_u8++)
    {
        g_OutDigSigInfo_as[LLI_u8].IsInterruptEnable_b = False;
        g_OutDigSigInfo_as[LLI_u8].IsSigConfigured_b   = False;
    }

    return RC_OK;
}
/*********************************
 * FMKIO_Cyclic
 *********************************/
t_eReturnState FMKIO_Cyclic(void)
{
    t_eReturnState Ret_e = RC_OK;

    switch (g_state_e)
    {
    case STATE_CYCLIC_WAITING:
    {
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_OPE:
    {
        Ret_e = s_FMKIO_Operational();
        if(Ret_e < RC_OK)
        {
            g_state_e = STATE_CYCLIC_ERROR;
        }
        break;
    }
    case STATE_CYCLIC_ERROR:
    {
        break;
    }
    case STATE_CYCLIC_PREOPE:
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
t_eReturnState FMKIO_GetState(t_eCyclicFuncState *f_State_pe)
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
 * FMKIO_SetState
 *********************************/
t_eReturnState FMKIO_SetState(t_eCyclicFuncState f_State_e)
{
    g_state_e = f_State_e;
    return RC_OK;
}
/*********************************
 * s_FMKIO_Get_BspPullMode
 *********************************/
t_eReturnState FMKIO_Set_InDigSigCfg(t_eFMKIO_InDigSig f_signal_e, t_eFMKIO_PullMode f_pull_e)
{
    t_eReturnState Ret_e = RC_OK;
    t_eFMKIO_GpioPort gpioPort_e;

    if (f_signal_e > FMKIO_INPUT_SIGDIG_NB || f_pull_e > FMKIO_PULL_MODE_NB)
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
                                      (t_uint32)MODE_INPUT,
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
t_eReturnState FMKIO_Set_InAnaSigCfg(t_eFMKIO_InAnaSig f_signal_e, 
                                        t_eFMKIO_PullMode f_pull_e,
                                        t_cbFMKIO_SigErrorMngmt *f_sigErr_cb)
{
    t_eReturnState Ret_e = RC_OK;

    if (f_signal_e > FMKIO_INPUT_SIGANA_NB || f_pull_e > FMKIO_PULL_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_InAnaSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKIO_Set_BspSigCfg(c_InAnaSigBspMap_as[f_signal_e].BasicCfg.HwGpio_e,
                                      c_InAnaSigBspMap_as[f_signal_e].BasicCfg.HwPin_e,
                                      (t_uint32)MODE_ANALOG,
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
t_eReturnState FMKIO_Set_InFreqSigCfg(t_eFMKIO_InFreqSig f_signal_e, 
                                            t_eFMKIO_SigTrigCptr f_trigger_e,
                                            t_eFMKIO_FreqMeas f_freqMeas_e,
                                            t_cbFMKIO_SigErrorMngmt *f_sigErr_cb)
{
    t_eReturnState Ret_e = RC_OK;
    t_eFMKCPU_ChnlMeasTrigger cpu_trigger_e = FMKCPU_CHNL_MEAS_NB;

    if (f_signal_e > FMKIO_INPUT_SIGFREQ_NB 
    || f_trigger_e > FMKIO_STC_NB 
    || f_freqMeas_e > FMKIO_FREQ_MEAS_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_InFreqSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKIO_Set_BspSigCfg(c_InFreqSigBspMap_as[f_signal_e].BasicCfg.HwGpio_e,
                                      c_InFreqSigBspMap_as[f_signal_e].BasicCfg.HwPin_e,
                                      (t_uint32)GPIO_MODE_AF_PP,
                                      FMKIO_PULL_MODE_UNABLE,
                                      FMKIO_SPD_MODE_HIGH, 
                                      c_InFreqSigBspMap_as[f_signal_e].BspAlternateFunc_u8);
        if (Ret_e == RC_OK)
        {   
            switch (f_trigger_e)
            {
                case FMKIO_STC_RISING_EDGE:
                    cpu_trigger_e = FMKCPU_CHNL_MEAS_RISING_EDGE;
                case FMKIO_STC_FALLING_EDGE:
                    cpu_trigger_e = FMKCPU_CHNL_MEAS_FALLING_EDGE;
                case FMKIO_STC_BOTH_EDGE:
                    cpu_trigger_e = FMKCPU_CHNL_MEAS_BOTH_EDGE;
                case FMKIO_STC_NB:
                default:
                    Ret_e = RC_ERROR_WRONG_CONFIG;
            }
        }
        if(Ret_e == RC_OK)
        {
            // get the FMKCPU channel meas corresponding to f_trigger_e
            Ret_e = FMKCPU_Set_ICChannelCfg(c_InFreqSigBspMap_as[f_signal_e].timer_e,
                                            c_InFreqSigBspMap_as[f_signal_e].channel_e,
                                            cpu_trigger_e,
                                            (t_cbFMKCPU_InterruptChnl *)s_FMKIO_MngSigFrequency);
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
 * FMKIO_Set_InEvntSigCfg
 *********************************/
t_eReturnState FMKIO_Set_InEvntSigCfg(t_eFMKIO_InEvntSig f_signal_e, 
                                          t_eFMKIO_PullMode f_pull_e,
                                          t_eFMKIO_SigTrigCptr f_trigger_e,
                                          t_cbFMKIO_EventFunc * f_Evnt_cb,
                                          t_cbFMKIO_SigErrorMngmt *f_sigErr_cb)
{
    t_eReturnState Ret_e = RC_OK;
    t_eFMKIO_GpioPort gpioPort_e;
    t_uint32 bspTrigger_u32;

    if (f_signal_e > FMKIO_INPUT_SIGEVNT_NB || f_pull_e > FMKIO_PULL_MODE_NB || f_trigger_e > FMKIO_STC_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_Evnt_cb == (t_cbFMKIO_EventFunc *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_InEvntSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        gpioPort_e = c_InEvntSigBspMap_as[f_signal_e].BasicCfg.HwGpio_e;
        Ret_e = s_FMKIO_Get_BspTriggerMode(f_trigger_e, &bspTrigger_u32);
        if (Ret_e == RC_OK)
        {
            Ret_e = s_FMKIO_Set_BspSigCfg(gpioPort_e,
                                          c_InEvntSigBspMap_as[f_signal_e].BasicCfg.HwPin_e,
                                          (t_uint32)bspTrigger_u32,
                                          FMKIO_PULL_MODE_UNABLE,
                                          FMKIO_SPD_MODE_LOW, // irrevelent for a input sig dig
                                          FMKIO_AF_UNUSED);
            if (Ret_e == RC_OK)
            {

                Ret_e = FMKCPU_Set_NVICState(c_InEvntSigBspMap_as[f_signal_e].ExtiIRQN_e,
                                             FMKCPU_NVIC_PRIORITY_MEDIUM,
                                             FMKCPU_NVIC_OPE_ENABLE);
                if (Ret_e == RC_OK)
                { // update info
                    g_InEvntSigInfo_as[f_signal_e].IsSigConfigured_b = (t_bool)True;
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
t_eReturnState FMKIO_Set_OutPwmSigCfg(t_eFMKIO_OutPwmSig       f_signal_e, 
                                          t_eFMKIO_PullMode        f_pull_e,
                                          t_uint32                 f_frequency_u32,
                                          t_uint16                 f_dutyCycle_u16,
                                          t_bool                   f_startNow_b,
                                          t_cbFMKIO_SigErrorMngmt *f_sigErr_cb)
{
    t_eReturnState Ret_e = RC_OK;
    t_eFMKIO_GpioPort gpioPort_e = FMKIO_GPIO_PORT_NB;
    t_eFMKCPU_Timer timer_e = FMKCPU_TIMER_NB;
    t_eFMKCPU_InterruptChnl TimChannel_e = FMKCPU_CHANNEL_NB;

    if (f_signal_e > FMKIO_OUTPUT_SIGPWM_NB || f_pull_e > FMKIO_PULL_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_OutPwmSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        timer_e = c_OutPwmSigBspMap_as[f_signal_e].timer_e;
        TimChannel_e = c_OutPwmSigBspMap_as[f_signal_e].channel_e;
        Ret_e = FMKCPU_Set_PWMChannelCfg(timer_e, TimChannel_e, f_frequency_u32);

        if (Ret_e == RC_OK && f_startNow_b == (t_bool)True)
        {
            Ret_e = FMKCPU_Set_PWMChannelDuty(timer_e, TimChannel_e, f_dutyCycle_u16);
        }
        
        if (Ret_e == RC_OK)
        {
            gpioPort_e = c_OutPwmSigBspMap_as[f_signal_e].BasicCfg.HwGpio_e;
            Ret_e = s_FMKIO_Set_BspSigCfg(gpioPort_e,
                                      c_OutPwmSigBspMap_as[f_signal_e].BasicCfg.HwPin_e,
                                      (t_uint32)GPIO_MODE_AF_PP,
                                      f_pull_e,
                                      FMKIO_SPD_MODE_LOW, // irrevelent for a input sig dig
                                      c_OutPwmSigBspMap_as[f_signal_e].BspAlternateFunc_u8);
            
            if (Ret_e == RC_OK)
            { // update info
                g_OutPwmSigInfo_as[f_signal_e].IsSigConfigured_b = (t_bool)True;
                g_OutPwmSigInfo_as[f_signal_e].sigError_cb = f_sigErr_cb;
            }
        }
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Set_OutDigSigCfg
 *********************************/
t_eReturnState FMKIO_Set_OutDigSigCfg(t_eFMKIO_OutDigSig f_signal_e,
                                      t_eFMKIO_PullMode f_pull_e,
                                      t_eFMKIO_SpdMode f_spd_e)
{
    t_eReturnState Ret_e = RC_OK;
    t_eFMKIO_GpioPort gpioPort_e;

    if (f_signal_e > FMKIO_OUTPUT_SIGDIG_NB || f_pull_e > FMKIO_PULL_MODE_NB || f_spd_e > FMKIO_SPD_MODE_NB)
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
 * FMKIO_Set_OutDigSigValue
 *********************************/
t_eReturnState FMKIO_Set_OutDigSigValue(t_eFMKIO_OutDigSig f_signal_e, t_eFMKIO_DigValue f_value_e)
{
    t_eReturnState Ret_e = RC_OK;
    GPIO_TypeDef *bspGpio_ps = (GPIO_TypeDef *)NULL;
    GPIO_PinState bspSigValue_e;

    if (f_signal_e > FMKIO_OUTPUT_SIGDIG_NB || f_value_e > FMKIO_DIG_VALUE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_OutDigSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKIO_Get_BspGpioPort(c_OutDigSigBspMap_as[f_signal_e].HwGpio_e, &bspGpio_ps);
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
                                  c_BspPinMapping_ua32[c_OutDigSigBspMap_as[f_signal_e].HwPin_e],
                                  bspSigValue_e);
            }
        }
    }
    return Ret_e;
}
/*********************************
 * FMKIO_Set_OutPwmSigValue
 *********************************/
t_eReturnState FMKIO_Set_OutPwmSigValue(t_eFMKIO_OutPwmSig f_signal_e, t_uint16 f_dutyCycle_u16)
{
    t_eReturnState Ret_e = RC_OK;

    if (f_signal_e > FMKIO_OUTPUT_SIGPWM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_OutPwmSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = FMKCPU_Set_PWMChannelDuty(c_OutPwmSigBspMap_as[f_signal_e].timer_e,
                                          c_OutPwmSigBspMap_as[f_signal_e].channel_e,
                                          f_dutyCycle_u16);
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Set_OutPwmSigValue
 *********************************/
t_eReturnState FMKIO_Get_InDigSigValue(t_eFMKIO_InDigSig f_signal_e, t_eFMKIO_DigValue *f_value_pe)
{
    t_eReturnState Ret_e = RC_OK;
    GPIO_TypeDef *bspGpio_ps = (GPIO_TypeDef *)NULL;
    GPIO_PinState bspSigValue_e;

    if (f_signal_e > FMKIO_INPUT_SIGDIG_NB)
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
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKIO_Get_BspGpioPort(c_InDigSigBspMap_as[f_signal_e].HwGpio_e, &bspGpio_ps);
        if (Ret_e == RC_OK)
        {
            bspSigValue_e = HAL_GPIO_ReadPin(bspGpio_ps, c_BspPinMapping_ua32[c_InDigSigBspMap_as[f_signal_e].HwPin_e]);
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
t_eReturnState FMKIO_Get_InAnaSigValue(t_eFMKIO_InAnaSig f_signal_e, t_uint16 *f_value_pu16)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint16 anaValue_16 = 0;

    if (f_signal_e > FMKIO_INPUT_SIGANA_NB)
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
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = FMKCDA_Get_AnaChannelMeasure(c_InAnaSigBspMap_as[f_signal_e].adc_e,
                                             c_InAnaSigBspMap_as[f_signal_e].adcChannel_e,
                                             &anaValue_16);
        if(Ret_e == RC_OK)
        {
            if(anaValue_16 < (t_uint16)FMKIO_ANALOG_OL_VALUE)
            {
                *f_value_pu16 = (t_uint16)FMKIO_ANALOG_MIN_VALUE;
                g_InAnaSigInfo_as[f_signal_e].sigError_cb((t_uint8)FMKIO_ANALOG_OL_DETECTED, (t_uint8)0);
            }
            else if(anaValue_16 > (t_uint16)FMKIO_ANALOG_SC_VALUE)
            {
                *f_value_pu16 = (t_uint16)FMKIO_ANALOG_MAX_VALUE;
                g_InAnaSigInfo_as[f_signal_e].sigError_cb((t_uint8)FMKIO_ANALOG_SC_DETECTED, (t_uint8)0);
            }
            else
            {
                *f_value_pu16 = (t_uint16)anaValue_16;
            }
        }
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Get_InFreqSigValue
 *********************************/
t_eReturnState FMKIO_Get_InFreqSigValue(t_eFMKIO_InFreqSig f_signal_e, t_uint32 *f_value_pu32)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint32 value_u32 = 0;
    if (f_signal_e > FMKIO_INPUT_SIGFREQ_NB)
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
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        // if flag writing value is False, make calcul on value, else make calcul on saved value
        if( g_InFreqSigInfo_as[f_signal_e].FlagValueWriting_b == (t_bool)False)
        {
            value_u32 = g_InFreqSigInfo_as[f_signal_e].value_u32;
        }
        else
        {
            value_u32 = g_InFreqSigInfo_as[f_signal_e].savedValue_32;
            Ret_e = RC_WARNING_BUSY;
        }
        if(value_u32 > (t_uint32)0)
        {
            switch(g_InFreqSigInfo_as[f_signal_e].meas_e)
            {
                case FMKIO_FREQ_MEAS_COUNT:
                    *f_value_pu32 = value_u32;
                    break;
                case FMKIO_FREQ_MEAS_PERIOD:
                    *f_value_pu32 = (t_uint32)((t_float32)value_u32 / (t_float32)HAL_RCC_GetPCLK1Freq());
                    break;
                case FMKIO_FREQ_MEAS_FREQ:
                    *f_value_pu32 = (t_uint32)((t_float32)HAL_RCC_GetPCLK1Freq() / (t_float32)value_u32);
                    break;
                case FMKIO_FREQ_MEAS_NB:
                default:
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;
            }
        }
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Get_OutPwmSigValue
 *********************************/
t_eReturnState FMKIO_Get_OutPwmSigValue(t_eFMKIO_OutPwmSig f_signal_e, t_uint16 *f_value_pu16)
{
    t_eReturnState Ret_e = RC_OK;

    if (f_signal_e > FMKIO_OUTPUT_SIGPWM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_value_pu16 == (t_uint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_OutPwmSigInfo_as[f_signal_e].IsSigConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = FMKCPU_Get_PWMChannelDuty(c_OutPwmSigBspMap_as[f_signal_e].timer_e,
                                          c_OutPwmSigBspMap_as[f_signal_e].channel_e,
                                          f_value_pu16);
    }
    return Ret_e;
}

/*********************************
 * FMKIO_Get_OutDigSigValue
 *********************************/
t_eReturnState FMKIO_Get_OutDigSigValue(t_eFMKIO_OutDigSig f_signal_e, t_eFMKIO_DigValue *f_value_pe)
{
    t_eReturnState Ret_e = RC_OK;
    GPIO_TypeDef *bspGpio_ps = (GPIO_TypeDef *)NULL;
    GPIO_PinState bspSigValue_e;

    if (f_signal_e > FMKIO_OUTPUT_SIGDIG_NB)
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
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKIO_Get_BspGpioPort(c_InDigSigBspMap_as[f_signal_e].HwGpio_e, &bspGpio_ps);
        if (Ret_e == RC_OK)
        {
            bspSigValue_e = HAL_GPIO_ReadPin(bspGpio_ps, c_BspPinMapping_ua32[c_InDigSigBspMap_as[f_signal_e].HwPin_e]);
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
 * s_FMKIO_Operational
 *********************************/
static t_eReturnState s_FMKIO_Operational(void)
{
    t_eReturnState Ret_e = RC_OK;
    static t_uint32 SavedTime_u32 = 0;
    t_uint32 currentTime_u32 = 0;

    Ret_e = FMKCPU_Get_Tick(&currentTime_u32);
    if(Ret_e == RC_OK)
    {
        if((currentTime_u32 - SavedTime_u32) > (t_uint32)FMKIO_TIME_BTWN_DIAG_MS)
        {//perform diag on timer / chnl used
            SavedTime_u32 = currentTime_u32;
            Ret_e = s_FMKIO_PerformDiagnostic();
        }
        // else do other thing(or nothing for now)
    }
    return Ret_e;
}

/*********************************
 * s_FMKIO_PerformDiagnostic
 *********************************/
static t_eReturnState s_FMKIO_PerformDiagnostic(void)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint8 LLI_u8;
    t_eFMKCPU_ChnlErrorState cpuChnlStatus_e;
    t_eFMKCDA_ChnlErrState   adcChnlStatus_e;

    // perform diag for PWM signal configuration 
    for(LLI_u8 = (t_uint8)0 ; (LLI_u8 < FMKIO_OUTPUT_SIGPWM_NB) ; LLI_u8++)
    {
        if(g_OutPwmSigInfo_as[LLI_u8].IsSigConfigured_b == (t_bool)True)
        {
            Ret_e = FMKCPU_Get_ChannelErrorStatus(c_OutPwmSigBspMap_as[LLI_u8].timer_e,
                                                    c_OutPwmSigBspMap_as[LLI_u8].channel_e,
                                                    &cpuChnlStatus_e);
            if((Ret_e == RC_OK)
            && (cpuChnlStatus_e != FMKCPU_ERRSTATE_OK)
            && (g_OutPwmSigInfo_as[LLI_u8].sigError_cb != (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION))
            {
                g_OutPwmSigInfo_as[LLI_u8].sigError_cb(cpuChnlStatus_e, 0);
            }
        }
    }
    // perform diag for Freqency signal configuration 
    for(LLI_u8 = (t_uint8)0 ; (LLI_u8 < FMKIO_INPUT_SIGFREQ_NB) ; LLI_u8++)
    {
        if(g_InFreqSigInfo_as[LLI_u8].IsSigConfigured_b == (t_bool)True)
        {
            Ret_e = FMKCPU_Get_ChannelErrorStatus(c_InFreqSigBspMap_as[LLI_u8].timer_e,
                                                    c_InFreqSigBspMap_as[LLI_u8].channel_e,
                                                    &cpuChnlStatus_e);

            if((Ret_e == RC_OK)
            && (cpuChnlStatus_e != FMKCPU_ERRSTATE_OK)
            && (g_InFreqSigInfo_as[LLI_u8].sigError_cb != (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION))
            {
                g_InFreqSigInfo_as[LLI_u8].sigError_cb(cpuChnlStatus_e, 0);
            }
        }
    } 
    // perform diag for Analog signal configuration 
    for(LLI_u8 = (t_uint8)0 ; (LLI_u8 < FMKIO_INPUT_SIGANA_NB) ; LLI_u8++)
    {
        if(g_InAnaSigInfo_as[LLI_u8].IsSigConfigured_b == (t_bool)True)
        {
            Ret_e = FMKCDA_Get_AdcError(c_InAnaSigBspMap_as[LLI_u8].adc_e,
                                             &adcChnlStatus_e);

            if((Ret_e == RC_OK)
            && (adcChnlStatus_e != FMKCDA_ERRSTATE_OK)
            && (g_InAnaSigInfo_as[LLI_u8].sigError_cb != (t_cbFMKIO_SigErrorMngmt *)NULL_FONCTION))
            {
                g_InAnaSigInfo_as[LLI_u8].sigError_cb(adcChnlStatus_e, 0);
            }
        }
    } 
    return Ret_e;
}
/*********************************
 * s_FMKIO_MngSigFrequency
 *********************************/
static t_eReturnState s_FMKIO_MngSigFrequency(t_eFMKCPU_Timer f_timer_e, t_eFMKCPU_InterruptChnl f_channel_e)
{
    t_eReturnState Ret_e = RC_OK;
    static t_uint32 lastCapture_u32 = 0;
    t_uint32 currentCapture_u32 = 0;
    t_uint8 LLI_u8= 0;
    t_eFMKIO_InFreqSig freqSig_e = FMKIO_INPUT_SIGFREQ_NB;

    // Know wich signal made the interruption 
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < FMKIO_INPUT_SIGFREQ_NB ; LLI_u8++)
    {
        if(f_timer_e == c_InFreqSigBspMap_as[LLI_u8].timer_e 
        && f_channel_e == c_InFreqSigBspMap_as[LLI_u8].channel_e)
        {
            freqSig_e = (t_eFMKIO_InFreqSig)LLI_u8;
            break;
        }
    }
    if(freqSig_e != FMKIO_INPUT_SIGFREQ_NB)
    {
        g_InFreqSigInfo_as[freqSig_e].savedValue_32 = 
                    g_InFreqSigInfo_as[freqSig_e].value_u32;
        // set flag to writing equals true
        g_InFreqSigInfo_as[freqSig_e].FlagValueWriting_b = (t_bool)True;
        switch (g_InFreqSigInfo_as[freqSig_e].meas_e)
        {
            case FMKIO_FREQ_MEAS_COUNT:
            {

                g_InFreqSigInfo_as[freqSig_e].value_u32 += (t_uint32)1;
                break;
            }
            case FMKIO_FREQ_MEAS_PERIOD:
            case FMKIO_FREQ_MEAS_FREQ:
            {
                // Read value for channel linked to the signal 
                Ret_e = FMKCPU_Get_RegisterCRRx(f_timer_e, f_channel_e, &currentCapture_u32);
                if(Ret_e == RC_OK)
                {   
                    // saved difference in freq sig structure, calcul will not be made in intrerruption                                                
                    g_InFreqSigInfo_as[freqSig_e].value_u32 = (t_uint32)(currentCapture_u32 - lastCapture_u32);
                    // saved last catpure value
                    lastCapture_u32 = currentCapture_u32;
                }                
                break;
            }
            case FMKIO_FREQ_MEAS_NB:
            default:
                Ret_e = RC_WARNING_NO_OPERATION;
                break;
        }
        // reset flag
        g_InFreqSigInfo_as[freqSig_e].FlagValueWriting_b = (t_bool)False;
    }
    else 
    {
        Ret_e = RC_ERROR_LIMIT_REACHED;
    }
    
}
/*********************************
 * s_FMKIO_Get_BspPullMode
 *********************************/
static t_eReturnState s_FMKIO_Get_BspPullMode(t_eFMKIO_PullMode f_pull_e, t_uint32 *f_bspPull_pu32)
{
    t_eReturnState Ret_e = RC_OK;

    if (f_pull_e > FMKIO_PULL_MODE_NB)
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
        case FMKIO_PULL_MODE_UNABLE:
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
static t_eReturnState s_FMKIO_Get_BspSpdMode(t_eFMKIO_SpdMode f_spd_e, t_uint32 *f_bspSpd_pu32)
{
    t_eReturnState Ret_e = RC_OK;

    if (f_spd_e > FMKIO_SPD_MODE_NB)
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
static t_eReturnState s_FMKIO_Get_BspTriggerMode(t_eFMKIO_SigTrigCptr f_trigger_e, t_uint32 *f_bspTrigger_pu32)
{
    t_eReturnState Ret_e = RC_OK;

    if (f_trigger_e > FMKIO_STC_NB)
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
 * s_FMKIO_Get_BspGpioPort
 *********************************/
static t_eReturnState s_FMKIO_Get_BspGpioPort(t_eFMKIO_GpioPort f_GpioPort_e, GPIO_TypeDef **f_BspGpio_ps)
{
    t_eReturnState Ret_e = RC_OK;

    if (f_GpioPort_e > FMKIO_GPIO_PORT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_BspGpio_ps == (GPIO_TypeDef **)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_GpioPort_e)
        {
            /* CAUTION : Automatic generated code section for GPIO switch case: Start */
            case FMKIO_GPIO_PORT_A:
                *f_BspGpio_ps = GPIOA;
                break;
            case FMKIO_GPIO_PORT_B:
                *f_BspGpio_ps = GPIOB;
                break;
            case FMKIO_GPIO_PORT_C:
                *f_BspGpio_ps = GPIOC;
                break;
            case FMKIO_GPIO_PORT_D:
                *f_BspGpio_ps = GPIOD;
                break;
            case FMKIO_GPIO_PORT_F:
                *f_BspGpio_ps = GPIOF;
                break;
            /* CAUTION : Automatic generated code section for GPIO switch case: End */
            case FMKIO_GPIO_PORT_NB:
            default:
                Ret_e = RC_WARNING_NO_OPERATION;
                break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKIO_Set_BspSigCfg
 *********************************/
static t_eReturnState s_FMKIO_Set_BspSigCfg(t_eFMKIO_GpioPort f_gpioPort_e,
                                            t_eFMKIO_BspGpioPin f_pin_e,
                                            t_uint32 f_mode_u32,
                                            t_eFMKIO_PullMode f_pull_e,
                                            t_eFMKIO_SpdMode f_spd_e,
                                            t_uint8 f_AltFunc_u8)
{
    t_eReturnState Ret_e = RC_OK;
    GPIO_TypeDef *bspGpio_ps = (GPIO_TypeDef *)NULL;
    GPIO_InitTypeDef bspInit_s;
    t_uint32 bspPull_32 = 0;
    t_uint32 bspSpd_u32 = 0;

    if (f_gpioPort_e > FMKIO_GPIO_PORT_NB || f_pin_e > FMKIO_GPIO_PIN_NB || f_pull_e > FMKIO_PULL_MODE_NB || f_spd_e > FMKIO_SPD_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKIO_Get_BspGpioPort(f_gpioPort_e, &bspGpio_ps);
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
            bspInit_s.Pin = (t_uint32)c_BspPinMapping_ua32[f_pin_e];
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
static t_eReturnState s_FMKIO_Set_GpioClkState(t_eFMKIO_GpioPort f_gpioPort_e, t_eFMKCPU_ClockPortOpe f_ope_e)
{
    t_eReturnState Ret_e = RC_OK;
    t_eFMKCPU_ClockPort gpioClkPort_e;

    if (f_gpioPort_e > FMKIO_GPIO_PORT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        // get the GPIO CLOCK ENUM
        switch (f_gpioPort_e)
        {
        case FMKIO_GPIO_PORT_A:
            gpioClkPort_e = FMKCPU_RCC_CLK_GPIOA;
            break;
        case FMKIO_GPIO_PORT_B:
            gpioClkPort_e = FMKCPU_RCC_CLK_GPIOB;
            break;
        case FMKIO_GPIO_PORT_C:
            gpioClkPort_e = FMKCPU_RCC_CLK_GPIOC;
            break;
        case FMKIO_GPIO_PORT_F:
            gpioClkPort_e = FMKCPU_RCC_CLK_GPIOF;
            break;
        case FMKIO_GPIO_PORT_D:
        case FMKIO_GPIO_PORT_NB:
        default:
            Ret_e = RC_WARNING_NO_OPERATION;
            break;
        }
        if (Ret_e == RC_OK)
        {
            Ret_e = FMKCPU_Set_HwClock(gpioClkPort_e, f_ope_e);
        }
        if (Ret_e == RC_OK)
        {
            g_IsGpioClockEnable_ae[f_gpioPort_e] = f_ope_e;
        }
    }
    return Ret_e;
}
//********************************************************************************
//                      HAL_Callback Implementation
//********************************************************************************
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    t_uint8 LLI_u8;
    t_eFMKIO_BspGpioPin bspPinEvnt_e;
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < FMKIO_INPUT_SIGEVNT_NB ; LLI_u8++)
    {
        bspPinEvnt_e = c_InEvntSigBspMap_as[LLI_u8].BasicCfg.HwPin_e;
        if(c_BspPinMapping_ua32[bspPinEvnt_e] == GPIO_Pin)
        {
            break;
        }
    }
    if(LLI_u8 < FMKIO_INPUT_SIGEVNT_NB)
    {
        if(g_InEvntSigInfo_as[LLI_u8].EvntFunc_cb != (t_cbFMKIO_EventFunc *)NULL_FONCTION)
        {
            g_InEvntSigInfo_as[LLI_u8].EvntFunc_cb();
        }
    }
    
    
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
 *	@params[in]
 *
 *
 *
 */
