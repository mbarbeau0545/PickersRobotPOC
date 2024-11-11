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
#include "./APPACT_SPEC_Cmd_IrrigValve_Carotte.h"
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
static const t_eFMKIO_OutDigSig c_InputSig_e = FMKIO_INPUT_SIGDIG_1;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Specific Function Implementation: Start */


/******************************************
* APPACT_SPEC_Cmd_IrrigValve_Carotte_SetCfg
******************************************/
t_eReturnState APPACT_SPEC_Cmd_IrrigValve_Carotte_SetCfg(void)
{
    t_eReturnState Ret_e = RC_OK;
    //    Your code for Cmd_IrrigValve_Carotte_SetActCfg here
    //Ret_e = FMKIO_Set_OutDigSigCfg(c_InputSig_e, FMKIO_PULL_MODE_DISABLE, FMKIO_SPD_MODE_LOW);


    return Ret_e;
}



/******************************************
* APPACT_SPEC_Cmd_IrrigValve_Carotte_GetValue
******************************************/
t_eReturnState APPACT_SPEC_Cmd_IrrigValve_Carotte_GetValue(t_sAPPACT_ValueInfo *f_value_ps)
{
    t_eReturnState Ret_e = RC_OK;
    t_eFMKIO_DigValue value_e;
    //    Your code for Cmd_IrrigValve_Carotte_GetActValue here
    Ret_e = FMKIO_Get_OutDigSigValue(c_InputSig_e, &value_e);
    if(Ret_e == RC_OK)
    {
        f_value_ps->IsValueOK_b = True;
        f_value_ps->rawValue_f32 = value_e;
    }
    else
    {
        f_value_ps->IsValueOK_b = False;
        f_value_ps->rawValue_f32 = value_e;
    }

    return Ret_e;
}



/******************************************
* APPACT_SPEC_Cmd_IrrigValve_Carotte_SetValue
******************************************/
t_eReturnState APPACT_SPEC_Cmd_IrrigValve_Carotte_SetValue(t_sint16 f_value_s16)
{
    t_eReturnState Ret_e = RC_OK;
    t_eFMKIO_DigValue value_e;
    //    Your code for Cmd_IrrigValve_Carotte_GetActValue here
    value_e = (t_eFMKIO_DigValue)f_value_s16;
    Ret_e = FMKIO_Set_OutDigSigValue(c_InputSig_e, value_e);
    if(Ret_e == RC_OK)
    {
       f_value_s16 = value_e;
    }
    else
    {
        f_value_s16 = value_e;
    }

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
