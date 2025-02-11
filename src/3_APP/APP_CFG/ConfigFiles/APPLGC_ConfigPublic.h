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
    #define APPLGC_APPUSER_COM_TIMEOUT ((t_uint32)1000)
    #define APPLGC_APPUSER_ERR_RX ((t_uint16)0)
    #define APPLGC_APPUSER_ERR_TX ((t_uint16)1)
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
    * @brief Enum for Service Gtry_X
    */
    typedef enum ____t_eAPPLGC_SrvGtry_X
    {
        APPLGC_SRV_GTRY_X_ACT_MTR_X_L_STATE = 0x00,
        APPLGC_SRV_GTRY_X_ACT_MTR_X_L_DIR,
        APPLGC_SRV_GTRY_X_ACT_MTR_X_L_PULSE,
        APPLGC_SRV_GTRY_X_ACT_MTR_X_R_STATE,
        APPLGC_SRV_GTRY_X_ACT_MTR_X_R_DIR,
        APPLGC_SRV_GTRY_X_ACT_MTR_X_R_PULSE,
        APPLGC_SRV_GTRY_X_ACT_MTR_X_L_SEED,
        APPLGC_SRV_GTRY_X_ACT_MTR_X_R_SPEED,
        APPLGC_SRV_GTRY_X_ACT_NB,
    } t_eAPPLGC_SrvGtry_X;

    /**
    * @brief Enum for Service Gtry_Y
    */
    typedef enum ____t_eAPPLGC_SrvGtry_Y
    {
        APPLGC_SRV_GTRY_Y_ACT_MTR_Y_STATE = 0x00,
        APPLGC_SRV_GTRY_Y_ACT_MTR_Y_DIR,
        APPLGC_SRV_GTRY_Y_ACT_MTR_Y_PULSE,
        APPLGC_SRV_GTRY_Y_ACT_MTR_Y_SPEED,
        APPLGC_SRV_GTRY_Y_ACT_NB,
    } t_eAPPLGC_SrvGtry_Y;

    /**
    * @brief Enum for Service Gtry_Z
    */
    typedef enum ____t_eAPPLGC_SrvGtry_Z
    {
        APPLGC_SRV_GTRY_Z_ACT_MTR_Z_STATE = 0x00,
        APPLGC_SRV_GTRY_Z_ACT_MTR_Z_DIR,
        APPLGC_SRV_GTRY_Z_ACT_MTR_Z_PULSE,
        APPLGC_SRV_GTRY_Z_ACT_MTR_Z_SPEED,
        APPLGC_SRV_GTRY_Z_ACT_NB,
    } t_eAPPLGC_SrvGtry_Z;

    /**
    * @brief Enum for Service Function Listy
    */
    typedef enum ____t_eAPPLGC_SrvList
    {
        APPLGC_SRV_GTRY_X = 0x00,
        APPLGC_SRV_GTRY_Y,
        APPLGC_SRV_GTRY_Z,

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
    
    /**
    * @brief Enum for requested Mode for Gantry Agent 
    */
    enum 
    {
        APPLGC_APP_RQST_GTR_PRODUCTION = 0x00,
        APPLGC_APP_RQST_GTR_PAUSE,
        APPLGC_APP_RQST_GTR_FAILURE,

        APPLGC_APP_RQST_GTR_NB
    };

    /**
    * @brief Enum for requested Mode for Agent Gantry in Production Mode 
    */
    enum
    {
        APPLGC_APP_RQST_GTRY_PROD_SEO = 0x00,
        APPLGC_APP_RQST_GTRY_PROD_MVMT,

        APPLGC_APP_RQST_GTRY_PROD_NB
    };
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
    typedef t_eReturnCode (t_cbAPPLGC_FSMInit)(void);
    /**
    *
    *	@brief      Set the Service Cyclic Function
    *
    */
   typedef t_eReturnCode (t_cbAPPLGC_FSMCyclic)(t_float32 * f_snsValues_paf32, t_sAPPLGC_ServiceInfo *f_SrvInfo_pas);
    /**
    *
    *	@brief      Set the Service Enter Mode Function
    *
    */
    typedef t_eReturnCode (t_cbAPPLGC_FSMEnterMode)(void);
    /**
    *
    *	@brief      Set the Service Exit Mode Function
    *
    */
    typedef t_eReturnCode (t_cbAPPLGC_FSMExitMode)(void);

    //-----------------------------STRUCT TYPES---------------------------//
    typedef struct 
    {
        t_cbAPPLGC_AgentInit * init_pcb;
        t_cbAPPLGC_AgentPeriodicTask * PeriodTask_pcb;
    } t_sAPPLGC_AgentFunc;

    typedef struct 
    {
        t_cbAPPLGC_FSMInit * Init_pcb;
        t_cbAPPLGC_FSMCyclic * Cyclic_pcb;
        t_cbAPPLGC_FSMEnterMode * Enter_pcb;
        t_cbAPPLGC_FSMExitMode * Exit_pcb;
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
