/*********************************************************************
 * @file        FMKCDA_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKCAN_CONFIGPRIVATE_H_INCLUDED
#define FMKCAN_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./FMKCAN_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    // Flag Automatic Generate Code
    typedef enum 
    {
        FMKCAN_HW_RX_FIFO_1 = 0x00,
        FMKCAN_HW_RX_FIFO_2,

        FMKCAN_HW_RX_FIFO_NB,
    } t_eFMKCAN_HwRxFifoList;

    #ifdef FMKCPU_STM32_ECU_FAMILY_G
    typedef enum 
    {
        FMKCAN_HW_TX_FIFO_1 = 0x00,

        FMKCAN_HW_TX_FIFO_NB,
    } t_eFMKCAN_HwTxFifoList;
    #elif defined FMKCPU_STM32_ECU_FAMILY_F
    typedef enum
    {
        FMKCAN_HW_TX_MAILBOX_1 = 0x00,
        FMKCAN_HW_TX_MAILBOX_2,
        FMKCAN_HW_TX_MAILBOX_3,

        FMKCAN_HW_TX_MAILBOX_NB,
    } t_eFMKCAN_HwTxFifoList
    #endif
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------TYPEDEF TYPES---------------------------//
    
    //-----------------------------STRUCT TYPES---------------------------//
    typedef struct 
    {
        t_uint8 HwRxFifoNb_u8;
        t_uint8 HwTxFifoNb_u8;
    } t_sFMKCAN_HwFifoCfg;

    typedef struct 
    {
        t_uint16 prescaler_u16;
        t_uint8 syncSeg_u8;
        t_uint8 timeSeg1_u8;
        t_uint8 timeSeg2_u8;
    } t_sFMKCAN_BaudrateCfg;
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
    const t_sFMKCAN_BaudrateCfg c_FmkCan_BspBaudrateCfg_as[FMKCAN_FRAME_BAUDRATE_NB] = {
    //       prescaler        syncSeg     timeSeg1     timeSeg2         
            {(t_uint16)960, (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKCAN_FRAME_BAUDRATE_40K
            {(t_uint16)288, (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKCAN_FRAME_BAUDRATE_125K
            {(t_uint16)144, (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKCAN_FRAME_BAUDRATE_250K
            {(t_uint16)72,  (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKCAN_FRAME_BAUDRATE_500K
            {(t_uint16)48,  (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKCAN_FRAME_BAUDRATE_1M
            {(t_uint16)24,  (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKCAN_FRAME_BAUDRATE_2M
            {(t_uint16)12,  (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKCAN_FRAME_BAUDRATE_4M
            {(t_uint16)6,   (t_uint8)1, (t_uint8)15, (t_uint8)4},    // FMKCAN_FRAME_BAUDRATE_8M
    };

    const t_sFMKCAN_DrvNodeCfg c_FmkCan_DriverNodeCfg_as[FMKCAN_NODE_CFG_NB] = {
            // FMKCAN_NODE_CFG_1
            // FMKCAN_NODE_CFG_2
            // FMKCAN_NODE_CFG_3
            // FMKCAN_NODE_CFG_4
    }
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
