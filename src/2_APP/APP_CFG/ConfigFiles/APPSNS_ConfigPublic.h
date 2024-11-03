/*********************************************************************
 * @file        APPSNS_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSNS_CONFIGPUBLIC_H_INCLUDED
#define APPSNS_CONFIGPUBLIC_H_INCLUDED





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
    /* Enum for Sensors list */
    typedef enum
    {
        APPSNS_SENSOR_AIRTEMPERATURE = 0x0,     /**< Temp�rature local de l'air */
    
        APPSNS_SENSOR_NB,
    } t_eAPPSNS_Sensors;

    /* Enum for Sensors drivers list */
    typedef enum
    {
    
        APPSNS_DRIVER_NB,
    } t_eAPPSNS_Drivers;

    /* Enum for sensor conversion list */
    typedef enum
    {
       APPSNS_MEASTYPE_TEMPERATURE = 0x00,
       APPSNS_MEASTYPE_PRESSURE,
    
        APPSNS_MEASTYPE_NB,
    } t_eAPPSNS_SnsMeasType;

    /* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//
    typedef enum 
    {
        APPSNS_SENSOR_STATE_DISABLE = 0,          /**< The sensor is unused in a system configuration */
        APPSNS_SENSOR_STATE_ENABLE,               /**< The sensor is used in a system configuration */
        APPSNS_SENSOR_STATE_NB                    /**< Number of sensor state */
    } t_eAPPSNS_SensorState;

    typedef enum 
    {
        APPSNS_DRIVER_STATE_DISABLE = 0,          /**< The driver is unused in a system configuration */
        APPSNS_DRIVER_STATE_ENABLE,                /**< The driver is used in a system configuration */
        APPSNS_DRIVER_STATE_NB,                    /**< Number of driver state */
    } t_eAPPSNS_DrvState;
	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    typedef struct
    {
        t_sint16 rawValue_s16;      /**< Store the sensor rawValue */
        t_sint16 SnsValue_s16;      /**< Store the sensor after conversion */
        t_bool   IsValueOK_b;       /**< Store flag value validity */
    } t_sAPPSNS_ValueInfo;
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

#endif // APPSNS_CONFIGPUBLIC_H_INCLUDED           
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
