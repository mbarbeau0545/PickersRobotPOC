/*********************************************************************
 * @file        FMKCDA_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKCDA_CONFIGPRIVATE_H_INCLUDED
#define FMKCDA_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    
    #include "stm32g4xx_hal.h"
    #include "./FMKCDA_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    /* CAUTION : Automatic generated code section for ADC channels number: Start */
    #define FMKCDA_ADC_INTERN_VREFINT_CAL_ADDRESS ((volatile t_uint16 *)0x1FFF75AA)
    #define FMKCDA_ADC_INTERN_TS_CAL1_ADDRESS ((volatile t_uint16*)0x1FFF75A8)
    #define FMKCDA_ADC_INTERN_TS_CAL2_ADDRESS ((volatile t_uint16*)0x1FFF75CA)
    #define FMKCDA_ADC_1_MAX_CHANNELS ((t_uint8)18)
    #define FMKCDA_ADC_2_MAX_CHANNELS ((t_uint8)18)
    #define FMKCDA_ADC_3_MAX_CHANNELS ((t_uint8)18)
    #define FMKCDA_ADC_4_MAX_CHANNELS ((t_uint8)18)
    #define FMKCDA_ADC_5_MAX_CHANNELS ((t_uint8)18)
    /* CAUTION : Automatic generated code section for ADC channels number: End */

    #define FMKCDA_TIME_BTWN_DIAG_MS ((t_uint16)2000)   /**< Time between diagnostic for adc & dac channel in cyclic ope mode*/
    #define FMKCDA_OVR_CONVERSION_MS ((t_uint32)500)    /**< Delay after considering there is no conversion in circular mode  */
    #define FMKCDA_CYCLIC_CALIB      ((t_uint16)2000)   /**< Time between we get the Vref for calibration */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------TYPEDEF TYPES---------------------------//
    
    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    typedef struct 
    {
        t_eFMKCDA_Adc adc_e;
        t_eFMKCDA_AdcChannel chnl_e;
    } t_sFMKCDA_HwAdcCfg;
    
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    /**< Variable for Adc Max channel*/
    const t_uint8 c_FmkCda_AdcMaxChnl_ua8[FMKCDA_ADC_NB] = {
        (t_uint8)FMKCDA_ADC_1_MAX_CHANNELS,
        (t_uint8)FMKCDA_ADC_2_MAX_CHANNELS,
        (t_uint8)FMKCDA_ADC_3_MAX_CHANNELS,
        (t_uint8)FMKCDA_ADC_4_MAX_CHANNELS,
        (t_uint8)FMKCDA_ADC_5_MAX_CHANNELS,
    };

    /**<     Variable for voltage ref calibration value */
    const volatile t_uint16* c_FmkCda_VrefCalibAddress_pas16[FMKCDA_ADC_NB] = {
        (volatile t_uint16 *)FMKCDA_ADC_INTERN_VREFINT_CAL_ADDRESS,                       // FMKCDA_ADC_1
    };

    /**< Variable for Hardware configuration adc and channel for Voltage Reference for each adc */
    const t_sFMKCDA_HwAdcCfg c_FmkCda_HwVrefCfg[FMKCDA_ADC_NB] = {
        {FMKCDA_ADC_1,                         FMKCDA_ADC_CHANNEL_17},                // for FMKCDA_ADC_1
    };

    /**< Variable for Interna Sensors configuration*/
    const t_sFMKCDA_HwAdcCfg c_FmkCda_HwInternalSnsCfg[FMKCDA_ADC_INTERN_NB] ={
        {FMKCDA_ADC_1,                         FMKCDA_ADC_CHANNEL_16},                // for FMKCDA_ADC_INTERN_TS
        {FMKCDA_ADC_5,                         FMKCDA_ADC_CHANNEL_4},                 // for FMKCDA_ADC_INTERN_TS
    };

    /**< Variable for Internal Sensors Calibration address */
    const volatile t_uint16* c_FmkCda_HwInternalSnsAddress_pas16[FMKCDA_ADC_INTERN_NB] = {
        (volatile t_uint16 *)FMKCDA_ADC_INTERN_TS_CAL1_ADDRESS,                           // FMKCDA_ADC_INTERN_TS
        (volatile t_uint16 *)FMKCDA_ADC_INTERN_TS_CAL2_ADDRESS,                           // FMKCDA_ADC_INTERN_TS
    };

    /* CAUTION : Automatic generated code section for Variable: End */
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKCDA_CONFIGPRIVATE_H_INCLUDED           
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@note   
 *
 *
 *	@params[in] 
 *	@params[out]
 *	 
 *
 *
 */
