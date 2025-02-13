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
    #include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"
    #include "APP_CTRL/APP_ACT/Src/APP_ACT.h"
    #include "APP_CTRL/APP_SNS/Src/APP_SNS.h"
    #include "APP_CTRL/APP_SDM/Src/APP_SDM.h"
    #include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPLGC_APP_COM_SEND(msg) FMKSRL_Transmit(   FMKSRL_SERIAL_LINE_2,         \
                                                        FMKSRL_TX_ONESHOT,            \
                                                        msg,                          \
                                                        APPLGC_APP_PROTOCOL_LEN_DATA, \
                                                        0,                            \
                                                        False)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    enum 
    {
        APPLGC_CMD_BYTE_0 = 0x00,
        APPLGC_CMD_BYTE_1,
        APPLGC_CMD_BYTE_2,
        APPLGC_CMD_BYTE_3,
        APPLGC_CMD_BYTE_4,
        APPLGC_CMD_BYTE_5,
        APPLGC_CMD_BYTE_6,
        APPLGC_CMD_BYTE_7,

        APPLGC_CMD_BYTE_NB,
    };

    typedef enum 
    {
        APPLGC_RCV_CMD_ID_DATA_MODE = 0x00,
        APPLGC_RCV_CMD_ID_GTRY_X,
        APPLGC_RCV_CMD_ID_GTRY_Y,
        APPLGC_RCV_CMD_ID_GTRY_Z,
        APPLGC_RCV_CMD_ID_EMERGENCY_STOP,
        APPLGC_RCV_CMD_ID_BIT_ALIVE,

        APPLGC_RCV_CMD_ID_NB,
    } t_eAPPGC_AppRcvCmdId;

    typedef enum 
    {
        APPLGC_SEND_CMD_ID_GTRY_STATE_XYZ = 0x00,
        APPLGC_SEND_CMD_ID_GTRY_SPEED_XYZ,
        APPLGC_SEND_CMD_ID_GTRY_INFO,
        APPLGC_SEND_CMD_ID_ROBOT_INFO,
        APPLGC_SEND_CMD_ID_ERROR_STATUS,
        
        APPLGC_SEND_CMD_ID_NB,
    } t_eAPPLGC_AppCmdSendId;
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
        t_sint32 pulse_s32;
        t_uint16 speed_u16;
    } t_sAPPLGC_CmdAxeInfo;

    typedef struct 
    {
        t_uint8 mainMode_u8;
        t_uint8 prodMode_u8;
    } t_sAPPLGC_FSMModeInfo;

    typedef union 
    {
        t_sAPPLGC_CmdAxeInfo    axe_s;
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
    void APPLGC_ComputeCheckSum(t_uint8 * f_startData_pu8, 
                                t_uint8 f_datalen_u8,
                                t_uint8 * f_cheksum_pu8);
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
