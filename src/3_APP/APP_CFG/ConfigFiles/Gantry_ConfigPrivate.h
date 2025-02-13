/*********************************************************************
 * @file        APPACT_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef GANTRY_CONFIGPRIVATE_H_INCLUDED
#define GANTRY_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPLGC_ConfigPublic.h"
    #include "./Gantry_ConfigPublic.h"
    #include "./APPSNS_ConfigPublic.h"

    #include "APP_LGC/Src/Agents/Gantry/Src/GantryMotionControl/Src/GMCAC.h"
    #include "APP_LGC/Src/Agents/Gantry/Src/GantryMotionControl/Src/GMCR.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define GTRY_SNS_LIMSWITCH_NB ((t_uint8)8) /**< Number of Limits Switch Used */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//
    typedef enum 
    {
        GTRY_MISSION_SUCCEED = 0x00,
        GTRY_MISSION_FAIL,
        GTRY_MISSION_READY,
    } t_eGTRY_MissionStatus;

	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	//-----------------------------TYPEDEF TYPES---------------------------//
	
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    const t_sAPPLGC_FSM_Func c_Gtry_SFMProdFunc_as[GTRY_SFM_PROD_NB] = 
    {// Init            Cyclic              EnterMode               ExitMode
        {GMCR_Init,      GMCR_Cyclic,        GMCR_EnterMode,         GMCR_ExitMode},
        {GMCAC_Init,     GMCAC_Cyclic,       GMCAC_EnterMode,        GMCAC_ExitMode},
    };

    const t_eAPPSNS_Sensors c_Gtry_LimSwitchIdx_ae[8] = {
        APPSNS_SENSOR_LIM_SWCH_X_L_MAX,
        APPSNS_SENSOR_LIM_SWCH_X_L_MIN,
        APPSNS_SENSOR_LIM_SWCH_X_R_MAX,
        APPSNS_SENSOR_LIM_SWCH_X_R_MIN,
        APPSNS_SENSOR_LIM_SWCH_Y_MAX,
        APPSNS_SENSOR_LIM_SWCH_Y_MIN,
        APPSNS_SENSOR_LIM_SWCH_Z_MAX,
        APPSNS_SENSOR_LIM_SWCH_Z_MIN,
    };
    /* CAUTION : Automatic generated code section for Variable: Start */

    /* CAUTION : Automatic generated code section for Variable: End */
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // GANTRY_CONFIGPRIVATE_H_INCLUDED           
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
