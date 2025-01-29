/*********************************************************************
 * @file        TemplateName.c
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
/* CAUTION : Automatic generated code section for Include: Start */
#include "./APPACT_SPEC_Motor_1_Pulse.h"
/* CAUTION : Automatic generated code section for Include: End */
#include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
#include "Motor/CL42T/Src/CL42T.h"
#include "APP_CFG/ConfigFiles/CL42T_ConfigPublic.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
/* CAUTION : Automatic generated code section for Include: Start */

/* CAUTION : Automatic generated code section for Include: End */
// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//


/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
static const t_eCL42T_MotorId c_IdMotor_e = CL42T_MOTOR_AXE_X_1;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
static void s_APPACT_SPEC_Motor_1_Pulse_Diag(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_DefeultInfo_e);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Specific Function Implementation: Start */


/******************************************
* APPACT_SPEC_Motor_1_Pulse_SetCfg
******************************************/
t_eReturnCode APPACT_SPEC_Motor_1_Pulse_SetCfg(void)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Motor_1_Pulse_SetActCfg here
    Ret_e = CL42T_AddMotorConfiguration(c_IdMotor_e,
                                        c_CL42T_MotorConfig_as[c_IdMotor_e],
                                        s_APPACT_SPEC_Motor_1_Pulse_Diag);


    return Ret_e;
}



/******************************************
* APPACT_SPEC_Motor_1_Pulse_GetValue
******************************************/
t_eReturnCode APPACT_SPEC_Motor_1_Pulse_GetValue(t_sAPPACT_ValueInfo *f_value_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uCL42T_MotorValue motorValue_u;
    //    Your code for Motor_1_Pulse_GetActValue here
    Ret_e = CL42T_GetMotorSigValue(c_IdMotor_e,
                                    CL42T_MOTOR_SIGTYPE_PULSE,
                                    &motorValue_u);

    if(Ret_e == RC_OK)
    {
        f_value_ps->IsValueOK_b = True;
        f_value_ps->rawValue_f32 = (t_float32)motorValue_u.nbPulses_u16;
    }
    else 
    {
        f_value_ps->IsValueOK_b = False;
        f_value_ps->rawValue_f32 = (t_float32)0;
    }


    return Ret_e;
}



/******************************************
* APPACT_SPEC_Motor_1_Pulse_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_Motor_1_Pulse_SetValue(t_sint16 f_value_s16)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Motor_1_Pulse_SetActValue here
    t_uCL42T_MotorValue motorValue_u;

    motorValue_u.nbPulses_u16 = f_value_s16;
    Ret_e = CL42T_SetMotorSigValue( c_IdMotor_e,
                                    CL42T_MOTOR_SIGTYPE_PULSE,
                                    motorValue_u);

    return Ret_e;
}

/* CAUTION : Automatic generated code section for Specific Function Implementation: End */


//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
static void s_APPACT_SPEC_Motor_1_Pulse_Diag(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_DefeultInfo_e)
{
    return ;
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
