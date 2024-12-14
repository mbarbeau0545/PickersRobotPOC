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
    /* Enum for Actuators list */
    typedef enum
    {
        APPACT_ACTUATOR_CMD_IRRIGVALVE_TOMATE = 0x0,/**< Commande du relais pour irriger les tomates  */
        APPACT_ACTUATOR_CMD_IRRIGVALVE_COURGETTE, /**< Commande du relais pour irriger les courgettes */
        APPACT_ACTUATOR_CMD_IRRIGVALVE_CAROTTE,   /**< Commande du relais pour irriger les carottes */
    
        APPACT_ACTUATOR_NB,
    } t_eAPPACT_Actuators;

    /* Enum for Actuators drivers list */
    typedef enum
    {
    
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
        t_bool   IsValueOK_b;       /**< Flag value is OK */
    } t_sAPPACT_ValueInfo;
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
