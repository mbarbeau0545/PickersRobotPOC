/**
 * @file        FMK_MAC.h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKCAN_H_INCLUDED
#define FMKCAN_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "FMK_CFG/FMKCFG_ConfigFiles/FMKCAN_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    typedef enum
    {
        FMKCAN_DLC_1 = 0x00,
        FMKCAN_DLC_2,
        FMKCAN_DLC_3,
        FMKCAN_DLC_4,
        FMKCAN_DLC_5,
        FMKCAN_DLC_6,
        FMKCAN_DLC_7,
        FMKCAN_DLC_8,

        #ifdef FMKCPU_STM32_ECU_FAMILY_G
        FMKCAN_DLC_16,
        FMKCAN_DLC_20,
        FMKCAN_DLC_24,
        FMKCAN_DLC_32,
        FMKCAN_DLC_48,
        FMKCAN_DLC_64,
        #endif

        FMKCAN_DLC_NB
    } t_eFMKCAN_DataLength;

    typedef enum 
    {
        FMKCAN_NODE_STATE_OK = 0x00,
        FMKCAN_NODE_STATE_QUEUE,
        FMKCAN_NODE_STATE_PROTOCOL,

        FMKCAN_NODE_STATE_NB
    } t_eFMKCAN_NodeStatus;

    typedef enum 
    {
        FMKCAN_NODE_DIRECTION_RX = 0X00,
        FMKCAN_NODE_DIRECTION_TX,

        FMKCAN_NODE_DIRECTION_NB
    } t_eFMKCAN_MsgDirection;
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
    /**< Enum for Dma channel state */
    //-----------------------------TYPEDEF TYPES---------------------------//
    /**
    *
    *	@brief      HAL Timer function in Interruption way  
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel 
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef t_eReturnState t_cbFMKCAN_RcvItem(t_uint32 f_Identifier_u32,
                                              t_eFMKCAN_DataBaudrate f_Dlc_e,
                                              t_uint8 *data_pua8,
                                              t_eFMKCAN_NodeStatus f_NodeStatus_e);
                                              /**
    *
    *	@brief      HAL Timer function in Interruption way  
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel 
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef t_eReturnState t_cbFMKCAN_TxItemStatus(t_eFMKCAN_NodeStatus f_NodeStatus_e, t_bool f_IsMsgTransmit);
    //-----------------------------STRUCT TYPES---------------------------//
    typedef struct 
    {
        t_uint32 Identifier_u32;
        t_eFMKCAN_IdentifierType IdType_e;
        t_eFMKCAN_FrameType FrameType_e;
    } t_sFMKCAN_ItemIdentifier;

    typedef struct 
    {
        t_eFMKCAN_DataLength Dlc_e;
        t_eFMKCAN_MsgDirection Direction_e;

        #ifdef FMKCPU_STM32_ECU_FAMILY_G
        t_uint8 data_pu8;
        #else
        t_uint8 data_ua8[FMKCAN_DLC_NB]
        #endif

    } t_sFMKCAN_NodeMessage;

    typedef struct
    {
        t_uint32 Identifier_u32;
        t_sFMKCAN_NodeMessage CanMsg_s;
        t_uint32 timeStamp_32;
        t_eFMKCAN_NodeStatus Nodetatus_e;
    } t_sRxItemEvent;

    typedef struct 
    {
        t_sFMKCAN_ItemIdentifier ItemId_s;
        t_uint32 maskId_u32;
        t_eFMKCAN_DataLength Dlc_e;
        t_cbFMKCAN_RcvItem *callback_cb;
    } t_sFMKCAN_RxItemEventCfg;

    typedef struct
    {
        t_sFMKCAN_ItemIdentifier ItemId_e;
        t_sFMKCAN_NodeMessage CanMsg_s;
        t_cbFMKCAN_TxItemStatus *callback_cb;
        #ifdef FMKCPU_STM32_ECU_FAMILY_G
        t_eFMKCAN_BitRateSwitchStatus BitRate_e;
        #endif
    } t_sFMKCAN_TxItemCfg;
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************



    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKCAN_H_INCLUDED           
//************************************************************************************
// End of File
//************************************************************************************

/**************************************************************************
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
