/**
 * @file        FMK_CPU.c
 * @brief       Framework for Unit Processing Control.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        25/08/2024
 * @version     1.0
 */

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./FMK_TIM.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKTIM_ConfigPrivate.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
#include "Constant.h"

#include "Library/SafeMem/SafeMem.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
// ********************************************************************
// *                      Types
// ********************************************************************

//-----------------------------ENUM TYPES-----------------------------//
typedef enum 
{
    FMKTIM_BSP_CB_PERIOD_ELAPSED = 0x00,
    FMKTIM_BSP_CB_IC_CAPTURE,
    FMKTIM_BSP_CB_OC_DELAY_ELAPSED,
    FMKTIM_BSP_CB_PWM_PULSE_FINISHED,

    FMKTIM_BSP_CB_NB,
} t_eFMKTIM_BspEvent;
/**< Enum  for channel state */
typedef enum
{
    FMKTIM_CHNLST_DISACTIVATED = 0x0U,       /**< the channel is disactivated by software, not running */
    FMKTIM_CHNLST_ACTIVATED,                 /**< The channel is acitvated by software, is running */

    FMKTIM_CHNLST_NB                         /**< Number of channel state */
} t_eFMKTIM_ChnlState;
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------TYPEDEF TYPES---------------------------//
//-----------------------------STRUCT TYPES---------------------------//
/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
typedef struct 
{
    t_uint32 * BufferAdd1_pu32; /**< Dma Buffer Address 1 */
    t_uint32 * BufferAdd2_pu32; /**< Dma Buffer Address 2 */
    t_uint16 bufferLen_u16;
    t_eFMKCPU_DmaRqst RqstId_e;
} t_sFMKTIM_ChnlDmaInfo;
/**< Structure of information on a timer-channel*/
typedef struct
{
    t_eFMKTIM_ChnlState State_e;                        /**< State of the channel */
    t_eFMKTIM_ChnlRunMode RunMode_e;                    /**< Run mode for the channel */
    t_sFMKTIM_ChnlDmaInfo DmaInfo_ps;
    t_uint16 ErrState_u16;                /**< Error state of the channel */
    t_cbFMKTIM_InterruptLine *chnl_cb;                  /**< Callback function of the channel */
    t_bool IsChnlConfigure_b;                           /**< Wether or not the channel has beeen configured */
    
} t_sFMKTIM_ChnlInfo;

/**< Structure of information on a timer*/
typedef struct
{
    TIM_HandleTypeDef bspTimer_s;                       /**< The Timer structure for HAL STM32*/
    t_eFMKTIM_HwTimerCfg HwCfg_e;                       /**< The hardware configuration of the timer */
    t_sFMKTIM_ChnlInfo Channel_as[FMKTIM_CHANNEL_NB];   /**< Channels info structure */
    const t_eFMKCPU_IRQNType c_IRQNType_e;              /**< IRQN type related to the timer */
    const t_eFMKCPU_ClockPort c_clock_e;                /**< RCC clock related to the timer */
    t_uint16 timerFreqMHz_u32;                              /**< Timer frequency in Mhz */
    //const t_eFMKCPU_DmaRqst c_RqstDma_e;               /**< RCC clock related to the timer */
    t_bool IsTimerRunning_b;                            /**< Flag for timer is runnning */
    t_bool isConfigured_b;                              /**< flag timer is configured */  
    t_bool IsNVICTimerEnable_b;                         /**< flag timer NVCIC enable or not */

} t_sFMKTIM_TimerInfo;

// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
static t_eCyclicModState g_FmkTim_ModState_e = STATE_CYCLIC_CFG;

/* CAUTION : Automatic generated code section for Timer Configuration: Start */
/**< timer information variable */
t_sFMKTIM_TimerInfo g_TimerInfo_as[FMKTIM_TIMER_NB] = {
    {
        // Timer_1
        .bspTimer_s.Instance = TIM1,
        .c_clock_e = FMKCPU_RCC_CLK_TIM1,
        .c_IRQNType_e = FMKCPU_NVIC_TIM1_UP_TIM16_IRQN
    },
    {
        // Timer_2
        .bspTimer_s.Instance = TIM2,
        .c_clock_e = FMKCPU_RCC_CLK_TIM2,
        .c_IRQNType_e = FMKCPU_NVIC_TIM2_IRQN
    },
    {
        // Timer_3
        .bspTimer_s.Instance = TIM3,
        .c_clock_e = FMKCPU_RCC_CLK_TIM3,
        .c_IRQNType_e = FMKCPU_NVIC_TIM3_IRQN
    },
    {
        // Timer_4
        .bspTimer_s.Instance = TIM4,
        .c_clock_e = FMKCPU_RCC_CLK_TIM4,
        .c_IRQNType_e = FMKCPU_NVIC_TIM4_IRQN
    },
    {
        // Timer_5
        .bspTimer_s.Instance = TIM5,
        .c_clock_e = FMKCPU_RCC_CLK_TIM5,
        .c_IRQNType_e = FMKCPU_NVIC_TIM5_IRQN
    },
    {
        // Timer_6
        .bspTimer_s.Instance = TIM6,
        .c_clock_e = FMKCPU_RCC_CLK_TIM6,
        .c_IRQNType_e = FMKCPU_NVIC_TIM6_DAC_IRQN
    },
    {
        // Timer_7
        .bspTimer_s.Instance = TIM7,
        .c_clock_e = FMKCPU_RCC_CLK_TIM7,
        .c_IRQNType_e = FMKCPU_NVIC_TIM7_DAC_IRQN
    },
    {
        // Timer_8
        .bspTimer_s.Instance = TIM8,
        .c_clock_e = FMKCPU_RCC_CLK_TIM8,
        .c_IRQNType_e = FMKCPU_NVIC_TIM8_BRK_IRQN
    },
    {
        // Timer_15
        .bspTimer_s.Instance = TIM15,
        .c_clock_e = FMKCPU_RCC_CLK_TIM15,
        .c_IRQNType_e = FMKCPU_NVIC_TIM1_BRK_TIM15_IRQN
    },
    {
        // Timer_16
        .bspTimer_s.Instance = TIM16,
        .c_clock_e = FMKCPU_RCC_CLK_TIM16,
        .c_IRQNType_e = FMKCPU_NVIC_TIM1_UP_TIM16_IRQN
    },
    {
        // Timer_17
        .bspTimer_s.Instance = TIM17,
        .c_clock_e = FMKCPU_RCC_CLK_TIM17,
        .c_IRQNType_e = FMKCPU_NVIC_TIM1_TRG_COM_TIM17_IRQN
    },
    {
        // Timer_20
        .bspTimer_s.Instance = TIM20,
        .c_clock_e = FMKCPU_RCC_CLK_TIM20,
        .c_IRQNType_e = FMKCPU_NVIC_TIM20_BRK_IRQN
    },
};

/* CAUTION : Automatic generated code section for Timer Configuration: End */
/**< In Pulses Mode when the timer is Launch hardware make a Interruption */
static t_bool g_timerPeriodPwm_ab[FMKTIM_TIMER_NB];
/** Only One Channel Has the Right to be in Pulses Mode */
static t_bool g_isPwmFinitePulseSet_ab[FMKTIM_TIMER_NB];
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
 *
 *	@brief      Function to set the bsp timer init container 
 *  @note       Depending on f_hwTimCfg_e and other variable, 
 *              this function filled f_timer_ps with cfg variable.\n
 *              This function set the rcc clock if needed and call HAL_Init function
 *
 *	@param[in]  f_timer_ps            : enum for the timer,value from @ref t_sFMKTIM_TimerInfo
 *	@param[in]  f_hwTimCfg_e           : enum for the hardware timer cfg,value from @ref t_eFMKTIM_HwTimerCfg
 *	@param[in]  f_InfoInit_u32       : the prescaler for the clock timer reference
 *	@param[in]  f_timerCfg_pv         : Specific Configuration for timer Init 
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
 *
 */
static t_eReturnCode s_FMKTIM_Set_BspTimerInit( t_sFMKTIM_TimerInfo * f_timer_ps,
                                                t_eFMKTIM_HwTimerCfg f_hwTimCfg_e,
                                                t_uint32 f_InfoInit_u32,
                                                void * f_timerCfg_pv);
/**
    *
    *	@brief      Configure a timer channel in PWM configuration.\n
    *   @note       First, this configuration set the bsp timer cfg in PWM mode.\n
    *               Once it's done, this function configure the bsp channel in PWM mode too.\n
    *               IMPORTANT, the PWM generation is based on a timer configuration which share
    *               multiple channels, ina sense that, frequency is shared by all PWM channels.\n
    *               In result, the modification of the timer configuration reverbate for all channels.\n          
    *
    *	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
    *	@param[in]  f_channel_e            : enum value for channel, , value from @ref f_channel_e
    *	@param[in]  f_pwmFreq_u32          : the frequency timer.
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
    */
static t_eReturnCode s_FMKTIM_Set_PwmChannelCfg(t_sFMKTIM_TimerInfo * f_timerInfo_ps,
                                                t_eFMKTIM_InterruptChnl f_channel_e, 
                                                t_uint32 f_pwmFreq_u32);
/**
    *
    *	@brief      Configure a timer channel in Encoder configuration.\n
    *   @note       
    *
    *	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
    *	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
    */
static t_eReturnCode s_FMKTIM_Set_EcdrChannelCfg(   t_sFMKTIM_TimerInfo * f_timerInfo_ps,
                                                    t_sFMKTIM_EcdrCfg * f_EcdrCfg_ps,
                                                    t_uint32 f_ARRValue_u32);
/**
*
*	@brief      Get Bsp Information from Cfg and Filled Bsp structure.\n
*   @note       
*
*	@param[in]  f_EcdrCdg_ps           : Software Configuration for Encoders
*	@param[in]  f_BspEcdrInit_ps           : Bsp Configuration for Encoders
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKTIM_FilledBspEcdrInit(t_sFMKTIM_EcdrCfg * f_EcdrCdg_ps,
                                                TIM_Encoder_InitTypeDef * f_BspEcdrInit_ps);
                                                
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
    *	@param[in]  f_timer_e              : enum value for the priority, value from @ref t_eFMKTIM_Timer
    *	@param[in]  f_channel_e            : enum value for the channel, value from @ref t_eFMKTIM_InterruptChnl
    *	@param[in]  f_MeasTrigger_e        : trigger for interruption, value from @ref t_eFMKTIM_ChnlMeasTrigger
    *	@param[in]  f_ITChannel_cb         : call back function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *  @retval RC_ERROR_NOT_ALLOWED              @ref RC_ERROR_NOT_ALLOWED
    */
    static t_eReturnCode s_FMKTIM_Set_ICChannelCfg( t_eFMKTIM_Timer f_timer_e,
                                                    t_eFMKTIM_InterruptChnl f_channel_e, 
                                                    t_eFMKTIM_ChnlMeasTrigger f_MeasTrigger_e,
                                                    t_cbFMKTIM_InterruptLine f_ITChannel_cb);
/**
*
*	@brief    Configure a timer channel on event configuration.\n
*   @note     This function initialize the timer in event configuration if the
*             timer is not configured yet.\n
*             Once the timer configure is done, update the channel state using function 
*             "FMKTIM_Set_EvntTimerState" and every f_periodms_u32 callback function is called.\n
*             IMPORTANT, In hardware this is the Timer which manage the interruption with ARR register,
*             In software this is channel structure who manage interruption to make all timer identical 
*             in just in variable.\n
*
*	@param[in]  f_evntChannel_e           : enum value for event channel, value from @ref f_timer_e
*	@param[in]  f_periodms_u32            : period before calling function, in millisecond
*	@param[in]  f_ITChannel_cb            : callback function to call
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
*  @retval RC_ERROR_NOT_ALLOWED              @ref RC_ERROR_NOT_ALLOWED
*/
static t_eReturnCode s_FMKTIM_Set_EvntChannelCfg(t_eFMKTIM_Timer f_Timer_e,
                                               t_eFMKTIM_InterruptChnl chnl_e,
                                               t_uint32 f_periodMs_u32,
                                               t_cbFMKTIM_InterruptLine f_ITChannel_cb);
/**
*
*	@brief      Set a InterruptLine  state ON/OFF.\n
*   @note       Using HAL_TIM function & Run mode Configured previously 
*               in API CfgF Function, we start_poll/It/Dma the Line
*           
*
*	@param[in]  f_ITLine_e              : enum value for the timer, value from @ref t_eFMKTIM_InterruptLineIO
*	@param[in]  f_EcdrState_e            : enum value for the channel, value from @ref t_eFMKTIM_EcdrStartOption
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*/
static t_eReturnCode s_FMKTIM_Set_ICOpeState(   t_eFMKTIM_Timer         f_timer_e,
                                                t_eFMKTIM_InterruptChnl f_chnl_e,
                                                t_sFMKTIM_ICOpe         f_ICOpe_s,
                                                t_uint8                 f_mask_u8);

/**
*
*	@brief      Set a InterruptLine  state ON/OFF.\n
*   @note       Using HAL_TIM function & Run mode Configured previously 
*               in API CfgF Function, we start_poll/It/Dma the Line
*           
*
*	@param[in]  f_ITLine_e              : enum value for the timer, value from @ref t_eFMKTIM_InterruptLineIO
*	@param[in]  f_EcdrState_e            : enum value for the channel, value from @ref t_eFMKTIM_EcdrStartOption
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*/
static t_eReturnCode s_FMKTIM_Set_EcdrOpeState( t_eFMKTIM_Timer   f_timer_e,
                                                t_eFMKTIM_EcdrOpe f_EcdrOpe,
                                                t_uint8           f_mask_u8);
/**
*
*	@brief      Set a InterruptLine  state ON/OFF.\n
*   @note       Using HAL_TIM function & Run mode Configured previously 
*               in API CfgF Function, we start_poll/It/Dma the Line
*           
*
*	@param[in]  f_ITLine_e              : enum value for the timer, value from @ref t_eFMKTIM_InterruptLineIO
*	@param[in]  f_EcdrState_e            : enum value for the channel, value from @ref t_eFMKTIM_EcdrStartOption
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*/
static t_eReturnCode s_FMKTIM_GetEcdrARRValue(  t_eFMKTIM_EcdrMode f_EcdrMode_e,
                                                t_uint32 f_rqstArrValue_u32,
                                                t_uint32 * f_ArrValue_pu32);

/**
*
*	@brief      Set a InterruptLine  state ON/OFF.\n
*   @note       Using HAL_TIM function & Run mode Configured previously 
*               in API CfgF Function, we start_poll/It/Dma the Line
*           
*
*	@param[in]  f_ITLine_e              : enum value for the timer, value from @ref t_eFMKTIM_InterruptLineIO
*	@param[in]  f_EcdrState_e            : enum value for the channel, value from @ref t_eFMKTIM_EcdrStartOption
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*/
static t_eReturnCode s_FMKTIM_Set_EvntOpeState( t_eFMKTIM_Timer   f_timer_e,
                                                t_eFMKTIM_InterruptChnl f_chnl_e,
                                                t_eFMKTIM_EvntOpe f_EvntOpe,
                                                t_uint8                 f_mask_u8);
/**
*
*	@brief      Set a InterruptLine  state ON/OFF.\n
*   @note       Using HAL_TIM function & Run mode Configured previously 
*               in API CfgF Function, we start_poll/It/Dma the Line
*           
*
*	@param[in]  f_ITLine_e              : enum value for the timer, value from @ref t_eFMKTIM_InterruptLineIO
*	@param[in]  f_EcdrState_e            : enum value for the channel, value from @ref t_eFMKTIM_EcdrStartOption
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*/
static t_eReturnCode s_FMKTIM_Set_PwmOpeState( t_eFMKTIM_Timer   f_timer_e,
                                                t_eFMKTIM_InterruptChnl f_chnl_e,
                                                t_sFMKTIM_PwmOpe f_PwmOpe_s,
                                                t_uint8 f_maskUpdate_u8);                                     
/**
 *
 *	@brief      Function to set the state ON/OFF of timer channel
 *
 *	@param[in]  f_timer_e              : enum value for the priority, value from @ref t_eFMKTIM_Timer
 *	@param[in]  f_channel_e            : enum value for the channel, value from @ref t_eFMKTIM_InterruptChnl
 *	@param[in]  f_chnlState_e          : The state of the timer.\n
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
 *
 */
static t_eReturnCode s_FMKTIM_Set_HwChannelState(t_eFMKTIM_Timer f_timer_e,
                                                  t_eFMKTIM_InterruptChnl f_channel_e,
                                                  t_eFMKTIM_ChnlState f_chnlState_e);

/**
 *
 *	@brief      Function to redirect all callback function.\n
 *  @note       Every HAL callback call this function, thsi function redirect to the right
 *              user function depending on which timer is called
 *
 *	@param[in]  f_timerIstce_ps         : bsp instance timer which make interruption
 *	@param[in]  f_HwTimcfg_e            : the timer configuration 
 *	@param[in]  f_chnlState_e           : The state of the timer.\n
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *
 */
static void s_FMKTIM_BspRqst_InterruptMngmt(TIM_HandleTypeDef *f_timerIstce_ps, t_eFMKTIM_BspEvent f_cbEvent_e);
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
static t_eReturnCode s_FMKTIM_Get_CCRxValue(t_eFMKTIM_Timer f_timer_e, 
                                            t_eFMKTIM_InterruptChnl f_channel_e,
                                            t_uint32 * f_comparedValue_pu32);

/**
 *
 *	@brief      Perform all cyclic operation
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 */
static t_eReturnCode s_FMKTIM_Operational(void);


/**
 *
 *	@brief      Perform Diagnostic on Timer and channels
 *  @note       If a error is detected on Timer, every channel used from this timer 
 *              inherit the error.\n
 * 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE

 */
static t_eReturnCode s_FMKTIM_PerformDiagnostic(void);
/**
*
*	@brief      Function to get the bsp channel
*
*	@param[in]  f_channel_e              : enum value for the channel, value from @ref t_eFMKTIM_InterruptChnl
*	@param[in]  f_bspChnl_pu32           : storage for bsp channel.\n
*
*  @retval RC_OK                             @ref RC_OK
*
*/
static t_eReturnCode s_FMKTIM_Get_BspChannel(t_eFMKTIM_InterruptChnl f_channel_e, t_uint32 *f_bspChnl_pu32);
/**
*
*	@brief      Function to get the bsp Encoder Mode
*
*	@param[in]  f_EcdrMode_e       : enum value for the Encoder Mode, value from @ref t_eFMKTIM_EcdrMode
*	@param[in]  f_bspEcdrMode_pu32  : storage for bsp Encoder Mode.\n
*
*  @retval RC_OK                             @ref RC_OK
*
*/
static t_eReturnCode s_FMKTIM_GetBspEcdrMode(t_eFMKTIM_EcdrMode f_EcdrMode_e, t_uint32 *f_bspEcdrMode_pu32);
/**
*
*	@brief      Function to get the bsp Encoder Mode
*
*	@param[in]  f_ICEcdrSelect_e      : enum value for the Encoder IC Selection, value from @ref t_eFMKTIM_ICSelection
*	@param[in]  f_bspEcdrMode_pu32     : storage for bsp IC Selection.\n
*
*  @retval RC_OK                             @ref RC_OK
*
*/
static t_eReturnCode s_FMKTIM_GetBspEcdrSelection(t_eFMKTIM_ICSelection f_ICEcdrSelect_e, t_uint32 *f_bspICEcdrSelect_pu32);
/**
*
*	@brief      Function to get the bsp Encoder Mode
*
*	@param[in]  f_ICEcdrPolarity_e      : enum value for the Encoder IC Selection, value from @ref t_eFMKTIM_ICSelection
*	@param[in]  f_bspICEcdrPolarity_pu32     : storage for bsp IC Selection.\n
*
*  @retval RC_OK                             @ref RC_OK
*
*/
static t_eReturnCode s_FMKTIM_GetBspEcdrPolarity(t_eFMKTIM_EcdrInPolarity f_ICEcdrPolarity_e, t_uint32 *f_bspICEcdrPolarity_pu32);

/**
 *
 *	@brief      Function to get the bsp IRQN enum
 *
 *	@param[in]  f_IRQN_e              : enum value for the priority, value from @ref t_eFMKCPU_IRQNType
 *	@param[in]  f_bspIRQN_pe          : storage for NVIC priority.\n
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKTIM_Get_BspICTrigger(t_eFMKTIM_ChnlMeasTrigger f_MeasTrigger_e, t_uint32 *f_bspMeasTrigger_u32);
/**
 *
 *	@brief      Function Timer and channel from a InterruptLine
 *
 *	@param[in]  f_ITLineType_e           : enum value for the type of interruptline, value from @ref t_eFMKTIM_InterruptLineType
 *	@param[in]  ITLine_u                 : union value for the interruptline, value from @ref t_uFMKTIM_InterruptLine
 *	@param[in]  f_timer_pe                : pointor enum value for containing timer, value from @ref t_eFMKTIM_Timer
 *	@param[in]  f_channel_pe              : pointor enum value for containing timer, value from @ref t_eFMKTIM_InterruptChnl
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKTIM_Get_TimChnlFromITLine(t_eFMKTIM_InterruptLineType f_ITLineType_e,
                                                    t_uint32                    f_ITLine_u32,    
                                                    t_eFMKTIM_Timer             *f_timer_pe,
                                                    t_eFMKTIM_InterruptChnl     *f_channel_pe);

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
t_eReturnCode FMKTIM_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 timIndex_u8;
    t_uint8 chnlIndex_u8;
    t_uint16 sysClkValueMHz_u16;
    t_uint16 timClkValueMHz_u16;
    t_eFMKCPU_SysClkOsc oscTimerSrc_e;
    t_sFMKTIM_TimerInfo * timerInfo_ps;
    t_sFMKTIM_ChnlInfo * chnlInfo_ps;

    Ret_e = FMKCPU_GetSysClkValue(FMKCPU_SYS_CLOCK_SYSTEM, &sysClkValueMHz_u16);

    if(Ret_e == RC_OK)
    {
        for (timIndex_u8 = (t_uint8)0 ; (timIndex_u8 < (t_eFMKTIM_Timer)FMKTIM_TIMER_NB) && (Ret_e == RC_OK) ; timIndex_u8++)
        {
            timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[timIndex_u8]);

            timerInfo_ps->IsNVICTimerEnable_b = (t_bool)False;
            timerInfo_ps->isConfigured_b = (t_bool)False;
            timerInfo_ps->IsTimerRunning_b    = (t_bool)False;
            timerInfo_ps->HwCfg_e = FMKTIM_HWTIM_CFG_NB;

            Ret_e = FMKCPU_GetOscRccSrc(timerInfo_ps->c_clock_e, &oscTimerSrc_e);

            if(Ret_e == RC_OK)
            {
                Ret_e = FMKCPU_GetSysClkValue(oscTimerSrc_e, &timClkValueMHz_u16);
            }
            if(Ret_e == RC_OK)
            {
                if(sysClkValueMHz_u16 > timClkValueMHz_u16)
                {
                    timerInfo_ps->timerFreqMHz_u32 = (t_uint32)((t_uint32)2 * (t_uint32)timClkValueMHz_u16);
                }
                else 
                {
                    timerInfo_ps->timerFreqMHz_u32 = (t_uint32)(timClkValueMHz_u16);
                }
            

                for (chnlIndex_u8 = (t_uint8)0 ; chnlIndex_u8 < (t_eFMKTIM_InterruptChnl)FMKTIM_CHANNEL_NB ; chnlIndex_u8++)
                {
                    chnlInfo_ps = (t_sFMKTIM_ChnlInfo *)(&timerInfo_ps->Channel_as[chnlIndex_u8]);

                    chnlInfo_ps->chnl_cb = NULL_FONCTION;
                    SETBIT_16B(chnlInfo_ps->ErrState_u16, FMKTIM_ERRSTATE_OK);
                    chnlInfo_ps->IsChnlConfigure_b =  (t_bool)False;
                    chnlInfo_ps->RunMode_e = FMKTIM_LINE_RUNMODE_POLLING;
                    chnlInfo_ps->State_e = FMKTIM_CHNLST_DISACTIVATED;
                    chnlInfo_ps->DmaInfo_ps.BufferAdd1_pu32 = (t_uint32 *)NULL;
                    chnlInfo_ps->DmaInfo_ps.BufferAdd2_pu32 = (t_uint32 *)NULL;
                    chnlInfo_ps->DmaInfo_ps.bufferLen_u16 = (t_uint16)0;
                }
            }
        }
    }

    return Ret_e;
}
/*********************************
 * FMKTIM_Cyclic
 *********************************/
t_eReturnCode FMKTIM_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch (g_FmkTim_ModState_e)
    {
        case STATE_CYCLIC_CFG:
        {
            g_FmkTim_ModState_e = STATE_CYCLIC_WAITING;
            break;
        }
        case STATE_CYCLIC_WAITING:
        {
            // nothing to do, just wait all module are Ope
            break;
        }
        case STATE_CYCLIC_PREOPE:
        {
            g_FmkTim_ModState_e = STATE_CYCLIC_OPE;
            break; 
        }
        case STATE_CYCLIC_OPE:
        {
            Ret_e = s_FMKTIM_Operational();
            if(Ret_e < RC_OK)
            {
                g_FmkTim_ModState_e = STATE_CYCLIC_ERROR;
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
 * FMKTIM_GetState
 *********************************/
t_eReturnCode FMKTIM_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_FmkTim_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * FMKTIM_SetState
 *********************************/
t_eReturnCode FMKTIM_SetState(t_eCyclicModState f_State_e)
{

    g_FmkTim_ModState_e = f_State_e;

    return RC_OK;
}

/*********************************
 * FMKTIM_Set_PWMMLineCfg
 *********************************/
t_eReturnCode FMKTIM_Set_PWMLineCfg(    t_eFMKTIM_InterruptLineIO f_InterruptLine_e,
                                        t_uint32 f_pwmFreq_u32,
                                        t_eFMKTIM_PwmMode f_PwmMode_e,
                                        t_cbFMKTIM_InterruptLine * f_PwmPulseFinished_pcb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_Timer timer_e;
    t_eFMKTIM_InterruptChnl chnl_e;

    if (f_InterruptLine_e >= FMKTIM_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    
    if(Ret_e == RC_OK)
    {
        timer_e = c_FmkTim_ITLineIOMapp_as[f_InterruptLine_e].timer_e;
        chnl_e = c_FmkTim_ITLineIOMapp_as[f_InterruptLine_e].channel_e;

        if(g_TimerInfo_as[timer_e].isConfigured_b == (t_bool)False)
        {
            Ret_e = s_FMKTIM_Set_BspTimerInit(&g_TimerInfo_as[timer_e],
                                                FMKTIM_HWTIM_CFG_PWM,
                                                f_pwmFreq_u32,
                                                (void *)NULL);
        }

        if(f_PwmMode_e == FMKTIM_PWM_MODE_FINITE_PULSE)
        {
            if(g_isPwmFinitePulseSet_ab[timer_e] == (t_bool)False)
            {   
                g_isPwmFinitePulseSet_ab[timer_e] = (t_bool)True;
            }
            else 
            {
                Ret_e = RC_ERROR_NOT_ALLOWED;
            }
        }
        

        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKTIM_Set_PwmChannelCfg( (&g_TimerInfo_as[timer_e]), 
                                                chnl_e,
                                                f_pwmFreq_u32);
        }

        if(Ret_e == RC_OK)
        {
            g_TimerInfo_as[timer_e].Channel_as[chnl_e].chnl_cb = f_PwmPulseFinished_pcb;
        }
    }
    return Ret_e;
}

/*********************************
 * FMKTIM_Set_EcdrLineCfg
 *********************************/
t_eReturnCode FMKTIM_Set_EcdrLineCfg(t_eFMKTIM_InterruptLineIO f_InterruptLine_e,
                                            t_sFMKTIM_EcdrCfg f_EcdrCfg_s,
                                            t_uint32 f_ARRValue_u32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_Timer timer_e;
    t_sFMKTIM_TimerInfo * timerInfo_ps;
    t_eFMKTIM_InterruptChnl chnl_e;
    

    if(f_InterruptLine_e >= FMKTIM_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        timer_e = c_FmkTim_ITLineIOMapp_as[f_InterruptLine_e].timer_e;
        chnl_e = c_FmkTim_ITLineIOMapp_as[f_InterruptLine_e].channel_e;
        timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[timer_e]);

        //----- According Bsp, timer must the CHANNEL 1 and 2 use for Encoder -----//
        if((chnl_e != FMKTIM_CHANNEL_1)
        || (timerInfo_ps->Channel_as[FMKTIM_CHANNEL_1].IsChnlConfigure_b == (t_bool)True)
        || (timerInfo_ps->Channel_as[FMKTIM_CHANNEL_2].IsChnlConfigure_b == (t_bool)True))
        {
            Ret_e = RC_WARNING_WRONG_CONFIG;
        }
       
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKTIM_Set_EcdrChannelCfg(timerInfo_ps,
                                                &f_EcdrCfg_s,
                                                f_ARRValue_u32);
        }
        if(Ret_e == RC_OK)
        {
            //------ Update Information ------//
            timerInfo_ps->Channel_as[FMKTIM_CHANNEL_1].IsChnlConfigure_b = (t_bool)True;
            timerInfo_ps->Channel_as[FMKTIM_CHANNEL_1].RunMode_e = FMKTIM_LINE_RUNMODE_POLLING;


            timerInfo_ps->Channel_as[FMKTIM_CHANNEL_2].IsChnlConfigure_b = (t_bool)True;
            timerInfo_ps->Channel_as[FMKTIM_CHANNEL_2].RunMode_e = FMKTIM_LINE_RUNMODE_POLLING;
        }    
        else 
        {
            SETBIT_16B(timerInfo_ps->Channel_as[FMKTIM_CHANNEL_2].ErrState_u16, FMKTIM_ERRSTATE_INIT_FAILED);
            SETBIT_16B(timerInfo_ps->Channel_as[FMKTIM_CHANNEL_1].ErrState_u16, FMKTIM_ERRSTATE_INIT_FAILED);
        }
        
    }
    
    return Ret_e;
}

/*********************************
 * FMKTIM_Get_EncoderValues
 *********************************/
t_eReturnCode FMKTIM_Get_EncoderValues( t_eFMKTIM_InterruptLineIO f_EcdrLine_e, 
                                        t_uint32 *f_position_pu32,
                                        t_uint8 *f_direction_pu8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_Timer timer_e;
    t_eFMKTIM_InterruptChnl chnl_e;
    t_sFMKTIM_TimerInfo * timerInfo_ps;

    if((f_direction_pu8 == (t_uint8 *)NULL)
    || f_position_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_FmkTim_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(f_EcdrLine_e >= FMKTIM_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        timer_e = c_FmkTim_ITLineIOMapp_as[f_EcdrLine_e].timer_e;
        chnl_e = c_FmkTim_ITLineIOMapp_as[f_EcdrLine_e].channel_e;
        timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[timer_e]);

        //--- check running validity
        if(timerInfo_ps->Channel_as[chnl_e].State_e != FMKTIM_CHNLST_ACTIVATED)
        {
            Ret_e = RC_WARNING_BUSY;
        }
        if(Ret_e == RC_OK)
        {
            *f_position_pu32 = (t_uint32)(timerInfo_ps->bspTimer_s.Instance->CNT);
            *f_direction_pu8 = (t_uint8)(timerInfo_ps->bspTimer_s.Instance->CR1);
        }
    }
    return Ret_e;
}
/*********************************
 * FMKTIM_Set_ICLineCfg
 *********************************/
t_eReturnCode FMKTIM_Set_ICLineCfg(t_eFMKTIM_InterruptLineIO f_InterruptLine_e,
                                         t_eFMKTIM_ChnlMeasTrigger f_MeasTrigger_e,
                                         t_cbFMKTIM_InterruptLine  * f_ITChannel_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_Timer timer_e;
    t_eFMKTIM_InterruptChnl chnl_e;

    if(f_ITChannel_cb == (t_cbFMKTIM_InterruptLine *)NULL_FONCTION)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if( (f_MeasTrigger_e >= FMKTIM_LINE_MEAS_NB)
    || (f_InterruptLine_e >= FMKTIM_INTERRUPT_LINE_IO_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get timer/channel information---------//
        timer_e = c_FmkTim_ITLineIOMapp_as[f_InterruptLine_e].timer_e;
        chnl_e = c_FmkTim_ITLineIOMapp_as[f_InterruptLine_e].channel_e;
        //---------Call Configuration function---------//
        Ret_e = s_FMKTIM_Set_ICChannelCfg(timer_e,
                                          chnl_e,
                                          f_MeasTrigger_e,
                                          f_ITChannel_cb);
    }
    return Ret_e;
}

/*********************************
 * FMKTIM_Set_EvntTimerCfg
 *********************************/
t_eReturnCode FMKCP_Set_EvntTimerCfg(   t_eFMKTIM_InterruptLineEvnt f_EvntITLine_e,
                                        t_uint32 f_periodms_u32,
                                        t_cbFMKTIM_InterruptLine f_ITChannel_cb)
{
    /********************************
     *   Some useful information for Evnt generation
     *   In FMKTIM_ConfigPrivate, 
     * 
     ********************************/
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_Timer timer_e;
    t_eFMKTIM_InterruptChnl chnl_e;

    if (f_EvntITLine_e >= FMKTIM_INTERRUPT_LINE_EVNT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_ITChannel_cb == (t_cbFMKTIM_InterruptLine *)NULL_FONCTION)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get timer/channel information---------//
        timer_e = c_FmkTim_ITLineEvntMapp_as[f_EvntITLine_e].timer_e;
        chnl_e = c_FmkTim_ITLineEvntMapp_as[f_EvntITLine_e].channel_e;
        //---------Get Event Init Function---------//
        Ret_e = s_FMKTIM_Set_EvntChannelCfg(timer_e,
                                            chnl_e,
                                            f_periodms_u32,
                                            f_ITChannel_cb);
    }
    

    return Ret_e;
}

/*********************************
 * FMKTIM_AddInterruptCallback
 *********************************/
    t_eReturnCode FMKTIM_AddInterruptCallback(t_eFMKTIM_InterruptLineIO f_InterruptLine_e,
                                             t_cbFMKTIM_InterruptLine *f_ITChannel_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_Timer timer_e;
    t_eFMKTIM_InterruptChnl chnl_e;

    if(f_InterruptLine_e >= FMKTIM_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_ITChannel_cb == (t_cbFMKTIM_InterruptLine *)NULL_FONCTION)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get timer/channel information---------//
        timer_e = c_FmkTim_ITLineIOMapp_as[f_InterruptLine_e].timer_e;
        chnl_e = c_FmkTim_ITLineIOMapp_as[f_InterruptLine_e].channel_e;

        //---------See if the configuration of the timer has alrerady been made---------//
        if (g_TimerInfo_as[timer_e].Channel_as[chnl_e].IsChnlConfigure_b != (t_bool)True 
        || g_TimerInfo_as[timer_e].isConfigured_b != (t_bool)True)
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
        else
        {
            //---------Update channel Run mode and Add Callback---------//
            g_TimerInfo_as[timer_e].Channel_as[chnl_e].RunMode_e = FMKTIM_LINE_RUNMODE_INTERRUPT;
            g_TimerInfo_as[timer_e].Channel_as[chnl_e].chnl_cb = f_ITChannel_cb;
        }
    }
    
    
    
    return Ret_e;
}

/*********************************
 * FMKTIM_Set_InterruptLineOpe
 *********************************/
t_eReturnCode FMKTIM_Set_InterruptLineOpe(  t_eFMKTIM_InterruptLineType f_ITLineType_e,
                                            t_uint8 f_IT_line_u8,
                                            t_uFMKTIM_ITLineOpe f_ITLineOpe_u,
                                            t_uint8 f_mask_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_Timer timer_e = FMKTIM_TIMER_NB;
    t_eFMKTIM_InterruptChnl chnl_e = FMKTIM_CHANNEL_NB;
    t_sFMKTIM_TimerInfo * timerInfo_ps;

    if((f_ITLineType_e >= FMKTIM_INTERRUPT_LINE_TYPE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get TImer/Channel frol InterruptLine---------//
        Ret_e = s_FMKTIM_Get_TimChnlFromITLine(f_ITLineType_e,
                                               f_IT_line_u8,
                                               &timer_e,
                                               &chnl_e);

        timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[timer_e]);

        if((timerInfo_ps->isConfigured_b == (t_bool)False)
        || (timerInfo_ps->Channel_as[chnl_e].IsChnlConfigure_b == (t_bool)False))
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
        if(Ret_e == RC_OK)
        {
            switch(timerInfo_ps->HwCfg_e)
            {
                case FMKTIM_HWTIM_CFG_IC:
                {
                    Ret_e = s_FMKTIM_Set_ICOpeState(timer_e,
                                                    chnl_e,
                                                    (t_sFMKTIM_ICOpe)f_ITLineOpe_u.ICOpe_s,
                                                    f_mask_u8);
                    break;
                }
                case FMKTIM_HWTIM_CFG_ECDR:
                {
                    Ret_e = s_FMKTIM_Set_EcdrOpeState(  (t_eFMKTIM_InterruptLineIO)f_IT_line_u8,
                                                        (t_eFMKTIM_EcdrOpe)f_ITLineOpe_u.EncoderOpe_e,
                                                        f_mask_u8);
                    break;
                }
                case FMKTIM_HWTIM_CFG_EVNT:
                {
                    Ret_e = s_FMKTIM_Set_EvntOpeState(  timer_e,
                                                        chnl_e,
                                                        (t_eFMKTIM_EvntOpe)f_ITLineOpe_u.EvntOpe_e,
                                                        f_mask_u8);
                    break;
                }
                case FMKTIM_HWTIM_CFG_PWM:
                {
                    Ret_e = s_FMKTIM_Set_PwmOpeState(   timer_e,
                                                        chnl_e,
                                                        (t_sFMKTIM_PwmOpe)f_ITLineOpe_u.PwmOpe_s,
                                                        f_mask_u8);
                    break;
                }
                case FMKTIM_HWTIM_CFG_OC:
                case FMKTIM_HWTIM_CFG_OP:
                case FMKTIM_HWTIM_CFG_DAC:
                {
                    Ret_e = RC_WARNING_NO_OPERATION;
                    break;
                }
                case FMKTIM_HWTIM_CFG_NB:
                default:
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;

            }
        }
    }

    return Ret_e;
}

/*********************************
 * FMKTIM_Get_InterruptLineValue
 *********************************/
t_eReturnCode FMKTIM_Get_InterruptLineValue(t_eFMKTIM_InterruptLineType f_ITLineType_e,
                                            t_uint8 f_IT_line_u8,
                                            t_uFMKTIM_ITLineValue * f_ITLineValue_u,
                                            t_uint8                 f_mask_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_Timer timer_e = FMKTIM_TIMER_NB;
    t_eFMKTIM_InterruptChnl chnl_e = FMKTIM_CHANNEL_NB;
    t_sFMKTIM_TimerInfo * timerInfo_ps;
    t_uint32 comparedValue_u32;

    if((f_ITLineType_e >= FMKTIM_INTERRUPT_LINE_TYPE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_ITLineValue_u == (t_uFMKTIM_ITLineValue *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get TImer/Channel frol InterruptLine---------//
        Ret_e = s_FMKTIM_Get_TimChnlFromITLine(f_ITLineType_e,
                                               f_IT_line_u8,
                                               &timer_e,
                                               &chnl_e);
    }
    if(Ret_e == RC_OK)
    {
        timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[timer_e]);

        if((timerInfo_ps->isConfigured_b == (t_bool)False)
        || (timerInfo_ps->Channel_as[chnl_e].IsChnlConfigure_b == (t_bool)False))
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
        if( (GETBIT(timerInfo_ps->Channel_as[chnl_e].ErrState_u16, FMKTIM_ERRSTATE_OK) == BIT_IS_RESET_16B)
        ||  (timerInfo_ps->Channel_as[chnl_e].State_e == FMKTIM_CHNLST_DISACTIVATED))
        {
            Ret_e = RC_WARNING_BUSY;
        }
        if(Ret_e == RC_OK)
        {
            switch(timerInfo_ps->HwCfg_e)
            {
                case FMKTIM_HWTIM_CFG_ECDR:
                {
                    if(GETBIT(f_mask_u8, FMKTIM_BIT_ECDR_DIRECTION) == BIT_IS_SET_8B)
                    {
                        f_ITLineValue_u->EncoderValue_s.direction_u8 = (t_uint8)(timerInfo_ps->bspTimer_s.Instance->CR1);
                    }
                    if(GETBIT(f_mask_u8, FMKTIM_BIT_ECDR_POSTION) == BIT_IS_SET_8B)
                    {
                        f_ITLineValue_u->EncoderValue_s.position_u32 = (t_uint32)(timerInfo_ps->bspTimer_s.Instance->CNT);
                    }
            
                    break;
                }
                
                case FMKTIM_HWTIM_CFG_PWM:
                {
                    if(GETBIT(f_mask_u8, FMKTIM_BIT_PWM_DUTYCYCLE) == BIT_IS_SET_8B)
                    {
                        Ret_e = s_FMKTIM_Get_CCRxValue(timer_e, chnl_e, &comparedValue_u32);

                        if(Ret_e == RC_OK)
                        {
                            f_ITLineValue_u->PwmValue_s.CCrxRegister_u16 = (t_uint16)(((t_float32)comparedValue_u32 * 1000) /
                                                                                (t_float32)(timerInfo_ps->bspTimer_s.Instance->ARR + 1));
                        }
                    }
                    if(GETBIT(f_mask_u8, FMKTIM_BIT_PWM_FREQUENCY) == BIT_IS_SET_8B)
                    {
                        //------ calculate frequency -----//
                        f_ITLineValue_u->PwmValue_s.frequency_u32 = (t_uint32)((t_float32)timerInfo_ps->timerFreqMHz_u32 * CST_MHZ_TO_HZ) /
                                                                        (t_float32)((timerInfo_ps->bspTimer_s.Instance->ARR + 1) *
                                                                        (timerInfo_ps->bspTimer_s.Instance->PSC + 1));
                    }
                    if(GETBIT(f_mask_u8, FMKTIM_BIT_PWM_NB_PULSES) == BIT_IS_SET_8B)
                    {
                        f_ITLineValue_u->PwmValue_s.nbPulses_u16 = (t_uint16)(timerInfo_ps->bspTimer_s.Instance->RCR - (t_uint16)1);
                    }
                    if(GETBIT(f_mask_u8, FMKTIM_BIT_PWM_CCRX_REGISTER) == BIT_IS_SET_8B)
                    {
                        Ret_e = s_FMKTIM_Get_CCRxValue(timer_e, chnl_e, &comparedValue_u32);

                        if(Ret_e == RC_OK)
                        {
                            f_ITLineValue_u->PwmValue_s.CCrxRegister_u16 = (t_uint16)comparedValue_u32;
                        }
                    }
                    break;
                }
                case FMKTIM_HWTIM_CFG_IC:
                {
                    if(GETBIT(f_mask_u8, FMKTIM_BIT_IC_FREQUENCY) == BIT_IS_SET_8B)
                    {
                        //------ calculate frequency -----//
                        f_ITLineValue_u->ICValue_s.frequency_u32 = (t_uint32)((t_float32)timerInfo_ps->timerFreqMHz_u32 * CST_MHZ_TO_HZ) /
                                                                        (t_float32)((timerInfo_ps->bspTimer_s.Instance->ARR + 1) *
                                                                        (timerInfo_ps->bspTimer_s.Instance->PSC + 1));
                    }
                    if(GETBIT(f_mask_u8, FMKTIM_BIT_IC_ARR_REGISTER) == BIT_IS_SET_8B)
                    {
                        f_ITLineValue_u->ICValue_s.ARR_Register_u32 = (t_uint32)(timerInfo_ps->bspTimer_s.Instance->ARR);
                    }
                    if(GETBIT(f_mask_u8, FMKTIM_BIT_IC_CCRX_REGISTER) == BIT_IS_SET_8B)
                    {   
                        Ret_e = s_FMKTIM_Get_CCRxValue(timer_e, chnl_e, &comparedValue_u32);

                        if(Ret_e == RC_OK)
                        {
                            f_ITLineValue_u->ICValue_s.CCRxRegister_u16 = (t_uint16)comparedValue_u32;
                        }
                    }
                    break;
                }
                case FMKTIM_HWTIM_CFG_OC:
                case FMKTIM_HWTIM_CFG_OP:
                case FMKTIM_HWTIM_CFG_DAC:
                {
                    Ret_e = RC_WARNING_NO_OPERATION;
                    break;
                }
                case FMKTIM_HWTIM_CFG_NB:
                default:
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;

            }
        }
    }

    return Ret_e;
}
/*********************************
 * FMKTIM_Get_LineErrorStatus
 *********************************/
t_eReturnCode FMKTIM_Get_LineErrorStatus(    t_eFMKTIM_InterruptLineType f_ITLineType_e,
                                                t_uint32 f_IT_line_u8,
                                                t_uint16 *f_chnlErrInfo_pu16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_Timer timer_e = FMKTIM_TIMER_NB;
    t_eFMKTIM_InterruptChnl chnl_e = FMKTIM_CHANNEL_NB;

    if(f_ITLineType_e >= FMKTIM_INTERRUPT_LINE_TYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_FmkTim_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(f_chnlErrInfo_pu16 == (t_uint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKTIM_Get_TimChnlFromITLine(f_ITLineType_e,
                                               f_IT_line_u8,
                                               &timer_e,
                                               &chnl_e);
        if(Ret_e == RC_OK)
        {
            *f_chnlErrInfo_pu16 = g_TimerInfo_as[timer_e].Channel_as[chnl_e].ErrState_u16;
        }
        
    }

    return Ret_e;
}

//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_FMKTIM_Operational
 *********************************/
static t_eReturnCode s_FMKTIM_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_uint32 SavedTime_u32 = 0;
    t_uint32 currentTime_u32 = 0;

    FMKCPU_Get_Tick(&currentTime_u32);

    if((currentTime_u32 - SavedTime_u32) > (t_uint32)FMKTIM_TIME_BTWN_DIAG_MS)
    {//perform diag on timer / chnl used
        SavedTime_u32 = currentTime_u32;
        Ret_e = s_FMKTIM_PerformDiagnostic();
    }
    // else do other thing( or nothing for now)
    
    return Ret_e;
}

/*********************************
 * s_FMKTIM_PerformDiagnostic
 *********************************/
static t_eReturnCode s_FMKTIM_PerformDiagnostic(void)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_TIM_StateTypeDef bspTimerState_e;
    t_uint16 channelErr_u16 = (t_uint16)0;
    HAL_TIM_ChannelStateTypeDef bspChnlState_e = HAL_TIM_CHANNEL_STATE_READY;
    t_uint32 bspChannel_u32 = 0;
    t_sFMKTIM_TimerInfo * timerInfo_ps;
    t_sFMKTIM_ChnlInfo * chnlInfo_ps;
    t_uint8 CLLI_u8; /**< Channel loop */
    t_uint8 TLLI_u8; /**< Timer loop  */

    for(TLLI_u8 = (t_uint8)0 ; TLLI_u8 < FMKTIM_TIMER_NB ; TLLI_u8++)
    {
        //-----------update information for loop-----------//
        timerInfo_ps = (t_sFMKTIM_TimerInfo *)&g_TimerInfo_as[TLLI_u8];

        //-----------diag for timer currently working/ Running-----------//
        if(timerInfo_ps->IsTimerRunning_b == (t_bool)True)
        {
            //-----------Timer diagnostic-----------//
            bspTimerState_e = c_FMKTIM_TimerFunc_apf[timerInfo_ps->HwCfg_e].GetTimerState_pcb(
                                    &timerInfo_ps->bspTimer_s);

            if((bspTimerState_e  != HAL_TIM_STATE_BUSY)
            && (bspTimerState_e  != HAL_TIM_STATE_READY)) // busy/ Ready means ok for stm32
            {
                //----------- associate bsp err with channel FMKTIM err-----------//
                if(bspTimerState_e  == HAL_TIM_STATE_RESET)
                {
                    SETBIT_16B(channelErr_u16, FMKTIM_ERRSTATE_NOT_CONFIGURED); 
                }
                if(bspTimerState_e  == HAL_TIM_STATE_TIMEOUT)
                {
                    SETBIT_16B(channelErr_u16, FMKTIM_ERRSTATE_TIMEOUT);
                }
                if(bspTimerState_e == HAL_TIM_STATE_ERROR)
                {
                    SETBIT_16B(channelErr_u16, HAL_TIM_STATE_ERROR);  
                }

                //-----------Propagate this error to every channel from this timer-----------//
                for(CLLI_u8 = (t_uint8)0 ; 
                    (CLLI_u8 < FMKTIM_CHANNEL_NB) 
                &&  (timerInfo_ps->Channel_as[CLLI_u8].State_e == FMKTIM_CHNLST_ACTIVATED) ; 
                    CLLI_u8++)
                {
                    timerInfo_ps->Channel_as[CLLI_u8].ErrState_u16 |= channelErr_u16;
                    RESETBIT_16B(timerInfo_ps->Channel_as[CLLI_u8].ErrState_u16, FMKTIM_ERRSTATE_OK);
                }
            }
            //-----------diag for the channel currently used-----------//
            for(CLLI_u8 = (t_uint8)0 ; CLLI_u8 < FMKTIM_CHANNEL_NB ; CLLI_u8++)
            {
                chnlInfo_ps = (t_sFMKTIM_ChnlInfo *)(&timerInfo_ps->Channel_as[CLLI_u8]);

                if(chnlInfo_ps->State_e == FMKTIM_CHNLST_ACTIVATED)
                {
                    Ret_e = s_FMKTIM_Get_BspChannel(CLLI_u8, &bspChannel_u32);

                    if(Ret_e == RC_OK)
                    {
                        bspChnlState_e = HAL_TIM_GetChannelState(&timerInfo_ps->bspTimer_s, bspChannel_u32);

                        if((bspChnlState_e != HAL_TIM_CHANNEL_STATE_BUSY)) // busy means ok
                        {
                            SETBIT_16B(chnlInfo_ps->ErrState_u16, FMKTIM_ERRSTATE_OFF_UNEXPECTED);
                        }
                    }
                }
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKTIM_Set_PwmChannelCfg
 *********************************/
static t_eReturnCode s_FMKTIM_Set_PwmChannelCfg(t_sFMKTIM_TimerInfo * f_timerInfo_ps,
                                                t_eFMKTIM_InterruptChnl f_channel_e, 
                                                t_uint32 f_pwmFreq_u32)
{
    /********************************
     *   Some useful information for PWM generation
     *   1 - ARR = Period in Init =  (((freq_timer)/ (freq_pwm * (PSC+1))) -1)
     *   For a dutycyle E [0 - 1000]
     *   2 - CCR1_2_3_4 depending on channel, set the Duty Cycle -> (DutyCyle/ 1000) * (ARR +1)
     ********************************/
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef BspRet_e = HAL_OK;
    HAL_TIM_ChannelStateTypeDef bspChannelState_e = HAL_TIM_CHANNEL_STATE_BUSY;
    TIM_OC_InitTypeDef BspOcInit_s;
    TIM_MasterConfigTypeDef masterCfg_s;
    t_uint32 bspChannel_u32 = 0;
    

    //----------Check if timer is not configured yet------------------//
    if ((f_timerInfo_ps->isConfigured_b == (t_bool)False))
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }
    //-------this timer has already been configured and cannot be used for another Type of Configuration------//
    if (f_timerInfo_ps->HwCfg_e != FMKTIM_HWTIM_CFG_PWM)
    { 
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    //-------Channel is already used------//
    if (f_timerInfo_ps->Channel_as[f_channel_e].IsChnlConfigure_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {   
        //-----Function get here only if Timer is initialized and channel not initialized yet----//
        //----Now Configure the channel in PWM mode-----//
        Ret_e = s_FMKTIM_Get_BspChannel(f_channel_e, &bspChannel_u32);

        if (Ret_e == RC_OK)
        {
            //-------see if channel state is ok-------//
            bspChannelState_e = HAL_TIM_GetChannelState(&f_timerInfo_ps->bspTimer_s, bspChannel_u32);

            if(bspChannelState_e == HAL_TIM_CHANNEL_STATE_READY)
            {
                BspOcInit_s.OCMode = TIM_OCMODE_PWM1;       // Mode PWM1
                BspOcInit_s.Pulse = 0;                     // Initial Duty Cycle à 0%
                BspOcInit_s.OCFastMode = TIM_OCFAST_DISABLE;    // Mode rapide désactivé
                BspOcInit_s.OCPolarity = TIM_OCPOLARITY_HIGH;  // Polarité normale (actif haut)
#ifdef FMKTIM_STM32_ECU_FAMILY_G
                BspOcInit_s.OCNPolarity = TIM_OCNPOLARITY_HIGH; // Non utilisé si pas de signal complémentaire
                BspOcInit_s.OCIdleState = TIM_OCIDLESTATE_RESET; // État au repos à 0
                BspOcInit_s.OCNIdleState = TIM_OCNIDLESTATE_RESET; // Non utilisé si pas de signal complémentaire
#endif
                BspRet_e = HAL_TIM_PWM_ConfigChannel(   &f_timerInfo_ps->bspTimer_s,
                                                        &BspOcInit_s,
                                                        (uint32_t)bspChannel_u32);  
                if (BspRet_e != HAL_OK)
                {
                    Ret_e = RC_ERROR_WRONG_STATE;
                }
            }
            else
            {
                Ret_e = RC_ERROR_BUSY;
            }
        }
        if(Ret_e == RC_OK)
        {
            masterCfg_s.MasterOutputTrigger = TIM_TRGO_RESET;
            masterCfg_s.MasterOutputTrigger2 = TIM_TRGO2_RESET;
            masterCfg_s.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
            BspRet_e = HAL_TIMEx_MasterConfigSynchronization(   &f_timerInfo_ps->bspTimer_s,
                                                                &masterCfg_s);

            if(BspRet_e != HAL_OK)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
        }
        if (Ret_e == RC_OK)
        { //----------Update INformation------------//
            f_timerInfo_ps->Channel_as[f_channel_e].IsChnlConfigure_b = (t_bool)True;
        }
        else 
        {
            SETBIT_16B(f_timerInfo_ps->Channel_as[f_channel_e].ErrState_u16, FMKTIM_ERRSTATE_INIT_FAILED);
        }
        
    }
    
    return Ret_e;
}

/*********************************
 * s_FMKTIM_Set_EcdrChannelCfg
 *********************************/
static t_eReturnCode s_FMKTIM_Set_EcdrChannelCfg(   t_sFMKTIM_TimerInfo * f_timerInfo_ps,
                                                    t_sFMKTIM_EcdrCfg * f_EcdrCfg_ps,
                                                    t_uint32 f_ARRValue_u32)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_uint32 computeARRVal_u32;
    TIM_Encoder_InitTypeDef bspEcdrInit_s;
    TIM_MasterConfigTypeDef masterCfg_s;

    //----------Check if timer is not configured yet------------------//
    if ((f_timerInfo_ps->isConfigured_b == (t_bool)True))
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKTIM_FilledBspEcdrInit(f_EcdrCfg_ps, &bspEcdrInit_s);
        
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKTIM_GetEcdrARRValue(   f_EcdrCfg_ps->HwMode_e,
                                                f_ARRValue_u32,
                                                &computeARRVal_u32);
            if(Ret_e == RC_OK)
            {
                Ret_e = s_FMKTIM_Set_BspTimerInit(  f_timerInfo_ps,
                                                    FMKTIM_HWTIM_CFG_ECDR,
                                                    computeARRVal_u32,
                                                    (void *)(&bspEcdrInit_s));
            }      
            if(Ret_e == RC_OK)
            {
                masterCfg_s.MasterOutputTrigger = TIM_TRGO_RESET;
                masterCfg_s.MasterOutputTrigger2 = TIM_TRGO2_RESET;
                masterCfg_s.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
                bspRet_e = HAL_TIMEx_MasterConfigSynchronization(   &f_timerInfo_ps->bspTimer_s,
                                                                    &masterCfg_s);

                if(bspRet_e != HAL_OK)
                {
                    Ret_e = RC_ERROR_WRONG_RESULT;
                }
            }                                            
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKTIM_Set_ICChannelCfg
 *********************************/
static t_eReturnCode s_FMKTIM_Set_ICChannelCfg( t_eFMKTIM_Timer f_timer_e,
                                                t_eFMKTIM_InterruptChnl f_channel_e, 
                                                t_eFMKTIM_ChnlMeasTrigger f_MeasTrigger_e,
                                                t_cbFMKTIM_InterruptLine f_ITChannel_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef BspRet_e = HAL_OK;
    HAL_TIM_ChannelStateTypeDef bspChannelState_e = HAL_TIM_CHANNEL_STATE_BUSY;
    t_sFMKTIM_TimerInfo * timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[f_timer_e]);
    TIM_IC_InitTypeDef BspICInit_s;
    t_uint32 bspChannel_u32 = 0;
    t_uint32 bspMeasPolarity_u32 = 0;
    
    //----------Check if timer is not configured yet------------------//
    if (timerInfo_ps->isConfigured_b == (t_bool)False)
    {
      
        //----------Set Input Compare configuration for all channels------------------//
        #warning('Found the right frequency for Ic Cfg')
        Ret_e = s_FMKTIM_Set_BspTimerInit(  timerInfo_ps,
                                            FMKTIM_HWTIM_CFG_IC,
                                            (t_uint32)2,
                                            (void *)NULL);
    }
    //-------this timer has already been configured and cannot be used for another Type of Configuration------//
    if (timerInfo_ps->HwCfg_e != FMKTIM_HWTIM_CFG_IC)
    {
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    //-------Channel is already used------//
    if (timerInfo_ps->Channel_as[f_channel_e].IsChnlConfigure_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKTIM_Get_BspChannel(f_channel_e, &bspChannel_u32);
        if (Ret_e == RC_OK)
        {
            Ret_e = s_FMKTIM_Get_BspICTrigger(f_MeasTrigger_e, &bspMeasPolarity_u32);
        }
        if(Ret_e == RC_OK)
        {
            bspChannelState_e = HAL_TIM_GetChannelState(&timerInfo_ps->bspTimer_s, bspChannel_u32);
            
            if(bspChannelState_e == HAL_TIM_CHANNEL_STATE_READY)
            {
                //-------Configure bsp channel structure------//
                BspICInit_s.ICPolarity = (t_uint32)bspMeasPolarity_u32;
                BspICInit_s.ICSelection = (t_uint32)TIM_ICSELECTION_DIRECTTI;
                BspICInit_s.ICPrescaler = (t_uint32)TIM_ICPSC_DIV1;
                BspICInit_s.ICFilter = (t_uint32)0;
                BspRet_e = HAL_TIM_IC_ConfigChannel(&timerInfo_ps->bspTimer_s,
                                                    &BspICInit_s,
                                                    bspChannel_u32);
                if (BspRet_e != HAL_OK)
                {
                    Ret_e = RC_ERROR_WRONG_STATE;
                }
            }
            else
            {
                Ret_e = RC_WARNING_BUSY;
            }
        }
        if (Ret_e == RC_OK)
        { 
            //-------update information-------//
            timerInfo_ps->Channel_as[f_channel_e].IsChnlConfigure_b = (t_bool)True;
            timerInfo_ps->Channel_as[f_channel_e].RunMode_e = FMKTIM_LINE_RUNMODE_INTERRUPT;
            timerInfo_ps->Channel_as[f_channel_e].chnl_cb = f_ITChannel_cb;
        }
        else
        {
            SETBIT_16B(timerInfo_ps->Channel_as[f_channel_e].ErrState_u16, FMKTIM_ERRSTATE_INIT_FAILED);
        }
    }
    
    return Ret_e;
}

/*********************************
 * s_FMKTIM_Set_EvntChannelCfg
 *********************************/
static t_eReturnCode s_FMKTIM_Set_EvntChannelCfg(t_eFMKTIM_Timer f_timer_e,
                                               t_eFMKTIM_InterruptChnl chnl_e,
                                               t_uint32 f_periodms_u32,
                                               t_cbFMKTIM_InterruptLine f_ITChannel_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 freqEvnt_f32 = 0.0f;
    t_sFMKTIM_TimerInfo * timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[f_timer_e]);

    //-------------See if timer has already been configured-------------//
    if(timerInfo_ps->isConfigured_b == (t_bool)True)
    {
        //-------------For Timer Event Configuration
        // As the timer itself generate the Interrutpion
        // You can use only on Aplication Channel-------------//
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if(Ret_e == RC_OK)
    {
        //----------Get the prescaler/ ARR for the timer ------------------//
        freqEvnt_f32 = (t_float32)(((t_float32)1.0f)/(f_periodms_u32/ (t_float32)CST_MSEC_TO_SEC));

        //-------------Call Init Function-------------//
        Ret_e = s_FMKTIM_Set_BspTimerInit(  timerInfo_ps,
                                            FMKTIM_HWTIM_CFG_EVNT,
                                            freqEvnt_f32,
                                            (void *)NULL);
        if (Ret_e == RC_OK)
        {
            //-------------Update Information-------------//
            timerInfo_ps->isConfigured_b = (t_bool)True;
            timerInfo_ps->Channel_as[chnl_e].chnl_cb = f_ITChannel_cb;
            timerInfo_ps->Channel_as[chnl_e].RunMode_e = FMKTIM_LINE_RUNMODE_INTERRUPT;
        }
        else
        {
            SETBIT_16B(timerInfo_ps->Channel_as[chnl_e].ErrState_u16, FMKTIM_ERRSTATE_INIT_FAILED);
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKTIM_Set_HwChannelState
 *********************************/
static t_eReturnCode s_FMKTIM_FilledBspEcdrInit(t_sFMKTIM_EcdrCfg * f_EcdrCdg_ps,
                                                TIM_Encoder_InitTypeDef * f_BspEcdrInit_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspEcdrMode_u32;
    t_uint32 bspIC1Selection_u32 = (t_uint32)0;
    t_uint32 bspIC2Selection_u32 = (t_uint32)0;
    t_uint32 bspIC1Polarity_u32 = (t_uint32)0;
    t_uint32 bspIC2Polarity_u32 = (t_uint32)0;

    if((f_EcdrCdg_ps == (t_sFMKTIM_EcdrCfg *)NULL)
    || (f_BspEcdrInit_ps == (TIM_Encoder_InitTypeDef *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //-------- Get Encoder Mode--------//
        Ret_e = s_FMKTIM_GetBspEcdrMode(f_EcdrCdg_ps->HwMode_e, &bspEcdrMode_u32);

        //-------- Get Encoder IC1 Selection--------//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKTIM_GetBspEcdrSelection(f_EcdrCdg_ps->IC1_s.Selection_e, &bspIC1Selection_u32);
        }
        //-------- Get Encoder IC1 Polarity--------//
        if(Ret_e == RC_OK)
        {
            s_FMKTIM_GetBspEcdrPolarity(f_EcdrCdg_ps->IC1_s.Polarity_e, &bspIC1Polarity_u32);
        }
        //-------- Get Encoder IC2 Selection--------//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKTIM_GetBspEcdrSelection(f_EcdrCdg_ps->IC1_s.Selection_e, &bspIC2Selection_u32);
        }
        //-------- Get Encoder IC2 Polarity--------//
        if(Ret_e == RC_OK)
        {
            s_FMKTIM_GetBspEcdrPolarity(f_EcdrCdg_ps->IC1_s.Polarity_e, &bspIC2Polarity_u32);
        }
        if(Ret_e == RC_OK)
        {
            //-------- Copy Data--------//
            f_BspEcdrInit_ps->EncoderMode = bspEcdrMode_u32;
            f_BspEcdrInit_ps->IC1Filter = 0x00;
            f_BspEcdrInit_ps->IC1Polarity = bspIC1Polarity_u32;
            f_BspEcdrInit_ps->IC1Selection = bspIC1Selection_u32;
            f_BspEcdrInit_ps->IC2Filter = 0x00;
            f_BspEcdrInit_ps->IC2Polarity = bspIC2Polarity_u32;
            f_BspEcdrInit_ps->IC2Selection = bspIC2Selection_u32;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKTIM_Set_EcdrOpeState
 *********************************/
static t_eReturnCode s_FMKTIM_Set_EcdrOpeState( t_eFMKTIM_Timer   f_timer_e,
                                                t_eFMKTIM_EcdrOpe f_EcdrOpe,
                                                t_uint8           f_mask_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_InterruptChnl chnl_e;
    t_eFMKTIM_ChnlState chnlState_e;


    if((f_timer_e >= FMKTIM_TIMER_NB)
    || (f_EcdrOpe >= FMKTIM_ECDR_OPE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get timer information---------//
        if(g_TimerInfo_as[f_timer_e].isConfigured_b == (t_bool)False)
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
        else 
        {
            switch (f_EcdrOpe)
            {
                case FMKTIM_ECDR_OPE_START_TI1:
                {
                    chnl_e = FMKTIM_CHANNEL_1;
                    chnlState_e = FMKTIM_CHNLST_ACTIVATED;
                    break;
                }
                case FMKTIM_ECDR_OPE_START_TI2:
                {
                    chnl_e = FMKTIM_CHANNEL_2;
                    chnlState_e = FMKTIM_CHNLST_ACTIVATED;
                    break;
                }
                case FMKTIM_ECDR_OPE_START_BOTH:
                {
                    chnl_e = FMKTIM_CHANNEL_ALL;
                    chnlState_e = FMKTIM_CHNLST_ACTIVATED;
                    break;
                }
                case FMKTIM_ECDR_OPE_STOP_TI1:
                {
                    chnl_e = FMKTIM_CHANNEL_1;
                    chnlState_e = FMKTIM_CHNLST_DISACTIVATED;
                    break;
                }
                case FMKTIM_ECDR_OPE_STOP_TI2:
                {
                    chnl_e = FMKTIM_CHANNEL_2;
                    chnlState_e = FMKTIM_CHNLST_DISACTIVATED;
                    break;
                }
                case FMKTIM_ECDR_OPE_STOP_BOTH:
                {
                    chnl_e = FMKTIM_CHANNEL_ALL;
                    chnlState_e = FMKTIM_CHNLST_DISACTIVATED;
                    break;
                }
                case FMKTIM_ECDR_OPE_NB:
                default:
                {   
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;
                }
            }
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKTIM_Set_HwChannelState(f_timer_e,
                                                chnl_e,
                                                chnlState_e);
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKTIM_Set_EvntOpeState
 *********************************/
static t_eReturnCode s_FMKTIM_Set_EvntOpeState( t_eFMKTIM_Timer         f_timer_e,
                                                t_eFMKTIM_InterruptChnl f_chnl_e,
                                                t_eFMKTIM_EvntOpe       f_EvntOpe,
                                                t_uint8                 f_mask_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_ChnlState chnlState_e;


    if((f_timer_e >= FMKTIM_TIMER_NB)
    || (f_chnl_e >= FMKTIM_CHANNEL_NB)
    || (f_EvntOpe >= FMKTIM_EVNT_OPE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_EvntOpe)
        {
            case FMKTIM_EVNT_OPE_START_TIMER:
                chnlState_e = FMKTIM_CHNLST_ACTIVATED;
                break;
            case FMKTIM_EVNT_OPE_STOP_TIMER:
                chnlState_e = FMKTIM_CHNLST_DISACTIVATED;
                break;
            case FMKTIM_EVNT_OPE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKTIM_Set_HwChannelState(f_timer_e,
                                                f_chnl_e,
                                                chnlState_e);
         }
    }

    return Ret_e;
}

/*********************************
 * s_FMKTIM_Set_PwmOpeState
 *********************************/
static t_eReturnCode s_FMKTIM_Set_PwmOpeState(  t_eFMKTIM_Timer   f_timer_e,
                                                t_eFMKTIM_InterruptChnl f_chnl_e,
                                                t_sFMKTIM_PwmOpe        f_PwmOpe_s,
                                                t_uint8 f_maskUpdate_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_sFMKTIM_TimerInfo * timerInfo_ps;
    TIM_TypeDef * bspIsct_ps;
    t_eFMKTIM_ChnlState chnlState_e = FMKTIM_CHNLST_DISACTIVATED;
    t_uint32 CCRxValue_u32 = (t_uint32)0;
    t_uint32 bspChannel_u32 = (t_uint32)0;
    t_uint32 bspARRVal_u32 = (t_uint32)0;
    t_uint32 bspPSCVal_u32 = (t_uint32)0;

    if((f_timer_e >= FMKTIM_TIMER_NB)
    || (f_chnl_e >= FMKTIM_CHANNEL_NB)
    || (f_PwmOpe_s.dutyCycle_u16 > FMKTIM_PWM_MAX_DUTY_CYLCE))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[f_timer_e]);
        bspIsct_ps = (TIM_TypeDef *)(timerInfo_ps->bspTimer_s.Instance); 

        if( (timerInfo_ps->isConfigured_b == (t_bool)False)
        ||  (timerInfo_ps->Channel_as[f_chnl_e].IsChnlConfigure_b == (t_bool)False))
        {
            Ret_e = RC_ERROR_MISSING_CONFIG;
        }
        if(GETBIT(timerInfo_ps->Channel_as[f_chnl_e].ErrState_u16, FMKTIM_ERRSTATE_OK) != BIT_IS_SET_16B)
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
        if(Ret_e == RC_OK)
        {
            // See if bit change frequency is SET
            if((GETBIT(f_maskUpdate_u8, FMKTIM_BIT_PWM_FREQUENCY) == BIT_IS_SET_8B)
            && (f_PwmOpe_s.frequency_u32 != (t_uint32)0))
            {
                Ret_e = c_FMKTIM_TimerFunc_apf[FMKTIM_HWTIM_CFG_PWM].
                        GetTimerInfoInit_pcb(   timerInfo_ps->c_clock_e,
                                                timerInfo_ps->timerFreqMHz_u32,
                                                (t_float32)f_PwmOpe_s.frequency_u32,
                                                &bspARRVal_u32,
                                                &bspPSCVal_u32);

                if(Ret_e == RC_OK)
                {
                    bspIsct_ps->ARR = (t_uint32)bspARRVal_u32;
                    bspIsct_ps->PSC = (t_uint32)bspPSCVal_u32;
                }
            }
            if((GETBIT(f_maskUpdate_u8, FMKTIM_BIT_PWM_DUTYCYCLE) == BIT_IS_SET_8B)
            && (f_PwmOpe_s.dutyCycle_u16 != (t_uint16)0))
            {
                //-------Calculate new CCR value-------------//
                CCRxValue_u32 = (t_uint32)((t_float32)f_PwmOpe_s.dutyCycle_u16 / (t_float32)FMKTIM_PWM_MAX_DUTY_CYLCE *
                            (t_float32)(timerInfo_ps->bspTimer_s.Init.Period + (t_uint32)1));

                //------- Get Bsp Channel -------------//
                Ret_e = s_FMKTIM_Get_BspChannel(f_chnl_e, &bspChannel_u32);
                
                if (Ret_e == RC_OK)
                {
                    //-------Update Duty Cycle-------------//
                    __HAL_TIM_SET_COMPARE(&timerInfo_ps->bspTimer_s, bspChannel_u32, (t_uint32)CCRxValue_u32);
                    chnlState_e = FMKTIM_CHNLST_ACTIVATED;
                }
            }
            if((GETBIT(f_maskUpdate_u8, FMKTIM_BIT_PWM_NB_PULSES) == BIT_IS_SET_8B)
            && (f_PwmOpe_s.nbPulses_u16 != (t_uint16)0))
            {
                //----- If user required a number of pulse 
                // we have to enable NVIC state to get ElapedTimeCallback 
                // when RCR goes to 0, then we start PWM in polling Mode-----//
                if(timerInfo_ps->IsNVICTimerEnable_b == (t_bool)False)
                {
                    Ret_e = FMKCPU_Set_NVICState(timerInfo_ps->c_IRQNType_e, FMKCPU_NVIC_OPE_ENABLE);

                    if(Ret_e == RC_OK)
                    {
                        timerInfo_ps->IsNVICTimerEnable_b = (t_bool)True;   
                    }
                }
                //__HAL_TIM_DISABLE_IT(&timerInfo_ps->bspTimer_s, TIM_IT_UPDATE);
   
                timerInfo_ps->Channel_as[f_chnl_e].RunMode_e = FMKTIM_LINE_RUNMODE_INTERRUPT; 
                
                bspIsct_ps->RCR = (t_uint16)(f_PwmOpe_s.nbPulses_u16 - (t_uint16)1);  // Modifier le RCR
                //__HAL_TIM_ENABLE_IT(&timerInfo_ps->bspTimer_s, TIM_IT_UPDATE);
                chnlState_e = FMKTIM_CHNLST_ACTIVATED;
            }

            //-------Forced actuation-------------//
            //HAL_TIM_GenerateEvent(&timerInfo_ps->bspTimer_s, TIM_EVENTSOURCE_UPDATE);
            if(Ret_e == RC_OK)
            {
                //-------Activate/ Deactivate  channel-------------//
                if(timerInfo_ps->Channel_as[f_chnl_e].State_e != chnlState_e)
                {
                    //----- Start Pwm Polling Mode -----//
                    Ret_e = s_FMKTIM_Set_HwChannelState(f_timer_e, f_chnl_e, chnlState_e);

                    //----- Effacer le flag d'update avant de démarrer les IT -----//
                    __HAL_TIM_CLEAR_FLAG(&timerInfo_ps->bspTimer_s, TIM_FLAG_UPDATE);

                    //----- Start Period Callback after RCR passed -----//
                    bspRet_e = HAL_TIM_Base_Start_IT(&timerInfo_ps->bspTimer_s);

                    if(bspRet_e != HAL_OK)
                    {
                        Ret_e = RC_ERROR_WRONG_RESULT; 
                    }
                    else
                    {
                        //----- Reset Flag -----//
                        g_timerPeriodPwm_ab[f_timer_e] = (t_bool)False;
                    }
                }
            }
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKTIM_Set_ICOpeState
 *********************************/
static t_eReturnCode s_FMKTIM_Set_ICOpeState(   t_eFMKTIM_Timer         f_timer_e,
                                                t_eFMKTIM_InterruptChnl f_chnl_e,
                                                t_sFMKTIM_ICOpe         f_ICOpe_s,
                                                t_uint8                 f_mask_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_ChnlState chnlState_e;
    t_sFMKTIM_TimerInfo * timerInfo_ps;
    TIM_TypeDef * bspIsct_ps;
    t_uint32 bspARRVal_u32 = (t_uint32)0;
    t_uint32 bspPSCVal_u32 = (t_uint32)0;

    if((f_timer_e >= FMKTIM_TIMER_NB)
    || (f_chnl_e >= FMKTIM_CHANNEL_NB)
    || (f_ICOpe_s.IcState_e >= FMKTIM_IC_STATE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        if(GETBIT(f_mask_u8, FMKTIM_BIT_IC_STATE) == BIT_IS_SET_8B)
        {
            switch(f_ICOpe_s.IcState_e)
            {
                case FMKTIM_IC_STATE_ENABLE:
                {
                    chnlState_e = FMKTIM_CHNLST_ACTIVATED;
                    break;
                }
                case FMKTIM_IC_STATE_DISABLE:
                {
                    chnlState_e = FMKTIM_CHNLST_DISACTIVATED;
                    break;
                }
                case FMKTIM_IC_STATE_NB:
                default:
                {
                    Ret_e =  RC_ERROR_NOT_SUPPORTED;
                    break;
                }
            }
            if(Ret_e == RC_OK)
            {
                Ret_e = s_FMKTIM_Set_HwChannelState(f_timer_e,
                                                    f_chnl_e,
                                                    chnlState_e);
            }
        }
        if(GETBIT(f_mask_u8, FMKTIM_BIT_IC_FREQUENCY) == BIT_IS_SET_8B)
        {
            timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[f_timer_e]);
            bspIsct_ps = (TIM_TypeDef *)(timerInfo_ps->bspTimer_s.Instance); 


            Ret_e = c_FMKTIM_TimerFunc_apf[FMKTIM_HWTIM_CFG_IC].
                    GetTimerInfoInit_pcb(   timerInfo_ps->c_clock_e,
                                            timerInfo_ps->timerFreqMHz_u32,
                                            (t_float32)f_ICOpe_s.frequency_u32,
                                            &bspARRVal_u32,
                                            &bspPSCVal_u32);

            if(Ret_e == RC_OK)
            {
                bspIsct_ps->ARR = (t_uint32)bspARRVal_u32;
                bspIsct_ps->PSC = (t_uint32)bspPSCVal_u32;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKTIM_Set_HwChannelState
 *********************************/
static t_eReturnCode s_FMKTIM_Set_HwChannelState(   t_eFMKTIM_Timer f_timer_e,
                                                    t_eFMKTIM_InterruptChnl f_channel_e,
                                                    t_eFMKTIM_ChnlState f_chnlStateOpe_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspChannel_u32 = 0;
    t_sFMKTIM_ChnlInfo  * channel_ps;
    t_sFMKTIM_TimerInfo * timerInfo_ps;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    static t_uint16 s_mskChnState_ua16[FMKTIM_TIMER_NB] = {0};

    // Argument already verify
    timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[f_timer_e]);

    if(f_channel_e == FMKTIM_CHANNEL_ALL)
    {
        //----- By default take Channel 1  ------//
        channel_ps = (t_sFMKTIM_ChnlInfo  *)(&g_TimerInfo_as[f_timer_e].Channel_as[FMKTIM_CHANNEL_1]);

    }
    else 
    {
        channel_ps = (t_sFMKTIM_ChnlInfo  *)(&g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e]);
    }

    if (channel_ps->State_e != f_chnlStateOpe_e)
    {
        Ret_e = s_FMKTIM_Get_BspChannel(f_channel_e, &bspChannel_u32);
        if (Ret_e == RC_OK)
        { 
            //--------Depending on wehter we need to activate or deactivate function--------//
            switch (f_chnlStateOpe_e)
            {
                case FMKTIM_CHNLST_ACTIVATED:
                { 
                    //--------Update Mask Channel status--------//
                    s_mskChnState_ua16[f_timer_e] |= 1 << (t_uint16)(f_channel_e);

                    //-------- We have to start HALfunction in Basic or Interrupt depending on f_chnlRunMode_e--------//
                    //--------call the right HAL function Polling or Interrupt mode--------//
                    if (timerInfo_ps->IsNVICTimerEnable_b == (t_bool)False)
                    {
                        Ret_e = FMKCPU_Set_NVICState(timerInfo_ps->c_IRQNType_e, FMKCPU_NVIC_OPE_ENABLE);
                    }
                    if (Ret_e == RC_OK)
                    {
                        switch (channel_ps->RunMode_e)
                        {
                        case FMKTIM_LINE_RUNMODE_POLLING:
                            bspRet_e = c_FMKTIM_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                            StartFuncPoll_pcb(&timerInfo_ps->bspTimer_s,
                                                              (t_uint32)bspChannel_u32);
                            break;
                        case FMKTIM_LINE_RUNMODE_INTERRUPT:
                            bspRet_e = c_FMKTIM_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                            StartFuncInterrupt_pcb(&timerInfo_ps->bspTimer_s,
                                                                   (t_uint32)bspChannel_u32);
                            break;
                        case FMKTIM_LINE_RUNMODE_DMA:
                        {
                            bspRet_e = c_FMKTIM_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                            StartFuncDma_pcb(&timerInfo_ps->bspTimer_s,
                                                            (t_uint32)bspChannel_u32,
                                                            channel_ps->DmaInfo_ps.BufferAdd1_pu32,
                                                            channel_ps->DmaInfo_ps.BufferAdd2_pu32,
                                                            channel_ps->DmaInfo_ps.bufferLen_u16);

                            break;
                        }
                        case FMKTIM_LINE_RUNMODE_NB:
                        default:
                            Ret_e = RC_ERROR_NOT_SUPPORTED;
                            break;
                        }
                    }

                    break;
                }

                case FMKTIM_CHNLST_DISACTIVATED:
                {
                    //--------Update Mask Channel status--------//
                    s_mskChnState_ua16[f_timer_e] &= ~(1 << (t_uint32)(f_channel_e));
                    if (timerInfo_ps->IsNVICTimerEnable_b == (t_bool)True)
                    {
                        Ret_e = FMKCPU_Set_NVICState(timerInfo_ps->c_IRQNType_e, FMKCPU_NVIC_OPE_DISABLE);
                    }
                    if (Ret_e == RC_OK)
                    {
                        switch (channel_ps->RunMode_e)
                        {
                            case FMKTIM_LINE_RUNMODE_POLLING:
                                bspRet_e = c_FMKTIM_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                                StopFuncPoll_pcb(&timerInfo_ps->bspTimer_s,
                                                (t_uint32)bspChannel_u32);
                                break;

                            case FMKTIM_LINE_RUNMODE_INTERRUPT:
                                bspRet_e = c_FMKTIM_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                                StopFuncInterrupt_pcb(&timerInfo_ps->bspTimer_s,
                                                                       (t_uint32)bspChannel_u32);
                                break;

                            case FMKTIM_LINE_RUNMODE_DMA:
                            {
                                bspRet_e = c_FMKTIM_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                            StopFuncDma_pcb(&timerInfo_ps->bspTimer_s,
                                                            (t_uint32)bspChannel_u32);
                                break;
                            }
                            case FMKTIM_LINE_RUNMODE_NB:
                            default:
                                Ret_e = RC_ERROR_NOT_SUPPORTED;
                                break;
                        }
                    }
                    break;
                }
                case FMKTIM_CHNLST_NB:
                default:
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;
            }
            if (bspRet_e != HAL_OK)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
            else
            {
               
                //--------Update Information--------//
                timerInfo_ps->IsTimerRunning_b =
                    (s_mskChnState_ua16[f_timer_e] == (t_uint32)0)? False : True;
                    
                channel_ps->State_e = f_chnlStateOpe_e;
            }
        }
    }
    return Ret_e;
}

/*********************************
 * FMKCPU_Get_PWMChannelDuty
 *********************************/
static t_eReturnCode s_FMKTIM_Get_CCRxValue(t_eFMKTIM_Timer f_timer_e, 
                                            t_eFMKTIM_InterruptChnl f_channel_e,
                                            t_uint32 * f_comparedValue_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 BspChannel_u32 = 0;
    t_sFMKTIM_TimerInfo * timerInfo_ps;

   if((f_timer_e >= FMKTIM_TIMER_NB)
   || (f_channel_e >= FMKTIM_CHANNEL_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_comparedValue_pu32 == (t_uint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {

        //--------- Get timer/channel information---------//
        timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[f_timer_e]);
        
        //--------- get dutycycle only if channel is active---------//

        if (Ret_e == RC_OK)
        {  
            Ret_e = s_FMKTIM_Get_BspChannel(f_channel_e, &BspChannel_u32);

            if (Ret_e == RC_OK)
            {
                //--------- use BSP function to know dutycyle---------//
                *f_comparedValue_pu32 = (t_uint32)HAL_TIM_ReadCapturedValue(&timerInfo_ps->bspTimer_s, BspChannel_u32);
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKTIM_GetEcdrARRValue
 *********************************/
static t_eReturnCode s_FMKTIM_GetEcdrARRValue(  t_eFMKTIM_EcdrMode f_EcdrMode_e,
                                                t_uint32 f_rqstArrValue_u32,
                                                t_uint32 * f_ArrValue_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_EcdrMode_e >= FMKTIM_ECDR_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_ArrValue_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_EcdrMode_e)
        {
            case FMKTIM_ECDR_MODE_TI1:
            case FMKTIM_ECDR_MODE_TI2:
            case FMKTIM_ECDR_MODE_CLOCKPLUS_DIRECTION_X1:
            case FMKTIM_ECDR_MODE_TI12:
            case FMKTIM_ECDR_MODE_DIRECTIONAL_CLK_X1_TI12:
            case FMKTIM_ECDR_MODE_X1_TI1:
            case FMKTIM_ECDR_MODE_X1_TI12:
            {
                *f_ArrValue_pu32 = (t_uint32)(f_rqstArrValue_u32);
                break;
            }
            case FMKTIM_ECDR_MODE_DIRECTIONAL_CLK_X2:
            case FMKTIM_ECDR_MODE_CLOCKPLUS_DIRECTION_X2:
            {
                *f_ArrValue_pu32 = (t_uint32)((t_uint32)2 * f_rqstArrValue_u32);
                break;
            }
            case FMKTIM_ECDR_MODE_NB:
            default:
            {
                Ret_e = RC_ERROR_NOT_SUPPORTED;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKTIM_Set_BspTimerInit
 *********************************/
static t_eReturnCode s_FMKTIM_Set_BspTimerInit( t_sFMKTIM_TimerInfo * f_timer_ps,
                                                t_eFMKTIM_HwTimerCfg f_hwTimCfg_e,
                                                t_uint32 f_InfoInit_u32,
                                                void * f_timerCfg_pv)

{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_uint32 bspPeriod_u32;
    t_uint32 bspPrescaler_u32;

    if (f_timer_ps == (t_sFMKTIM_TimerInfo *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKCPU_Set_HwClock(f_timer_ps->c_clock_e, FMKCPU_CLOCKPORT_OPE_ENABLE);
    }
    if(Ret_e == RC_OK)
    {
        //----------Get the prescaler/ ARR for the timer ------------------//
        Ret_e = c_FMKTIM_TimerFunc_apf[f_hwTimCfg_e].
                    GetTimerInfoInit_pcb(f_timer_ps->c_clock_e,
                                         f_timer_ps->timerFreqMHz_u32,
                                        (t_float32)f_InfoInit_u32,
                                        &bspPeriod_u32,
                                        &bspPrescaler_u32);
    }
    if (Ret_e == RC_OK)
    {
        //---------- Set Bsp Structure ------------------//
        f_timer_ps->bspTimer_s.Init.Prescaler         = bspPrescaler_u32;
        f_timer_ps->bspTimer_s.Init.Period            = bspPeriod_u32;
        f_timer_ps->bspTimer_s.Init.RepetitionCounter = (t_uint32)0;
        f_timer_ps->bspTimer_s.Init.CounterMode       = TIM_COUNTERMODE_UP;
        f_timer_ps->bspTimer_s.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
        f_timer_ps->bspTimer_s.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

        //------- Call the Right Bsp Timer Init -----//
        if(Ret_e == RC_OK)
        {
            bspRet_e = c_FMKTIM_TimerFunc_apf[f_hwTimCfg_e].TimerInit_pcb(  &f_timer_ps->bspTimer_s,
                                                                            (void *)f_timerCfg_pv);
            if(bspRet_e != HAL_OK)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
            else 
            {
                f_timer_ps->HwCfg_e = f_hwTimCfg_e;
                f_timer_ps->isConfigured_b = (t_bool)True;
            }
        }        
    }

    return Ret_e;
}

/***********************************
 * s_FMKTIM_BspRqst_InterruptMngmt
 ***********************************/
static void s_FMKTIM_BspRqst_InterruptMngmt(TIM_HandleTypeDef *f_timerIstce_ps, t_eFMKTIM_BspEvent f_cbEvnt_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKTIM_Timer Calltimer_e = FMKTIM_TIMER_NB;
    HAL_TIM_ActiveChannel BspITChnl_e = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
    t_eFMKTIM_InterruptChnl ITChnl_e = FMKTIM_CHANNEL_NB;
    t_sFMKTIM_TimerInfo * timerInfo_ps;
    t_uint8 LLI_u8 = 0;

    // loop to know  which timer it is
    for (LLI_u8 = (t_uint8)0; LLI_u8 < (t_uint8)FMKTIM_TIMER_NB; LLI_u8++)
    {
        if (&g_TimerInfo_as[LLI_u8].bspTimer_s == (TIM_HandleTypeDef *)f_timerIstce_ps)
        {
            Calltimer_e = (t_eFMKTIM_Timer)LLI_u8;
            break;
        }
    }
    if (Calltimer_e >= FMKTIM_TIMER_NB)
    {
        //------------Call somoene to deal with this error------------//
        return; 
    }
    else
    {
        timerInfo_ps = (t_sFMKTIM_TimerInfo *)(&g_TimerInfo_as[Calltimer_e]);

        switch(timerInfo_ps->HwCfg_e)
        {  
            case FMKTIM_HWTIM_CFG_PWM:
            {
                //----- Pulse finished -----//
                if(f_cbEvnt_e == FMKTIM_BSP_CB_PERIOD_ELAPSED)
                {
                    if(g_timerPeriodPwm_ab[Calltimer_e] == (t_bool)False)
                    {
                        //----- Update Flag -----//
                        g_timerPeriodPwm_ab[Calltimer_e] = (t_bool)True;
                    }
                    else 
                    {
                        //----- Reset PWM ON & call user-----//
                        for(LLI_u8 = (t_uint8)0 ; (LLI_u8 < FMKTIM_CHANNEL_NB) && (Ret_e == RC_OK) ; LLI_u8++)
                        {
                            if(timerInfo_ps->Channel_as[LLI_u8].State_e == FMKTIM_CHNLST_ACTIVATED
                            && timerInfo_ps->Channel_as[LLI_u8].RunMode_e == FMKTIM_LINE_RUNMODE_INTERRUPT)
                            {
                                Ret_e = s_FMKTIM_Set_HwChannelState(Calltimer_e, LLI_u8, FMKTIM_CHNLST_DISACTIVATED);

                                if( (Ret_e == RC_OK) && 
                                    (timerInfo_ps->Channel_as[LLI_u8].chnl_cb != NULL_FONCTION))
                                {
                                    timerInfo_ps->Channel_as[LLI_u8].
                                        chnl_cb(c_FmkTim_ChnlItLineMapp[Calltimer_e][LLI_u8].type_e,
                                                c_FmkTim_ChnlItLineMapp[Calltimer_e][LLI_u8].ITLine_u8);

                                    //---- update chnl state ----//
                                    timerInfo_ps->Channel_as[LLI_u8].RunMode_e = FMKTIM_LINE_RUNMODE_INTERRUPT;
                                }
                            }
                        }
                    }
                }
                break;
            }
            case FMKTIM_HWTIM_CFG_EVNT:
            {
                if(timerInfo_ps->Channel_as[FMKTIM_CHANNEL_1].chnl_cb != NULL_FONCTION)
                {
                    timerInfo_ps->Channel_as[FMKTIM_CHANNEL_1].
                        chnl_cb(c_FmkTim_ChnlItLineMapp[Calltimer_e][FMKTIM_CHANNEL_1].type_e,
                                c_FmkTim_ChnlItLineMapp[Calltimer_e][FMKTIM_CHANNEL_1].ITLine_u8);
                }
                break;
            }
            case FMKTIM_HWTIM_CFG_IC:
            {
                //------------Find Bsp Channel which triggered the interruption------------//
                BspITChnl_e = HAL_TIM_GetActiveChannel(&timerInfo_ps->bspTimer_s);
                switch (BspITChnl_e)
                {
                    case HAL_TIM_ACTIVE_CHANNEL_1:
                        ITChnl_e = FMKTIM_CHANNEL_1;
                        break;

                    case HAL_TIM_ACTIVE_CHANNEL_2:
                        ITChnl_e = FMKTIM_CHANNEL_2;
                        break;

                    case HAL_TIM_ACTIVE_CHANNEL_3:
                        ITChnl_e = FMKTIM_CHANNEL_3;
                        break;

                    case HAL_TIM_ACTIVE_CHANNEL_4:
                        ITChnl_e = FMKTIM_CHANNEL_4;
                        break;
#ifdef FMKTIM_STM32_ECU_FAMILY_G
                    case HAL_TIM_ACTIVE_CHANNEL_5:
                        ITChnl_e = FMKTIM_CHANNEL_5;
                        break;

                    case HAL_TIM_ACTIVE_CHANNEL_6:
                        ITChnl_e = FMKTIM_CHANNEL_6;
                        break;
#endif              
                    case HAL_TIM_ACTIVE_CHANNEL_CLEARED:
                    default:
                        Ret_e = RC_ERROR_NOT_SUPPORTED;
                        break;
                }
                if( (Ret_e == RC_OK) 
                && (timerInfo_ps->Channel_as[LLI_u8].chnl_cb != NULL_FONCTION))
                {
                    timerInfo_ps->Channel_as[ITChnl_e].
                        chnl_cb(c_FmkTim_ChnlItLineMapp[Calltimer_e][ITChnl_e].type_e,
                                c_FmkTim_ChnlItLineMapp[Calltimer_e][ITChnl_e].ITLine_u8);
                }
                break;
            }
            case FMKTIM_HWTIM_CFG_OC:
            case FMKTIM_HWTIM_CFG_OP:
            case FMKTIM_HWTIM_CFG_ECDR:
            case FMKTIM_HWTIM_CFG_DAC:
            case FMKTIM_HWTIM_CFG_NB:
            default:
            {
                Ret_e = RC_WARNING_NO_OPERATION;
            }

        }
    }

    return;
}

/*********************************
 * s_FMKTIM_Get_BspChannel
 *********************************/
static t_eReturnCode s_FMKTIM_Get_BspChannel(t_eFMKTIM_InterruptChnl f_channel_e, t_uint32 *f_bspChnl_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_bspChnl_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_channel_e >= FMKTIM_CHANNEL_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_channel_e)
        {
        case FMKTIM_CHANNEL_1:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_1;
            break;
        case FMKTIM_CHANNEL_2:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_2;
            break;
        case FMKTIM_CHANNEL_3:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_3;
            break;
        case FMKTIM_CHANNEL_4:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_4;
            break;
#ifdef FMKTIM_STM32_ECU_FAMILY_G
        case FMKTIM_CHANNEL_5:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_5;
            break;
        case FMKTIM_CHANNEL_6:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_6;
            break;
#endif
        case FMKTIM_CHANNEL_ALL:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_ALL;
            break;
        case FMKTIM_CHANNEL_NB:
        default:
            Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
            break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKTIM_Get_BspTimer
 *********************************/
static t_eReturnCode s_FMKTIM_Get_BspICTrigger(t_eFMKTIM_ChnlMeasTrigger f_MeasTrigger_e, t_uint32 *f_bspMeasTrigger_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_bspMeasTrigger_u32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_MeasTrigger_e >= FMKTIM_LINE_MEAS_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_MeasTrigger_e)
        {
        case FMKTIM_LINE_MEAS_FALLING_EDGE:
            *f_bspMeasTrigger_u32 = (t_uint32)TIM_ICPOLARITY_FALLING;
            break;
        case FMKTIM_LINE_MEAS_RISING_EDGE:
            *f_bspMeasTrigger_u32 = (t_uint32)TIM_ICPOLARITY_RISING;
            break;
        case FMKTIM_LINE_MEAS_BOTH_EDGE:
            *f_bspMeasTrigger_u32 = (t_uint32)TIM_ICPOLARITY_BOTHEDGE;
            break;
        case FMKTIM_LINE_MEAS_NB:
        default:
            Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
            break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKTIM_Get_BspTimer
 *********************************/
static t_eReturnCode s_FMKTIM_GetBspEcdrPolarity(t_eFMKTIM_EcdrInPolarity f_ICEcdrPolarity_e, t_uint32 *f_bspICEcdrPolarity_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_bspICEcdrPolarity_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_ICEcdrPolarity_e >= FMKTIM_ECDR_IN_POLARITY_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_ICEcdrPolarity_e)
        {
            case FMKTIM_ECDR_IN_POLARITY_RISING:
                *f_bspICEcdrPolarity_pu32 = (t_uint32)TIM_ENCODERINPUTPOLARITY_RISING;
                break;
            case FMKTIM_ECDR_IN_POLARITY_FALLING:
                *f_bspICEcdrPolarity_pu32 = (t_uint32)TIM_ENCODERINPUTPOLARITY_FALLING;
                break;
            case FMKTIM_ECDR_IN_POLARITY_NB:
            default:
                Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
                break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKTIM_Get_BspTimer
 *********************************/
static t_eReturnCode s_FMKTIM_GetBspEcdrMode(t_eFMKTIM_EcdrMode f_EcdrMode_e, t_uint32 *f_bspEcdrMode_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_bspEcdrMode_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_EcdrMode_e >= FMKTIM_ECDR_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_EcdrMode_e)
        {
            case FMKTIM_ECDR_MODE_TI1:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_TI1;
                break;
            case FMKTIM_ECDR_MODE_TI2:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_TI2;
                break;
            case FMKTIM_ECDR_MODE_TI12:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_TI2;
                break;
            case FMKTIM_ECDR_MODE_CLOCKPLUS_DIRECTION_X2:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X2;
                break;
            case FMKTIM_ECDR_MODE_CLOCKPLUS_DIRECTION_X1:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X1;
                break;
            case FMKTIM_ECDR_MODE_DIRECTIONAL_CLK_X2:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_DIRECTIONALCLOCK_X2;
                break;
            case FMKTIM_ECDR_MODE_DIRECTIONAL_CLK_X1_TI12:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_DIRECTIONALCLOCK_X1_TI12;
                break;
            case FMKTIM_ECDR_MODE_X1_TI1:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_X1_TI1;
                break;
            case FMKTIM_ECDR_MODE_X1_TI12:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_X1_TI2;
                break;
            case FMKTIM_ECDR_MODE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;   
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKTIM_Get_BspTimer
 *********************************/
static t_eReturnCode s_FMKTIM_GetBspEcdrSelection(t_eFMKTIM_ICSelection f_ICEcdrSelect_e, t_uint32 *f_bspICEcdrSelect_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_bspICEcdrSelect_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_ICEcdrSelect_e >= FMKTIM_ICSELECT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_ICEcdrSelect_e)
        {
            case FMKTIM_ICSELECT_INDIRECT_TI:
                *f_bspICEcdrSelect_pu32 = (t_uint32)TIM_ICSELECTION_DIRECTTI;
                break;
            case FMKTIM_ICSELECT_DIRECT_TI:
                *f_bspICEcdrSelect_pu32 = (t_uint32)TIM_ICSELECTION_INDIRECTTI;
                break;
            case FMKTIM_ICSELECT_TRC:
                *f_bspICEcdrSelect_pu32 = (t_uint32)TIM_ICSELECTION_TRC;
                break;
            case FMKTIM_ICSELECT_NB:
            default:
                Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
                break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKTIM_Get_TimChnlFromITLine
 *********************************/
static t_eReturnCode s_FMKTIM_Get_TimChnlFromITLine(t_eFMKTIM_InterruptLineType f_ITLineType_e,
                                                    t_uint32                    f_ITLine_u32,    
                                                    t_eFMKTIM_Timer             *f_timer_pe,
                                                    t_eFMKTIM_InterruptChnl     *f_channel_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    switch(f_ITLineType_e)
    {
        case FMKTIM_INTERRUPT_LINE_TYPE_IO:
        {
            if(f_ITLine_u32 >= FMKTIM_INTERRUPT_LINE_IO_NB)
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            else 
            {
                *f_timer_pe = c_FmkTim_ITLineIOMapp_as[(t_eFMKTIM_InterruptLineIO)f_ITLine_u32].timer_e;
                if(g_TimerInfo_as[(*f_timer_pe)].HwCfg_e == FMKTIM_HWTIM_CFG_ECDR)
                {
                    *f_channel_pe = FMKTIM_CHANNEL_ALL;
                }
                else 
                {
                    *f_channel_pe = c_FmkTim_ITLineIOMapp_as[(t_eFMKTIM_InterruptLineIO)f_ITLine_u32].channel_e;
                }
            }
            break;
        }
        case FMKTIM_INTERRUPT_LINE_TYPE_EVNT:
        {
            if(f_ITLine_u32 >= FMKTIM_INTERRUPT_LINE_EVNT_NB)
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            else 
            {
                *f_timer_pe = c_FmkTim_ITLineEvntMapp_as[(t_eFMKTIM_InterruptLineEvnt)f_ITLine_u32].timer_e;
                *f_channel_pe = c_FmkTim_ITLineEvntMapp_as[(t_eFMKTIM_InterruptLineEvnt)f_ITLine_u32].channel_e;
            }
            
            break;
        }
        case FMKTIM_INTERRUPT_LINE_TYPE_DAC:
        {
            if(f_ITLine_u32 >= FMKTIM_INTERRUPT_LINE_EVNT_NB)
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            else 
            {
                *f_timer_pe = c_FmkTim_ITLineDacMapp_as[(t_eFMKTIM_InterruptLineDAC)f_ITLine_u32].timer_e;
                *f_channel_pe = c_FmkTim_ITLineDacMapp_as[(t_eFMKTIM_InterruptLineDAC)f_ITLine_u32].channel_e;
            }
            
            break;
        }
        case FMKTIM_INTERRUPT_LINE_TYPE_NB:
        default:
            Ret_e = RC_ERROR_NOT_SUPPORTED;
            break;
    }
    
    return Ret_e;
}


//********************************************************************************
//                      HAL_Callback Implementation
//********************************************************************************
/**
 *
 *	@brief      Implementation of every timer IRQHandler wardware function.\n 
 *
 */
/* CAUTION : Automatic generated code section for TIMx IRQHandler: Start */
/*********************************
 * TIM1_BRK_TIM15_IRQHandler
*********************************/
void TIM1_BRK_TIM15_IRQHandler(void)      {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_15].bspTimer_s);}
/*********************************
 * TIM1_UP_TIM16_IRQHandler
*********************************/
void TIM1_UP_TIM16_IRQHandler(void)       {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_1].bspTimer_s);}
/*********************************
 * TIM1_TRG_COM_TIM17_IRQHandler
*********************************/
void TIM1_TRG_COM_TIM17_IRQHandler(void)  {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_17].bspTimer_s);}
/*********************************
 * TIM1_CC_IRQHandler
*********************************/
void TIM1_CC_IRQHandler(void)             {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_1].bspTimer_s);}
/*********************************
 * TIM2_IRQHandler
*********************************/
void TIM2_IRQHandler(void)                {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_2].bspTimer_s);}
/*********************************
 * TIM3_IRQHandler
*********************************/
void TIM3_IRQHandler(void)                {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_3].bspTimer_s);}
/*********************************
 * TIM4_IRQHandler
*********************************/
void TIM4_IRQHandler(void)                {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_4].bspTimer_s);}
/*********************************
 * TIM6_DAC_IRQHandler
*********************************/
void TIM6_DAC_IRQHandler(void)            {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_6].bspTimer_s);}
/*********************************
 * TIM7_DAC_IRQHandler
*********************************/
void TIM7_DAC_IRQHandler(void)            {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_7].bspTimer_s);}
/*********************************
 * TIM20_BRK_IRQHandler
*********************************/
void TIM20_BRK_IRQHandler(void)           {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_20].bspTimer_s);}
/*********************************
 * TIM20_UP_IRQHandler
*********************************/
void TIM20_UP_IRQHandler(void)            {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_20].bspTimer_s);}
/*********************************
 * TIM20_TRG_COM_IRQHandler
*********************************/
void TIM20_TRG_COM_IRQHandler(void)       {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_20].bspTimer_s);}
/*********************************
 * TIM20_CC_IRQHandler
*********************************/
void TIM20_CC_IRQHandler(void)            {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKTIM_TIMER_20].bspTimer_s);}
/* CAUTION : Automatic generated code section for TIMx IRQHandler: End */

/**
 *
 *	@brief      Every callback function is now centralized in one function
 *
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) { return s_FMKTIM_BspRqst_InterruptMngmt(htim, FMKTIM_BSP_CB_PERIOD_ELAPSED); }
//void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim) { return s_FMKTIM_BspRqst_InterruptMngmt(htim); }
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) { return s_FMKTIM_BspRqst_InterruptMngmt(htim, FMKTIM_BSP_CB_IC_CAPTURE); }
//void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim) { return s_FMKTIM_BspRqst_InterruptMngmt(htim); }
//void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) { return s_FMKTIM_BspRqst_InterruptMngmt(htim, FMKTIM_BSP_CB_OC_DELAY_ELAPSED); }
//void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) { return s_FMKTIM_BspRqst_InterruptMngmt(htim, FMKTIM_BSP_CB_PWM_PULSE_FINISHED); }
//void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim) { return s_FMKTIM_BspRqst_InterruptMngmt(htim); }
//void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim) { return s_FMKTIM_BspRqst_InterruptMngmt(htim, FMKTIM_HWTIM_CFG_TRGR); }


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
