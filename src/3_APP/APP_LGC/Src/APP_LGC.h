/*********************************************************************
 * @file        APP_LGC.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APP_LGC_H_INCLUDED
#define APP_LGC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "APP_CFG/ConfigFiles/APPLGC_ConfigPublic.h"

    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    typedef enum 
    {
        APPLGC_RCV_CMD_ID_DATA_MODE = 0x00,
        APPLGC_RCV_CMD_ID_DATA_SPEED_XYZ,
        APPLGC_RCV_CMD_ID_DATA_DIR_XYZ,
        APPLGC_RCV_CMD_ID_DATA_PULSE_XYZ,
        APPLGC_RCV_CMD_ID_EMERGENCY_STOP,
        APPLGC_RCV_CMD_ID_BIT_ALIVE,

        APPLGC_RCV_CMD_ID_NB,
    } t_eAPPGC_AppRcvCmdId;

    typedef enum 
    {
        APPMGC_SND_CMD_ID_GTRY_STATE_XYZ = 0x00,
        APPMGC_SND_CMD_ID_GTRY_MISSION_INFO,
        APPMGC_SND_CMD_ID_GTRY_ROBOT_INFO,

        APPLGC_SND_CMD_ID_NB
    } t_eAPPLGC_AppSendCmdId;
	/* CAUTION : Automatic generated code section for Enum: Start */

	/* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//


	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    typedef struct 
    {
        t_uint16 nbPulseX_u16;
        t_uint16 nbPulseY_u16;
        t_uint16 nbPulseZ_u16;
    } t_sAPPLGC_PulseInfo;

    typedef struct 
    {
        t_uint16 DirX_u16;
        t_uint16 DirY_u16;
        t_uint16 DirZ_u16;
    } t_sAPPLGC_DirInfo;

    typedef struct 
    {
        t_uint16 speedX_u16;
        t_uint16 speedY_u16;
        t_uint16 speedZ_u16;
    } t_sAPPLGC_SpeedInfo;

    typedef struct 
    {
        t_uint8 mainMode_u8;
        t_uint8 prodMode_u8;
    } t_sAPPLGC_FSMModeInfo;

    typedef union 
    {
        t_sAPPLGC_PulseInfo     pulseInfo_s;
        t_sAPPLGC_DirInfo       dirInfo_s;
        t_sAPPLGC_SpeedInfo     speedInfo_s;
        t_sAPPLGC_FSMModeInfo   SFMModeInfo_s;
    } t_uAPPLGC_CmdValues;
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	//-----------------------------TYPEDEF TYPES---------------------------//
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
    t_eReturnCode APPLGC_Init(void);
    /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
    t_eReturnCode APPLGC_Cyclic(void);
    /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
    t_eReturnCode APPLGC_GetState(t_eCyclicModState *f_State_pe);
    /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
    t_eReturnCode APPLGC_SetState(t_eCyclicModState f_State_e);
    /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
   t_eReturnCode APPLGC_SetServiceHealth(t_eAPPLGC_SrvList f_service_e, t_eAPPLGC_SrvHealth f_srvHealth_e);
   /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
   t_eReturnCode APPLGC_GetServiceHealth(t_eAPPLGC_SrvList f_service_e, t_eAPPLGC_SrvHealth * f_srvHealth_pe);
   /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
   t_eReturnCode APPLGC_GetAppCmd(t_eAPPGC_AppRcvCmdId f_cmdId_e, t_uAPPLGC_CmdValues * f_cmdValues_pu);

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APP_LGC_H_INCLUDED           
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
