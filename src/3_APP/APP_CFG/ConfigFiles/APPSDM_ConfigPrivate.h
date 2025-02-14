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
    t_cbAPPSDM_AppliedDiagStrategy * c_AppSdm_DiagStragies_apf[APPSDM_DIAG_STRAT_NB]= {
        APPSDM_SPEC_DiagStrat_Gantry_Off,
        APPSDM_SPEC_DiagStrat_Gantry_Axe_X_Off,
        APPSDM_SPEC_DiagStrat_Gantry_Axe_Y_Off,
        APPSDM_SPEC_DiagStrat_Gantry_Axe_Z_Off,
    };

    /**
    * @brief Diagnostic Item Configuration
    */
    t_sAPPSM_DiagItemCfg c_AppSdm_DiagItemCfg_as[APPSDM_DIAG_ITEM_NB] ={
        // DebuncerValueMs                        NotifyUser                     Log Error                      Applied Startegy
    /**
    * @brief Variable for Diagnostic Item Information
    */
        {(t_uint16)0,                  (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_GANTRY_OFF},  // FMK_CFG_ERROR
        {(t_uint16)1000,               (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_GANTRY_OFF},  // FMK_OPE_ERROR
        {(t_uint16)0,                  (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_GANTRY_AXE_X_OFF},// GTRY_AXE_X_ERR
        {(t_uint16)0,                  (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_GANTRY_AXE_Y_OFF},// GTRY_AXE_Y_ERR
        {(t_uint16)1000,               (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_GANTRY_AXE_Z_OFF},// GTRY_AXE_Z_ERR
        {(t_uint16)500,                (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_GANTRY_OFF},  // SUPPLY_VOLTAGE_ERROR
        {(t_uint16)1500,               (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_GANTRY_OFF},  // APPSYS_CYCLIC_TIMEOUT
        {(t_uint16)250,                (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_GANTRY_OFF},  // APPUSER_BIT_ALIVE_TIMEOUT
        {(t_uint16)250,                (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_NONE},        // APPUSER_COMMUNICATION_FAILED
        {(t_uint16)0,                  (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_NONE},        // APPUSER_COM_CHECKSUM_FAILED
        {(t_uint16)0,                  (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_GANTRY_OFF},  // GANTRY_MVMT_ERROR
        {(t_uint16)0,                  (t_bool)True,                 (t_bool)False,                APPSDM_DIAG_STRAT_GANTRY_OFF},  // GANTRY_SWITCH_LIMIT
    };

    /* CAUTION : Automatic generated code section for Variable: End */
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
