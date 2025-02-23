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
#include "./APPSNS_SPEC_Lim_Swch_Y_Max.h"
/* CAUTION : Automatic generated code section for Include: End */
#include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
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
static const t_eFMKIO_InDigSig c_LimSwSig_e = FMKIO_INPUT_SIGDIG_6;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Specific Function Implementation: Start */


/******************************************
* APPSNS_SPEC_Lim_Swch_Y_Max_SetCfg
******************************************/
t_eReturnCode APPSNS_SPEC_Lim_Swch_Y_Max_SetCfg(void)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Lim_Swch_Y_Max_SetSnsCfg here
    Ret_e = FMKIO_Set_InDigSigCfg(  c_LimSwSig_e,
                                    FMKIO_PULL_MODE_DOWN);


    return Ret_e;
}



/******************************************
* APPSNS_SPEC_Lim_Swch_Y_Max_GetSigValue
******************************************/
t_eReturnCode APPSNS_SPEC_Lim_Swch_Y_Max_GetSigValue(t_float32 *f_rawSigValue_pf32, t_bool * f_isValue_OK)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Lim_Swch_Y_Max_GetSigValue here
    t_eFMKIO_DigValue digValue_e;

    Ret_e = FMKIO_Get_InDigSigValue(c_LimSwSig_e, &digValue_e);

    if(Ret_e == RC_OK)
    {
        *f_rawSigValue_pf32 = (t_float32)digValue_e;
        *f_isValue_OK = (t_bool)True;
    }
    else 
    {   
        *f_rawSigValue_pf32 = (t_float32)0.0;
        *f_isValue_OK = (t_bool)False;
    }

    return Ret_e;
}



/******************************************
* APPSNS_SPEC_Lim_Swch_Y_Max_FormatValue
******************************************/
t_eReturnCode APPSNS_SPEC_Lim_Swch_Y_Max_FormatValue(t_float32  rawValue_f32, t_float32 *SnsValue_f32)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Lim_Swch_Y_Max_FormatValSI here
    *SnsValue_f32 = rawValue_f32;


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
