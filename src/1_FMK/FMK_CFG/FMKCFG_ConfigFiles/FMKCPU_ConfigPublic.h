/*********************************************************************
 * @file        FMKCPU_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        31/08/2024
 * @version     1.0
 */
  
#ifndef FMKCPU_CONFIGPUBLIC_H_INCLUDED
#define FMKCPU_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    /* CAUTION : Automatic generated code section for CPU Configuration: Start */
    #include "stm32f103x6.h"
    #include "stm32f1xx_hal.h"
    /* CAUTION : Automatic generated code section for CPU Configuration: End */
    // flag automatic generate code
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKCPU_WWDG_RESET_CFG  FMKCPU_WWDG_RESET_100MS /**< default watchdogs configuration */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    
    //-----------------------------ENUM TYPES-----------------------------//
    /* CAUTION : Automatic generated code section for Enum: Start */
    /* Number of timer enable in smt32xxx board */
    typedef enum
    {
        FMKCPU_TIMER_1 = 0x0,                  /**< Reference for HAL timer_1, this timer has 4 channel(s) */
        FMKCPU_TIMER_3,                        /**< Reference for HAL timer_3, this timer has 4 channel(s) */
        FMKCPU_TIMER_14,                       /**< Reference for HAL timer_14, this timer has 1 channel(s) */
        FMKCPU_TIMER_15,                       /**< Reference for HAL timer_15, this timer has 2 channel(s) */
        FMKCPU_TIMER_16,                       /**< Reference for HAL timer_16, this timer has 1 channel(s) */
        FMKCPU_TIMER_17,                       /**< Reference for HAL timer_17, this timer has 1 channel(s) */
    
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

    /* Enum for rcc clock state reference */
    typedef enum
    {
        FMKCPU_RCC_CLK_SYSCFG = 0x0,             /**< Clock for Global System configuration. */
        FMKCPU_RCC_CLK_ADC1,                     /**< Clock for ADC1 register access. */
        FMKCPU_RCC_CLK_TIM1,                     /**< Clock for Timer 1 register access. */
        FMKCPU_RCC_CLK_TIM3,                     /**< Clock for Timer 3 register access. */
        FMKCPU_RCC_CLK_TIM14,                    /**< Clock for Timer 14 register access. */
        FMKCPU_RCC_CLK_TIM15,                    /**< Clock for Timer 15 register access. */
        FMKCPU_RCC_CLK_TIM16,                    /**< Clock for Timer 16 register access. */
        FMKCPU_RCC_CLK_TIM17,                    /**< Clock for Timer 17 register access. */
        FMKCPU_RCC_CLK_SPI1,                     /**< Clock for SPI1 register access (Serial Peripheral Interface). */
        FMKCPU_RCC_CLK_SPI2,                     /**< Clock for SPI2 register access (Serial Peripheral Interface). */
        FMKCPU_RCC_CLK_USART1,                   /**< Clock for USART1 register access (Universal Synchronous/Asynchronous Receiver/Transmitter). */
        FMKCPU_RCC_CLK_USART2,                   /**< Clock for USART2 register access (Universal Synchronous/Asynchronous Receiver/Transmitter). */
        FMKCPU_RCC_CLK_I2C1,                     /**< Clock for I2C1 register access (Inter-Integrated Circuit). */
        FMKCPU_RCC_CLK_GPIOA,                    /**< Clock for GPIOA register access (General Purpose Input/Output A). */
        FMKCPU_RCC_CLK_GPIOB,                    /**< Clock for GPIOB register access (General Purpose Input/Output B). */
        FMKCPU_RCC_CLK_GPIOC,                    /**< Clock for GPIOC register access (General Purpose Input/Output C). */
        FMKCPU_RCC_CLK_GPIOF,                    /**< Clock for GPIOF register access (General Purpose Input/Output F). */
        FMKCPU_RCC_CLK_CRC,                      /**< Clock for CRC register access (Cyclic Redundancy Check). */
        FMKCPU_RCC_CLK_DMA1,                     /**< Clock for DMA1 register access (Direct Memory Access). */
        FMKCPU_RCC_CLK_SRAM,                     /**< Clock for SRAM register access (Static Random Access Memory). */
        FMKCPU_RCC_CLK_FLITF,                    /**< Clock for Flash Interface register access. */
        FMKCPU_RCC_CLK_WWDG,                     /**< Clock for Window Watchdog register access. */
        FMKCPU_RCC_CLK_PWR,                      /**< Clock for Power Control register access. */
    
        FMKCPU_RCC_CLK_NB,
    } t_eFMKCPU_ClockPort;

    /* Enum for NVIC list */
    typedef enum
    {
        FMKCPU_NVIC_WWDG_IRQN = 0x0,          /**< Reference to HAL nvic WWDG_IRQn */
        FMKCPU_NVIC_RTC_IRQN,                 /**< Reference to HAL nvic RTC_IRQn */
        FMKCPU_NVIC_FLASH_IRQN,               /**< Reference to HAL nvic FLASH_IRQn */
        FMKCPU_NVIC_RCC_IRQN,                 /**< Reference to HAL nvic RCC_IRQn */
        FMKCPU_NVIC_EXTI0_1_IRQN,             /**< Reference to HAL nvic EXTI0_1_IRQn */
        FMKCPU_NVIC_EXTI2_3_IRQN,             /**< Reference to HAL nvic EXTI2_3_IRQn */
        FMKCPU_NVIC_EXTI4_15_IRQN,            /**< Reference to HAL nvic EXTI4_15_IRQn */
        FMKCPU_NVIC_DMA1_CHANNEL1_IRQN,       /**< Reference to HAL nvic DMA1_Channel1_IRQn */
        FMKCPU_NVIC_DMA1_CHANNEL2_3_IRQN,     /**< Reference to HAL nvic DMA1_Channel2_3_IRQn */
        FMKCPU_NVIC_DMA1_CHANNEL4_5_IRQN,     /**< Reference to HAL nvic DMA1_Channel4_5_IRQn */
        FMKCPU_NVIC_ADC1_IRQN,                /**< Reference to HAL nvic ADC1_IRQn */
        FMKCPU_NVIC_TIM1_BRK_UP_TRG_COM_IRQN, /**< Reference to HAL nvic TIM1_BRK_UP_TRG_COM_IRQn */
        FMKCPU_NVIC_TIM1_CC_IRQN,             /**< Reference to HAL nvic TIM1_CC_IRQn */
        FMKCPU_NVIC_TIM3_IRQN,                /**< Reference to HAL nvic TIM3_IRQn */
        FMKCPU_NVIC_TIM6_IRQN,                /**< Reference to HAL nvic TIM6_IRQn */
        FMKCPU_NVIC_TIM14_IRQN,               /**< Reference to HAL nvic TIM14_IRQn */
        FMKCPU_NVIC_TIM15_IRQN,               /**< Reference to HAL nvic TIM15_IRQn */
        FMKCPU_NVIC_TIM16_IRQN,               /**< Reference to HAL nvic TIM16_IRQn */
        FMKCPU_NVIC_TIM17_IRQN,               /**< Reference to HAL nvic TIM17_IRQn */
        FMKCPU_NVIC_I2C1_IRQN,                /**< Reference to HAL nvic I2C1_IRQn */
        FMKCPU_NVIC_I2C2_IRQN,                /**< Reference to HAL nvic I2C2_IRQn */
        FMKCPU_NVIC_SPI1_IRQN,                /**< Reference to HAL nvic SPI1_IRQn */
        FMKCPU_NVIC_SPI2_IRQN,                /**< Reference to HAL nvic SPI2_IRQn */
        FMKCPU_NVIC_USART1_IRQN,              /**< Reference to HAL nvic USART1_IRQn */
        FMKCPU_NVIC_USART2_IRQN,              /**< Reference to HAL nvic USART2_IRQn */
    
        FMKCPU_NVIC_NB,
    } t_eFMKCPU_IRQNType;

    /* CAUTION : Automatic generated code section for Enum: End */
  
    /**< typedef enum for channel mode */
    typedef enum 
    {
        FMKCPU_HWTIM_CFG_PWM = 0x0U,        /**< Timer configuration in PWM mode */
        FMKCPU_HWTIM_CFG_IC,                /**< Timer configuration in Input Capture mode */
        FMKCPU_HWTIM_CFG_OC,                /**< Timer configuration in Ouput Compare mode */
        FMKCPU_HWTIM_CFG_OP,                /**< Timer configuration in One Pulse mode */
        FMKCPU_HWTIM_CFG_EVNT,              /**< Timer configuration in Event mode */
        FMKCPU_HWTIM_CFG_ECDR,              /**< Timer configuration in encoder mode */

        FMKCPU_HWTIM_CFG_NB,                /**< Number of timer configuration mode*/
    } t_eFMKCPU_HwTimerCfg;

    /**< Enum for NVIC priority */
    typedef enum 
    {
        FMKCPU_NVIC_PRIORITY_LOW = 0x0U,    /**< Reference to bsp priority low value */
        FMKCPU_NVIC_PRIORITY_MEDIUM,        /**< Reference to bsp priority medium value */
        FMKCPU_NVIC_PRIORITY_HIGH,          /**< Reference to bsp priority high value */

        FMKCPU_NVIC_PRIORITY_NB             /**< Number of reference to bsp priority */
    } t_eFMKCPU_NVICPriority;

    /**< Enum for watchdog timer list */
    typedef enum
    {
        FMKCPU_WWDG_RESET_50MS = 0,     /**< Watchdogs reset parameter is 50 ms */
        FMKCPU_WWDG_RESET_100MS,        /**< Watchdogs reset parameter is 100 ms */
        FMKCPU_WWDG_RESET_200MS,        /**< Watchdogs reset parameter is 200 ms */
        FMKCPU_WWDG_RESET_500MS,        /**< Watchdogs reset parameter is 500 ms */

        FMKCPU_WWDG_RESET_NB,           /**< Number of watchdogs reset parameter  */
    } t_eFMKCPu_WwdgResetPeriod;
    //-----------------------------TYPEDEF TYPES---------------------------//
    
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    


    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKCPU_CONFIGPUBLIC_H_INCLUDED           
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
