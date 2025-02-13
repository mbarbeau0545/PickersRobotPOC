/*********************************************************************
 * @file        APPSYS_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSDM_CONFIGSPECIFIC_H_INCLUDED
#define APPSDM_CONFIGSPECIFIC_H_INCLUDED





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
    typedef enum 
    {
        APPSDM_DIAG_STRAT_INHIBIT_OFF = 0x00,
        APPSDM_DIAG_STRAT_INHIBIT_ON,

        APPSDM_DIAG_STRAT_INHIBIT_NB
    } t_eAPPSDM_DiagStratOpe;
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
    //                      Public functions - Prototyupe
    //********************************************************************************
    /* CAUTION : Automatic generated code section for Diag Strategy Function Declaration: Start */
    /**
    * @brief Stratefy Function : Set All Axe of the Gantry Off 
    */
    void APPSDM_SPEC_DiagStrat_Gantry_Off(t_eAPPSDM_DiagStratOpe f_stratOpe_e);

    /**
    * @brief Stratefy Function : Set Axe X of the Gantry Off
    */
    void APPSDM_SPEC_DiagStrat_Gantry_Axe_X_Off(t_eAPPSDM_DiagStratOpe f_stratOpe_e);

    /**
    * @brief Stratefy Function : Set Axe Y of the Gantry Off
    */
    void APPSDM_SPEC_DiagStrat_Gantry_Axe_Y_Off(t_eAPPSDM_DiagStratOpe f_stratOpe_e);

    /**
    * @brief Stratefy Function : Set Axe Z of the Gantry Off
    */
    void APPSDM_SPEC_DiagStrat_Gantry_Axe_Z_Off(t_eAPPSDM_DiagStratOpe f_stratOpe_e);

    /* CAUTION : Automatic generated code section for Diag Strategy Function Declaration: End */
   

#endif // APPSDM_CONFIGSPECIFIC_H_INCLUDED           
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
