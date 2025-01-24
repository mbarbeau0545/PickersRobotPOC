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
#include "./FMK_CPU.h"
#include "FMK_HAL/FMK_MAC/Src/FMK_MAC.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKCPU_ConfigPrivate.h"
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
    FMKCPU_BSP_CB_PERIOD_ELAPSED = 0x00,
    FMKCPU_BSP_CB_IC_CAPTURE,
    FMKCPU_BSP_CB_OC_DELAY_ELAPSED,
    FMKCPU_BSP_CB_PWM_PULSE_FINISHED,

    FMKCPU_BSP_CB_NB,
} t_eFMKCPU_BspEvent;
/**< Enum  for channel state */
typedef enum
{
    FMKCPU_CHNLST_DISACTIVATED = 0x0U,       /**< the channel is disactivated by software, not running */
    FMKCPU_CHNLST_ACTIVATED,                 /**< The channel is acitvated by software, is running */

    FMKCPU_CHNLST_NB                         /**< Number of channel state */
} t_eFMKCPU_ChnlState;
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
    t_eFMKMAC_DmaRqst RqstId_e;
} t_sFMKCPU_ChnlDmaInfo;
/**< Structure of information on a timer-channel*/
typedef struct
{
    t_eFMKCPU_ChnlState State_e;                        /**< State of the channel */
    t_eFMKCPU_ChnlRunMode RunMode_e;                    /**< Run mode for the channel */
    t_sFMKCPU_ChnlDmaInfo DmaInfo_ps;
    t_uint16 ErrState_u16;                /**< Error state of the channel */
    t_cbFMKCPU_InterruptLine *chnl_cb;                  /**< Callback function of the channel */
    t_bool IsChnlConfigure_b;                           /**< Wether or not the channel has beeen configured */
    
} t_sFMKCPU_ChnlInfo;

/**< Structure of information on a timer*/
typedef struct
{
    TIM_HandleTypeDef bspTimer_s;                       /**< The Timer structure for HAL STM32*/
    t_eFMKCPU_HwTimerCfg HwCfg_e;                       /**< The hardware configuration of the timer */
    t_sFMKCPU_ChnlInfo Channel_as[FMKCPU_CHANNEL_NB];   /**< Channels info structure */
    const t_eFMKCPU_IRQNType c_IRQNType_e;              /**< IRQN type related to the timer */
    const t_eFMKCPU_ClockPort c_clock_e;                /**< RCC clock related to the timer */
    t_uint16 timerFreqMHz_u32;                              /**< Timer frequency in Mhz */
    //const t_eFMKMAC_DmaRqst c_RqstDma_e;               /**< RCC clock related to the timer */
    t_bool IsTimerRunning_b;                            /**< Flag for timer is runnning */
    t_bool isConfigured_b;                              /**< flag timer is configured */  
    t_bool IsNVICTimerEnable_b;                         /**< flag timer NVCIC enable or not */

} t_sFMKCPU_TimerInfo;

// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
static t_eCyclicModState g_FmkCpu_ModState_e = STATE_CYCLIC_CFG;

WWDG_HandleTypeDef g_wwdgInfos_s = {0};

t_uint8 g_SysClockValue_ua8[FMKCPU_SYS_CLOCK_NB];

/* CAUTION : Automatic generated code section for Timer Configuration: Start */
/**< timer information variable */
t_sFMKCPU_TimerInfo g_TimerInfo_as[FMKCPU_TIMER_NB] = {
    {
        // Timer_1
        .bspTimer_s.Instance = TIM1,
        .c_clock_e = FMKCPU_RCC_CLK_TIM1,
        .c_IRQNType_e = FMKCPU_NVIC_TIM1_BRK_TIM15_IRQN,
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
 *	@param[in]  f_timer_ps            : enum for the timer,value from @ref t_sFMKCPU_TimerInfo
 *	@param[in]  f_hwTimCfg_e           : enum for the hardware timer cfg,value from @ref t_eFMKCPU_HwTimerCfg
 *	@param[in]  f_InfoInit_u32       : the prescaler for the clock timer reference
 *	@param[in]  f_timerCfg_pv         : Specific Configuration for timer Init 
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
 *
 */
static t_eReturnCode s_FMKCPU_Set_BspTimerInit( t_sFMKCPU_TimerInfo * f_timer_ps,
                                                t_eFMKCPU_HwTimerCfg f_hwTimCfg_e,
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
    *	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKCPU_Timer
    *	@param[in]  f_channel_e            : enum value for channel, , value from @ref f_channel_e
    *	@param[in]  f_pwmFreq_u32          : the frequency timer.
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
    */
static t_eReturnCode s_FMKCPU_Set_PwmChannelCfg(t_sFMKCPU_TimerInfo * f_timerInfo_ps,
                                                t_eFMKCPU_InterruptChnl f_channel_e, 
                                                t_uint32 f_pwmFreq_u32);
/**
    *
    *	@brief      Configure a timer channel in Encoder configuration.\n
    *   @note       
    *
    *	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKCPU_Timer
    *	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
    */
static t_eReturnCode s_FMKCPU_Set_EcdrChannelCfg(   t_sFMKCPU_TimerInfo * f_timerInfo_ps,
                                                    t_sFMKCPU_EcdrCfg * f_EcdrCfg_ps,
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
static t_eReturnCode s_FMKCPU_FilledBspEcdrInit(t_sFMKCPU_EcdrCfg * f_EcdrCdg_ps,
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
    *	@param[in]  f_timer_e              : enum value for the priority, value from @ref t_eFMKCPU_Timer
    *	@param[in]  f_channel_e            : enum value for the channel, value from @ref t_eFMKCPU_InterruptChnl
    *	@param[in]  f_MeasTrigger_e        : trigger for interruption, value from @ref t_eFMKCPU_ChnlMeasTrigger
    *	@param[in]  f_ITChannel_cb         : call back function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *  @retval RC_ERROR_NOT_ALLOWED              @ref RC_ERROR_NOT_ALLOWED
    */
    static t_eReturnCode s_FMKCPU_Set_ICChannelCfg( t_eFMKCPU_Timer f_timer_e,
                                                    t_eFMKCPU_InterruptChnl f_channel_e, 
                                                    t_eFMKCPU_ChnlMeasTrigger f_MeasTrigger_e,
                                                    t_cbFMKCPU_InterruptLine f_ITChannel_cb);
/**
*
*	@brief    Configure a timer channel on event configuration.\n
*   @note     This function initialize the timer in event configuration if the
*             timer is not configured yet.\n
*             Once the timer configure is done, update the channel state using function 
*             "FMKCPU_Set_EvntTimerState" and every f_periodms_u32 callback function is called.\n
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
static t_eReturnCode s_FMKCPU_Set_EvntChannelCfg(t_eFMKCPU_Timer f_Timer_e,
                                               t_eFMKCPU_InterruptChnl chnl_e,
                                               t_uint32 f_periodMs_u32,
                                               t_cbFMKCPU_InterruptLine f_ITChannel_cb);
/**
*
*	@brief      Set a InterruptLine  state ON/OFF.\n
*   @note       Using HAL_TIM function & Run mode Configured previously 
*               in API CfgF Function, we start_poll/It/Dma the Line
*           
*
*	@param[in]  f_ITLine_e              : enum value for the timer, value from @ref t_eFMKCPU_InterruptLineIO
*	@param[in]  f_EcdrState_e            : enum value for the channel, value from @ref t_eFMKCPU_EcdrStartOption
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*/
static t_eReturnCode s_FMKCPU_Set_ICOpeState(   t_eFMKCPU_Timer         f_timer_e,
                                                t_eFMKCPU_InterruptChnl f_chnl_e,
                                                t_eFMKCPU_ICOpe         f_ICState_e);

/**
*
*	@brief      Set a InterruptLine  state ON/OFF.\n
*   @note       Using HAL_TIM function & Run mode Configured previously 
*               in API CfgF Function, we start_poll/It/Dma the Line
*           
*
*	@param[in]  f_ITLine_e              : enum value for the timer, value from @ref t_eFMKCPU_InterruptLineIO
*	@param[in]  f_EcdrState_e            : enum value for the channel, value from @ref t_eFMKCPU_EcdrStartOption
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*/
static t_eReturnCode s_FMKCPU_Set_EcdrOpeState( t_eFMKCPU_Timer   f_timer_e,
                                                t_eFMKCPU_EcdrOpe f_EcdrOpe);
/**
*
*	@brief      Set a InterruptLine  state ON/OFF.\n
*   @note       Using HAL_TIM function & Run mode Configured previously 
*               in API CfgF Function, we start_poll/It/Dma the Line
*           
*
*	@param[in]  f_ITLine_e              : enum value for the timer, value from @ref t_eFMKCPU_InterruptLineIO
*	@param[in]  f_EcdrState_e            : enum value for the channel, value from @ref t_eFMKCPU_EcdrStartOption
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*/
static t_eReturnCode s_FMKCPU_GetEcdrARRValue(  t_eFMKCPU_EcdrMode f_EcdrMode_e,
                                                t_uint32 f_rqstArrValue_u32,
                                                t_uint32 * f_ArrValue_pu32);

/**
*
*	@brief      Set a InterruptLine  state ON/OFF.\n
*   @note       Using HAL_TIM function & Run mode Configured previously 
*               in API CfgF Function, we start_poll/It/Dma the Line
*           
*
*	@param[in]  f_ITLine_e              : enum value for the timer, value from @ref t_eFMKCPU_InterruptLineIO
*	@param[in]  f_EcdrState_e            : enum value for the channel, value from @ref t_eFMKCPU_EcdrStartOption
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*/
static t_eReturnCode s_FMKCPU_Set_EvntOpeState( t_eFMKCPU_Timer   f_timer_e,
                                                t_eFMKCPU_InterruptChnl f_chnl_e,
                                                t_eFMKCPU_EvntOpe f_EvntOpe);
/**
*
*	@brief      Set a InterruptLine  state ON/OFF.\n
*   @note       Using HAL_TIM function & Run mode Configured previously 
*               in API CfgF Function, we start_poll/It/Dma the Line
*           
*
*	@param[in]  f_ITLine_e              : enum value for the timer, value from @ref t_eFMKCPU_InterruptLineIO
*	@param[in]  f_EcdrState_e            : enum value for the channel, value from @ref t_eFMKCPU_EcdrStartOption
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*/
static t_eReturnCode s_FMKCPU_Set_PwmOpeState( t_eFMKCPU_Timer   f_timer_e,
                                                t_eFMKCPU_InterruptChnl f_chnl_e,
                                                t_sFMKCPU_PwmOpe f_PwmOpe_s);                                       
/**
 *
 *	@brief      Function to set the state ON/OFF of timer channel
 *
 *	@param[in]  f_timer_e              : enum value for the priority, value from @ref t_eFMKCPU_Timer
 *	@param[in]  f_channel_e            : enum value for the channel, value from @ref t_eFMKCPU_InterruptChnl
 *	@param[in]  f_chnlState_e          : The state of the timer.\n
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
 *
 */
static t_eReturnCode s_FMKCPU_Set_HwChannelState(t_eFMKCPU_Timer f_timer_e,
                                                  t_eFMKCPU_InterruptChnl f_channel_e,
                                                  t_eFMKCPU_ChnlState f_chnlState_e);

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
static void s_FMKCPU_BspRqst_InterruptMngmt(TIM_HandleTypeDef *f_timerIstce_ps, t_eFMKCPU_BspEvent f_cbEvent_e);

/**
 *
 *	@brief      Perform all cyclic operation
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 */
static t_eReturnCode s_FMKCPU_Operational(void);


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
static t_eReturnCode s_FMKCPU_PerformDiagnostic(void);
/**
*
*	@brief      Function to get the bsp channel
*
*	@param[in]  f_channel_e              : enum value for the channel, value from @ref t_eFMKCPU_InterruptChnl
*	@param[in]  f_bspChnl_pu32           : storage for bsp channel.\n
*
*  @retval RC_OK                             @ref RC_OK
*
*/
static t_eReturnCode s_FMKCPU_Get_BspChannel(t_eFMKCPU_InterruptChnl f_channel_e, t_uint32 *f_bspChnl_pu32);
/**
*
*	@brief      Function to get the bsp Encoder Mode
*
*	@param[in]  f_EcdrMode_e       : enum value for the Encoder Mode, value from @ref t_eFMKCPU_EcdrMode
*	@param[in]  f_bspEcdrMode_pu32  : storage for bsp Encoder Mode.\n
*
*  @retval RC_OK                             @ref RC_OK
*
*/
static t_eReturnCode s_FMKCPU_GetBspEcdrMode(t_eFMKCPU_EcdrMode f_EcdrMode_e, t_uint32 *f_bspEcdrMode_pu32);
/**
*
*	@brief      Function to get the bsp Encoder Mode
*
*	@param[in]  f_ICEcdrSelect_e      : enum value for the Encoder IC Selection, value from @ref t_eFMKCPU_ICSelection
*	@param[in]  f_bspEcdrMode_pu32     : storage for bsp IC Selection.\n
*
*  @retval RC_OK                             @ref RC_OK
*
*/
static t_eReturnCode s_FMKCPU_GetBspEcdrSelection(t_eFMKCPU_ICSelection f_ICEcdrSelect_e, t_uint32 *f_bspICEcdrSelect_pu32);
/**
*
*	@brief      Function to get the bsp Encoder Mode
*
*	@param[in]  f_ICEcdrPolarity_e      : enum value for the Encoder IC Selection, value from @ref t_eFMKCPU_ICSelection
*	@param[in]  f_bspICEcdrPolarity_pu32     : storage for bsp IC Selection.\n
*
*  @retval RC_OK                             @ref RC_OK
*
*/
static t_eReturnCode s_FMKCPU_GetBspEcdrPolarity(t_eFMKCPU_EcdrInPolarity f_ICEcdrPolarity_e, t_uint32 *f_bspICEcdrPolarity_pu32);
/**
 *
 *	@brief      Function to get the bsp NVIC priority init
 *
 *	@param[in]  f_priority_e              : enum value for the priority, value from @ref t_eFMKCPU_NVICPriority
 *	@param[in]  BspNVICPriority_pu32      : storage for NVIC priority.\n
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKCPU_Get_BspNVICPriority(t_eFMKCPU_NVICPriority f_priority_e, t_uint32 *BspNVICPriority_pu32);

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
static t_eReturnCode s_FMKCPU_Get_BspICTrigger(t_eFMKCPU_ChnlMeasTrigger f_MeasTrigger_e, t_uint32 *f_bspMeasTrigger_u32);
/**
 *
 *	@brief      Function Timer and channel from a InterruptLine
 *
 *	@param[in]  f_ITLineType_e           : enum value for the type of interruptline, value from @ref t_eFMKCPU_InterruptLineType
 *	@param[in]  ITLine_u                 : union value for the interruptline, value from @ref t_uFMKCPU_InterruptLine
 *	@param[in]  f_timer_pe                : pointor enum value for containing timer, value from @ref t_eFMKCPU_Timer
 *	@param[in]  f_channel_pe              : pointor enum value for containing timer, value from @ref t_eFMKCPU_InterruptChnl
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKCPU_Get_TimChnlFromITLine(t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                                    t_uint32                    f_ITLine_u32,    
                                                    t_eFMKCPU_Timer             *f_timer_pe,
                                                    t_eFMKCPU_InterruptChnl     *f_channel_pe);

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
t_eReturnCode FMKCPU_Init(void)
{
    t_uint8 timIndex_u8;
    t_uint8 chnlIndex_u8;
    t_uint8 ClockIndex_u8;
    t_eFMKCPU_SysClkOsc oscTimerSrc_e;
    t_sFMKCPU_TimerInfo * timerInfo_ps;
    t_sFMKCPU_ChnlInfo * chnlInfo_ps;

    for (timIndex_u8 = (t_uint8)0 ; timIndex_u8 < (t_eFMKCPU_Timer)FMKCPU_TIMER_NB ; timIndex_u8++)
    {
        timerInfo_ps = (t_sFMKCPU_TimerInfo *)(&g_TimerInfo_as[timIndex_u8]);

        timerInfo_ps->IsNVICTimerEnable_b = (t_bool)False;
        timerInfo_ps->isConfigured_b = (t_bool)False;
        timerInfo_ps->IsTimerRunning_b    = (t_bool)False;
        timerInfo_ps->HwCfg_e = FMKCPU_HWTIM_CFG_NB;
        oscTimerSrc_e = c_FmkCpu_RccClockOscSrc_ae[timerInfo_ps->c_clock_e];

        if(g_SysClockValue_ua8[FMKCPU_SYS_CLOCK_SYSTEM] > g_SysClockValue_ua8[oscTimerSrc_e])
        {
            timerInfo_ps->timerFreqMHz_u32 = (t_uint32)((t_uint32)2 * (t_uint32)g_SysClockValue_ua8[oscTimerSrc_e]);
        }
        else 
        {
            timerInfo_ps->timerFreqMHz_u32 = (t_uint32)(g_SysClockValue_ua8[oscTimerSrc_e]);
        }

        for (chnlIndex_u8 = (t_uint8)0 ; chnlIndex_u8 < (t_eFMKCPU_InterruptChnl)FMKCPU_CHANNEL_NB ; chnlIndex_u8++)
        {
            chnlInfo_ps = (t_sFMKCPU_ChnlInfo *)(&timerInfo_ps->Channel_as[chnlIndex_u8]);

            chnlInfo_ps->chnl_cb = NULL_FONCTION;
            SETBIT_16B(chnlInfo_ps->ErrState_u16, FMKCPU_ERRSTATE_OK);
            chnlInfo_ps->IsChnlConfigure_b =  (t_bool)False;
            chnlInfo_ps->RunMode_e = FMKCPU_CNHL_RUNMODE_POLLING;
            chnlInfo_ps->State_e = FMKCPU_CHNLST_DISACTIVATED;
            chnlInfo_ps->DmaInfo_ps.BufferAdd1_pu32 = (t_uint32 *)NULL;
            chnlInfo_ps->DmaInfo_ps.BufferAdd2_pu32 = (t_uint32 *)NULL;
            chnlInfo_ps->DmaInfo_ps.bufferLen_u16 = (t_uint16)0;
        }
    }
    for (ClockIndex_u8 = (t_uint8)0 ; ClockIndex_u8 < FMKCPU_SYS_CLOCK_NB ; ClockIndex_u8++)
    {
        g_SysClockValue_ua8[ClockIndex_u8] = (t_uint8)0;
    }

    return RC_OK;
}
/*********************************
 * FMKCPU_Cyclic
 *********************************/
t_eReturnCode FMKCPU_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch (g_FmkCpu_ModState_e)
    {
        case STATE_CYCLIC_CFG:
        {
            g_FmkCpu_ModState_e = STATE_CYCLIC_WAITING;
            break;
        }
        case STATE_CYCLIC_WAITING:
        {
            // nothing to do, just wait all module are Ope
            break;
        }
        case STATE_CYCLIC_PREOPE:
        {
            g_FmkCpu_ModState_e = STATE_CYCLIC_OPE;
            break; 
        }
        case STATE_CYCLIC_OPE:
        {
            Ret_e = s_FMKCPU_Operational();
            if(Ret_e < RC_OK)
            {
                g_FmkCpu_ModState_e = STATE_CYCLIC_ERROR;
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
 * FMKCPU_GetState
 *********************************/
t_eReturnCode FMKCPU_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_FmkCpu_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * FMKCPU_SetState
 *********************************/
t_eReturnCode FMKCPU_SetState(t_eCyclicModState f_State_e)
{

    g_FmkCpu_ModState_e = f_State_e;

    return RC_OK;
}

/*********************************
 * FMKCPU_Set_Delay
 *********************************/
void FMKCPU_Set_Delay(t_uint32 f_delayms_u32) 
{
    t_uint32 startTime_u32 = (t_uint32)0;
    t_uint32 currentTime_u32 = (t_uint32)0;
    t_uint32 elapsedTime_u32 = (t_uint32)0;
    t_uint32 timeout_u32 = 1000;  // Timeout de 1000ms (1 seconde), ajustable selon vos besoins

    // Récupérer le tick initial
    FMKCPU_Get_Tick(&startTime_u32);

    // Si la valeur de startTime est 0, il y a un problème avec l'initialisation du tick
    if (startTime_u32 == (t_uint32)0)
    {
        return;  // Sortir immédiatement si HAL_GetTick() retourne 0
    }

    while (elapsedTime_u32 < f_delayms_u32)
    {
        // Vérifier si on atteint le timeout
        if (elapsedTime_u32 > timeout_u32)
        {
            // Timeout atteint, sortir de la fonction
            return;
        }

        // Récupérer le tick actuel
        FMKCPU_Get_Tick(&currentTime_u32);

        // Calcul de la différence en tenant compte de l'overflow
        if (currentTime_u32 >= startTime_u32)
        {
            elapsedTime_u32 = currentTime_u32 - startTime_u32;
        }
        else
        {
            // Gestion de l'overflow
            elapsedTime_u32 = (0xFFFFFFFF - startTime_u32) + currentTime_u32;
        }

        // Appeler une fonction d'arrière-plan ou mettre en veille pour économiser du CPU
        __NOP(); // No-operation (placeholder pour ne pas surcharger la CPU)
    }

    return;
}


/*********************************
 * FMKCPU_Get_Tick
 *********************************/
void FMKCPU_Get_Tick(t_uint32 * f_tickms_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if( f_tickms_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_tickms_pu32 = HAL_GetTick();
    }
    else 
    {
        *f_tickms_pu32 = (t_uint32)0;
    }
    return;
}

/*********************************
 * FMKCPU_Set_SysClockCfg
 *********************************/
t_eReturnCode FMKCPU_Set_SysClockCfg(t_eFMKCPU_CoreClockSpeed f_SystemCoreFreq_e)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef  bspRet_e = HAL_OK;
    
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    t_uint32 bspSysClkFreqHz_u32;
    t_uint32 SysClkFreqHz_u32;
    t_sFMKCPU_SysOscCfg * bspOscCfg_ps;


    if(f_SystemCoreFreq_e >= FMKCPU_CORE_CLOCK_SPEED_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        bspOscCfg_ps = (t_sFMKCPU_SysOscCfg *)&c_FmkCpu_SysOscCfg_as[f_SystemCoreFreq_e];

#ifdef FMKCPU_STM32_ECU_FAMILY_G

        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;               // 16 MHz
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
        RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                             // use divider and stuff
        RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;                     // use HSI as PLL source clock
        RCC_OscInitStruct.PLL.PLLM = bspOscCfg_ps->PLLM_Divider_u32;             // Divided the HSI clock sources
        RCC_OscInitStruct.PLL.PLLN = bspOscCfg_ps->PPLN_Multplier_u32;           // Multiplied the HSI clock sources
        RCC_OscInitStruct.PLL.PLLP = bspOscCfg_ps->PLLP_Divider_u32;             // Divided the HSI clock sources -> that gives us PPLP clock source    
        RCC_OscInitStruct.PLL.PLLQ = bspOscCfg_ps->PPLQ_Divider_u32;             // Divided the HSI clock sources -> that gives us PPLQ clock source    
        RCC_OscInitStruct.PLL.PLLR = bspOscCfg_ps->PLLR_Divider_u32;             // Divided the HSI clock sources -> that gives us PPLCLK (SYSCLK) clock sources

        bspRet_e = HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
        
#elif defined FMKCPU_STM32_ECU_FAMILY_F

        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
        RCC_OscInitStruct.HSIState = RCC_HSI_ON;
        RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

#else 
    #error("Unknwon Stm32 Family")
#endif


        RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                            |RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;

        RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK; 
        RCC_ClkInitStruct.AHBCLKDivider  = bspOscCfg_ps->AHB_Divider;
        RCC_ClkInitStruct.APB1CLKDivider = bspOscCfg_ps->APB1_Divider_u32;
        RCC_ClkInitStruct.APB2CLKDivider = bspOscCfg_ps->APB2_Divider_u32;

        if(bspRet_e == HAL_OK)
        bspRet_e = HAL_RCC_OscConfig(&RCC_OscInitStruct);
        if(bspRet_e == HAL_OK)
        {
            bspRet_e = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
        }
        if(bspRet_e != HAL_OK)
        {
            g_FmkCpu_ModState_e = STATE_CYCLIC_ERROR;
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
        else 
        {
            Ret_e = SafeMem_memcpy(&g_SysClockValue_ua8, &c_FmkCpu_CoreClkValue_ua8[f_SystemCoreFreq_e], (t_uint16)(sizeof(t_uint8) * FMKCPU_SYS_CLOCK_NB));
            if(Ret_e == RC_OK)
            {
                //------Get the system core frequency set by the bsp------//
                bspSysClkFreqHz_u32 = HAL_RCC_GetSysClockFreq();
                //------Get the system core frequency wanted by user------//
                SysClkFreqHz_u32 = (t_uint32)g_SysClockValue_ua8[FMKCPU_SYS_CLOCK_SYSTEM];
                //------Compare both value------//
                if(bspSysClkFreqHz_u32 != (t_uint32)(SysClkFreqHz_u32 * CST_MHZ_TO_HZ))
                {
                    Ret_e = RC_ERROR_WRONG_RESULT;
                }
            }
        }
    }

    return Ret_e;
}

/*********************************
 * FMKCPU_Set_SysClockCfg
 *********************************/
t_eReturnCode FMKCPU_Set_HardwareInit(void)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;

    bspRet_e = HAL_Init();
    if(bspRet_e != HAL_OK)
    {
        Ret_e = RC_ERROR_WRONG_RESULT;
    }

#ifdef FMKCPU_STM32_ECU_FAMILY_G
    
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKCPU_Set_HwClock(FMKCPU_RCC_CLK_SYSCFG, FMKCPU_CLOCKPORT_OPE_ENABLE);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKCPU_Set_HwClock(FMKCPU_RCC_CLK_PWR, FMKCPU_CLOCKPORT_OPE_ENABLE);
    }
    if(Ret_e == RC_OK)
    {
        HAL_PWREx_DisableUCPDDeadBattery();
    }
#endif

    if(Ret_e != RC_OK)
    {
        g_FmkCpu_ModState_e = STATE_CYCLIC_ERROR;
    }

    return Ret_e;
}

/*********************************
 * FMKCPU_Set_NVICState
 *********************************/
t_eReturnCode FMKCPU_Set_NVICState(t_eFMKCPU_IRQNType f_IRQN_e, t_eFMKCPU_NVIC_Ope f_OpeState_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 BspPriority_u32 = 0;
    IRQn_Type bspIRQN_e;

    if (f_IRQN_e > (t_eFMKCPU_IRQNType)FMKCPU_NVIC_NB || f_OpeState_e >= FMKCPU_NVIC_OPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = FMKCPU_Get_BspIRQNType(f_IRQN_e, &bspIRQN_e);
    }
    if(Ret_e == RC_OK)
    {
        switch (f_OpeState_e)
        {
            case FMKCPU_NVIC_OPE_ENABLE:
            { // Get the bspPriority using t_eFMKCPU_NVICPriority
                Ret_e = s_FMKCPU_Get_BspNVICPriority(c_FMKCPU_IRQNPriority_ae[f_IRQN_e], &BspPriority_u32);
                if (Ret_e == RC_OK)
                {
                    HAL_NVIC_SetPriority((IRQn_Type)bspIRQN_e, BspPriority_u32, 0);
                    HAL_NVIC_EnableIRQ((IRQn_Type)bspIRQN_e);
                }
                break;
            }

            case FMKCPU_NVIC_OPE_DISABLE:
            {
                HAL_NVIC_DisableIRQ((IRQn_Type)f_IRQN_e);
                break;
            }
            case FMKCPU_NVIC_OPE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }

    return Ret_e;
}

/*********************************
 * FMKCPU_Set_HwClock
 *********************************/
t_eReturnCode FMKCPU_Set_HwClock(t_eFMKCPU_ClockPort f_clkPort_e,
                                  t_eFMKCPU_ClockPortOpe f_OpeState_e)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_clkPort_e >= FMKCPU_RCC_CLK_NB || f_OpeState_e >= FMKCPU_CLOCKPORT_OPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_OpeState_e)
        {
        case FMKCPU_CLOCKPORT_OPE_ENABLE:
        {
#ifdef FMKCPU_STM32_ECU_FAMILY_G
            //------------------- Set Peripheral Clock config if needed----------------//
            Ret_e = FMKCPU_SetPeriphClockCfg(f_clkPort_e);
#endif
            if(Ret_e == RC_OK)
            {
                if (c_FMKCPU_ClkFunctions_apcb[f_clkPort_e].EnableClk_pcb != (t_cbFMKCPU_ClockDisable *)NULL_FONCTION)
                {
                    c_FMKCPU_ClkFunctions_apcb[f_clkPort_e].EnableClk_pcb();
                }
                else
                {
                    Ret_e = RC_WARNING_NO_OPERATION;
                }

            }
            
            break;
        }
        case FMKCPU_CLOCKPORT_OPE_DISABLE:
        {
            if (c_FMKCPU_ClkFunctions_apcb[f_clkPort_e].DisableClk_pcb != (t_cbFMKCPU_ClockDisable *)NULL_FONCTION)
            {
                c_FMKCPU_ClkFunctions_apcb[f_clkPort_e].DisableClk_pcb();
            }
            else
            {
                Ret_e = RC_WARNING_NO_OPERATION;
            }
            break;
        }
        case FMKCPU_CLOCKPORT_OPE_NB:
        default:
            Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
            break;
        }
    }
    return Ret_e;
}

/*********************************
 * FMKCPU_Set_WwdgCfg
 *********************************/
t_eReturnCode FMKCPU_Set_WwdgCfg(t_eFMKCPu_WwdgResetPeriod f_period_e)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;

    Ret_e = FMKCPU_Set_HwClock(FMKCPU_RCC_CLK_WWDG, FMKCPU_CLOCKPORT_OPE_ENABLE);
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKCPU_Set_NVICState(FMKCPU_NVIC_WWDG_IRQN ,FMKCPU_NVIC_OPE_ENABLE);
    }
    if(Ret_e == RC_OK)
    {
        g_wwdgInfos_s.Instance       = WWDG;
        g_wwdgInfos_s.Init.Prescaler = c_FMKCPU_WwdgPeriodcfg_ua16[f_period_e].psc_u16;
        g_wwdgInfos_s.Init.Counter   = c_FMKCPU_WwdgPeriodcfg_ua16[f_period_e].reload_u16;
        g_wwdgInfos_s.Init.Window    = (t_uint32)0x0FFF;
        g_wwdgInfos_s.Init.EWIMode   = WWDG_EWI_ENABLE;
        bspRet_e = HAL_WWDG_Init(&g_wwdgInfos_s);

        if(bspRet_e != HAL_OK)
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
    }

    return Ret_e;
}

/*********************************
 * FMKCPU_ResetWwdg
 *********************************/
t_eReturnCode FMKCPU_ResetWwdg(void)
{
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_eReturnCode Ret_e = RC_OK;
    bspRet_e = HAL_WWDG_Refresh(&g_wwdgInfos_s);

    if(bspRet_e != HAL_OK)
    {
        Ret_e = RC_ERROR_WRONG_RESULT;
    }
    return Ret_e;
}
/*********************************
 * FMKCPU_Set_PWMChannelCfg
 *********************************/
t_eReturnCode FMKCPU_Set_PWMChannelCfg( t_eFMKCPU_InterruptLineIO f_InterruptLine_e,
                                        t_uint32 f_pwmFreq_u32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e;
    t_eFMKCPU_InterruptChnl chnl_e;

    if (f_InterruptLine_e >= FMKCPU_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        timer_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].timer_e;
        chnl_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].channel_e;

        if(g_TimerInfo_as[timer_e].isConfigured_b == (t_bool)False)
        {
            Ret_e = s_FMKCPU_Set_BspTimerInit(&g_TimerInfo_as[timer_e],
                                                FMKCPU_HWTIM_CFG_PWM,
                                                f_pwmFreq_u32,
                                                (void *)NULL);
        }

        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKCPU_Set_PwmChannelCfg( (&g_TimerInfo_as[timer_e]), 
                                                chnl_e,
                                                f_pwmFreq_u32);
        }


        
    }
    return Ret_e;
}

/*********************************
 * FMKCPU_Set_EcdrChannelCfg
 *********************************/
t_eReturnCode FMKCPU_Set_EcdrChannelCfg(t_eFMKCPU_InterruptLineIO f_InterruptLine_e,
                                            t_sFMKCPU_EcdrCfg f_EcdrCfg_s,
                                            t_uint32 f_ARRValue_u32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e;
    t_sFMKCPU_TimerInfo * timerInfo_ps;
    t_eFMKCPU_InterruptChnl chnl_e;
    

    if(f_InterruptLine_e >= FMKCPU_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        timer_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].timer_e;
        chnl_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].channel_e;
        timerInfo_ps = (t_sFMKCPU_TimerInfo *)(&g_TimerInfo_as[timer_e]);

        //----- According Bsp, timer must the CHANNEL 1 and 2 use for Encoder -----//
        if((chnl_e != FMKCPU_CHANNEL_1)
        || (timerInfo_ps->Channel_as[FMKCPU_CHANNEL_1].IsChnlConfigure_b == (t_bool)True)
        || (timerInfo_ps->Channel_as[FMKCPU_CHANNEL_2].IsChnlConfigure_b == (t_bool)True))
        {
            Ret_e = RC_WARNING_WRONG_CONFIG;
        }
       
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKCPU_Set_EcdrChannelCfg(timerInfo_ps,
                                                &f_EcdrCfg_s,
                                                f_ARRValue_u32);
        }
        if(Ret_e == RC_OK)
        {
            //------ Update Information ------//
            timerInfo_ps->Channel_as[FMKCPU_CHANNEL_1].IsChnlConfigure_b = (t_bool)True;
            timerInfo_ps->Channel_as[FMKCPU_CHANNEL_1].RunMode_e = FMKCPU_CNHL_RUNMODE_POLLING;


            timerInfo_ps->Channel_as[FMKCPU_CHANNEL_2].IsChnlConfigure_b = (t_bool)True;
            timerInfo_ps->Channel_as[FMKCPU_CHANNEL_2].RunMode_e = FMKCPU_CNHL_RUNMODE_POLLING;
        }    
        else 
        {
            SETBIT_16B(timerInfo_ps->Channel_as[FMKCPU_CHANNEL_2].ErrState_u16, FMKCPU_ERRSTATE_INIT_FAILED);
            SETBIT_16B(timerInfo_ps->Channel_as[FMKCPU_CHANNEL_1].ErrState_u16, FMKCPU_ERRSTATE_INIT_FAILED);
        }
        
    }
    
    return Ret_e;
}

/*********************************
 * FMKCPU_Get_PWMChannelDuty
 *********************************/
t_eReturnCode FMKCPU_Get_PWMChannelDuty(t_eFMKCPU_InterruptLineIO f_InterruptLine_e, t_uint16 *f_dutyCycle_u16)
{
    /********************************
     *   Some useful information for PWM generation
     *   1 - ARR = Period in Init =  (((freq_timer)/ (freq_pwm * (PSC+1))) -1)
     *   For a dutycyle E [0 - 1000]
     *   2 - CCR1_2_3_4 depending on channel, set the Duty Cycle -> CCR = (DutyCyle/ 1000) * (ARR +1)
     ********************************/
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 BspChannel_u32 = 0;
    t_uint32 comparedValue_u32 = 0;
    t_eFMKCPU_Timer timer_e;
    t_eFMKCPU_InterruptChnl chnl_e;
    t_sFMKCPU_TimerInfo * timerInfo_ps;

   if(f_InterruptLine_e >= FMKCPU_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_FmkCpu_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if (f_dutyCycle_u16 == (t_uint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {

        //---------Get timer/channel information---------//
        timer_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].timer_e;
        chnl_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].channel_e;
        timerInfo_ps = (t_sFMKCPU_TimerInfo *)(&g_TimerInfo_as[timer_e]);
        
        if ((timerInfo_ps->isConfigured_b == (t_bool)False)
        ||  (timerInfo_ps->Channel_as[chnl_e].IsChnlConfigure_b == (t_bool)False))
        {
            Ret_e = RC_ERROR_MISSING_CONFIG;
        }
        if(GETBIT(timerInfo_ps->Channel_as[chnl_e].ErrState_u16, FMKCPU_ERRSTATE_OK != BIT_IS_SET_16B))
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
        //---------get dutycycle only if channel is active---------//
        if (timerInfo_ps->Channel_as[chnl_e].State_e == FMKCPU_CHNLST_DISACTIVATED)
        {
            Ret_e = RC_ERROR_WRONG_CONFIG;
        }
        if (Ret_e == RC_OK)
        {  
            Ret_e = s_FMKCPU_Get_BspChannel(chnl_e, &BspChannel_u32);
            if (Ret_e == RC_OK)
            {
                //---------use BSP function to know dutycyle---------//
                comparedValue_u32 = (t_uint32)HAL_TIM_ReadCapturedValue(&timerInfo_ps->bspTimer_s, BspChannel_u32);

                //---------use formule in description---------//
                *f_dutyCycle_u16 = (t_uint16)(((t_float32)comparedValue_u32 * 1000) /
                                                (t_float32)(timerInfo_ps->bspTimer_s.Instance->ARR + 1));
            }
        }
    }

    return Ret_e;
}

/*********************************
 * FMKCPU_Get_EncoderValues
 *********************************/
t_eReturnCode FMKCPU_Get_EncoderValues( t_eFMKCPU_InterruptLineIO f_EcdrLine_e, 
                                        t_uint32 *f_position_pu32,
                                        t_uint8 *f_direction_pu8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e;
    t_eFMKCPU_InterruptChnl chnl_e;
    t_sFMKCPU_TimerInfo * timerInfo_ps;

    if((f_direction_pu8 == (t_uint8 *)NULL)
    || f_position_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_FmkCpu_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(f_EcdrLine_e >= FMKCPU_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        timer_e = c_FmkCpu_ITLineIOMapp_as[f_EcdrLine_e].timer_e;
        chnl_e = c_FmkCpu_ITLineIOMapp_as[f_EcdrLine_e].channel_e;
        timerInfo_ps = (t_sFMKCPU_TimerInfo *)(&g_TimerInfo_as[timer_e]);

        //--- check running validity
        if(timerInfo_ps->Channel_as[chnl_e].State_e != FMKCPU_CHNLST_ACTIVATED)
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
 * FMKCPU_Set_ICChannelCfg
 *********************************/
t_eReturnCode FMKCPU_Set_ICChannelCfg(t_eFMKCPU_InterruptLineIO f_InterruptLine_e,
                                         t_eFMKCPU_ChnlMeasTrigger f_MeasTrigger_e,
                                         t_cbFMKCPU_InterruptLine  * f_ITChannel_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e;
    t_eFMKCPU_InterruptChnl chnl_e;

    if(f_ITChannel_cb == (t_cbFMKCPU_InterruptLine *)NULL_FONCTION)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if( (f_MeasTrigger_e >= FMKCPU_CHNL_MEAS_NB)
    || (f_InterruptLine_e >= FMKCPU_INTERRUPT_LINE_IO_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get timer/channel information---------//
        timer_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].timer_e;
        chnl_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].channel_e;
        //---------Call Configuration function---------//
        Ret_e = s_FMKCPU_Set_ICChannelCfg(timer_e,
                                          chnl_e,
                                          f_MeasTrigger_e,
                                          f_ITChannel_cb);
    }
    return Ret_e;
}

/*********************************
 * FMKCPU_Set_EvntTimerCfg
 *********************************/
t_eReturnCode FMKCP_Set_EvntTimerCfg(   t_eFMKCPU_InterruptLineEvnt f_EvntITLine_e,
                                        t_uint32 f_periodms_u32,
                                        t_cbFMKCPU_InterruptLine f_ITChannel_cb)
{
    /********************************
     *   Some useful information for Evnt generation
     *   In FMKCPU_ConfigPrivate, 
     * 
     ********************************/
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e;
    t_eFMKCPU_InterruptChnl chnl_e;

    if (f_EvntITLine_e >= FMKCPU_INTERRUPT_LINE_EVNT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_ITChannel_cb == (t_cbFMKCPU_InterruptLine *)NULL_FONCTION)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get timer/channel information---------//
        timer_e = c_FmkCpu_ITLineEvntMapp_as[f_EvntITLine_e].timer_e;
        chnl_e = c_FmkCpu_ITLineEvntMapp_as[f_EvntITLine_e].channel_e;
        //---------Get Event Init Function---------//
        Ret_e = s_FMKCPU_Set_EvntChannelCfg(timer_e,
                                            chnl_e,
                                            f_periodms_u32,
                                            f_ITChannel_cb);
    }
    

    return Ret_e;
}

/*********************************
 * FMKCPU_AddInterruptCallback
 *********************************/
    t_eReturnCode FMKCPU_AddInterruptCallback(t_eFMKCPU_InterruptLineIO f_InterruptLine_e,
                                             t_cbFMKCPU_InterruptLine *f_ITChannel_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e;
    t_eFMKCPU_InterruptChnl chnl_e;

    if(f_InterruptLine_e >= FMKCPU_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_ITChannel_cb == (t_cbFMKCPU_InterruptLine *)NULL_FONCTION)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get timer/channel information---------//
        timer_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].timer_e;
        chnl_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].channel_e;

        //---------See if the configuration of the timer has alrerady been made---------//
        if (g_TimerInfo_as[timer_e].Channel_as[chnl_e].IsChnlConfigure_b != (t_bool)True 
        || g_TimerInfo_as[timer_e].isConfigured_b != (t_bool)True)
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
        else
        {
            //---------Update channel Run mode and Add Callback---------//
            g_TimerInfo_as[timer_e].Channel_as[chnl_e].RunMode_e = FMKCPU_CNHL_RUNMODE_INTERRUPT;
            g_TimerInfo_as[timer_e].Channel_as[chnl_e].chnl_cb = f_ITChannel_cb;
        }
    }
    
    
    
    return Ret_e;
}

/*********************************
 * FMKCPU_Set_InterruptLineOpe
 *********************************/
t_eReturnCode FMKCPU_Set_InterruptLineOpe(t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                            t_uint8 f_IT_line_u8,
                                            t_uFMKCPU_ITLineOpe f_ITLineOpe_u)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e = FMKCPU_TIMER_NB;
    t_eFMKCPU_InterruptChnl chnl_e = FMKCPU_CHANNEL_NB;
    t_sFMKCPU_TimerInfo * timerInfo_ps;

    if((f_ITLineType_e >= FMKCPU_INTERRUPT_LINE_TYPE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get TImer/Channel frol InterruptLine---------//
        Ret_e = s_FMKCPU_Get_TimChnlFromITLine(f_ITLineType_e,
                                               f_IT_line_u8,
                                               &timer_e,
                                               &chnl_e);

        timerInfo_ps = (t_sFMKCPU_TimerInfo *)(&g_TimerInfo_as[timer_e]);

        if((timerInfo_ps->isConfigured_b == (t_bool)False)
        || (timerInfo_ps->Channel_as[chnl_e].IsChnlConfigure_b == (t_bool)False))
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
        if(Ret_e == RC_OK)
        {
            switch(timerInfo_ps->HwCfg_e)
            {
                case FMKCPU_HWTIM_CFG_IC:
                {
                    Ret_e = s_FMKCPU_Set_ICOpeState(timer_e,
                                                    chnl_e,
                                                    (t_eFMKCPU_ICOpe)f_ITLineOpe_u.ICOpe_e);
                    break;
                }
                case FMKCPU_HWTIM_CFG_ECDR:
                {
                    Ret_e = s_FMKCPU_Set_EcdrOpeState(  (t_eFMKCPU_InterruptLineIO)f_IT_line_u8,
                                                        (t_eFMKCPU_EcdrOpe)f_ITLineOpe_u.EncoderOpe_e);
                    break;
                }
                case FMKCPU_HWTIM_CFG_EVNT:
                {
                    Ret_e = s_FMKCPU_Set_EvntOpeState(  timer_e,
                                                        chnl_e,
                                                        (t_eFMKCPU_EvntOpe)f_ITLineOpe_u.EvntOpe_e);
                    break;
                }
                case FMKCPU_HWTIM_CFG_OC:
                case FMKCPU_HWTIM_CFG_OP:
                case FMKCPU_HWTIM_CFG_PWM:
                {
                    Ret_e = s_FMKCPU_Set_PwmOpeState(   timer_e,
                                                        chnl_e,
                                                        (t_sFMKCPU_PwmOpe)f_ITLineOpe_u.PwmOpe_s);
                }
                case FMKCPU_HWTIM_CFG_DAC:
                {
                    Ret_e = RC_WARNING_NO_OPERATION;
                    break;
                }
                case FMKCPU_HWTIM_CFG_NB:
                default:
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;

            }
        }
    }

    return Ret_e;
}

/*********************************
 * FMKCPU_Get_InterruptLineValue
 *********************************/
t_eReturnCode FMKCPU_Get_InterruptLineValue(t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                            t_uint8 f_IT_line_u8,
                                            t_uFMKCPU_ITLineValue * f_ITLineValue_u)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e = FMKCPU_TIMER_NB;
    t_eFMKCPU_InterruptChnl chnl_e = FMKCPU_CHANNEL_NB;
    t_sFMKCPU_TimerInfo * timerInfo_ps;
    t_uint32 oscTimerSrc_u32;

    if((f_ITLineType_e >= FMKCPU_INTERRUPT_LINE_TYPE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_ITLineValue_u == (t_uFMKCPU_ITLineValue *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get TImer/Channel frol InterruptLine---------//
        Ret_e = s_FMKCPU_Get_TimChnlFromITLine(f_ITLineType_e,
                                               f_IT_line_u8,
                                               &timer_e,
                                               &chnl_e);

        timerInfo_ps = (t_sFMKCPU_TimerInfo *)(&g_TimerInfo_as[timer_e]);

        if((timerInfo_ps->isConfigured_b == (t_bool)False)
        || (timerInfo_ps->Channel_as[chnl_e].IsChnlConfigure_b == (t_bool)False))
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
        if(GETBIT(timerInfo_ps->Channel_as[chnl_e].ErrState_u16, FMKCPU_ERRSTATE_OK) == BIT_IS_RESET_16B)
        {
            Ret_e = RC_WARNING_BUSY;
        }
        if(Ret_e == RC_OK)
        {
            switch(timerInfo_ps->HwCfg_e)
            {
                case FMKCPU_HWTIM_CFG_ECDR:
                {
                    f_ITLineValue_u->EncoderValue_s.direction_u8 = (t_uint8)(timerInfo_ps->bspTimer_s.Instance->CR1);
                    f_ITLineValue_u->EncoderValue_s.position_u32 = (t_uint32)(timerInfo_ps->bspTimer_s.Instance->CNT);
                    break;
                }
                
                case FMKCPU_HWTIM_CFG_PWM:
                {
                    if(GETBIT(f_ITLineValue_u->PwmValue_s.updateMask_u8, FMKCPU_PWM_DUTYCYCLE) == BIT_IS_SET_8B)
                    {
                        Ret_e = FMKCPU_Get_PWMChannelDuty(  f_IT_line_u8,
                                                            &f_ITLineValue_u->PwmValue_s.dutyCycle_u16);
                    }
                    if(GETBIT(f_ITLineValue_u->PwmValue_s.updateMask_u8, FMKCPU_PWM_FREQUENCY) == BIT_IS_SET_8B)
                    {
                        // Timer depend on APB1 or APB2, if these clock were divided per 2 or more,
                        // Hardware multiply by 2 the core freqency of the timer
                        // In other word 

                        //------ calculate frequency -----//
                        f_ITLineValue_u->PwmValue_s.frequency_u32 = (t_uint32)((t_float32)timerInfo_ps->timerFreqMHz_u32 * CST_MHZ_TO_HZ) /
                                                                        (t_float32)((timerInfo_ps->bspTimer_s.Instance->ARR + 1) *
                                                                        (timerInfo_ps->bspTimer_s.Instance->PSC + 1));
                    }
                }
                case FMKCPU_HWTIM_CFG_OC:
                case FMKCPU_HWTIM_CFG_OP:
                case FMKCPU_HWTIM_CFG_DAC:
                {
                    Ret_e = RC_WARNING_NO_OPERATION;
                    break;
                }
                case FMKCPU_HWTIM_CFG_NB:
                default:
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;

            }
        }
    }

    return Ret_e;
}
/*********************************
 * FMKCPU_Get_ChannelErrorStatus
 *********************************/
t_eReturnCode FMKCPU_Get_ChannelErrorStatus(    t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                                t_uint32 f_IT_line_u8,
                                                t_uint16 *f_chnlErrInfo_pu16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e = FMKCPU_TIMER_NB;
    t_eFMKCPU_InterruptChnl chnl_e = FMKCPU_CHANNEL_NB;

    if(f_ITLineType_e >= FMKCPU_INTERRUPT_LINE_TYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_FmkCpu_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(f_chnlErrInfo_pu16 == (t_uint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKCPU_Get_TimChnlFromITLine(f_ITLineType_e,
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

/*********************************
 * FMKCPU_Get_RegisterCRRx
 *********************************/
t_eReturnCode FMKCPU_Get_RegisterCRRx(  t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                        t_uint32 f_IT_line_u8,
                                        t_uint32 * f_CCRxValue_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e = FMKCPU_TIMER_NB;
    t_eFMKCPU_InterruptChnl chnl_e = FMKCPU_CHANNEL_NB;
    t_uint32 bspChannel_u32 = 0;
    t_sFMKCPU_TimerInfo * timerInfo_ps;

    if(f_ITLineType_e >= FMKCPU_INTERRUPT_LINE_TYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_FmkCpu_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKCPU_Get_TimChnlFromITLine(f_ITLineType_e,
                                               f_IT_line_u8,
                                               &timer_e,
                                               &chnl_e);
        if(Ret_e == RC_OK)
        {
            timerInfo_ps = (t_sFMKCPU_TimerInfo *)(&g_TimerInfo_as[timer_e]);

            //---------If the bit for chnl_e is running---------//
            if(timerInfo_ps->Channel_as[chnl_e].State_e == FMKCPU_CHNLST_ACTIVATED)
            {
                //---------Read CCRxc from the channel---------//
                Ret_e = s_FMKCPU_Get_BspChannel(chnl_e, &bspChannel_u32);
        
                if(Ret_e == RC_OK)
                {
                    *f_CCRxValue_pu32 = (t_uint32)HAL_TIM_ReadCapturedValue(&timerInfo_ps->bspTimer_s,  
                                                                            bspChannel_u32);
                }
            }
            else 
            {
                Ret_e = RC_WARNING_NO_OPERATION;
                *f_CCRxValue_pu32 = (t_uint32)0;
            }  
        }
    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_FMKCPU_Operational
 *********************************/
static t_eReturnCode s_FMKCPU_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_uint32 SavedTime_u32 = 0;
    t_uint32 currentTime_u32 = 0;

     FMKCPU_Get_Tick(&currentTime_u32);

    if((currentTime_u32 - SavedTime_u32) > (t_uint32)FMKCPU_TIME_BTWN_DIAG_MS)
    {//perform diag on timer / chnl used
        SavedTime_u32 = currentTime_u32;
        Ret_e = s_FMKCPU_PerformDiagnostic();
    }
    // else do other thing( or nothing for now)
    
    return Ret_e;
}

/*********************************
 * s_FMKCPU_PerformDiagnostic
 *********************************/
static t_eReturnCode s_FMKCPU_PerformDiagnostic(void)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_TIM_StateTypeDef bspTimerState_e;
    t_uint16 channelErr_u16 = (t_uint16)0;
    HAL_TIM_ChannelStateTypeDef bspChnlState_e = HAL_TIM_CHANNEL_STATE_READY;
    t_uint32 bspChannel_u32 = 0;
    t_sFMKCPU_TimerInfo * timerInfo_ps;
    t_sFMKCPU_ChnlInfo * chnlInfo_ps;
    t_uint8 CLLI_u8; /**< Channel loop */
    t_uint8 TLLI_u8; /**< Timer loop  */

    for(TLLI_u8 = (t_uint8)0 ; TLLI_u8 < FMKCPU_TIMER_NB ; TLLI_u8++)
    {
        //-----------update information for loop-----------//
        timerInfo_ps = (t_sFMKCPU_TimerInfo *)&g_TimerInfo_as[TLLI_u8];

        //-----------diag for timer currently working/ Running-----------//
        if(timerInfo_ps->IsTimerRunning_b == (t_bool)True)
        {
            //-----------Timer diagnostic-----------//
            bspTimerState_e = c_FMKCPU_TimerFunc_apf[timerInfo_ps->HwCfg_e].GetTimerState_pcb(
                                    &timerInfo_ps->bspTimer_s);

            if((bspTimerState_e  != HAL_TIM_STATE_BUSY)
            && (bspTimerState_e  != HAL_TIM_STATE_READY)) // busy/ Ready means ok for stm32
            {
                //----------- associate bsp err with channel FMKCPU err-----------//
                if(bspTimerState_e  == HAL_TIM_STATE_RESET)
                {
                    SETBIT_16B(channelErr_u16, FMKCPU_ERRSTATE_NOT_CONFIGURED); 
                }
                if(bspTimerState_e  == HAL_TIM_STATE_TIMEOUT)
                {
                    SETBIT_16B(channelErr_u16, FMKCPU_ERRSTATE_TIMEOUT);
                }
                if(bspTimerState_e == HAL_TIM_STATE_ERROR)
                {
                    SETBIT_16B(channelErr_u16, HAL_TIM_STATE_ERROR);  
                }

                //-----------Propagate this error to every channel from this timer-----------//
                for(CLLI_u8 = (t_uint8)0 ; 
                    (CLLI_u8 < FMKCPU_CHANNEL_NB) 
                &&  (timerInfo_ps->Channel_as[CLLI_u8].State_e == FMKCPU_CHNLST_ACTIVATED) ; 
                    CLLI_u8++)
                {
                    timerInfo_ps->Channel_as[CLLI_u8].ErrState_u16 |= channelErr_u16;
                    RESETBIT_16B(timerInfo_ps->Channel_as[CLLI_u8].ErrState_u16, FMKCPU_ERRSTATE_OK);
                }
            }
            //-----------diag for the channel currently used-----------//
            for(CLLI_u8 = (t_uint8)0 ; CLLI_u8 < FMKCPU_CHANNEL_NB ; CLLI_u8++)
            {
                chnlInfo_ps = (t_sFMKCPU_ChnlInfo *)(&timerInfo_ps->Channel_as[CLLI_u8]);

                if(chnlInfo_ps->State_e == FMKCPU_CHNLST_ACTIVATED)
                {
                    Ret_e = s_FMKCPU_Get_BspChannel(CLLI_u8, &bspChannel_u32);

                    if(Ret_e == RC_OK)
                    {
                        bspChnlState_e = HAL_TIM_GetChannelState(&timerInfo_ps->bspTimer_s, bspChannel_u32);

                        if((bspChnlState_e != HAL_TIM_CHANNEL_STATE_BUSY)) // busy means ok
                        {
                            SETBIT_16B(chnlInfo_ps->ErrState_u16, FMKCPU_ERRSTATE_OFF_UNEXPECTED);
                        }
                    }
                }
            }
        }
    }

    return Ret_e;
}


/*********************************
 * s_FMKCPU_Set_PwmChannelCfg
 *********************************/
static t_eReturnCode s_FMKCPU_Set_PwmChannelCfg(t_sFMKCPU_TimerInfo * f_timerInfo_ps,
                                                t_eFMKCPU_InterruptChnl f_channel_e, 
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
    t_uint32 bspChannel_u32 = 0;
    

    //----------Check if timer is not configured yet------------------//
    if ((f_timerInfo_ps->isConfigured_b == (t_bool)False))
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }
    //-------this timer has already been configured and cannot be used for another Type of Configuration------//
    if (f_timerInfo_ps->HwCfg_e != FMKCPU_HWTIM_CFG_PWM)
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
        Ret_e = s_FMKCPU_Get_BspChannel(f_channel_e, &bspChannel_u32);

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
#ifdef FMKCPU_STM32_ECU_FAMILY_G
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
        if (Ret_e == RC_OK)
        { //----------Update INformation------------//
            f_timerInfo_ps->Channel_as[f_channel_e].IsChnlConfigure_b = (t_bool)True;
        }
        else 
        {
            SETBIT_16B(f_timerInfo_ps->Channel_as[f_channel_e].ErrState_u16, FMKCPU_ERRSTATE_INIT_FAILED);
        }
        
    }
    
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Set_EcdrChannelCfg
 *********************************/
static t_eReturnCode s_FMKCPU_Set_EcdrChannelCfg(   t_sFMKCPU_TimerInfo * f_timerInfo_ps,
                                                    t_sFMKCPU_EcdrCfg * f_EcdrCfg_ps,
                                                    t_uint32 f_ARRValue_u32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 computeARRVal_u32;
    TIM_Encoder_InitTypeDef bspEcdrInit_s;
    TIM_MasterConfigTypeDef masterCfg_s;
    HAL_StatusTypeDef bspRet_e = HAL_OK;

    //----------Check if timer is not configured yet------------------//
    if ((f_timerInfo_ps->isConfigured_b == (t_bool)True))
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKCPU_FilledBspEcdrInit(f_EcdrCfg_ps, &bspEcdrInit_s);
        
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKCPU_GetEcdrARRValue(   f_EcdrCfg_ps->HwMode_e,
                                                f_ARRValue_u32,
                                                &computeARRVal_u32);
            if(Ret_e == RC_OK)
            {
                Ret_e = s_FMKCPU_Set_BspTimerInit(  f_timerInfo_ps,
                                                    FMKCPU_HWTIM_CFG_ECDR,
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
            }                                            
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKCPU_Set_ICChannelCfg
 *********************************/
static t_eReturnCode s_FMKCPU_Set_ICChannelCfg( t_eFMKCPU_Timer f_timer_e,
                                                t_eFMKCPU_InterruptChnl f_channel_e, 
                                                t_eFMKCPU_ChnlMeasTrigger f_MeasTrigger_e,
                                                t_cbFMKCPU_InterruptLine f_ITChannel_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef BspRet_e = HAL_OK;
    HAL_TIM_ChannelStateTypeDef bspChannelState_e = HAL_TIM_CHANNEL_STATE_BUSY;
    t_sFMKCPU_TimerInfo * timerInfo_ps = (t_sFMKCPU_TimerInfo *)(&g_TimerInfo_as[f_timer_e]);
    TIM_IC_InitTypeDef BspICInit_s;
    t_uint32 bspChannel_u32 = 0;
    t_uint32 bspMeasPolarity_u32 = 0;
    
    //----------Check if timer is not configured yet------------------//
    if (timerInfo_ps->isConfigured_b == (t_bool)False)
    {
      
        //----------Set Input Compare configuration for all channels------------------//
        #warning('Found the right frequency for Ic Cfg')
        Ret_e = s_FMKCPU_Set_BspTimerInit(  timerInfo_ps,
                                            FMKCPU_HWTIM_CFG_IC,
                                            (t_uint32)1000,
                                            (void *)NULL);
    }
    //-------this timer has already been configured and cannot be used for another Type of Configuration------//
    if (timerInfo_ps->HwCfg_e != FMKCPU_HWTIM_CFG_IC)
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
        Ret_e = s_FMKCPU_Get_BspChannel(f_channel_e, &bspChannel_u32);
        if (Ret_e == RC_OK)
        {
            Ret_e = s_FMKCPU_Get_BspICTrigger(f_MeasTrigger_e, &bspMeasPolarity_u32);
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
            timerInfo_ps->Channel_as[f_channel_e].RunMode_e = FMKCPU_CNHL_RUNMODE_INTERRUPT;
            timerInfo_ps->Channel_as[f_channel_e].chnl_cb = f_ITChannel_cb;
        }
        else
        {
            SETBIT_16B(timerInfo_ps->Channel_as[f_channel_e].ErrState_u16, FMKCPU_ERRSTATE_INIT_FAILED);
        }
    }
    
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Set_EvntChannelCfg
 *********************************/
static t_eReturnCode s_FMKCPU_Set_EvntChannelCfg(t_eFMKCPU_Timer f_timer_e,
                                               t_eFMKCPU_InterruptChnl chnl_e,
                                               t_uint32 f_periodms_u32,
                                               t_cbFMKCPU_InterruptLine f_ITChannel_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 freqEvnt_f32 = 0.0f;
    t_sFMKCPU_TimerInfo * timerInfo_ps = (t_sFMKCPU_TimerInfo *)(&g_TimerInfo_as[f_timer_e]);

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
        Ret_e = s_FMKCPU_Set_BspTimerInit(  timerInfo_ps,
                                            FMKCPU_HWTIM_CFG_EVNT,
                                            freqEvnt_f32,
                                            (void *)NULL);
        if (Ret_e == RC_OK)
        {
            //-------------Update Information-------------//
            timerInfo_ps->isConfigured_b = (t_bool)True;
            timerInfo_ps->Channel_as[chnl_e].chnl_cb = f_ITChannel_cb;
            timerInfo_ps->Channel_as[chnl_e].RunMode_e = FMKCPU_CNHL_RUNMODE_INTERRUPT;
        }
        else
        {
            SETBIT_16B(timerInfo_ps->Channel_as[chnl_e].ErrState_u16, FMKCPU_ERRSTATE_INIT_FAILED);
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKCPU_Set_HwChannelState
 *********************************/
static t_eReturnCode s_FMKCPU_FilledBspEcdrInit(t_sFMKCPU_EcdrCfg * f_EcdrCdg_ps,
                                                TIM_Encoder_InitTypeDef * f_BspEcdrInit_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspEcdrMode_u32;
    t_uint32 bspIC1Selection_u32 = (t_uint32)0;
    t_uint32 bspIC2Selection_u32 = (t_uint32)0;
    t_uint32 bspIC1Polarity_u32 = (t_uint32)0;
    t_uint32 bspIC2Polarity_u32 = (t_uint32)0;

    if((f_EcdrCdg_ps == (t_sFMKCPU_EcdrCfg *)NULL)
    || (f_BspEcdrInit_ps == (TIM_Encoder_InitTypeDef *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //-------- Get Encoder Mode--------//
        Ret_e = s_FMKCPU_GetBspEcdrMode(f_EcdrCdg_ps->HwMode_e, &bspEcdrMode_u32);

        //-------- Get Encoder IC1 Selection--------//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKCPU_GetBspEcdrSelection(f_EcdrCdg_ps->IC1_s.Selection_e, &bspIC1Selection_u32);
        }
        //-------- Get Encoder IC1 Polarity--------//
        if(Ret_e == RC_OK)
        {
            s_FMKCPU_GetBspEcdrPolarity(f_EcdrCdg_ps->IC1_s.Polarity_e, &bspIC1Polarity_u32);
        }
        //-------- Get Encoder IC2 Selection--------//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKCPU_GetBspEcdrSelection(f_EcdrCdg_ps->IC1_s.Selection_e, &bspIC2Selection_u32);
        }
        //-------- Get Encoder IC2 Polarity--------//
        if(Ret_e == RC_OK)
        {
            s_FMKCPU_GetBspEcdrPolarity(f_EcdrCdg_ps->IC1_s.Polarity_e, &bspIC2Polarity_u32);
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
 * s_FMKCPU_Set_EcdrOpeState
 *********************************/
static t_eReturnCode s_FMKCPU_Set_EcdrOpeState( t_eFMKCPU_Timer   f_timer_e,
                                                t_eFMKCPU_EcdrOpe f_EcdrOpe)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_InterruptChnl chnl_e;
    t_eFMKCPU_ChnlState chnlState_e;


    if((f_timer_e >= FMKCPU_TIMER_NB)
    || (f_EcdrOpe >= FMKCPU_ECDR_OPE_NB))
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
                case FMKCPU_ECDR_OPE_START_TI1:
                {
                    chnl_e = FMKCPU_CHANNEL_1;
                    chnlState_e = FMKCPU_CHNLST_ACTIVATED;
                    break;
                }
                case FMKCPU_ECDR_OPE_START_TI2:
                {
                    chnl_e = FMKCPU_CHANNEL_2;
                    chnlState_e = FMKCPU_CHNLST_ACTIVATED;
                    break;
                }
                case FMKCPU_ECDR_OPE_START_BOTH:
                {
                    chnl_e = FMKCPU_CHANNEL_ALL;
                    chnlState_e = FMKCPU_CHNLST_ACTIVATED;
                    break;
                }
                case FMKCPU_ECDR_OPE_STOP_TI1:
                {
                    chnl_e = FMKCPU_CHANNEL_1;
                    chnlState_e = FMKCPU_CHNLST_DISACTIVATED;
                    break;
                }
                case FMKCPU_ECDR_OPE_STOP_TI2:
                {
                    chnl_e = FMKCPU_CHANNEL_2;
                    chnlState_e = FMKCPU_CHNLST_DISACTIVATED;
                    break;
                }
                case FMKCPU_ECDR_OPE_STOP_BOTH:
                {
                    chnl_e = FMKCPU_CHANNEL_ALL;
                    chnlState_e = FMKCPU_CHNLST_DISACTIVATED;
                    break;
                }
                case FMKCPU_ECDR_OPE_NB:
                default:
                {   
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;
                }
            }
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKCPU_Set_HwChannelState(f_timer_e,
                                                chnl_e,
                                                chnlState_e);
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKCPU_Set_EvntOpeState
 *********************************/
static t_eReturnCode s_FMKCPU_Set_EvntOpeState( t_eFMKCPU_Timer         f_timer_e,
                                                t_eFMKCPU_InterruptChnl f_chnl_e,
                                                t_eFMKCPU_EvntOpe       f_EvntOpe)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_ChnlState chnlState_e;


    if((f_timer_e >= FMKCPU_TIMER_NB)
    || (f_chnl_e >= FMKCPU_CHANNEL_NB)
    || (f_EvntOpe >= FMKCPU_EVNT_OPE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_EvntOpe)
        {
            case FMKCPU_EVNT_OPE_START_TIMER:
                chnlState_e = FMKCPU_CHNLST_ACTIVATED;
                break;
            case FMKCPU_EVNT_OPE_STOP_TIMER:
                chnlState_e = FMKCPU_CHNLST_DISACTIVATED;
                break;
            case FMKCPU_EVNT_OPE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKCPU_Set_HwChannelState(f_timer_e,
                                                f_chnl_e,
                                                chnlState_e);
         }
    }

    return Ret_e;
}

/*********************************
 * s_FMKCPU_Set_PwmOpeState
 *********************************/
static t_eReturnCode s_FMKCPU_Set_PwmOpeState(  t_eFMKCPU_Timer   f_timer_e,
                                                t_eFMKCPU_InterruptChnl f_chnl_e,
                                                t_sFMKCPU_PwmOpe f_PwmOpe_s)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sFMKCPU_TimerInfo * timerInfo_ps;
    TIM_TypeDef * bspIsct_ps;
    t_uint32 CCRxValue_u32 = (t_uint32)0;
    t_uint32 bspChannel_u32 = (t_uint32)0;
    t_uint32 bspARRVal_u32 = (t_uint32)0;
    t_uint32 bspPSCVal_u32 = (t_uint32)0;

    if((f_timer_e >= FMKCPU_TIMER_NB)
    || (f_chnl_e >= FMKCPU_CHANNEL_NB)
    || (f_PwmOpe_s.dutyCycle_u16 > FMKCPU_PWM_MAX_DUTY_CYLCE))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        timerInfo_ps = (t_sFMKCPU_TimerInfo *)(&g_TimerInfo_as[f_timer_e]);
        bspIsct_ps = (TIM_TypeDef *)(&timerInfo_ps->bspTimer_s.Instance); 

        if( (timerInfo_ps->isConfigured_b == (t_bool)False)
        ||  (timerInfo_ps->Channel_as[f_chnl_e].IsChnlConfigure_b == (t_bool)False))
        {
            Ret_e = RC_ERROR_MISSING_CONFIG;
        }
        if(GETBIT(timerInfo_ps->Channel_as[f_chnl_e].ErrState_u16, FMKCPU_ERRSTATE_OK) != BIT_IS_SET_16B)
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
        //-------Activate channel-------------//
        if (timerInfo_ps->Channel_as[f_chnl_e].State_e == FMKCPU_CHNLST_DISACTIVATED)
        {
            Ret_e = s_FMKCPU_Set_HwChannelState(f_timer_e, f_chnl_e, FMKCPU_CHNLST_ACTIVATED);
        }
        if(Ret_e == RC_OK)
        {
            // See if bit change frequency is SET
            if(GETBIT(f_PwmOpe_s.updateMask_u8, FMKCPU_PWM_FREQUENCY) == BIT_IS_SET_8B)
            {
                Ret_e = c_FMKCPU_TimerFunc_apf[FMKCPU_HWTIM_CFG_PWM].
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
            if(GETBIT(f_PwmOpe_s.updateMask_u8, FMKCPU_PWM_DUTYCYCLE) == BIT_IS_SET_8B)
            {
                //-------Calculate new CCR value-------------//
                CCRxValue_u32 = (t_uint32)((t_float32)f_PwmOpe_s.dutyCycle_u16 / (t_float32)FMKCPU_PWM_MAX_DUTY_CYLCE *
                            (t_float32)(timerInfo_ps->bspTimer_s.Init.Period + (t_uint32)1));

                //------- Get Bsp Channel -------------//
                Ret_e = s_FMKCPU_Get_BspChannel(f_chnl_e, &bspChannel_u32);
                
                if (Ret_e == RC_OK)
                {
                    //-------Update Duty Cycle-------------//
                    __HAL_TIM_SET_COMPARE(&timerInfo_ps->bspTimer_s, bspChannel_u32, (t_uint32)CCRxValue_u32);
                }
            }
            if(GETBIT(f_PwmOpe_s.updateMask_u8, FMKCPU_PWM_NB_PULSES) == BIT_IS_SET_8B)
            {
                bspIsct_ps->RCR = (t_uint32)(f_PwmOpe_s.nbPulses_u16 + 1);
            }
            //-------Forced actuation-------------//
            HAL_TIM_GenerateEvent(&timerInfo_ps->bspTimer_s, TIM_EVENTSOURCE_UPDATE);
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKCPU_Set_ICOpeState
 *********************************/
static t_eReturnCode s_FMKCPU_Set_ICOpeState(   t_eFMKCPU_Timer         f_timer_e,
                                                t_eFMKCPU_InterruptChnl f_chnl_e,
                                                t_eFMKCPU_ICOpe         f_ICState_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_ChnlState chnlState_e;

    if((f_timer_e >= FMKCPU_TIMER_NB)
    || (f_chnl_e >= FMKCPU_CHANNEL_NB)
    || (f_ICState_e >= FMKCPU_IC_OPE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_ICState_e)
        {
            case FMKCPU_IC_OPE_ENABLE:
            {
                chnlState_e = FMKCPU_CHNLST_ACTIVATED;
                break;
            }
            case FMKCPU_IC_OPE_DISABLE:
            {
                chnlState_e = FMKCPU_CHNLST_DISACTIVATED;
                break;
            }
            case FMKCPU_IC_OPE_NB:
            default:
            {
                Ret_e =  RC_ERROR_NOT_SUPPORTED;
                break;
            }
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKCPU_Set_HwChannelState(f_timer_e,
                                                f_chnl_e,
                                                chnlState_e);
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKCPU_Set_HwChannelState
 *********************************/
static t_eReturnCode s_FMKCPU_Set_HwChannelState(   t_eFMKCPU_Timer f_timer_e,
                                                    t_eFMKCPU_InterruptChnl f_channel_e,
                                                    t_eFMKCPU_ChnlState f_chnlStateOpe_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspChannel_u32 = 0;
    t_sFMKCPU_ChnlInfo  * channel_ps;
    t_sFMKCPU_TimerInfo * timerInfo_ps;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    static t_uint16 s_mskChnState_ua16[FMKCPU_TIMER_NB] = {0};

    // Argument already verify
    timerInfo_ps = (t_sFMKCPU_TimerInfo *)(&g_TimerInfo_as[f_timer_e]);

    if(f_channel_e == FMKCPU_CHANNEL_ALL)
    {
        //----- By default take Channel 1  ------//
        channel_ps = (t_sFMKCPU_ChnlInfo  *)(&g_TimerInfo_as[f_timer_e].Channel_as[FMKCPU_CHANNEL_1]);

    }
    else 
    {
        channel_ps = (t_sFMKCPU_ChnlInfo  *)(&g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e]);
    }

    if (channel_ps->State_e != f_chnlStateOpe_e)
    {
        Ret_e = s_FMKCPU_Get_BspChannel(f_channel_e, &bspChannel_u32);
        if (Ret_e == RC_OK)
        { 
            //--------Depending on wehter we need to activate or deactivate function--------//
            switch (f_chnlStateOpe_e)
            {
                case FMKCPU_CHNLST_ACTIVATED:
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
                        case FMKCPU_CNHL_RUNMODE_POLLING:
                            bspRet_e = c_FMKCPU_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                            StartFuncPoll_pcb(&timerInfo_ps->bspTimer_s,
                                                              (t_uint32)bspChannel_u32);
                            break;
                        case FMKCPU_CNHL_RUNMODE_INTERRUPT:
                            bspRet_e = c_FMKCPU_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                            StartFuncInterrupt_pcb(&timerInfo_ps->bspTimer_s,
                                                                   (t_uint32)bspChannel_u32);
                            break;
                        case FMKCPU_CHNL_RUNMODE_DMA:
                        {
                            bspRet_e = c_FMKCPU_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                            StartFuncDma_pcb(&timerInfo_ps->bspTimer_s,
                                                            (t_uint32)bspChannel_u32,
                                                            channel_ps->DmaInfo_ps.BufferAdd1_pu32,
                                                            channel_ps->DmaInfo_ps.BufferAdd2_pu32,
                                                            channel_ps->DmaInfo_ps.bufferLen_u16);

                            break;
                        }
                        case FMKCPU_CNHL_RUNMODE_NB:
                        default:
                            Ret_e = RC_ERROR_NOT_SUPPORTED;
                            break;
                        }
                    }

                    break;
                }

                case FMKCPU_CHNLST_DISACTIVATED:
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
                            case FMKCPU_CNHL_RUNMODE_POLLING:
                                bspRet_e = c_FMKCPU_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                                StopFuncPoll_pcb(&timerInfo_ps->bspTimer_s,
                                                (t_uint32)bspChannel_u32);
                                break;

                            case FMKCPU_CNHL_RUNMODE_INTERRUPT:
                                bspRet_e = c_FMKCPU_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                                StopFuncInterrupt_pcb(&timerInfo_ps->bspTimer_s,
                                                                       (t_uint32)bspChannel_u32);
                                break;

                            case FMKCPU_CHNL_RUNMODE_DMA:
                            {
                                bspRet_e = c_FMKCPU_TimerFunc_apf[timerInfo_ps->HwCfg_e].
                                            StopFuncDma_pcb(&timerInfo_ps->bspTimer_s,
                                                            (t_uint32)bspChannel_u32);
                                break;
                            }
                            case FMKCPU_CNHL_RUNMODE_NB:
                            default:
                                Ret_e = RC_ERROR_NOT_SUPPORTED;
                                break;
                        }
                    }
                    break;
                }
                case FMKCPU_CHNLST_NB:
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
 * s_FMKCPU_GetEcdrARRValue
 *********************************/
static t_eReturnCode s_FMKCPU_GetEcdrARRValue(  t_eFMKCPU_EcdrMode f_EcdrMode_e,
                                                t_uint32 f_rqstArrValue_u32,
                                                t_uint32 * f_ArrValue_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_EcdrMode_e >= FMKCPU_ECDR_MODE_NB)
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
            case FMKCPU_ECDR_MODE_TI1:
            case FMKCPU_ECDR_MODE_TI2:
            case FMKCPU_ECDR_MODE_CLOCKPLUS_DIRECTION_X1:
            case FMKCPU_ECDR_MODE_TI12:
            case FMKCPU_ECDR_MODE_DIRECTIONAL_CLK_X1_TI12:
            case FMKCPU_ECDR_MODE_X1_TI1:
            case FMKCPU_ECDR_MODE_X1_TI12:
            {
                *f_ArrValue_pu32 = (t_uint32)(f_rqstArrValue_u32);
                break;
            }
            case FMKCPU_ECDR_MODE_DIRECTIONAL_CLK_X2:
            case FMKCPU_ECDR_MODE_CLOCKPLUS_DIRECTION_X2:
            {
                *f_ArrValue_pu32 = (t_uint32)((t_uint32)2 * f_rqstArrValue_u32);
                break;
            }
            case FMKCPU_ECDR_MODE_NB:
            default:
            {
                Ret_e = RC_ERROR_NOT_SUPPORTED;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKCPU_Set_BspTimerInit
 *********************************/
static t_eReturnCode s_FMKCPU_Set_BspTimerInit( t_sFMKCPU_TimerInfo * f_timer_ps,
                                                t_eFMKCPU_HwTimerCfg f_hwTimCfg_e,
                                                t_uint32 f_InfoInit_u32,
                                                void * f_timerCfg_pv)

{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_uint32 bspPeriod_u32;
    t_uint32 bspPrescaler_u32;

    if (f_timer_ps == (t_sFMKCPU_TimerInfo *)NULL)
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
        Ret_e = c_FMKCPU_TimerFunc_apf[f_hwTimCfg_e].
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
            bspRet_e = c_FMKCPU_TimerFunc_apf[f_hwTimCfg_e].TimerInit_pcb(  &f_timer_ps->bspTimer_s,
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
 * s_FMKCPU_BspRqst_InterruptMngmt
 ***********************************/
static void s_FMKCPU_BspRqst_InterruptMngmt(TIM_HandleTypeDef *f_timerIstce_ps, t_eFMKCPU_BspEvent f_cbEvnt_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer Calltimer_e = FMKCPU_TIMER_NB;
    HAL_TIM_ActiveChannel BspITChnl_e = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
    t_eFMKCPU_InterruptChnl ITChnl_e = FMKCPU_CHANNEL_NB;
    const t_sFMKCPU_BspTimerCfg * c_ITLineCfg_ps;
    t_eFMKCPU_InterruptLineType ITType_e;
    t_uint8 maxITLine_u8;
    t_uint8 LLI_u8 = 0;

    // loop to know  which timer it is
    for (LLI_u8 = (t_uint8)0; LLI_u8 < (t_uint8)FMKCPU_TIMER_NB; LLI_u8++)
    {
        if (&g_TimerInfo_as[LLI_u8].bspTimer_s == (TIM_HandleTypeDef *)f_timerIstce_ps)
        {
            Calltimer_e = (t_eFMKCPU_Timer)LLI_u8;
            break;
        }
    }
    if (Calltimer_e >= FMKCPU_TIMER_NB)
    {
        //------------Call somoene to deal with this error------------//
        return; 
    }
    else
    {
        //------------Find Bsp Channel which triggered the interruption------------//
        BspITChnl_e = HAL_TIM_GetActiveChannel(&g_TimerInfo_as[Calltimer_e].bspTimer_s);
        switch (BspITChnl_e)
        {
            case HAL_TIM_ACTIVE_CHANNEL_1:
                ITChnl_e = FMKCPU_CHANNEL_1;
                break;

            case HAL_TIM_ACTIVE_CHANNEL_2:
                ITChnl_e = FMKCPU_CHANNEL_2;
                break;

            case HAL_TIM_ACTIVE_CHANNEL_3:
                ITChnl_e = FMKCPU_CHANNEL_3;
                break;

            case HAL_TIM_ACTIVE_CHANNEL_4:
                ITChnl_e = FMKCPU_CHANNEL_4;
                break;
#ifdef FMKCPU_STM32_ECU_FAMILY_G
            case HAL_TIM_ACTIVE_CHANNEL_5:
                ITChnl_e = FMKCPU_CHANNEL_5;
                break;

            case HAL_TIM_ACTIVE_CHANNEL_6:
                ITChnl_e = FMKCPU_CHANNEL_6;
                break;
#endif
            case HAL_TIM_ACTIVE_CHANNEL_CLEARED:
                //----------The timer himself trigerred the interruption
                // but for us, it's like the CHANNEL_1 did it------------//
                ITChnl_e = FMKCPU_CHANNEL_1;
                break;
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
        //------ Maybe make an switch case later but one condition is faster -----// 
        if(f_cbEvnt_e == FMKCPU_BSP_CB_PWM_PULSE_FINISHED)
        {
            Ret_e = s_FMKCPU_Set_HwChannelState(Calltimer_e, ITChnl_e, FMKCPU_CHNLST_DISACTIVATED);
        }
        if(Ret_e == RC_OK)
        {
            //------------Find Max Interrupt line depending on------------//
            switch (g_TimerInfo_as[Calltimer_e].HwCfg_e)
            {
                case FMKCPU_HWTIM_CFG_PWM:
                case FMKCPU_HWTIM_CFG_IC:
                case FMKCPU_HWTIM_CFG_OC:
                case FMKCPU_HWTIM_CFG_OP:
                case FMKCPU_HWTIM_CFG_ECDR:
                    c_ITLineCfg_ps = (t_sFMKCPU_BspTimerCfg *)&c_FmkCpu_ITLineIOMapp_as;
                    ITType_e = FMKCPU_INTERRUPT_LINE_TYPE_IO;
                    maxITLine_u8 = FMKCPU_INTERRUPT_LINE_IO_NB;
                    break;
                case FMKCPU_HWTIM_CFG_EVNT:
                    c_ITLineCfg_ps = (t_sFMKCPU_BspTimerCfg *)&c_FmkCpu_ITLineEvntMapp_as;
                    ITType_e = FMKCPU_INTERRUPT_LINE_TYPE_EVNT;
                    maxITLine_u8 = FMKCPU_INTERRUPT_LINE_EVNT_NB;
                    break;
                case FMKCPU_HWTIM_CFG_DAC:
                    c_ITLineCfg_ps = (t_sFMKCPU_BspTimerCfg *)&c_FmkCpu_ITLineDacMapp_as;
                    ITType_e = FMKCPU_INTERRUPT_LINE_TYPE_DAC;
                    maxITLine_u8 = FMKCPU_INTERRUPT_LINE_DAC_NB;
                    break;
                default:
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;
            }
            if (Ret_e == RC_OK)
            {   
                //------------Find Interrupt Line------------//
                for (LLI_u8 = (t_uint8)0 ; LLI_u8 < maxITLine_u8 ; LLI_u8++)
                {
                    if((c_ITLineCfg_ps[LLI_u8].timer_e == Calltimer_e)
                    && (c_ITLineCfg_ps[LLI_u8].channel_e == ITChnl_e))
                    {
                        break;
                    }
                }
                if(LLI_u8 < maxITLine_u8)
                {
                    //------------Call Callback user function------------//
                    g_TimerInfo_as[Calltimer_e].Channel_as[ITChnl_e].chnl_cb(ITType_e, LLI_u8);
                }
            }
        }
    }

    return;
}

/*********************************
 * s_FMKCPU_Get_BspChannel
 *********************************/
static t_eReturnCode s_FMKCPU_Get_BspChannel(t_eFMKCPU_InterruptChnl f_channel_e, t_uint32 *f_bspChnl_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_bspChnl_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_channel_e >= FMKCPU_CHANNEL_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_channel_e)
        {
        case FMKCPU_CHANNEL_1:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_1;
            break;
        case FMKCPU_CHANNEL_2:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_2;
            break;
        case FMKCPU_CHANNEL_3:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_3;
            break;
        case FMKCPU_CHANNEL_4:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_4;
            break;
#ifdef FMKCPU_STM32_ECU_FAMILY_G
        case FMKCPU_CHANNEL_5:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_5;
            break;
        case FMKCPU_CHANNEL_6:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_6;
            break;
#endif
        case FMKCPU_CHANNEL_ALL:
            *f_bspChnl_pu32 = (t_uint32)TIM_CHANNEL_ALL;
            break;
        case FMKCPU_CHANNEL_NB:
        default:
            Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
            break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Get_BspTimer
 *********************************/
static t_eReturnCode s_FMKCPU_Get_BspICTrigger(t_eFMKCPU_ChnlMeasTrigger f_MeasTrigger_e, t_uint32 *f_bspMeasTrigger_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_bspMeasTrigger_u32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_MeasTrigger_e >= FMKCPU_CHNL_MEAS_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_MeasTrigger_e)
        {
        case FMKCPU_CHNL_MEAS_FALLING_EDGE:
            *f_bspMeasTrigger_u32 = (t_uint32)TIM_ICPOLARITY_FALLING;
            break;
        case FMKCPU_CHNL_MEAS_RISING_EDGE:
            *f_bspMeasTrigger_u32 = (t_uint32)TIM_ICPOLARITY_RISING;
            break;
        case FMKCPU_CHNL_MEAS_BOTH_EDGE:
            *f_bspMeasTrigger_u32 = (t_uint32)TIM_ICPOLARITY_BOTHEDGE;
            break;
        case FMKCPU_CHNL_MEAS_NB:
        default:
            Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
            break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Get_BspTimer
 *********************************/
static t_eReturnCode s_FMKCPU_GetBspEcdrPolarity(t_eFMKCPU_EcdrInPolarity f_ICEcdrPolarity_e, t_uint32 *f_bspICEcdrPolarity_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_bspICEcdrPolarity_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_ICEcdrPolarity_e >= FMKCPU_ECDR_IN_POLARITY_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_ICEcdrPolarity_e)
        {
            case FMKCPU_ECDR_IN_POLARITY_RISING:
                *f_bspICEcdrPolarity_pu32 = (t_uint32)TIM_ENCODERINPUTPOLARITY_RISING;
                break;
            case FMKCPU_ECDR_IN_POLARITY_FALLING:
                *f_bspICEcdrPolarity_pu32 = (t_uint32)TIM_ENCODERINPUTPOLARITY_FALLING;
                break;
            case FMKCPU_ECDR_IN_POLARITY_NB:
            default:
                Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
                break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Get_BspTimer
 *********************************/
static t_eReturnCode s_FMKCPU_GetBspEcdrMode(t_eFMKCPU_EcdrMode f_EcdrMode_e, t_uint32 *f_bspEcdrMode_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_bspEcdrMode_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_EcdrMode_e >= FMKCPU_ECDR_MODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_EcdrMode_e)
        {
            case FMKCPU_ECDR_MODE_TI1:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_TI1;
                break;
            case FMKCPU_ECDR_MODE_TI2:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_TI2;
                break;
            case FMKCPU_ECDR_MODE_TI12:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_TI2;
                break;
            case FMKCPU_ECDR_MODE_CLOCKPLUS_DIRECTION_X2:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X2;
                break;
            case FMKCPU_ECDR_MODE_CLOCKPLUS_DIRECTION_X1:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X1;
                break;
            case FMKCPU_ECDR_MODE_DIRECTIONAL_CLK_X2:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_DIRECTIONALCLOCK_X2;
                break;
            case FMKCPU_ECDR_MODE_DIRECTIONAL_CLK_X1_TI12:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_DIRECTIONALCLOCK_X1_TI12;
                break;
            case FMKCPU_ECDR_MODE_X1_TI1:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_X1_TI1;
                break;
            case FMKCPU_ECDR_MODE_X1_TI12:
                *f_bspEcdrMode_pu32 = (t_uint32)TIM_ENCODERMODE_X1_TI2;
                break;
            case FMKCPU_ECDR_MODE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;   
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Get_BspTimer
 *********************************/
static t_eReturnCode s_FMKCPU_GetBspEcdrSelection(t_eFMKCPU_ICSelection f_ICEcdrSelect_e, t_uint32 *f_bspICEcdrSelect_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_bspICEcdrSelect_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_ICEcdrSelect_e >= FMKCPU_ICSELECT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_ICEcdrSelect_e)
        {
            case FMKCPU_ICSELECT_INDIRECT_TI:
                *f_bspICEcdrSelect_pu32 = (t_uint32)TIM_ICSELECTION_DIRECTTI;
                break;
            case FMKCPU_ICSELECT_DIRECT_TI:
                *f_bspICEcdrSelect_pu32 = (t_uint32)TIM_ICSELECTION_INDIRECTTI;
                break;
            case FMKCPU_ICSELECT_TRC:
                *f_bspICEcdrSelect_pu32 = (t_uint32)TIM_ICSELECTION_TRC;
                break;
            case FMKCPU_ICSELECT_NB:
            default:
                Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
                break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Get_BspNVICPriority
 *********************************/
static t_eReturnCode s_FMKCPU_Get_BspNVICPriority(t_eFMKCPU_NVICPriority f_priority_e, t_uint32 *f_BspNVICPriority_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_BspNVICPriority_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_priority_e >= FMKCPU_NVIC_PRIORITY_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_priority_e)
        {
            case FMKCPU_NVIC_PRIORITY_LOW:
                *f_BspNVICPriority_pu32 = 6;
                break;
            case FMKCPU_NVIC_PRIORITY_MEDIUM:
                *f_BspNVICPriority_pu32 = 3;
                break;
            case FMKCPU_NVIC_PRIORITY_HIGH:
                *f_BspNVICPriority_pu32 = 0;
                break;

            case FMKCPU_NVIC_PRIORITY_NB:
            default:
                Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
                break;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Get_TimChnlFromITLine
 *********************************/
static t_eReturnCode s_FMKCPU_Get_TimChnlFromITLine(t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                                    t_uint32                    f_ITLine_u32,    
                                                    t_eFMKCPU_Timer             *f_timer_pe,
                                                    t_eFMKCPU_InterruptChnl     *f_channel_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    switch(f_ITLineType_e)
    {
        case FMKCPU_INTERRUPT_LINE_TYPE_IO:
        {
            if(f_ITLine_u32 >= FMKCPU_INTERRUPT_LINE_IO_NB)
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            else 
            {
                *f_timer_pe = c_FmkCpu_ITLineIOMapp_as[(t_eFMKCPU_InterruptLineIO)f_ITLine_u32].timer_e;
                if(g_TimerInfo_as[(*f_timer_pe)].HwCfg_e == FMKCPU_HWTIM_CFG_ECDR)
                {
                    *f_channel_pe = FMKCPU_CHANNEL_ALL;
                }
                else 
                {
                    *f_channel_pe = c_FmkCpu_ITLineIOMapp_as[(t_eFMKCPU_InterruptLineIO)f_ITLine_u32].channel_e;
                }
            }
            break;
        }
        case FMKCPU_INTERRUPT_LINE_TYPE_EVNT:
        {
            if(f_ITLine_u32 >= FMKCPU_INTERRUPT_LINE_EVNT_NB)
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            else 
            {
                *f_timer_pe = c_FmkCpu_ITLineEvntMapp_as[(t_eFMKCPU_InterruptLineEvnt)f_ITLine_u32].timer_e;
                *f_channel_pe = c_FmkCpu_ITLineEvntMapp_as[(t_eFMKCPU_InterruptLineEvnt)f_ITLine_u32].channel_e;
            }
            
            break;
        }
        case FMKCPU_INTERRUPT_LINE_TYPE_DAC:
        {
            if(f_ITLine_u32 >= FMKCPU_INTERRUPT_LINE_EVNT_NB)
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            else 
            {
                *f_timer_pe = c_FmkCpu_ITLineDacMapp_as[(t_eFMKCPU_InterruptLineDAC)f_ITLine_u32].timer_e;
                *f_channel_pe = c_FmkCpu_ITLineDacMapp_as[(t_eFMKCPU_InterruptLineDAC)f_ITLine_u32].channel_e;
            }
            
            break;
        }
        case FMKCPU_INTERRUPT_LINE_TYPE_NB:
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
void TIM1_BRK_TIM15_IRQHandler(void)      {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_15].bspTimer_s);}
/*********************************
 * TIM1_UP_TIM16_IRQHandler
*********************************/
void TIM1_UP_TIM16_IRQHandler(void)       {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_16].bspTimer_s);}
/*********************************
 * TIM1_TRG_COM_TIM17_IRQHandler
*********************************/
void TIM1_TRG_COM_TIM17_IRQHandler(void)  {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_17].bspTimer_s);}
/*********************************
 * TIM1_CC_IRQHandler
*********************************/
void TIM1_CC_IRQHandler(void)             {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_1].bspTimer_s);}
/*********************************
 * TIM2_IRQHandler
*********************************/
void TIM2_IRQHandler(void)                {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_2].bspTimer_s);}
/*********************************
 * TIM3_IRQHandler
*********************************/
void TIM3_IRQHandler(void)                {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_3].bspTimer_s);}
/*********************************
 * TIM4_IRQHandler
*********************************/
void TIM4_IRQHandler(void)                {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_4].bspTimer_s);}
/*********************************
 * TIM6_DAC_IRQHandler
*********************************/
void TIM6_DAC_IRQHandler(void)            {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_6].bspTimer_s);}
/*********************************
 * TIM7_DAC_IRQHandler
*********************************/
void TIM7_DAC_IRQHandler(void)            {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_7].bspTimer_s);}
/*********************************
 * TIM20_BRK_IRQHandler
*********************************/
void TIM20_BRK_IRQHandler(void)           {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_20].bspTimer_s);}
/*********************************
 * TIM20_UP_IRQHandler
*********************************/
void TIM20_UP_IRQHandler(void)            {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_20].bspTimer_s);}
/*********************************
 * TIM20_TRG_COM_IRQHandler
*********************************/
void TIM20_TRG_COM_IRQHandler(void)       {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_20].bspTimer_s);}
/*********************************
 * TIM20_CC_IRQHandler
*********************************/
void TIM20_CC_IRQHandler(void)            {return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_20].bspTimer_s);}
/* CAUTION : Automatic generated code section for TIMx IRQHandler: End */

/**
 *
 *	@brief      Every callback function is now centralized in one function
 *
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_BSP_CB_PERIOD_ELAPSED); }
//void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim); }
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_BSP_CB_IC_CAPTURE); }
//void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim); }
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_BSP_CB_OC_DELAY_ELAPSED); }
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_BSP_CB_PWM_PULSE_FINISHED); }
//void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim); }
//void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_HWTIM_CFG_TRGR); }
void SysTick_Handler(void) { return HAL_IncTick(); }


/***********************************
 * WWDG_IRQHandler
 ***********************************/
void WWDG_IRQHandler(void)
{
    if (g_wwdgInfos_s.Instance->SR & WWDG_SR_EWIF)
    {
        // Effacer le drapeau d'interruption précoce
        g_wwdgInfos_s.Instance->SR &= ~WWDG_SR_EWIF;

        // deal with error
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
