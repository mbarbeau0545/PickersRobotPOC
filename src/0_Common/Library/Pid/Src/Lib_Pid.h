/**
 * @file        Lib_Pid.h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      sde
 * @date        17/01/2025
 * @version     1.0
 */
  
#ifndef LIB_PID_H_INCLUDED
#define LIB_PID_H_INCLUDED

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "TypeCommon.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define LIBPID_MAX_USER_REGISTRATION ((t_uint8) 14)
// ********************************************************************
// *                      Types
// ********************************************************************

//-----------------------------ENUM TYPES-----------------------------//

/* CAUTION : Automatic generated code section for Enum: Start */
typedef enum
{
    LIBPID_FORMAT_RESULT_F32, /**< */
    
    LIBPID_FORMAT_RESULT_NB,
} t_eLibPid_FormatResult;

typedef enum
{
    LIBPID_RESET_STATE_ENABLE, /**< Reset the state to 0*/
    LIBPID_RESET_STATE_DISABLE, /**< 1 */

    LIBPID_RESET_STATE_NB,
} t_eLibPid_ResetState;
/* CAUTION : Automatic generated code section for Enum: End */

//-----------------------------STRUCT TYPES---------------------------//

typedef struct 
{
    t_uint32   Kp_u32;       
    t_uint32   Ki_u32;       
    t_uint32   Kd_u32;        
    t_eLibPid_FormatResult mode_e;
            
} t_sLibPid_ParamCfg;

typedef struct
{
        t_float32 A0;          /**< The derived gain, A0 = Kp + Ki + Kd . */
        t_float32 A1;          /**< The derived gain, A1 = -Kp - 2Kd. */
        t_float32 A2;          /**< The derived gain, A2 = Kd . */
        t_float32 state[3];    /**< The state array of length 3. */
        t_float32 Kp;          /**< The proportional gain. */
        t_float32 Ki;          /**< The integral gain. */
        t_float32 Kd;          /**< The derivative gain. */
} t_sLibPid_instance_f32; 

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
*	@brief      Configure and initialize PID.
*   @note       User can choose if he want to reset the state or not with parameter ResetState. 
*               User can also choose what kind of format between Q15, Q31 and F32. 
*               He must give a structure with value of Ki, Kd, Kp and mode wanted 
*               function initialize the instance required and gives to user'instance an ID.
*               There is only LIBPID_MAX_USER_REGISTRATION instance ID possible otherwise the system will return an error
*               To use other function user need to transmit only the ID return by the function.
*               
*
*	@param[in]  f_ParamCfg_s          : structure with value of Ki, Kp, Kd and the instance mode wanted\n
*	@param[in]  f_ResetState_e        : reset flag is used to reset the PID State\n
*	@param[out] f_userId_pu8          : Storage for user ID
*
*   @retval RC_OK                             @ref RC_OK
*   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
*   @retval RC_ERROR_INSTANCE_NOT_INITIALIZED @ref RC_ERROR_INSTANCE_NOT_INITIALIZED
*   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*   @retval RC_ERROR_LIMIT_REACHED            @ref RC_ERROR_LIMIT_REACHED
*/
t_eReturnCode LibPid_InitPid(   t_sLibPid_ParamCfg f_ParamCfg_s,
                                t_eLibPid_ResetState f_ResetState_e,
                                t_uint8 * f_userId_pu8);
/**
*
*	@brief      Compute PID.
*   @note       User need to transmit user id of his PID instance. 
*               Then the value to compute and storage pointer for value computed
*               
*
*	@param[in]  f_userId_u8              : Storage for user ID
*	@param[in]  f_ValueToCompute_f32     : value to compute
*	@param[out] f_ValueComputed_pf32     : Storage for value computed
*
*   @retval RC_OK                             @ref RC_OK
*   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
*   @retval RC_ERROR_INSTANCE_NOT_INITIALIZED @ref RC_ERROR_INSTANCE_NOT_INITIALIZED
*   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*   @retval RC_ERROR_LIMIT_REACHED            @ref RC_ERROR_LIMIT_REACHED
*/
t_eReturnCode LibPid_ComputePid(t_uint8  f_userId_u8, 
                                t_float32 f_ValueToCompute_f32,
                                t_float32 * f_ValueComputed_pf32);
/**
*
*	@brief      Reset PID.
*   @note       User need to transmit user id of his PID instance. 
*               
*
*	@param[in]  f_userId_u8              : Storage for user ID
*
*   @retval RC_OK                             @ref RC_OK
*   @retval RC_ERROR_NOT_SUPPORTED            @ref RC_ERROR_NOT_SUPPORTED
*   @retval RC_ERROR_LIMIT_REACHED            @ref RC_ERROR_LIMIT_REACHED
*/
t_eReturnCode LibPid_ResetPid(t_uint8 f_userId_u8);   



#endif // LIBPID_H_INCLUDED
//************************************************************************************
// End of File
//************************************************************************************

/**
 *	@brief
*	@note   
*
*
*	@param[in] 
*	@param[in]
*	 
*
*
*/
