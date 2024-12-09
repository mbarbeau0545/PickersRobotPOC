/*********************************************************************
 * @file        FMKCPU_ConfigSpecific.c
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
#include "FMKCPU_ConfigSpecific.h"

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
//                      Local functions - Prototypes
//********************************************************************************

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Enable Clk Implementation: Start */
/**< Function to enable DMA1 rcc clock*/
void FMKCPU_Enable_DMA1_Clock(void) {__HAL_RCC_DMA1_CLK_ENABLE();}
/**< Function to enable DMA2 rcc clock*/
void FMKCPU_Enable_DMA2_Clock(void) {__HAL_RCC_DMA2_CLK_ENABLE();}
/**< Function to enable DMAMUX1 rcc clock*/
void FMKCPU_Enable_DMAMUX1_Clock(void) {__HAL_RCC_DMAMUX1_CLK_ENABLE();}
/**< Function to enable CORDIC rcc clock*/
void FMKCPU_Enable_CORDIC_Clock(void) {__HAL_RCC_CORDIC_CLK_ENABLE();}
/**< Function to enable FMAC rcc clock*/
void FMKCPU_Enable_FMAC_Clock(void) {__HAL_RCC_FMAC_CLK_ENABLE();}
/**< Function to enable FLASH rcc clock*/
void FMKCPU_Enable_FLASH_Clock(void) {__HAL_RCC_FLASH_CLK_ENABLE();}
/**< Function to enable CRC rcc clock*/
void FMKCPU_Enable_CRC_Clock(void) {__HAL_RCC_CRC_CLK_ENABLE();}
/**< Function to enable GPIOG rcc clock*/
void FMKCPU_Enable_GPIOG_Clock(void) {__HAL_RCC_GPIOG_CLK_ENABLE();}
/**< Function to enable GPIOF rcc clock*/
void FMKCPU_Enable_GPIOF_Clock(void) {__HAL_RCC_GPIOF_CLK_ENABLE();}
/**< Function to enable GPIOE rcc clock*/
void FMKCPU_Enable_GPIOE_Clock(void) {__HAL_RCC_GPIOE_CLK_ENABLE();}
/**< Function to enable GPIOD rcc clock*/
void FMKCPU_Enable_GPIOD_Clock(void) {__HAL_RCC_GPIOD_CLK_ENABLE();}
/**< Function to enable GPIOC rcc clock*/
void FMKCPU_Enable_GPIOC_Clock(void) {__HAL_RCC_GPIOC_CLK_ENABLE();}
/**< Function to enable GPIOB rcc clock*/
void FMKCPU_Enable_GPIOB_Clock(void) {__HAL_RCC_GPIOB_CLK_ENABLE();}
/**< Function to enable GPIOA rcc clock*/
void FMKCPU_Enable_GPIOA_Clock(void) {__HAL_RCC_GPIOA_CLK_ENABLE();}
/**< Function to enable ADC12 rcc clock*/
void FMKCPU_Enable_ADC12_Clock(void) {__HAL_RCC_ADC12_CLK_ENABLE();}
/**< Function to enable ADC345 rcc clock*/
void FMKCPU_Enable_ADC345_Clock(void) {__HAL_RCC_ADC345_CLK_ENABLE();}
/**< Function to enable DAC1 rcc clock*/
void FMKCPU_Enable_DAC1_Clock(void) {__HAL_RCC_DAC1_CLK_ENABLE();}
/**< Function to enable DAC2 rcc clock*/
void FMKCPU_Enable_DAC2_Clock(void) {__HAL_RCC_DAC2_CLK_ENABLE();}
/**< Function to enable DAC3 rcc clock*/
void FMKCPU_Enable_DAC3_Clock(void) {__HAL_RCC_DAC3_CLK_ENABLE();}
/**< Function to enable DAC4 rcc clock*/
void FMKCPU_Enable_DAC4_Clock(void) {__HAL_RCC_DAC4_CLK_ENABLE();}
/**< Function to enable RNG rcc clock*/
void FMKCPU_Enable_RNG_Clock(void) {__HAL_RCC_RNG_CLK_ENABLE();}
/**< Function to enable FMC rcc clock*/
void FMKCPU_Enable_FMC_Clock(void) {__HAL_RCC_FMC_CLK_ENABLE();}
/**< Function to enable QSPI rcc clock*/
void FMKCPU_Enable_QSPI_Clock(void) {__HAL_RCC_QSPI_CLK_ENABLE();}
/**< Function to enable TIM2 rcc clock*/
void FMKCPU_Enable_TIM2_Clock(void) {__HAL_RCC_TIM2_CLK_ENABLE();}
/**< Function to enable TIM3 rcc clock*/
void FMKCPU_Enable_TIM3_Clock(void) {__HAL_RCC_TIM3_CLK_ENABLE();}
/**< Function to enable TIM4 rcc clock*/
void FMKCPU_Enable_TIM4_Clock(void) {__HAL_RCC_TIM4_CLK_ENABLE();}
/**< Function to enable TIM5 rcc clock*/
void FMKCPU_Enable_TIM5_Clock(void) {__HAL_RCC_TIM5_CLK_ENABLE();}
/**< Function to enable TIM6 rcc clock*/
void FMKCPU_Enable_TIM6_Clock(void) {__HAL_RCC_TIM6_CLK_ENABLE();}
/**< Function to enable TIM7 rcc clock*/
void FMKCPU_Enable_TIM7_Clock(void) {__HAL_RCC_TIM7_CLK_ENABLE();}
/**< Function to enable CRS rcc clock*/
void FMKCPU_Enable_CRS_Clock(void) {__HAL_RCC_CRS_CLK_ENABLE();}
/**< Function to enable RTCAPB rcc clock*/
void FMKCPU_Enable_RTCAPB_Clock(void) {__HAL_RCC_RTCAPB_CLK_ENABLE();}
/**< Function to enable WWDG rcc clock*/
void FMKCPU_Enable_WWDG_Clock(void) {__HAL_RCC_WWDG_CLK_ENABLE();}
/**< Function to enable SPI2 rcc clock*/
void FMKCPU_Enable_SPI2_Clock(void) {__HAL_RCC_SPI2_CLK_ENABLE();}
/**< Function to enable SPI3 rcc clock*/
void FMKCPU_Enable_SPI3_Clock(void) {__HAL_RCC_SPI3_CLK_ENABLE();}
/**< Function to enable USART2 rcc clock*/
void FMKCPU_Enable_USART2_Clock(void) {__HAL_RCC_USART2_CLK_ENABLE();}
/**< Function to enable USART3 rcc clock*/
void FMKCPU_Enable_USART3_Clock(void) {__HAL_RCC_USART3_CLK_ENABLE();}
/**< Function to enable UART4 rcc clock*/
void FMKCPU_Enable_UART4_Clock(void) {__HAL_RCC_UART4_CLK_ENABLE();}
/**< Function to enable UART5 rcc clock*/
void FMKCPU_Enable_UART5_Clock(void) {__HAL_RCC_UART5_CLK_ENABLE();}
/**< Function to enable I2C2 rcc clock*/
void FMKCPU_Enable_I2C2_Clock(void) {__HAL_RCC_I2C2_CLK_ENABLE();}
/**< Function to enable USB rcc clock*/
void FMKCPU_Enable_USB_Clock(void) {__HAL_RCC_USB_CLK_ENABLE();}
/**< Function to enable FDCAN rcc clock*/
void FMKCPU_Enable_FDCAN_Clock(void) {__HAL_RCC_FDCAN_CLK_ENABLE();}
/**< Function to enable PWR rcc clock*/
void FMKCPU_Enable_PWR_Clock(void) {__HAL_RCC_PWR_CLK_ENABLE();}
/**< Function to enable I2C3 rcc clock*/
void FMKCPU_Enable_I2C3_Clock(void) {__HAL_RCC_I2C3_CLK_ENABLE();}
/**< Function to enable LPTIM1 rcc clock*/
void FMKCPU_Enable_LPTIM1_Clock(void) {__HAL_RCC_LPTIM1_CLK_ENABLE();}
/**< Function to enable UCPD1 rcc clock*/
void FMKCPU_Enable_UCPD1_Clock(void) {__HAL_RCC_UCPD1_CLK_ENABLE();}
/**< Function to enable SYSCFG rcc clock*/
void FMKCPU_Enable_SYSCFG_Clock(void) {__HAL_RCC_SYSCFG_CLK_ENABLE();}
/**< Function to enable TIM1 rcc clock*/
void FMKCPU_Enable_TIM1_Clock(void) {__HAL_RCC_TIM1_CLK_ENABLE();}
/**< Function to enable SPI1 rcc clock*/
void FMKCPU_Enable_SPI1_Clock(void) {__HAL_RCC_SPI1_CLK_ENABLE();}
/**< Function to enable TIM8 rcc clock*/
void FMKCPU_Enable_TIM8_Clock(void) {__HAL_RCC_TIM8_CLK_ENABLE();}
/**< Function to enable USART1 rcc clock*/
void FMKCPU_Enable_USART1_Clock(void) {__HAL_RCC_USART1_CLK_ENABLE();}
/**< Function to enable SPI4 rcc clock*/
void FMKCPU_Enable_SPI4_Clock(void) {__HAL_RCC_SPI4_CLK_ENABLE();}
/**< Function to enable TIM15 rcc clock*/
void FMKCPU_Enable_TIM15_Clock(void) {__HAL_RCC_TIM15_CLK_ENABLE();}
/**< Function to enable TIM16 rcc clock*/
void FMKCPU_Enable_TIM16_Clock(void) {__HAL_RCC_TIM16_CLK_ENABLE();}
/**< Function to enable TIM17 rcc clock*/
void FMKCPU_Enable_TIM17_Clock(void) {__HAL_RCC_TIM17_CLK_ENABLE();}
/**< Function to enable TIM20 rcc clock*/
void FMKCPU_Enable_TIM20_Clock(void) {__HAL_RCC_TIM20_CLK_ENABLE();}
/**< Function to enable SAI1 rcc clock*/
void FMKCPU_Enable_SAI1_Clock(void) {__HAL_RCC_SAI1_CLK_ENABLE();}
/**< Function to enable HRTIM1 rcc clock*/
void FMKCPU_Enable_HRTIM1_Clock(void) {__HAL_RCC_HRTIM1_CLK_ENABLE();}
/* CAUTION : Automatic generated code section for Enable Clk Implementation: End */

/* CAUTION : Automatic generated code section for Disable Clk Implementation: Start */
/**< Function to disable DMA1 rcc clock*/
void FMKCPU_Disable_DMA1_Clock(void) {__HAL_RCC_DMA1_CLK_DISABLE();}
/**< Function to disable DMA2 rcc clock*/
void FMKCPU_Disable_DMA2_Clock(void) {__HAL_RCC_DMA2_CLK_DISABLE();}
/**< Function to disable DMAMUX1 rcc clock*/
void FMKCPU_Disable_DMAMUX1_Clock(void) {__HAL_RCC_DMAMUX1_CLK_DISABLE();}
/**< Function to disable CORDIC rcc clock*/
void FMKCPU_Disable_CORDIC_Clock(void) {__HAL_RCC_CORDIC_CLK_DISABLE();}
/**< Function to disable FMAC rcc clock*/
void FMKCPU_Disable_FMAC_Clock(void) {__HAL_RCC_FMAC_CLK_DISABLE();}
/**< Function to disable FLASH rcc clock*/
void FMKCPU_Disable_FLASH_Clock(void) {__HAL_RCC_FLASH_CLK_DISABLE();}
/**< Function to disable CRC rcc clock*/
void FMKCPU_Disable_CRC_Clock(void) {__HAL_RCC_CRC_CLK_DISABLE();}
/**< Function to disable GPIOG rcc clock*/
void FMKCPU_Disable_GPIOG_Clock(void) {__HAL_RCC_GPIOG_CLK_DISABLE();}
/**< Function to disable GPIOF rcc clock*/
void FMKCPU_Disable_GPIOF_Clock(void) {__HAL_RCC_GPIOF_CLK_DISABLE();}
/**< Function to disable GPIOE rcc clock*/
void FMKCPU_Disable_GPIOE_Clock(void) {__HAL_RCC_GPIOE_CLK_DISABLE();}
/**< Function to disable GPIOD rcc clock*/
void FMKCPU_Disable_GPIOD_Clock(void) {__HAL_RCC_GPIOD_CLK_DISABLE();}
/**< Function to disable GPIOC rcc clock*/
void FMKCPU_Disable_GPIOC_Clock(void) {__HAL_RCC_GPIOC_CLK_DISABLE();}
/**< Function to disable GPIOB rcc clock*/
void FMKCPU_Disable_GPIOB_Clock(void) {__HAL_RCC_GPIOB_CLK_DISABLE();}
/**< Function to disable GPIOA rcc clock*/
void FMKCPU_Disable_GPIOA_Clock(void) {__HAL_RCC_GPIOA_CLK_DISABLE();}
/**< Function to disable ADC12 rcc clock*/
void FMKCPU_Disable_ADC12_Clock(void) {__HAL_RCC_ADC12_CLK_DISABLE();}
/**< Function to disable ADC345 rcc clock*/
void FMKCPU_Disable_ADC345_Clock(void) {__HAL_RCC_ADC345_CLK_DISABLE();}
/**< Function to disable DAC1 rcc clock*/
void FMKCPU_Disable_DAC1_Clock(void) {__HAL_RCC_DAC1_CLK_DISABLE();}
/**< Function to disable DAC2 rcc clock*/
void FMKCPU_Disable_DAC2_Clock(void) {__HAL_RCC_DAC2_CLK_DISABLE();}
/**< Function to disable DAC3 rcc clock*/
void FMKCPU_Disable_DAC3_Clock(void) {__HAL_RCC_DAC3_CLK_DISABLE();}
/**< Function to disable DAC4 rcc clock*/
void FMKCPU_Disable_DAC4_Clock(void) {__HAL_RCC_DAC4_CLK_DISABLE();}
/**< Function to disable RNG rcc clock*/
void FMKCPU_Disable_RNG_Clock(void) {__HAL_RCC_RNG_CLK_DISABLE();}
/**< Function to disable FMC rcc clock*/
void FMKCPU_Disable_FMC_Clock(void) {__HAL_RCC_FMC_CLK_DISABLE();}
/**< Function to disable QSPI rcc clock*/
void FMKCPU_Disable_QSPI_Clock(void) {__HAL_RCC_QSPI_CLK_DISABLE();}
/**< Function to disable TIM2 rcc clock*/
void FMKCPU_Disable_TIM2_Clock(void) {__HAL_RCC_TIM2_CLK_DISABLE();}
/**< Function to disable TIM3 rcc clock*/
void FMKCPU_Disable_TIM3_Clock(void) {__HAL_RCC_TIM3_CLK_DISABLE();}
/**< Function to disable TIM4 rcc clock*/
void FMKCPU_Disable_TIM4_Clock(void) {__HAL_RCC_TIM4_CLK_DISABLE();}
/**< Function to disable TIM5 rcc clock*/
void FMKCPU_Disable_TIM5_Clock(void) {__HAL_RCC_TIM5_CLK_DISABLE();}
/**< Function to disable TIM6 rcc clock*/
void FMKCPU_Disable_TIM6_Clock(void) {__HAL_RCC_TIM6_CLK_DISABLE();}
/**< Function to disable TIM7 rcc clock*/
void FMKCPU_Disable_TIM7_Clock(void) {__HAL_RCC_TIM7_CLK_DISABLE();}
/**< Function to disable CRS rcc clock*/
void FMKCPU_Disable_CRS_Clock(void) {__HAL_RCC_CRS_CLK_DISABLE();}
/**< Function to disable RTCAPB rcc clock*/
void FMKCPU_Disable_RTCAPB_Clock(void) {__HAL_RCC_RTCAPB_CLK_DISABLE();}
/**< Function to disable WWDG rcc clock*/
void FMKCPU_Disable_WWDG_Clock(void) {__HAL_RCC_WWDG_CLK_DISABLE();}
/**< Function to disable SPI2 rcc clock*/
void FMKCPU_Disable_SPI2_Clock(void) {__HAL_RCC_SPI2_CLK_DISABLE();}
/**< Function to disable SPI3 rcc clock*/
void FMKCPU_Disable_SPI3_Clock(void) {__HAL_RCC_SPI3_CLK_DISABLE();}
/**< Function to disable USART2 rcc clock*/
void FMKCPU_Disable_USART2_Clock(void) {__HAL_RCC_USART2_CLK_DISABLE();}
/**< Function to disable USART3 rcc clock*/
void FMKCPU_Disable_USART3_Clock(void) {__HAL_RCC_USART3_CLK_DISABLE();}
/**< Function to disable UART4 rcc clock*/
void FMKCPU_Disable_UART4_Clock(void) {__HAL_RCC_UART4_CLK_DISABLE();}
/**< Function to disable UART5 rcc clock*/
void FMKCPU_Disable_UART5_Clock(void) {__HAL_RCC_UART5_CLK_DISABLE();}
/**< Function to disable I2C2 rcc clock*/
void FMKCPU_Disable_I2C2_Clock(void) {__HAL_RCC_I2C2_CLK_DISABLE();}
/**< Function to disable USB rcc clock*/
void FMKCPU_Disable_USB_Clock(void) {__HAL_RCC_USB_CLK_DISABLE();}
/**< Function to disable FDCAN rcc clock*/
void FMKCPU_Disable_FDCAN_Clock(void) {__HAL_RCC_FDCAN_CLK_DISABLE();}
/**< Function to disable PWR rcc clock*/
void FMKCPU_Disable_PWR_Clock(void) {__HAL_RCC_PWR_CLK_DISABLE();}
/**< Function to disable I2C3 rcc clock*/
void FMKCPU_Disable_I2C3_Clock(void) {__HAL_RCC_I2C3_CLK_DISABLE();}
/**< Function to disable LPTIM1 rcc clock*/
void FMKCPU_Disable_LPTIM1_Clock(void) {__HAL_RCC_LPTIM1_CLK_DISABLE();}
/**< Function to disable UCPD1 rcc clock*/
void FMKCPU_Disable_UCPD1_Clock(void) {__HAL_RCC_UCPD1_CLK_DISABLE();}
/**< Function to disable SYSCFG rcc clock*/
void FMKCPU_Disable_SYSCFG_Clock(void) {__HAL_RCC_SYSCFG_CLK_DISABLE();}
/**< Function to disable TIM1 rcc clock*/
void FMKCPU_Disable_TIM1_Clock(void) {__HAL_RCC_TIM1_CLK_DISABLE();}
/**< Function to disable SPI1 rcc clock*/
void FMKCPU_Disable_SPI1_Clock(void) {__HAL_RCC_SPI1_CLK_DISABLE();}
/**< Function to disable TIM8 rcc clock*/
void FMKCPU_Disable_TIM8_Clock(void) {__HAL_RCC_TIM8_CLK_DISABLE();}
/**< Function to disable USART1 rcc clock*/
void FMKCPU_Disable_USART1_Clock(void) {__HAL_RCC_USART1_CLK_DISABLE();}
/**< Function to disable SPI4 rcc clock*/
void FMKCPU_Disable_SPI4_Clock(void) {__HAL_RCC_SPI4_CLK_DISABLE();}
/**< Function to disable TIM15 rcc clock*/
void FMKCPU_Disable_TIM15_Clock(void) {__HAL_RCC_TIM15_CLK_DISABLE();}
/**< Function to disable TIM16 rcc clock*/
void FMKCPU_Disable_TIM16_Clock(void) {__HAL_RCC_TIM16_CLK_DISABLE();}
/**< Function to disable TIM17 rcc clock*/
void FMKCPU_Disable_TIM17_Clock(void) {__HAL_RCC_TIM17_CLK_DISABLE();}
/**< Function to disable TIM20 rcc clock*/
void FMKCPU_Disable_TIM20_Clock(void) {__HAL_RCC_TIM20_CLK_DISABLE();}
/**< Function to disable SAI1 rcc clock*/
void FMKCPU_Disable_SAI1_Clock(void) {__HAL_RCC_SAI1_CLK_DISABLE();}
/**< Function to disable HRTIM1 rcc clock*/
void FMKCPU_Disable_HRTIM1_Clock(void) {__HAL_RCC_HRTIM1_CLK_DISABLE();}
/* CAUTION : Automatic generated code section for Disable Clk Implementation: End */

/**< This function has been made to filled in c_FMKCPU_bspTimFunc_apf */
HAL_StatusTypeDef FMKCPU_HAL_TIM_Base_Start(TIM_HandleTypeDef *htim, uint32_t Channel){UNUSED(Channel); return HAL_TIM_Base_Start(htim);}
HAL_StatusTypeDef FMKCPU_HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim, uint32_t Channel){UNUSED(Channel); return HAL_TIM_Base_Stop(htim);}
HAL_StatusTypeDef FMKCPU_HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel){UNUSED(Channel); return HAL_TIM_Base_Start_IT(htim);}
HAL_StatusTypeDef FMKCPU_HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel){UNUSED(Channel); return HAL_TIM_Base_Stop_IT(htim);}


//Function to Get the Prescaler of Adc Configuration from Adc frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForAdc(t_eFMKCPU_SysClkOsc f_AdcOscSrc_e,
                                            t_eFMKCPU_CoreClockSpeed * f_SysClockValues_pae,
                                            t_uint8 f_idxAdcRccClock_u8,
                                            t_uint32 * f_bspAdcPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_CoreClockSpeed OscAdcSrcValue_e;

    if((f_bspAdcPrescaler_pu32 == (t_uint32 *)NULL)
    || (f_SysClockValues_pae == (t_eFMKCPU_CoreClockSpeed *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if((f_idxAdcRccClock_u8 > FMKCPU_RCC_CLK_NB)
    || (f_AdcOscSrc_e > FMKCPU_SYS_CLOCK_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        OscAdcSrcValue_e = f_SysClockValues_pae[f_AdcOscSrc_e];

        if (OscAdcSrcValue_e < FMKCPU_CORE_CLOCK_SPEED_64MHZ)
        {
            *f_bspAdcPrescaler_pu32 = (t_uint8)ADC_CLOCK_ASYNC_DIV1;
        }
        else if((OscAdcSrcValue_e >= (t_uint8)FMKCPU_CORE_CLOCK_SPEED_64MHZ)  
           && (OscAdcSrcValue_e < (t_uint8)FMKCPU_CORE_CLOCK_SPEED_132MHZ))
        {
            *f_bspAdcPrescaler_pu32 = (t_uint32)ADC_CLOCK_ASYNC_DIV2 ;
        }
        else if(OscAdcSrcValue_e >= (t_uint8)FMKCPU_CORE_CLOCK_SPEED_132MHZ)
        {
            *f_bspAdcPrescaler_pu32 = (t_uint8)ADC_CLOCK_ASYNC_DIV4;
        }
        else 
        {
            *f_bspAdcPrescaler_pu32 = (t_uint32)0;
            Ret_e = RC_WARNING_NO_OPERATION;
        }
    }
    return Ret_e;
}
//Function to Get the Prescaler of Rng Configuration from Rng frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForRng(t_eFMKCPU_SysClkOsc f_RngOscSrc_e,
                                        t_uint8 f_RngOscValue_u8,
                                        t_uint8 f_idxRngRccClock_u8,
                                        t_uint32 * f_bspRngPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    
    return Ret_e;  
}
//Function to Get the Prescaler of Tim Configuration from Tim frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForTim(t_eFMKCPU_SysClkOsc f_TimOscSrc_e,
                                            t_eFMKCPU_CoreClockSpeed * f_SysClockValues_pae,
                                            t_uint8 f_idxTimRccClock_u8,
                                            t_uint32 * f_bspTimPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCPU_CoreClockSpeed OscTimSrcValue_e;

    if((f_bspTimPrescaler_pu32 == (t_uint32 *)NULL)
    || (f_SysClockValues_pae == (t_eFMKCPU_CoreClockSpeed *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if((f_idxTimRccClock_u8 > FMKCPU_RCC_CLK_NB)
    || (f_TimOscSrc_e > FMKCPU_SYS_CLOCK_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        // Timer depend on APB1 or APB2, if these clock were divided per 2 or more,
        // Hardware mutliply by 2 the core freqency of the timer
        // In other word
    }

    return Ret_e;  
}
//Function to Get the Prescaler of Usart Configuration from Usart frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForUsart(t_eFMKCPU_SysClkOsc f_UsartOscSrc_e,
                                        t_uint8 f_UsartOscValue_u8,
                                        t_uint8 f_idxUsartRccClock_u8,
                                        t_uint32 * f_bspUsartPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    return Ret_e;  
}
//Function to Get the Prescaler of Uart Configuration from Uart frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForUart(t_eFMKCPU_SysClkOsc f_UartOscSrc_e,
                                        t_uint8 f_UartOscValue_u8,
                                        t_uint8 f_idxUartRccClock_u8,
                                        t_uint32 * f_bspUartPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    return Ret_e;     
}
//Function to Get the Prescaler of I2c Configuration from I2c frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForI2c(t_eFMKCPU_SysClkOsc f_I2cOscSrc_e,
                                        t_uint8 f_I2cOscValue_u8,
                                        t_uint8 f_idxI2cRccClock_u8,
                                        t_uint32 * f_bspI2cPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    return Ret_e;     
}
//Function to Get the Prescaler of Usb Configuration from Usb frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForUsb(t_eFMKCPU_SysClkOsc f_UsbOscSrc_e,
                                        t_uint8 f_UsbOscValue_u8,
                                        t_uint8 f_idxUsbRccClock_u8,
                                        t_uint32 * f_bspUsbPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    return Ret_e;     
}
//Function to Get the Prescaler of Fdcan Configuration from Fdcan frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForFdcan(t_eFMKCPU_SysClkOsc f_FdcanOscSrc_e,
                                        t_uint8 f_FdcanOscValue_u8,
                                        t_uint8 f_idxFdcanRccClock_u8,
                                        t_uint32 * f_bspFdcanPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    return Ret_e;  
}
//Function to Get the Prescaler of Can Configuration from Can frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForCan(t_eFMKCPU_SysClkOsc f_CanOscSrc_e,
                                        t_uint8 f_CanOscValue_u8,
                                        t_uint8 f_idxCanRccClock_u8,
                                        t_uint32 * f_bspCanPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    return Ret_e;  
}
//Function to Get the Prescaler of Lptim Configuration from Lptim frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForLptim(t_eFMKCPU_SysClkOsc f_LptimOscSrc_e,
                                        t_uint8 f_LptimOscValue_u8,
                                        t_uint8 f_idxLptimRccClock_u8,
                                        t_uint32 * f_bspLptimPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    return Ret_e;  
}
//Function to Get the Prescaler of Sai1 Configuration from Sai1 frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForSai1(t_eFMKCPU_SysClkOsc f_Sai1OscSrc_e,
                                        t_uint8 f_Sai1OscValue_u8,
                                        t_uint8 f_idxSai1RccClock_u8,
                                        t_uint32 * f_bspSai1Prescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    return Ret_e;  
}
//Function to Get the Prescaler of Hrtim Configuration from Hrtim frequency constraint and the Bus used
t_eReturnCode FMKCPU_GetPrescalerForHrtim(t_eFMKCPU_SysClkOsc f_HrtimOscSrc_e,
                                        t_uint8 f_HrtimOscValue_u8,
                                        t_uint8 f_idxHrtimRccClock_u8,
                                        t_uint32 * f_bspHrtimPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    return Ret_e;   
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
           
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
