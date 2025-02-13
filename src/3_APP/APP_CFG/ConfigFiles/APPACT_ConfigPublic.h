/*********************************************************************
 * @file        APPACT_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPACT_CONFIGPUBLIC_H_INCLUDED
#define APPACT_CONFIGPUBLIC_H_INCLUDED





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
    /**
    * @brief Enum for Actuators list.
    */
    typedef enum
    {
        APPACT_ACTUATOR_MTR_X_L_STATE = 0x0,      /**< Left Motor Axe X Commande for Motor State */
        APPACT_ACTUATOR_MTR_X_L_DIR,              /**< Left Motor Axe X Commande for Motor Direction */
        APPACT_ACTUATOR_MTR_X_L_PULSE,            /**< Left Motor Axe X Commande for Motor Pulses */
        APPACT_ACTUATOR_MTR_X_L_SPEED,             /**< Left Motor Axe X Commande for Motor Speed */
        APPACT_ACTUATOR_MTR_X_R_STATE,            /**< Right Motor Axe X Commande for Motor State */
        APPACT_ACTUATOR_MTR_X_R_DIR,              /**< Right Motor Axe X Commande for Motor Direction */
        APPACT_ACTUATOR_MTR_X_R_PULSE,            /**< Right Motor Axe X Commande for Motor Pulses */
        APPACT_ACTUATOR_MTR_X_R_SPEED,            /**< Left Motor Axe X_Right Commande for Motor Speed */
        APPACT_ACTUATOR_MTR_Y_STATE,              /**< Motor Axe Y Commande for Motor State */
        APPACT_ACTUATOR_MTR_Y_DIR,                /**< Motor Axe Y Commande for Motor Direction */
        APPACT_ACTUATOR_MTR_Y_PULSE,              /**< Motor Axe Y Commande for Motor Pulses */
        APPACT_ACTUATOR_MTR_Y_SPEED,              /**< Left Motor Axe Y Commande for Motor Speed */
        APPACT_ACTUATOR_MTR_Z_STATE,              /**< Motor Axe Z Commande for Motor State */
        APPACT_ACTUATOR_MTR_Z_DIR,                /**< Motor Axe Z Commande for Motor Direction */
        APPACT_ACTUATOR_MTR_Z_PULSE,              /**< Motor Axe Z Commande for Motor Pulses */
        APPACT_ACTUATOR_MTR_Z_SPEED,              /**< Left Motor Axe Z Commande for Motor Speed */
    
        APPACT_ACTUATOR_NB,
    } t_eAPPACT_Actuators;

    /**
    * @brief Enum for Actuators drivers list.
    */
    typedef enum
    {
        APPACT_DRIVER_CL42T = 0x0,              /**< Driver for Motor Variateur */
    
        APPACT_DRIVER_NB,
    } t_eAPPACT_Drivers;

    /* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//
    typedef enum 
    {
        APPACT_ACTUATOR_STATE_DISABLE = 0,    /**< The actuator is unused in a system configuration */
        APPACT_ACTUATOR_STATE_ENABLE,         /**< The actuator is used in a system configuration */
        APPACT_ACTUATOR_STATE_NB,             /**< Number of actuator state */
    } t_eAPPACT_ActuatorState;

    typedef enum 
    {
        APPACT_DRIVER_STATE_DISABLE = 0,      /**< The driver is used in a system configuration */
        APPACT_DRIVER_STATE_ENABLE,           /**< The driver is used in a system configuration */
        APPACT_DRIVER_STATE_NB,               /**< Number of driver state */
    } t_eAPPACT_DriverState;
	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    typedef struct
    {
        t_sint16 rawValue_f32;      /**< Store the actuators rawValue */
        t_bool   f_isValue_OK;       /**< Flag value is OK */
    } t_sAPPACT_ValueInfo;

    typedef struct 
    {
        
    }
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

#endif // APPACT_CONFIGPUBLIC_H_INCLUDED           
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
