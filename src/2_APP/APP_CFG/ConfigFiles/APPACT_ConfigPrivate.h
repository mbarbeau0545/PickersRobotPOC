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
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Cmd_IrrigValve_Tomate.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Cmd_IrrigValve_Courgette.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Cmd_IrrigValve_Carotte.h"
    /* CAUTION : Automatic generated code section for Include: End */

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
    };

    /**< Variable for System Actuators functions*/
    const t_sAPPACT_SysActFunc c_AppAct_SysAct_apf[APPACT_ACTUATOR_NB] = {
        {APPACT_SPEC_Cmd_IrrigValve_Tomate_SetCfg,                   APPACT_SPEC_Cmd_IrrigValve_Tomate_SetValue,                 APPACT_SPEC_Cmd_IrrigValve_Tomate_GetValue}, //APPACT_ACTUATOR_CMD_IRRIGVALVE_TOMATE
        {APPACT_SPEC_Cmd_IrrigValve_Courgette_SetCfg,                APPACT_SPEC_Cmd_IrrigValve_Courgette_SetValue,              APPACT_SPEC_Cmd_IrrigValve_Courgette_GetValue}, //APPACT_ACTUATOR_CMD_IRRIGVALVE_COURGETTE
        {APPACT_SPEC_Cmd_IrrigValve_Carotte_SetCfg,                  APPACT_SPEC_Cmd_IrrigValve_Carotte_SetValue,                APPACT_SPEC_Cmd_IrrigValve_Carotte_GetValue}, //APPACT_ACTUATOR_CMD_IRRIGVALVE_CAROTTE
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
