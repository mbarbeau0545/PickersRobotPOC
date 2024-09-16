/*********************************************************************
 * @file        APPSNS_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSNS_CONFIGPRIVATE_H_INCLUDED
#define APPSNS_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPSNS_ConfigPublic.h"
    /* CAUTION : Automatic generated code section for Include: Start */
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_AirTemperature.h"
    /* CAUTION : Automatic generated code section for Include: End */
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPSNS_CFG_NB_PER_CYCLE ((t_uint8)5)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
	/* CAUTION : Automatic generated code section for Enum: Start */

	/* CAUTION : Automatic generated code section for Enum: End */
    /* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    
	//-----------------------------ENUM TYPES-----------------------------//

    //-----------------------------TYPEDEF TYPES---------------------------//
    /**
    *
    *	@brief      Set a sensor configuration 

    */
    typedef t_eReturnState (t_cbAppSns_SetSnsCfg)(void);
    /**
    *
    *	@brief      get value for a sensor
    *
    *	@param[in] f_SnsValue_ps : structure to store value and validity
    *
    */
    typedef t_eReturnState (t_cbAppSns_GetSnsValue)(t_sAPPSNS_ValueInfo *f_SnsValue_ps);
    /**
    *
    *	@brief      Set the driver init function
    */
    typedef t_eReturnState (t_cbAppSns_DrvInit)(void);
    /**
    *
    *	@brief      Set the driver cyclic function
    *
    */
    typedef t_eReturnState (t_cbAppSns_DrvCyclic)(void);

	
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	/**< Structure to store needed functions for a sensor */
    typedef struct 
    {
        t_cbAppSns_SetSnsCfg      * SetCfg_pcb;         /**< Reference to "set config" function */
        t_cbAppSns_GetSnsValue    * GetValue_pcb;       /**< Reference to "get value" function */
    } t_sAPPSNS_SysSnsFunc;

    /**< Structure to store needed functions for a driver */
    typedef struct 
    {
        t_cbAppSns_DrvInit   * Init_pcb;
        t_cbAppSns_DrvCyclic * Cyclic_pcb;
    } t_sAPPSNS_SysDrvFunc;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    /**< Variable for System Sensors drivers functions*/
    const t_sAPPSNS_SysDrvFunc c_AppSns_SysDrv_apf[APPSNS_DRIVER_NB] = {
        {(t_cbAppSns_DrvInit *)FMKDRV_Sick_Init,                     (t_cbAppSns_DrvInit *)NULL_FONCTION},  // APPSNS_DRIVER_SICK
        {(t_cbAppSns_DrvInit *)FMKDRV_Kuber_Init,                    (t_cbAppSns_DrvCyclic *)FMKDRV_Kuber_Cyclic},  // APPSNS_DRIVER_KUBER
        {(t_cbAppSns_DrvInit *)NULL_FONCTION,                        (t_cbAppSns_DrvCyclic *)FMKDRV_MTS_Cyclic},  // APPSNS_DRIVER_MTS
    };

    /**< Variable for System Sensors functions*/
    const t_sAPPSNS_SysSnsFunc c_AppSns_SysSns_apf[APPSNS_SENSOR_NB] = {
        {APPSNS_SPEC_AirTemperature_SetCfg,                          APPSNS_SPEC_AirTemperature_GetValue}, //APPSNS_SENSOR_AIRTEMPERATURE
    };

    /**< Variable for Sensors Unity Management */
    const t_eAPPSNS_SnsMeasType c_AppSns_SnsMeasType_ae[APPSNS_SENSOR_NB] = {
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_AIRTEMPERATURE
    };

    /* CAUTION : Automatic generated code section for Variable: End */

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPSNS_CONFIGPRIVATE_H_INCLUDED           
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
