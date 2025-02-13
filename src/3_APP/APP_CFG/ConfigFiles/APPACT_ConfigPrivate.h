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
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_X_L.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_X_R.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_Y.h"
    #include "APP_CFG\ConfigSpecific\AppAct_ConfigSpecific/APPACT_SPEC_Mtr_Z.h"
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
    typedef t_eReturnCode (t_cbAppAct_GetActValue)(t_uAPPACT_GetValue *f_value_pu);
    /**
    *
    *	@brief      Set value for an actuator
    *
    *	@param[in] f_value_s16 : value to set
    *
    */
    typedef t_eReturnCode (t_cbAppAct_SetActValue)(t_uAPPACT_SetValue f_value_u);
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
        {APPACT_SPEC_Mtr_X_L_SetCfg,                                 APPACT_SPEC_Mtr_X_L_SetValue,                               APPACT_SPEC_Mtr_X_L_GetValue}, //APPACT_ACTUATOR_MTR_X_L
        {APPACT_SPEC_Mtr_X_R_SetCfg,                                 APPACT_SPEC_Mtr_X_R_SetValue,                               APPACT_SPEC_Mtr_X_R_GetValue}, //APPACT_ACTUATOR_MTR_X_R
        {APPACT_SPEC_Mtr_Y_SetCfg,                                   APPACT_SPEC_Mtr_Y_SetValue,                                 APPACT_SPEC_Mtr_Y_GetValue}, //APPACT_ACTUATOR_MTR_Y
        {APPACT_SPEC_Mtr_Z_SetCfg,                                   APPACT_SPEC_Mtr_Z_SetValue,                                 APPACT_SPEC_Mtr_Z_GetValue}, //APPACT_ACTUATOR_MTR_Z
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
