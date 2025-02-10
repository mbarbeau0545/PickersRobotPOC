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
    #include "../ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC.h"
    /* CAUTION : Automatic generated code section for Include: Start */
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Diag_Motor_X_Left.h"
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Diag_Motor_X_Right.h"
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Diag_Motor_Y.h"
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Diag_Motor_Z.h"
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Limit_Switch_X_Left_Min.h"
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Limit_Switch_X_Left_Max.h"
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Limit_Switch_X_Right_Min.h"
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Limit_Switch_X_Right_Max.h"
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Limit_Switch_Y_Min.h"
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Limit_Switch_Y_Max.h"
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Limit_Switch_Z_Min.h"
    #include "APP_CFG/ConfigSpecific/AppSns_ConfigSpecific/APPSNS_SPEC_Limit_Switch_Z_Max.h"
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
    typedef t_eReturnCode (t_cbAppSns_SetSnsCfg)(void);
    /**
    *
    *	@brief      get value for a sensor
    *
    *	@param[in] f_SnsValue_ps : structure to store value and validity
    *
    */
    typedef t_eReturnCode (t_cbAppSns_GetSigValue)(t_float32 *f_rawSigValue_pf32, t_bool * isValueOK_b);
    /**
    *
    *	@brief      Format the value sensors depdning on how it will be treated in Logic
    *   @note       For example, if the Sensors is a temperature, no matter the signal was (digital, analogic)
    *               this function has to format it into a Temperature SI (system international) value. 
    *
    *	@param[in] rawValue_f32 : the value from ana/dig signal 
    *	@param[in] SnsValue_f32 : the value which will be used in logic
    *
    */
    typedef t_eReturnCode (t_cbAppSns_FormatValSI)(t_float32  rawValue_f32, t_float32 *SnsValue_f32);
    /**
    *
    *	@brief      Set the driver init function
    */
    typedef t_eReturnCode (t_cbAppSns_DrvInit)(void);
    /**
    *
    *	@brief      Set the driver cyclic function
    *
    */
    typedef t_eReturnCode (t_cbAppSns_DrvCyclic)(void);
    /**
    *
    *	@brief      Conversion Management function.\n
    *
    */
   typedef t_eReturnCode (t_cbAppSns_ConversionMngmt)(t_float32 f_rawValue_f32, t_float32 *f_snsValue_ps16);
	
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */

	/**< Structure to store needed functions for a sensor */
    typedef struct 
    {
        t_eAPPSNS_SnsMeasType          measTyp_e;
        t_cbAppSns_SetSnsCfg         * SetCfg_pcb;             /**< Reference to "set config" function */
        t_cbAppSns_GetSigValue       * GetValue_pcb;           /**< Reference to "get value" function */
        t_cbAppSns_FormatValSI       * FormatValSI_pcb;        /**< Reference to convert signal function */ 
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
        
    };

    /**< Variable for System Sensors functions*/
    const t_sAPPSNS_SysSnsFunc c_AppSns_SysSns_apf[APPSNS_SENSOR_NB] = {
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Diag_Motor_X_Left_SetCfg,                       APPSNS_SPEC_Diag_Motor_X_Left_GetSigValue,                     APPSNS_SPEC_Diag_Motor_X_Left_FormatValue}, //APPSNS_SENSOR_DIAG_MOTOR_X_LEFT
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Diag_Motor_X_Right_SetCfg,                      APPSNS_SPEC_Diag_Motor_X_Right_GetSigValue,                    APPSNS_SPEC_Diag_Motor_X_Right_FormatValue}, //APPSNS_SENSOR_DIAG_MOTOR_X_RIGHT
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Diag_Motor_Y_SetCfg,                            APPSNS_SPEC_Diag_Motor_Y_GetSigValue,                          APPSNS_SPEC_Diag_Motor_Y_FormatValue}, //APPSNS_SENSOR_DIAG_MOTOR_Y
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Diag_Motor_Z_SetCfg,                            APPSNS_SPEC_Diag_Motor_Z_GetSigValue,                          APPSNS_SPEC_Diag_Motor_Z_FormatValue}, //APPSNS_SENSOR_DIAG_MOTOR_Z
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Limit_Switch_X_Left_Min_SetCfg,                 APPSNS_SPEC_Limit_Switch_X_Left_Min_GetSigValue,               APPSNS_SPEC_Limit_Switch_X_Left_Min_FormatValue}, //APPSNS_SENSOR_LIMIT_SWITCH_X_LEFT_MIN
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Limit_Switch_X_Left_Max_SetCfg,                 APPSNS_SPEC_Limit_Switch_X_Left_Max_GetSigValue,               APPSNS_SPEC_Limit_Switch_X_Left_Max_FormatValue}, //APPSNS_SENSOR_LIMIT_SWITCH_X_LEFT_MAX
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Limit_Switch_X_Right_Min_SetCfg,                APPSNS_SPEC_Limit_Switch_X_Right_Min_GetSigValue,              APPSNS_SPEC_Limit_Switch_X_Right_Min_FormatValue}, //APPSNS_SENSOR_LIMIT_SWITCH_X_RIGHT_MIN
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Limit_Switch_X_Right_Max_SetCfg,                APPSNS_SPEC_Limit_Switch_X_Right_Max_GetSigValue,              APPSNS_SPEC_Limit_Switch_X_Right_Max_FormatValue}, //APPSNS_SENSOR_LIMIT_SWITCH_X_RIGHT_MAX
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Limit_Switch_Y_Min_SetCfg,                      APPSNS_SPEC_Limit_Switch_Y_Min_GetSigValue,                    APPSNS_SPEC_Limit_Switch_Y_Min_FormatValue}, //APPSNS_SENSOR_LIMIT_SWITCH_Y_MIN
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Limit_Switch_Y_Max_SetCfg,                      APPSNS_SPEC_Limit_Switch_Y_Max_GetSigValue,                    APPSNS_SPEC_Limit_Switch_Y_Max_FormatValue}, //APPSNS_SENSOR_LIMIT_SWITCH_Y_MAX
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Limit_Switch_Z_Min_SetCfg,                      APPSNS_SPEC_Limit_Switch_Z_Min_GetSigValue,                    APPSNS_SPEC_Limit_Switch_Z_Min_FormatValue}, //APPSNS_SENSOR_LIMIT_SWITCH_Z_MIN
        {APPSNS_MEASTYPE_RAW,                                         APPSNS_SPEC_Limit_Switch_Z_Max_SetCfg,                      APPSNS_SPEC_Limit_Switch_Z_Max_GetSigValue,                    APPSNS_SPEC_Limit_Switch_Z_Max_FormatValue}, //APPSNS_SENSOR_LIMIT_SWITCH_Z_MAX
    };

    /**< Variable for Sensors Unity Management */
    const t_eAPPSNS_SnsMeasType c_AppSns_SnsMeasType_ae[APPSNS_SENSOR_NB] = {
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_DIAG_MOTOR_X_LEFT
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_DIAG_MOTOR_X_RIGHT
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_DIAG_MOTOR_Y
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_DIAG_MOTOR_Z
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_LIMIT_SWITCH_X_LEFT_MIN
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_LIMIT_SWITCH_X_LEFT_MAX
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_LIMIT_SWITCH_X_RIGHT_MIN
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_LIMIT_SWITCH_X_RIGHT_MAX
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_LIMIT_SWITCH_Y_MIN
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_LIMIT_SWITCH_Y_MAX
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_LIMIT_SWITCH_Z_MIN
        APPSNS_MEASTYPE_RAW,                                         // APPSNS_SENSOR_LIMIT_SWITCH_Z_MAX
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
