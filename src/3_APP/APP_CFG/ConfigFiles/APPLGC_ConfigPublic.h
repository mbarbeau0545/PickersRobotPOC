/**
 * @file        CL42T_ConfigPublic.h
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef APPLGC_CONFIGPUBLIC_H_INCLUDED
#define APPLGC_CONFIGPUBLIC_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPLGC_APP_PROTOCOL_LEN_DATA ((t_uint8)8)
    #define APPLGC_IDX_APP_DATA_START ((t_uint8)1)
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    /**
    * @brief Enum for Service Func Health Status
    */
    typedef enum 
    {
        APPLGC_SRV_HEALTH_OK = 0x00,
        APPLGC_SRV_HEALTH_ERROR,

        APPLGC_SRV_HEALTH_NB,
    } t_eAPPLGC_SrvHealth;

    /**
    * @brief Enum for Service Function Health
    */
    typedef enum 
    {
        APPLGC_SRV_STATE_STOPPED = 0x00,
        APPLGC_SRV_STATE_MOVING,
        APPLGC_SRV_STATE_INHIBIT,

        APPLGC_SRV_STATE_NB,
    } t_eAPPLGC_SrvState;
    /* CAUTION : Automatic generated code section for Enum: Start */
    /**
    * @brief Enum for Service Gantry_X
    */
    typedef enum ____t_eAPPLGC_SrvGantry_X
    {
        APPLGC_SRV_GANTRY_X_ACT_MOTOR_AXE_X_LEFT_STATE = 0x00,
        APPLGC_SRV_GANTRY_X_ACT_MOTOR_AXE_X_LEFT_DIR,
        APPLGC_SRV_GANTRY_X_ACT_MOTOR_AXE_X_LEFT_PULSE,
        APPLGC_SRV_GANTRY_X_ACT_MOTOR_AXE_X_RIGHT_STATE,
        APPLGC_SRV_GANTRY_X_ACT_MOTOR_AXE_X_RIGHT_DIR,
        APPLGC_SRV_GANTRY_X_ACT_MOTOR_AXE_X_RIGHT_PULSE,
        APPLGC_SRV_GANTRY_X_ACT_NB,
    } t_eAPPLGC_SrvGantry_X;

    /**
    * @brief Enum for Service Gantry_Y
    */
    typedef enum ____t_eAPPLGC_SrvGantry_Y
    {
        APPLGC_SRV_GANTRY_Y_ACT_MOTOR_AXE_Y_STATE = 0x00,
        APPLGC_SRV_GANTRY_Y_ACT_MOTOR_AXE_Y_DIR,
        APPLGC_SRV_GANTRY_Y_ACT_MOTOR_AXE_Y_PULSE,
        APPLGC_SRV_GANTRY_Y_ACT_NB,
    } t_eAPPLGC_SrvGantry_Y;

    /**
    * @brief Enum for Service Gantry_Z
    */
    typedef enum ____t_eAPPLGC_SrvGantry_Z
    {
        APPLGC_SRV_GANTRY_Z_ACT_MOTOR_AXE_Z_STATE = 0x00,
        APPLGC_SRV_GANTRY_Z_ACT_MOTOR_AXE_Z_DIR,
        APPLGC_SRV_GANTRY_Z_ACT_MOTOR_AXE_Z_PULSE,
        APPLGC_SRV_GANTRY_Z_ACT_NB,
    } t_eAPPLGC_SrvGantry_Z;

    /**
    * @brief Enum for Service Function Listy
    */
    typedef enum ____t_eAPPLGC_SrvList
    {
        APPLGC_SRV_GANTRY_X = 0x00,
        APPLGC_SRV_GANTRY_Y,
        APPLGC_SRV_GANTRY_Z,

        APPLGC_SRV_NB,
    } t_eAPPLGC_SrvList;
    /**
    * @brief Enum for Agent
    */
    typedef enum ____t_eAPPLGC_AgentList
    {
        APPLGC_AGENT_GANTRY = 0x00,          // None

        APPLGC_AGENT_NB,
    } t_eAPPLGC_AgentList;
    /* CAUTION : Automatic generated code section for Enum: End */
   
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    typedef struct 
    {
        t_eAPPLGC_SrvHealth health_e;
        t_eAPPLGC_SrvState  state_e;
        t_float32 * actValues_paf32;
    } t_sAPPLGC_ServiceInfo;

    /**
    *
    *	@brief      Set the Agent Init Function
    *
    */
    typedef t_eReturnCode (t_cbAPPLGC_AgentInit)(void);
    /**
    *
    *	@brief      Set the Agent Init Function
    *
    *   @param[in]  f_snsValues_paf32 : All Values Sensors.\n
    *   @param[in]  f_SrvInfo_pas     : All Services Infos.\n
    *
    */
    typedef t_eReturnCode (t_cbAPPLGC_AgentPeriodicTask)(t_float32 *f_snsValues_paf32, t_sAPPLGC_ServiceInfo *f_SrvInfo_pas);

    /**
    *
    *	@brief      Set the Service Init Function
    *
    */
    typedef t_eReturnCode (t_cbAPPLGC_FSMSrvInit)(void);
    /**
    *
    *	@brief      Set the Service Cyclic Function
    *
    */
   typedef t_eReturnCode (t_cbAPPLGC_FSMSrvCyclic)(t_float32 f_snsValues_paf32, t_sAPPLGC_ServiceInfo *f_SrvInfo_pas);
    /**
    *
    *	@brief      Set the Service Enter Mode Function
    *
    */
    typedef t_eReturnCode (t_cbAPPLGC_FSMSrvEnterMode)(void);
    /**
    *
    *	@brief      Set the Service Exit Mode Function
    *
    */
    typedef t_eReturnCode (t_cbAPPLGC_FSMSrvExitMode)(void);

    //-----------------------------STRUCT TYPES---------------------------//
    typedef struct 
    {
        t_cbAPPLGC_AgentInit * init_pcb;
        t_cbAPPLGC_AgentPeriodicTask * PeriodiTask_pcb;
    } t_sAPPLGC_AgentFunc;

    typedef struct 
    {
        t_cbAPPLGC_FSMSrvInit * srvInit_pcb;
        t_cbAPPLGC_FSMSrvCyclic * srvCyclic_pcb;
        t_cbAPPLGC_FSMSrvEnterMode * srvEnter_pcb;
        t_cbAPPLGC_FSMSrvExitMode * srvExit_pcb;
    } t_sAPPLGC_FSM_Func;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    
#endif // APPLGC_CONFIGPUBLIC_H_INCLUDED
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
