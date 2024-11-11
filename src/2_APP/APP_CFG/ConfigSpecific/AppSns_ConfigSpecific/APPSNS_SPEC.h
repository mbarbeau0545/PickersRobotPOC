/*********************************************************************
 * @file        APPSYS_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSNS_CONFIGSPECIFIC_H_INCLUDED
#define APPSNS_CONFIGSPECIFIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
	/* CAUTION : Automatic generated code section for Enum: Start */

	/* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//
    /**< enum for module list */

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
    //                      Public functions - Prototyupes
    //********************************************************************************
    /**
    *
    *	@brief      
    *	@note       
    *
    *
    *	@param[in]      
    *	@param[in]      
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *
    */
    t_eReturnState APPSNS_SPEC_ConvertTemperature(t_uint8 f_idxTempUnity_u8, 
                                                    t_sint16 f_rawVal_s16,
                                                    t_sint16 f_snsVal_s16);
   

#endif // APPSYS_CONFIGPUBLIC_H_INCLUDED           
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
