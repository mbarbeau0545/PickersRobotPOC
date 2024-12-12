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
#include <math.h>
#include "FMKCPU_ConfigSpecific.h"

// ********************************************************************
// *                      Defines
// ********************************************************************
#define FMKCPU_MAX_LOOP_DECREASING ((t_uint8)30)
#define FMKCPU_ARR_DECREASING_VAL_16B ((t_uint32)2000)
#define FMKCPU_ARR_DECREASING_VAL_32B ((t_uint32)20000)

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

//********************************************************************************
//                      Public functions - Prototypes
//********************************************************************************
/*********************************
 * s_FMKCPU_GetMaxFreqSupported
 *********************************/
static inline t_float32 s_FMKCPU_GetMaxFreqSupported(t_uint32 osc_val, t_uint32 ARRVal) {
    return (t_float32)(((t_uint32)osc_val * CST_MHZ_TO_HZ) / ((t_uint32)ARRVal + 1));
}
/*********************************
 * s_FMKCPU_Timer_GetPrescaler
 *********************************/
static inline t_float32 s_FMKCPU_Timer_GetPrescaler(t_uint32 osc_valMhz, t_uint32 ARRVal, t_float32 freqPwm) {
    return (t_float32)(((t_float32)osc_valMhz * CST_MHZ_TO_HZ) / (((t_float32)ARRVal + 1) * (t_float32)freqPwm));
}
/*********************************
 * s_FMKCPU_Timer_GetArrRegister
 *********************************/
static inline t_uint32 s_FMKCPU_Timer_GetArrRegister(t_uint32 osc_valMhz, t_uint32 f_Prescaler_u32, t_float32 freqPwm) {
    return (t_uint32)(((t_float32)osc_valMhz * CST_MHZ_TO_HZ) / (((t_float32)f_Prescaler_u32 + 1) * (t_float32)freqPwm));
}
/*********************************
 * s_FMKCPU_Timer_GeFreqPwm
 *********************************/
static inline t_float32 s_FMKCPU_Timer_GetFreqPwm(t_uint32 osc_valMhz, t_uint32 f_Prescaler_u32, t_uint32 f_ARRVal) {
    return (t_float32)(((t_float32)osc_valMhz * CST_MHZ_TO_HZ) / (((t_float32)f_Prescaler_u32 + 1) * ((t_float32)(f_ARRVal + 1))));
}
/*********************************
 * s_FMKCPU_DecomposeFloat
 *********************************/
// Fonction inline pour décomposer une valeur
static inline void  s_FMKCPU_DecomposeFloat(t_float32 f_value_f32,t_uint32 *f_partieEntiere_pu32, t_float32 *f_fractionleft_pf32 ) {

    *f_partieEntiere_pu32 = (t_uint32)((f_value_f32 >= 0) ? floorf(f_value_f32 + 0.5f) : ceilf(f_value_f32 - 0.5f)); // Arrondi vers l'entier le plus proche
    *f_fractionleft_pf32 = (t_float32)(f_value_f32 - (t_float32)(*f_partieEntiere_pu32)); // Partie fractionnelle
}
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * FMKCPU_GetPwmTimerInitParam
 *********************************/
t_eReturnCode FMKCPU_GetPwmTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32 f_PwmFreq_f32,
                                                t_uint32 * f_bspTimARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint16 OscTimSrcValue_u16;
    t_uint32 maxARRValue_u32 =  (t_uint32)0;
    t_uint32 targetARRValue_u32 = (t_uint32)0;
    t_uint8 multiplier_u8 = (t_uint8)1;
    t_float32 freqMaxSupported_f32 = (t_uint16)0.0f;
    t_float32 prescalerTheo_f32 = (t_float32)0.0f;
    t_float32 deltaPrescaler_f32 = 0;
    t_float32 freqPwmCompute_f32 = (t_float32);
    t_float32 deltaFreqPwm_f32 = (t_float32)0;
    t_uint32 decreasingValue_u32 = (t_uint32)FMKCPU_ARR_DECREASING_VAL_16B;
    t_uint32 realPrescaler_u32 = (t_uint32)0;
    t_uint32 realARR_u32 = (t_uint32)0;
    
    t_uint8 LLI_u8;

    if((f_bspTimPrescaler_pu32 == (t_uint32 *)NULL)
    || (f_SysClockValues_ua8   == (t_uint8 *)NULL)
    || (f_bspTimARR_pu32       == (t_uint32 *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if((f_idxTimRccClock_u8 > FMKCPU_RCC_CLK_NB)
    || (f_timOscSrc_e > FMKCPU_SYS_CLOCK_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        // Timer depend on APB1 or APB2, if these clock were divided per 2 or more,
        // Hardware multiply by 2 the core freqency of the timer
        // In other word 
        OscTimSrcValue_u16 = (t_uint8)f_SysClockValues_ua8[f_timOscSrc_e];

        if(f_SysClockValues_ua8[FMKCPU_SYS_CLOCK_SYSTEM] > OscTimSrcValue_u16)
        {
            multiplier_u8 = (t_uint8)2;
        }
        //---------Ocillator value---------//
        OscTimSrcValue_u16 = (t_uint16)(OscTimSrcValue_u16 * (t_uint16)multiplier_u8);
        
        //----------Know if it is a 16 or 32 bit timer 
        switch(f_idxTimRccClock_u8)
        {
            case FMKCPU_RCC_CLK_TIM1:
            case FMKCPU_RCC_CLK_TIM3:
            case FMKCPU_RCC_CLK_TIM4:
            case FMKCPU_RCC_CLK_TIM6:
            case FMKCPU_RCC_CLK_TIM7:
            case FMKCPU_RCC_CLK_TIM8:
            case FMKCPU_RCC_CLK_TIM15:
            case FMKCPU_RCC_CLK_TIM16:
            case FMKCPU_RCC_CLK_TIM17:
            case FMKCPU_RCC_CLK_TIM20:
            {
                maxARRValue_u32 = (t_uint32)(CST_MAX_UINT_16BIT - 1); // 16-bit target
                decreasingValue_u32 = FMKCPU_ARR_DECREASING_VAL_16B;
                break;
            }
            case FMKCPU_RCC_CLK_TIM2:
            case FMKCPU_RCC_CLK_TIM5:
            {
                maxARRValue_u32 = (t_uint32)(CST_MAX_UINT_32BIT - 1); // 32-bit target
                decreasingValue_u32 = FMKCPU_ARR_DECREASING_VAL_32B;
                break;
            }
            default:
            {
                maxARRValue_u32 = (t_uint32)(CST_MAX_UINT_16BIT - 1);
                break;
            }
        }
        //---------Know the max frequency supported with max Arr Value---------//
        targetARRValue_u32 = maxARRValue_u32;
        freqMaxSupported_f32 = s_FMKCPU_GetMaxFreqSupported((t_uint32)OscTimSrcValue_u16, targetARRValue_u32);

        for(LLI_u8 = (t_uint8)0 ; 
        (LLI_u8 < FMKCPU_MAX_LOOP_DECREASING)
        && (f_PwmFreq_f32 > freqMaxSupported_f32); 
        LLI_u8++)
        {
            //---------Compute New Max Frequency with new ARR value---------//
            targetARRValue_u32 -= (t_uint32)decreasingValue_u32;
            freqMaxSupported_f32 = s_FMKCPU_GetMaxFreqSupported((t_uint32)OscTimSrcValue_u16, targetARRValue_u32);
        }
        if(LLI_u8 >= (t_uint8)FMKCPU_MAX_LOOP_DECREASING)
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
        //---- Prescaler Théorique--------//
        prescalerTheo_f32 = s_FMKCPU_Timer_GetPrescaler((t_uint32)OscTimSrcValue_u16, targetARRValue_u32, f_PwmFreq_f32);
        //---- Delta Prescaler--------//
        s_FMKCPU_DecomposeFloat(prescalerTheo_f32, &realPrescaler_u32, &deltaPrescaler_f32);

        //----Manage prescaler == 0 for DIV 0 --------//
        if(realPrescaler_u32 == (t_uint32)0)
        {
            realARR_u32 = (t_uint32)((((t_uint32)OscTimSrcValue_u16 * CST_MHZ_TO_HZ) /
                                                (t_uint32)(f_PwmFreq_f32)) - (t_uint32)1);
        }
        else 
        {

            //---- recalculate ARR value--------//
            realARR_u32 = (t_uint32)((t_float32)targetARRValue_u32 + (t_float32)((t_float32)(targetARRValue_u32/realPrescaler_u32) * deltaPrescaler_f32));
            realARR_u32 -= (t_uint32)1;

            //---- Loop to adapt ARR value to not exceed maxARRValue_u32--------//
            for(LLI_u8 = (t_uint8)0 ;
                (LLI_u8 < FMKCPU_MAX_LOOP_DECREASING)
                && (realARR_u32 > (t_uint32)(maxARRValue_u32)) ; 
                LLI_u8++)
            {
                //----Two cases are reertory 
                // - The prescaler is 0 and 1,2 is enough to get an ARR valid
                // - The prescaler is >> 1 and we need to get a bigger prescaler--------//

                if(LLI_u8 > (t_uint8)(FMKCPU_MAX_LOOP_DECREASING)/ 2)
                {
                    realPrescaler_u32 += (t_uint32)100;
                }
                else 
                {
                    realPrescaler_u32 += (t_uint32)1;
                }

                realARR_u32 = (t_uint32)((t_float32)targetARRValue_u32 + 
                            (t_float32)((t_float32)(targetARRValue_u32/ realPrescaler_u32) * deltaPrescaler_f32));
                realARR_u32 -= (t_uint32)1; 
            }
            if(LLI_u8 >= (t_uint8)FMKCPU_MAX_LOOP_DECREASING)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
        }
        //----Verify Range Validity--------//
        //                                  0xFFFF or 0xFFFFFFFF , no need to create a variable just for that
        if(realPrescaler_u32 > (t_uint32)(maxARRValue_u32 + 1))
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
        else 
        {
            //----Verify Compute value--------//
            freqPwmCompute_f32 = s_FMKCPU_Timer_GeFreqPwm((t_uint32)OscTimSrcValue_u16, (realPrescaler_u32 - 1), realARR_u32);
            deltaFreqPwm_f32 = (t_float32)(f_PwmFreq_f32 - freqPwmCompute_f32);

            if (fabsf(deltaFreqPwm_f32) > (t_float32)FMKCPU_FREQ_COMPUTE_DELTA_ACCEPTANCE)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }

            //----Copy values--------//
            if(Ret_e == RC_OK)
            {
                *f_bspTimARR_pu32 = (t_uint32)realARR_u32;
                *f_bspTimPrescaler_pu32 = (t_uint32)(realPrescaler_u32 - 1);
            }
        }
    }

    return Ret_e;  
}

/*********************************
 * FMKCPU_GetICTimerInitParam
 *********************************/
t_eReturnCode FMKCPU_GetICTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                          t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                          t_uint8 * f_SysClockValues_ua8,
                                          t_float32   f_RqstTimerFreq_f32,
                                          t_uint32 * f_bspTimARR_pu32,
                                          t_uint32 * f_bspTimPrescaler_pu32)
{
    return RC_ERROR_INSTANCE_NOT_INITIALIZED;
}         
t_eReturnCode FMKCPU_GetOCTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32   f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspTimARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32)
{
    return RC_ERROR_INSTANCE_NOT_INITIALIZED;
}                                                
t_eReturnCode FMKCPU_GetOPTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32   f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32)
{
    return RC_ERROR_INSTANCE_NOT_INITIALIZED;
}
t_eReturnCode FMKCPU_GetEvntTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32 f_EvntFreq_f32,
                                                t_uint32 * f_bspTimARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 lowPrescaler_f32  = (t_float32)0.0f;
    t_float32 highPrescaler_f32 = (t_float32)0.0f;
    t_float32 deltaFreq_f32     = (t_float32)0.0f;
    t_float32 freqCompute_f32    = (t_uint32)0.0f;

    t_uint32 realPrescaler_u32  = (t_uint32)0;
    t_uint32 realARR_u32        = (t_uint32)0;
    t_uint32 OscTimSrcValue_u32 = (t_uint32)0;
    t_uint32 maxARRValue_u32    = (t_uint32)0;
    t_uint32 minARRValue_u32    = (t_uint32)0;
    t_uint32 maxNumberBit_u32   = (t_uint32)0;
    t_uint8 multiplier_u8       = (t_uint8)1;

    if((f_bspTimPrescaler_pu32 == (t_uint32 *)NULL)
    || (f_SysClockValues_ua8   == (t_uint8 *)NULL)
    || (f_bspTimARR_pu32       == (t_uint32 *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if((f_idxTimRccClock_u8 > FMKCPU_RCC_CLK_NB)
    || (f_timOscSrc_e > FMKCPU_SYS_CLOCK_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        // Timer depend on APB1 or APB2, if these clock were divided per 2 or more,
        // Hardware multiply by 2 the core freqency of the timer
        // In other word 
        OscTimSrcValue_u32 = (t_uint32)f_SysClockValues_ua8[f_timOscSrc_e];

        if((t_uint32)f_SysClockValues_ua8[FMKCPU_SYS_CLOCK_SYSTEM] > OscTimSrcValue_u32)
        {
            multiplier_u8 = (t_uint8)2;
        }
        //---------Ocillator value---------//
        OscTimSrcValue_u32 = (t_uint16)(OscTimSrcValue_u32 * (t_uint16)multiplier_u8);
        
        //----------Know if it is a 16 or 32 bit timer---------//
        switch(f_idxTimRccClock_u8)
        {
            case FMKCPU_RCC_CLK_TIM1:
            case FMKCPU_RCC_CLK_TIM3:
            case FMKCPU_RCC_CLK_TIM4:
            case FMKCPU_RCC_CLK_TIM6:
            case FMKCPU_RCC_CLK_TIM7:
            case FMKCPU_RCC_CLK_TIM8:
            case FMKCPU_RCC_CLK_TIM15:
            case FMKCPU_RCC_CLK_TIM16:
            case FMKCPU_RCC_CLK_TIM17:
            case FMKCPU_RCC_CLK_TIM20:
            {
                maxNumberBit_u32 = (t_uint32)(CST_MAX_UINT_16BIT);
                minARRValue_u32  = (t_uint32)FMKCPU_ARR_LOW_LIMIT_16BIT;
                maxARRValue_u32  = (t_uint32)FMKCPU_ARR_HIGH_LIMIT_16BIT;
                break;
            }
            case FMKCPU_RCC_CLK_TIM2:
            case FMKCPU_RCC_CLK_TIM5:
            {
                maxNumberBit_u32 = (t_uint32)(CST_MAX_UINT_32BIT);
                minARRValue_u32 = (t_uint32)FMKCPU_ARR_LOW_LIMIT_32BIT;
                maxARRValue_u32 = (t_uint32)FMKCPU_ARR_HIGH_LIMIT_32BIT;
                break;
            }
            default:
            {
                maxNumberBit_u32 = (t_uint32)(CST_MAX_UINT_16BIT);
                minARRValue_u32 = (t_uint32)FMKCPU_ARR_LOW_LIMIT_16BIT;
                maxARRValue_u32 = (t_uint32)FMKCPU_ARR_HIGH_LIMIT_16BIT;
                break;
            }
        }
        //----------Calculate Low/High/Mean Prescaler---------//
        lowPrescaler_f32 = s_FMKCPU_Timer_GetPrescaler(OscTimSrcValue_u32, minARRValue_u32, f_EvntFreq_f32);
        highPrescaler_f32 = s_FMKCPU_Timer_GetPrescaler(OscTimSrcValue_u32, maxARRValue_u32, f_EvntFreq_f32);
        realPrescaler_u32 = (t_uint32)((lowPrescaler_f32 + highPrescaler_f32) / (t_float32)2.0f);

        //----------Calculate ARR with prescaler---------//
        realARR_u32 = s_FMKCPU_Timer_GetArrRegister(OscTimSrcValue_u32, realPrescaler_u32, f_EvntFreq_f32);

        //----Varify Range Value--------//
        if(realARR_u32 > maxNumberBit_u32
        ||realPrescaler_u32 > maxNumberBit_u32)
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
        else
        {
            //----Verify Compute value--------//
            freqCompute_f32 = s_FMKCPU_Timer_GeFreqPwm((t_uint32)OscTimSrcValue_u32, realPrescaler_u32, realARR_u32);
            deltaFreq_f32 = (t_float32)(f_EvntFreq_f32 - freqCompute_f32);

            if (fabsf(deltaFreq_f32) > (t_float32)FMKCPU_FREQ_COMPUTE_DELTA_ACCEPTANCE)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
            if(Ret_e == RC_OK)
            {
                f_bspTimARR_pu32 = (t_uint32)realARR_u32;
                f_bspTimPrescaler_pu32 = (t_uint32)(realPrescaler_u32);
            }
        }
    }

    return Ret_e;
}
t_eReturnCode FMKCPU_GetECDRTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32   f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32)
{
    return RC_ERROR_INSTANCE_NOT_INITIALIZED;
}
t_eReturnCode FMKCPU_GetDacTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32   f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32) 
{
    return RC_ERROR_INSTANCE_NOT_INITIALIZED;
}
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
