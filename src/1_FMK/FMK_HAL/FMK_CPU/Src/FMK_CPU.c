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
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------TYPEDEF TYPES---------------------------//
//-----------------------------STRUCT TYPES---------------------------//
/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */

/**< Structure of information on a timer-channel*/
typedef struct
{
    t_eFMKCPU_ChnlState State_e;                        /**< State of the channel */
    t_eFMKCPU_ChnlRunMode RunMode_e;                    /**< Run mode for the channel */
    t_eFMKCPU_ChnlErrorState ErrState_e;                /**< Error state of the channel */
    t_cbFMKCPU_InterruptLine *chnl_cb;                  /**< Callback function of the channel */
    t_bool IsChnlConfigure_b;                           /**< Wether or not the channel has beeen configured */
    
} t_sFMKCPU_ChnlInfo;

/**< Structure of information on a timer*/
typedef struct
{
    TIM_HandleTypeDef BspTimer_ps;                      /**< The Timer structure for HAL STM32*/
    t_eFMKCPU_HwTimerCfg HwCfg_e;                       /**< The hardware configuration of the timer */
    t_sFMKCPU_ChnlInfo Channel_as[FMKCPU_CHANNEL_NB];   /**< Channels info structure */
    const t_eFMKCPU_IRQNType c_IRQNType_e;              /**< IRQN type related to the timer */
    const t_eFMKCPU_ClockPort c_clock_e;                /**< RCC clock related to the timer */
    t_bool IsTimerRunning_b;                            /**< Flag for timer is runnning */
    t_bool IsTimerConfigured_b;                         /**< flag timer is configured */  
    t_bool IsNVICTimerEnable_b;                         /**< flag timer NVCIC enable or not */

} t_sFMKCPU_TimerInfo;

// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
static t_eCyclicFuncState g_state_e = STATE_CYCLIC_WAITING;

WWDG_HandleTypeDef g_wwdgInfos_s = {0};

t_eFMKCPU_CoreClockSpeed g_SysClockValue_ae[FMKCPU_SYS_CLOCK_NB];
/* CAUTION : Automatic generated code section for Timer Configuration: Start */
/**< timer information variable */
t_sFMKCPU_TimerInfo g_TimerInfo_as[FMKCPU_TIMER_NB] = {
    {
        // Timer_1
        .BspTimer_ps.Instance = TIM1,
        .c_clock_e = FMKCPU_RCC_CLK_TIM1,
        .c_IRQNType_e = FMKCPU_NVIC_TIM1_BRK_TIM15_IRQN
},
    {
        // Timer_2
        .BspTimer_ps.Instance = TIM2,
        .c_clock_e = FMKCPU_RCC_CLK_TIM2,
        .c_IRQNType_e = FMKCPU_NVIC_TIM2_IRQN
},
    {
        // Timer_3
        .BspTimer_ps.Instance = TIM3,
        .c_clock_e = FMKCPU_RCC_CLK_TIM3,
        .c_IRQNType_e = FMKCPU_NVIC_TIM3_IRQN
},
    {
        // Timer_4
        .BspTimer_ps.Instance = TIM4,
        .c_clock_e = FMKCPU_RCC_CLK_TIM4,
        .c_IRQNType_e = FMKCPU_NVIC_TIM4_IRQN
},
    {
        // Timer_5
        .BspTimer_ps.Instance = TIM5,
        .c_clock_e = FMKCPU_RCC_CLK_TIM5,
        .c_IRQNType_e = FMKCPU_NVIC_TIM5_IRQN
},
    {
        // Timer_6
        .BspTimer_ps.Instance = TIM6,
        .c_clock_e = FMKCPU_RCC_CLK_TIM6,
        .c_IRQNType_e = FMKCPU_NVIC_TIM6_DAC_IRQN
},
    {
        // Timer_7
        .BspTimer_ps.Instance = TIM7,
        .c_clock_e = FMKCPU_RCC_CLK_TIM7,
        .c_IRQNType_e = FMKCPU_NVIC_TIM7_DAC_IRQN
},
    {
        // Timer_8
        .BspTimer_ps.Instance = TIM8,
        .c_clock_e = FMKCPU_RCC_CLK_TIM8,
        .c_IRQNType_e = FMKCPU_NVIC_TIM8_BRK_IRQN
},
    {
        // Timer_15
        .BspTimer_ps.Instance = TIM15,
        .c_clock_e = FMKCPU_RCC_CLK_TIM15,
        .c_IRQNType_e = FMKCPU_NVIC_TIM5_IRQN
},
    {
        // Timer_16
        .BspTimer_ps.Instance = TIM16,
        .c_clock_e = FMKCPU_RCC_CLK_TIM16,
        .c_IRQNType_e = FMKCPU_NVIC_TIM1_UP_TIM16_IRQN
},
    {
        // Timer_17
        .BspTimer_ps.Instance = TIM17,
        .c_clock_e = FMKCPU_RCC_CLK_TIM17,
        .c_IRQNType_e = FMKCPU_NVIC_TIM1_TRG_COM_TIM17_IRQN
},
    {
        // Timer_20
        .BspTimer_ps.Instance = TIM20,
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
 *	@param[in]  f_timer_ps            : enum for the hardware timer cfg,value from @ref t_eFMKCPU_HwTimerCfg
 *	@param[in]  f_prescaler_u32       : the prescaler for the clock timer reference
 *	@param[in]  f_period_u32          : the period value to be loaded into active autoreload register 
 *	@param[in]  f_counterMode_32      : counter mode, up or down 
 *	@param[in]  f_clockDivision_u32   : clock division
 *	@param[in]  f_autoRePreload_u32   : enable/ disable auto reloadpreload
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
 *
 */
static t_eReturnCode s_FMKCPU_Set_BspTimerInit(t_sFMKCPU_TimerInfo * f_timer_ps,
                                                t_eFMKCPU_HwTimerCfg f_hwTimCfg_e,
                                                  t_uint32 f_prescaler_u32,
                                                  t_uint32 f_period_u32,
                                                  t_uint32 f_counterMode_32,
                                                  t_uint32 f_clockDivision_u32,
                                                  t_uint32 f_autoRePreload_u32);
/**
    *
    *	@brief      Configure a timer channel in PWM configuration.\n
    *   @note       First, this configuration set the bsp timer cfg in PWM mode.\n
    *               Once it's done, this function configure the bsp channel in PWM mode too.\n
    *               IMPORTANT, the PWM generation is based on a timer configuration which share
    *               multiple channels, ina sense that, frequency is shared by all PWM channels.\n
    *               In result, the modification of the timer configuration reverbate for all channels.\n          
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_pwmFreq_u32          : the frequency timer.
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
    *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
    */
static t_eReturnCode s_FMKCPU_Set_PwmChannelCfg(t_eFMKCPU_Timer f_timer_e,
                                                t_eFMKCPU_InterruptChnl f_channel_e, 
                                                t_uint32 f_pwmFreq_u32);
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
    static t_eReturnCode s_FMKCPU_Set_ICChannelCfg(t_eFMKCPU_Timer f_timer_e,
                                         t_eFMKCPU_InterruptChnl f_channel_e, 
                                         t_eFMKCPU_ChnlMeasTrigger f_MeasTrigger_e,
                                         t_cbFMKCPU_InterruptLine f_ITChannel_cb);
/**
*
*	@brief    Configure a a timer channel on event configuration.\n
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
static void s_FMKCPU_BspRqst_InterruptMngmt(TIM_HandleTypeDef *f_timerIstce_ps, t_eFMKCPU_HwTimerCfg f_HwTimcfg_e);

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
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
*  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
*
*/
static t_eReturnCode s_FMKCPU_Get_BspChannel(t_eFMKCPU_InterruptChnl f_channel_e, t_uint32 *f_bspChnl_pu32);
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
static t_eReturnCode s_FMKCPU_Get_BspIRQNType(t_eFMKCPU_IRQNType f_IRQN_e, IRQn_Type *f_bspIRQN_pe);
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
                                                    t_uFMKCPU_InterruptLine     f_ITLine_u,    
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

    for (timIndex_u8 = (t_uint8)0 ; timIndex_u8 < (t_eFMKCPU_Timer)FMKCPU_TIMER_NB ; timIndex_u8++)
    {
        g_TimerInfo_as[timIndex_u8].IsNVICTimerEnable_b = (t_bool)False;
        g_TimerInfo_as[timIndex_u8].IsTimerConfigured_b = (t_bool)False;
        g_TimerInfo_as[timIndex_u8].IsTimerRunning_b    = (t_bool)False;
        g_TimerInfo_as[timIndex_u8].HwCfg_e = FMKCPU_HWTIM_CFG_NB;
        for (chnlIndex_u8 = (t_uint8)0 ; chnlIndex_u8 < (t_eFMKCPU_InterruptChnl)FMKCPU_CHANNEL_NB ; chnlIndex_u8++)
        {
            g_TimerInfo_as[timIndex_u8].Channel_as[chnlIndex_u8].chnl_cb = NULL_FONCTION;
            g_TimerInfo_as[timIndex_u8].Channel_as[chnlIndex_u8].ErrState_e = FMKCPU_ERRSTATE_OK;
            
            g_TimerInfo_as[timIndex_u8].Channel_as[chnlIndex_u8].IsChnlConfigure_b =  (t_bool)False;
            g_TimerInfo_as[timIndex_u8].Channel_as[chnlIndex_u8].RunMode_e = FMKCPU_CNHL_RUNMODE_POLLING;
            g_TimerInfo_as[timIndex_u8].Channel_as[chnlIndex_u8].State_e = FMKCPU_CHNLST_DISACTIVATED;
        }
    }
    for (ClockIndex_u8 = (t_uint8)0 ; ClockIndex_u8 < FMKCPU_SYS_CLOCK_NB ; ClockIndex_u8++)
    {
        g_SysClockValue_ae[ClockIndex_u8] = FMKCPU_CORE_CLOCK_SPEED_UNKNOWN;
    }
    return RC_OK;
}
/*********************************
 * FMKCPU_Set_Delay
 *********************************/
t_eReturnCode FMKCPU_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch (g_state_e)
    {

    case STATE_CYCLIC_WAITING:
    {
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_OPE:
    {
        Ret_e = s_FMKCPU_Operational();
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
    {
        g_state_e = STATE_CYCLIC_WAITING;
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
t_eReturnCode FMKCPU_GetState(t_eCyclicFuncState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

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
 * FMKCPU_SetState
 *********************************/
t_eReturnCode FMKCPU_SetState(t_eCyclicFuncState f_State_e)
{

    g_state_e = f_State_e;

    return RC_OK;
}

/*********************************
 * FMKCPU_Set_Delay
 *********************************/
void FMKCPU_Set_Delay(t_uint32 f_delayms_u32)
{
    return HAL_Delay(f_delayms_u32);
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


    if(f_SystemCoreFreq_e > FMKCPU_CORE_CLOCK_SPEED_NB)
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
            g_state_e = STATE_CYCLIC_ERROR;
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
        else 
        {
            Ret_e = SafeMem_memcpy(&g_SysClockValue_ae, &c_FmkCpu_CoreClkValue_ua8[f_SystemCoreFreq_e], (t_uint16)(sizeof(t_uint8) * FMKCPU_SYS_CLOCK_NB));
            if(Ret_e == RC_OK)
            {
                //------Get the system core frequency set by the bsp------//
                bspSysClkFreqHz_u32 = HAL_RCC_GetSysClockFreq();
                //------Get the system core frequency wanted by user------//
                SysClkFreqHz_u32 = (t_uint32)c_FmkCpu_ClkSpeedFreqValueMhz_ua8[f_SystemCoreFreq_e];
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
 * FMKCPU_Get_PeripheryPrescaler
 *********************************/
t_eReturnCode FMKCPU_Get_PeripheryPrescaler(t_eFMKCPU_ClockPeriphExtType  f_SysClkType_e, 
                                            t_uint8 f_idxRccPeriphExt_u8,
                                            t_uint32 * f_bspPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 OscSrcValue_u8;
    t_eFMKCPU_SysClkOsc OscPeriphSrc_e;

    if(f_SysClkType_e > FMKCPU_CLOCK_PERIPH_EXT_TYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspPrescaler_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get Oscillator Source Enum---------//
        OscPeriphSrc_e = c_FmkCpu_RccClockOscSrc_ae[f_idxRccPeriphExt_u8];
        //---------Get Oscillator Source Value---------//
        OscSrcValue_u8 = c_FmkCpu_ClkSpeedFreqValueMhz_ua8[g_SysClockValue_ae[OscPeriphSrc_e]];
        switch(f_SysClkType_e)
        {
            /* CAUTION : Automatic generated code section for Peripheric Prescaler switch case: Start */
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_ADC:
                Ret_e = FMKCPU_GetPrescalerForAdc(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_RNG:
                Ret_e = FMKCPU_GetPrescalerForRng(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_TIM:
                Ret_e = FMKCPU_GetPrescalerForTim(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_USART:
                Ret_e = FMKCPU_GetPrescalerForUsart(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_UART:
                Ret_e = FMKCPU_GetPrescalerForUart(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_I2C:
                Ret_e = FMKCPU_GetPrescalerForI2c(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_USB:
                Ret_e = FMKCPU_GetPrescalerForUsb(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_FDCAN:
                Ret_e = FMKCPU_GetPrescalerForFdcan(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_CAN:
                Ret_e = FMKCPU_GetPrescalerForCan(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_LPTIM:
                Ret_e = FMKCPU_GetPrescalerForLptim(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_SAI1:
                Ret_e = FMKCPU_GetPrescalerForSai1(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_HRTIM:
                Ret_e = FMKCPU_GetPrescalerForHrtim(OscPeriphSrc_e,
                                                 &g_SysClockValue_ae,
                                                (t_uint8)f_idxRccPeriphExt_u8
,                                                f_bspPrescaler_pu32);
                break;
            /* CAUTION : Automatic generated code section for Peripheric Prescaler switch case: End */
            case FMKCPU_CLOCK_PERIPH_EXT_TYPE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
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
#endif

    if(Ret_e != RC_OK)
    {
        g_state_e = STATE_CYCLIC_ERROR;
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

    if (f_IRQN_e > (t_eFMKCPU_IRQNType)FMKCPU_NVIC_NB || f_OpeState_e > FMKCPU_NVIC_OPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKCPU_Get_BspIRQNType(f_IRQN_e, &bspIRQN_e);
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

    if (f_clkPort_e > FMKCPU_RCC_CLK_NB || f_OpeState_e > FMKCPU_CLOCKPORT_OPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_OpeState_e)
        {
        case FMKCPU_CLOCKPORT_OPE_ENABLE:
        {
            if (c_FMKCPU_ClkFunctions_apcb[f_clkPort_e].EnableClk_pcb != (t_cbFMKCPU_ClockDisable *)NULL_FONCTION)
            {
                c_FMKCPU_ClkFunctions_apcb[f_clkPort_e].EnableClk_pcb();
            }
            else
            {
                Ret_e = RC_WARNING_NO_OPERATION;
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
t_eReturnCode FMKCPU_Set_PWMChannelCfg(t_eFMKCPU_InterruptLineIO f_InterruptLine_e, t_uint32 f_pwmFreq_u32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e;
    t_eFMKCPU_InterruptChnl chnl_e;
    

    if (f_InterruptLine_e > FMKCPU_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        timer_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].timer_e;
        chnl_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].channel_e;
        Ret_e = s_FMKCPU_Set_PwmChannelCfg(timer_e, chnl_e, f_pwmFreq_u32);
    }
    return Ret_e;
}

/*********************************
 * FMKCPU_Set_PWMChannelDuty
 *********************************/
t_eReturnCode FMKCPU_Set_PWMChannelDuty(t_eFMKCPU_InterruptLineIO f_InterruptLine_e, t_uint16 f_dutyCycle_u16)
/********************************
 *   Some useful information for PWM generation
 *   1 - ARR = Period in Init = (((freq_timer)/ (freq_pwm * (PSC+1))) - 1)
 *   For a dutycyle E [0 - 1000]
 *   2 - CCR1_2_3_4 depending on channel, set the Duty Cycle -> CCR = (DutyCyle/ 1000) * (ARR +1)
 ********************************/
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 BspChannel_u32 = 0;
    t_uint32 CCRxValue_u32 = 0;
    t_eFMKCPU_Timer timer_e;
    t_eFMKCPU_InterruptChnl chnl_e;

    if(f_InterruptLine_e > FMKCPU_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(Ret_e == RC_OK)
    {   
        //--------- Get timer/channel information---------//
        timer_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].timer_e;
        chnl_e = c_FmkCpu_ITLineIOMapp_as[f_InterruptLine_e].channel_e;

        if (g_TimerInfo_as[timer_e].IsTimerConfigured_b == (t_bool)False 
        || g_TimerInfo_as[timer_e].Channel_as[chnl_e].IsChnlConfigure_b == (t_bool)False)
        {
            Ret_e = RC_ERROR_ALREADY_CONFIGURED;
        }
        if(g_TimerInfo_as[timer_e].Channel_as[chnl_e].ErrState_e != FMKCPU_ERRSTATE_OK)
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
        if (Ret_e == RC_OK)
        {
            //-------Shutdown channel if dutycycle == 0 & channel is active---------//
            //-------else make dutycycle to channel, shut on channel if not on yet---------//
            if ((f_dutyCycle_u16 == (t_uint16)0) 
            && (g_TimerInfo_as[timer_e].Channel_as[chnl_e].State_e == FMKCPU_CHNLST_ACTIVATED))
            {
                //-------Shutdown channel-------------//
                s_FMKCPU_Set_HwChannelState(timer_e, chnl_e, FMKCPU_CHNLST_DISACTIVATED);
            }
            else if (f_dutyCycle_u16 > (t_uint16)FMKCPU_PWM_MIN_DUTY_CYLCE && f_dutyCycle_u16 <= (t_uint16)FMKCPU_PWM_MAX_DUTY_CYLCE)
            { 
                CCRxValue_u32 = (t_uint32)((t_float32)f_dutyCycle_u16 / (t_float32)FMKCPU_PWM_MAX_DUTY_CYLCE *
                            (t_float32)(g_TimerInfo_as[timer_e].BspTimer_ps.Init.Period + (t_uint32)1));
                if (g_TimerInfo_as[timer_e].Channel_as[chnl_e].State_e == FMKCPU_CHNLST_DISACTIVATED)
                {
                    //-------Activate channel-------------//
                    Ret_e = s_FMKCPU_Set_HwChannelState(timer_e, chnl_e, FMKCPU_CHNLST_ACTIVATED);
                }
                if (Ret_e == RC_OK)
                {
                    Ret_e = s_FMKCPU_Get_BspChannel(chnl_e, &BspChannel_u32);
                }
                if (Ret_e == RC_OK)
                {
                    //-------Update Duty Cycle-------------//
                    __HAL_TIM_SET_COMPARE(&g_TimerInfo_as[timer_e].BspTimer_ps, BspChannel_u32, (t_uint32)CCRxValue_u32);
                }
            }
            else
            {
                Ret_e = RC_WARNING_NO_OPERATION;
            }
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


   if(f_InterruptLine_e > FMKCPU_INTERRUPT_LINE_IO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_state_e != STATE_CYCLIC_OPE)
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
        
        if (g_TimerInfo_as[timer_e].IsTimerConfigured_b == (t_bool)False 
        || g_TimerInfo_as[timer_e].Channel_as[chnl_e].IsChnlConfigure_b == (t_bool)False)
        {
            Ret_e = RC_ERROR_MISSING_CONFIG;
        }
        if(g_TimerInfo_as[timer_e].Channel_as[chnl_e].ErrState_e != FMKCPU_ERRSTATE_OK)
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
        //---------get dutycycle only if channel is active---------//
        if (g_TimerInfo_as[timer_e].Channel_as[chnl_e].State_e == FMKCPU_CHNLST_ACTIVATED)
        {
            Ret_e = RC_ERROR_WRONG_CONFIG;
        }
        if (Ret_e == RC_OK)
        {  
            Ret_e = s_FMKCPU_Get_BspChannel(chnl_e, &BspChannel_u32);
            if (Ret_e == RC_OK)
            {
                //---------use BSP function to know dutycyle---------//
                comparedValue_u32 = (t_uint32)HAL_TIM_ReadCapturedValue(&g_TimerInfo_as[timer_e].BspTimer_ps, BspChannel_u32);
                //---------use formule in description---------//
                *f_dutyCycle_u16 = (t_uint16)((comparedValue_u32 * 1000) /
                                                (g_TimerInfo_as[timer_e].BspTimer_ps.Init.Period + 1));
            }
        }
    }
    return Ret_e;
}
/*********************************
 * FMKCPU_Set_ICChannelCfg
 *********************************/
t_eReturnCode FMKCPU_Set_ICChannelCfg(t_eFMKCPU_InterruptLineIO f_InterruptLine_e,
                                         t_eFMKCPU_ChnlMeasTrigger f_MeasTrigger_e,
                                         t_cbFMKCPU_InterruptLine f_ITChannel_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e;
    t_eFMKCPU_InterruptChnl chnl_e;

    if(f_ITChannel_cb == (t_cbFMKCPU_InterruptLine *)NULL_FONCTION)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if( (f_MeasTrigger_e > FMKCPU_CHNL_MEAS_NB)
    || (f_InterruptLine_e > FMKCPU_INTERRUPT_LINE_IO_NB))
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
t_eReturnCode FMKCP_Set_EvntTimerCfg(t_eFMKCPU_InterruptLineEvnt f_EvntITLine_e,
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

    if (f_EvntITLine_e > FMKCPU_INTERRUPT_LINE_EVNT_NB)
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
 * FMKCPU_AddTimerChnlCallback
 *********************************/
    t_eReturnCode FMKCPU_AddTimerChnlCallback(t_eFMKCPU_InterruptLineIO f_InterruptLine_e,
                                             t_cbFMKCPU_InterruptLine *f_ITChannel_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e;
    t_eFMKCPU_InterruptChnl chnl_e;

    if(f_InterruptLine_e > FMKCPU_INTERRUPT_LINE_IO_NB)
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
        || g_TimerInfo_as[timer_e].IsTimerConfigured_b != (t_bool)True)
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
 * FMKCPU_Set_InterruptLineState
 *********************************/
t_eReturnCode FMKCPU_Set_InterruptLineState(t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                                t_uFMKCPU_InterruptLine f_IT_line_u,
                                                t_eFMKCPU_ChnlState f_channelState_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e = FMKCPU_TIMER_NB;
    t_eFMKCPU_InterruptChnl chnl_e = FMKCPU_CHANNEL_NB;

    if((f_channelState_e > FMKCPU_CHNLST_NB)
    || (f_ITLineType_e > FMKCPU_INTERRUPT_LINE_TYPE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(Ret_e == RC_OK)
    {
        //---------Get TImer/Channel frol InterruptLine---------//
        Ret_e = s_FMKCPU_Get_TimChnlFromITLine(f_ITLineType_e,
                                               f_IT_line_u,
                                               &timer_e,
                                               &chnl_e);
        if(Ret_e == RC_OK)
        {
            //---------Set Start/Stop of channel---------//
            Ret_e = s_FMKCPU_Set_HwChannelState(timer_e, chnl_e, f_channelState_e);
        }
    }

    return Ret_e;
}


/*********************************
 * FMKCPU_Get_ChannelErrorStatus
 *********************************/
t_eReturnCode FMKCPU_Get_ChannelErrorStatus(t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                                t_uFMKCPU_InterruptLine f_IT_line_u,
                                                t_eFMKCPU_ChnlErrorState *f_chnlErrInfo_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e = FMKCPU_TIMER_NB;
    t_eFMKCPU_InterruptChnl chnl_e = FMKCPU_CHANNEL_NB;

    if(f_ITLineType_e > FMKCPU_INTERRUPT_LINE_TYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(f_chnlErrInfo_pe == (t_eFMKCPU_ChnlErrorState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKCPU_Get_TimChnlFromITLine(f_ITLineType_e,
                                               f_IT_line_u,
                                               &timer_e,
                                               &chnl_e);
        if(Ret_e == RC_OK)
        {
            *f_chnlErrInfo_pe = g_TimerInfo_as[timer_e].Channel_as[chnl_e].ErrState_e;
        }
        
    }

    return Ret_e;
}

/*********************************
 * FMKCPU_Get_RegisterCRRx
 *********************************/
t_eReturnCode FMKCPU_Get_RegisterCRRx(t_eFMKCPU_InterruptLineType f_ITLineType_e,
                                          t_uFMKCPU_InterruptLine f_IT_line_u,
                                          t_uint32 * f_CCRxValue_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_Timer timer_e = FMKCPU_TIMER_NB;
    t_eFMKCPU_InterruptChnl chnl_e = FMKCPU_CHANNEL_NB;
    t_uint32 bspChannel_u32 = 0;

    if(f_ITLineType_e > FMKCPU_INTERRUPT_LINE_TYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKCPU_Get_TimChnlFromITLine(f_ITLineType_e,
                                               f_IT_line_u,
                                               &timer_e,
                                               &chnl_e);
        if(Ret_e == RC_OK)
        {
            //---------If the bit for chnl_e is running---------//
            if(g_TimerInfo_as[timer_e].Channel_as[chnl_e].State_e == FMKCPU_CHNLST_ACTIVATED)
            {
                //---------Read CCRxc from the channel---------//
                Ret_e = s_FMKCPU_Get_BspChannel(chnl_e, &bspChannel_u32);
        
                if(Ret_e == RC_OK)
                {
                    *f_CCRxValue_pu32 = (t_uint32)HAL_TIM_ReadCapturedValue(&g_TimerInfo_as[timer_e].BspTimer_ps,  bspChannel_u32);
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
    t_eFMKCPU_ChnlErrorState channelErr_e = FMKCPU_ERRSTATE_OK;
    HAL_TIM_ChannelStateTypeDef bspChnlState_e = HAL_TIM_CHANNEL_STATE_READY;
    t_uint32 bspChannel_u32 = 0;
    t_sFMKCPU_TimerInfo * timerInfo_ps;
    t_uint8 CLLI_u8; /**< Channel loop  */
    t_uint8 TLLI_u8; /**< Timer loop  */
    t_bool flagCheckTimerRunning_b;
    for(TLLI_u8 = (t_uint8)0 ; TLLI_u8 < FMKCPU_TIMER_NB ; TLLI_u8++)
    {
        //-----------update information for loop-----------//
        flagCheckTimerRunning_b = (t_bool)False;
        timerInfo_ps = (t_sFMKCPU_TimerInfo *)&g_TimerInfo_as[TLLI_u8];
        //-----------diag for timer currently working/ Running-----------//
        if(timerInfo_ps->IsTimerRunning_b == (t_bool)True)
        {
            bspTimerState_e = c_FMKCPU_BspTimFunc_apf[timerInfo_ps->HwCfg_e].GetTimerState_cb(
                                        &timerInfo_ps->BspTimer_ps);

            if((bspTimerState_e & HAL_TIM_STATE_BUSY) != HAL_TIM_STATE_BUSY) // busy means ok for stm32
            {
                //----------- associate bsp err with channel FMKCPU err-----------//
                if((bspTimerState_e & HAL_TIM_STATE_RESET) == HAL_TIM_STATE_RESET
                || (bspTimerState_e & HAL_TIM_STATE_READY) == HAL_TIM_STATE_READY)
                {
                    channelErr_e |= FMKCPU_ERRSTATE_NOT_CONFIGURED;
                }
                if( (bspTimerState_e & HAL_TIM_STATE_TIMEOUT) == HAL_TIM_STATE_TIMEOUT)
                {
                    channelErr_e |= FMKCPU_ERRSTATE_TIMEOUT;
                }
                if((bspTimerState_e & HAL_TIM_STATE_ERROR) == HAL_TIM_STATE_ERROR)
                {
                    //-----------bspTimerState_e = HAL_TIM_STATE_ERROR-----------//
                    channelErr_e |= FMKCPU_ERRSTATE_UNKNOWN;   
                }
                //-----------Propagate this error to every channel from this timer-----------//
                for(CLLI_u8 = (t_uint8)0 ; CLLI_u8 < FMKCPU_CHANNEL_NB ; CLLI_u8++)
                {
                    if(timerInfo_ps->Channel_as[CLLI_u8].State_e == FMKCPU_CHNLST_ACTIVATED)
                    {
                        flagCheckTimerRunning_b = (t_bool)True;
                        timerInfo_ps->Channel_as[CLLI_u8].ErrState_e |= channelErr_e;
                    }
                }
            }
            //-----------diag for the channel currently used-----------//
            for(CLLI_u8 = (t_uint8)0 ; CLLI_u8 < FMKCPU_CHANNEL_NB ; CLLI_u8++)
            {
                if(timerInfo_ps->Channel_as[CLLI_u8].State_e == FMKCPU_CHNLST_ACTIVATED)
                {
                    flagCheckTimerRunning_b = (t_bool)True;
                    Ret_e = s_FMKCPU_Get_BspChannel(CLLI_u8, &bspChannel_u32);
                    if(Ret_e == RC_OK)
                    {
                        bspChnlState_e = HAL_TIM_GetChannelState(&timerInfo_ps->BspTimer_ps, bspChannel_u32);
                        if((bspChnlState_e & HAL_TIM_CHANNEL_STATE_BUSY) != HAL_TIM_CHANNEL_STATE_BUSY) // busy means ok
                        {
                            timerInfo_ps->Channel_as[CLLI_u8].ErrState_e |= FMKCPU_ERRSTATE_UNKNOWN;
                        }
                    }
                }
            }
            if (flagCheckTimerRunning_b == (t_bool)False)
            {
                timerInfo_ps->IsTimerRunning_b = (t_bool)False;
            }
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCPU_PerformDiagnostic
 *********************************/
static t_eReturnCode s_FMKCPU_Set_PwmChannelCfg(t_eFMKCPU_Timer f_timer_e,
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
    TIM_MasterConfigTypeDef masterCfg_s = {0};
    TIM_OC_InitTypeDef BspOcInit_s;
    t_uint32 bspChannel_u32 = 0;
    t_uint32 bspPeriod_u32;
    t_uint32 bspPrescaler_u32;
    t_uint8 timerOscFreqMhz_u8;
    t_eFMKCPU_SysClkOsc OscTimerSrc_e;

    //----------Check if timer is not configured yet------------------//
    if ((g_TimerInfo_as[f_timer_e].IsTimerConfigured_b == (t_bool)False))
    {
        //----------Get the prescalerr for the timer ------------------//
        Ret_e = FMKCPU_Get_PeripheryPrescaler(FMKCPU_CLOCK_PERIPH_EXT_TYPE_TIM, 
                                            g_TimerInfo_as[f_timer_e].c_clock_e,
                                            &bspPrescaler_u32);
        if(Ret_e == RC_OK)
        {
            //-------------Calculate the Timer Source Frequency-------------//
            //                      Rcc Clock Src
            OscTimerSrc_e = c_FmkCpu_RccClockOscSrc_ae[g_TimerInfo_as[f_timer_e].c_clock_e];
            //                          Value u8 from enum          Enum Frequency speed for the oscillator Source
            timerOscFreqMhz_u8 = c_FmkCpu_ClkSpeedFreqValueMhz_ua8[ g_SysClockValue_ae[OscTimerSrc_e] ];
            //-------------Calculate  Period-------------//
            bspPeriod_u32 = (t_uint32)(((timerOscFreqMhz_u8 * CST_MHZ_TO_HZ) /
                                                (f_pwmFreq_u32 * (bspPrescaler_u32))) - (t_uint32)1);
            //----------Set PWM Timer configuration for all channels------------------//
            Ret_e = s_FMKCPU_Set_BspTimerInit(&g_TimerInfo_as[f_timer_e],
                                                        FMKCPU_HWTIM_CFG_PWM,
                                                        (t_uint32)bspPrescaler_u32,
                                                        (t_uint32)bspPeriod_u32,
                                                        (t_uint32)TIM_COUNTERMODE_UP,
                                                        (t_uint32)TIM_CLOCKDIVISION_DIV1,
                                                        (t_uint32)TIM_AUTORELOAD_PRELOAD_DISABLE); // Irreveleent in PWM                           
            masterCfg_s.MasterOutputTrigger = TIM_TRGO_RESET;
            masterCfg_s.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
            BspRet_e = HAL_TIMEx_MasterConfigSynchronization(&g_TimerInfo_as[f_timer_e].BspTimer_ps,
                                                                &masterCfg_s);
            if(BspRet_e != HAL_OK)
            {
                g_TimerInfo_as[f_timer_e].IsTimerConfigured_b = (t_bool)False;
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
        }
    }
    //-------this timer has already been configured and cannot be used for another Type of Configuration------//
    if (g_TimerInfo_as[f_timer_e].HwCfg_e != FMKCPU_HWTIM_CFG_PWM)
    { 
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    //-------Channel is already used------//
    if (g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].IsChnlConfigure_b == (t_bool)True)
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
            bspChannelState_e = HAL_TIM_GetChannelState(&g_TimerInfo_as[f_timer_e].BspTimer_ps, bspChannel_u32);
            if(bspChannelState_e == HAL_TIM_CHANNEL_STATE_READY)
            {
                BspOcInit_s.OCMode = (t_uint32)TIM_OCMODE_PWM1; 
                BspOcInit_s.Pulse = (t_uint32)0;   // set init DutyCycle to 0
                BspOcInit_s.OCNPolarity = (t_uint32)TIM_OCPOLARITY_HIGH;
                BspOcInit_s.OCFastMode = (t_uint32)TIM_OCFAST_DISABLE;
                BspRet_e = HAL_TIM_PWM_ConfigChannel(&g_TimerInfo_as[f_timer_e].BspTimer_ps,
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
            g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].IsChnlConfigure_b = (t_bool)True;
        }
        else 
        {
            g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].ErrState_e |= FMKCPU_ERRSTATE_INIT_FAILED;
        }
        
    }
    
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Set_ICChannelCfg
 *********************************/
static t_eReturnCode s_FMKCPU_Set_ICChannelCfg(t_eFMKCPU_Timer f_timer_e,
                                         t_eFMKCPU_InterruptChnl f_channel_e, 
                                         t_eFMKCPU_ChnlMeasTrigger f_MeasTrigger_e,
                                         t_cbFMKCPU_InterruptLine f_ITChannel_cb)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef BspRet_e = HAL_OK;
    HAL_TIM_ChannelStateTypeDef bspChannelState_e = HAL_TIM_CHANNEL_STATE_BUSY;
    TIM_IC_InitTypeDef BspICInit_s;
    t_uint32 bspChannel_u32 = 0;
    t_uint32 bspMeasPolarity_u32 = 0;
    t_uint32 bspICPrescaler_u32 = 0;

    
    //----------Check if timer is not configured yet------------------//
    if ((g_TimerInfo_as[f_timer_e].IsTimerConfigured_b == (t_bool)False) && (Ret_e == RC_OK))
    {
        //----------Get Init prescaler------------------//
        Ret_e = FMKCPU_Get_PeripheryPrescaler(FMKCPU_CLOCK_PERIPH_EXT_TYPE_TIM, 
                                            g_TimerInfo_as[f_timer_e].c_clock_e,
                                            &bspICPrescaler_u32);
        if(Ret_e == RC_OK)
        {
            //----------Set PWM Input Compare configuration for all channels------------------//
            Ret_e = s_FMKCPU_Set_BspTimerInit(&g_TimerInfo_as[f_timer_e],
                                        FMKCPU_HWTIM_CFG_IC,
                                        (t_uint32)bspICPrescaler_u32,
                                        (t_uint32)FMKCPU_TIMER_IC_ARR,
                                        (t_uint32)TIM_COUNTERMODE_UP,
                                        (t_uint32)TIM_CLOCKDIVISION_DIV1,
                                        (t_uint32)TIM_AUTORELOAD_PRELOAD_DISABLE);
        }
                
    }
    //-------this timer has already been configured and cannot be used for another Type of Configuration------//
    if (g_TimerInfo_as[f_timer_e].HwCfg_e != FMKCPU_HWTIM_CFG_IC)
    {
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    //-------Channel is already used------//
    if (g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].IsChnlConfigure_b == (t_bool)True)
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
            bspChannelState_e = HAL_TIM_GetChannelState(&g_TimerInfo_as[f_timer_e].BspTimer_ps, bspChannel_u32);
            
            if(bspChannelState_e == HAL_TIM_CHANNEL_STATE_READY)
            {
                //-------Configure bsp channel structure------//
                BspICInit_s.ICPolarity = (t_uint32)bspMeasPolarity_u32;
                BspICInit_s.ICSelection = (t_uint32)TIM_ICSELECTION_DIRECTTI;
                BspICInit_s.ICPrescaler = (t_uint32)TIM_ICPSC_DIV1;
                BspICInit_s.ICFilter = (t_uint32)0;
                BspRet_e = HAL_TIM_IC_ConfigChannel(&g_TimerInfo_as[f_timer_e].BspTimer_ps,
                                                    &BspICInit_s,
                                                    bspChannel_u32);
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
        { 
            //-------update information-------//
            g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].IsChnlConfigure_b = (t_bool)True;
            g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].RunMode_e = FMKCPU_CNHL_RUNMODE_INTERRUPT;
            g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].chnl_cb = f_ITChannel_cb;
        }
        else
        {
            g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].ErrState_e |= FMKCPU_ERRSTATE_INIT_FAILED;   
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
    t_uint32 bspPeriod_u32 = 0; 
    t_uint32 prescaler_u32 = 0;
    t_uint8 timerOscFreqMhz_u8 = 0;
    t_eFMKCPU_SysClkOsc OscTimerSrc_e;

    //-------------See if timer has already been configured-------------//
    if(g_TimerInfo_as[f_timer_e].IsTimerConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if(Ret_e == RC_OK)
    {
        //------------- Choose the Prescaler the more adapted to Period requested-------------//
        if(f_periodms_u32 < FMKCPU_TIMER_EVNT_MAX_LOW_PERIOD_MS)
        {
            prescaler_u32 = FMKCPU_TIMER_EVNT_PSC_HIGH; 
        }
        else 
        {
            prescaler_u32 = FMKCPU_TIMER_EVNT_PSC_LOW;
        }
        //-------------Calculate the Timer Source Frequency-------------//
        //                      Rcc Clock Src
        OscTimerSrc_e = c_FmkCpu_RccClockOscSrc_ae[g_TimerInfo_as[f_timer_e].c_clock_e];
        //                          Value u8 from enum          Enum Frequency speed for the oscillator Source
        timerOscFreqMhz_u8 = c_FmkCpu_ClkSpeedFreqValueMhz_ua8[ g_SysClockValue_ae[OscTimerSrc_e] ];
        //-------------Calculate the timer Period-------------//
        bspPeriod_u32 = (t_uint32)((t_float32)((t_float32)(timerOscFreqMhz_u8 * CST_MHZ_TO_HZ) * (t_float32)(f_periodms_u32 / 1000)) / 
                                                (t_float32)((prescaler_u32 + 1)));

        //-------------Call Init Function-------------//
        Ret_e = s_FMKCPU_Set_BspTimerInit(&g_TimerInfo_as[f_timer_e],
                                            FMKCPU_HWTIM_CFG_EVNT,
                                            (t_uint32)(prescaler_u32 - (t_uint32)1),
                                            (t_uint32)(bspPeriod_u32 - (t_uint32)1),
                                            (t_uint32)TIM_COUNTERMODE_UP,
                                            (t_uint32)TIM_CLOCKDIVISION_DIV1,
                                            (t_uint32)TIM_AUTORELOAD_PRELOAD_DISABLE);
        if (Ret_e == RC_OK)
        {
            //-------------Update Information-------------//
            g_TimerInfo_as[f_timer_e].IsTimerConfigured_b = (t_bool)True;
            g_TimerInfo_as[f_timer_e].Channel_as[chnl_e].chnl_cb = f_ITChannel_cb;
            g_TimerInfo_as[f_timer_e].Channel_as[chnl_e].RunMode_e = FMKCPU_CNHL_RUNMODE_INTERRUPT;
        }
        else 
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
    }

    return Ret_e;
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
    if (f_channel_e > FMKCPU_CHANNEL_NB)
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
    if (f_MeasTrigger_e > FMKCPU_CHNL_MEAS_NB)
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
 * s_FMKCPU_Get_BspNVICPriority
 *********************************/
static t_eReturnCode s_FMKCPU_Get_BspNVICPriority(t_eFMKCPU_NVICPriority f_priority_e, t_uint32 *f_BspNVICPriority_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_BspNVICPriority_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_priority_e > FMKCPU_NVIC_PRIORITY_NB)
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
                                                    t_uFMKCPU_InterruptLine     f_ITLine_u,    
                                                    t_eFMKCPU_Timer             *f_timer_pe,
                                                    t_eFMKCPU_InterruptChnl     *f_channel_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    switch(f_ITLineType_e)
    {
        case FMKCPU_INTERRUPT_LINE_TYPE_IO:
        {
            *f_timer_pe = c_FmkCpu_ITLineIOMapp_as[(t_eFMKCPU_InterruptLineIO)f_ITLine_u.ITLine_IO_e].timer_e;
            *f_channel_pe = c_FmkCpu_ITLineIOMapp_as[(t_eFMKCPU_InterruptLineIO)f_ITLine_u.ITLine_IO_e].channel_e;
            break;
        }
        case FMKCPU_INTERRUPT_LINE_TYPE_EVNT:
        {
            *f_timer_pe = c_FmkCpu_ITLineEvntMapp_as[(t_eFMKCPU_InterruptLineEvnt)f_ITLine_u.ITLine_Evnt_e].timer_e;
            *f_channel_pe = c_FmkCpu_ITLineEvntMapp_as[(t_eFMKCPU_InterruptLineEvnt)f_ITLine_u.ITLine_Evnt_e].channel_e;
            break;
        }
        case FMKCPU_INTERRUPT_LINE_TYPE_DAC:
        {
            *f_timer_pe = c_FmkCpu_ITLineDacMapp_as[(t_eFMKCPU_InterruptLineDAC)f_ITLine_u.ITLine_Dac_e].timer_e;
            *f_channel_pe = c_FmkCpu_ITLineDacMapp_as[(t_eFMKCPU_InterruptLineDAC)f_ITLine_u.ITLine_Dac_e].channel_e;
            break;
        }
        case FMKCPU_INTERRUPT_LINE_TYPE_NB:
        default:
            Ret_e = RC_ERROR_NOT_SUPPORTED;
            break;
    }
    
    return Ret_e;
}
/*********************************
 * s_FMKCPU_Set_HwChannelState
 *********************************/
static t_eReturnCode s_FMKCPU_Set_HwChannelState(t_eFMKCPU_Timer f_timer_e,
                                                  t_eFMKCPU_InterruptChnl f_channel_e,
                                                  t_eFMKCPU_ChnlState f_chnlStateOpe_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspChannel_u32 = 0;
    t_sFMKCPU_ChnlInfo  * channel_ps;
    t_sFMKCPU_TimerInfo * timer_ps;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_bool isTimerSetOn_b = False;
    // Argument already verify
    channel_ps = &g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e];
    timer_ps = &g_TimerInfo_as[f_timer_e];
    if (channel_ps->State_e != f_chnlStateOpe_e)
    {
        Ret_e = s_FMKCPU_Get_BspChannel(f_channel_e, &bspChannel_u32);
        if (Ret_e == RC_OK)
        { //--------Depending on wehter we need to activate or deactivate function--------//
            switch (f_chnlStateOpe_e)
            {
                case FMKCPU_CHNLST_ACTIVATED:
                { 
                    //-------- We have to start HALfunction in Basic or Interrupt depending on f_chnlRunMode_e--------//
                    //--------call the right HAL function Polling or Interrupt mode--------//
                    if (g_TimerInfo_as[f_timer_e].IsNVICTimerEnable_b == (t_bool)False)
                    {
                        Ret_e = FMKCPU_Set_NVICState(g_TimerInfo_as[f_timer_e].c_IRQNType_e, FMKCPU_NVIC_OPE_ENABLE);
                    }
                    if (Ret_e == RC_OK)
                    {
                        isTimerSetOn_b = (t_bool)True;
                        switch (channel_ps->RunMode_e)
                        {
                        case FMKCPU_CNHL_RUNMODE_POLLING:
                            bspRet_e = c_FMKCPU_BspTimFunc_apf[timer_ps->HwCfg_e].StartFuncPoll_pcb(&g_TimerInfo_as[f_timer_e].BspTimer_ps,
                                                                                                            (t_uint32)bspChannel_u32);
                            break;
                        case FMKCPU_CNHL_RUNMODE_INTERRUPT:
                            bspRet_e = c_FMKCPU_BspTimFunc_apf[timer_ps->HwCfg_e].StartFuncInterrupt_pcb(&g_TimerInfo_as[f_timer_e].BspTimer_ps,
                                                                                                                (t_uint32)bspChannel_u32);
                            break;
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
                    if (g_TimerInfo_as[f_timer_e].IsNVICTimerEnable_b == (t_bool)True)
                    {
                        Ret_e = FMKCPU_Set_NVICState(g_TimerInfo_as[f_timer_e].c_IRQNType_e, FMKCPU_NVIC_OPE_DISABLE);
                    }
                    if (Ret_e == RC_OK)
                    {
                        switch (channel_ps->RunMode_e)
                        {
                            case FMKCPU_CNHL_RUNMODE_POLLING:
                                bspRet_e = c_FMKCPU_BspTimFunc_apf[timer_ps->HwCfg_e].StopFuncPoll_pcb(&g_TimerInfo_as[f_timer_e].BspTimer_ps,
                                                                                                            (t_uint32)bspChannel_u32);
                                break;
                            case FMKCPU_CNHL_RUNMODE_INTERRUPT:
                                bspRet_e = c_FMKCPU_BspTimFunc_apf[timer_ps->HwCfg_e].StopFuncInterrupt_pcb(&g_TimerInfo_as[f_timer_e].BspTimer_ps,
                                                                                                                    (t_uint32)bspChannel_u32);
                                break;
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
                if(isTimerSetOn_b == (t_bool)True)
                {
                    g_TimerInfo_as[f_timer_e].IsTimerRunning_b  = (t_bool)True;
                }
                channel_ps->State_e = f_chnlStateOpe_e;
            }
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Set_BspTimerInit
 *********************************/
static t_eReturnCode s_FMKCPU_Set_BspTimerInit(t_sFMKCPU_TimerInfo * f_timer_ps,
                                                t_eFMKCPU_HwTimerCfg f_hwTimCfg_e,
                                                  t_uint32 f_prescaler_u32,
                                                  t_uint32 f_period_u32,
                                                  t_uint32 f_counterMode_32,
                                                  t_uint32 f_clockDivision_u32,
                                                  t_uint32 f_autoRePreload_u32)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;

    if (f_timer_ps == (t_sFMKCPU_TimerInfo *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKCPU_Set_HwClock(f_timer_ps->c_clock_e, FMKCPU_CLOCKPORT_OPE_ENABLE);
    }
    if (Ret_e == RC_OK)
    {
        f_timer_ps->BspTimer_ps.Init.Prescaler = f_prescaler_u32;
        f_timer_ps->BspTimer_ps.Init.Period = f_period_u32;
        f_timer_ps->BspTimer_ps.Init.CounterMode = f_counterMode_32;
        f_timer_ps->BspTimer_ps.Init.ClockDivision = f_clockDivision_u32;
        f_timer_ps->BspTimer_ps.Init.AutoReloadPreload = f_autoRePreload_u32;

        bspRet_e = c_FMKCPU_BspTimFunc_apf[f_hwTimCfg_e].TimerInit_pcb(&f_timer_ps->BspTimer_ps);
        if(bspRet_e != HAL_OK)
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
        else 
        {
            f_timer_ps->HwCfg_e = f_hwTimCfg_e;
            f_timer_ps->IsTimerConfigured_b = (t_bool)True;
        }
    }

    return Ret_e;
}

/***********************************
 * s_FMKCPU_BspRqst_InterruptMngmt
 ***********************************/
static void s_FMKCPU_BspRqst_InterruptMngmt(TIM_HandleTypeDef *f_timerIstce_ps, t_eFMKCPU_HwTimerCfg f_HwTimcfg_e)
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
        if (&g_TimerInfo_as[LLI_u8].BspTimer_ps == (TIM_HandleTypeDef *)f_timerIstce_ps)
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
        BspITChnl_e = HAL_TIM_GetActiveChannel(&g_TimerInfo_as[Calltimer_e].BspTimer_ps);
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
            case HAL_TIM_ACTIVE_CHANNEL_CLEARED:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
        //------------Find Max Interrupt line depending on------------//
        switch (f_HwTimcfg_e)
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
    return;
}

/*********************************
 * s_FMKCPU_Get_BspTimer
 *********************************/
static t_eReturnCode s_FMKCPU_Get_BspIRQNType(t_eFMKCPU_IRQNType f_IRQN_e, IRQn_Type *f_bspIRQN_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_IRQN_e > FMKCPU_NVIC_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspIRQN_pe == (IRQn_Type *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_IRQN_e)
        {
            /* CAUTION : Automatic generated code section for IRQNType switch case: Start */
            case FMKCPU_NVIC_WWDG_IRQN:
                *f_bspIRQN_pe = WWDG_IRQn;
                break;
            case FMKCPU_NVIC_PVD_PVM_IRQN:
                *f_bspIRQN_pe = PVD_PVM_IRQn;
                break;
            case FMKCPU_NVIC_RTC_TAMP_LSECSS_IRQN:
                *f_bspIRQN_pe = RTC_TAMP_LSECSS_IRQn;
                break;
            case FMKCPU_NVIC_RTC_WKUP_IRQN:
                *f_bspIRQN_pe = RTC_WKUP_IRQn;
                break;
            case FMKCPU_NVIC_FLASH_IRQN:
                *f_bspIRQN_pe = FLASH_IRQn;
                break;
            case FMKCPU_NVIC_RCC_IRQN:
                *f_bspIRQN_pe = RCC_IRQn;
                break;
            case FMKCPU_NVIC_EXTI0_IRQN:
                *f_bspIRQN_pe = EXTI0_IRQn;
                break;
            case FMKCPU_NVIC_EXTI1_IRQN:
                *f_bspIRQN_pe = EXTI1_IRQn;
                break;
            case FMKCPU_NVIC_EXTI2_IRQN:
                *f_bspIRQN_pe = EXTI2_IRQn;
                break;
            case FMKCPU_NVIC_EXTI3_IRQN:
                *f_bspIRQN_pe = EXTI3_IRQn;
                break;
            case FMKCPU_NVIC_EXTI4_IRQN:
                *f_bspIRQN_pe = EXTI4_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL1_IRQN:
                *f_bspIRQN_pe = DMA1_Channel1_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL2_IRQN:
                *f_bspIRQN_pe = DMA1_Channel2_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL3_IRQN:
                *f_bspIRQN_pe = DMA1_Channel3_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL4_IRQN:
                *f_bspIRQN_pe = DMA1_Channel4_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL5_IRQN:
                *f_bspIRQN_pe = DMA1_Channel5_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL6_IRQN:
                *f_bspIRQN_pe = DMA1_Channel6_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL7_IRQN:
                *f_bspIRQN_pe = DMA1_Channel7_IRQn;
                break;
            case FMKCPU_NVIC_ADC1_2_IRQN:
                *f_bspIRQN_pe = ADC1_2_IRQn;
                break;
            case FMKCPU_NVIC_USB_HP_IRQN:
                *f_bspIRQN_pe = USB_HP_IRQn;
                break;
            case FMKCPU_NVIC_USB_LP_IRQN:
                *f_bspIRQN_pe = USB_LP_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN1_IT0_IRQN:
                *f_bspIRQN_pe = FDCAN1_IT0_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN1_IT1_IRQN:
                *f_bspIRQN_pe = FDCAN1_IT1_IRQn;
                break;
            case FMKCPU_NVIC_EXTI9_5_IRQN:
                *f_bspIRQN_pe = EXTI9_5_IRQn;
                break;
            case FMKCPU_NVIC_TIM1_BRK_TIM15_IRQN:
                *f_bspIRQN_pe = TIM1_BRK_TIM15_IRQn;
                break;
            case FMKCPU_NVIC_TIM1_UP_TIM16_IRQN:
                *f_bspIRQN_pe = TIM1_UP_TIM16_IRQn;
                break;
            case FMKCPU_NVIC_TIM1_TRG_COM_TIM17_IRQN:
                *f_bspIRQN_pe = TIM1_TRG_COM_TIM17_IRQn;
                break;
            case FMKCPU_NVIC_TIM1_CC_IRQN:
                *f_bspIRQN_pe = TIM1_CC_IRQn;
                break;
            case FMKCPU_NVIC_TIM2_IRQN:
                *f_bspIRQN_pe = TIM2_IRQn;
                break;
            case FMKCPU_NVIC_TIM3_IRQN:
                *f_bspIRQN_pe = TIM3_IRQn;
                break;
            case FMKCPU_NVIC_TIM4_IRQN:
                *f_bspIRQN_pe = TIM4_IRQn;
                break;
            case FMKCPU_NVIC_I2C1_EV_IRQN:
                *f_bspIRQN_pe = I2C1_EV_IRQn;
                break;
            case FMKCPU_NVIC_I2C1_ER_IRQN:
                *f_bspIRQN_pe = I2C1_ER_IRQn;
                break;
            case FMKCPU_NVIC_I2C2_EV_IRQN:
                *f_bspIRQN_pe = I2C2_EV_IRQn;
                break;
            case FMKCPU_NVIC_I2C2_ER_IRQN:
                *f_bspIRQN_pe = I2C2_ER_IRQn;
                break;
            case FMKCPU_NVIC_SPI1_IRQN:
                *f_bspIRQN_pe = SPI1_IRQn;
                break;
            case FMKCPU_NVIC_SPI2_IRQN:
                *f_bspIRQN_pe = SPI2_IRQn;
                break;
            case FMKCPU_NVIC_USART1_IRQN:
                *f_bspIRQN_pe = USART1_IRQn;
                break;
            case FMKCPU_NVIC_USART2_IRQN:
                *f_bspIRQN_pe = USART2_IRQn;
                break;
            case FMKCPU_NVIC_USART3_IRQN:
                *f_bspIRQN_pe = USART3_IRQn;
                break;
            case FMKCPU_NVIC_EXTI15_10_IRQN:
                *f_bspIRQN_pe = EXTI15_10_IRQn;
                break;
            case FMKCPU_NVIC_RTC_ALARM_IRQN:
                *f_bspIRQN_pe = RTC_Alarm_IRQn;
                break;
            case FMKCPU_NVIC_USBWAKEUP_IRQN:
                *f_bspIRQN_pe = USBWakeUp_IRQn;
                break;
            case FMKCPU_NVIC_TIM8_BRK_IRQN:
                *f_bspIRQN_pe = TIM8_BRK_IRQn;
                break;
            case FMKCPU_NVIC_TIM8_UP_IRQN:
                *f_bspIRQN_pe = TIM8_UP_IRQn;
                break;
            case FMKCPU_NVIC_TIM8_TRG_COM_IRQN:
                *f_bspIRQN_pe = TIM8_TRG_COM_IRQn;
                break;
            case FMKCPU_NVIC_TIM8_CC_IRQN:
                *f_bspIRQN_pe = TIM8_CC_IRQn;
                break;
            case FMKCPU_NVIC_ADC3_IRQN:
                *f_bspIRQN_pe = ADC3_IRQn;
                break;
            case FMKCPU_NVIC_FMC_IRQN:
                *f_bspIRQN_pe = FMC_IRQn;
                break;
            case FMKCPU_NVIC_LPTIM1_IRQN:
                *f_bspIRQN_pe = LPTIM1_IRQn;
                break;
            case FMKCPU_NVIC_TIM5_IRQN:
                *f_bspIRQN_pe = TIM5_IRQn;
                break;
            case FMKCPU_NVIC_SPI3_IRQN:
                *f_bspIRQN_pe = SPI3_IRQn;
                break;
            case FMKCPU_NVIC_UART4_IRQN:
                *f_bspIRQN_pe = UART4_IRQn;
                break;
            case FMKCPU_NVIC_UART5_IRQN:
                *f_bspIRQN_pe = UART5_IRQn;
                break;
            case FMKCPU_NVIC_TIM6_DAC_IRQN:
                *f_bspIRQN_pe = TIM6_DAC_IRQn;
                break;
            case FMKCPU_NVIC_TIM7_DAC_IRQN:
                *f_bspIRQN_pe = TIM7_DAC_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL1_IRQN:
                *f_bspIRQN_pe = DMA2_Channel1_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL2_IRQN:
                *f_bspIRQN_pe = DMA2_Channel2_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL3_IRQN:
                *f_bspIRQN_pe = DMA2_Channel3_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL4_IRQN:
                *f_bspIRQN_pe = DMA2_Channel4_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL5_IRQN:
                *f_bspIRQN_pe = DMA2_Channel5_IRQn;
                break;
            case FMKCPU_NVIC_ADC4_IRQN:
                *f_bspIRQN_pe = ADC4_IRQn;
                break;
            case FMKCPU_NVIC_ADC5_IRQN:
                *f_bspIRQN_pe = ADC5_IRQn;
                break;
            case FMKCPU_NVIC_UCPD1_IRQN:
                *f_bspIRQN_pe = UCPD1_IRQn;
                break;
            case FMKCPU_NVIC_COMP1_2_3_IRQN:
                *f_bspIRQN_pe = COMP1_2_3_IRQn;
                break;
            case FMKCPU_NVIC_COMP4_5_6_IRQN:
                *f_bspIRQN_pe = COMP4_5_6_IRQn;
                break;
            case FMKCPU_NVIC_COMP7_IRQN:
                *f_bspIRQN_pe = COMP7_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_MASTER_IRQN:
                *f_bspIRQN_pe = HRTIM1_Master_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIMA_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIMA_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIMB_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIMB_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIMC_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIMC_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIMD_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIMD_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIME_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIME_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_FLT_IRQN:
                *f_bspIRQN_pe = HRTIM1_FLT_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIMF_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIMF_IRQn;
                break;
            case FMKCPU_NVIC_CRS_IRQN:
                *f_bspIRQN_pe = CRS_IRQn;
                break;
            case FMKCPU_NVIC_SAI1_IRQN:
                *f_bspIRQN_pe = SAI1_IRQn;
                break;
            case FMKCPU_NVIC_TIM20_BRK_IRQN:
                *f_bspIRQN_pe = TIM20_BRK_IRQn;
                break;
            case FMKCPU_NVIC_TIM20_UP_IRQN:
                *f_bspIRQN_pe = TIM20_UP_IRQn;
                break;
            case FMKCPU_NVIC_TIM20_TRG_COM_IRQN:
                *f_bspIRQN_pe = TIM20_TRG_COM_IRQn;
                break;
            case FMKCPU_NVIC_TIM20_CC_IRQN:
                *f_bspIRQN_pe = TIM20_CC_IRQn;
                break;
            case FMKCPU_NVIC_FPU_IRQN:
                *f_bspIRQN_pe = FPU_IRQn;
                break;
            case FMKCPU_NVIC_I2C4_EV_IRQN:
                *f_bspIRQN_pe = I2C4_EV_IRQn;
                break;
            case FMKCPU_NVIC_I2C4_ER_IRQN:
                *f_bspIRQN_pe = I2C4_ER_IRQn;
                break;
            case FMKCPU_NVIC_SPI4_IRQN:
                *f_bspIRQN_pe = SPI4_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN2_IT0_IRQN:
                *f_bspIRQN_pe = FDCAN2_IT0_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN2_IT1_IRQN:
                *f_bspIRQN_pe = FDCAN2_IT1_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN3_IT0_IRQN:
                *f_bspIRQN_pe = FDCAN3_IT0_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN3_IT1_IRQN:
                *f_bspIRQN_pe = FDCAN3_IT1_IRQn;
                break;
            case FMKCPU_NVIC_RNG_IRQN:
                *f_bspIRQN_pe = RNG_IRQn;
                break;
            case FMKCPU_NVIC_LPUART1_IRQN:
                *f_bspIRQN_pe = LPUART1_IRQn;
                break;
            case FMKCPU_NVIC_I2C3_EV_IRQN:
                *f_bspIRQN_pe = I2C3_EV_IRQn;
                break;
            case FMKCPU_NVIC_I2C3_ER_IRQN:
                *f_bspIRQN_pe = I2C3_ER_IRQn;
                break;
            case FMKCPU_NVIC_DMAMUX_OVR_IRQN:
                *f_bspIRQN_pe = DMAMUX_OVR_IRQn;
                break;
            case FMKCPU_NVIC_QUADSPI_IRQN:
                *f_bspIRQN_pe = QUADSPI_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL8_IRQN:
                *f_bspIRQN_pe = DMA1_Channel8_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL6_IRQN:
                *f_bspIRQN_pe = DMA2_Channel6_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL7_IRQN:
                *f_bspIRQN_pe = DMA2_Channel7_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL8_IRQN:
                *f_bspIRQN_pe = DMA2_Channel8_IRQn;
                break;
            case FMKCPU_NVIC_CORDIC_IRQN:
                *f_bspIRQN_pe = CORDIC_IRQn;
                break;
            case FMKCPU_NVIC_FMAC_IRQN:
                *f_bspIRQN_pe = FMAC_IRQn;
                break;
            /* CAUTION : Automatic generated code section for IRQNType switch case: End */
            case FMKCPU_NVIC_NB:
            default:
            {
                Ret_e = RC_ERROR_NOT_ALLOWED;
            }

        }
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
void TIM1_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_1].BspTimer_ps);}
void TIM2_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_2].BspTimer_ps);}
void TIM3_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_3].BspTimer_ps);}
void TIM4_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_4].BspTimer_ps);}
void TIM5_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_5].BspTimer_ps);}
void TIM6_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_6].BspTimer_ps);}
void TIM7_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_7].BspTimer_ps);}
void TIM8_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_8].BspTimer_ps);}
void TIM15_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_15].BspTimer_ps);}
void TIM16_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_16].BspTimer_ps);}
void TIM17_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_17].BspTimer_ps);}
void TIM20_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_20].BspTimer_ps);}
/* CAUTION : Automatic generated code section for TIMx IRQHandler: End */

/**
 *
 *	@brief      Every callback function is now centralized in one function
 *
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_HWTIM_CFG_EVNT); }
void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_HWTIM_CFG_EVNT); }
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_HWTIM_CFG_IC); }
void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_HWTIM_CFG_IC); }
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_HWTIM_CFG_OC); }
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_HWTIM_CFG_PWM); }
void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim) { return s_FMKCPU_BspRqst_InterruptMngmt(htim, FMKCPU_HWTIM_CFG_PWM); }
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
