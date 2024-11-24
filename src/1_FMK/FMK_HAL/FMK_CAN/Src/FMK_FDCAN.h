/**
 * @file        FMK_MAC.h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKFDCAN_H_INCLUDED
#define FMKFDCAN_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "FMK_CFG/FMKCFG_ConfigFiles/FMKFDCAN_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    typedef enum
    {
        FMKFDCAN_DLC_0 = 0x00,
        FMKFDCAN_DLC_1,
        FMKFDCAN_DLC_2,
        FMKFDCAN_DLC_3,
        FMKFDCAN_DLC_4,
        FMKFDCAN_DLC_5,
        FMKFDCAN_DLC_6,
        FMKFDCAN_DLC_7,
        FMKFDCAN_DLC_8,
        FMKFDCAN_DLC_16,
        FMKFDCAN_DLC_20,
        FMKFDCAN_DLC_24,
        FMKFDCAN_DLC_32,
        FMKFDCAN_DLC_48,
        FMKFDCAN_DLC_64,

        FMKFDCAN_DLC_NB
    } t_eFMKFDCAN_DataLength;

    typedef enum 
    {
        FMKFDCAN_NODE_STATE_OK = 0x00,
        FMKFDCAN_NODE_STATE_QUEUE,
        FMKFDCAN_NODE_STATE_PROTOCOL,

        FMKFDCAN_NODE_STATE_NB
    } t_eFMKFDCAN_NodeStatus;

    typedef enum 
    {
        FMKFDCAN_NODE_DIRECTION_RX = 0X00,
        FMKFDCAN_NODE_DIRECTION_TX,

        FMKFDCAN_NODE_DIRECTION_NB
    } t_eFMKFDCAN_MsgDirection;
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
    typedef struct 
    {
        t_uint32 Identifier_u32;
        t_eFMKFDCAN_IdentifierType IdType_e;
        t_eFMKFDCAN_FramePurpose FramePurpose_e;
    } t_sFMKFDCAN_ItemIdentifier;

    typedef struct 
    {
        t_eFMKFDCAN_DataLength Dlc_e;
        t_eFMKFDCAN_MsgDirection Direction_e;
        t_uint8 *data_pu8;

    } t_sFMKFDCAN_NodeMessage;

    typedef struct
    {
        t_sFMKFDCAN_ItemIdentifier ItemId_s;
        t_sFMKFDCAN_NodeMessage CanMsg_s;
        t_uint32 timeStamp_32;
        t_eFMKFDCAN_NodeStatus Nodetatus_e;
    } t_sFMKFDCAN_RxItemEvent;
    //-----------------------------TYPEDEF TYPES---------------------------//
    /**
    *
    *	@brief      Callback function to be called when a Can Message is received.\n
    *	@note       If a can message is received and it matches
    *               is used in blocking mode t_sFMKFDCAN_RxItemEventCfg @ref t_sFMKFDCAN_RxItemEventCfg
    *
    *	@param[in]      
    *	@param[in]      
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef t_eReturnCode t_cbFMKFDCAN_RcvItem(t_sFMKFDCAN_RxItemEvent f_RxItem_s, t_eFMKFDCAN_NodeStatus f_NodeStatus_e);
                                              /**
    *
    *	@brief      HAL Timer function in Interruption way  
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *	@param[in]     
    *	@param[in ]     
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef t_eReturnCode t_cbFMKFDCAN_TxItemStatus(t_eFMKFDCAN_NodeStatus f_NodeStatus_e, t_bool f_IsMsgTransmit);
    //-----------------------------STRUCT TYPES---------------------------//
    

    
    typedef struct 
    {
        t_sFMKFDCAN_ItemIdentifier ItemId_s;
        t_uint32 maskId_u32;
        t_eFMKFDCAN_DataLength Dlc_e;
        t_cbFMKFDCAN_RcvItem *callback_cb;
    } t_sFMKFDCAN_RxItemEventCfg;

    typedef struct
    {
        t_sFMKFDCAN_ItemIdentifier ItemId_s;
        t_sFMKFDCAN_NodeMessage CanMsg_s;
        t_eFMKFDCAN_FrameFormat frameFormat_e;
        t_eFMKFDCAN_BitRateSwitchStatus BitRate_e;

    } t_sFMKFDCAN_TxItemCfg;
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
    /**
    *
    *	@brief      Perform all Init action for this module.\n
    *	@note       Set to default value all globals structure that
    *                store information for each signals.\n
    *
    */
    t_eReturnCode FMKFDCAN_Init(void);
    /**
    *
    *	@brief      Perform all Cyclic action for this module.\n
    *	@note       
    *
    */
    t_eReturnCode FMKFDCAN_Cyclic(void);
    /**
    *
    *	@brief Function to know the module state.\n 
    *
    *	@param[in]  f_State_pe : store the value, value from @ref t_eCyclicFuncState
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
    */
    t_eReturnCode FMKFDCAN_GetState(t_eCyclicFuncState *f_State_pe);
    /**
    *
    *	@brief Function to update the module state.\n
    *
    *	@param[in]  f_State_e : the new value, value from @ref t_eCyclicFuncState
    *
    *   @retval RC_OK                             @ref RC_OK
    */
    t_eReturnCode FMKFDCAN_SetState(t_eCyclicFuncState f_State_e);
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
    t_eReturnCode FMKFDCAN_InitDriver(t_eFMKFDCAN_NodeList f_Node_e, t_sFMKFDCAN_DrvNodeCfg f_NodeCfg_s);
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
    t_eReturnCode FMKFDCAN_ConfigureRxItemEvent(t_eFMKFDCAN_NodeList f_Node_e, t_sFMKFDCAN_RxItemEventCfg f_RxItemCfg_s);
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
    t_eReturnCode FMKFDCAN_SendTxItem(t_eFMKFDCAN_NodeList f_Node_e, t_sFMKFDCAN_TxItemCfg f_TxItemCfg_s);
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
    t_eReturnCode FMKFDCAN_GetRxItem(t_eFMKFDCAN_NodeList f_Node_e, t_sFMKFDCAN_RxItemEvent *f_RxItem_ps);

#endif // FMKFDCAN_H_INCLUDED           
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
