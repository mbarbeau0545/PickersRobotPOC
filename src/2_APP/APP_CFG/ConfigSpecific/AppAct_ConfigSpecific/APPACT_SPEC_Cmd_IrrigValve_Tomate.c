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
#include "./APPACT_SPEC_Cmd_IrrigValve_Tomate.h"
/* CAUTION : Automatic generated code section for Include: End */
#include "./FMK_HAL/FMK_IO/Src/FMK_IO.h"
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
static const t_eFMKIO_OutDigSig c_InputSig_e = FMKIO_OUTPUT_SIGPWM_5;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Specific Function Implementation: Start */


/******************************************
* APPACT_SPEC_Cmd_IrrigValve_Tomate_SetCfg
******************************************/
t_eReturnState APPACT_SPEC_Cmd_IrrigValve_Tomate_SetCfg(void)
{
    t_eReturnState Ret_e = RC_OK;
    //    Your code for Cmd_IrrigValve_Tomate_SetActCfg here
    //Ret_e = FMKIO_Set_OutPwmSigCfg(c_InputSig_e, 
    //                                FMKIO_PULL_MODE_DISABLE,
    //                                200,
    //                                500,
    //                                False,
    //                                NULL_FONCTION);
//
    return Ret_e;
}



/******************************************
* APPACT_SPEC_Cmd_IrrigValve_Tomate_GetValue
******************************************/
t_eReturnState APPACT_SPEC_Cmd_IrrigValve_Tomate_GetValue(t_sAPPACT_ValueInfo *f_value_ps)
{
    t_eReturnState Ret_e = RC_OK;
    //    Your code for Cmd_IrrigValve_Tomate_GetActValue here
    t_uint16 value_u16 = 0;
    Ret_e = FMKIO_Get_OutPwmSigValue(c_InputSig_e, &value_u16);
    f_value_ps->rawValue_f32 = (t_sint16)value_u16;

    return Ret_e;
}



/******************************************
* APPACT_SPEC_Cmd_IrrigValve_Tomate_SetValue
******************************************/
t_eReturnState APPACT_SPEC_Cmd_IrrigValve_Tomate_SetValue(t_sint16 f_value_s16)
{
    t_eReturnState Ret_e = RC_OK;
    //    Your code for Cmd_IrrigValve_Tomate_SetActValue here
    Ret_e = FMKIO_Set_OutPwmSigValue(c_InputSig_e, 500);


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
