/*********************************************************************
 * @file        APPACT_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef GANTRY_CONFIGPUBLIC_H_INCLUDED
#define GANTRY_CONFIGPUBLIC_H_INCLUDED

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
    typedef enum 
    {
        GTRY_SFM_GANTRY_PRE_PRODUCTION = 0x00,
        GTRY_SFM_GANTRY_PRODUCTION,
        GTRY_SFM_GANTRY_PAUSE,
        GTRY_SFM_GANTRY_DEFAULT,

        GTRY_SFM_GANTRY_NB,
    } t_eGTRY_FSMGantry;

    typedef enum        
    {
        GTRY_FSM_PROD_SEO = 0x00,   /**< Production SEO (Referencement) */
        GTRY_FSM_PROD_AC,           /**< Production Application Control */

        GTRY_SFM_PROD_NB,
    } t_eGTRY_FSMProduction;

    typedef enum 
    {
        GTRY_FSM_PAUSE_NB = 0x00,
    } t_eGTRY_FSMPause;

    typedef enum 
    {
        GTRY_FSM_FAILURE_NB = 0x00,
    } t_eGTRY_FSMFailure;
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

#endif // GANTRY_CONFIGPUBLIC_H_INCLUDED           
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
