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
    t_float32 deltaPrescaler_f32 = (t_float32)0.0f;
    t_float32 freqPwmCompute_f32 = (t_float32)0.0f;
    t_float32 deltaFreqPwm_f32 = (t_float32)0;

    t_uint32 maxNumberBit_u32   = (t_uint32)0;
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
                maxNumberBit_u32 = (t_uint32)(CST_MAX_UINT_16BIT);
                maxARRValue_u32 = (t_uint32)(FMKCPU_TIMER_PWM_ARR_TARGET_16_BIT); // 16-bit target
                decreasingValue_u32 = FMKCPU_ARR_DECREASING_VAL_16B;
                break;
            }
            case FMKCPU_RCC_CLK_TIM2:
            case FMKCPU_RCC_CLK_TIM5:
            {
                maxNumberBit_u32 = (t_uint32)(CST_MAX_UINT_32BIT);
                maxARRValue_u32 = (t_uint32)(FMKCPU_TIMER_PWM_ARR_TARGET_32_BIT); // 32-bit target
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
                && (realARR_u32 > (t_uint32)(maxNumberBit_u32)) ; 
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
        // 0xFFFF or 0xFFFFFFFF , no need to create a variable just for that
        if(realPrescaler_u32 > (t_uint32)(maxNumberBit_u32))
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
        else 
        {
            //----Verify Compute value--------//
            freqPwmCompute_f32 = s_FMKCPU_Timer_GetFreqPwm((t_uint32)OscTimSrcValue_u16, (realPrescaler_u32 - 1), realARR_u32);
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

/*********************************
 * FMKCPU_GetOCTimerInitParam
 *********************************/
t_eReturnCode FMKCPU_GetOCTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32   f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspTimARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32)
{
    return RC_ERROR_INSTANCE_NOT_INITIALIZED;
}

/*********************************
 * FMKCPU_GetOPTimerInitParam
 *********************************/
t_eReturnCode FMKCPU_GetOPTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32   f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32)
{
    return RC_ERROR_INSTANCE_NOT_INITIALIZED;
}

/*********************************
 * FMKCPU_GetEvntTimerInitParam
 *********************************/
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
            freqCompute_f32 = s_FMKCPU_Timer_GetFreqPwm((t_uint32)OscTimSrcValue_u32, realPrescaler_u32, realARR_u32);
            deltaFreq_f32 = (t_float32)(f_EvntFreq_f32 - freqCompute_f32);

            if (fabsf(deltaFreq_f32) > (t_float32)FMKCPU_FREQ_COMPUTE_DELTA_ACCEPTANCE)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
            if(Ret_e == RC_OK)
            {
                *f_bspTimARR_pu32 = (t_uint32)realARR_u32;
                *f_bspTimPrescaler_pu32 = (t_uint32)(realPrescaler_u32);
            }
        }
    }

    return Ret_e;
}

/*********************************
 * FMKCPU_GetECDRTimerInitParam
 *********************************/
t_eReturnCode FMKCPU_GetECDRTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32   f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32)
{
    return RC_ERROR_INSTANCE_NOT_INITIALIZED;
}

/*********************************
 * FMKCPU_GetDacTimerInitParam
 *********************************/
t_eReturnCode FMKCPU_GetDacTimerInitParam(t_uint8  f_idxTimRccClock_u8,
                                                t_eFMKCPU_SysClkOsc f_timOscSrc_e,
                                                t_uint8 * f_SysClockValues_ua8,
                                                t_float32   f_RqstTimerFreq_f32,
                                                t_uint32 * f_bspARR_pu32,
                                                t_uint32 * f_bspTimPrescaler_pu32) 
{
    return RC_ERROR_INSTANCE_NOT_INITIALIZED;
}


/*********************************
 * FMKCPU_Get_BspIRQNType
 *********************************/
t_eReturnCode FMKCPU_Get_BspIRQNType(t_eFMKCPU_IRQNType f_IRQN_e, IRQn_Type *f_bspIRQN_pe)
{
    t_eReturnCode Ret_e = RC_OK;

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
            case FMKCPU_NVIC_PVD_PVM_IRQN:
                *f_bspIRQN_pe = PVD_PVM_IRQn;
                break;
            case FMKCPU_NVIC_RTC_TAMP_LSECSS_IRQN:
                *f_bspIRQN_pe = RTC_TAMP_LSECSS_IRQn;
                break;
            case FMKCPU_NVIC_RTC_WKUP_IRQN:
                *f_bspIRQN_pe = RTC_WKUP_IRQn;
                break;
            case FMKCPU_NVIC_FLASH_IRQN:
                *f_bspIRQN_pe = FLASH_IRQn;
                break;
            case FMKCPU_NVIC_RCC_IRQN:
                *f_bspIRQN_pe = RCC_IRQn;
                break;
            case FMKCPU_NVIC_EXTI0_IRQN:
                *f_bspIRQN_pe = EXTI0_IRQn;
                break;
            case FMKCPU_NVIC_EXTI1_IRQN:
                *f_bspIRQN_pe = EXTI1_IRQn;
                break;
            case FMKCPU_NVIC_EXTI2_IRQN:
                *f_bspIRQN_pe = EXTI2_IRQn;
                break;
            case FMKCPU_NVIC_EXTI3_IRQN:
                *f_bspIRQN_pe = EXTI3_IRQn;
                break;
            case FMKCPU_NVIC_EXTI4_IRQN:
                *f_bspIRQN_pe = EXTI4_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL1_IRQN:
                *f_bspIRQN_pe = DMA1_Channel1_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL2_IRQN:
                *f_bspIRQN_pe = DMA1_Channel2_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL3_IRQN:
                *f_bspIRQN_pe = DMA1_Channel3_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL4_IRQN:
                *f_bspIRQN_pe = DMA1_Channel4_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL5_IRQN:
                *f_bspIRQN_pe = DMA1_Channel5_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL6_IRQN:
                *f_bspIRQN_pe = DMA1_Channel6_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL7_IRQN:
                *f_bspIRQN_pe = DMA1_Channel7_IRQn;
                break;
            case FMKCPU_NVIC_ADC1_2_IRQN:
                *f_bspIRQN_pe = ADC1_2_IRQn;
                break;
            case FMKCPU_NVIC_USB_HP_IRQN:
                *f_bspIRQN_pe = USB_HP_IRQn;
                break;
            case FMKCPU_NVIC_USB_LP_IRQN:
                *f_bspIRQN_pe = USB_LP_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN1_IT0_IRQN:
                *f_bspIRQN_pe = FDCAN1_IT0_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN1_IT1_IRQN:
                *f_bspIRQN_pe = FDCAN1_IT1_IRQn;
                break;
            case FMKCPU_NVIC_EXTI9_5_IRQN:
                *f_bspIRQN_pe = EXTI9_5_IRQn;
                break;
            case FMKCPU_NVIC_TIM1_BRK_TIM15_IRQN:
                *f_bspIRQN_pe = TIM1_BRK_TIM15_IRQn;
                break;
            case FMKCPU_NVIC_TIM1_UP_TIM16_IRQN:
                *f_bspIRQN_pe = TIM1_UP_TIM16_IRQn;
                break;
            case FMKCPU_NVIC_TIM1_TRG_COM_TIM17_IRQN:
                *f_bspIRQN_pe = TIM1_TRG_COM_TIM17_IRQn;
                break;
            case FMKCPU_NVIC_TIM1_CC_IRQN:
                *f_bspIRQN_pe = TIM1_CC_IRQn;
                break;
            case FMKCPU_NVIC_TIM2_IRQN:
                *f_bspIRQN_pe = TIM2_IRQn;
                break;
            case FMKCPU_NVIC_TIM3_IRQN:
                *f_bspIRQN_pe = TIM3_IRQn;
                break;
            case FMKCPU_NVIC_TIM4_IRQN:
                *f_bspIRQN_pe = TIM4_IRQn;
                break;
            case FMKCPU_NVIC_I2C1_EV_IRQN:
                *f_bspIRQN_pe = I2C1_EV_IRQn;
                break;
            case FMKCPU_NVIC_I2C1_ER_IRQN:
                *f_bspIRQN_pe = I2C1_ER_IRQn;
                break;
            case FMKCPU_NVIC_I2C2_EV_IRQN:
                *f_bspIRQN_pe = I2C2_EV_IRQn;
                break;
            case FMKCPU_NVIC_I2C2_ER_IRQN:
                *f_bspIRQN_pe = I2C2_ER_IRQn;
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
            case FMKCPU_NVIC_USART3_IRQN:
                *f_bspIRQN_pe = USART3_IRQn;
                break;
            case FMKCPU_NVIC_EXTI15_10_IRQN:
                *f_bspIRQN_pe = EXTI15_10_IRQn;
                break;
            case FMKCPU_NVIC_RTC_ALARM_IRQN:
                *f_bspIRQN_pe = RTC_Alarm_IRQn;
                break;
            case FMKCPU_NVIC_USBWAKEUP_IRQN:
                *f_bspIRQN_pe = USBWakeUp_IRQn;
                break;
            case FMKCPU_NVIC_TIM8_BRK_IRQN:
                *f_bspIRQN_pe = TIM8_BRK_IRQn;
                break;
            case FMKCPU_NVIC_TIM8_UP_IRQN:
                *f_bspIRQN_pe = TIM8_UP_IRQn;
                break;
            case FMKCPU_NVIC_TIM8_TRG_COM_IRQN:
                *f_bspIRQN_pe = TIM8_TRG_COM_IRQn;
                break;
            case FMKCPU_NVIC_TIM8_CC_IRQN:
                *f_bspIRQN_pe = TIM8_CC_IRQn;
                break;
            case FMKCPU_NVIC_ADC3_IRQN:
                *f_bspIRQN_pe = ADC3_IRQn;
                break;
            case FMKCPU_NVIC_FMC_IRQN:
                *f_bspIRQN_pe = FMC_IRQn;
                break;
            case FMKCPU_NVIC_LPTIM1_IRQN:
                *f_bspIRQN_pe = LPTIM1_IRQn;
                break;
            case FMKCPU_NVIC_TIM5_IRQN:
                *f_bspIRQN_pe = TIM5_IRQn;
                break;
            case FMKCPU_NVIC_SPI3_IRQN:
                *f_bspIRQN_pe = SPI3_IRQn;
                break;
            case FMKCPU_NVIC_UART4_IRQN:
                *f_bspIRQN_pe = UART4_IRQn;
                break;
            case FMKCPU_NVIC_UART5_IRQN:
                *f_bspIRQN_pe = UART5_IRQn;
                break;
            case FMKCPU_NVIC_TIM6_DAC_IRQN:
                *f_bspIRQN_pe = TIM6_DAC_IRQn;
                break;
            case FMKCPU_NVIC_TIM7_DAC_IRQN:
                *f_bspIRQN_pe = TIM7_DAC_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL1_IRQN:
                *f_bspIRQN_pe = DMA2_Channel1_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL2_IRQN:
                *f_bspIRQN_pe = DMA2_Channel2_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL3_IRQN:
                *f_bspIRQN_pe = DMA2_Channel3_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL4_IRQN:
                *f_bspIRQN_pe = DMA2_Channel4_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL5_IRQN:
                *f_bspIRQN_pe = DMA2_Channel5_IRQn;
                break;
            case FMKCPU_NVIC_ADC4_IRQN:
                *f_bspIRQN_pe = ADC4_IRQn;
                break;
            case FMKCPU_NVIC_ADC5_IRQN:
                *f_bspIRQN_pe = ADC5_IRQn;
                break;
            case FMKCPU_NVIC_UCPD1_IRQN:
                *f_bspIRQN_pe = UCPD1_IRQn;
                break;
            case FMKCPU_NVIC_COMP1_2_3_IRQN:
                *f_bspIRQN_pe = COMP1_2_3_IRQn;
                break;
            case FMKCPU_NVIC_COMP4_5_6_IRQN:
                *f_bspIRQN_pe = COMP4_5_6_IRQn;
                break;
            case FMKCPU_NVIC_COMP7_IRQN:
                *f_bspIRQN_pe = COMP7_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_MASTER_IRQN:
                *f_bspIRQN_pe = HRTIM1_Master_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIMA_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIMA_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIMB_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIMB_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIMC_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIMC_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIMD_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIMD_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIME_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIME_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_FLT_IRQN:
                *f_bspIRQN_pe = HRTIM1_FLT_IRQn;
                break;
            case FMKCPU_NVIC_HRTIM1_TIMF_IRQN:
                *f_bspIRQN_pe = HRTIM1_TIMF_IRQn;
                break;
            case FMKCPU_NVIC_CRS_IRQN:
                *f_bspIRQN_pe = CRS_IRQn;
                break;
            case FMKCPU_NVIC_SAI1_IRQN:
                *f_bspIRQN_pe = SAI1_IRQn;
                break;
            case FMKCPU_NVIC_TIM20_BRK_IRQN:
                *f_bspIRQN_pe = TIM20_BRK_IRQn;
                break;
            case FMKCPU_NVIC_TIM20_UP_IRQN:
                *f_bspIRQN_pe = TIM20_UP_IRQn;
                break;
            case FMKCPU_NVIC_TIM20_TRG_COM_IRQN:
                *f_bspIRQN_pe = TIM20_TRG_COM_IRQn;
                break;
            case FMKCPU_NVIC_TIM20_CC_IRQN:
                *f_bspIRQN_pe = TIM20_CC_IRQn;
                break;
            case FMKCPU_NVIC_FPU_IRQN:
                *f_bspIRQN_pe = FPU_IRQn;
                break;
            case FMKCPU_NVIC_I2C4_EV_IRQN:
                *f_bspIRQN_pe = I2C4_EV_IRQn;
                break;
            case FMKCPU_NVIC_I2C4_ER_IRQN:
                *f_bspIRQN_pe = I2C4_ER_IRQn;
                break;
            case FMKCPU_NVIC_SPI4_IRQN:
                *f_bspIRQN_pe = SPI4_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN2_IT0_IRQN:
                *f_bspIRQN_pe = FDCAN2_IT0_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN2_IT1_IRQN:
                *f_bspIRQN_pe = FDCAN2_IT1_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN3_IT0_IRQN:
                *f_bspIRQN_pe = FDCAN3_IT0_IRQn;
                break;
            case FMKCPU_NVIC_FDCAN3_IT1_IRQN:
                *f_bspIRQN_pe = FDCAN3_IT1_IRQn;
                break;
            case FMKCPU_NVIC_RNG_IRQN:
                *f_bspIRQN_pe = RNG_IRQn;
                break;
            case FMKCPU_NVIC_LPUART1_IRQN:
                *f_bspIRQN_pe = LPUART1_IRQn;
                break;
            case FMKCPU_NVIC_I2C3_EV_IRQN:
                *f_bspIRQN_pe = I2C3_EV_IRQn;
                break;
            case FMKCPU_NVIC_I2C3_ER_IRQN:
                *f_bspIRQN_pe = I2C3_ER_IRQn;
                break;
            case FMKCPU_NVIC_DMAMUX_OVR_IRQN:
                *f_bspIRQN_pe = DMAMUX_OVR_IRQn;
                break;
            case FMKCPU_NVIC_QUADSPI_IRQN:
                *f_bspIRQN_pe = QUADSPI_IRQn;
                break;
            case FMKCPU_NVIC_DMA1_CHANNEL8_IRQN:
                *f_bspIRQN_pe = DMA1_Channel8_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL6_IRQN:
                *f_bspIRQN_pe = DMA2_Channel6_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL7_IRQN:
                *f_bspIRQN_pe = DMA2_Channel7_IRQn;
                break;
            case FMKCPU_NVIC_DMA2_CHANNEL8_IRQN:
                *f_bspIRQN_pe = DMA2_Channel8_IRQn;
                break;
            case FMKCPU_NVIC_CORDIC_IRQN:
                *f_bspIRQN_pe = CORDIC_IRQn;
                break;
            case FMKCPU_NVIC_FMAC_IRQN:
                *f_bspIRQN_pe = FMAC_IRQn;
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

#ifdef FMKCPU_STM32_ECU_FAMILY_G
/*********************************
 * FMKCPU_SetPeriphClockCfg
 *********************************/
t_eReturnCode FMKCPU_SetPeriphClockCfg(t_eFMKCPU_ClockPort f_clockPort_e)
{
    t_eReturnCode Ret_e = RC_OK; 
    RCC_PeriphCLKInitTypeDef PeriphClkCfg_s;
    HAL_StatusTypeDef bspRet_e = HAL_OK;

    if(f_clockPort_e >= FMKCPU_RCC_CLK_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_clockPort_e)
        {
            /* CAUTION : Automatic generated code section for Periph Clock Cfg: Start */
            case FMKCPU_RCC_CLK_ADC12:
                PeriphClkCfg_s.Adc12ClockSelection = RCC_PERIPHCLK_ADC12;
                //------ Reference Clock  Source PLLP ------//
                PeriphClkCfg_s.PeriphClockSelection = RCC_ADC12CLKSOURCE_PLL;
                break;
            case FMKCPU_RCC_CLK_ADC345:
                PeriphClkCfg_s.Adc345ClockSelection = RCC_PERIPHCLK_ADC345;
                //------ Reference Clock  Source PLLP ------//
                PeriphClkCfg_s.PeriphClockSelection = RCC_ADC345CLKSOURCE_PLL;
                break;
            case FMKCPU_RCC_CLK_QSPI:
                PeriphClkCfg_s.QspiClockSelection = RCC_PERIPHCLK_QSPI;
                //------ Reference Clock  Source PLLQ ------//
                PeriphClkCfg_s.PeriphClockSelection = RCC_QSPICLKSOURCE_PLL;
                break;
            case FMKCPU_RCC_CLK_USART2:
                PeriphClkCfg_s.Usart2ClockSelection = RCC_PERIPHCLK_USART2;
                //------ Reference Clock  Source APB1 ------//
                PeriphClkCfg_s.PeriphClockSelection = RCC_USART2CLKSOURCE_PCLK1;
                break;
            case FMKCPU_RCC_CLK_USART3:
                PeriphClkCfg_s.Usart3ClockSelection = RCC_PERIPHCLK_USART3;
                //------ Reference Clock  Source APB1 ------//
                PeriphClkCfg_s.PeriphClockSelection = RCC_USART3CLKSOURCE_PCLK1;
                break;
            case FMKCPU_RCC_CLK_UART4:
                PeriphClkCfg_s.Uart4ClockSelection = RCC_PERIPHCLK_UART4;
                //------ Reference Clock  Source APB1 ------//
                PeriphClkCfg_s.PeriphClockSelection = RCC_UART4CLKSOURCE_PCLK1;
                break;
            case FMKCPU_RCC_CLK_UART5:
                PeriphClkCfg_s.Uart5ClockSelection = RCC_PERIPHCLK_UART5;
                //------ Reference Clock  Source APB1 ------//
                PeriphClkCfg_s.PeriphClockSelection = RCC_UART5CLKSOURCE_PCLK1;
                break;
            case FMKCPU_RCC_CLK_FDCAN:
                PeriphClkCfg_s.FdcanClockSelection = RCC_PERIPHCLK_FDCAN;
                //------ Reference Clock  Source PLLQ ------//
                PeriphClkCfg_s.PeriphClockSelection = RCC_FDCANCLKSOURCE_PLL;
                break;
            case FMKCPU_RCC_CLK_I2C3:
                PeriphClkCfg_s.I2c3ClockSelection = RCC_PERIPHCLK_I2C3;
                //------ Reference Clock  Source APB1 ------//
                PeriphClkCfg_s.PeriphClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
                break;
            case FMKCPU_RCC_CLK_USART1:
                PeriphClkCfg_s.Usart1ClockSelection = RCC_PERIPHCLK_USART1;
                //------ Reference Clock  Source APB2 ------//
                PeriphClkCfg_s.PeriphClockSelection = RCC_USART1CLKSOURCE_PCLK2;
                break;
            case FMKCPU_RCC_CLK_DMA1:
            case FMKCPU_RCC_CLK_DMA2:
            case FMKCPU_RCC_CLK_DMAMUX1:
            case FMKCPU_RCC_CLK_CORDIC:
            case FMKCPU_RCC_CLK_FMAC:
            case FMKCPU_RCC_CLK_FLASH:
            case FMKCPU_RCC_CLK_CRC:
            case FMKCPU_RCC_CLK_GPIOG:
            case FMKCPU_RCC_CLK_GPIOF:
            case FMKCPU_RCC_CLK_GPIOE:
            case FMKCPU_RCC_CLK_GPIOD:
            case FMKCPU_RCC_CLK_GPIOC:
            case FMKCPU_RCC_CLK_GPIOB:
            case FMKCPU_RCC_CLK_GPIOA:
            case FMKCPU_RCC_CLK_DAC1:
            case FMKCPU_RCC_CLK_DAC2:
            case FMKCPU_RCC_CLK_DAC3:
            case FMKCPU_RCC_CLK_DAC4:
            case FMKCPU_RCC_CLK_RNG:
            case FMKCPU_RCC_CLK_FMC:
            case FMKCPU_RCC_CLK_TIM2:
            case FMKCPU_RCC_CLK_TIM3:
            case FMKCPU_RCC_CLK_TIM4:
            case FMKCPU_RCC_CLK_TIM5:
            case FMKCPU_RCC_CLK_TIM6:
            case FMKCPU_RCC_CLK_TIM7:
            case FMKCPU_RCC_CLK_CRS:
            case FMKCPU_RCC_CLK_RTCAPB:
            case FMKCPU_RCC_CLK_WWDG:
            case FMKCPU_RCC_CLK_SPI2:
            case FMKCPU_RCC_CLK_SPI3:
            case FMKCPU_RCC_CLK_I2C2:
            case FMKCPU_RCC_CLK_USB:
            case FMKCPU_RCC_CLK_PWR:
            case FMKCPU_RCC_CLK_LPTIM1:
            case FMKCPU_RCC_CLK_UCPD1:
            case FMKCPU_RCC_CLK_SYSCFG:
            case FMKCPU_RCC_CLK_TIM1:
            case FMKCPU_RCC_CLK_SPI1:
            case FMKCPU_RCC_CLK_TIM8:
            case FMKCPU_RCC_CLK_SPI4:
            case FMKCPU_RCC_CLK_TIM15:
            case FMKCPU_RCC_CLK_TIM16:
            case FMKCPU_RCC_CLK_TIM17:
            case FMKCPU_RCC_CLK_TIM20:
            case FMKCPU_RCC_CLK_SAI1:
            case FMKCPU_RCC_CLK_HRTIM1:
            case FMKCPU_RCC_CLK_NB:
            default:
                Ret_e = RC_WARNING_NO_OPERATION;
                break;
            /* CAUTION : Automatic generated code section for Periph Clock Cfg: End */

        }
        
        if(Ret_e == RC_OK)
        {
            bspRet_e = HAL_RCCEx_PeriphCLKConfig(&PeriphClkCfg_s);
            if(bspRet_e != HAL_OK)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
        }
        //------ No Need To Transfer this return code ------//
        if(Ret_e == RC_WARNING_NO_OPERATION)
        {
            Ret_e = RC_OK;
        }
    }

    return Ret_e;
}
#endif


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

/**< This function has been made to filled in c_FMKCPU_TimerFunc_apf */
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
