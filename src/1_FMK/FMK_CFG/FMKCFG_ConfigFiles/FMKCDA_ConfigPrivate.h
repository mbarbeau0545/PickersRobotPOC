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
    #include "TypeCommon.h"
    #include "stm32f0xx_hal.h"
    #include "./FMKCDA_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    /* CAUTION : Automatic generated code section for ADC channels number: Start */
    #define FMKCDA_ADC_1_MAX_CHANNELS ((t_uint8)18)
    /* CAUTION : Automatic generated code section for ADC channels number: End */

    #define FMKCDA_TIME_BTWN_DIAG_MS ((t_uint16)2000) /**< Time between diagnostic for adc & dac channel in cyclic ope mode*/
    #define FMKCDA_OVR_CONVERSION_MS ((t_uint32)500)    /**< delay after considering there is no conversion in circular mode  */
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
