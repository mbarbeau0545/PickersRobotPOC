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
    #define GTRY_MTR_X_L_DIR ((t_sint32)1)
    #define GTRY_MTR_X_R_DIR ((t_sint32)-1)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//

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

    typedef enum 
    {
        GTRY_MISSION_SUCCEED = 0x00,
        GTRY_MISSION_FAIL,
        GTRY_MISSION_READY,
        GTRY_MISSION_BUSY,
    } t_eGTRY_MissionStatus;
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
