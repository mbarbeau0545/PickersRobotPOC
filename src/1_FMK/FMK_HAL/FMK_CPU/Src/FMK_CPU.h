/**
 * @file        FMK_CPU.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKCPU_H_INCLUDED
#define FMKCPU_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "FMK_CFG/FMKCFG_ConfigFiles/FMKCPU_ConfigPublic.h"
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKCPU_PWM_MAX_DUTY_CYLCE ((t_uint16)1000) /**< Max duty cycle allowed */
    #define FMKCPU_PWM_MIN_DUTY_CYLCE ((t_uint16)0)    /**< Min dutyCycle allowed */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
    /**< Enum for harware channel polarity */
    typedef enum
    {
        FMKCPU_CHNLPOLARITY_LOW = 0x0U,         /**< Reference to harware channel polarity low */
        FMKCPU_CHNLPOLARITY_HIGH,               /**< Reference to harware channel polarity high */

        FMKCPU_CHNLPOLARITY_NB                  /**< Number of hardxware channel polarity */
    } t_eFMKCPU_ChnlPolarity;

    /**< Enum  for channel state */
    typedef enum
    {
        FMKCPU_CHNLST_DISACTIVATED = 0x0U,       /**< the channel is disactivated by software, not running */
        FMKCPU_CHNLST_ACTIVATED,                 /**< The channel is acitvated by software, is running */

        FMKCPU_CHNLST_NB                        /**< Number of channel state */
    } t_eFMKCPU_ChnlState;

    /**< Enum for timer state */
    typedef enum
    {
        FMKCPU_TIMST_DISACTIVATED = 0x0U,       /**< Event timer is disactivated */
        FMKCPU_TIMST_ACTIVATED,                 /**< Event timer is activated */

        FMKCPU_TIMST_NB 
    } t_eFMKCPU_EvntTimState;

    /**< Enum for channel run mode */
    typedef enum 
    {
        FMKCPU_CNHL_RUNMODE_POLLING = 0x0U,     /**< The channel is running in polling mode (standard mode) */
        FMKCPU_CNHL_RUNMODE_INTERRUPT,          /**< The channel is running in interrupt mode, which means HAL error callback is active,
                                                 among other things*/
        FMKCPU_CHNL_RUNMODE_DMA,                /**< The channel is running in DMA Mode */

        FMKCPU_CNHL_RUNMODE_NB                  /**< Number of channel run mode take in charge (DMA currently not available) */
    } t_eFMKCPU_ChnlRunMode; 

    /**< Enuum for crcc clock port operation */
    typedef enum 
    {
        FMKCPU_CLOCKPORT_OPE_ENABLE = 0x0U,     /**< The operation to make on rcc clock port will be to enable it */
        FMKCPU_CLOCKPORT_OPE_DISABLE,           /**< The operation to make on rcc clock port will be to disable it */

        FMKCPU_CLOCKPORT_OPE_NB                 /**< Number of operation on rcc clock state */
    } t_eFMKCPU_ClockPortOpe;

    /**< enum for NVIC operation state */
    typedef enum 
    {
        FMKCPU_NVIC_OPE_ENABLE = 0x0U,          /**< The operation to make on NVIC is to enable it */
        FMKCPU_NVIC_OPE_DISABLE,                /**< The operation to make on NVIC is to disable it */

        FMKCPU_NVIC_OPE_NB
    } t_eFMKCPU_NVIC_Ope;

    /**< Enum for interruption channel trigger */
    typedef enum 
    {
        FMKCPU_CHNL_MEAS_RISING_EDGE = 0x0U,        /**< The channel interrupt will be triggered on rising edge */
        FMKCPU_CHNL_MEAS_FALLING_EDGE,              /**< The channel interrupt will be triggered on falling edge */
        FMKCPU_CHNL_MEAS_BOTH_EDGE,                 /**< The channel interrupt will be triggered on both edge */

        FMKCPU_CHNL_MEAS_NB                         /**< Number of trigger mode */
    }t_eFMKCPU_ChnlMeasTrigger;

    /**< Enum for timer channel  error */
    typedef enum
    {
        FMKCPU_ERRSTATE_OK = 0X00U,                  /**< No error detected */
        FMKCPU_ERRSTATE_INVALID_CHANNEL,             /**< Invalid canal */
        FMKCPU_ERRSTATE_TIMEOUT,                     /**< time waiting excedeed */
        FMKCPU_ERRSTATE_OVERFLOW,                    /**< overflow capacity */
        FMKCPU_ERRSTATE_UNDERFLOW,                   /**< Under flow capacity */
        FMKCPU_ERRSTATE_NOT_CONFIGURED,              /**< timer or channel not configured */
        FMKCPU_ERRSTATE_OFF_UNEXPECTED,              /**< channel is busy */
        FMKCPU_ERRSTATE_INIT_FAILED,                 /**< Failed during intitialize of channel */
        FMKCPU_ERRSTATE_UNKNOWN,                     /**< unknown error detected */

    } t_eFMKCPU_ChnlErrorState;

    /**< union for Centralize Certain Function */
    typedef union
    {
        t_eFMKCPU_InterruptLineIO ITLine_IO_e;
        t_eFMKCPU_InterruptLineEvnt ITLine_Evnt_e;
        t_eFMKCPU_InterruptLineDAC ITLine_Dac_e;
    } t_uFMKCPU_InterruptLine;
    //-----------------------------TYPEDEF TYPES---------------------------//
    /**
    *
    *	@brief  Call back function for channels
    *
    *	@param[in]      f_timer_e : timer channel 
    *	@param[out]     f_channel_e : channel which make the interruption
    *	 
    *
    */
   typedef t_eReturnCode (t_cbFMKCPU_InterruptLine)(t_eFMKCPU_InterruptLineType f_InterruptType_e, t_uint8 f_InterruptLine_u8);
    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    


    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    /**
    *
    *	@brief      Perform all Init action for this module.\n
    *	@note       Set to default value all globals structure that
    *                store information for each signals.\n
    *
    */
    t_eReturnCode FMKCPU_Init(void);
    /**
    *
    *	@brief      Perform all Cyclic action for this module.\n
    *	@note       In preOpe mode this module makes the configuration of the system clock and 
    *               watchdogs configuration.\n 
    *               In ope mode, this module makesdiag on timer channel currently used, and 
    *               called the appropriate callback if an error occured + call APPDEM
    *               to reference error.\n
    *
    */
    t_eReturnCode FMKCPU_Cyclic(void);
    /**
    *
    *	@brief Function to know the module state.\n 
    *
    *	@param[in]  f_State_pe : store the value, value from @ref t_eCyclicModState
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
    */
    t_eReturnCode FMKCPU_GetState(t_eCyclicModState *f_State_pe);
    /**
    *
    *	@brief Function to update the module state.\n
    *
    *	@param[in]  f_State_e : the new value, value from @ref t_eCyclicModState
    *
    *   @retval RC_OK                             @ref RC_OK
    */
    t_eReturnCode FMKCPU_SetState(t_eCyclicModState f_State_e);
    /**
    *
    *	@brief      Set the system clock configuration.\n
    *   @note       This function has to be first one to be call in the Software.\n
    *               Configure the Clocks used and the frequency for each clock.\n
    *
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    */
    t_eReturnCode FMKCPU_Set_SysClockCfg(t_eFMKCPU_CoreClockSpeed f_SystemCoreFreq_e);
    /**
    *
    *	@brief      Set a Delay without bloxking other interruption.\n
    *
    *	@param[in]  f_delayms_u32 : period delay in millisecond.\n
    *
    */
    void FMKCPU_Set_Delay(t_uint32 f_delayms_u32);
    /**
    *
    *	@brief      Get a tick from clock freqency.\n
    *
    *	@param[in]  f_tickms_pu32 : store the tick value in millisecond.\n
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    */
    void FMKCPU_Get_Tick(t_uint32 * f_tickms_pu32);
    /**
    *
    *	@brief      Set the hardware configuration.\n
    *   @note       Reset of all peripherals, Initializes the Flash interface and the Systick..\n              
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
    */
   t_eReturnCode FMKCPU_Set_HardwareInit(void);
    /**
    *
    *	@brief      Set the priority for a NVIC and the state ON/OFF\n
    *   @note       This function is called to set the interruption priority
    *               for f_IRQN_e interruption.\n 
    *               If an interruption (2) occur while another Interruption (1) is running, 
    *               depending on the value of c_FMKCPU_IRQNPriority_ae (2) that will interrupt or not
    *               the interruption (1).\n
    *               This function also disable the IRQN interruption if needed.\n
    *
    *	@param[in]  f_IRQN_e     : enum value for IRQN type, value from @ref t_eFMKCPU_IRQNType
    *	@param[in]  f_OpeState_e : enum value for  pose state,value from @ref t_eFMKCPU_NVIC_Ope
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
    */
    t_eReturnCode FMKCPU_Set_NVICState(t_eFMKCPU_IRQNType f_IRQN_e, t_eFMKCPU_NVIC_Ope f_OpeState_e);
    /**
    *
    *	@brief      Set the RCC clock state.\n
    *   @note       In order to write down bit in everry register (ADC,GPIO,TIM,etc),
    *               the RCC clock has to be enable first. This function enable or disable
    *               the RCC clock reference to f_clkPort_e.\n
    *              
    *
    *	@param[in]  f_clkPort_e     : enum value for RCC clock, value from @ref t_eFMKCPU_ClockPort
    *	@param[in]  f_OpeState_e    : enum value for priority, value from @ref t_eFMKCPU_NVICPriority
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
    *  @retval RC_WARNING_NO_OPERATION           @ref RC_WARNING_NO_OPERATION
    */
    t_eReturnCode FMKCPU_Set_HwClock(t_eFMKCPU_ClockPort f_clkPort_e, 
                                       t_eFMKCPU_ClockPortOpe f_OpeState_e);
    /**
    *
    *	@brief      Set the watchdog configuration.\n
    *   @note       Set the watchdogs configuration and active it imeddiately.\n              
    *
    *	@param[in]  f_period_e      : enum value for period before reset, value from @ref t_eFMKCPu_WwdgResetPeriod
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    */
    t_eReturnCode FMKCPU_Set_WwdgCfg(t_eFMKCPu_WwdgResetPeriod f_period_e);
    /**
    *
    *	@brief      Reset the watchdogs counter.\n
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    */
    t_eReturnCode FMKCPU_ResetWwdg(void);
    /**
    *
    *	@brief      Configure an tinterrupt line in PWM configuration.\n
    *   @note       First, this configuration set the bsp timer cfg in PWM mode.\n
    *               Once it's done, this function configure the bsp channel in PWM mode too.\n
    *               IMPORTANT, the PWM generation is based on a timer configuration which share
    *               multiple channels, in a sense that, frequency is shared by all PWM channels.\n
    *               In result, the modification of the timer configuration reverbate for all channels.\n     
    *               For Instance, every FMKCPU_INTERRUPT_LINE_IO_0Y, Y belong to [0, Innfini] shared the same timer.\n
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_pwmFreq_u32          : the frequency timer.
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
    */
    t_eReturnCode FMKCPU_Set_PWMChannelCfg( t_eFMKCPU_InterruptLineIO f_InterruptLine_e, 
                                            t_uint32 f_pwmFreq_u32);
    /**
    *
    *	@brief    Set the DutyCycle to a timer channel
    *   @note     Modify the CCRx register to change the dutyCycle.\n
    *             If the timer channel is disable, and the value is diferrent from 0,
    *             this function will enable the channel and set dutycycle give by f_dutyCycle_u16.\n
    *             If the value equals 0 this function will stop the PWM pulse (channel).\n 
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_dutyCycle_u16        : the dutycyle, value from [0, 1000]
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *  @retval RC_WARNING_NO_OPERATION           @ref RC_WARNING_NO_OPERATION
    */
    t_eReturnCode FMKCPU_Set_PWMChannelDuty(t_eFMKCPU_InterruptLineIO f_InterruptLine_e,
                                            t_uint16 f_dutyCycle_u16);
    /**
    *
    *	@brief    Get the DutyCycle from a timer channel
    *   @note     Get the value from CCRx register and convert it in dutycycle
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_dutyCycle_u16        : the dutycyle, value from [0, 1000]
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *  @retval RC_WARNING_NO_OPERATION           @ref RC_WARNING_NO_OPERATION
    */
    t_eReturnCode FMKCPU_Get_PWMChannelDuty(t_eFMKCPU_InterruptLineIO f_InterruptLine_e, 
                                            t_uint16 *f_dutyCycle_u16);
    /**
    *
    *	@brief    Configure a timer channel in Input Compare configuration.\n
    *   @note     The IC Timer configuration is used to measure a signal frequency.\n
    *             This function initialize the timer in Input Compare confgiuration if the
    *             timer is not configured yet.\n
    *             IMPORTANT, the IC config is based on a timer configuration which share
    *             multiple channels, ina sense that, frequency is shared by all PWM channels.\n
    *             In result, the modification of the timer configuration reverbate for all channels.\n   
    *             Once the timer is init correctly, this function set f_channel_e configuration
    *             based on the interrupt mode gives by f_MeasTrigger_e.\n
    *             Finally, if the CPU detect the event, it will call the function f_ITChannel_cb.\n
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_MeasTrigger_e        : trigger for interruption, value from @ref t_eFMKCPU_ChnlMeasTrigger
    *	@param[in]  f_ITChannel_cb         : call back function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *  @retval RC_ERROR_NOT_ALLOWED              @ref RC_ERROR_NOT_ALLOWED
    */
    t_eReturnCode FMKCPU_Set_ICChannelCfg(  t_eFMKCPU_InterruptLineIO f_InterruptLine_e,
                                            t_eFMKCPU_ChnlMeasTrigger f_MeasTrigger_e,
                                            t_cbFMKCPU_InterruptLine * f_ITChannel_cb);
    /**
    *
    *	@brief    Configure a timer channel on event configuration.\n
    *   @note     This function initialize the timer in event configuration if the
    *             timer is not configured yet.\n
    *             Once the timer configure is done, update the channel state using function 
    *             "FMKCPU_Set_InterruptLineState" and every f_periodms_u32 callback function is called.\n
    *             IMPORTANT, In hardware this is the Timer which manage the interruption with ARR register,
    *             which means, it is best that the timer is a basic timer with only one channel, 'cause the others will
    *             be unused.\n
    *
    *	@param[in]  f_EvntITLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineEvnt
    *	@param[in]  f_periodms_u32            : period before calling function, in millisecond
    *	@param[in]  f_ITChannel_cb            : callback function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *  @retval RC_ERROR_NOT_ALLOWED              @ref RC_ERROR_NOT_ALLOWED
    */
    t_eReturnCode FMKCP_Set_EvntTimerCfg(   t_eFMKCPU_InterruptLineEvnt f_EvntITLine_e,
                                            t_uint32 f_periodms_u32,
                                            t_cbFMKCPU_InterruptLine f_ITChannel_cb);
    /**
    *
    *	@brief      Add a callback function to a timer channel.\n
    *   @note       For the configuration where the callback is optionnal (PWM, OP,etc)
    *               This function allow to add a callback. 
    *               On PWM -> callback will be call whenever the PWM pulse generation (not implemented yet) is done 
    *               On OnePulse -> Not implemented
    *           
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_ITChannel_cb      : the frequency timer.
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    */
    t_eReturnCode FMKCPU_AddTimerChnlCallback(  t_eFMKCPU_InterruptLineIO f_InterruptLine_e,
                                                t_cbFMKCPU_InterruptLine *f_ITChannel_cb);
    /**
    *
    *	@brief      Set a InterruptLine  state ON/OFF.\n
    *   @note       Using HAL_TIM function 
    *           
    *
    *	@param[in]  f_timer_e              : enum value for the timer, value from @ref t_eFMKCPU_Timer
    *	@param[in]  f_channel_e            : enum value for the channel, value from @ref t_eFMKCPU_InterruptChnl
    *	@param[in]  f_channelState_e       : enum value for the state operation, value from @ref t_eFMKCPU_ChnlState
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    */
    t_eReturnCode FMKCPU_Set_InterruptLineState(t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                                t_uFMKCPU_InterruptLine IT_line_u,
                                                t_eFMKCPU_ChnlState f_channelState_e);
    /**
    *
    *	@brief      Function to get the error code for a timer_channel
    *
    *	@param[in]  f_timer_e                : enum value for the timer, value from @ref t_eFMKCPU_Timer
    *	@param[in]  f_channel_e              : enum value for the channel, value from @ref t_eFMKCPU_InterruptChnl
    *	@param[in]  f_chnlErrInfo_pu16       : storage for channel error.\n
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *
    */
    t_eReturnCode FMKCPU_Get_ChannelErrorStatus(t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                                t_uFMKCPU_InterruptLine f_IT_line_u,
                                                t_uint16 *f_chnlErrInfo_pu16);
    /**
    *
    *	@brief      Function to get CCRx register value
    *
    *	@param[in]  f_timer_e                : enum value for the timer, value from @ref t_eFMKCPU_Timer
    *	@param[in]  f_channel_e              : enum value for the channel, value from @ref t_eFMKCPU_InterruptChnl
    *	@param[in]  f_CCRxValue_pu32         : storage for CCRx Value.\n
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *
    */
    t_eReturnCode FMKCPU_Get_RegisterCRRx(  t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                            t_uFMKCPU_InterruptLine f_IT_line_u,
                                            t_uint32 * f_CCRxValue_pu32);
#endif // FMKCPU_H_INCLUDED           
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
