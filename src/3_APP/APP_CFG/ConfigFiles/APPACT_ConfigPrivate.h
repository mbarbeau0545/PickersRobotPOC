/*********************************************************************
 * @file        APPACT_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPACT_CONFIGPRIVATE_H_INCLUDED
#define APPACT_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPACT_ConfigPublic.h"
    /* CAUTION : Automatic generated code section for Include: Start */
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_X_L_State.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_X_L_Dir.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_X_L_Pulse.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_MTr_X_L_Seed.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_X_R_State.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_X_R_Dir.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_X_R_Pulse.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_X_R_Speed.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_Y_State.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_Y_Dir.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_Y_Pulse.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_Y_Speed.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_Z_State.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_Z_Dir.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_Z_Pulse.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_Z_Speed.h"
    /* CAUTION : Automatic generated code section for Include: End */
    #include "Motor/CL42T/Src/CL42T.h"

    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPACT_CFG_NB_PER_CYCLE ((t_uint8)5) /**< Number of actuators configuration per cycle */
    
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
    /**
    *
    *	@brief      Set a actuator configuration 

    */
    typedef t_eReturnCode (t_cbAppAct_SetActCfg)(void);
    /**
    *
    *	@brief  Get actuator value 
    *
    *	@param[in]  f_value_ps : structure to store value and validity
    *
    */
    typedef t_eReturnCode (t_cbAppAct_GetActValue)(t_sAPPACT_ValueInfo *f_value_ps);
    /**
    *
    *	@brief      Set value for an actuator
    *
    *	@param[in] f_value_s16 : value to set
    *
    */
    typedef t_eReturnCode (t_cbAppAct_SetActValue)(t_sint16 f_value_s16);
    /**
    *
    *	@brief      Set the driver init function
    */
    typedef t_eReturnCode (t_cbAppAct_DrvInit)(void);
    /**
    *
    *	@brief      Set the driver cyclic function
    *
    */
    typedef t_eReturnCode (t_cbAppAct_DrvCyclic)(void);

	
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	
    /**< Structure to store needed functions for an actuators */
    typedef struct 
    {
        t_cbAppAct_SetActCfg      * SetCfg_pcb;         /**< Reference to "set config" function */
        t_cbAppAct_SetActValue    * SetValue_pcb;       /**< Reference to "set value" function */
        t_cbAppAct_GetActValue    * GetValue_pcb;       /**< Reference to "get value" function */
    } t_sAPPACT_SysActFunc;

    /**< Structure to store needed functions for a driver */
    typedef struct 
    {
        t_cbAppAct_DrvInit   * Init_pcb;        /**< Reference for init driver function */
        t_cbAppAct_DrvCyclic * Cyclic_pcb;      /**< Reference for cyclic driver function */
    } t_sAPPACT_SysDrvFunc;


    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    /**< Variable for System Actuators drivers functions*/
    const t_sAPPACT_SysDrvFunc c_AppAct_SysDrv_apf[APPACT_DRIVER_NB] = {
        {CL42T_Init,                                           CL42T_Cyclic},  // APPACT_DRIVER_CL42T
    };

    /**< Variable for System Actuators functions*/
    const t_sAPPACT_SysActFunc c_AppAct_SysAct_apf[APPACT_ACTUATOR_NB] = {
        {APPACT_SPEC_Mtr_X_L_State_SetCfg,                           APPACT_SPEC_Mtr_X_L_State_SetValue,                         APPACT_SPEC_Mtr_X_L_State_GetValue}, //APPACT_ACTUATOR_MTR_X_L_STATE
        {APPACT_SPEC_Mtr_X_L_Dir_SetCfg,                             APPACT_SPEC_Mtr_X_L_Dir_SetValue,                           APPACT_SPEC_Mtr_X_L_Dir_GetValue}, //APPACT_ACTUATOR_MTR_X_L_DIR
        {APPACT_SPEC_Mtr_X_L_Pulse_SetCfg,                           APPACT_SPEC_Mtr_X_L_Pulse_SetValue,                         APPACT_SPEC_Mtr_X_L_Pulse_GetValue}, //APPACT_ACTUATOR_MTR_X_L_PULSE
        {APPACT_SPEC_MTr_X_L_Seed_SetCfg,                            APPACT_SPEC_MTr_X_L_Seed_SetValue,                          APPACT_SPEC_MTr_X_L_Seed_GetValue}, //APPACT_ACTUATOR_MTR_X_L_SEED
        {APPACT_SPEC_Mtr_X_R_State_SetCfg,                           APPACT_SPEC_Mtr_X_R_State_SetValue,                         APPACT_SPEC_Mtr_X_R_State_GetValue}, //APPACT_ACTUATOR_MTR_X_R_STATE
        {APPACT_SPEC_Mtr_X_R_Dir_SetCfg,                             APPACT_SPEC_Mtr_X_R_Dir_SetValue,                           APPACT_SPEC_Mtr_X_R_Dir_GetValue}, //APPACT_ACTUATOR_MTR_X_R_DIR
        {APPACT_SPEC_Mtr_X_R_Pulse_SetCfg,                           APPACT_SPEC_Mtr_X_R_Pulse_SetValue,                         APPACT_SPEC_Mtr_X_R_Pulse_GetValue}, //APPACT_ACTUATOR_MTR_X_R_PULSE
        {APPACT_SPEC_Mtr_X_R_Speed_SetCfg,                           APPACT_SPEC_Mtr_X_R_Speed_SetValue,                         APPACT_SPEC_Mtr_X_R_Speed_GetValue}, //APPACT_ACTUATOR_MTR_X_R_SPEED
        {APPACT_SPEC_Mtr_Y_State_SetCfg,                             APPACT_SPEC_Mtr_Y_State_SetValue,                           APPACT_SPEC_Mtr_Y_State_GetValue}, //APPACT_ACTUATOR_MTR_Y_STATE
        {APPACT_SPEC_Mtr_Y_Dir_SetCfg,                               APPACT_SPEC_Mtr_Y_Dir_SetValue,                             APPACT_SPEC_Mtr_Y_Dir_GetValue}, //APPACT_ACTUATOR_MTR_Y_DIR
        {APPACT_SPEC_Mtr_Y_Pulse_SetCfg,                             APPACT_SPEC_Mtr_Y_Pulse_SetValue,                           APPACT_SPEC_Mtr_Y_Pulse_GetValue}, //APPACT_ACTUATOR_MTR_Y_PULSE
        {APPACT_SPEC_Mtr_Y_Speed_SetCfg,                             APPACT_SPEC_Mtr_Y_Speed_SetValue,                           APPACT_SPEC_Mtr_Y_Speed_GetValue}, //APPACT_ACTUATOR_MTR_Y_SPEED
        {APPACT_SPEC_Mtr_Z_State_SetCfg,                             APPACT_SPEC_Mtr_Z_State_SetValue,                           APPACT_SPEC_Mtr_Z_State_GetValue}, //APPACT_ACTUATOR_MTR_Z_STATE
        {APPACT_SPEC_Mtr_Z_Dir_SetCfg,                               APPACT_SPEC_Mtr_Z_Dir_SetValue,                             APPACT_SPEC_Mtr_Z_Dir_GetValue}, //APPACT_ACTUATOR_MTR_Z_DIR
        {APPACT_SPEC_Mtr_Z_Pulse_SetCfg,                             APPACT_SPEC_Mtr_Z_Pulse_SetValue,                           APPACT_SPEC_Mtr_Z_Pulse_GetValue}, //APPACT_ACTUATOR_MTR_Z_PULSE
        {APPACT_SPEC_Mtr_Z_Speed_SetCfg,                             APPACT_SPEC_Mtr_Z_Speed_SetValue,                           APPACT_SPEC_Mtr_Z_Speed_GetValue}, //APPACT_ACTUATOR_MTR_Z_SPEED
    };

    /* CAUTION : Automatic generated code section for Variable: End */


    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPACT_CONFIGPRIVATE_H_INCLUDED           
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
