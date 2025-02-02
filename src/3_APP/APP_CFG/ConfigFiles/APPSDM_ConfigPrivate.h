/*********************************************************************
 * @file        APPACT_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSDM_CONFIGPRIVATE_H_INCLUDED
#define APPSDM_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPSDM_ConfigPublic.h"
    #include "APP_CFG/ConfigSpecific/APPSDM_ConfigSpecific.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPSDM_MAX_DIAG_ITEM_MONITORING ((t_uint8)10)
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
	
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	
    /**
    *
    *	@brief      Function to inhibit actuators or sysfunction
    *
    *
    * @retval RC_OK                             @ref RC_OK
    *
    */
    typedef void (t_cbAPPSDM_AppliedDiagStrategy)(t_eAPPSDM_DiagStratOpe f_diagStratOpe_e);
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    /**
    * @brief Diagnostic Item Configuration
    */
    t_sAPPSM_DiagItemCfg c_AppSdm_DiagItemCfg_as[APPSDM_DIAG_ITEM_NB] ={
        // DebuncerValueMs                        NotifyUser                     Log Error                      Applied Startegy
        {(t_uint16)1000,                          True,                          False,                         APPSDM_DIAG_STRAT_NONE},  // APPSDM_DIAG_ITEM_AAAAA
        {(t_uint16)2000,                          True,                          False,                         APPSDM_DIAG_STRAT_NONE},  // APPSDM_DIAG_ITEM_BBBBB
        {(t_uint16)3000,                          True,                          False,                         APPSDM_DIAG_STRAT_NONE},  // APPSDM_DIAG_ITEM_CCCCC
        {(t_uint16)4000,                          True,                          False,                         APPSDM_DIAG_STRAT_NONE},  // APPSDM_DIAG_ITEM_DDDD
    };

    /* CAUTION : Automatic generated code section for Variable: End */

    t_cbAPPSDM_AppliedDiagStrategy * c_AppSdm_DiagStragies_pf[APPSDM_DIAG_STRAT_NB] = {

    };
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPSDM_CONFIGPRIVATE_H_INCLUDED           
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
