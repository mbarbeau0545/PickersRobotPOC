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
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
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
    /* /!\/!\/!\ This configration has been calculated for CLOCK FDCAN equals 48MHz  /!\/!\/!\*/
    /*< Configuration to found Init baudrate value*/ 
    const t_sFMKFDCAN_BaudrateCfg c_FmkCan_BspBaudrateCfg_as[FMKFDCAN_FRAME_BAUDRATE_NB] = {
    //       prescaler        syncSeg     timeSeg1     timeSeg2         
            {(t_uint16)960, (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_40K
            {(t_uint16)288, (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_125K
            {(t_uint16)144, (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_250K
            {(t_uint16)72,  (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_500K
            {(t_uint16)48,  (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_1M
            {(t_uint16)24,  (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_2M
            {(t_uint16)12,  (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_4M
            {(t_uint16)6,   (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKFDCAN_FRAME_BAUDRATE_8M
};

    const t_sFMKFDCAN_DrvNodeCfg c_FmkCan_DriverNodeCfg_as[FMKFDCAN_NODE_CFG_NB] = {
            // FMKFDCAN_NODE_CFG_1
            // FMKFDCAN_NODE_CFG_2
            // FMKFDCAN_NODE_CFG_3
            // FMKFDCAN_NODE_CFG_4
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
    }
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
