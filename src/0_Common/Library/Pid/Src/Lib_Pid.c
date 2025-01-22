/**
 * @file        
 * @brief       LIB PID CONTROL MODULE.
 * @note        TemplateDetailsDescription.!!!WARNING!!! THE ONLY FORMAT POSSIBLE IS F32 !!!WARNING!!!.\n
 *
 * @author      sde
 * @date        17/01/2025
 * @version     1.0
 */
// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./Lib_Pid.h"
#include "arm_math.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
typedef union 
{
    t_sLibPid_instance_f32 BspPidIstcF32_s;

} t_uLibPid_BspIstc;
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */

//-----------------------------ENUM TYPES-----------------------------//

/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
typedef struct
{
    t_uint16 Kd_s;
    t_uint16 Ki_s;
    t_uint16 Kp_s;
    t_eLibPid_FormatResult FormatResult_s;
    t_uLibPid_BspIstc BspIstc_u;
    t_bool IsConfigured_b;
} t_sLibPid_PidInfo; 

    

/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//

// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
static t_sLibPid_PidInfo g_PidInfo_as[LIBPID_MAX_USER_REGISTRATION];
static t_uint8 g_UserCpt_u8 = (t_uint8) 0;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
//**********************
// LIBPID_Create
//**********************
/**
 *	@brief          Configure Instance for PID\n
 *
 *	@param[in]      f_ParamCfg_s             : structure with value of Ki, Kp, Kd and the instance mode wanted\n
 *	@param[in]      f_userId_pu8             : id of PID instance from 0 to 14 
 *	@param[in]      f_ResetFlag_e            : reset flag is used to reset the PID State\n
 *  
 * 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_NOT_SUPPORTED            @ref RC_ERROR_NOT_SUPPORTED
 *  @retval RC_ERROR_LIMIT_REACHED            @ref RC_ERROR_LIMIT_REACHED
*/
static t_eReturnCode s_LibPid_ConfigIstc(t_sLibPid_ParamCfg * f_ParamCfg_s,
                                         t_uint8 f_userId_pu8,
                                         t_eLibPid_ResetState f_ResetFlag_e);

/**
 *	@brief          converted the state of ResetFlag into a t_uint32\n
 *
 *	@param[in]       f_ResetFlag_e             : Enum for the state of ResetFlag Disable or Enable\n
 *	@param[out]      f_ResetFlag_u32           : Storage for ResetFlag value in t_uint32
 * 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_NOT_SUPPORTED            @ref RC_ERROR_NOT_SUPPORTED
*/
static t_eReturnCode s_LibPid_GetBspResetFlag(  t_eLibPid_ResetState f_ResetFlag_e, 
                                                t_uint32 * f_ResetFlag_u32);

/**
 * @brief  Initialization function for the floating-point PID Control.
 * @param[in,out] f_Bsp_instance_ps               points to an instance of the PID structure.
 * @param[in]     f_resetStateFlag_s32  flag to reset the state. 0 = no change in state 1 = reset the state.
 */
static void s_LibPid_init_f32(  t_sLibPid_instance_f32 * f_Bsp_instance_ps,
                                t_sint32 f_resetStateFlag_s32);
/**
 * @brief  Reset function for the floating-point PID Control.
 * @param[in,out] S  is an instance of the floating-point PID Control structure
 */
static void s_LibPid_reset_f32(t_sLibPid_instance_f32 * f_Bsp_instance_ps);

static t_float32 s_LibPid_Compute_f32(  t_sLibPid_instance_f32 * f_Bsp_instance_ps,
                                        t_float32 f_value_f32);
//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
//**********************
// LIBPID_Create
//**********************
t_eReturnCode LibPid_InitPid(   t_sLibPid_ParamCfg f_ParamCfg_s,
                                t_eLibPid_ResetState f_ResetState_e,
                                t_uint8 * f_userId_pu8)
{
    t_eReturnCode Ret_e = RC_OK;


    if(f_userId_pu8 == (t_uint8 *) NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if( (f_ParamCfg_s.mode_e >= LIBPID_FORMAT_RESULT_NB) 
    ||  (f_ResetState_e >= LIBPID_RESET_STATE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_UserCpt_u8 > (t_uint8) LIBPID_MAX_USER_REGISTRATION)
    {
        Ret_e = RC_ERROR_LIMIT_REACHED;       
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_LibPid_ConfigIstc(&f_ParamCfg_s, 
                                    g_UserCpt_u8,
                                    f_ResetState_e);

        if(Ret_e == RC_OK)
        {
            *f_userId_pu8 = (t_uint8)g_UserCpt_u8;
            g_PidInfo_as[g_UserCpt_u8].IsConfigured_b = true;
            g_UserCpt_u8 += (t_uint8) 1;

        }

    }
     
     return Ret_e;
}

t_eReturnCode LibPid_ComputePid(t_uint8  f_userId_u8, 
                                t_float32 f_ValueToCompute_f32,
                                t_float32 * f_ValueComputed_pf32)

{
    t_eReturnCode Ret_e = RC_OK;
    t_sLibPid_PidInfo * PidInfo_ps;
    t_float32 BufferValueComputed_u32;

    if(f_userId_u8 > (t_uint8) LIBPID_MAX_USER_REGISTRATION)
    {
        Ret_e = RC_ERROR_LIMIT_REACHED;       
    }
    if(f_ValueComputed_pf32 == (t_float32 *) NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;   
    }
    if(Ret_e == RC_OK)
    {
        if(g_PidInfo_as[f_userId_u8].IsConfigured_b != true )
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
    }  
    if(Ret_e == RC_OK)
    { 

        PidInfo_ps = (t_sLibPid_PidInfo *)(&g_PidInfo_as[f_userId_u8]);

        switch (PidInfo_ps->FormatResult_s)
        {

            case LIBPID_FORMAT_RESULT_F32:

                BufferValueComputed_u32 = (t_float32)s_LibPid_Compute_f32(&PidInfo_ps->BspIstc_u.BspPidIstcF32_s,
                                                            f_ValueToCompute_f32);
                break;

            default:

                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }

        if(Ret_e == RC_OK)
        {
            *f_ValueComputed_pf32 = (t_float32) BufferValueComputed_u32;
        }
    }

    return Ret_e;
}

t_eReturnCode LibPid_ResetPid(t_uint8 f_userId_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sLibPid_PidInfo * PidInfo_ps;

    if(f_userId_u8 > (t_uint8) LIBPID_MAX_USER_REGISTRATION)
    {
        Ret_e = RC_ERROR_LIMIT_REACHED;       
    }
    if(Ret_e == RC_OK)
    {
        PidInfo_ps = (t_sLibPid_PidInfo *)(&g_PidInfo_as[f_userId_u8]);

        switch (PidInfo_ps->FormatResult_s)
        {
            case LIBPID_FORMAT_RESULT_F32:

                s_LibPid_reset_f32(&PidInfo_ps->BspIstc_u.BspPidIstcF32_s);
                break;

            default:

                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }
    
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
//**********************
// LIBPID_Create
//**********************
static t_eReturnCode s_LibPid_ConfigIstc(t_sLibPid_ParamCfg * f_ParamCfg_s,
                                         t_uint8 f_userId_u8,
                                         t_eLibPid_ResetState f_ResetFlag_e)
{
        t_float32 A0_f32;
        t_float32 A1_f32;
        t_float32 A2_f32;
        t_sLibPid_PidInfo * pidInfo_ps;
        t_eReturnCode Ret_e = RC_OK;
        t_uint32 BspResetFlag_u32; 


        if(f_userId_u8 > (t_uint8)LIBPID_MAX_USER_REGISTRATION)
        {
            Ret_e = RC_ERROR_LIMIT_REACHED;
        }
        if(f_ParamCfg_s == (t_sLibPid_ParamCfg *)NULL)
        {
            Ret_e = RC_ERROR_PTR_NULL;
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_LibPid_GetBspResetFlag(f_ResetFlag_e, &BspResetFlag_u32);
        }
        if(Ret_e == RC_OK)
        {   
            pidInfo_ps = (t_sLibPid_PidInfo *)(&g_PidInfo_as[f_userId_u8]);
            /**< The derived gain, A0 = Kp + Ki + Kd . */
            A0_f32 = (t_float32)(f_ParamCfg_s->Kd_u32 + f_ParamCfg_s->Ki_u32 + f_ParamCfg_s->Kp_u32);
            /**< The derived gain, A1 = -Kp - 2Kd. */
            A1_f32 = (t_float32)((t_float32)(-2)*f_ParamCfg_s->Kd_u32 - f_ParamCfg_s->Kp_u32); 
            /**< The derived gain, A2 = Kd . */
            A2_f32 = (t_float32)(f_ParamCfg_s->Kd_u32);

            switch(f_ParamCfg_s->mode_e){

                case LIBPID_FORMAT_RESULT_F32:

                    pidInfo_ps->BspIstc_u.BspPidIstcF32_s.A0 = (t_uint32) (A0_f32);
                    pidInfo_ps->BspIstc_u.BspPidIstcF32_s.A1 = (t_uint32) (A1_f32);
                    pidInfo_ps->BspIstc_u.BspPidIstcF32_s.A2 = (t_uint32) (A2_f32);
                    pidInfo_ps->BspIstc_u.BspPidIstcF32_s.Kd = (t_uint32)f_ParamCfg_s->Kd_u32;
                    pidInfo_ps->BspIstc_u.BspPidIstcF32_s.Ki = (t_uint32)f_ParamCfg_s->Ki_u32;
                    pidInfo_ps->BspIstc_u.BspPidIstcF32_s.Kp = (t_uint32)f_ParamCfg_s->Kp_u32;

                    s_LibPid_init_f32(&pidInfo_ps->BspIstc_u.BspPidIstcF32_s, BspResetFlag_u32);

                    break;

                default:

                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;
            }
        }

    return Ret_e;
}

static t_eReturnCode s_LibPid_GetBspResetFlag(  t_eLibPid_ResetState f_ResetFlag_e, 
                                                t_uint32 * f_ResetFlag_u32)
{

    t_eReturnCode Ret_e = RC_OK;

    if(f_ResetFlag_e >= LIBPID_RESET_STATE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_ResetFlag_u32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_ResetFlag_e)
        {
        case LIBPID_RESET_STATE_ENABLE:
            
            *f_ResetFlag_u32 = (t_uint32)0;
            break;

        case LIBPID_RESET_STATE_DISABLE:

            *f_ResetFlag_u32 = (t_uint32)1;
            break;   

        default:

            Ret_e = RC_ERROR_NOT_SUPPORTED;
            break;
        }
    }

    return Ret_e;
}

static void s_LibPid_init_f32(t_sLibPid_instance_f32 * f_Bsp_instance_ps,
    t_sint32 f_resetStateFlag_s32)
{
  /* Derived coefficient A0 */
  f_Bsp_instance_ps->A0 = f_Bsp_instance_ps->Kp + f_Bsp_instance_ps->Ki + f_Bsp_instance_ps->Kd;

  /* Derived coefficient A1 */
  f_Bsp_instance_ps->A1 = (-f_Bsp_instance_ps->Kp) - ((t_float32) 2.0 * f_Bsp_instance_ps->Kd);

  /* Derived coefficient A2 */
  f_Bsp_instance_ps->A2 = f_Bsp_instance_ps->Kd;

  /* Check whether state needs reset or not */
  if (f_resetStateFlag_s32)
  {
    /* Reset state to zero, The size will be always 3 samples */
    memset(f_Bsp_instance_ps->state, 0, 3U * sizeof(t_float32));
  }

}

static void s_LibPid_reset_f32(
    t_sLibPid_instance_f32 * f_Bsp_instance_ps)
{
  /* Reset state to zero, The size will be always 3 samples */
  memset(f_Bsp_instance_ps->state, 0, 3U * sizeof(t_float32));
}


static t_float32 s_LibPid_Compute_f32(
    t_sLibPid_instance_f32 * f_Bsp_instance_ps,
    t_float32 f_value_f32)
{
t_float32 out;

/* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
out = (f_Bsp_instance_ps->A0 * f_value_f32) +
    (f_Bsp_instance_ps->A1 * f_Bsp_instance_ps->state[0]) + (f_Bsp_instance_ps->A2 * f_Bsp_instance_ps->state[1]) + (f_Bsp_instance_ps->state[2]);

/* Update state */
f_Bsp_instance_ps->state[1] = f_Bsp_instance_ps->state[0];
f_Bsp_instance_ps->state[0] = f_value_f32;
f_Bsp_instance_ps->state[2] = out;

/* return to application */
return (out);

}
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
