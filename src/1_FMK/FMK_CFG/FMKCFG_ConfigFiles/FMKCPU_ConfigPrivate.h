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
    #include "../FMKCFG_ConfigSpecific/FMKCPU_ConfigSpecific.h"
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Timer channels number: Start */
    #define FMKCPU_MAX_CHNL_TIMER_1 ((t_uint8)4)
    #define FMKCPU_MAX_CHNL_TIMER_2 ((t_uint8)4)
    #define FMKCPU_MAX_CHNL_TIMER_3 ((t_uint8)4)
    #define FMKCPU_MAX_CHNL_TIMER_4 ((t_uint8)4)
    #define FMKCPU_MAX_CHNL_TIMER_5 ((t_uint8)4)
    #define FMKCPU_MAX_CHNL_TIMER_6 ((t_uint8)1)
    #define FMKCPU_MAX_CHNL_TIMER_7 ((t_uint8)1)
    #define FMKCPU_MAX_CHNL_TIMER_8 ((t_uint8)4)
    #define FMKCPU_MAX_CHNL_TIMER_15 ((t_uint8)2)
    #define FMKCPU_MAX_CHNL_TIMER_16 ((t_uint8)1)
    #define FMKCPU_MAX_CHNL_TIMER_17 ((t_uint8)1)
    #define FMKCPU_MAX_CHNL_TIMER_20 ((t_uint8)4)
    /* CAUTION : Automatic generated code section for Timer channels number: End */


    #define FMKCPU_TIMER_IC_PSC          ((t_uint8)20)        /**<  for every InputCOmpare the Prescaler is a constant */
    #define FMKCPU_TIMER_IC_ARR          ((t_uint16)0xFFFF)       /**<  for every InputCOmpare the Prescaler is a constant */

    #define FMKCPU_TIMER_EVNT_MAX_LOW_PERIOD_MS ((t_uint16)60000)
    #define FMKCPU_TIMER_EVNT_PSC_HIGH          ((t_uint16)(20 * 1000) - (t_uint16)1) /**<  The prescaler use for evnt timer, having 1000Hz (1ms) */
    #define FMKCPU_TIMER_EVNT_PSC_LOW           ((t_uint16)65534)
    #define FMKCPU_TIME_BTWN_DIAG_MS            ((t_uint16)2000)   /**< Time between diagnostic for timer and channel in cyclic ope mode*/

    #define FMKCPU_MASK_CHNL_RUN  ((t_uint16)1) /**< Mask to indicate that the channel is running */
    #define FMKCPU_MASK_CHNL_STOP ((t_uint16)0) /**< Mask to indicate that the channel is stopped */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Enum: Start */
    /* Number of timer enable in smt32xxx board */
    typedef enum
    {
        FMKCPU_TIMER_1 = 0x0,                  /**< Reference for HAL timer_1, this timer has 4 channel(s) */
        FMKCPU_TIMER_2,                        /**< Reference for HAL timer_2, this timer has 4 channel(s) */
        FMKCPU_TIMER_3,                        /**< Reference for HAL timer_3, this timer has 4 channel(s) */
        FMKCPU_TIMER_4,                        /**< Reference for HAL timer_4, this timer has 4 channel(s) */
        FMKCPU_TIMER_5,                        /**< Reference for HAL timer_5, this timer has 4 channel(s) */
        FMKCPU_TIMER_6,                        /**< Reference for HAL timer_6, this timer has 1 channel(s) */
        FMKCPU_TIMER_7,                        /**< Reference for HAL timer_7, this timer has 1 channel(s) */
        FMKCPU_TIMER_8,                        /**< Reference for HAL timer_8, this timer has 4 channel(s) */
        FMKCPU_TIMER_15,                       /**< Reference for HAL timer_15, this timer has 2 channel(s) */
        FMKCPU_TIMER_16,                       /**< Reference for HAL timer_16, this timer has 1 channel(s) */
        FMKCPU_TIMER_17,                       /**< Reference for HAL timer_17, this timer has 1 channel(s) */
        FMKCPU_TIMER_20,                       /**< Reference for HAL timer_20, this timer has 4 channel(s) */
    
        FMKCPU_TIMER_NB,
    } t_eFMKCPU_Timer;

    /* Number max of channel enable by timer */
    typedef enum
    {
        FMKCPU_CHANNEL_1 = 0x0,                  /**< Reference to HAL channel 0 */
        FMKCPU_CHANNEL_2,                        /**< Reference to HAL channel 1 */
        FMKCPU_CHANNEL_3,                        /**< Reference to HAL channel 2 */
        FMKCPU_CHANNEL_4,                        /**< Reference to HAL channel 3 */
    
        FMKCPU_CHANNEL_NB,
    } t_eFMKCPU_InterruptChnl;

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
   /**
    *
    *	@brief    Get the Prescaler and ARR value For Timer Configured in PWM.\n
    *
    *	@param[in]  f_idxTimRccClock_u8     : enum value for Idx Rcc Clock Timer, value from @ref t_eFMKCPU_ClockPort
    *	@param[in]  f_timOscSrc_e           : enum value to know which bsp clock support the frequence based to the timer
    *	@param[in]  f_SysClockValues_ua8    : pointor to all sys clock value of the system
    *	@param[in]  f_RqstTimerFreq_u32     : the timer frequency requested
    *	@param[in]  f_RqstTimerFreq_u32     : Container for ARR register value 
    *	@param[in]  f_RqstTimerFreq_u32     : Container for Prescaler Value
    *	@param[in]  f_ITChannel_cb         : call back function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
    */
    typedef t_eReturnCode (t_cbFMKCPU_GetTimerInfoInit)(t_uint8  f_idxTimRccClock_u8,
                                                        t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                        t_uint8  * f_SysClockValues_ua8,
                                                        t_float32   f_RqstTimerFreq_f32,
                                                        t_uint32 * f_bspTimARR_pu32,
                                                        t_uint32 * f_bspTimPrescaler_pu32);
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

    typedef struct 
    {
        t_uint32 PLLM_Divider_u32;
        t_uint32 PPLN_Multplier_u32;
        t_uint32 PLLR_Divider_u32;
        t_uint32 PPLQ_Divider_u32;
        t_uint32 PLLP_Divider_u32;
        t_uint32 AHB_Divider;
        t_uint32 APB1_Divider_u32;
        t_uint32 APB2_Divider_u32;
    } t_sFMKCPU_SysOscCfg;

    // **********²**********************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
#ifdef FMKCPU_STM32_ECU_FAMILY_G
    //---------Configuration Clock System---------------------------//
    // SysClock -> 120 Mhz
    // HCLK     -> 120 MHz
    // APB1     -> 60 MHz
    // APB2     -> 60  MHz
    // PLLQ     -> 60  MHz
    // PLLP     -> 40  MHz
    const t_sFMKCPU_SysOscCfg c_FmkCpu_SysOscCfg_as[FMKCPU_CORE_CLOCK_SPEED_NB] = {
    //   PLLM_Divider_u32         PPLN_Multplier_u32         PLLR_Divider_u32        PPLQ_Divider_u32         PLLP_Divider_u32            AHB_Divider                  APB1_Divider_u32        APB2_Divider_u32
        {RCC_PLLM_DIV2,         (t_uint32)12,                RCC_PLLR_DIV8,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV2,              RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, // FMKCPU_CORE_CLOCK_SPEED_8MHZ
        {RCC_PLLM_DIV4,         (t_uint32)16,                RCC_PLLR_DIV6,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV2,              RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, //  FMKCPU_CORE_CLOCK_SPEED_16MHZ
        {RCC_PLLM_DIV4,         (t_uint32)48,                RCC_PLLR_DIV6,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV4,              RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, //  FMKCPU_CORE_CLOCK_SPEED_32MHZ
        {RCC_PLLM_DIV4,         (t_uint32)60,                RCC_PLLR_DIV6,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV6,              RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, //  FMKCPU_CORE_CLOCK_SPEED_40MHZ
        {RCC_PLLM_DIV4,         (t_uint32)72,                RCC_PLLR_DIV6,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV6,              RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, //  FMKCPU_CORE_CLOCK_SPEED_48MHZ
        {RCC_PLLM_DIV4,         (t_uint32)64,                RCC_PLLR_DIV4,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV6,              RCC_SYSCLK_DIV1,             RCC_HCLK_DIV1,          RCC_HCLK_DIV1}, //  FMKCPU_CORE_CLOCK_SPEED_64MHZ
        {RCC_PLLM_DIV3,         (t_uint32)60,                RCC_PLLR_DIV4,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV8,              RCC_SYSCLK_DIV1,             RCC_HCLK_DIV2,          RCC_HCLK_DIV2}, //  FMKCPU_CORE_CLOCK_SPEED_80MHZ
        {RCC_PLLM_DIV3,         (t_uint32)24,                RCC_PLLR_DIV2,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV4,              RCC_SYSCLK_DIV1,             RCC_HCLK_DIV2,          RCC_HCLK_DIV2}, //  FMKCPU_CORE_CLOCK_SPEED_96MHZ
        {RCC_PLLM_DIV1,         (t_uint32)16,                RCC_PLLR_DIV2,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV6,              RCC_SYSCLK_DIV1,             RCC_HCLK_DIV2,          RCC_HCLK_DIV2}, //  FMKCPU_CORE_CLOCK_SPEED_132MHZ
        {RCC_PLLM_DIV1,         (t_uint32)20,                RCC_PLLR_DIV2,          RCC_PLLQ_DIV2,           RCC_PLLP_DIV8,              RCC_SYSCLK_DIV1,             RCC_HCLK_DIV2,          RCC_HCLK_DIV2}, //  FMKCPU_CORE_CLOCK_SPEED_160MHZ
    };

    const t_uint8 c_FmkCpu_CoreClkValue_ua8[FMKCPU_CORE_CLOCK_SPEED_NB][FMKCPU_SYS_CLOCK_NB] = 
    {//    HSE                                      HSI                             SYSTEM                           HCLK1                         AHB1                          AHB2                          APB1                          APB2                          PLLQ                          PLLP 
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)12,                   (t_uint8)12,                    (t_uint8)12,                 (t_uint8)12,                 (t_uint8)12,                    (t_uint8)12,                  (t_uint8)48,                  (t_uint8)48},  //  FMKCPU_CORE_CLOCK_SPEED_8MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)16,                   (t_uint8)16,                    (t_uint8)16,                 (t_uint8)16,                 (t_uint8)16,                    (t_uint8)16,                  (t_uint8)64,                  (t_uint8)42},  //  FMKCPU_CORE_CLOCK_SPEED_16MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)32,                   (t_uint8)32,                    (t_uint8)32,                 (t_uint8)32,                 (t_uint8)32,                    (t_uint8)32,                  (t_uint8)96,                  (t_uint8)48},  //  FMKCPU_CORE_CLOCK_SPEED_32MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)40,                   (t_uint8)40,                    (t_uint8)40,                 (t_uint8)40,                 (t_uint8)40,                    (t_uint8)40,                  (t_uint8)120,                 (t_uint8)40},  //  FMKCPU_CORE_CLOCK_SPEED_40MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)48,                   (t_uint8)48,                    (t_uint8)48,                 (t_uint8)48,                 (t_uint8)48,                    (t_uint8)48,                  (t_uint8)144,                 (t_uint8)48},  //  FMKCPU_CORE_CLOCK_SPEED_48MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)64,                   (t_uint8)64,                    (t_uint8)64,                 (t_uint8)64,                 (t_uint8)64,                    (t_uint8)64,                  (t_uint8)128,                 (t_uint8)42},  //  FMKCPU_CORE_CLOCK_SPEED_64MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)80,                   (t_uint8)80,                    (t_uint8)80,                 (t_uint8)80,                 (t_uint8)40,                    (t_uint8)40,                  (t_uint8)160,                 (t_uint8)40},  //  FMKCPU_CORE_CLOCK_SPEED_80MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)96,                   (t_uint8)96,                    (t_uint8)96,                 (t_uint8)96,                 (t_uint8)48,                    (t_uint8)48,                  (t_uint8)96,                  (t_uint8)48},  //  FMKCPU_CORE_CLOCK_SPEED_96MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)128,                  (t_uint8)128,                   (t_uint8)128,                (t_uint8)128,                (t_uint8)64,                    (t_uint8)64,                  (t_uint8)128,                 (t_uint8)42},  //  FMKCPU_CORE_CLOCK_SPEED_132MHZ
        {(t_uint8)8,                            (t_uint8)16,                      (t_uint8)160,                  (t_uint8)160,                   (t_uint8)160,                (t_uint8)160,                (t_uint8)80,                    (t_uint8)80,                  (t_uint8)160,                 (t_uint8)40},  //  FMKCPU_CORE_CLOCK_SPEED_160MHZ
    };
#elif defined FMKCPU_STM32_ECU_FAMILY_F
    const t_sFMKCPU_SysOscCfg c_FmkCpu_SysOscCfg_s = {
    // PLLM_Divider_u32         PPLN_Multplier_u32          PLLR_Divider_u32        PPLQ_Divider_u32         PLLP_Divider_u32            AHB_Divider                  APB1_Divider_u32        APB2_Divider_u32
    };
    const t_uint8 c_FmkCpu_CoreClkValue_ua8[FMKCPU_SYS_CLOCK_NB] = 
    {
        (t_uint8)0,     // FMKCPU_SYS_CLOCK_HSI
        (t_uint8)0,    // FMKCPU_SYS_CLOCK_CORE
        (t_uint8)0,    // FMKCPU_SYS_CLOCK_HCLK
        (t_uint8)0,    // FMKCPU_SYS_CLOCK_APB1
        (t_uint8)0,    // FMKCPU_SYS_CLOCK_APB2
        (t_uint8)0,     // FMKCPU_SYS_CLOCK_PLLQ
        (t_uint8)0,     // FMKCPU_SYS_CLOCK_PLLP
    };
#endif

    const t_uint32 c_FmkCpu_ClkSpeedFreqValueMhz_ua8[FMKCPU_CORE_CLOCK_SPEED_NB] = {
        (t_uint32)(8  ),//  FMKCPU_CORE_CLOCK_SPEED_8MHZ
        (t_uint32)(16 ),//  FMKCPU_CORE_CLOCK_SPEED_16MHZ
        (t_uint32)(32 ),//  FMKCPU_CORE_CLOCK_SPEED_32MHZ
        (t_uint32)(40 ),//  FMKCPU_CORE_CLOCK_SPEED_40MHZ
        (t_uint32)(48 ),//  FMKCPU_CORE_CLOCK_SPEED_48MHZ
        (t_uint32)(64 ),//  FMKCPU_CORE_CLOCK_SPEED_64MHZ
        (t_uint32)(80 ),//  FMKCPU_CORE_CLOCK_SPEED_80MHZ
        (t_uint32)(96 ),//  FMKCPU_CORE_CLOCK_SPEED_96MHZ
        (t_uint32)(132),//  FMKCPU_CORE_CLOCK_SPEED_132MHZ
        (t_uint32)(160),//  FMKCPU_CORE_CLOCK_SPEED_160MHZ
    };

    /**< Referencing all HAL_TIM function*/
    const t_sFMKCPU_TimChannelFunc c_FMKCPU_BspTimFunc_apf[FMKCPU_HWTIM_CFG_NB] = 
    {//    Get Timer State                 Init Timer                       DeInitTimer                   StartPolling Func                StopPolling Funnc            Start Interrupt Func             Stop Interrupt Func
        {HAL_TIM_PWM_GetState,             HAL_TIM_PWM_Init,                HAL_TIM_PWM_DeInit,           HAL_TIM_PWM_Start,               HAL_TIM_PWM_Stop,             HAL_TIM_PWM_Start_IT,           HAL_TIM_PWM_Stop_IT},         // FMKCPU_CHANNEL_CFG_PWM 
        {HAL_TIM_IC_GetState,              HAL_TIM_IC_Init,                 HAL_TIM_IC_DeInit,            HAL_TIM_IC_Start,                HAL_TIM_IC_Stop,              HAL_TIM_IC_Start_IT,            HAL_TIM_IC_Stop_IT},          // FMKCPU_CHANNEL_CFG_IC
        {HAL_TIM_OC_GetState,              HAL_TIM_OC_Init,                 HAL_TIM_OC_DeInit,            HAL_TIM_OC_Start,                HAL_TIM_OC_Stop,              HAL_TIM_OC_Start_IT,            HAL_TIM_OC_Stop_IT},          // FMKCPU_CHANNEL_CFG_OC
        {HAL_TIM_OnePulse_GetState,        NULL_FONCTION,                   HAL_TIM_OnePulse_DeInit,      HAL_TIM_OnePulse_Start,          HAL_TIM_OnePulse_Stop,        HAL_TIM_OnePulse_Start_IT,      HAL_TIM_OnePulse_Stop_IT},    // FMKCPU_CHANNEL_CFG_OP
        {HAL_TIM_Base_GetState,            HAL_TIM_Base_Init,               HAL_TIM_Base_DeInit,          FMKCPU_HAL_TIM_Base_Start,       FMKCPU_HAL_TIM_Base_Stop,     FMKCPU_HAL_TIM_Base_Start_IT,   FMKCPU_HAL_TIM_Base_Stop_IT}, // FMKCPU_CHANNEL_CFG_EVNT
        {HAL_TIM_Encoder_GetState,         NULL_FONCTION,                   HAL_TIM_Encoder_DeInit,       HAL_TIM_Encoder_Start,           HAL_TIM_Encoder_Stop,         HAL_TIM_Encoder_Start_IT,       HAL_TIM_Encoder_Stop_IT},     // FMKCPU_CHANNEL_CFG_ECDR
        {HAL_TIM_PWM_GetState,             HAL_TIM_PWM_Init,                HAL_TIM_PWM_DeInit,           HAL_TIM_PWM_Start,               HAL_TIM_PWM_Stop,             HAL_TIM_PWM_Start_IT,           HAL_TIM_PWM_Stop_IT},         // FMKCPU_CHANNEL_CFG_DAC 
    };

    /**< Function to dynamically set the the best init value for Timer */
    const t_cbFMKCPU_GetTimerInfoInit * c_FMKCPU_GetTimInfoInit_apf[FMKCPU_HWTIM_CFG_NB] = {
        FMKCPU_GetPwmTimerInitParam,// FMKCPU_CHANNEL_CFG_PWM
        FMKCPU_GetICTimerInitParam,// FMKCPU_CHANNEL_CFG_IC
        FMKCPU_GetOCTimerInitParam,// FMKCPU_CHANNEL_CFG_OC
        FMKCPU_GetOPTimerInitParam,// FMKCPU_CHANNEL_CFG_OP
        FMKCPU_GetEvntTimerInitParam,// FMKCPU_CHANNEL_CFG_EVNT
        FMKCPU_GetECDRTimerInitParam,// FMKCPU_CHANNEL_CFG_ECDR
        FMKCPU_GetDacTimerInitParam,// FMKCPU_CHANNEL_CFG_DAC
    };

    /**< Hardware configuration watchdog Period Timer */
    const t_sFMKCPU_BspWwdgCfg c_FMKCPU_WwdgPeriodcfg_ua16[FMKCPU_WWDG_RESET_NB] = {
        // prescaler value         reload value
        {WWDG_PRESCALER_1,          98}, // FMKCPU_WWDG_RESET_50MS
        {WWDG_PRESCALER_2,          98}, // FMKCPU_WWDG_RESET_100MS
        {WWDG_PRESCALER_4,          98}, // FMKCPU_WWDG_RESET_200MS
        {WWDG_PRESCALER_8,          122},// FMKCPU_WWDG_RESET_500MS
    };

    /* CAUTION : Automatic generated code section for Variable: Start */
    /**< General Purpose Timer Channel Mapping */
    t_sFMKCPU_BspTimerCfg c_FmkCpu_ITLineIOMapp_as[FMKCPU_INTERRUPT_LINE_IO_NB] = {
        {FMKCPU_TIMER_1,                        FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_IO_11
        {FMKCPU_TIMER_1,                        FMKCPU_CHANNEL_2},    // FMKCPU_INTERRUPT_LINE_IO_12
        {FMKCPU_TIMER_1,                        FMKCPU_CHANNEL_3},    // FMKCPU_INTERRUPT_LINE_IO_13
        {FMKCPU_TIMER_1,                        FMKCPU_CHANNEL_4},    // FMKCPU_INTERRUPT_LINE_IO_14
        {FMKCPU_TIMER_2,                        FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_IO_21
        {FMKCPU_TIMER_2,                        FMKCPU_CHANNEL_2},    // FMKCPU_INTERRUPT_LINE_IO_22
        {FMKCPU_TIMER_2,                        FMKCPU_CHANNEL_3},    // FMKCPU_INTERRUPT_LINE_IO_23
        {FMKCPU_TIMER_2,                        FMKCPU_CHANNEL_4},    // FMKCPU_INTERRUPT_LINE_IO_24
        {FMKCPU_TIMER_3,                        FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_IO_31
        {FMKCPU_TIMER_3,                        FMKCPU_CHANNEL_2},    // FMKCPU_INTERRUPT_LINE_IO_32
        {FMKCPU_TIMER_3,                        FMKCPU_CHANNEL_3},    // FMKCPU_INTERRUPT_LINE_IO_33
        {FMKCPU_TIMER_3,                        FMKCPU_CHANNEL_4},    // FMKCPU_INTERRUPT_LINE_IO_34
        {FMKCPU_TIMER_4,                        FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_IO_41
        {FMKCPU_TIMER_4,                        FMKCPU_CHANNEL_2},    // FMKCPU_INTERRUPT_LINE_IO_42
        {FMKCPU_TIMER_4,                        FMKCPU_CHANNEL_3},    // FMKCPU_INTERRUPT_LINE_IO_43
        {FMKCPU_TIMER_4,                        FMKCPU_CHANNEL_4},    // FMKCPU_INTERRUPT_LINE_IO_44
        {FMKCPU_TIMER_5,                        FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_IO_51
        {FMKCPU_TIMER_5,                        FMKCPU_CHANNEL_2},    // FMKCPU_INTERRUPT_LINE_IO_52
        {FMKCPU_TIMER_5,                        FMKCPU_CHANNEL_3},    // FMKCPU_INTERRUPT_LINE_IO_53
        {FMKCPU_TIMER_5,                        FMKCPU_CHANNEL_4},    // FMKCPU_INTERRUPT_LINE_IO_54
        {FMKCPU_TIMER_8,                        FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_IO_61
        {FMKCPU_TIMER_8,                        FMKCPU_CHANNEL_2},    // FMKCPU_INTERRUPT_LINE_IO_62
        {FMKCPU_TIMER_8,                        FMKCPU_CHANNEL_3},    // FMKCPU_INTERRUPT_LINE_IO_63
        {FMKCPU_TIMER_8,                        FMKCPU_CHANNEL_4},    // FMKCPU_INTERRUPT_LINE_IO_64
        {FMKCPU_TIMER_20,                       FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_IO_71
        {FMKCPU_TIMER_20,                       FMKCPU_CHANNEL_2},    // FMKCPU_INTERRUPT_LINE_IO_72
        {FMKCPU_TIMER_20,                       FMKCPU_CHANNEL_3},    // FMKCPU_INTERRUPT_LINE_IO_73
        {FMKCPU_TIMER_20,                       FMKCPU_CHANNEL_4},    // FMKCPU_INTERRUPT_LINE_IO_74
    };

    /**< Event Purpose Timer Channel Mapping */
    t_sFMKCPU_BspTimerCfg c_FmkCpu_ITLineEvntMapp_as[FMKCPU_INTERRUPT_LINE_EVNT_NB] = {
        {FMKCPU_TIMER_15,                       FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_EVNT_1
        {FMKCPU_TIMER_15,                       FMKCPU_CHANNEL_2},    // FMKCPU_INTERRUPT_LINE_EVNT_1
        {FMKCPU_TIMER_16,                       FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_EVNT_3
        {FMKCPU_TIMER_17,                       FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_EVNT_4
    };

    /**< Dac Purpose Timer Channel Mapping */
    t_sFMKCPU_BspTimerCfg c_FmkCpu_ITLineDacMapp_as[FMKCPU_INTERRUPT_LINE_DAC_NB] = {
        {FMKCPU_TIMER_6,                        FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_DAC_1
        {FMKCPU_TIMER_7,                        FMKCPU_CHANNEL_1},    // FMKCPU_INTERRUPT_LINE_DAC_2
    };

    /**< Set the NVIC Priority for all NVIC_IRqn Priority */
    const t_eFMKCPU_NVICPriority c_FMKCPU_IRQNPriority_ae[FMKCPU_NVIC_NB] = {
      //Colonne1                      Colonne2                      
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  WWDG_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  PVD_PVM_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RTC_TAMP_LSECSS_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RTC_WKUP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  FLASH_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RCC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI0_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel7_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ADC1_2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USB_HP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USB_LP_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN1_IT0_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN1_IT1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI9_5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM1_BRK_TIM15_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM1_UP_TIM16_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM1_TRG_COM_TIM17_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM1_CC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C1_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C1_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C2_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C2_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI15_10_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RTC_Alarm_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USBWakeUp_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM8_BRK_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM8_UP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM8_TRG_COM_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM8_CC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ADC3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  FMC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LPTIM1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  UART4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  UART5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM6_DAC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM7_DAC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ADC4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ADC5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  UCPD1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  COMP1_2_3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  COMP4_5_6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  COMP7_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_Master_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_TIMA_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_TIMB_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_TIMC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_TIMD_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_TIME_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_FLT_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_TIMF_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  CRS_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SAI1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM20_BRK_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM20_UP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM20_TRG_COM_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM20_CC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  FPU_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C4_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C4_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI4_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN2_IT0_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN2_IT1_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN3_IT0_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN3_IT1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RNG_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LPUART1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C3_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C3_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMAMUX_OVR_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  QUADSPI_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Channel8_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel7_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Channel8_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  CORDIC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  FMAC_IRQn
    };

    /**< Referencing all Enable/Disable Rcc clock function */
    const t_sFMKCPU_ClkFunc c_FMKCPU_ClkFunctions_apcb[FMKCPU_NVIC_NB] = {
      //Colonne1                      Colonne2                      
        {FMKCPU_Enable_DMA1_Clock,      FMKCPU_Disable_DMA1_Clock},     // FMKCPU_RCC_CLK_DMA1
        {FMKCPU_Enable_DMA2_Clock,      FMKCPU_Disable_DMA2_Clock},     // FMKCPU_RCC_CLK_DMA2
        {FMKCPU_Enable_DMAMUX1_Clock,   FMKCPU_Disable_DMAMUX1_Clock},  // FMKCPU_RCC_CLK_DMAMUX1
        {FMKCPU_Enable_CORDIC_Clock,    FMKCPU_Disable_CORDIC_Clock},   // FMKCPU_RCC_CLK_CORDIC
        {FMKCPU_Enable_FMAC_Clock,      FMKCPU_Disable_FMAC_Clock},     // FMKCPU_RCC_CLK_FMAC
        {FMKCPU_Enable_FLASH_Clock,     FMKCPU_Disable_FLASH_Clock},    // FMKCPU_RCC_CLK_FLASH
        {FMKCPU_Enable_CRC_Clock,       FMKCPU_Disable_CRC_Clock},      // FMKCPU_RCC_CLK_CRC
        {FMKCPU_Enable_GPIOG_Clock,     FMKCPU_Disable_GPIOG_Clock},    // FMKCPU_RCC_CLK_GPIOG
        {FMKCPU_Enable_GPIOF_Clock,     FMKCPU_Disable_GPIOF_Clock},    // FMKCPU_RCC_CLK_GPIOF
        {FMKCPU_Enable_GPIOE_Clock,     FMKCPU_Disable_GPIOE_Clock},    // FMKCPU_RCC_CLK_GPIOE
        {FMKCPU_Enable_GPIOD_Clock,     FMKCPU_Disable_GPIOD_Clock},    // FMKCPU_RCC_CLK_GPIOD
        {FMKCPU_Enable_GPIOC_Clock,     FMKCPU_Disable_GPIOC_Clock},    // FMKCPU_RCC_CLK_GPIOC
        {FMKCPU_Enable_GPIOB_Clock,     FMKCPU_Disable_GPIOB_Clock},    // FMKCPU_RCC_CLK_GPIOB
        {FMKCPU_Enable_GPIOA_Clock,     FMKCPU_Disable_GPIOA_Clock},    // FMKCPU_RCC_CLK_GPIOA
        {FMKCPU_Enable_ADC12_Clock,     FMKCPU_Disable_ADC12_Clock},    // FMKCPU_RCC_CLK_ADC12
        {FMKCPU_Enable_ADC345_Clock,    FMKCPU_Disable_ADC345_Clock},   // FMKCPU_RCC_CLK_ADC345
        {FMKCPU_Enable_DAC1_Clock,      FMKCPU_Disable_DAC1_Clock},     // FMKCPU_RCC_CLK_DAC1
        {FMKCPU_Enable_DAC2_Clock,      FMKCPU_Disable_DAC2_Clock},     // FMKCPU_RCC_CLK_DAC2
        {FMKCPU_Enable_DAC3_Clock,      FMKCPU_Disable_DAC3_Clock},     // FMKCPU_RCC_CLK_DAC3
        {FMKCPU_Enable_DAC4_Clock,      FMKCPU_Disable_DAC4_Clock},     // FMKCPU_RCC_CLK_DAC4
        {FMKCPU_Enable_RNG_Clock,       FMKCPU_Disable_RNG_Clock},      // FMKCPU_RCC_CLK_RNG
        {FMKCPU_Enable_FMC_Clock,       FMKCPU_Disable_FMC_Clock},      // FMKCPU_RCC_CLK_FMC
        {FMKCPU_Enable_QSPI_Clock,      FMKCPU_Disable_QSPI_Clock},     // FMKCPU_RCC_CLK_QSPI
        {FMKCPU_Enable_TIM2_Clock,      FMKCPU_Disable_TIM2_Clock},     // FMKCPU_RCC_CLK_TIM2
        {FMKCPU_Enable_TIM3_Clock,      FMKCPU_Disable_TIM3_Clock},     // FMKCPU_RCC_CLK_TIM3
        {FMKCPU_Enable_TIM4_Clock,      FMKCPU_Disable_TIM4_Clock},     // FMKCPU_RCC_CLK_TIM4
        {FMKCPU_Enable_TIM5_Clock,      FMKCPU_Disable_TIM5_Clock},     // FMKCPU_RCC_CLK_TIM5
        {FMKCPU_Enable_TIM6_Clock,      FMKCPU_Disable_TIM6_Clock},     // FMKCPU_RCC_CLK_TIM6
        {FMKCPU_Enable_TIM7_Clock,      FMKCPU_Disable_TIM7_Clock},     // FMKCPU_RCC_CLK_TIM7
        {FMKCPU_Enable_CRS_Clock,       FMKCPU_Disable_CRS_Clock},      // FMKCPU_RCC_CLK_CRS
        {FMKCPU_Enable_RTCAPB_Clock,    FMKCPU_Disable_RTCAPB_Clock},   // FMKCPU_RCC_CLK_RTCAPB
        {FMKCPU_Enable_WWDG_Clock,      FMKCPU_Disable_WWDG_Clock},     // FMKCPU_RCC_CLK_WWDG
        {FMKCPU_Enable_SPI2_Clock,      FMKCPU_Disable_SPI2_Clock},     // FMKCPU_RCC_CLK_SPI2
        {FMKCPU_Enable_SPI3_Clock,      FMKCPU_Disable_SPI3_Clock},     // FMKCPU_RCC_CLK_SPI3
        {FMKCPU_Enable_USART2_Clock,    FMKCPU_Disable_USART2_Clock},   // FMKCPU_RCC_CLK_USART2
        {FMKCPU_Enable_USART3_Clock,    FMKCPU_Disable_USART3_Clock},   // FMKCPU_RCC_CLK_USART3
        {FMKCPU_Enable_UART4_Clock,     FMKCPU_Disable_UART4_Clock},    // FMKCPU_RCC_CLK_UART4
        {FMKCPU_Enable_UART5_Clock,     FMKCPU_Disable_UART5_Clock},    // FMKCPU_RCC_CLK_UART5
        {FMKCPU_Enable_I2C2_Clock,      FMKCPU_Disable_I2C2_Clock},     // FMKCPU_RCC_CLK_I2C2
        {FMKCPU_Enable_USB_Clock,       FMKCPU_Disable_USB_Clock},      // FMKCPU_RCC_CLK_USB
        {FMKCPU_Enable_FDCAN_Clock,     FMKCPU_Disable_FDCAN_Clock},    // FMKCPU_RCC_CLK_FDCAN
        {FMKCPU_Enable_PWR_Clock,       FMKCPU_Disable_PWR_Clock},      // FMKCPU_RCC_CLK_PWR
        {FMKCPU_Enable_I2C3_Clock,      FMKCPU_Disable_I2C3_Clock},     // FMKCPU_RCC_CLK_I2C3
        {FMKCPU_Enable_LPTIM1_Clock,    FMKCPU_Disable_LPTIM1_Clock},   // FMKCPU_RCC_CLK_LPTIM1
        {FMKCPU_Enable_UCPD1_Clock,     FMKCPU_Disable_UCPD1_Clock},    // FMKCPU_RCC_CLK_UCPD1
        {FMKCPU_Enable_SYSCFG_Clock,    FMKCPU_Disable_SYSCFG_Clock},   // FMKCPU_RCC_CLK_SYSCFG
        {FMKCPU_Enable_TIM1_Clock,      FMKCPU_Disable_TIM1_Clock},     // FMKCPU_RCC_CLK_TIM1
        {FMKCPU_Enable_SPI1_Clock,      FMKCPU_Disable_SPI1_Clock},     // FMKCPU_RCC_CLK_SPI1
        {FMKCPU_Enable_TIM8_Clock,      FMKCPU_Disable_TIM8_Clock},     // FMKCPU_RCC_CLK_TIM8
        {FMKCPU_Enable_USART1_Clock,    FMKCPU_Disable_USART1_Clock},   // FMKCPU_RCC_CLK_USART1
        {FMKCPU_Enable_SPI4_Clock,      FMKCPU_Disable_SPI4_Clock},     // FMKCPU_RCC_CLK_SPI4
        {FMKCPU_Enable_TIM15_Clock,     FMKCPU_Disable_TIM15_Clock},    // FMKCPU_RCC_CLK_TIM15
        {FMKCPU_Enable_TIM16_Clock,     FMKCPU_Disable_TIM16_Clock},    // FMKCPU_RCC_CLK_TIM16
        {FMKCPU_Enable_TIM17_Clock,     FMKCPU_Disable_TIM17_Clock},    // FMKCPU_RCC_CLK_TIM17
        {FMKCPU_Enable_TIM20_Clock,     FMKCPU_Disable_TIM20_Clock},    // FMKCPU_RCC_CLK_TIM20
        {FMKCPU_Enable_SAI1_Clock,      FMKCPU_Disable_SAI1_Clock},     // FMKCPU_RCC_CLK_SAI1
        {FMKCPU_Enable_HRTIM1_Clock,    FMKCPU_Disable_HRTIM1_Clock},   // FMKCPU_RCC_CLK_HRTIM1
    };

    /**< timer max channel variable */
    const t_uint8 c_FMKCPU_TimMaxChnl_ua8[FMKCPU_TIMER_NB] = {
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_1,      // FMKCPU_TIMER_1
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_2,      // FMKCPU_TIMER_2
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_3,      // FMKCPU_TIMER_3
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_4,      // FMKCPU_TIMER_4
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_5,      // FMKCPU_TIMER_5
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_6,      // FMKCPU_TIMER_6
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_7,      // FMKCPU_TIMER_7
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_8,      // FMKCPU_TIMER_8
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_15,     // FMKCPU_TIMER_15
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_16,     // FMKCPU_TIMER_16
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_17,     // FMKCPU_TIMER_17
        (t_uint8)FMKCPU_MAX_CHNL_TIMER_20,     // FMKCPU_TIMER_20
    };

    /**< Timer/Oscillator source constant */
    const t_eFMKCPU_SysClkOsc c_FmkCpu_TimClkSrc_ae[FMKCPU_TIMER_NB] ={
        FMKCPU_SYS_CLOCK_APB2,          // FMKCPU_TIMER_1
        FMKCPU_SYS_CLOCK_APB1,          // FMKCPU_TIMER_2
        FMKCPU_SYS_CLOCK_APB1,          // FMKCPU_TIMER_3
        FMKCPU_SYS_CLOCK_APB1,          // FMKCPU_TIMER_4
        FMKCPU_SYS_CLOCK_APB1,          // FMKCPU_TIMER_5
        FMKCPU_SYS_CLOCK_APB1,          // FMKCPU_TIMER_6
        FMKCPU_SYS_CLOCK_APB2,          // FMKCPU_TIMER_7
        FMKCPU_SYS_CLOCK_APB2,          // FMKCPU_TIMER_8
        FMKCPU_SYS_CLOCK_APB2,          // FMKCPU_TIMER_15
        FMKCPU_SYS_CLOCK_APB2,          // FMKCPU_TIMER_16
        FMKCPU_SYS_CLOCK_APB2,          // FMKCPU_TIMER_17
        FMKCPU_SYS_CLOCK_APB2,          // FMKCPU_TIMER_20
    };

    const t_eFMKCPU_SysClkOsc c_FmkCpu_RccClockOscSrc_ae[FMKCPU_RCC_CLK_NB] = {
    FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_DMA1
    FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_DMA2
    FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_DMAMUX1
    FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_CORDIC
    FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_FMAC
    FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_FLASH
    FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_CRC
    FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOG
    FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOF
    FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOE
    FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOD
    FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOC
    FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOB
    FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_GPIOA
    FMKCPU_SYS_CLOCK_PLLP,            // FMKCPU_RCC_CLK_ADC12
    FMKCPU_SYS_CLOCK_PLLP,            // FMKCPU_RCC_CLK_ADC345
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_DAC1
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_DAC2
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_DAC3
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_DAC4
    FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_RNG
    FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_FMC
    FMKCPU_SYS_CLOCK_PLLQ,            // FMKCPU_RCC_CLK_QSPI
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM2
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM3
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM4
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM5
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM6
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM7
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_CRS
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_RTCAPB
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_WWDG
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_SPI2
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_SPI3
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_USART2
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_USART3
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_UART4
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_UART5
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_I2C2
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_USB
    FMKCPU_SYS_CLOCK_PLLQ,            // FMKCPU_RCC_CLK_FDCAN
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_PWR
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_I2C3
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_LPTIM1
    FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_UCPD1
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SYSCFG
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM1
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SPI1
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM8
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_USART1
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SPI4
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM15
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM16
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM17
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM20
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SAI1
    FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_HRTIM1
    };

    /* CAUTION : Automatic generated code section for Variable: End */
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
