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
#include "./APPACT_SPEC_Mtr_Z.h"
/* CAUTION : Automatic generated code section for Include: End */
#include "APP_CTRL/APP_SDM/Src/APP_SDM.h"
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
static const t_eCL42T_MotorId c_MotorId_e = CL42T_MOTOR_4;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
static void MtrZ_MotorDiagnostic(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_DefeultInfo_e);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/* CAUTION : Automatic generated code section for Specific Function Implementation: Start */


/******************************************
* APPACT_SPEC_Mtr_Z_SetCfg
******************************************/
t_eReturnCode APPACT_SPEC_Mtr_Z_SetCfg(void)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Mtr_Z_SetActCfg here
    t_sCL42T_MotorSigCfg MotorConfig_s = {
        .PulseSigCfg_s = {
            .PulseSignal_e = FMKIO_OUTPUT_SIGPWM_5,
            .PullMode_e =  FMKIO_PULL_MODE_DOWN,
            .f_PulseInitFreq_u32 = APPACT_DEFAULT_FREQ_MOTOR
        },
        .StateSigCfg = {
            .DigitalSignal_e = FMKIO_OUTPUT_SIGDIG_8, 
            .PullMode_e = FMKIO_PULL_MODE_DISABLE,
        },
        .DirSigCfg_s = {
            .DigitalSignal_e = FMKIO_OUTPUT_SIGDIG_5, 
            .PullMode_e = FMKIO_PULL_MODE_DISABLE,
        },
        .DiagSigCfg_s = {
            .FreqSignal_e = FMKIO_INPUT_SIGFREQ_4, 
            .PullMode_e = FMKIO_PULL_MODE_DISABLE,
        },
    };

    Ret_e = CL42T_AddMotorConfiguration(c_MotorId_e,
                                        MotorConfig_s,
                                        CL42T_PULSE_CHANGE_DIR_OPE_CANCEL,
                                        MtrZ_MotorDiagnostic);



    return Ret_e;
}



/******************************************
* APPACT_SPEC_Mtr_Z_GetValue
******************************************/
t_eReturnCode APPACT_SPEC_Mtr_Z_GetValue(t_uAPPACT_GetValue *f_value_pu)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Mtr_Z_GetActValue here
    Ret_e = CL42T_GetMotorSigValue(c_MotorId_e, (t_sCL42T_GetMotorValue *)(&f_value_pu->Motor_s));
    return Ret_e;
}



/******************************************
* APPACT_SPEC_Mtr_Z_SetValue
******************************************/
t_eReturnCode APPACT_SPEC_Mtr_Z_SetValue(t_uAPPACT_SetValue f_value_u)
{
    t_eReturnCode Ret_e = RC_OK;
    //    Your code for Mtr_Z_SetActValue here

    Ret_e = CL42T_SetMotorSigValue(c_MotorId_e, (t_sCL42T_SetMotorValue)(f_value_u.Motor_s));

    return Ret_e;
}

/* CAUTION : Automatic generated code section for Specific Function Implementation: End */
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
static void MtrZ_MotorDiagnostic(t_eCL42T_MotorId f_MotorID_e, t_eCL42T_DiagError f_DefeultInfo_e)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_MotorID_e != c_MotorId_e)
    {
        Ret_e = RC_WARNING_NO_OPERATION;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_DefeultInfo_e)
        {
            case CL42T_DIAGNOSTIC_OK:
            {
                Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_GTRY_AXE_Z_ERR,
                                                APPSDM_DIAG_ITEM_REPORT_PASS,
                                                (t_uint16)0,
                                                (t_uint16)0);
                break;
            }
            case CL42T_DIAGNOSTIC_PRESENTS:
            case CL42T_DIAGNOSTIC_OVER_CURRENT:
            case CL42T_DIAGNOSTIC_OVER_VOLTAGE:
            case CL42T_DIAGNOSTIC_CHIP_ERROR:
            case CL42T_DIAGNOSTIC_LOCK_MOTOR_SHAFT:
            case CL42T_DIAGNOSTIC_AUTO_TUNNING:
            case CL42T_DIAGNOSTIC_EEPROM:
            case CL42T_DIAGNOSTIC_POSITION:
            case CL42T_DIAGNOSTIC_PCB_BOARD:
            case CL42T_DIAGNOSTIC_SIGNAL_PULSE:
            case CL42T_DIAGNOSTIC_SIGNAL_DIG:
            case CL42T_DIAGNOSTIC_PULSE_INFINITE:
            {
                Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_GTRY_AXE_Z_ERR,
                                                APPSDM_DIAG_ITEM_REPORT_FAIL,
                                                (t_uint16)f_MotorID_e,
                                                (t_uint16)f_DefeultInfo_e);
                break;
            }
            case CL42T_DIAGNOSTIC_NB:
            default:
            {
                break;
            }
        }
    }
    return;
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
