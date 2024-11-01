/**
 * @file        FMK_CPU.c
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
#include "./FMK_CPU.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKCPU_ConfigPrivate.h"
#include "Constant.h"
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
    t_cbFMKCPU_InterruptChnl *chnl_cb;                  /**< Callback function of the channel */
    t_bool IsChnlConfigure_b;                           /**< Wether or not the channel has beeen configured */
} t_sFMKCPU_ChnlInfo;

/**< Structure of information on a timer*/
typedef struct
{
    TIM_HandleTypeDef BspTimer_ps;                      /**< The Timer structure for HAL STM32*/
    t_eFMKCPU_HwTimerCfg HwCfg_e;                       /**< The hardware configuration of the timer */
    t_sFMKCPU_ChnlInfo Channel_as[FMKCPU_CHANNEL_NB];   /**< Channels info structure */
    const t_eFMKCPU_IRQNType IRQNType_e;                /**< IRQN type related to the timer */
    const t_eFMKCPU_ClockPort clock_e;                  /**< RCC clock related to the timer */
    t_bool IsTimerRunning_b;                            /**< Flag Timer start function set, and timer running */
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
/* CAUTION : Automatic generated code section for Timer Configuration: Start */
/**< timer information variable */
t_sFMKCPU_TimerInfo g_TimerInfo_as[FMKCPU_TIMER_NB] = {
    {
        // Timer_1
        .BspTimer_ps.Instance = TIM1,
        .clock_e = FMKCPU_RCC_CLK_TIM1,
        .IRQNType_e = FMKCPU_NVIC_TIM1_BRK_UP_TRG_COM_IRQN,
    },
    {
        // Timer_3
        .BspTimer_ps.Instance = TIM3,
        .clock_e = FMKCPU_RCC_CLK_TIM3,
        .IRQNType_e = FMKCPU_NVIC_TIM3_IRQN,
    },
    {
        // Timer_14
        .BspTimer_ps.Instance = TIM14,
        .clock_e = FMKCPU_RCC_CLK_TIM14,
        .IRQNType_e = FMKCPU_NVIC_TIM14_IRQN,
    },
    {
        // Timer_15
        .BspTimer_ps.Instance = TIM15,
        .clock_e = FMKCPU_RCC_CLK_TIM15,
        .IRQNType_e = FMKCPU_NVIC_TIM15_IRQN,
    },
    {
        // Timer_16
        .BspTimer_ps.Instance = TIM16,
        .clock_e = FMKCPU_RCC_CLK_TIM16,
        .IRQNType_e = FMKCPU_NVIC_TIM16_IRQN,
    },
    {
        // Timer_17
        .BspTimer_ps.Instance = TIM17,
        .clock_e = FMKCPU_RCC_CLK_TIM17,
        .IRQNType_e = FMKCPU_NVIC_TIM17_IRQN,
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
static t_eReturnState s_FMKCPU_Set_BspTimerInit(t_sFMKCPU_TimerInfo * f_timer_ps,
                                                t_eFMKCPU_HwTimerCfg f_hwTimCfg_e,
                                                  t_uint32 f_prescaler_u32,
                                                  t_uint32 f_period_u32,
                                                  t_uint32 f_counterMode_32,
                                                  t_uint32 f_clockDivision_u32,
                                                  t_uint32 f_autoRePreload_u32);
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
static t_eReturnState s_FMKCPU_Get_BspChannel(t_eFMKCPU_InterruptChnl f_channel_e, t_uint32 *f_bspChnl_pu32);
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
static t_eReturnState s_FMKCPU_Get_BspNVICPriority(t_eFMKCPU_NVICPriority f_priority_e, t_uint32 *BspNVICPriority_pu32);
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
static t_eReturnState s_FMKCPU_Get_BspIRQNType(t_eFMKCPU_IRQNType f_IRQN_e, IRQn_Type *f_bspIRQN_pe);
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
static t_eReturnState s_FMKCPU_Set_HwChannelState(t_eFMKCPU_Timer f_timer_e,
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
static t_eReturnState s_FMKCPU_Operational(void);


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
static t_eReturnState s_FMKCPU_PerformDiagnostic(void);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
t_eReturnState FMKCPU_Init(void)
{
    t_uint8 LLI_u8;
    t_uint8 LLI2_u8;
    for (LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_eFMKCPU_Timer)FMKCPU_TIMER_NB ; LLI_u8++)
    {
        g_TimerInfo_as[LLI_u8].IsNVICTimerEnable_b = (t_bool)False;
        g_TimerInfo_as[LLI_u8].IsTimerConfigured_b = (t_bool)False;
        g_TimerInfo_as[LLI_u8].IsTimerRunning_b    = (t_bool)False;
        g_TimerInfo_as[LLI_u8].HwCfg_e = FMKCPU_HWTIM_CFG_EVNT;
        for (LLI2_u8 = (t_uint8)0 ; LLI2_u8 < (t_eFMKCPU_InterruptChnl)FMKCPU_CHANNEL_NB ; LLI2_u8++)
        {
            g_TimerInfo_as[LLI_u8].Channel_as[LLI2_u8].chnl_cb = NULL_FONCTION;
            g_TimerInfo_as[LLI_u8].Channel_as[LLI2_u8].ErrState_e = FMKCPU_ERRSTATE_OK;
            
            g_TimerInfo_as[LLI_u8].Channel_as[LLI2_u8].IsChnlConfigure_b =  (t_bool)False;
            g_TimerInfo_as[LLI_u8].Channel_as[LLI2_u8].RunMode_e = FMKCPU_CNHL_RUNMODE_POLLING;
            g_TimerInfo_as[LLI_u8].Channel_as[LLI2_u8].State_e = FMKCPU_CHNLST_DISACTIVATED;
        }
    }
    return RC_OK;
}
/*********************************
 * FMKCPU_Set_Delay
 *********************************/
t_eReturnState FMKCPU_Cyclic(void)
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
t_eReturnState FMKCPU_GetState(t_eCyclicFuncState *f_State_pe)
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
 * FMKCPU_SetState
 *********************************/
t_eReturnState FMKCPU_SetState(t_eCyclicFuncState f_State_e)
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
    t_eReturnState Ret_e = RC_OK;

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
t_eReturnState FMKCPU_Set_SysClockCfg(void)
{
    t_eReturnState Ret_e = RC_OK;
    HAL_StatusTypeDef  bspRet_e = HAL_OK;
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                    |RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    bspRet_e = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    if(bspRet_e == HAL_OK)
    {
        bspRet_e = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
    }
    if(bspRet_e != HAL_OK)
    {
        g_state_e = STATE_CYCLIC_ERROR;
        Ret_e = RC_ERROR_WRONG_RESULT;
    }
    return Ret_e;
}

/*********************************
 * FMKCPU_Set_SysClockCfg
 *********************************/
t_eReturnState FMKCPU_Set_HardwareInit(void)
{
    t_eReturnState Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;

    bspRet_e = HAL_Init();
    if(bspRet_e != HAL_OK)
    {
        Ret_e = RC_ERROR_WRONG_RESULT;
        g_state_e = STATE_CYCLIC_ERROR;
    }

    return Ret_e;
}

/*********************************
 * FMKCPU_Set_NVICState
 *********************************/
t_eReturnState FMKCPU_Set_NVICState(t_eFMKCPU_IRQNType f_IRQN_e, t_eFMKCPU_NVIC_Ope f_OpeState_e)
{
    t_eReturnState Ret_e = RC_OK;
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
t_eReturnState FMKCPU_Set_HwClock(t_eFMKCPU_ClockPort f_clkPort_e,
                                  t_eFMKCPU_ClockPortOpe f_OpeState_e)
{
    t_eReturnState Ret_e = RC_OK;

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
t_eReturnState FMKCPU_Set_WwdgCfg(t_eFMKCPu_WwdgResetPeriod f_period_e)
{
    t_eReturnState Ret_e = RC_OK;
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
t_eReturnState FMKCPU_ResetWwdg(void)
{
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_eReturnState Ret_e = RC_OK;
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
t_eReturnState FMKCPU_Set_PWMChannelCfg(t_eFMKCPU_Timer f_timer_e,
                                         t_eFMKCPU_InterruptChnl f_channel_e,
                                          t_uint32 f_pwmFreq_u32)
{
    /********************************
     *   Some useful information for PWM generation
     *   1 - ARR = Period in Init =  (((freq_timer)/ (freq_pwm * (PSC+1))) -1)
     *   For a dutycyle E [0 - 1000]
     *   2 - CCR1_2_3_4 depending on channel, set the Duty Cycle -> (DutyCyle/ 1000) * (ARR +1)
     ********************************/
    t_eReturnState Ret_e = RC_OK;
    HAL_StatusTypeDef BspRet_e = HAL_OK;
    HAL_TIM_ChannelStateTypeDef bspChannelState_e = HAL_TIM_CHANNEL_STATE_BUSY;
    TIM_MasterConfigTypeDef masterCfg_s = {0};
    TIM_OC_InitTypeDef BspOcInit_s;
    t_uint32 bspChannel_u32 = 0;
    t_uint32 bspPeriod_u32;

    if (f_timer_e > FMKCPU_TIMER_NB 
    || f_channel_e > c_FMKCPU_TimMaxChnl_ua8[f_timer_e])
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if ((g_TimerInfo_as[f_timer_e].IsTimerConfigured_b == (t_bool)False) && (Ret_e == RC_OK))
    {
        bspPeriod_u32 = (t_uint32)(((FMKCPU_TIMER_CLOCK_OSC_MHZ * CST_MHZ_TO_HZ) /
                                            (f_pwmFreq_u32 * (FMKCPU_TIMER_PWM_PSC + 1))) - (t_uint32)1);
        Ret_e = s_FMKCPU_Set_BspTimerInit(&g_TimerInfo_as[f_timer_e],
                                                    FMKCPU_HWTIM_CFG_PWM,
                                                    (t_uint32)FMKCPU_TIMER_PWM_PSC,
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
    if (g_TimerInfo_as[f_timer_e].HwCfg_e != FMKCPU_HWTIM_CFG_PWM)
    { // this timer and channel is already configured for another purpose
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    if (g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].IsChnlConfigure_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {   // Function get here only if Timer is initialized and channel not initialized yet
        
        // Now Configure the channel in PWM mode
        Ret_e = s_FMKCPU_Get_BspChannel(f_channel_e, &bspChannel_u32);
        if (Ret_e == RC_OK)
        {
            // see if channel state is ok 
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
        { // Update INformation
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
 * FMKCPU_Set_PWMChannelDuty
 *********************************/
t_eReturnState FMKCPU_Set_PWMChannelDuty(t_eFMKCPU_Timer f_timer_e,
                                         t_eFMKCPU_InterruptChnl f_channel_e,
                                         t_uint16 f_dutyCycle_u16)
/********************************
 *   Some useful information for PWM generation
 *   1 - ARR = Period in Init = (((freq_timer)/ (freq_pwm * (PSC+1))) -1)
 *   For a dutycyle E [0 - 1000]
 *   2 - CCR1_2_3_4 depending on channel, set the Duty Cycle -> CCR = (DutyCyle/ 1000) * (ARR +1)
 ********************************/
{
    t_eReturnState Ret_e = RC_OK;
    t_uint32 BspChannel_u32 = 0;
    t_uint32 CCRxValue_u32 = 0;

    if (f_timer_e > FMKCPU_TIMER_NB || f_channel_e > FMKCPU_CHANNEL_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if (g_TimerInfo_as[f_timer_e].IsTimerConfigured_b == (t_bool)False 
    || g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].IsChnlConfigure_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if(g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].ErrState_e != FMKCPU_ERRSTATE_OK)
    {
        Ret_e = RC_ERROR_WRONG_STATE;
    }
    if (Ret_e == RC_OK)
    {
        // Shutdown channel if dutycycle == 0 & channel is active
        //  else make dutycycle to channel, shut on channel if not on yet
        if (f_dutyCycle_u16 == (t_uint16)0 && g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].State_e == FMKCPU_CHNLST_ACTIVATED)
        {
            s_FMKCPU_Set_HwChannelState(f_timer_e, f_channel_e, FMKCPU_CHNLST_DISACTIVATED);
        }
        if (f_dutyCycle_u16 > (t_uint16)FMKCPU_PWM_MIN_DUTY_CYLCE && f_dutyCycle_u16 <= (t_uint16)FMKCPU_PWM_MAX_DUTY_CYLCE)
        { // update dutycycle
            CCRxValue_u32 = (t_uint32)((t_float32)f_dutyCycle_u16 / (t_float32)FMKCPU_PWM_MAX_DUTY_CYLCE *
                           (t_float32)(g_TimerInfo_as[f_timer_e].BspTimer_ps.Init.Period + (t_uint32)1));
            if (g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].State_e == FMKCPU_CHNLST_DISACTIVATED)
            {

                Ret_e = s_FMKCPU_Set_HwChannelState(f_timer_e, f_channel_e, FMKCPU_CHNLST_ACTIVATED);
            }
            if (Ret_e == RC_OK)
            {
                Ret_e = s_FMKCPU_Get_BspChannel(f_channel_e, &BspChannel_u32);
            }
            if (Ret_e == RC_OK)
            {
                __HAL_TIM_SET_COMPARE(&g_TimerInfo_as[f_timer_e].BspTimer_ps, BspChannel_u32, (t_uint32)CCRxValue_u32);
            }
        }
        else
        {
            Ret_e = RC_WARNING_NO_OPERATION;
        }
    }
    return Ret_e;
}

/*********************************
 * FMKCPU_Get_PWMChannelDuty
 *********************************/
t_eReturnState FMKCPU_Get_PWMChannelDuty(t_eFMKCPU_Timer f_timer_e,
                                         t_eFMKCPU_InterruptChnl f_channel_e,
                                         t_uint16 *f_dutyCycle_u16)
{
    /********************************
     *   Some useful information for PWM generation
     *   1 - ARR = Period in Init =  (((freq_timer)/ (freq_pwm * (PSC+1))) -1)
     *   For a dutycyle E [0 - 1000]
     *   2 - CCR1_2_3_4 depending on channel, set the Duty Cycle -> CCR = (DutyCyle/ 1000) * (ARR +1)
     ********************************/
    t_eReturnState Ret_e = RC_OK;
    t_uint32 BspChannel_u32 = 0;
    t_uint32 comparedValue_u32 = 0;

    if (f_timer_e > FMKCPU_TIMER_NB || f_channel_e > FMKCPU_CHANNEL_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if (f_dutyCycle_u16 == (t_uint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (g_TimerInfo_as[f_timer_e].IsTimerConfigured_b == (t_bool)False || g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].IsChnlConfigure_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].ErrState_e != FMKCPU_ERRSTATE_OK)
    {
        Ret_e = RC_ERROR_WRONG_STATE;
    }
    // get dutycycle only if channel is active
    if (g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].State_e == FMKCPU_CHNLST_ACTIVATED)
    {
        Ret_e = RC_ERROR_WRONG_CONFIG;
    }
    if (Ret_e == RC_OK)
    {  
        Ret_e = s_FMKCPU_Get_BspChannel(f_channel_e, &BspChannel_u32);
        if (Ret_e == RC_OK)
        {
            comparedValue_u32 = (t_uint32)HAL_TIM_ReadCapturedValue(&g_TimerInfo_as[f_timer_e].BspTimer_ps, BspChannel_u32);
            *f_dutyCycle_u16 = (t_uint16)((comparedValue_u32 * 1000) /
                                            (g_TimerInfo_as[f_timer_e].BspTimer_ps.Init.Period + 1));
        }
    }
    return Ret_e;
}
/*********************************
 * FMKCPU_Set_ICChannelCfg
 *********************************/
t_eReturnState FMKCPU_Set_ICChannelCfg(t_eFMKCPU_Timer f_timer_e,
                                         t_eFMKCPU_InterruptChnl f_channel_e, 
                                         t_eFMKCPU_ChnlMeasTrigger f_MeasTrigger_e,
                                         t_cbFMKCPU_InterruptChnl f_ITChannel_cb)
{
    t_eReturnState Ret_e = RC_OK;
    HAL_StatusTypeDef BspRet_e = HAL_OK;
    HAL_TIM_ChannelStateTypeDef bspChannelState_e = HAL_TIM_CHANNEL_STATE_BUSY;
    TIM_IC_InitTypeDef BspICInit_s;
    t_uint32 bspChannel_u32 = 0;

    if(f_ITChannel_cb == (t_cbFMKCPU_InterruptChnl *)NULL_FONCTION)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (f_timer_e > FMKCPU_TIMER_NB 
    || f_channel_e > c_FMKCPU_TimMaxChnl_ua8[f_timer_e])
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if ((g_TimerInfo_as[f_timer_e].IsTimerConfigured_b == (t_bool)False) && (Ret_e == RC_OK))
    {
        s_FMKCPU_Set_BspTimerInit(&g_TimerInfo_as[f_timer_e],
                                    FMKCPU_HWTIM_CFG_IC,
                                    (t_uint32)FMKCPU_TIMER_IC_PSC,
                                    (t_uint32)FMKCPU_TIMER_IC_ARR,
                                    (t_uint32)TIM_COUNTERMODE_UP,
                                    (t_uint32)TIM_CLOCKDIVISION_DIV1,
                                    (t_uint32)TIM_AUTORELOAD_PRELOAD_DISABLE);
                
    }
    if (g_TimerInfo_as[f_timer_e].HwCfg_e != FMKCPU_HWTIM_CFG_IC)
    { // this timer and channel is already configured for another purpose
        Ret_e = RC_ERROR_NOT_ALLOWED;
    }
    if (g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].IsChnlConfigure_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKCPU_Get_BspChannel(f_channel_e, &bspChannel_u32);
        if (Ret_e == RC_OK)
        {
            // see if channel state is ok 
            bspChannelState_e = HAL_TIM_GetChannelState(&g_TimerInfo_as[f_timer_e].BspTimer_ps, bspChannel_u32);
            if(bspChannelState_e == HAL_TIM_CHANNEL_STATE_READY)
            {
                BspICInit_s.ICPolarity = (t_uint32)TIM_ICPOLARITY_RISING;
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
        { // update information
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
 * FMKCPU_Set_EvntTimerCfg
 *********************************/
t_eReturnState FMKCP_Set_EvntTimerCfg(t_eFMKCPU_Timer f_timer_e,
                                         t_uint32 f_periodms_u32,
                                         t_cbFMKCPU_InterruptChnl f_ITChannel_cb)
{
    /********************************
     *   Some useful information for Evnt generation
     *   In FMKCPU_ConfigPrivate, 
     * 
     ********************************/
    t_eReturnState Ret_e = RC_OK;
    t_uint32 bspPeriod_u32 = 0; 
    t_uint32 prescaler_u32 = 0;

    if (f_timer_e > FMKCPU_TIMER_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_ITChannel_cb == (t_cbFMKCPU_InterruptChnl *)NULL_FONCTION)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
     if(g_TimerInfo_as[f_timer_e].IsTimerConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if(Ret_e == RC_OK)
    {
        if(f_periodms_u32 < FMKCPU_TIMER_EVNT_MAX_LOW_PERIOD_MS)
        {
            prescaler_u32 = FMKCPU_TIMER_EVNT_PSC_HIGH; 
        }
        else 
        {
            prescaler_u32 = FMKCPU_TIMER_EVNT_PSC_LOW;
        }

        bspPeriod_u32 = (t_uint32)((t_float32)((t_float32)(FMKCPU_HSI_CLOCK_OSC_MHZ * CST_MHZ_TO_HZ) * (t_float32)(f_periodms_u32 / 1000)) / 
                                                (t_float32)((prescaler_u32 + 1))
                                );

        Ret_e = s_FMKCPU_Set_BspTimerInit(&g_TimerInfo_as[f_timer_e],
                                            FMKCPU_HWTIM_CFG_EVNT,
                                            (t_uint32)(prescaler_u32 - (t_uint32)1),
                                            (t_uint32)(bspPeriod_u32 - (t_uint32)1),
                                            (t_uint32)TIM_COUNTERMODE_UP,
                                            (t_uint32)TIM_CLOCKDIVISION_DIV1,
                                            (t_uint32)TIM_AUTORELOAD_PRELOAD_DISABLE);
        if (Ret_e == RC_OK)
        {
            g_TimerInfo_as[f_timer_e].Channel_as[FMKCPU_CHANNEL_1].chnl_cb = f_ITChannel_cb;
            g_TimerInfo_as[f_timer_e].Channel_as[FMKCPU_CHANNEL_1].RunMode_e = FMKCPU_CNHL_RUNMODE_INTERRUPT;
        }
        else 
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
    }

    return Ret_e;
}
/*********************************
 * FMKCPU_AddTimerChnlCallback
 *********************************/
t_eReturnState FMKCPU_AddTimerChnlCallback(t_eFMKCPU_Timer f_timer_e,
                                           t_eFMKCPU_InterruptChnl f_channel_e,
                                           t_cbFMKCPU_InterruptChnl *f_ITChannel_cb)
{
    t_eReturnState Ret_e = RC_OK;

    if (f_timer_e > FMKCPU_TIMER_NB || f_channel_e > FMKCPU_CHANNEL_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_ITChannel_cb == (t_cbFMKCPU_InterruptChnl *)NULL_FONCTION)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].IsChnlConfigure_b != (t_bool)True 
    || g_TimerInfo_as[f_timer_e].IsTimerConfigured_b != (t_bool)True)
    {
        Ret_e = RC_ERROR_WRONG_STATE;
    }
    if (Ret_e == RC_OK)
    {
        // Update channel Run mode and Add Callback
        g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].RunMode_e = FMKCPU_CNHL_RUNMODE_INTERRUPT;
        g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].chnl_cb = f_ITChannel_cb;
    }
    return Ret_e;
}

/*********************************
 * FMKCPU_Set_EventTimerState
 *********************************/
t_eReturnState FMKCPU_Set_EventTimerState(t_eFMKCPU_Timer f_timer_e, t_eFMKCPU_EvntTimState f_TimState_e)
{
    t_eReturnState Ret_e = RC_OK;
    t_eFMKCPU_ChnlState chnlOpe_e;
    if (f_timer_e > FMKCPU_TIMER_NB
    || f_TimState_e > FMKCPU_TIMST_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        // IMPORTANT in hardware the timer is the one managing interruption for event timer
        // but in software to make every timer modular decided to make channel as if the channel make 
        // interruption and not the timer, in consequence to set the timer state, we have to make the channel 1 state
        // on other channel are not used
        switch(f_TimState_e)
        {
            case FMKCPU_TIMST_DISACTIVATED:
                chnlOpe_e = FMKCPU_CHNLST_DISACTIVATED;
                break;
            case FMKCPU_TIMST_ACTIVATED:
                chnlOpe_e = FMKCPU_CHNLST_ACTIVATED;
                break;
            case FMKCPU_TIMST_NB:
            default:
                Ret_e = RC_ERROR_NOT_ALLOWED;
                break;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKCPU_Set_HwChannelState(f_timer_e, FMKCPU_CHANNEL_1, chnlOpe_e );
        }
    }

    return Ret_e;
}
/*********************************
 * FMKCPU_Set_ChannelState
 *********************************/
t_eReturnState FMKCPU_Set_ChannelState(t_eFMKCPU_Timer f_timer_e,
                                       t_eFMKCPU_InterruptChnl f_channel_e,
                                       t_eFMKCPU_ChnlState f_channelState_e)
{
    t_eReturnState Ret_e = RC_OK;

    if (f_timer_e > FMKCPU_TIMER_NB 
    || f_channel_e > FMKCPU_CHANNEL_NB 
    || f_channelState_e > FMKCPU_CHNLST_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        Ret_e = s_FMKCPU_Set_HwChannelState(f_timer_e, f_channel_e, f_channelState_e);
    }
    return Ret_e;
}

/*********************************
 * FMKCPU_Get_ChannelErrorStatus
 *********************************/
t_eReturnState FMKCPU_Get_ChannelErrorStatus(t_eFMKCPU_Timer f_timer_e, 
                                        t_eFMKCPU_InterruptChnl f_channel_e, 
                                        t_eFMKCPU_ChnlErrorState *f_chnlErrInfo_pe)
{
    t_eReturnState Ret_e = RC_OK;

    if(f_timer_e > FMKCPU_TIMER_NB 
    || f_channel_e > FMKCPU_CHANNEL_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_state_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_MODULE_NOT_INITIALIZED;
    }
    if(f_chnlErrInfo_pe == (t_eFMKCPU_ChnlErrorState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_chnlErrInfo_pe = g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e].ErrState_e;
    }

    return Ret_e;
}

t_eReturnState FMKCPU_Get_RegisterCRRx(t_eFMKCPU_Timer f_timer_e, 
                                        t_eFMKCPU_InterruptChnl f_channel_e,
                                        t_uint32 * f_CCRxValue_pu32)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint32 bspChannel_u32 = 0;

    if(f_timer_e > FMKCPU_TIMER_NB 
    || f_channel_e > FMKCPU_CHANNEL_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_CCRxValue_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKCPU_Get_BspChannel(f_channel_e, &bspChannel_u32);
    }
    if(Ret_e == RC_OK)
    {
        *f_CCRxValue_pu32 = (t_uint32)HAL_TIM_ReadCapturedValue(&g_TimerInfo_as[f_timer_e].BspTimer_ps,  bspChannel_u32);
    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_FMKCPU_Operational
 *********************************/
static t_eReturnState s_FMKCPU_Operational(void)
{
    t_eReturnState Ret_e = RC_OK;
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
static t_eReturnState s_FMKCPU_PerformDiagnostic(void)
{
    t_eReturnState Ret_e = RC_OK;
    HAL_TIM_StateTypeDef bspTimerState_e;
    t_eFMKCPU_ChnlErrorState channelErr_e = FMKCPU_ERRSTATE_OK;
    HAL_TIM_ChannelStateTypeDef bspChnlState_e = HAL_TIM_CHANNEL_STATE_READY;
    t_uint32 bspChannel_u32 = 0;
    t_sFMKCPU_TimerInfo * timerInfo_ps;
    t_uint8 CLLI_u8; /**< Channel loop  */
    t_uint8 TLLI_u8; /**< Timer loop  */

    for(TLLI_u8 = (t_uint8)0 ; TLLI_u8 < FMKCPU_TIMER_NB ; TLLI_u8++)
    {
        timerInfo_ps = (t_sFMKCPU_TimerInfo *)&g_TimerInfo_as[TLLI_u8];
        // diag for timer currently working/ Running
        if(timerInfo_ps->IsTimerRunning_b == (t_bool)True)
        {
            bspTimerState_e = c_FMKCPU_BspTimFunc_apf[timerInfo_ps->HwCfg_e].GetTimerState_cb(
                                        &timerInfo_ps->BspTimer_ps);

            if((bspTimerState_e & HAL_TIM_STATE_BUSY) != HAL_TIM_STATE_BUSY) // busy means ok for stm32
            {// associate bsp err with channel FMKCPU err
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
                {// bspTimerState_e = HAL_TIM_STATE_ERROR
                    channelErr_e |= FMKCPU_ERRSTATE_UNKNOWN;   
                }
                // Propagate this error to every channel from this timer
                for(CLLI_u8 = (t_uint8)0 ; CLLI_u8 < FMKCPU_CHANNEL_NB ; CLLI_u8++)
                {
                    if(timerInfo_ps->Channel_as[CLLI_u8].State_e == FMKCPU_CHNLST_ACTIVATED)
                    {
                        timerInfo_ps->Channel_as[CLLI_u8].ErrState_e |= channelErr_e;
                    }
                }
            }
            // diag for the channel currently used
            for(CLLI_u8 = (t_uint8)0 ; CLLI_u8 < FMKCPU_CHANNEL_NB ; CLLI_u8++)
            {
                if(timerInfo_ps->Channel_as[CLLI_u8].State_e == FMKCPU_CHNLST_ACTIVATED)
                {
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
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Get_BspChannel
 *********************************/
static t_eReturnState s_FMKCPU_Get_BspChannel(t_eFMKCPU_InterruptChnl f_channel_e, t_uint32 *f_bspChnl_pu32)
{
    t_eReturnState Ret_e = RC_OK;

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
static t_eReturnState s_FMKCPU_Get_BspIRQNType(t_eFMKCPU_IRQNType f_IRQN_e, IRQn_Type *f_bspIRQN_pe)
{
    t_eReturnState Ret_e = RC_OK;

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
            case FMKCPU_NVIC_RTC_IRQN:
                *f_bspIRQN_pe = RTC_IRQn;
                break;
            case FMKCPU_NVIC_FLASH_IRQN:
                *f_bspIRQN_pe = FLASH_IRQn;
                break;
            case FMKCPU_NVIC_RCC_IRQN:
                *f_bspIRQN_pe = RCC_IRQn;
                break;
            case FMKCPU_NVIC_EXTI0_1_IRQN:
                *f_bspIRQN_pe = EXTI0_1_IRQn;
                break;
            case FMKCPU_NVIC_EXTI2_3_IRQN:
                *f_bspIRQN_pe = EXTI2_3_IRQn;
                break;
            case FMKCPU_NVIC_EXTI4_15_IRQN:
                *f_bspIRQN_pe = EXTI4_15_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL1_IRQN:
                *f_bspIRQN_pe = DMA1_Channel1_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL2_3_IRQN:
                *f_bspIRQN_pe = DMA1_Channel2_3_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL4_5_IRQN:
                *f_bspIRQN_pe = DMA1_Channel4_5_IRQn;
                break;
            case FMKCPU_NVIC_ADC1_IRQN:
                *f_bspIRQN_pe = ADC1_IRQn;
                break;
            case FMKCPU_NVIC_TIM1_BRK_UP_TRG_COM_IRQN:
                *f_bspIRQN_pe = TIM1_BRK_UP_TRG_COM_IRQn;
                break;
            case FMKCPU_NVIC_TIM1_CC_IRQN:
                *f_bspIRQN_pe = TIM1_CC_IRQn;
                break;
            case FMKCPU_NVIC_TIM3_IRQN:
                *f_bspIRQN_pe = TIM3_IRQn;
                break;
            case FMKCPU_NVIC_TIM6_IRQN:
                *f_bspIRQN_pe = TIM6_IRQn;
                break;
            case FMKCPU_NVIC_TIM14_IRQN:
                *f_bspIRQN_pe = TIM14_IRQn;
                break;
            case FMKCPU_NVIC_TIM15_IRQN:
                *f_bspIRQN_pe = TIM15_IRQn;
                break;
            case FMKCPU_NVIC_TIM16_IRQN:
                *f_bspIRQN_pe = TIM16_IRQn;
                break;
            case FMKCPU_NVIC_TIM17_IRQN:
                *f_bspIRQN_pe = TIM17_IRQn;
                break;
            case FMKCPU_NVIC_I2C1_IRQN:
                *f_bspIRQN_pe = I2C1_IRQn;
                break;
            case FMKCPU_NVIC_I2C2_IRQN:
                *f_bspIRQN_pe = I2C2_IRQn;
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
/*********************************
 * s_FMKCPU_Get_BspTimer
 *********************************/
static t_eReturnState s_FMKCPU_Get_BspNVICPriority(t_eFMKCPU_NVICPriority f_priority_e, t_uint32 *f_BspNVICPriority_pu32)
{
    t_eReturnState Ret_e = RC_OK;

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
                *f_BspNVICPriority_pu32 = 1;
                break;
            case FMKCPU_NVIC_PRIORITY_MEDIUM:
                *f_BspNVICPriority_pu32 = 3;
                break;
            case FMKCPU_NVIC_PRIORITY_HIGH:
                *f_BspNVICPriority_pu32 = 5;
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
 * s_FMKCPU_Set_HwChannelState
 *********************************/
static t_eReturnState s_FMKCPU_Set_HwChannelState(t_eFMKCPU_Timer f_timer_e,
                                                  t_eFMKCPU_InterruptChnl f_channel_e,
                                                  t_eFMKCPU_ChnlState f_chnlStateOpe_e)
{
    t_eReturnState Ret_e = RC_OK;
    t_uint32 bspChannel_u32 = 0;
    t_sFMKCPU_ChnlInfo  * channel_ps;
    t_sFMKCPU_TimerInfo * timer_ps;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_bool flagTimerRunning_b = False;

    // Argument already verify
    channel_ps = &g_TimerInfo_as[f_timer_e].Channel_as[f_channel_e];
    timer_ps = &g_TimerInfo_as[f_timer_e];
    if (channel_ps->State_e != f_chnlStateOpe_e)
    {
        Ret_e = s_FMKCPU_Get_BspChannel(f_channel_e, &bspChannel_u32);
        if (Ret_e == RC_OK)
        { // Depending on wehter we need to activate or deactivate function
            switch (f_chnlStateOpe_e)
            {
                case FMKCPU_CHNLST_ACTIVATED:
                { // We have to start HALfunction in Basic or Interrupt depending on f_chnlRunMode_e
                    // call the right HAL function Polling or Interrupt mode
                    if (g_TimerInfo_as[f_timer_e].IsNVICTimerEnable_b == (t_bool)False)
                    {
                        Ret_e = FMKCPU_Set_NVICState(g_TimerInfo_as[f_timer_e].IRQNType_e, FMKCPU_NVIC_OPE_ENABLE);
                    }
                    if (Ret_e == RC_OK)
                    {
                        flagTimerRunning_b = (t_bool)True;
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
                        Ret_e = FMKCPU_Set_NVICState(g_TimerInfo_as[f_timer_e].IRQNType_e, FMKCPU_NVIC_OPE_DISABLE);
                    }
                    if (Ret_e == RC_OK)
                    {
                        flagTimerRunning_b = (t_bool)False;
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
                timer_ps->IsTimerRunning_b = flagTimerRunning_b;
                channel_ps->State_e = f_chnlStateOpe_e;
            }
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCPU_Set_BspTimerInit
 *********************************/
static t_eReturnState s_FMKCPU_Set_BspTimerInit(t_sFMKCPU_TimerInfo * f_timer_ps,
                                                t_eFMKCPU_HwTimerCfg f_hwTimCfg_e,
                                                  t_uint32 f_prescaler_u32,
                                                  t_uint32 f_period_u32,
                                                  t_uint32 f_counterMode_32,
                                                  t_uint32 f_clockDivision_u32,
                                                  t_uint32 f_autoRePreload_u32)
{
    t_eReturnState Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;

    if (f_timer_ps == (t_sFMKCPU_TimerInfo *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKCPU_Set_HwClock(f_timer_ps->clock_e, FMKCPU_CLOCKPORT_OPE_ENABLE);
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
    t_eFMKCPU_Timer Calltimer_e = FMKCPU_TIMER_NB;
    HAL_TIM_ActiveChannel BspITChnl_e = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
    t_eFMKCPU_InterruptChnl ITChnl_e = FMKCPU_CHANNEL_NB;
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
        return; // Call somoene to deal with this error
    }
    else
    {
        if(g_TimerInfo_as[Calltimer_e].HwCfg_e == FMKCPU_HWTIM_CFG_EVNT)
        {
            ITChnl_e = FMKCPU_CHANNEL_1;
        }
        else
        {
            BspITChnl_e = HAL_TIM_GetActiveChannel(&g_TimerInfo_as[Calltimer_e].BspTimer_ps);
            switch (BspITChnl_e)
            {
                case HAL_TIM_ACTIVE_CHANNEL_1:
                    ITChnl_e = FMKCPU_CHANNEL_1;
                    break;

                case HAL_TIM_ACTIVE_CHANNEL_2:
                    ITChnl_e = FMKCPU_CHANNEL_1;
                    break;

                case HAL_TIM_ACTIVE_CHANNEL_3:
                    ITChnl_e = FMKCPU_CHANNEL_1;
                    break;

                case HAL_TIM_ACTIVE_CHANNEL_4:
                    ITChnl_e = FMKCPU_CHANNEL_1;
                    break;
                case HAL_TIM_ACTIVE_CHANNEL_CLEARED:
                default:
                    break;
            }
        }
        if (ITChnl_e != FMKCPU_CHANNEL_NB)
        {
            g_TimerInfo_as[Calltimer_e].Channel_as[ITChnl_e].chnl_cb(Calltimer_e, ITChnl_e);
        }
    }
    return;
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
void TIM3_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_3].BspTimer_ps);}
void TIM14_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_14].BspTimer_ps);}
void TIM15_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_15].BspTimer_ps);}
void TIM16_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_16].BspTimer_ps);}
void TIM17_IRQHandler(void){return HAL_TIM_IRQHandler(&g_TimerInfo_as[FMKCPU_TIMER_17].BspTimer_ps);}
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
