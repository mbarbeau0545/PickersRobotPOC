/*********************************************************************
 * @file        FMKCDA_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */


#ifndef FMKFDCAN_CONFIGPUBLIC_H_INCLUDED
#define FMKFDCAN_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************

    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
    // Flag Automatic Generate Code
    typedef enum
    {
        FMKFDCAN_NODE_1 = 0x00, 
        FMKFDCAN_NODE_2, 
        FMKFDCAN_NODE_3, 

        FMKFDCAN_NODE_NB, 
    } t_eFMKFDCAN_NodeList;

    typedef enum
    {
        FMKFDCAN_NODE_OPEMODE_NORMAL = 0x00,
        FMKFDCAN_NODE_OPEMODE_RESTRICTED,
        FMKFDCAN_NODE_OPEMODE_BUS_MONITRING,
        FMKFDCAN_NODE_OPEMODE_INTERNAL_LB,
        FMKFDCAN_NODE_OPEMODE_EXTERNAL_LB,

        FMKFDCAN_NODE_OPEMODE_NB,
    } t_eFMKFDCAN_NodeOpeMode;

    typedef enum
    {
        FMKFDCAN_NODE_CFG_1 = 0x00,
        FMKFDCAN_NODE_CFG_2,
        FMKFDCAN_NODE_CFG_3,
        FMKFDCAN_NODE_CFG_4,

        FMKFDCAN_NODE_CFG_NB,
    } t_eFMKFDCAN_NodeCfgList;
    
    // Flag Automatic Generate Code
    typedef enum
    {
        FMKFDCAN_INTERUPT_LINE_1 = 0x00,
        FMKFDCAN_INTERUPT_LINE_2,

        FMKFDCAN_INTERUPT_LINE_NB,
    } t_eFMKFDCAN_InterruptLine;

    typedef enum
    {
        FMKFDCAN_FRAME_BAUDRATE_40K =0x00,
        FMKFDCAN_FRAME_BAUDRATE_125K,
        FMKFDCAN_FRAME_BAUDRATE_250K,
        FMKFDCAN_FRAME_BAUDRATE_500K,
        FMKFDCAN_FRAME_BAUDRATE_1M,
        FMKFDCAN_FRAME_BAUDRATE_2M,
        FMKFDCAN_FRAME_BAUDRATE_4M,
        FMKFDCAN_FRAME_BAUDRATE_8M,

        FMKFDCAN_FRAME_BAUDRATE_NB,

    } t_eFMKFDCAN_Baudrate;

    typedef enum 
    {
        FMKFDCAN_CLOCK_KERNEL_DIV1  = 0x01,   /**< FDCAN Clock Source Divided  1  */ 
        FMKFDCAN_CLOCK_KERNEL_DIV2  = 0x02,   /**< FDCAN Clock Source Divided  2  */  
        FMKFDCAN_CLOCK_KERNEL_DIV4  = 0x04,   /**< FDCAN Clock Source Divided  4  */  
        FMKFDCAN_CLOCK_KERNEL_DIV6  = 0x06,   /**< FDCAN Clock Source Divided  6  */  
        FMKFDCAN_CLOCK_KERNEL_DIV8  = 0x08,   /**< FDCAN Clock Source Divided  8  */  
        FMKFDCAN_CLOCK_KERNEL_DIV10 = 0x0A,   /**< FDCAN Clock Source Divided  10 */
        FMKFDCAN_CLOCK_KERNEL_DIV12 = 0x0C,   /**< FDCAN Clock Source Divided  12 */
        FMKFDCAN_CLOCK_KERNEL_DIV14 = 0x0E,   /**< FDCAN Clock Source Divided  14 */
        FMKFDCAN_CLOCK_KERNEL_DIV16 = 0x10,   /**< FDCAN Clock Source Divided  16 */
        FMKFDCAN_CLOCK_KERNEL_DIV18 = 0x12,   /**< FDCAN Clock Source Divided  18 */
        FMKFDCAN_CLOCK_KERNEL_DIV20 = 0x14,   /**< FDCAN Clock Source Divided  20 */
        FMKFDCAN_CLOCK_KERNEL_DIV22 = 0x16,   /**< FDCAN Clock Source Divided  22 */
        FMKFDCAN_CLOCK_KERNEL_DIV24 = 0x18,   /**< FDCAN Clock Source Divided  24 */
        FMKFDCAN_CLOCK_KERNEL_DIV26 = 0x1A,   /**< FDCAN Clock Source Divided  26 */
        FMKFDCAN_CLOCK_KERNEL_DIV28 = 0x1C,   /**< FDCAN Clock Source Divided  28 */
        FMKFDCAN_CLOCK_KERNEL_DIV30 = 0x1E,   /**< FDCAN Clock Source Divided  30 */

        FMKFDCAN_CLOCK_KERNEL_DIV_NB = 0x1F   /**< FDCAN Clock Source Divider Number */
    } t_eFMKFDCAN_ClockKernelDiv;
    typedef enum 
    {
        FMKFDCAN_HWQUEUE_TYPE_NORMAL = 0x00,   /**< Hardware Queue is a queue */
        FMKFDCAN_HWQUEUE_TYPE_FIFO,

        FMKFDCAN_HWQUEUE_TYPE_NB,
    } t_eFMKFDCAN_HwTxQueueType;

    typedef enum 
    {
        FMKFDCAN_FIFO_OPEMODE_OVERWRITE = 0x00,
        FMKFDCAN_FIFO_OPEMODE_BLOCKING,

        FMKFDCAN_FIFO_OPEMODE_NB,
    } t_eFMKFDCAN_FifoOpeMode;

    typedef enum 
    {
        FMKFDCAN_FRAME_FORMAT_CLASSIC = 0x00,
        FMKFDCAN_FRAME_FORMAT_FDCAN,

        FMKFDCAN_FRAME_FORMAT_NB,
    } t_eFMKFDCAN_FrameFormat;

    typedef enum 
    {
        FMKFDCAN_BITRATE_SWITCH_ON = 0x00,
        FMKFDCAN_BITRATE_SWITCH_OFF,

        FMKFDCAN_BITRATE_SWITCH_NB
    } t_eFMKFDCAN_BitRateSwitchStatus;


    typedef enum 
    {
        FMKFDCAN_PROTOCOL_CAN2_0B = 0x00,
        FMKFDCAN_PROTOCOL_FDCAN_NO_BRS,
        FMKFDCAN_PROTOCOL_FDCAN_BRS,


        FMKFDCAN_PROTOCOL_FDCAN_NB,
    } t_eFMKFDCAN_ProtocolType;

    typedef enum
    {
        FMKFDCAN_IDTYPE_STANDARD = 0x00,
        FMKFDCAN_IDTYPE_EXTENDED,

        FMKFDCAN_IDTYPE_NB,
    } t_eFMKFDCAN_IdentifierType;

    typedef enum 
    {
        FMKFDCAN_FRAME_PURPOSE_REMOTE = 0x00,
        FMKFDCAN_FRAME_PURPOSE_DATA,

        FMKFDCAN_FRAME_PURPOSE_NB,
    } t_eFMKFDCAN_FramePurpose;


    //-----------------------------ENUM TYPES-----------------------------//
    
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------TYPEDEF TYPES---------------------------//
    
    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    typedef struct
    {
        t_eFMKFDCAN_ClockKernelDiv clockDivider_e;
        t_eFMKFDCAN_ProtocolType ProtocolUse_e;
        t_eFMKFDCAN_Baudrate FrameBaudrate_e;
        t_eFMKFDCAN_Baudrate DataBaudrate_e;
        t_eFMKFDCAN_HwTxQueueType QueueType_e;
        t_eFMKFDCAN_FifoOpeMode FifoMode_e;

    } t_sFMKFDCAN_DrvNodeCfg;
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
