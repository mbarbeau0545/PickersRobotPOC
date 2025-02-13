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
#include "./APPACT_SPEC_Mtr_X_L.h"
/* CAUTION : Automatic generated code section for Include: End */
#include "Motor/CL42T/Src/CL42T.h"
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

//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Specific Function Implementation: Start */


/******************************************
* APPACT_SPEC_Mtr_X_L_SetCfg
******************************************/
t_eReturnCode APPACT_SPEC_Mtr_X_L_SetCfg(void)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Mtr_X_L_SetActCfg here



    return Ret_e;
}



/******************************************
* APPACT_SPEC_Mtr_X_L_GetValue
******************************************/
t_eReturnCode APPACT_SPEC_Mtr_X_L_GetValue(t_uAPPACT_GetValue *f_value_pu)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Mtr_X_L_GetActValue here



    return Ret_e;
}



/******************************************
* APPACT_SPEC_Mtr_X_L_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_Mtr_X_L_SetValue(t_uAPPACT_SetValue f_value_u)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Mtr_X_L_SetActValue here
    Ret_e = CL42T_SetMotorSigValue(CL42T_MOTOR_AXE_X_1, f_value_u.Motor_s);


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
