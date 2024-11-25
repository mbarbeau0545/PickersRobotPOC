/*********************************************************************
 * @file        FMKCDA_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKFDCAN_CONFIGPRIVATE_H_INCLUDED
#define FMKFDCAN_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./FMKFDCAN_ConfigPublic.h"
    #include "./FMKCPU_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKFDCAN_SRC_CLOCK ((t_uint8)FMKCPU_PLLQ_CLOCK_OSC_MHZ)

    #define FMKFDCAN_RX_NO_CB_BUFF_SIZE ((t_uint8)15)        /**< Buffer size for Reception FDCan software queue */
    #define FMKFDCAN_RX_SOFT_BUFF_SIZE ((t_uint8)20)        /**< Buffer size for Reception FDCan software queue */
    #define FMKFDCAN_TX_SOFT_BUFF_SIZE ((t_uint8)20)        /**< Buffer size for Transmission FDCan software queue */

    #define FMKFDCAN_RX_NUM_REGISTRATION_EVNT ((t_uint8)30)
//    #define FMKFDCAN_RX_NUM_REGISTRATION_POLL ((t_uint8)20)

    #define FMKFDCAN_NODE_MODE (FDCAN_MODE_NORMAL)


    #define FMKFDCAN_MAX_TX_ITEM_SEND_PER_IT ((t_uint8)5)
    #define FMKFDCAN_MAX_ITEM_ON_QUEUE_PER_IT ((t_uint8)5)

    #define FMKFDCAN_64_BYTES ((t_uint8)64)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    // Flag Automatic Generate Code
    typedef enum 
    {
        FMKFDCAN_HW_RX_FIFO_0 = 0x00,
        FMKFDCAN_HW_RX_FIFO_1,

        FMKFDCAN_HW_RX_FIFO_NB,
    } t_eFMKFDCAN_HwRxFifoList;


    typedef enum 
    {
        FMKFDCAN_HW_TX_FIFO_1 = 0x00,

        FMKFDCAN_HW_TX_FIFO_NB,
    } t_eFMKFDCAN_HwTxFifoList;
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------TYPEDEF TYPES---------------------------//
    
    //-----------------------------STRUCT TYPES---------------------------//
    typedef struct 
    {
        t_uint16 prescaler_u16;
        t_uint8 syncSeg_u8;
        t_uint8 timeSeg1_u8;
        t_uint8 timeSeg2_u8;
    } t_sFMKFDCAN_BaudrateCfg;
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */

    /* CAUTION : Automatic generated code section for Variable: End */

    const t_eFMKFDCAN_NodeCfgList c_FmkCan_NodeCfg_ae[FMKFDCAN_NODE_NB] = {
        FMKFDCAN_NODE_CFG_1,  // FMKFDCAN_NODE_1
        FMKFDCAN_NODE_CFG_1, // FMKFDCAN_NODE_2
        FMKFDCAN_NODE_CFG_1, // FMKFDCAN_NODE_3
    };
    

    const t_bool c_FmkCan_IsNodeActive[FMKFDCAN_NODE_NB] = {
        (t_bool)True,  // FMKFDCAN_NODE_1
        (t_bool)False, // FMKFDCAN_NODE_2
        (t_bool)False, // FMKFDCAN_NODE_3
    };

    const t_uint32 c_FmkCan_NodeItLine[FMKFDCAN_NODE_NB] = {
        FDCAN_INTERRUPT_LINE0,        // FMKFDCAN_NODE_1
        FDCAN_INTERRUPT_LINE1,        // FMKFDCAN_NODE_2
        FDCAN_INTERRUPT_LINE1,        // FMKFDCAN_NODE_3
    };

    const t_sFMKFDCAN_DrvNodeCfg c_FmkCan_BspNodeCfgList_as[FMKFDCAN_NODE_CFG_NB] = 
    {// clockDivider_e                      ProtocolUse_e                       FrameBaudrate_e                 DataBaudrate_e                    QueueType_e                       FifoMode_e
        {FMKFDCAN_CLOCK_KERNEL_DIV1,        FMKFDCAN_PROTOCOL_CAN2_0B,          FMKFDCAN_FRAME_BAUDRATE_250K,   FMKFDCAN_FRAME_BAUDRATE_250K,    FMKFDCAN_HWQUEUE_TYPE_NORMAL,      FMKFDCAN_FIFO_OPEMODE_BLOCKING}, // FMKFDCAN_NODE_CFG_1
        {FMKFDCAN_CLOCK_KERNEL_DIV1,        FMKFDCAN_PROTOCOL_CAN2_0B,          FMKFDCAN_FRAME_BAUDRATE_1M,     FMKFDCAN_FRAME_BAUDRATE_1M,      FMKFDCAN_HWQUEUE_TYPE_NORMAL,      FMKFDCAN_FIFO_OPEMODE_BLOCKING}, // FMKFDCAN_NODE_CFG_2
        {FMKFDCAN_CLOCK_KERNEL_DIV1,        FMKFDCAN_PROTOCOL_FDCAN_NO_BRS,     FMKFDCAN_FRAME_BAUDRATE_1M,     FMKFDCAN_FRAME_BAUDRATE_1M,      FMKFDCAN_HWQUEUE_TYPE_NORMAL,      FMKFDCAN_FIFO_OPEMODE_BLOCKING}, // FMKFDCAN_NODE_CFG_3
        {FMKFDCAN_CLOCK_KERNEL_DIV1,        FMKFDCAN_PROTOCOL_FDCAN_BRS,        FMKFDCAN_FRAME_BAUDRATE_1M,     FMKFDCAN_FRAME_BAUDRATE_4M,      FMKFDCAN_HWQUEUE_TYPE_NORMAL,      FMKFDCAN_FIFO_OPEMODE_BLOCKING}, // FMKFDCAN_NODE_CFG_4
    };
    /* /!\/!\/!\ This configration has been calculated for CLOCK FDCAN equals 64MHz  /!\/!\/!\*/
    /*  Formule :
    *                                  Fclock (FMKFDCAN_SRC_CLOCK)
    *  Baudrate =     -----------------------------------------
    *                   Prescaler * (SyncSeg + TimSeg1 + TimSeg2)
    */                  
    /*< Configuration to found Init baudrate value*/ 
    const t_sFMKFDCAN_BaudrateCfg c_FmkCan_BspBaudrateCfg_as[FMKFDCAN_FRAME_BAUDRATE_NB] = {
    //       prescaler        syncSeg     timeSeg1     timeSeg2         
            {(t_uint16)80,  (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_40K
            {(t_uint16)32,  (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_125K
            {(t_uint16)16,  (t_uint8)1, (t_uint8)11, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_250K 
            {(t_uint16)8,   (t_uint8)1, (t_uint8)11, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_500K 
            {(t_uint16)4,   (t_uint8)1, (t_uint8)11, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_1M 
            {(t_uint16)2,   (t_uint8)1, (t_uint8)11, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_2M
            {(t_uint16)1,   (t_uint8)1, (t_uint8)11, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_4M
            {(t_uint16)1,   (t_uint8)1, (t_uint8)5,  (t_uint8)2},    // FMKFDCAN_FRAME_BAUDRATE_8M
    };

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKFDCAN_CONFIGPRIVATE_H_INCLUDED           
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
