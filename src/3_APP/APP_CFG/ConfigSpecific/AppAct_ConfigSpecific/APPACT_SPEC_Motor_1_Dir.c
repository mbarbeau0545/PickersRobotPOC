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
#include "./APPACT_SPEC_Motor_1_Dir.h"
/* CAUTION : Automatic generated code section for Include: End */

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
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Specific Function Implementation: Start */


/******************************************
* APPACT_SPEC_Motor_1_Dir_SetCfg
******************************************/
t_eReturnCode APPACT_SPEC_Motor_1_Dir_SetCfg(void)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Motor_1_Dir_SetActCfg here

    // Configuration already made in APPACT_Pulse

    return Ret_e;
}



/******************************************
* APPACT_SPEC_Motor_1_Dir_GetValue
******************************************/
t_eReturnCode APPACT_SPEC_Motor_1_Dir_GetValue(t_sAPPACT_ValueInfo *f_value_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eCL42T_MotorDirection motorDir_e;
    //    Your code for Motor_1_Dir_GetActValue here
    if(f_value_ps == (t_sAPPACT_ValueInfo *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = CL42T_GetDirSignal( c_motorId_e,
                                    &motorDir_e);

        if(Ret_e == RC_OK)
        {
            f_value_ps->IsValueOK_b = (t_bool)true;
            f_value_ps->rawValue_f32 = (t_float32)motorDir_e;
        }
        else 
        {
            f_value_ps->IsValueOK_b = (t_bool)false;
            f_value_ps->rawValue_f32 = (t_float32)0;
        }
    }

    return Ret_e;
}



/******************************************
* APPACT_SPEC_Motor_1_Dir_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_Motor_1_Dir_SetValue(t_sint16 f_value_s16)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Motor_1_Dir_SetActValue here



    return Ret_e;
}

/* CAUTION : Automatic generated code section for Specific Function Implementation: End */
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
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
