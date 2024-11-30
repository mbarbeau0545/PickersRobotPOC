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
    #include "stm32g4xx_hal.h"
    #include "stm32g4xx.h"
    /* CAUTION : Automatic generated code section for CPU Configuration: End */
    // flag automatic generate code
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    // flag automatic generate code
    #define FMKCPU_STM32_ECU_FAMILY_G

    #define FMKCPU_WWDG_RESET_CFG  FMKCPU_WWDG_RESET_100MS /**< default watchdogs configuration */

    #define FMKCPU_PLLQ_CLOCK_OSC_MHZ    ((t_uint8)64)       /**< LLP oscillator equals to 64 MHz */
    #define FMKCPU_HSI_CLOCK_OSC_MHZ     ((t_uint8)8)        /**<  HSI oscillatator equals to 8 MHz */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    
    //-----------------------------ENUM TYPES-----------------------------//
    /**< Interrupt Line Type */
    typedef enum 
    {
        FMKCPU_INTERRUPT_LINE_TYPE_IO = 0x00,       /**< Timer/Channel use for PWM, IC, OC, OP Purpose */
        FMKCPU_INTERRUPT_LINE_TYPE_EVNT,            /**< Timer/Channel use for Event purpose */
        FMKCPU_INTERRUPT_LINE_TYPE_DAC,             /**< Timmer/Channel use for DAC purpose */

        FMKCPU_INTERRUPT_LINE_TYPE_NB,
    } t_eFMKCPU_InterruptLineType;
    /* CAUTION : Automatic generated code section for Enum: Start */
    /* Number of General Purpose Interrupt Line, for PWM, Input-Compare, Output Compare, One sPulse */
    typedef enum
    {
        FMKCPU_INTERRUPT_LINE_IO_01 = 0x0,                 /**< General Purpose Timer, Reference to Timer 1 Channel 1 */
        FMKCPU_INTERRUPT_LINE_IO_02,                       /**< General Purpose Timer, Reference to Timer 1 Channel 2 */
        FMKCPU_INTERRUPT_LINE_IO_03,                       /**< General Purpose Timer, Reference to Timer 1 Channel 3 */
        FMKCPU_INTERRUPT_LINE_IO_04,                       /**< General Purpose Timer, Reference to Timer 1 Channel 4 */
        FMKCPU_INTERRUPT_LINE_IO_11,                       /**< General Purpose Timer, Reference to Timer 2 Channel 1 */
        FMKCPU_INTERRUPT_LINE_IO_12,                       /**< General Purpose Timer, Reference to Timer 2 Channel 2 */
        FMKCPU_INTERRUPT_LINE_IO_13,                       /**< General Purpose Timer, Reference to Timer 2 Channel 3 */
        FMKCPU_INTERRUPT_LINE_IO_14,                       /**< General Purpose Timer, Reference to Timer 2 Channel 4 */
        FMKCPU_INTERRUPT_LINE_IO_21,                       /**< General Purpose Timer, Reference to Timer 3 Channel 1 */
        FMKCPU_INTERRUPT_LINE_IO_22,                       /**< General Purpose Timer, Reference to Timer 3 Channel 2 */
        FMKCPU_INTERRUPT_LINE_IO_23,                       /**< General Purpose Timer, Reference to Timer 3 Channel 3 */
        FMKCPU_INTERRUPT_LINE_IO_24,                       /**< General Purpose Timer, Reference to Timer 3 Channel 4 */
        FMKCPU_INTERRUPT_LINE_IO_31,                       /**< General Purpose Timer, Reference to Timer 4 Channel 1 */
        FMKCPU_INTERRUPT_LINE_IO_32,                       /**< General Purpose Timer, Reference to Timer 4 Channel 2 */
        FMKCPU_INTERRUPT_LINE_IO_33,                       /**< General Purpose Timer, Reference to Timer 4 Channel 3 */
        FMKCPU_INTERRUPT_LINE_IO_34,                       /**< General Purpose Timer, Reference to Timer 4 Channel 4 */
        FMKCPU_INTERRUPT_LINE_IO_41,                       /**< General Purpose Timer, Reference to Timer 5 Channel 1 */
        FMKCPU_INTERRUPT_LINE_IO_42,                       /**< General Purpose Timer, Reference to Timer 5 Channel 2 */
        FMKCPU_INTERRUPT_LINE_IO_43,                       /**< General Purpose Timer, Reference to Timer 5 Channel 3 */
        FMKCPU_INTERRUPT_LINE_IO_44,                       /**< General Purpose Timer, Reference to Timer 5 Channel 4 */
        FMKCPU_INTERRUPT_LINE_IO_51,                       /**< General Purpose Timer, Reference to Timer 8 Channel 1 */
        FMKCPU_INTERRUPT_LINE_IO_52,                       /**< General Purpose Timer, Reference to Timer 8 Channel 2 */
        FMKCPU_INTERRUPT_LINE_IO_53,                       /**< General Purpose Timer, Reference to Timer 8 Channel 3 */
        FMKCPU_INTERRUPT_LINE_IO_54,                       /**< General Purpose Timer, Reference to Timer 8 Channel 4 */
        FMKCPU_INTERRUPT_LINE_IO_61,                       /**< General Purpose Timer, Reference to Timer 20 Channel 1 */
        FMKCPU_INTERRUPT_LINE_IO_62,                       /**< General Purpose Timer, Reference to Timer 20 Channel 2 */
        FMKCPU_INTERRUPT_LINE_IO_63,                       /**< General Purpose Timer, Reference to Timer 20 Channel 3 */
        FMKCPU_INTERRUPT_LINE_IO_64,                       /**< General Purpose Timer, Reference to Timer 20 Channel 4 */
    
        FMKCPU_INTERRUPT_LINE_IO_NB,
    } t_eFMKCPU_InterruptLineIO;

    /* Number of Event Purpose Interrupt Line */
    typedef enum
    {
        FMKCPU_INTERRUPT_LINE_EVNT_1 = 0x0,                  /**< Event Purpose Timer, Reference to Timer 15 Channel 1 */
        FMKCPU_INTERRUPT_LINE_EVNT_2,                        /**< Event Purpose Timer, Reference to Timer 15 Channel 2 */
        FMKCPU_INTERRUPT_LINE_EVNT_1,                        /**< Event Purpose Timer, Reference to Timer 16 Channel 1 */
        FMKCPU_INTERRUPT_LINE_EVNT_1,                        /**< Event Purpose Timer, Reference to Timer 17 Channel 1 */
    
        FMKCPU_INTERRUPT_LINE_EVNT_NB,
    } t_eFMKCPU_InterruptLineEvnt;

    /* Number of DAC Purpose Interrupt Line */
    typedef enum
    {
        FMKCPU_INTERRUPT_LINE_DAC_1 = 0x0,                  /**< Dac Purpose Timer, Reference to Timer 6 Channel 1 */
        FMKCPU_INTERRUPT_LINE_DAC_1,                        /**< Dac Purpose Timer, Reference to Timer 7 Channel 1 */
    
        FMKCPU_INTERRUPT_LINE_DAC_NB,
    } t_eFMKCPU_InterruptLineDAC;

    /* Enum for rcc clock state reference */
    typedef enum
    {
        FMKCPU_RCC_CLK_DMA1 = 0x0,               /**< None */
        FMKCPU_RCC_CLK_DMA2,                     /**< None */
        FMKCPU_RCC_CLK_DMAMUX1,                  /**< None */
        FMKCPU_RCC_CLK_CORDIC,                   /**< None */
        FMKCPU_RCC_CLK_FMAC,                     /**< None */
        FMKCPU_RCC_CLK_FLASH,                    /**< None */
        FMKCPU_RCC_CLK_CRC,                      /**< None */
        FMKCPU_RCC_CLK_GPIOG,                    /**< None */
        FMKCPU_RCC_CLK_GPIOF,                    /**< None */
        FMKCPU_RCC_CLK_GPIOE,                    /**< None */
        FMKCPU_RCC_CLK_GPIOD,                    /**< None */
        FMKCPU_RCC_CLK_GPIOC,                    /**< None */
        FMKCPU_RCC_CLK_GPIOB,                    /**< None */
        FMKCPU_RCC_CLK_GPIOA,                    /**< None */
        FMKCPU_RCC_CLK_ADC12,                    /**< None */
        FMKCPU_RCC_CLK_ADC345,                   /**< None */
        FMKCPU_RCC_CLK_DAC1,                     /**< None */
        FMKCPU_RCC_CLK_DAC2,                     /**< None */
        FMKCPU_RCC_CLK_DAC3,                     /**< None */
        FMKCPU_RCC_CLK_DAC4,                     /**< None */
        FMKCPU_RCC_CLK_RNG,                      /**< None */
        FMKCPU_RCC_CLK_FMC,                      /**< None */
        FMKCPU_RCC_CLK_QSPI,                     /**< None */
        FMKCPU_RCC_CLK_TIM2,                     /**< None */
        FMKCPU_RCC_CLK_TIM3,                     /**< None */
        FMKCPU_RCC_CLK_TIM4,                     /**< None */
        FMKCPU_RCC_CLK_TIM5,                     /**< None */
        FMKCPU_RCC_CLK_TIM6,                     /**< None */
        FMKCPU_RCC_CLK_TIM7,                     /**< None */
        FMKCPU_RCC_CLK_CRS,                      /**< None */
        FMKCPU_RCC_CLK_RTCAPB,                   /**< None */
        FMKCPU_RCC_CLK_WWDG,                     /**< None */
        FMKCPU_RCC_CLK_SPI2,                     /**< None */
        FMKCPU_RCC_CLK_SPI3,                     /**< None */
        FMKCPU_RCC_CLK_USART2,                   /**< None */
        FMKCPU_RCC_CLK_USART3,                   /**< None */
        FMKCPU_RCC_CLK_USART4,                   /**< None */
        FMKCPU_RCC_CLK_USART5,                   /**< None */
        FMKCPU_RCC_CLK_I2C2,                     /**< None */
        FMKCPU_RCC_CLK_USB,                      /**< None */
        FMKCPU_RCC_CLK_FDCAN,                    /**< None */
        FMKCPU_RCC_CLK_PWR,                      /**< None */
        FMKCPU_RCC_CLK_I2C3,                     /**< None */
        FMKCPU_RCC_CLK_LPTIM1,                   /**< None */
        FMKCPU_RCC_CLK_UCPD1,                    /**< None */
        FMKCPU_RCC_CLK_SYSCFG,                   /**< None */
        FMKCPU_RCC_CLK_TIM1,                     /**< None */
        FMKCPU_RCC_CLK_SPI1,                     /**< None */
        FMKCPU_RCC_CLK_TIM8,                     /**< x */
        FMKCPU_RCC_CLK_USART1,                   /**< x */
        FMKCPU_RCC_CLK_SPI4,                     /**< x */
        FMKCPU_RCC_CLK_TIM15,                    /**< None */
        FMKCPU_RCC_CLK_TIM16,                    /**< None */
        FMKCPU_RCC_CLK_TIM17,                    /**< None */
        FMKCPU_RCC_CLK_TIM20,                    /**< None */
        FMKCPU_RCC_CLK_SAI1,                     /**< None */
        FMKCPU_RCC_CLK_HRTIM1,                   /**< None */
    
        FMKCPU_RCC_CLK_NB,
    } t_eFMKCPU_ClockPort;

    /* Enum for NVIC list */
    typedef enum
    {
        FMKCPU_NVIC_WWDG_IRQN = 0x0,          /**< Reference to HAL nvic WWDG_IRQn */
        FMKCPU_NVIC_PVD_PVM_IRQN,             /**< Reference to HAL nvic PVD_PVM_IRQn */
        FMKCPU_NVIC_RTC_TAMP_LSECSS_IRQN,     /**< Reference to HAL nvic RTC_TAMP_LSECSS_IRQn */
        FMKCPU_NVIC_RTC_WKUP_IRQN,            /**< Reference to HAL nvic RTC_WKUP_IRQn */
        FMKCPU_NVIC_FLASH_IRQN,               /**< Reference to HAL nvic FLASH_IRQn */
        FMKCPU_NVIC_RCC_IRQN,                 /**< Reference to HAL nvic RCC_IRQn */
        FMKCPU_NVIC_EXTI0_IRQN,               /**< Reference to HAL nvic EXTI0_IRQn */
        FMKCPU_NVIC_EXTI1_IRQN,               /**< Reference to HAL nvic EXTI1_IRQn */
        FMKCPU_NVIC_EXTI2_IRQN,               /**< Reference to HAL nvic EXTI2_IRQn */
        FMKCPU_NVIC_EXTI3_IRQN,               /**< Reference to HAL nvic EXTI3_IRQn */
        FMKCPU_NVIC_EXTI4_IRQN,               /**< Reference to HAL nvic EXTI4_IRQn */
        FMKCPU_NVIC_DMA1_CHANNEL1_IRQN,       /**< Reference to HAL nvic DMA1_Channel1_IRQn */
        FMKCPU_NVIC_DMA1_CHANNEL2_IRQN,       /**< Reference to HAL nvic DMA1_Channel2_IRQn */
        FMKCPU_NVIC_DMA1_CHANNEL3_IRQN,       /**< Reference to HAL nvic DMA1_Channel3_IRQn */
        FMKCPU_NVIC_DMA1_CHANNEL4_IRQN,       /**< Reference to HAL nvic DMA1_Channel4_IRQn */
        FMKCPU_NVIC_DMA1_CHANNEL5_IRQN,       /**< Reference to HAL nvic DMA1_Channel5_IRQn */
        FMKCPU_NVIC_DMA1_CHANNEL6_IRQN,       /**< Reference to HAL nvic DMA1_Channel6_IRQn */
        FMKCPU_NVIC_DMA1_CHANNEL7_IRQN,       /**< Reference to HAL nvic DMA1_Channel7_IRQn */
        FMKCPU_NVIC_ADC1_2_IRQN,              /**< Reference to HAL nvic ADC1_2_IRQn */
        FMKCPU_NVIC_USB_HP_IRQN,              /**< Reference to HAL nvic USB_HP_IRQn */
        FMKCPU_NVIC_USB_LP_IRQN,              /**< Reference to HAL nvic USB_LP_IRQn */
        FMKCPU_NVIC_FDCAN1_IT0_IRQN,          /**< Reference to HAL nvic FDCAN1_IT0_IRQn */
        FMKCPU_NVIC_FDCAN1_IT1_IRQN,          /**< Reference to HAL nvic FDCAN1_IT1_IRQn */
        FMKCPU_NVIC_EXTI9_5_IRQN,             /**< Reference to HAL nvic EXTI9_5_IRQn */
        FMKCPU_NVIC_TIM1_BRK_TIM15_IRQN,      /**< Reference to HAL nvic TIM1_BRK_TIM15_IRQn */
        FMKCPU_NVIC_TIM1_UP_TIM16_IRQN,       /**< Reference to HAL nvic TIM1_UP_TIM16_IRQn */
        FMKCPU_NVIC_TIM1_TRG_COM_TIM17_IRQN,  /**< Reference to HAL nvic TIM1_TRG_COM_TIM17_IRQn */
        FMKCPU_NVIC_TIM1_CC_IRQN,             /**< Reference to HAL nvic TIM1_CC_IRQn */
        FMKCPU_NVIC_TIM2_IRQN,                /**< Reference to HAL nvic TIM2_IRQn */
        FMKCPU_NVIC_TIM3_IRQN,                /**< Reference to HAL nvic TIM3_IRQn */
        FMKCPU_NVIC_TIM4_IRQN,                /**< Reference to HAL nvic TIM4_IRQn */
        FMKCPU_NVIC_I2C1_EV_IRQN,             /**< Reference to HAL nvic I2C1_EV_IRQn */
        FMKCPU_NVIC_I2C1_ER_IRQN,             /**< Reference to HAL nvic I2C1_ER_IRQn */
        FMKCPU_NVIC_I2C2_EV_IRQN,             /**< Reference to HAL nvic I2C2_EV_IRQn */
        FMKCPU_NVIC_I2C2_ER_IRQN,             /**< Reference to HAL nvic I2C2_ER_IRQn */
        FMKCPU_NVIC_SPI1_IRQN,                /**< Reference to HAL nvic SPI1_IRQn */
        FMKCPU_NVIC_SPI2_IRQN,                /**< Reference to HAL nvic SPI2_IRQn */
        FMKCPU_NVIC_USART1_IRQN,              /**< Reference to HAL nvic USART1_IRQn */
        FMKCPU_NVIC_USART2_IRQN,              /**< Reference to HAL nvic USART2_IRQn */
        FMKCPU_NVIC_USART3_IRQN,              /**< Reference to HAL nvic USART3_IRQn */
        FMKCPU_NVIC_EXTI15_10_IRQN,           /**< Reference to HAL nvic EXTI15_10_IRQn */
        FMKCPU_NVIC_RTC_ALARM_IRQN,           /**< Reference to HAL nvic RTC_Alarm_IRQn */
        FMKCPU_NVIC_USBWAKEUP_IRQN,           /**< Reference to HAL nvic USBWakeUp_IRQn */
        FMKCPU_NVIC_TIM8_BRK_IRQN,            /**< Reference to HAL nvic TIM8_BRK_IRQn */
        FMKCPU_NVIC_TIM8_UP_IRQN,             /**< Reference to HAL nvic TIM8_UP_IRQn */
        FMKCPU_NVIC_TIM8_TRG_COM_IRQN,        /**< Reference to HAL nvic TIM8_TRG_COM_IRQn */
        FMKCPU_NVIC_TIM8_CC_IRQN,             /**< Reference to HAL nvic TIM8_CC_IRQn */
        FMKCPU_NVIC_ADC3_IRQN,                /**< Reference to HAL nvic ADC3_IRQn */
        FMKCPU_NVIC_FMC_IRQN,                 /**< Reference to HAL nvic FMC_IRQn */
        FMKCPU_NVIC_LPTIM1_IRQN,              /**< Reference to HAL nvic LPTIM1_IRQn */
        FMKCPU_NVIC_TIM5_IRQN,                /**< Reference to HAL nvic TIM5_IRQn */
        FMKCPU_NVIC_SPI3_IRQN,                /**< Reference to HAL nvic SPI3_IRQn */
        FMKCPU_NVIC_UART4_IRQN,               /**< Reference to HAL nvic UART4_IRQn */
        FMKCPU_NVIC_UART5_IRQN,               /**< Reference to HAL nvic UART5_IRQn */
        FMKCPU_NVIC_TIM6_DAC_IRQN,            /**< Reference to HAL nvic TIM6_DAC_IRQn */
        FMKCPU_NVIC_TIM7_DAC_IRQN,            /**< Reference to HAL nvic TIM7_DAC_IRQn */
        FMKCPU_NVIC_DMA2_CHANNEL1_IRQN,       /**< Reference to HAL nvic DMA2_Channel1_IRQn */
        FMKCPU_NVIC_DMA2_CHANNEL2_IRQN,       /**< Reference to HAL nvic DMA2_Channel2_IRQn */
        FMKCPU_NVIC_DMA2_CHANNEL3_IRQN,       /**< Reference to HAL nvic DMA2_Channel3_IRQn */
        FMKCPU_NVIC_DMA2_CHANNEL4_IRQN,       /**< Reference to HAL nvic DMA2_Channel4_IRQn */
        FMKCPU_NVIC_DMA2_CHANNEL5_IRQN,       /**< Reference to HAL nvic DMA2_Channel5_IRQn */
        FMKCPU_NVIC_ADC4_IRQN,                /**< Reference to HAL nvic ADC4_IRQn */
        FMKCPU_NVIC_ADC5_IRQN,                /**< Reference to HAL nvic ADC5_IRQn */
        FMKCPU_NVIC_UCPD1_IRQN,               /**< Reference to HAL nvic UCPD1_IRQn */
        FMKCPU_NVIC_COMP1_2_3_IRQN,           /**< Reference to HAL nvic COMP1_2_3_IRQn */
        FMKCPU_NVIC_COMP4_5_6_IRQN,           /**< Reference to HAL nvic COMP4_5_6_IRQn */
        FMKCPU_NVIC_COMP7_IRQN,               /**< Reference to HAL nvic COMP7_IRQn */
        FMKCPU_NVIC_HRTIM1_MASTER_IRQN,       /**< Reference to HAL nvic HRTIM1_Master_IRQn */
        FMKCPU_NVIC_HRTIM1_TIMA_IRQN,         /**< Reference to HAL nvic HRTIM1_TIMA_IRQn */
        FMKCPU_NVIC_HRTIM1_TIMB_IRQN,         /**< Reference to HAL nvic HRTIM1_TIMB_IRQn */
        FMKCPU_NVIC_HRTIM1_TIMC_IRQN,         /**< Reference to HAL nvic HRTIM1_TIMC_IRQn */
        FMKCPU_NVIC_HRTIM1_TIMD_IRQN,         /**< Reference to HAL nvic HRTIM1_TIMD_IRQn */
        FMKCPU_NVIC_HRTIM1_TIME_IRQN,         /**< Reference to HAL nvic HRTIM1_TIME_IRQn */
        FMKCPU_NVIC_HRTIM1_FLT_IRQN,          /**< Reference to HAL nvic HRTIM1_FLT_IRQn */
        FMKCPU_NVIC_HRTIM1_TIMF_IRQN,         /**< Reference to HAL nvic HRTIM1_TIMF_IRQn */
        FMKCPU_NVIC_CRS_IRQN,                 /**< Reference to HAL nvic CRS_IRQn */
        FMKCPU_NVIC_SAI1_IRQN,                /**< Reference to HAL nvic SAI1_IRQn */
        FMKCPU_NVIC_TIM20_BRK_IRQN,           /**< Reference to HAL nvic TIM20_BRK_IRQn */
        FMKCPU_NVIC_TIM20_UP_IRQN,            /**< Reference to HAL nvic TIM20_UP_IRQn */
        FMKCPU_NVIC_TIM20_TRG_COM_IRQN,       /**< Reference to HAL nvic TIM20_TRG_COM_IRQn */
        FMKCPU_NVIC_TIM20_CC_IRQN,            /**< Reference to HAL nvic TIM20_CC_IRQn */
        FMKCPU_NVIC_FPU_IRQN,                 /**< Reference to HAL nvic FPU_IRQn */
        FMKCPU_NVIC_I2C4_EV_IRQN,             /**< Reference to HAL nvic I2C4_EV_IRQn */
        FMKCPU_NVIC_I2C4_ER_IRQN,             /**< Reference to HAL nvic I2C4_ER_IRQn */
        FMKCPU_NVIC_SPI4_IRQN,                /**< Reference to HAL nvic SPI4_IRQn */
        FMKCPU_NVIC_FDCAN2_IT0_IRQN,          /**< Reference to HAL nvic FDCAN2_IT0_IRQn */
        FMKCPU_NVIC_FDCAN2_IT1_IRQN,          /**< Reference to HAL nvic FDCAN2_IT1_IRQn */
        FMKCPU_NVIC_FDCAN3_IT0_IRQN,          /**< Reference to HAL nvic FDCAN3_IT0_IRQn */
        FMKCPU_NVIC_FDCAN3_IT1_IRQN,          /**< Reference to HAL nvic FDCAN3_IT1_IRQn */
        FMKCPU_NVIC_RNG_IRQN,                 /**< Reference to HAL nvic RNG_IRQn */
        FMKCPU_NVIC_LPUART1_IRQN,             /**< Reference to HAL nvic LPUART1_IRQn */
        FMKCPU_NVIC_I2C3_EV_IRQN,             /**< Reference to HAL nvic I2C3_EV_IRQn */
        FMKCPU_NVIC_I2C3_ER_IRQN,             /**< Reference to HAL nvic I2C3_ER_IRQn */
        FMKCPU_NVIC_DMAMUX_OVR_IRQN,          /**< Reference to HAL nvic DMAMUX_OVR_IRQn */
        FMKCPU_NVIC_QUADSPI_IRQN,             /**< Reference to HAL nvic QUADSPI_IRQn */
        FMKCPU_NVIC_DMA1_CHANNEL8_IRQN,       /**< Reference to HAL nvic DMA1_Channel8_IRQn */
        FMKCPU_NVIC_DMA2_CHANNEL6_IRQN,       /**< Reference to HAL nvic DMA2_Channel6_IRQn */
        FMKCPU_NVIC_DMA2_CHANNEL7_IRQN,       /**< Reference to HAL nvic DMA2_Channel7_IRQn */
        FMKCPU_NVIC_DMA2_CHANNEL8_IRQN,       /**< Reference to HAL nvic DMA2_Channel8_IRQn */
        FMKCPU_NVIC_CORDIC_IRQN,              /**< Reference to HAL nvic CORDIC_IRQn */
        FMKCPU_NVIC_FMAC_IRQN,                /**< Reference to HAL nvic FMAC_IRQn */
    
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
