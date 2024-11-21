/*********************************************************************
 * @file        FMKCDA_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */


#ifndef FMKCAN_CONFIGPUBLIC_H_INCLUDED
#define FMKCAN_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./FMKCPU_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
    // Flag Automatic Generate Code
    typedef enum
    {
        FMKCAN_NODE_1 = 0x00, 
        FMKCAN_NODE_2, 
        FMKCAN_NODE_3, 

        FMKCAN_NODE_NB, 
    } t_eFMKCAN_NodeList;

    typedef enum
    {
        FMKCAN_NODE_OPEMODE_NORMAL = 0x00,
        FMKCAN_NODE_OPEMODE_RESTRICTED,
        FMKCAN_NODE_OPEMODE_BUS_MONITRING,
        FMKCAN_NODE_OPEMODE_INTERNAL_LB,
        FMKCAN_NODE_OPEMODE_EXTERNAL_LB,

        FMKCAN_NODE_OPEMODE_NB,
    } t_eFMKCAN_NodeOpeMode;

    typedef enum
    {
        FMKCAN_NODE_CFG_1 = 0x00,
        FMKCAN_NODE_CFG_2,
        FMKCAN_NODE_CFG_3,
        FMKCAN_NODE_CFG_4,

        FMKCAN_NODE_CFG_NB,
    } t_eFMKCAN_NodeCfgList;
    
    // Flag Automatic Generate Code
    typedef enum
    {
        FMKCAN_INTERUPT_LINE_1 = 0x00,
        FMKCAN_INTERUPT_LINE_2,

        FMKCAN_INTERUPT_LINE_NB,
    } t_eFMKCAN_InterruptLine;

    typedef enum
    {
        FMKCAN_FRAME_BAUDRATE_40K =0x00,
        FMKCAN_FRAME_BAUDRATE_125K,
        FMKCAN_FRAME_BAUDRATE_250K,
        FMKCAN_FRAME_BAUDRATE_500K,
        FMKCAN_FRAME_BAUDRATE_1M,

        #ifdef FMKCPU_STM32_ECU_FAMILY_G
        FMKCAN_FRAME_BAUDRATE_2M,
        FMKCAN_FRAME_BAUDRATE_4M,
        FMKCAN_FRAME_BAUDRATE_8M,
        #endif

        FMKCAN_FRAME_BAUDRATE_NB,

    } t_eFMKCAN_FrameBaudrate;

    #ifdef FMKCPU_STM32_ECU_FAMILY_G
    typedef enum 
    {
        FMKCAN_DATA_BAUDRATE_125K = 0x00,
        FMKCAN_DATA_BAUDRATE_250K,
        FMKCAN_DATA_BAUDRATE_500K,
        FMKCAN_DATA_BAUDRATE_1M,

       
        FMKCAN_DATA_BAUDRATE_2M,
        FMKCAN_DATA_BAUDRATE_4M,
        FMKCAN_DATA_BAUDRATE_8M,


        FMKCAN_DATA_BAUDRATE_NB,
    } t_eFMKCAN_DataBaudrate;

    typedef enum 
    {
        FMKCAN_HWQUEUE_TYPE_NORMAL = 0x00,   /**< Hardware Queue is a queue */
        FMKCAN_HWQUEUE_TYPE_FIFO,

        FMKCAN_HWQUEUE_TYPE_NB,
    } t_eFMKCAN_HwTxQueueType;

    typedef enum 
    {
        FMKCAN_FIFO_OPEMODE_OVERWRITE = 0x00,
        FMKCAN_FIFO_OPEMODE_BLOCKING,

        FMKCAN_FIFO_OPEMODE_NB,
    } t_eFMKCAN_FifoOpeMode;

    typedef enum 
    {
        FMKCAN_FRAME_FORMAT_CLASSIC = 0x00,
        FMKCAN_FRAME_FORMAT_FDCAN,

        FMKCAN_FRAME_FORMAT_NB,
    } t_eFMKCAN_FrameFormat;

    typedef enum 
    {
        FMKCAN_BITRATE_SWITCH_ON = 0x00,
        FMKCAN_BITRATE_SWITCH_OFF,

        FMKCAN_BITRATE_SWITCH_NB
    } t_eFMKCAN_BitRateSwitchStatus;
    #endif

    typedef enum 
    {
        FMKCAN_PROTOCOL_CAN2_0B = 0x00,

        #ifdef FMKCPU_STM32_ECU_FAMILY_G
        FMKCAN_PROTOCOL_FDCAN_NO_BRS,
        FMKCAN_PROTOCOL_FDCAN_BRS,
        #endif

        FMKCAN_PROTOCOL_FDCAN_NB,
    } t_eFMKCAN_ProtocolType;

    typedef enum
    {
        FMKCAN_IDTYPE_STANDARD = 0x00,
        FMKCAN_IDTYPE_EXTENDED,

        FMKCAN_IDTYPE_NB,
    } t_eFMKCAN_IdentifierType;

    typedef enum 
    {
        FMKCAN_FRAME_TYPE_REMOTE = 0x00,
        FMKCAN_FRAME_TYPE_DATA,

        FMKCAN_FRAME_TYPE_NB,
    } t_eFMKCAN_FrameType;
    //-----------------------------ENUM TYPES-----------------------------//
    
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------TYPEDEF TYPES---------------------------//
    
    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    typedef struct
    {
        t_eFMKCAN_ProtocolType ProtocolUse_e;
        t_eFMKCAN_NodeOpeMode  NodeMode_e;
        t_eFMKCAN_FrameBaudrate FrameBaudrate_e;
        #ifdef FMKCPU_STM32_ECU_FAMILY_G
        t_uint32 clockDivider_u32;
        t_eFMKCAN_DataBaudrate DataBaudrate_e;
        t_eFMKCAN_HwTxQueueType QueueType_e;
        t_eFMKCAN_FifoOpeMode FifoMode_e;
        #endif
    } t_sFMKCAN_DrvNodeCfg;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */

    /* CAUTION : Automatic generated code section for Variable: End */
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKCDA_CONFIGPRIVATE_H_INCLUDED           
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
