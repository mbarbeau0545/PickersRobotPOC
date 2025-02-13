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
    #include "Motor/CL42T/Src/CL42T.h"
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
        APPACT_ACT_MTR_X_L = 0x00,
        APPACT_ACT_MTR_X_R,
        APPACT_ACT_MTR_Y,
        APPACT_ACT_MTR_Z,
        APPACT_ACT_BOBINE_1 ,
        APPACT_ACT_NB,
    } t_eAPPACT_Actuators;

   
    typedef union 
    {
        t_sCL42T_SetMotorValue Motor_s;
        t_sint32 setPoint_s32;
    } t_uAPPACT_GetValue;

    typedef union 
    {
        t_sCL42T_GetMotorValue Motor_s;
        t_sint32 setPoint_s32;
    } t_uAPPACT_SetValue;
    /**
    * @brief Enum for Actuators drivers list.
    */
    typedef enum
    {
        APPACT_DRIVER_CL42T = 0x0,              /**< None */
    
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
