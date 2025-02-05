/**
 * @file        CL42T_ConfigPublic.h
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef CL42T_CONFIGPUBLIC_H_INCLUDED
#define CL42T_CONFIGPUBLIC_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    typedef enum 
    {
        CL42T_MOTOR_AXE_X_1,
        CL42T_MOTOR_AXE_X_2,

        CL42T_MOTOR_NB
    } t_eCL42T_MotorId;
    
    typedef enum 
    {
        CL42T_SIGTYPE_PULSE = 0x00,
        CL42T_SIGTYPE_SPEED,
        CL42T_SIGTYPE_DIR,
        CL42T_SIGTYPE_STATE,
        CL42T_SIGTYPE_DIAG,

        CL42T_SIGTYPE_NB
    } t_eCL42T_MotorSignalType;
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
   
    //-----------------------------STRUCT TYPES---------------------------//
    typedef struct 
    {
        t_eFMKIO_OutPwmSig PulseSignal_e;
        t_eFMKIO_PullMode PullMode_e;
        t_uint32 f_PulseInitFreq_u32;
    } t_sCL42T_PwmSignalCfg;

    typedef struct 
    {
        t_eFMKIO_OutDigSig  DigitalSignal_e;
        t_eFMKIO_PullMode   PullMode_e;
    } t_sCL42T_DigitalSignalCfg;

    typedef struct 
    {
        t_eFMKIO_InFreqSig  FreqSignal_e;
        t_eFMKIO_PullMode   PullMode_e;
    } t_sCL42T_FreqSignalCfg;

    typedef struct 
    {
        t_sCL42T_PwmSignalCfg       PulseSigCfg_s;
        t_sCL42T_DigitalSignalCfg   StateSigCfg;
        t_sCL42T_DigitalSignalCfg   DirSigCfg_s;
        t_sCL42T_FreqSignalCfg      DiagSigCfg_s;

    } t_sCL42T_MotorSigCfg;

    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /*const t_sCL42T_MotorSigCfg c_CL42T_MotorConfig_as[CL42T_MOTOR_NB] = {
        [CL42T_MOTOR_AXE_X_1] = {
            .PulseSigCfg_s = {
                .PulseSignal_e = FMKIO_OUTPUT_SIGPWM_8,
                .PullMode_e =  FMKIO_PULL_MODE_DISABLE,
                .f_PulseInitFreq_u32 = 0
            },
            .StateSigCfg = {
                .DigitalSignal_e = FMKIO_OUTPUT_SIGDIG_2,
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
            .DirSigCfg_s = {
                .DigitalSignal_e = FMKIO_OUTPUT_SIGDIG_1,
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
            .DiagSigCfg_s = {
                .FreqSignal_e = FMKIO_INPUT_SIGFREQ_1,
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
        },

        [CL42T_MOTOR_AXE_X_2] = {
            .PulseSigCfg_s = {
                .PulseSignal_e = FMKIO_OUTPUT_SIGPWM_4,
                .PullMode_e =  FMKIO_PULL_MODE_DISABLE,
                .f_PulseInitFreq_u32 = 0
            },
            .StateSigCfg = {
                .DigitalSignal_e = FMKIO_OUTPUT_SIGDIG_4,
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
            .DirSigCfg_s = {
                .DigitalSignal_e = FMKIO_OUTPUT_SIGDIG_5,
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
            .DiagSigCfg_s = {
                .FreqSignal_e = FMKIO_INPUT_SIGFREQ_2,
                .PullMode_e = FMKIO_PULL_MODE_DISABLE,
            },
        },
    };*/
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    
#endif // CL42T_CONFIGPUBLIC_H_INCLUDED
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
