/*********************************************************************
 * @file        APPACT_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSDM_CONFIGPUBLIC_H_INCLUDED
#define APPSDM_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPSDM_BROADCAST_TIMEOUT ((t_uint32)1000) /**< Every Second  */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Enum: Start */
    /**
    * @brief Enum for Diagnostic Item
    */
    typedef enum __t_eAPPSDM_DiagnosticItem
    {
        APPSDM_DIAG_ITEM_AAAAA = 0x00,
        APPSDM_DIAG_ITEM_BBBBB,
        APPSDM_DIAG_ITEM_CCCCC,
        APPSDM_DIAG_ITEM_DDDD,
        APPSDM_DIAG_ITEM_NB,
    } t_eAPPSDM_DiagnosticItem;
    /* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//


    typedef enum 
    {
        APPSDM_DIAG_STRAT_NONE = -1,

        APPSDM_DIAG_STRAT_NB,
    } t_eAPPSDM_DiagnosticStrat;
	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    typedef struct
    {
        t_uint16 debuncValueMs_u16;
        t_bool notifyUser_b;
        t_bool logItem_b;
        t_eAPPSDM_DiagnosticStrat diagStrat_e;
    }t_sAPPSM_DiagItemCfg;
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

#endif // APPSDM_CONFIGPUBLIC_H_INCLUDED           
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
