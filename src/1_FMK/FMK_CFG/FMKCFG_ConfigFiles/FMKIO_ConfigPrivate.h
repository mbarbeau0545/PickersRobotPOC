/*********************************************************************
 * @file        FMKCIO_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKIO_CONFIGPRIVATE_H_INCLUDED
#define FMKIO_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "../FMKCFG_ConfigSpecific/FMKIO_ConfigSpecific.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKIO_TIME_BTWN_DIAG_MS ((t_uint16)2000)  /**< Time between diagnostic for timer and channel in cyclic ope mode*/
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
    typedef struct 
    {
        t_eFMKIO_GpioPort    HwGpio_e;      /**< GPIO Port used for a certain signal */
        t_eFMKIO_BspGpioPin  HwPin_e;       /**< GPIO Pin used for a certain signal */
    } t_sFMKIO_BspSigCfg;

    /**< Structure configuration for Pwm and Signal needed timer*/
    typedef struct 
    {
        t_sFMKIO_BspSigCfg             BasicCfg_s;               /**< GPIO configuration */
        t_uint8                        BspAlternateFunc_u8;    /**< Alterante function/Timer_Channel relate to the pin */
        t_eFMKCPU_InterruptLineIO      ITLine_e;               /**< Interrupt Line connected to signal */
    } t_sFMKIO_BspTimerSigCfg;
    
    /**< Structure for Analog signal adc configuration */
    typedef struct 
    {
        t_sFMKIO_BspSigCfg      BasicCfg_s;
        t_eFMKCDA_Adc           adc_e;
        t_eFMKCDA_AdcChannel    adcChannel_e;
    }t_sFMKIO_AnaAdcCfg;
     
    /**< Structure configuration for Event Signal*/
    typedef struct 
    {
        t_sFMKIO_BspSigCfg      BasicCfg_s;               /**< GPIO configuration */
        t_eFMKCPU_IRQNType      ExtiIRQN_e;             /**< IRQN Type related to the signal */
    } t_sFMKIO_BspEvntSigCfg;

    typedef struct 
    {
        t_sFMKIO_BspSigCfg RxPin_s;                /**< GPIO configuration for RxCAN pin*/
        t_sFMKIO_BspSigCfg TxPin_s;                /**< GPIO configuration for TxCAN pin*/
        t_uint8            BspAlternateFunc_u8;    /**< Alterante function/FDCAN relate to the pin */
    } t_sFMKIO_RxTxComCfg;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    /**< Variable for bsp_enum pin mapping */
    const t_uint32 c_BspPinMapping_ua16[FMKIO_GPIO_PIN_NB] = {
        GPIO_PIN_0,               // FMKIO_GPIO_PIN_0
        GPIO_PIN_1,               // FMKIO_GPIO_PIN_1
        GPIO_PIN_2,               // FMKIO_GPIO_PIN_2
        GPIO_PIN_3,               // FMKIO_GPIO_PIN_3
        GPIO_PIN_4,               // FMKIO_GPIO_PIN_4
        GPIO_PIN_5,               // FMKIO_GPIO_PIN_5
        GPIO_PIN_6,               // FMKIO_GPIO_PIN_6
        GPIO_PIN_7,               // FMKIO_GPIO_PIN_7
        GPIO_PIN_8,               // FMKIO_GPIO_PIN_8
        GPIO_PIN_9,               // FMKIO_GPIO_PIN_9
        GPIO_PIN_10,              // FMKIO_GPIO_PIN_10
        GPIO_PIN_11,              // FMKIO_GPIO_PIN_11
        GPIO_PIN_12,              // FMKIO_GPIO_PIN_12
        GPIO_PIN_13,              // FMKIO_GPIO_PIN_13
        GPIO_PIN_14,              // FMKIO_GPIO_PIN_14
        GPIO_PIN_15,              // FMKIO_GPIO_PIN_15
    };

    /**< Variable for bsp_Gpio_Pin Digital input signal mapping */
    const t_sFMKIO_BspSigCfg c_InDigSigBspMap_as[FMKIO_INPUT_SIGDIG_NB] = {
        //GPIO_name                     Pin_name                      
        {FMKIO_GPIO_PORT_A,             FMKIO_GPIO_PIN_14},   // FMKIO_INPUT_SIGDIG_1,
        {FMKIO_GPIO_PORT_A,             FMKIO_GPIO_PIN_15},   // FMKIO_INPUT_SIGDIG_2,
        {FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_15},   // FMKIO_INPUT_SIGDIG_3,
        {FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_14},   // FMKIO_INPUT_SIGDIG_4,
        {FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_2},    // FMKIO_INPUT_SIGDIG_5,
        {FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_3},    // FMKIO_INPUT_SIGDIG_6,
        {FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_4},    // FMKIO_INPUT_SIGDIG_7,
        {FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_5},    // FMKIO_INPUT_SIGDIG_8,
        {FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_11},   // FMKIO_INPUT_SIGDIG_9,
    };

    /**< Variable for bsp_Gpio_Pin, adc coonfig Analog input signal mapping */
    const t_sFMKIO_AnaAdcCfg c_InAnaSigBspMap_as[FMKIO_INPUT_SIGANA_NB] = {
        //GPIO_name                     Pin_name                      ADC_Used                      Adc_Channel                   
        {{FMKIO_GPIO_PORT_C,             FMKIO_GPIO_PIN_0},               FMKCDA_ADC_1,                  FMKCDA_ADC_CHANNEL_6}, // FMKIO_INPUT_SIGANA_1;
        {{FMKIO_GPIO_PORT_C,             FMKIO_GPIO_PIN_1},               FMKCDA_ADC_1,                  FMKCDA_ADC_CHANNEL_7}, // FMKIO_INPUT_SIGANA_2;
        {{FMKIO_GPIO_PORT_C,             FMKIO_GPIO_PIN_2},               FMKCDA_ADC_1,                  FMKCDA_ADC_CHANNEL_8}, // FMKIO_INPUT_SIGANA_3;
        {{FMKIO_GPIO_PORT_C,             FMKIO_GPIO_PIN_3},               FMKCDA_ADC_1,                  FMKCDA_ADC_CHANNEL_9}, // FMKIO_INPUT_SIGANA_4;
        {{FMKIO_GPIO_PORT_A,             FMKIO_GPIO_PIN_6},               FMKCDA_ADC_2,                  FMKCDA_ADC_CHANNEL_3}, // FMKIO_INPUT_SIGANA_5;
        {{FMKIO_GPIO_PORT_A,             FMKIO_GPIO_PIN_7},               FMKCDA_ADC_2,                  FMKCDA_ADC_CHANNEL_4}, // FMKIO_INPUT_SIGANA_6;
        {{FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_0},               FMKCDA_ADC_1,                  FMKCDA_ADC_CHANNEL_15},// FMKIO_INPUT_SIGANA_7;
        {{FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_1},               FMKCDA_ADC_1,                  FMKCDA_ADC_CHANNEL_12},// FMKIO_INPUT_SIGANA_8;
        {{FMKIO_GPIO_PORT_F,             FMKIO_GPIO_PIN_2},               FMKCDA_ADC_1,                  FMKCDA_ADC_CHANNEL_3}, // FMKIO_INPUT_SIGANA_9;
        {{FMKIO_GPIO_PORT_F,             FMKIO_GPIO_PIN_3},               FMKCDA_ADC_1,                  FMKCDA_ADC_CHANNEL_4}, // FMKIO_INPUT_SIGANA_10;
    };

    /**< Variable for bsp_Gpio_Pin frequency input signal mapping */
    const t_sFMKIO_BspTimerSigCfg c_InFreqSigBspMap_as[FMKIO_INPUT_SIGFREQ_NB] = {
        //GPIO_name                     Pin_name                      alternate function            Interrupt Line                
        {{FMKIO_GPIO_PORT_E,             FMKIO_GPIO_PIN_2},              GPIO_AF9_TIM15,                FMKCPU_INTERRUPT_LINE_IO_61},    // FMKIO_INPUT_SIGFREQ_1,
        {{FMKIO_GPIO_PORT_E,             FMKIO_GPIO_PIN_3},              GPIO_AF1_TIM16,                FMKCPU_INTERRUPT_LINE_IO_34},    // FMKIO_INPUT_SIGFREQ_2,
        {{FMKIO_GPIO_PORT_E,             FMKIO_GPIO_PIN_4},              GPIO_AF1_TIM17,                FMKCPU_INTERRUPT_LINE_IO_33},    // FMKIO_INPUT_SIGFREQ_3,
    };

    /**< Variable for bsp_Gpio_Pin frequency input signal mapping */
    const t_sFMKIO_BspEvntSigCfg c_InEvntSigBspMap_as[FMKIO_INPUT_SIGEVNT_NB] = {
        //GPIO_name                     Pin_name                      GPIO_IRQN                     
        {{FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_10},             FMKCPU_NVIC_EXTI15_10_IRQN},           // FMKIO_INPUT_SIGEVNT_1,
        {{FMKIO_GPIO_PORT_A,             FMKIO_GPIO_PIN_4},              FMKCPU_NVIC_EXTI4_IRQN},               // FMKIO_INPUT_SIGEVNT_2,
    };

    /**< Variable for bsp_Gpio_Pin Digital ouput signal mapping */
    const t_sFMKIO_BspSigCfg c_OutDigSigBspMap_as[FMKIO_OUTPUT_SIGDIG_NB] = {
        //GPIO_name                     Pin_name                      
        {FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_12},   // FMKIO_OUTPUT_SIGDIG_1,
        {FMKIO_GPIO_PORT_B,             FMKIO_GPIO_PIN_13},   // FMKIO_OUTPUT_SIGDIG_2,
        {FMKIO_GPIO_PORT_C,             FMKIO_GPIO_PIN_4},    // FMKIO_OUTPUT_SIGDIG_3,
        {FMKIO_GPIO_PORT_C,             FMKIO_GPIO_PIN_5},    // FMKIO_OUTPUT_SIGDIG_4,
        {FMKIO_GPIO_PORT_C,             FMKIO_GPIO_PIN_13},   // FMKIO_OUTPUT_SIGDIG_5,
        {FMKIO_GPIO_PORT_F,             FMKIO_GPIO_PIN_4},    // FMKIO_OUTPUT_SIGDIG_6,
        {FMKIO_GPIO_PORT_D,             FMKIO_GPIO_PIN_13},   // FMKIO_OUTPUT_SIGDIG_7,
        {FMKIO_GPIO_PORT_D,             FMKIO_GPIO_PIN_9},    // FMKIO_OUTPUT_SIGDIG_8,
        {FMKIO_GPIO_PORT_D,             FMKIO_GPIO_PIN_10},   // FMKIO_OUTPUT_SIGDIG_9,
    };

    /**< Variable for bsp_Gpio_Pin PWM output signal mapping */
    const t_sFMKIO_BspTimerSigCfg c_OutPwmSigBspMap_as[FMKIO_OUTPUT_SIGPWM_NB] = {
        //GPIO_name                     Pin_name                      alternate function            Interrupt Line                
        {{FMKIO_GPIO_PORT_C,             FMKIO_GPIO_PIN_7},              GPIO_AF2_TIM3,                 FMKCPU_INTERRUPT_LINE_IO_32},    // FMKIO_OUTPUT_SIGPWM_1,
        {{FMKIO_GPIO_PORT_C,             FMKIO_GPIO_PIN_6},              GPIO_AF2_TIM3,                 FMKCPU_INTERRUPT_LINE_IO_31},    // FMKIO_OUTPUT_SIGPWM_2,
        {{FMKIO_GPIO_PORT_F,             FMKIO_GPIO_PIN_12},             GPIO_AF2_TIM20,                FMKCPU_INTERRUPT_LINE_IO_71},    // FMKIO_OUTPUT_SIGPWM_3,
        {{FMKIO_GPIO_PORT_F,             FMKIO_GPIO_PIN_13},             GPIO_AF2_TIM20,                FMKCPU_INTERRUPT_LINE_IO_72},    // FMKIO_OUTPUT_SIGPWM_4,
        {{FMKIO_GPIO_PORT_F,             FMKIO_GPIO_PIN_14},             GPIO_AF2_TIM20,                FMKCPU_INTERRUPT_LINE_IO_73},    // FMKIO_OUTPUT_SIGPWM_5,
        {{FMKIO_GPIO_PORT_F,             FMKIO_GPIO_PIN_15},             GPIO_AF2_TIM20,                FMKCPU_INTERRUPT_LINE_IO_74},    // FMKIO_OUTPUT_SIGPWM_6,
        {{FMKIO_GPIO_PORT_F,             FMKIO_GPIO_PIN_6},              GPIO_AF6_TIM5,                 FMKCPU_INTERRUPT_LINE_IO_51},    // FMKIO_OUTPUT_SIGPWM_7,
        {{FMKIO_GPIO_PORT_F,             FMKIO_GPIO_PIN_7},              GPIO_AF6_TIM5,                 FMKCPU_INTERRUPT_LINE_IO_52},    // FMKIO_OUTPUT_SIGPWM_8,
    };

    /**< Variable for RxTx Reference for Can Node */
    const t_sFMKIO_RxTxComCfg c_FmkIo_CanSigCfg_as[FMKIO_COM_SIGNAL_CAN_NB] ={
        // Rx Gpio Port                        Rx Pin                       Tx Gpio Port                      Tx Pin                    Alternate Function
        {{FMKIO_GPIO_PORT_A,             FMKIO_GPIO_PIN_11},             {FMKIO_GPIO_PORT_A,             FMKIO_GPIO_PIN_12},             GPIO_AF9_FDCAN1}, // FMKIO_COM_SIGNAL_CAN_1
        {{FMKIO_GPIO_PORT_G,             FMKIO_GPIO_PIN_14},             {FMKIO_GPIO_PORT_G,             FMKIO_GPIO_PIN_15},             GPIO_AF9_FDCAN1}, // FMKIO_COM_SIGNAL_CAN_2
        {{FMKIO_GPIO_PORT_G,             FMKIO_GPIO_PIN_13},             {FMKIO_GPIO_PORT_G,             FMKIO_GPIO_PIN_12},             GPIO_AF9_FDCAN1}, // FMKIO_COM_SIGNAL_CAN_3
    };
    /**< Variable for RxTx Reference for Serial Line */
    const t_sFMKIO_RxTxComCfg c_FmkIo_SerialSigCfg_as[FMKIO_COM_SIGNAL_SERIAL_NB] ={
        // Rx Gpio Port                        Rx Pin                       Tx Gpio Port                      Tx Pin                    Alternate Function
        {{FMKIO_GPIO_PORT_A,             FMKIO_GPIO_PIN_3},              {FMKIO_GPIO_PORT_A,             FMKIO_GPIO_PIN_2},              GPIO_AF7_USART2}, // FMKIO_COM_SIGNAL_SERIAL_1
        {{FMKIO_GPIO_PORT_C,             FMKIO_GPIO_PIN_11},             {FMKIO_GPIO_PORT_C,             FMKIO_GPIO_PIN_10},             GPIO_AF5_UART4}, // FMKIO_COM_SIGNAL_SERIAL_2
    };
    /* CAUTION : Automatic generated code section for Variable: End */

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKIO_CONFIGPRIVATE_H_INCLUDED           
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
