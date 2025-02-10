/**
 * @file        CL42T_ConfigPrivate.h
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef APPLGC_CONFIGPRIVATE_H_INCLUDED
#define APPLGC_CONFIGPRIVATE_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPLGC_ConfigPublic.h"
    #include "APP_CFG/ConfigFiles/APPACT_ConfigPublic.h"

    #include "APP_LGC/Src/Agents/Gantry/Src/Gantry.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
 
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
   
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
    /**
    * @brief Agent Configuration Function
    */
    const t_sAPPLGC_AgentFunc c_AppLGc_AgentFunc_apf[APPLGC_AGENT_NB] ={
        {Gantry_Init,                       Gantry_Cyclic},// APPLGC_AGENT_GANTRY
    };

    /**
    * @brief Service Max Actuators values 
    */
    const t_uint8 c_AppLGc_SrvActuatorsMax_ua8[APPLGC_SRV_NB] = {
        (t_uint8)APPLGC_SRV_GANTRY_X_ACT_NB,
        (t_uint8)APPLGC_SRV_GANTRY_Y_ACT_NB,
        (t_uint8)APPLGC_SRV_GANTRY_Z_ACT_NB,
    };

    /**
    * @brief Variable for Actuators/Service Mapping
    */
        const t_eAPPACT_Actuators c_AppLgc_ActServiceGantry_XMapp_ae[APPLGC_SRV_GANTRY_X_ACT_NB]= {
        APPACT_ACTUATOR_MOTOR_AXE_X_LEFT_STATE,
        APPACT_ACTUATOR_MOTOR_AXE_X_LEFT_DIR,
        APPACT_ACTUATOR_MOTOR_AXE_X_LEFT_PULSE,
        APPACT_ACTUATOR_MOTOR_AXE_X_RIGHT_STATE,
        APPACT_ACTUATOR_MOTOR_AXE_X_RIGHT_DIR,
        APPACT_ACTUATOR_MOTOR_AXE_X_RIGHT_PULSE,
    };

    /**
    * @brief Variable for Actuators/Service Mapping
    */
        const t_eAPPACT_Actuators c_AppLgc_ActServiceGantry_YMapp_ae[APPLGC_SRV_GANTRY_Y_ACT_NB]= {
        APPACT_ACTUATOR_MOTOR_AXE_Y_STATE,
        APPACT_ACTUATOR_MOTOR_AXE_Y_DIR,
        APPACT_ACTUATOR_MOTOR_AXE_Y_PULSE,
    };

    /**
    * @brief Variable for Actuators/Service Mapping
    */
        const t_eAPPACT_Actuators c_AppLgc_ActServiceGantry_ZMapp_ae[APPLGC_SRV_GANTRY_Z_ACT_NB]= {
        APPACT_ACTUATOR_MOTOR_AXE_Z_STATE,
        APPACT_ACTUATOR_MOTOR_AXE_Z_DIR,
        APPACT_ACTUATOR_MOTOR_AXE_Z_PULSE,
    };

    /**
    * @brief Service Actuators Variable Mapping
    */
    const t_eAPPACT_Actuators  * c_AppLGc_SrvDepedencies_pae[APPLGC_SRV_NB] ={
        (t_eAPPACT_Actuators *)(&c_AppLgc_ActServiceGantry_XMapp_ae),
        (t_eAPPACT_Actuators *)(&c_AppLgc_ActServiceGantry_YMapp_ae),
        (t_eAPPACT_Actuators *)(&c_AppLgc_ActServiceGantry_ZMapp_ae),
    };

    /* CAUTION : Automatic generated code section for Variable: End */
    
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    
#endif // APPLGC_CONFIGPRIVATE_H_INCLUDED
//************************************************************************************
// End of File
//************************************************************************************

/**
 *	@brief
 *	@note   
 *
 *
 *	@param[in] 
 *	@param[in]
 *	 
 *
 *
 */
