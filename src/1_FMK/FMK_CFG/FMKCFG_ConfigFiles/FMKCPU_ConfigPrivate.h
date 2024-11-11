/*********************************************************************
 * @file        FMKCPU_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKCPU_CONFIGPRIVATE_H_INCLUDED
#define FMKCPU_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./FMKCPU_ConfigPublic.h"
    #include "../FMKCFG_ConfigSpecific/FMKCPU_ConfigSpecific.h"
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Timer channels number: Start */
    #define FMKCPU_MAX_CHNL_TIMER_1 ((t_uint8)4)
    #define FMKCPU_MAX_CHNL_TIMER_3 ((t_uint8)4)
    #define FMKCPU_MAX_CHNL_TIMER_14 ((t_uint8)1)
    #define FMKCPU_MAX_CHNL_TIMER_15 ((t_uint8)2)
    #define FMKCPU_MAX_CHNL_TIMER_16 ((t_uint8)1)
    #define FMKCPU_MAX_CHNL_TIMER_17 ((t_uint8)1)
    /* CAUTION : Automatic generated code section for Timer channels number: End */
    #define FMKCPU_HSI_CLOCK_OSC_MHZ     ((t_uint8)8)        /**<  HSI oscillatator equals to 8 MHz */
    #define FMKCPU_TIMER_CLOCK_OSC_MHZ   ((t_uint8)8)        /**<  Frequency of the timer are 8 MHz */
    #define FMKCPU_TIMER_PWM_PSC         ((t_uint8)50)       /**<  for every PWM the Prescaler is a constant */
    #define FMKCPU_TIMER_IC_PSC          ((t_uint8)0)        /**<  for every InputCOmpare the Prescaler is a constant */
    #define FMKCPU_TIMER_IC_ARR          ((t_uint16)0xFFFF)       /**<  for every InputCOmpare the Prescaler is a constant */

    #define FMKCPU_TIMER_EVNT_MAX_LOW_PERIOD_MS ((t_uint16)60000)
    #define FMKCPU_TIMER_EVNT_PSC_HIGH          ((t_uint16)(FMKCPU_TIMER_CLOCK_OSC_MHZ * 1000)- (t_uint16)1) /**<  The prescaler use for evnt timer, having 1000Hz (1ms) */
    #define FMKCPU_TIMER_EVNT_PSC_LOW           ((t_uint16)65534)
    #define FMKCPU_TIME_BTWN_DIAG_MS            ((t_uint16)2000)   /**< Time between diagnostic for timer and channel in cyclic ope mode*/
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    /**
     *
     *	@brief      HAL enable clock Function abstraction
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel 
    *	 
    *
    *
    */
    typedef void (t_cbFMKCPU_ClockEnable)(void);
    /**
     *
     *	@brief      HAL Disable clock Function abstraction
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel 
    *	 
    *
    *
    */
    typedef void (t_cbFMKCPU_ClockDisable)(void);
    /**
    *
    *	@brief      HAL Timer function for get the hardware timer state
    *	@note       This function repertory in stm32f00xx_hal_tim,
    * 
    *   @param[in] f_handleTimer_s : the bsp init structure
    *  
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef HAL_TIM_StateTypeDef (t_cbFMKCPU_GetTimerState)(TIM_HandleTypeDef *f_handleTimer_s);
    /**
    *
    *	@brief      HAL Timer function for Init
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    * 
    *   @param[in] f_handleTimer_s : the bsp init structure
    *  
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef HAL_StatusTypeDef (t_cbFMKCPU_TimerInitFunc)(TIM_HandleTypeDef *f_handleTimer_s);
    /**
    *
    *	@brief      HAL Timer function for Init
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    * 
    *   @param[in] f_handleTimer_s : the bsp init structure
    * 
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef HAL_StatusTypeDef (t_cbFMKCPU_TimerDeInitFunc)(TIM_HandleTypeDef *f_handleTimer_s);
    /**
    *
    *	@brief      HAL Timer function in Polling xay
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    * 
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR 
    */
    typedef HAL_StatusTypeDef (t_cbFMKCPU_TimStartFuncModePolling)(TIM_HandleTypeDef *f_handleTimer_s, uint32_t f_channel_u32);
    /**
    *
    *	@brief      HAL Timer function in Interruption way  
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel 
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef HAL_StatusTypeDef (t_cbFMKCPU_TimStartFuncModeInterrupt)(TIM_HandleTypeDef *f_handleTimer_s, uint32_t f_channel_u32);
    /**
    *
    *	@brief      HAL Timer function in Polling xay
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef HAL_StatusTypeDef (t_cbFMKCPU_TimStopFuncModePolling)(TIM_HandleTypeDef *f_handleTimer_s, uint32_t f_channel_u32);
    /**
    *
    *	@brief      HAL Timer function in Interruption way  
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel 
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef HAL_StatusTypeDef (t_cbFMKCPU_TimStopFuncModeInterrupt)(TIM_HandleTypeDef *f_handleTimer_s, uint32_t f_channel_u32);

    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    /**< Structure for repertory all HAL_TIM function */
    typedef struct
    {
        t_cbFMKCPU_GetTimerState             * GetTimerState_cb;        /**< HAL_TIM function to get the timer state */
        t_cbFMKCPU_TimerInitFunc             * TimerInit_pcb;           /**< HAL_TIM function to set a timer init */
        t_cbFMKCPU_TimerDeInitFunc           * TimerDeInit_pcb;         /**< HAL_TIM function to set a timer deinit */
        t_cbFMKCPU_TimStartFuncModePolling   * StartFuncPoll_pcb;       /**< HAL_TIM function to start a timer_channel in polling mode */
        t_cbFMKCPU_TimStopFuncModePolling    * StopFuncPoll_pcb;        /**< HAL_TIM function to start a timer_channel in interruption mode */
        t_cbFMKCPU_TimStartFuncModeInterrupt * StartFuncInterrupt_pcb;  /**< HAL_TIM function to stop a timer_channel in polling mode */
        t_cbFMKCPU_TimStopFuncModeInterrupt  * StopFuncInterrupt_pcb;   /**< HAL_TIM function to stop a timer_channel in interruption mode */
    } t_sFMKCPU_TimChannelFunc;

    /**< Structure for repertory all clock enable/disable function */
    typedef struct
    {
        t_cbFMKCPU_ClockEnable  * EnableClk_pcb;        /**< HAL_TIM function to enable rcc clock */
        t_cbFMKCPU_ClockDisable * DisableClk_pcb;       /**< HAL_TIM function to disable rcc clock */
    }t_sFMKCPU_ClkFunc;

    /**< Structure for watchdog configuration */
    typedef struct 
    {
        t_uint16 psc_u16;           /**< variable for wacthdog timer prescaler value */
        t_uint16 reload_u16;        /**< variable for wacthdog timer ARR value */
    } t_sFMKCPU_BspWwdgCfg;

    /**< Structure for timer channel configuration */
    typedef struct
    {
        t_eFMKCPU_Timer               timer_e;      /**< timer configuration */
        t_eFMKCPU_InterruptChnl       channel_e;    /**< channel configuration */
    } t_sFMKCPU_BspTimerCfg;
    // **********²**********************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    /**< Set the NVIC Priority for all NVIC_IRqn Priority */
    const t_eFMKCPU_NVICPriority c_FMKCPU_IRQNPriority_ae[FMKCPU_NVIC_NB] = {
      //Colonne1                      Colonne2                      
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  WWDG_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RTC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  FLASH_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RCC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI0_1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI2_3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI4_15_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel2_3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel4_5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ADC1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM1_BRK_UP_TRG_COM_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM1_CC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM14_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM15_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM16_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM17_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART2_IRQn
    };

    /**< Referencing all Enable/Disable Rcc clock function */
    const t_sFMKCPU_ClkFunc c_FMKCPU_ClkFunctions_apcb[FMKCPU_NVIC_NB] = {
      //Colonne1                      Colonne2                      
        {FMKCPU_Enable_SYSCFG_Clock,    FMKCPU_Disable_SYSCFG_Clock},   // FMKCPU_RCC_CLK_SYSCFG
        {FMKCPU_Enable_ADC1_Clock,      FMKCPU_Disable_ADC1_Clock},     // FMKCPU_RCC_CLK_ADC1
        {FMKCPU_Enable_TIM1_Clock,      FMKCPU_Disable_TIM1_Clock},     // FMKCPU_RCC_CLK_TIM1
        {FMKCPU_Enable_TIM3_Clock,      FMKCPU_Disable_TIM3_Clock},     // FMKCPU_RCC_CLK_TIM3
        {FMKCPU_Enable_TIM14_Clock,     FMKCPU_Disable_TIM14_Clock},    // FMKCPU_RCC_CLK_TIM14
        {FMKCPU_Enable_TIM15_Clock,     FMKCPU_Disable_TIM15_Clock},    // FMKCPU_RCC_CLK_TIM15
        {FMKCPU_Enable_TIM16_Clock,     FMKCPU_Disable_TIM16_Clock},    // FMKCPU_RCC_CLK_TIM16
        {FMKCPU_Enable_TIM17_Clock,     FMKCPU_Disable_TIM17_Clock},    // FMKCPU_RCC_CLK_TIM17
        {FMKCPU_Enable_SPI1_Clock,      FMKCPU_Disable_SPI1_Clock},     // FMKCPU_RCC_CLK_SPI1
        {FMKCPU_Enable_SPI2_Clock,      FMKCPU_Disable_SPI2_Clock},     // FMKCPU_RCC_CLK_SPI2
        {FMKCPU_Enable_USART1_Clock,    FMKCPU_Disable_USART1_Clock},   // FMKCPU_RCC_CLK_USART1
        {FMKCPU_Enable_USART2_Clock,    FMKCPU_Disable_USART2_Clock},   // FMKCPU_RCC_CLK_USART2
        {FMKCPU_Enable_I2C1_Clock,      FMKCPU_Disable_I2C1_Clock},     // FMKCPU_RCC_CLK_I2C1
        {FMKCPU_Enable_GPIOA_Clock,     FMKCPU_Disable_GPIOA_Clock},    // FMKCPU_RCC_CLK_GPIOA
        {FMKCPU_Enable_GPIOB_Clock,     FMKCPU_Disable_GPIOB_Clock},    // FMKCPU_RCC_CLK_GPIOB
        {FMKCPU_Enable_GPIOC_Clock,     FMKCPU_Disable_GPIOC_Clock},    // FMKCPU_RCC_CLK_GPIOC
        {FMKCPU_Enable_GPIOF_Clock,     FMKCPU_Disable_GPIOF_Clock},    // FMKCPU_RCC_CLK_GPIOF
        {FMKCPU_Enable_CRC_Clock,       FMKCPU_Disable_CRC_Clock},      // FMKCPU_RCC_CLK_CRC
        {FMKCPU_Enable_DMA1_Clock,      FMKCPU_Disable_DMA1_Clock},     // FMKCPU_RCC_CLK_DMA1
        {FMKCPU_Enable_SRAM_Clock,      FMKCPU_Disable_SRAM_Clock},     // FMKCPU_RCC_CLK_SRAM
        {FMKCPU_Enable_FLITF_Clock,     FMKCPU_Disable_FLITF_Clock},    // FMKCPU_RCC_CLK_FLITF
        {FMKCPU_Enable_WWDG_Clock,      FMKCPU_Disable_WWDG_Clock},     // FMKCPU_RCC_CLK_WWDG
        {FMKCPU_Enable_PWR_Clock,       FMKCPU_Disable_PWR_Clock},      // FMKCPU_RCC_CLK_PWR
    };

    /**< timer max channel variable */
    const t_uint8 c_FMKCPU_TimMaxChnl_ua8[FMKCPU_TIMER_NB] = {
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_1,      // FMKCPU_TIMER_1
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_3,      // FMKCPU_TIMER_3
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_14,     // FMKCPU_TIMER_14
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_15,     // FMKCPU_TIMER_15
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_16,     // FMKCPU_TIMER_16
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_17,     // FMKCPU_TIMER_17
    };

    /* CAUTION : Automatic generated code section for Variable: End */

    /**< Referencing all HAL_TIM function*/
    const t_sFMKCPU_TimChannelFunc c_FMKCPU_BspTimFunc_apf[FMKCPU_HWTIM_CFG_NB] = 
    {//    Get Timer State                 Init Timer                       DeInitTimer                   StartPolling Func                StopPolling Funnc            Start Interrupt Func             Stop Interrupt Func
        {HAL_TIM_PWM_GetState,             HAL_TIM_PWM_Init,                HAL_TIM_PWM_DeInit,           HAL_TIM_PWM_Start,               HAL_TIM_PWM_Stop,             HAL_TIM_PWM_Start_IT,           HAL_TIM_PWM_Stop_IT},         // FMKCPU_CHANNEL_CFG_PWM 
        {HAL_TIM_IC_GetState,              HAL_TIM_IC_Init,                 HAL_TIM_IC_DeInit,            HAL_TIM_IC_Start,                HAL_TIM_IC_Stop,              HAL_TIM_IC_Start_IT,            HAL_TIM_IC_Stop_IT},          // FMKCPU_CHANNEL_CFG_IC
        {HAL_TIM_OC_GetState,              HAL_TIM_OC_Init,                 HAL_TIM_OC_DeInit,            HAL_TIM_OC_Start,                HAL_TIM_OC_Stop,              HAL_TIM_OC_Start_IT,            HAL_TIM_OC_Stop_IT},          // FMKCPU_CHANNEL_CFG_OC
        {HAL_TIM_OnePulse_GetState,        NULL_FONCTION,                   HAL_TIM_OnePulse_DeInit,      HAL_TIM_OnePulse_Start,          HAL_TIM_OnePulse_Stop,        HAL_TIM_OnePulse_Start_IT,      HAL_TIM_OnePulse_Stop_IT},    // FMKCPU_CHANNEL_CFG_OP
        {HAL_TIM_Base_GetState,            HAL_TIM_Base_Init,               HAL_TIM_Base_DeInit,          FMKCPU_HAL_TIM_Base_Start,       FMKCPU_HAL_TIM_Base_Stop,     FMKCPU_HAL_TIM_Base_Start_IT,   FMKCPU_HAL_TIM_Base_Stop_IT}, // FMKCPU_CHANNEL_CFG_EVNT
        {HAL_TIM_Encoder_GetState,         NULL_FONCTION,                   HAL_TIM_Encoder_DeInit,       HAL_TIM_Encoder_Start,           HAL_TIM_Encoder_Stop,         HAL_TIM_Encoder_Start_IT,       HAL_TIM_Encoder_Stop_IT},     // FMKCPU_CHANNEL_CFG_ECDR
    };

    /**< Hardware configuration watchdog Period Timer */
    const t_sFMKCPU_BspWwdgCfg c_FMKCPU_WwdgPeriodcfg_ua16[FMKCPU_WWDG_RESET_NB] = {
        // prescaler value         reload value
        {WWDG_PRESCALER_1,          98}, // FMKCPU_WWDG_RESET_50MS
        {WWDG_PRESCALER_2,          98}, // FMKCPU_WWDG_RESET_100MS
        {WWDG_PRESCALER_4,          98}, // FMKCPU_WWDG_RESET_200MS
        {WWDG_PRESCALER_8,          122},// FMKCPU_WWDG_RESET_500MS
    };
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKCPU_CONFIGPRIVATE_H_INCLUDED           
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
