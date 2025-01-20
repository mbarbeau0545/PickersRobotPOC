/**
 * @file        LibRamp.c
 * @brief       Framework Memory Access Control module.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        15/09/2024
 * @version     1.0
 */
// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./LibRamp.h"
#include "math.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define CST_MS_IN_SEC 1000
// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */

//-----------------------------ENUM TYPES-----------------------------//

/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
typedef struct 
{
    t_float32 maxSlope_u32;
    t_uint32 updatePeriod_u32;
    t_float32 startValue_f32;
    
} t_sLIBRamp_LinearInfo;

typedef struct 
{
    t_float32 expFactor_f32;
    t_float32 smoothingFactor_f32;

} t_sLIBRamp_ExpInfo;

typedef struct 
{
    t_float32 kFactor_f32;
    t_float32 midPoint_f32;
    t_float32 startValue_f32;

} t_sLIBRamp_SigmoidaleInfo;
    
typedef union 
{
    t_sLIBRamp_LinearInfo        linear_s;
    t_sLIBRamp_ExpInfo           exp_s;
    t_sLIBRamp_SigmoidaleInfo    sigmoidale_s;
} t_uLIBRamp_RampInfo;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
typedef struct 
{
    t_eLIBRamp_Mode Mode_e;
    t_uLIBRamp_RampInfo Info_u;
    t_float32 previousValue_f32;
    t_uint32 maxDuration_u32;
    t_bool isConfigured_b;
} t_sLIBRamp_RampInfo;
//-----------------------------TYPEDEF TYPES---------------------------//
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
typedef t_eReturnCode (t_cbLIBRamp_ComputeMode)(t_sLIBRamp_RampInfo *f_rampInfo_ps, 
                                                t_float32 f_rqstValue_f32,
                                                t_float32 * f_computeValue_pf32);

//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
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
static t_eReturnCode s_LIBRamp_SetInitRegistration(t_sLIBRamp_RampCfg * f_rampCfg_ps, t_uint8 f_rampID_u8);
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
static t_eReturnCode s_LIBRamp_ComputeValue(t_uint8 f_rampID_u8, 
                                            t_float32 f_valueRqst_f32,
                                            t_float32 * f_computeValue_pf32);
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
static t_eReturnCode s_LIBRamp_ComputeLinearRamp(   t_sLIBRamp_RampInfo * f_rampInfo_ps,
                                                    t_float32 f_valueRqst_f32,
                                                    t_float32 *f_ComputeValue_pf32);
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
static t_eReturnCode s_LIBRamp_ComputeExponentialRamp(  t_sLIBRamp_RampInfo * f_rampInfo_ps,
                                                        t_float32 f_valueRqst_f32,
                                                        t_float32 * f_ComputeValue_pf32);
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
static t_eReturnCode s_LIBRamp_ComputeSigmoidalRamp(t_sLIBRamp_RampInfo * f_rampInfo_ps,
                                                    t_float32 f_valueRqst_f32,
                                                    t_float32 * f_ComputeValu_epf32);
// ********************************************************************
// *                      Variables
// ********************************************************************
static t_cbLIBRamp_ComputeMode * c_ComputeMode_apf[LIBRAMP_MODE_NB] = 
{
    s_LIBRamp_ComputeLinearRamp,
    s_LIBRamp_ComputeExponentialRamp,
    s_LIBRamp_ComputeSigmoidalRamp,
};

static t_sLIBRamp_RampInfo g_RampInfo_as[LIBRAMP_MAX_REGISTRATION];
static t_uint8 g_CntRegistration_u8 = (t_uint8)0;

//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
//**********************
// LIBRamp_Init
//**********************
t_eReturnCode LIBRamp_Init(t_sLIBRamp_RampCfg f_rampCfg_s, t_uint8 *f_rampID_pu8)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_rampID_pu8 == (t_uint8 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_CntRegistration_u8 >= LIBRAMP_MAX_REGISTRATION)
    {
        Ret_e = RC_ERROR_LIMIT_REACHED;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_LIBRamp_SetInitRegistration(&f_rampCfg_s, g_CntRegistration_u8);

        if(Ret_e == RC_OK)
        {
            *f_rampID_pu8 = (t_uint8)g_CntRegistration_u8;
            g_CntRegistration_u8 += (t_uint8)1;
        }
    }

    return Ret_e;
}

//**********************
// LIBRamp_Compute
//**********************
t_eReturnCode LIBRamp_Compute(  t_uint8 f_rampID_u8, 
                                t_float32 f_valueRqst_f32,
                                t_float32 * f_computeValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 computeValue_f32 = (t_float32)0;

    if(f_computeValue_pf32 == (t_float32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(f_rampID_u8 > LIBRAMP_MAX_REGISTRATION)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_LIBRamp_ComputeValue( f_rampID_u8,
                                        f_valueRqst_f32,
                                        &computeValue_f32);

        if(Ret_e == RC_OK)
        {
            *f_computeValue_pf32 = (t_float32)computeValue_f32;
        }

    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
//********************************
// s_LIBRamp_SetInitRegistration
//********************************
static t_eReturnCode s_LIBRamp_SetInitRegistration(t_sLIBRamp_RampCfg * f_rampCfg_ps, t_uint8 f_rampID_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sLIBRamp_RampInfo * rampInfo_ps; 

    if(f_rampCfg_ps == (t_sLIBRamp_RampCfg *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL; 
    }   
    if(Ret_e == RC_OK)
    {
        //------ Reach Ramp Information -----//
        rampInfo_ps = (t_sLIBRamp_RampInfo *)(&g_RampInfo_as[f_rampID_u8]);

        //------ Copy Config -----//
        switch (f_rampCfg_ps->rampMode_e)
        {
            case LIBRAMP_MODE_LINEAR:
            {
                rampInfo_ps->Info_u.linear_s.maxSlope_u32       = f_rampCfg_ps->rampModeCfg_u.linearCfg_s.maxSlope_u32;
                rampInfo_ps->Info_u.linear_s.updatePeriod_u32   = f_rampCfg_ps->rampModeCfg_u.linearCfg_s.updatePeriod_u32;
                rampInfo_ps->Info_u.linear_s.startValue_f32     = f_rampCfg_ps->startValue_f32;
                break;
            }
            case LIBRAMP_MODE_EXPONENTIAL:
            {
                rampInfo_ps->Info_u.exp_s.expFactor_f32         = f_rampCfg_ps->rampModeCfg_u.expCfg_s.expFactor_f32;
                rampInfo_ps->Info_u.exp_s.smoothingFactor_f32   = f_rampCfg_ps->rampModeCfg_u.expCfg_s.smoothingFactor_f32;
                break;
            }
            case LIBRAMP_MODE_SIGMOIDALE:
            {
                rampInfo_ps->Info_u.sigmoidale_s.midPoint_f32   = f_rampCfg_ps->rampModeCfg_u.sigmoidaleCfg_s.midPoint_f32;
                rampInfo_ps->Info_u.linear_s.startValue_f32     = (t_float32)0;
                break;
            }
            case LIBRAMP_MODE_NB:
            default:
            {
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
            }
        }
        if(Ret_e == RC_OK)
        {
            rampInfo_ps->previousValue_f32 = (t_float32)f_rampCfg_ps->startValue_f32;
            rampInfo_ps->Mode_e = f_rampCfg_ps->rampMode_e;
            rampInfo_ps->maxDuration_u32 = f_rampCfg_ps->maxDuration_u32;
            rampInfo_ps->isConfigured_b = (t_bool)True;
        }
    }

    return Ret_e;
}

//********************************
// s_LIBRamp_ComputeValue
//********************************
static t_eReturnCode s_LIBRamp_ComputeValue(t_uint8 f_rampID_u8, 
                                            t_float32 f_valueRqst_f32,
                                            t_float32 * f_computeValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sLIBRamp_RampInfo * rampInfo_ps = (t_sLIBRamp_RampInfo *)(&g_RampInfo_as[f_rampID_u8]);

    if(f_computeValue_pf32 == (t_float32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(rampInfo_ps->isConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }
    if(Ret_e == RC_OK)
    {
        //------ Compute Ramp Calculation -----//
        Ret_e = c_ComputeMode_apf[rampInfo_ps->Mode_e]( rampInfo_ps, 
                                                        f_valueRqst_f32, 
                                                        f_computeValue_pf32);
    }

    return Ret_e;
} 

//********************************
// s_LIBRamp_ComputeLinearRamp
//********************************
static t_eReturnCode s_LIBRamp_ComputeLinearRamp(t_sLIBRamp_RampInfo * f_rampInfo_ps,
                                                 t_float32 f_valueRqst_f32,
                                                 t_float32 *f_ComputeValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 step_f32;
    t_float32 delta_f32;

    if ((f_rampInfo_ps == (t_sLIBRamp_RampInfo *)NULL) 
    || (f_ComputeValue_pf32 == (t_float32 *)NULL)) 
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }

    if (Ret_e == RC_OK) 
    {
        delta_f32 = f_valueRqst_f32 - f_rampInfo_ps->previousValue_f32;

        if(((delta_f32 > 0)
        && (f_rampInfo_ps->previousValue_f32 <= f_rampInfo_ps->Info_u.linear_s.startValue_f32))
        || ((delta_f32 < (t_float32)0)
        && (f_rampInfo_ps->previousValue_f32 >= f_rampInfo_ps->Info_u.linear_s.startValue_f32)))
        {
            f_rampInfo_ps->Info_u.linear_s.startValue_f32 = f_rampInfo_ps->previousValue_f32;
        }
        
        //--- Compute step ---//
        step_f32 = (t_float32)(f_valueRqst_f32 - f_rampInfo_ps->Info_u.linear_s.startValue_f32) / 
                        (t_float32)(f_rampInfo_ps->maxDuration_u32 / f_rampInfo_ps->Info_u.linear_s.updatePeriod_u32);

        //--- If approaching value ---//
        if (fabs(delta_f32) <= fabs(step_f32)) 
        {
            f_rampInfo_ps->previousValue_f32 = f_valueRqst_f32;
        } 
        //--- Add step ---//
        else 
        {
            f_rampInfo_ps->previousValue_f32 += step_f32;
        }

        //--- Copy Data ---//
        *f_ComputeValue_pf32 = f_rampInfo_ps->previousValue_f32;
    }

    return Ret_e;
}

static t_eReturnCode s_LIBRamp_ComputeExponentialRamp(t_sLIBRamp_RampInfo * f_rampInfo_ps,
                                                      t_float32 f_valueRqst_f32,
                                                      t_float32 * f_ComputeValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 delta_f32;
    t_float32 delta_abs_f32;
    t_float32 expFactorUp_f32;
    t_float32 expFactorDown_f32;

    if ((f_rampInfo_ps == (t_sLIBRamp_RampInfo *)NULL) 
    || (f_ComputeValue_pf32 == (t_float32 *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }

    if (Ret_e == RC_OK)
    {
        //--- calculate delta ---//
        delta_f32 = f_valueRqst_f32 - f_rampInfo_ps->previousValue_f32;
        delta_abs_f32 = (t_float32)fabs(delta_f32);

        //--- Get Exp Factor Increase/Decrease ---//
        expFactorUp_f32 = f_rampInfo_ps->Info_u.exp_s.expFactor_f32;
        expFactorDown_f32 = f_rampInfo_ps->Info_u.exp_s.expFactor_f32 * 0.8f;

        //--- Compute value ---//
        if (delta_abs_f32 > (t_float32)f_rampInfo_ps->Info_u.exp_s.smoothingFactor_f32)
        {
            f_rampInfo_ps->previousValue_f32 += (delta_f32 > 0) 
                                                ? delta_f32 * expFactorUp_f32 
                                                : delta_f32 * expFactorDown_f32;
        }
        else
        {  
            f_rampInfo_ps->previousValue_f32 = f_valueRqst_f32;
        }

        //--- Copy data ---//
        *f_ComputeValue_pf32 = f_rampInfo_ps->previousValue_f32;
    }

    return Ret_e;
}




//**********************************
// s_LIBRamp_ComputeSigmoidalRamp
//**********************************
static t_eReturnCode s_LIBRamp_ComputeSigmoidalRamp(t_sLIBRamp_RampInfo * f_rampInfo_ps,
                                                    t_float32 f_valueRqst_f32,
                                                    t_float32 * f_ComputeValue_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 cstK_f32;
    t_float32 midTime_f32;
    t_float32 normalizedTime_f32;
    t_float32 sigmoidalValue_f32;

    if((f_rampInfo_ps == (t_sLIBRamp_RampInfo *)NULL) 
    || (f_ComputeValue_pf32 == (t_float32 *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }

    if(Ret_e == RC_OK)
    {
        //---- Changement of target detection -----//
        if(f_valueRqst_f32 != f_rampInfo_ps->Info_u.sigmoidale_s.startValue_f32)
        {
            f_rampInfo_ps->Info_u.sigmoidale_s.startValue_f32 = f_rampInfo_ps->previousValue_f32;
            cstK_f32 =  (t_float32)(5.0 / f_valueRqst_f32);
            f_rampInfo_ps->Info_u.sigmoidale_s.kFactor_f32 = cstK_f32;
        } 

        //---- update parameter -----//
        midTime_f32 = (t_float32)(fabs(f_valueRqst_f32 - f_rampInfo_ps->Info_u.sigmoidale_s.startValue_f32) * 
                            (f_rampInfo_ps->Info_u.sigmoidale_s.midPoint_f32 / (t_float32)100));
        
        normalizedTime_f32 = (t_float32)((f_rampInfo_ps->previousValue_f32 - midTime_f32) * 
                                (f_rampInfo_ps->Info_u.sigmoidale_s.kFactor_f32));   
        //---- increasing sens -----//
        if(f_rampInfo_ps->previousValue_f32 < f_valueRqst_f32)
        {
            sigmoidalValue_f32 = (t_float32)((t_float32)1.0f / ((t_float32)1.0f + (t_float32)exp(-normalizedTime_f32)));
        }

        //---- decreasing sens -----//
        else if(f_rampInfo_ps->previousValue_f32 > f_valueRqst_f32)
        {
            sigmoidalValue_f32 = (t_float32)((t_float32)1.0f / ((t_float32)1.0f + (t_float32)exp(normalizedTime_f32)));
        }
        else 
        {
            sigmoidalValue_f32 = (t_float32)0.0;
        }

        //---- Compute next value -----//
        f_rampInfo_ps->previousValue_f32 = f_rampInfo_ps->previousValue_f32 + 
                                            (f_valueRqst_f32 - f_rampInfo_ps->previousValue_f32) * sigmoidalValue_f32;
        *f_ComputeValue_pf32 = f_rampInfo_ps->previousValue_f32;
    }
    return Ret_e;
}

/*delta_f32 = f_valueRqst_f32 - f_rampInfo_ps->previousValue_f32;

        if((delta_f32 > (t_float32)0)
        && (f_rampInfo_ps->previousValue_f32 <= f_rampInfo_ps->Info_u.linear_s.startValue_f32))
        {
            f_rampInfo_ps->Info_u.sigmoidale_s.startValue_f32 = f_valueRqst_f32;
        }
        else if((delta_f32 < (t_float32)0)
        && (f_rampInfo_ps->previousValue_f32 >= f_rampInfo_ps->Info_u.linear_s.startValue_f32))
        {
            f_rampInfo_ps->Info_u.sigmoidale_s.startValue_f32 = f_rampInfo_ps->previousValue_f32;
        }
        
        midTime_f32 = (f_rampInfo_ps->Info_u.sigmoidale_s.startValue_f32 * f_rampInfo_ps->Info_u.sigmoidale_s.midPoint_f32 / (t_float32)100);
        cstK_f32 = 0.01 + (f_valueRqst_f32 - f_rampInfo_ps->previousValue_f32) / (t_float32)f_rampInfo_ps->maxDuration_u32 * 0.5;
        //--- Increase Mode ---//
        if (f_valueRqst_f32 < f_rampInfo_ps->previousValue_f32)
        {
            normalizedTime_f32 = (t_float32)((f_rampInfo_ps->previousValue_f32 - midTime_f32) * (cstK_f32));   
        }
        //--- Decrease Mode ---//
        else
        {
            normalizedTime_f32 = (t_float32)(-(f_rampInfo_ps->previousValue_f32 - midTime_f32) * (cstK_f32));
        }

        if(fabs(normalizedTime_f32) > 3)
        {
            normalizedTime_f32 = (t_float32)3.0;
        }
        //--- Compute Value ---//
        sigmoidalValue_f32 = (t_float32)((t_float32)1.0f / ((t_float32)1.0f + (t_float32)exp(-normalizedTime_f32)));

        f_rampInfo_ps->previousValue_f32 = f_rampInfo_ps->previousValue_f32 + 
                                            (f_valueRqst_f32 - f_rampInfo_ps->previousValue_f32) * sigmoidalValue_f32;

        //--- To avoid 0.0000001 or reverse wwith max value ---//
        if(fabs(f_valueRqst_f32 - f_rampInfo_ps->previousValue_f32) < (t_float32)1)
        {
            f_rampInfo_ps->previousValue_f32 = f_valueRqst_f32;
        }

        //--- Copy data ---//
        *f_ComputeValue_pf32 = f_rampInfo_ps->previousValue_f32;
    }*/
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
