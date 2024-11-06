/*********************************************************************
 * @file        FMKIO_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKIO_ConfigPublic_H_INCLUDED
#define FMKIO_ConfigPublic_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "./FMKCDA_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    /* CAUTION : Automatic generated code section for Enum: Start */
    /* List of gpio port available on this board */
    typedef enum
    {
        FMKIO_GPIO_PORT_A = 0x0,                  /**< Reference to bsp gpio A register */
        FMKIO_GPIO_PORT_B,                        /**< Reference to bsp gpio B register */
        FMKIO_GPIO_PORT_C,                        /**< Reference to bsp gpio C register */
        FMKIO_GPIO_PORT_D,                        /**< Reference to bsp gpio D register */
        FMKIO_GPIO_PORT_F,                        /**< Reference to bsp gpio F register */
    
        FMKIO_GPIO_PORT_NB,
    } t_eFMKIO_GpioPort;

    /* List of Pin available for each GPIO on this board */
    typedef enum
    {
        FMKIO_GPIO_PIN_0 = 0x0,                  /**< Reference to bsp gpio pin 0 */
        FMKIO_GPIO_PIN_1,                        /**< Reference to bsp gpio pin 1 */
        FMKIO_GPIO_PIN_2,                        /**< Reference to bsp gpio pin 2 */
        FMKIO_GPIO_PIN_3,                        /**< Reference to bsp gpio pin 3 */
        FMKIO_GPIO_PIN_4,                        /**< Reference to bsp gpio pin 4 */
        FMKIO_GPIO_PIN_5,                        /**< Reference to bsp gpio pin 5 */
        FMKIO_GPIO_PIN_6,                        /**< Reference to bsp gpio pin 6 */
        FMKIO_GPIO_PIN_7,                        /**< Reference to bsp gpio pin 7 */
        FMKIO_GPIO_PIN_8,                        /**< Reference to bsp gpio pin 8 */
        FMKIO_GPIO_PIN_9,                        /**< Reference to bsp gpio pin 9 */
        FMKIO_GPIO_PIN_10,                       /**< Reference to bsp gpio pin 10 */
        FMKIO_GPIO_PIN_11,                       /**< Reference to bsp gpio pin 11 */
        FMKIO_GPIO_PIN_12,                       /**< Reference to bsp gpio pin 12 */
        FMKIO_GPIO_PIN_13,                       /**< Reference to bsp gpio pin 13 */
        FMKIO_GPIO_PIN_14,                       /**< Reference to bsp gpio pin 14 */
        FMKIO_GPIO_PIN_15,                       /**< Reference to bsp gpio pin 15 */
    
        FMKIO_GPIO_PIN_NB,
    } t_eFMKIO_BspGpioPin;

    /* /List of input digital pin available on this board */
    typedef enum
    {
        FMKIO_INPUT_SIGDIG_1 = 0x0,                  /**< PA12 */
        FMKIO_INPUT_SIGDIG_2,                        /**< PA13 */
        FMKIO_INPUT_SIGDIG_3,                        /**< PA14 */
        FMKIO_INPUT_SIGDIG_4,                        /**< PA15 */
        FMKIO_INPUT_SIGDIG_5,                        /**< PB0 */
        FMKIO_INPUT_SIGDIG_6,                        /**< PB1 */
        FMKIO_INPUT_SIGDIG_7,                        /**< PB2 */
        FMKIO_INPUT_SIGDIG_8,                        /**< PB3 */
        FMKIO_INPUT_SIGDIG_9,                        /**< PB4 */
        FMKIO_INPUT_SIGDIG_10,                       /**< PB5 */
        FMKIO_INPUT_SIGDIG_11,                       /**< PB11 */
    
        FMKIO_INPUT_SIGDIG_NB,
    } t_eFMKIO_InDigSig;

    /* List of input Analog pin available on this board */
    typedef enum
    {
        FMKIO_INPUT_SIGANA_1 = 0x0,                  /**< PC0 */
        FMKIO_INPUT_SIGANA_2,                        /**< PC1 */
        FMKIO_INPUT_SIGANA_3,                        /**< PC2 */
        FMKIO_INPUT_SIGANA_4,                        /**< PC3 */
        FMKIO_INPUT_SIGANA_5,                        /**< PA6 */
        FMKIO_INPUT_SIGANA_6,                        /**< PA7 */
        FMKIO_INPUT_SIGANA_7,                        /**< PB8 */
        FMKIO_INPUT_SIGANA_8,                        /**< PB9 */
        FMKIO_INPUT_SIGANA_9,                        /**< PA2 */
        FMKIO_INPUT_SIGANA_10,                       /**< PA3 */
    
        FMKIO_INPUT_SIGANA_NB,
    } t_eFMKIO_InAnaSig;

    /* List of input frequency pin available on this board */
    typedef enum
    {
        FMKIO_INPUT_SIGFREQ_1 = 0x0,                  /**< PA4 */
        FMKIO_INPUT_SIGFREQ_2,                        /**< PB14 */
        FMKIO_INPUT_SIGFREQ_3,                        /**< PB15 */
    
        FMKIO_INPUT_SIGFREQ_NB,
    } t_eFMKIO_InFreqSig;

    /* List of input event pin available on this board */
    typedef enum
    {
        FMKIO_INPUT_SIGEVNT_1 = 0x0,                  /**< PB10 */
        FMKIO_INPUT_SIGEVNT_2,                        /**< PA1 */
    
        FMKIO_INPUT_SIGEVNT_NB,
    } t_eFMKIO_InEvntSig;

    /* List of output digital pin available on this board */
    typedef enum
    {
        FMKIO_OUTPUT_SIGDIG_1 = 0x0,                  /**< PB12 */
        FMKIO_OUTPUT_SIGDIG_2,                        /**< PB13 */
        FMKIO_OUTPUT_SIGDIG_3,                        /**< PC4 */
        FMKIO_OUTPUT_SIGDIG_4,                        /**< PC5 */
        FMKIO_OUTPUT_SIGDIG_5,                        /**< PC13 */
        FMKIO_OUTPUT_SIGDIG_6,                        /**< PF4 */
        FMKIO_OUTPUT_SIGDIG_7,                        /**< PF5 */
        FMKIO_OUTPUT_SIGDIG_8,                        /**< PF6 */
        FMKIO_OUTPUT_SIGDIG_9,                        /**< PF7 */
    
        FMKIO_OUTPUT_SIGDIG_NB,
    } t_eFMKIO_OutDigSig;

    /* List of output PWM pin available on this board */
    typedef enum
    {
        FMKIO_OUTPUT_SIGPWM_1 = 0x0,                  /**< PC6 */
        FMKIO_OUTPUT_SIGPWM_2,                        /**< PC7 */
        FMKIO_OUTPUT_SIGPWM_3,                        /**< PC8 */
        FMKIO_OUTPUT_SIGPWM_4,                        /**< PC9 */
        FMKIO_OUTPUT_SIGPWM_5,                        /**< PA8 */
        FMKIO_OUTPUT_SIGPWM_6,                        /**< PA9 */
        FMKIO_OUTPUT_SIGPWM_7,                        /**< PA10 */
        FMKIO_OUTPUT_SIGPWM_8,                        /**< PA11 */
    
        FMKIO_OUTPUT_SIGPWM_NB,
    } t_eFMKIO_OutPwmSig;

    /* CAUTION : Automatic generated code section for Enum: End */
    
    // Flag automatic generate code
    /**< List of alternate function*/
    typedef enum
    {
        FMKIO_AF0_EVENTOUT = 0x0U,  /*!< AF0: EVENTOUT Alternate Function mapping */
        FMKIO_AF0_MCO,           /*!< AF0: MCO Alternate Function mapping */
        FMKIO_AF0_SPI1,          /*!< AF0: SPI1 Alternate Function mapping */
        FMKIO_AF0_SPI2,          /*!< AF0: SPI2 Alternate Function mapping */
        FMKIO_AF0_TIM15,         /*!< AF0: TIM15 Alternate Function mapping */
        FMKIO_AF0_TIM17,         /*!< AF0: TIM17 Alternate Function mapping */
        FMKIO_AF0_SWDIO,         /*!< AF0: SWDIO Alternate Function mapping */
        FMKIO_AF0_SWCLK,         /*!< AF0: SWCLK Alternate Function mapping */
        FMKIO_AF0_TIM14,         /*!< AF0: TIM14 Alternate Function mapping */
        FMKIO_AF0_USART1,        /*!< AF0: USART1 Alternate Function mapping */
        FMKIO_AF0_IR,            /*!< AF0: IR Alternate Function mapping */
        FMKIO_AF0_TIM3,          /*!< AF0: TIM3 Alternate Function mapping */

        FMKIO_AF1_TIM3,          /*!< AF1: TIM3 Alternate Function mapping */
        FMKIO_AF1_TIM15,         /*!< AF1: TIM15 Alternate Function mapping */
        FMKIO_AF1_USART1,        /*!< AF1: USART1 Alternate Function mapping */
        FMKIO_AF1_USART2,        /*!< AF1: USART2 Alternate Function mapping */
        FMKIO_AF1_EVENTOUT,      /*!< AF1: EVENTOUT Alternate Function mapping */
        FMKIO_AF1_I2C1,          /*!< AF1: I2C1 Alternate Function mapping */
        FMKIO_AF1_I2C2,          /*!< AF1: I2C2 Alternate Function mapping */
        FMKIO_AF1_IR,            /*!< AF1: IR Alternate Function mapping */

        FMKIO_AF2_TIM1,          /*!< AF2: TIM1 Alternate Function mapping */
        FMKIO_AF2_TIM16,         /*!< AF2: TIM16 Alternate Function mapping */
        FMKIO_AF2_TIM17,         /*!< AF2: TIM17 Alternate Function mapping */
        FMKIO_AF2_EVENTOUT,      /*!< AF2: EVENTOUT Alternate Function mapping */

        FMKIO_AF3_EVENTOUT,      /*!< AF3: EVENTOUT Alternate Function mapping */
        FMKIO_AF3_I2C1,          /*!< AF3: I2C1 Alternate Function mapping */
        FMKIO_AF3_TIM15,         /*!< AF3: TIM15 Alternate Function mapping */

        FMKIO_AF4_TIM14,         /*!< AF4: TIM14 Alternate Function mapping */

        FMKIO_AF5_TIM16,         /*!< AF5: TIM16 Alternate Function mapping */
        FMKIO_AF5_TIM17,         /*!< AF5: TIM17 Alternate Function mapping */

        FMKIO_AF6_EVENTOUT,      /*!< AF6: EVENTOUT Alternate Function mapping */

        FMKIO_AF_NB              /*!< Total number of alternate functions */
    } t_eFMKIO_AlternateFunc;



    //-----------------------------TYPEDEF TYPES---------------------------//
    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    /**< Basic configuration needed in all Signal configuration*/



    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************


    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKIO_ConfigPublic_H_INCLUDED           
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
