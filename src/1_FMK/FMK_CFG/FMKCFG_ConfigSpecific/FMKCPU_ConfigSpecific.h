/*********************************************************************
 * @file        FMKCPU_ConfigSpecific.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKPU_CONFIGSPECIFIC_H_INCLUDED
#define FMKPU_CONFIGSPECIFIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "FMK_CFG/FMKCFG_ConfigFiles/FMKCPU_ConfigPublic.h"
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
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
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    


    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    /**
    *
    *	@brief    Get the Prescaler and ARR value For Timer Configured in PWM.\n
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_MeasTrigger_e        : trigger for interruption, value from @ref t_eFMKCPU_ChnlMeasTrigger
    *	@param[in]  f_ITChannel_cb         : call back function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_RESULT              @ref RC_ERROR_WRONG_RESULT
    */
    t_eReturnCode FMKCPU_GetPwmTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32 f_PwmFreq_f32,
                                                t_uint32 * f_bspTimARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32);
    /**
    *
    *	@brief    Get the Prescaler and ARR value For Timer Configured in Input Compar.\n
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_MeasTrigger_e        : trigger for interruption, value from @ref t_eFMKCPU_ChnlMeasTrigger
    *	@param[in]  f_ITChannel_cb         : call back function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_RESULT              @ref RC_ERROR_WRONG_RESULT
    */
    t_eReturnCode FMKCPU_GetICTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32   f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspTimARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32);
    /**
    *
    *	@brief    Get the Prescaler and ARR value For Timer Configured in Output Compare.\n
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_MeasTrigger_e        : trigger for interruption, value from @ref t_eFMKCPU_ChnlMeasTrigger
    *	@param[in]  f_ITChannel_cb         : call back function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_RESULT              @ref RC_ERROR_WRONG_RESULT
    */
    t_eReturnCode FMKCPU_GetOCTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32   f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspTimARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32);

    /**
    *
    *	@brief    Get the Prescaler and ARR value For Timer Configured in OP.\n
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_MeasTrigger_e        : trigger for interruption, value from @ref t_eFMKCPU_ChnlMeasTrigger
    *	@param[in]  f_ITChannel_cb         : call back function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_RESULT              @ref RC_ERROR_WRONG_RESULT
    */
    t_eReturnCode FMKCPU_GetOPTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32   f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32);
    /**
    *
    *	@brief    Get the Prescaler and ARR value For Timer Configured in Event.\n
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_MeasTrigger_e        : trigger for interruption, value from @ref t_eFMKCPU_ChnlMeasTrigger
    *	@param[in]  f_ITChannel_cb         : call back function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_RESULT              @ref RC_ERROR_WRONG_RESULT
    */
    t_eReturnCode FMKCPU_GetEvntTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32 f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32);
    /**
    *
    *	@brief    Get the Prescaler and ARR value For Timer Configured in Encoder.\n
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_MeasTrigger_e        : trigger for interruption, value from @ref t_eFMKCPU_ChnlMeasTrigger
    *	@param[in]  f_ITChannel_cb         : call back function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_RESULT              @ref RC_ERROR_WRONG_RESULT
    */
    t_eReturnCode FMKCPU_GetECDRTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32 f_EcdrFreq_f32,
                                                t_uint32 * f_bspARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32);
    /**
    *
    *	@brief    Get the Prescaler and ARR value For Timer Configured in Dac.\n
    *
    *	@param[in]  f_InterruptLine_e      : enum value for Interrupt Line, value from @ref t_eFMKCPU_InterruptLineIO
    *	@param[in]  f_MeasTrigger_e        : trigger for interruption, value from @ref t_eFMKCPU_ChnlMeasTrigger
    *	@param[in]  f_ITChannel_cb         : call back function to call
    *
    *  @retval RC_OK                             @ref RC_OK
    *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *  @retval RC_ERROR_WRONG_RESULT              @ref RC_ERROR_WRONG_RESULT
    */
    t_eReturnCode FMKCPU_GetDacTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32 f_DacFreq_f32,
                                                t_uint32 * f_bspARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32);

    /* CAUTION : Automatic generated code section for Enable Clk Declaration: Start */
    /**< Function to enable  DMA1 rcc clock*/
    void FMKCPU_Enable_DMA1_Clock(void);
    /**< Function to enable  DMA2 rcc clock*/
    void FMKCPU_Enable_DMA2_Clock(void);
    /**< Function to enable  DMAMUX1 rcc clock*/
    void FMKCPU_Enable_DMAMUX1_Clock(void);
    /**< Function to enable  CORDIC rcc clock*/
    void FMKCPU_Enable_CORDIC_Clock(void);
    /**< Function to enable  FMAC rcc clock*/
    void FMKCPU_Enable_FMAC_Clock(void);
    /**< Function to enable  FLASH rcc clock*/
    void FMKCPU_Enable_FLASH_Clock(void);
    /**< Function to enable  CRC rcc clock*/
    void FMKCPU_Enable_CRC_Clock(void);
    /**< Function to enable  GPIOG rcc clock*/
    void FMKCPU_Enable_GPIOG_Clock(void);
    /**< Function to enable  GPIOF rcc clock*/
    void FMKCPU_Enable_GPIOF_Clock(void);
    /**< Function to enable  GPIOE rcc clock*/
    void FMKCPU_Enable_GPIOE_Clock(void);
    /**< Function to enable  GPIOD rcc clock*/
    void FMKCPU_Enable_GPIOD_Clock(void);
    /**< Function to enable  GPIOC rcc clock*/
    void FMKCPU_Enable_GPIOC_Clock(void);
    /**< Function to enable  GPIOB rcc clock*/
    void FMKCPU_Enable_GPIOB_Clock(void);
    /**< Function to enable  GPIOA rcc clock*/
    void FMKCPU_Enable_GPIOA_Clock(void);
    /**< Function to enable  ADC12 rcc clock*/
    void FMKCPU_Enable_ADC12_Clock(void);
    /**< Function to enable  ADC345 rcc clock*/
    void FMKCPU_Enable_ADC345_Clock(void);
    /**< Function to enable  DAC1 rcc clock*/
    void FMKCPU_Enable_DAC1_Clock(void);
    /**< Function to enable  DAC2 rcc clock*/
    void FMKCPU_Enable_DAC2_Clock(void);
    /**< Function to enable  DAC3 rcc clock*/
    void FMKCPU_Enable_DAC3_Clock(void);
    /**< Function to enable  DAC4 rcc clock*/
    void FMKCPU_Enable_DAC4_Clock(void);
    /**< Function to enable  RNG rcc clock*/
    void FMKCPU_Enable_RNG_Clock(void);
    /**< Function to enable  FMC rcc clock*/
    void FMKCPU_Enable_FMC_Clock(void);
    /**< Function to enable  QSPI rcc clock*/
    void FMKCPU_Enable_QSPI_Clock(void);
    /**< Function to enable  TIM2 rcc clock*/
    void FMKCPU_Enable_TIM2_Clock(void);
    /**< Function to enable  TIM3 rcc clock*/
    void FMKCPU_Enable_TIM3_Clock(void);
    /**< Function to enable  TIM4 rcc clock*/
    void FMKCPU_Enable_TIM4_Clock(void);
    /**< Function to enable  TIM5 rcc clock*/
    void FMKCPU_Enable_TIM5_Clock(void);
    /**< Function to enable  TIM6 rcc clock*/
    void FMKCPU_Enable_TIM6_Clock(void);
    /**< Function to enable  TIM7 rcc clock*/
    void FMKCPU_Enable_TIM7_Clock(void);
    /**< Function to enable  CRS rcc clock*/
    void FMKCPU_Enable_CRS_Clock(void);
    /**< Function to enable  RTCAPB rcc clock*/
    void FMKCPU_Enable_RTCAPB_Clock(void);
    /**< Function to enable  WWDG rcc clock*/
    void FMKCPU_Enable_WWDG_Clock(void);
    /**< Function to enable  SPI2 rcc clock*/
    void FMKCPU_Enable_SPI2_Clock(void);
    /**< Function to enable  SPI3 rcc clock*/
    void FMKCPU_Enable_SPI3_Clock(void);
    /**< Function to enable  USART2 rcc clock*/
    void FMKCPU_Enable_USART2_Clock(void);
    /**< Function to enable  USART3 rcc clock*/
    void FMKCPU_Enable_USART3_Clock(void);
    /**< Function to enable  UART4 rcc clock*/
    void FMKCPU_Enable_UART4_Clock(void);
    /**< Function to enable  UART5 rcc clock*/
    void FMKCPU_Enable_UART5_Clock(void);
    /**< Function to enable  I2C2 rcc clock*/
    void FMKCPU_Enable_I2C2_Clock(void);
    /**< Function to enable  USB rcc clock*/
    void FMKCPU_Enable_USB_Clock(void);
    /**< Function to enable  FDCAN rcc clock*/
    void FMKCPU_Enable_FDCAN_Clock(void);
    /**< Function to enable  PWR rcc clock*/
    void FMKCPU_Enable_PWR_Clock(void);
    /**< Function to enable  I2C3 rcc clock*/
    void FMKCPU_Enable_I2C3_Clock(void);
    /**< Function to enable  LPTIM1 rcc clock*/
    void FMKCPU_Enable_LPTIM1_Clock(void);
    /**< Function to enable  UCPD1 rcc clock*/
    void FMKCPU_Enable_UCPD1_Clock(void);
    /**< Function to enable  SYSCFG rcc clock*/
    void FMKCPU_Enable_SYSCFG_Clock(void);
    /**< Function to enable  TIM1 rcc clock*/
    void FMKCPU_Enable_TIM1_Clock(void);
    /**< Function to enable  SPI1 rcc clock*/
    void FMKCPU_Enable_SPI1_Clock(void);
    /**< Function to enable  TIM8 rcc clock*/
    void FMKCPU_Enable_TIM8_Clock(void);
    /**< Function to enable  USART1 rcc clock*/
    void FMKCPU_Enable_USART1_Clock(void);
    /**< Function to enable  SPI4 rcc clock*/
    void FMKCPU_Enable_SPI4_Clock(void);
    /**< Function to enable  TIM15 rcc clock*/
    void FMKCPU_Enable_TIM15_Clock(void);
    /**< Function to enable  TIM16 rcc clock*/
    void FMKCPU_Enable_TIM16_Clock(void);
    /**< Function to enable  TIM17 rcc clock*/
    void FMKCPU_Enable_TIM17_Clock(void);
    /**< Function to enable  TIM20 rcc clock*/
    void FMKCPU_Enable_TIM20_Clock(void);
    /**< Function to enable  SAI1 rcc clock*/
    void FMKCPU_Enable_SAI1_Clock(void);
    /**< Function to enable  HRTIM1 rcc clock*/
    void FMKCPU_Enable_HRTIM1_Clock(void);
    /* CAUTION : Automatic generated code section for Enable Clk Declaration: End */

    /* CAUTION : Automatic generated code section for Disable Clk Declaration: Start */
    /**< Function to disable DMA1 rcc clock*/
    void FMKCPU_Disable_DMA1_Clock(void);
    /**< Function to disable DMA2 rcc clock*/
    void FMKCPU_Disable_DMA2_Clock(void);
    /**< Function to disable DMAMUX1 rcc clock*/
    void FMKCPU_Disable_DMAMUX1_Clock(void);
    /**< Function to disable CORDIC rcc clock*/
    void FMKCPU_Disable_CORDIC_Clock(void);
    /**< Function to disable FMAC rcc clock*/
    void FMKCPU_Disable_FMAC_Clock(void);
    /**< Function to disable FLASH rcc clock*/
    void FMKCPU_Disable_FLASH_Clock(void);
    /**< Function to disable CRC rcc clock*/
    void FMKCPU_Disable_CRC_Clock(void);
    /**< Function to disable GPIOG rcc clock*/
    void FMKCPU_Disable_GPIOG_Clock(void);
    /**< Function to disable GPIOF rcc clock*/
    void FMKCPU_Disable_GPIOF_Clock(void);
    /**< Function to disable GPIOE rcc clock*/
    void FMKCPU_Disable_GPIOE_Clock(void);
    /**< Function to disable GPIOD rcc clock*/
    void FMKCPU_Disable_GPIOD_Clock(void);
    /**< Function to disable GPIOC rcc clock*/
    void FMKCPU_Disable_GPIOC_Clock(void);
    /**< Function to disable GPIOB rcc clock*/
    void FMKCPU_Disable_GPIOB_Clock(void);
    /**< Function to disable GPIOA rcc clock*/
    void FMKCPU_Disable_GPIOA_Clock(void);
    /**< Function to disable ADC12 rcc clock*/
    void FMKCPU_Disable_ADC12_Clock(void);
    /**< Function to disable ADC345 rcc clock*/
    void FMKCPU_Disable_ADC345_Clock(void);
    /**< Function to disable DAC1 rcc clock*/
    void FMKCPU_Disable_DAC1_Clock(void);
    /**< Function to disable DAC2 rcc clock*/
    void FMKCPU_Disable_DAC2_Clock(void);
    /**< Function to disable DAC3 rcc clock*/
    void FMKCPU_Disable_DAC3_Clock(void);
    /**< Function to disable DAC4 rcc clock*/
    void FMKCPU_Disable_DAC4_Clock(void);
    /**< Function to disable RNG rcc clock*/
    void FMKCPU_Disable_RNG_Clock(void);
    /**< Function to disable FMC rcc clock*/
    void FMKCPU_Disable_FMC_Clock(void);
    /**< Function to disable QSPI rcc clock*/
    void FMKCPU_Disable_QSPI_Clock(void);
    /**< Function to disable TIM2 rcc clock*/
    void FMKCPU_Disable_TIM2_Clock(void);
    /**< Function to disable TIM3 rcc clock*/
    void FMKCPU_Disable_TIM3_Clock(void);
    /**< Function to disable TIM4 rcc clock*/
    void FMKCPU_Disable_TIM4_Clock(void);
    /**< Function to disable TIM5 rcc clock*/
    void FMKCPU_Disable_TIM5_Clock(void);
    /**< Function to disable TIM6 rcc clock*/
    void FMKCPU_Disable_TIM6_Clock(void);
    /**< Function to disable TIM7 rcc clock*/
    void FMKCPU_Disable_TIM7_Clock(void);
    /**< Function to disable CRS rcc clock*/
    void FMKCPU_Disable_CRS_Clock(void);
    /**< Function to disable RTCAPB rcc clock*/
    void FMKCPU_Disable_RTCAPB_Clock(void);
    /**< Function to disable WWDG rcc clock*/
    void FMKCPU_Disable_WWDG_Clock(void);
    /**< Function to disable SPI2 rcc clock*/
    void FMKCPU_Disable_SPI2_Clock(void);
    /**< Function to disable SPI3 rcc clock*/
    void FMKCPU_Disable_SPI3_Clock(void);
    /**< Function to disable USART2 rcc clock*/
    void FMKCPU_Disable_USART2_Clock(void);
    /**< Function to disable USART3 rcc clock*/
    void FMKCPU_Disable_USART3_Clock(void);
    /**< Function to disable UART4 rcc clock*/
    void FMKCPU_Disable_UART4_Clock(void);
    /**< Function to disable UART5 rcc clock*/
    void FMKCPU_Disable_UART5_Clock(void);
    /**< Function to disable I2C2 rcc clock*/
    void FMKCPU_Disable_I2C2_Clock(void);
    /**< Function to disable USB rcc clock*/
    void FMKCPU_Disable_USB_Clock(void);
    /**< Function to disable FDCAN rcc clock*/
    void FMKCPU_Disable_FDCAN_Clock(void);
    /**< Function to disable PWR rcc clock*/
    void FMKCPU_Disable_PWR_Clock(void);
    /**< Function to disable I2C3 rcc clock*/
    void FMKCPU_Disable_I2C3_Clock(void);
    /**< Function to disable LPTIM1 rcc clock*/
    void FMKCPU_Disable_LPTIM1_Clock(void);
    /**< Function to disable UCPD1 rcc clock*/
    void FMKCPU_Disable_UCPD1_Clock(void);
    /**< Function to disable SYSCFG rcc clock*/
    void FMKCPU_Disable_SYSCFG_Clock(void);
    /**< Function to disable TIM1 rcc clock*/
    void FMKCPU_Disable_TIM1_Clock(void);
    /**< Function to disable SPI1 rcc clock*/
    void FMKCPU_Disable_SPI1_Clock(void);
    /**< Function to disable TIM8 rcc clock*/
    void FMKCPU_Disable_TIM8_Clock(void);
    /**< Function to disable USART1 rcc clock*/
    void FMKCPU_Disable_USART1_Clock(void);
    /**< Function to disable SPI4 rcc clock*/
    void FMKCPU_Disable_SPI4_Clock(void);
    /**< Function to disable TIM15 rcc clock*/
    void FMKCPU_Disable_TIM15_Clock(void);
    /**< Function to disable TIM16 rcc clock*/
    void FMKCPU_Disable_TIM16_Clock(void);
    /**< Function to disable TIM17 rcc clock*/
    void FMKCPU_Disable_TIM17_Clock(void);
    /**< Function to disable TIM20 rcc clock*/
    void FMKCPU_Disable_TIM20_Clock(void);
    /**< Function to disable SAI1 rcc clock*/
    void FMKCPU_Disable_SAI1_Clock(void);
    /**< Function to disable HRTIM1 rcc clock*/
    void FMKCPU_Disable_HRTIM1_Clock(void);
    /* CAUTION : Automatic generated code section for Disable Clk Declaration: End */

/**< This function has been made to filled in c_FMKCPU_TimerFunc_apf */
HAL_StatusTypeDef FMKCPU_HAL_TIM_Base_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef FMKCPU_HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef FMKCPU_HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef FMKCPU_HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
#endif // FMKPU_CONFIGSPECIFIC_H_INCLUDED           
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
