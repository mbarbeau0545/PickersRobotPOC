/**
 * @file        FMK_MAC.c
 * @brief       Framework Memory Access Control module.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        15/09/2024
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************

#include "./FMK_FDCAN.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKFDCAN_ConfigPrivate.h"

#include "Library/Queue/Src/LIBQueue.h"
#include "stm32g4xx_hal.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */


typedef enum 
{
    FMKFDCAN_BSP_TX_CB_EVENT = 0x00,
    FMKFDCAN_BSP_TX_CB_BUFFER_COMPLETE,
    FMKFDCAN_BSP_TX_CB_BUFFER_ABORT, 
    FMKFDCAN_BSP_TX_CB_FIFO_EMPTY,

    FMKFDCAN_BSP_RX_CB_FIFO_0,
    FMKFDCAN_BSP_RX_CB_FIFO_1,

    FMKFDCAN_BSP_CB_NB
} t_eFMKFDCAN_BspCallbackList;

typedef enum 
{
    FMKFDCAN_CALLBACK_STATUS_ACTIVATE = 0x00,
    FMKFDCAN_CALLBACK_STATUS_DEACTIVATE,

    FMKFDCAN_CALLBACK_STATUS_NB,
} t_eFMKFDCAN_BspStatusCb;
//-----------------------------ENUM TYPES-----------------------------//

/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
typedef struct 
{
    t_bool TxQueuePending_b;
    t_bool RxQueuePending_b;
    t_bool TxFramePrioPending_b;
    t_bool ErrorDetected_b;
} t_sFMKFDCAN_FlagSoft;


typedef struct
{
    FDCAN_HandleTypeDef bspNode_s;
    const t_eFMKCPU_ClockPort c_Clock_e;
    const t_eFMKCPU_IRQNType c_IrqnType_e;
    t_sFMKFDCAN_FlagSoft Flag_s;
    t_bool isNodeConfigured_b;
    t_bool isNodeActive_b;

} t_sFMKFDCAN_NodeInfo;

// Création d'un alias de type pour simplifier l'utilisation
typedef FDCAN_RxHeaderTypeDef t_sFMKFDCAN_RxItemBuffer;

typedef struct 
{
    FDCAN_TxHeaderTypeDef bspTxItem_s;
    t_uint8 data_ua8[FMKFDCAN_DLC_8];
} t_sFMKFDCAN_TxItemBuffer;


/**< User register Structure */
typedef struct
{
    t_sFMKFDCAN_ItemIdentifier itemId_s;
    t_uint32 maskId_u32;
    t_cbFMKFDCAN_RcvItem *rcvItem_cb;
} t_sFMKFDCAN_UserItemRegister;


/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//

// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
static t_eCyclicFuncState g_Modulestate_e = STATE_CYCLIC_WAITING;
/* Store information about node*/
t_sFMKFDCAN_NodeInfo g_NodeInfo_as[FMKFDCAN_NODE_NB];

/**< Transmission software Buffer*/
t_sFMKFDCAN_TxItemBuffer g_TxSoftBuffer_as[FMKFDCAN_NODE_NB][FMKFDCAN_TX_SOFT_BUFF_SIZE];
/**< Transmission Queue management*/
t_sLIBQUEUE_QueueCore g_TxSoftQueue_as[FMKFDCAN_NODE_NB];

/**< Reception software Buffer*/
t_sFMKFDCAN_RxItemBuffer g_RxSoftBuffer_as[FMKFDCAN_NODE_NB][FMKFDCAN_RX_SOFT_BUFF_SIZE];
/**< Reception Queue management*/
t_sLIBQUEUE_QueueCore g_RxSoftQueue_as[FMKFDCAN_NODE_NB];

/**< User Item Registration Managment */
t_sFMKFDCAN_UserItemRegister g_UserRegister_as[FMKFDCAN_NODE_NB][FMKFDCAN_RX_NUM_REGISTRATION];
/**< Save the number of register already received */
t_uint8 g_CounterUserRegister_ua8[FMKFDCAN_NODE_NB];

/**< Hardware Interrupt Management */
t_eFMKFDCAN_BspStatusCb g_BspCbMngmt_ae[FMKFDCAN_NODE_NB][FMKFDCAN_BSP_CB_NB];

//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
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
static t_eReturnCode s_FMKFDCAN_SetBspNodeInit(FDCAN_HandleTypeDef *f_bspInit_ps, t_sFMKFDCAN_DrvNodeCfg f_NodeCfg_s);
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
static t_eReturnCode s_FMKFDCAN_SetBspTxItem(FDCAN_HandleTypeDef *f_bspInit_ps, t_sFMKFDCAN_DrvNodeCfg f_NodeCfg_s);
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
static void s_FMKFDCAN_BspTxEventCb(FDCAN_HandleTypeDef *f_bspInfo_ps, 
                                              t_uint32 f_EvntCbInfo_u32, 
                                              t_eFMKFDCAN_BspStatusCb f_bspTxCallback_e);
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
static void s_FMKFDCAN_BspRxEventCb(FDCAN_HandleTypeDef *f_bspInfo_ps, 
                                              t_uint32 f_EvntCbInfo_u32, 
                                              t_eFMKFDCAN_BspStatusCb f_bspRxCallback_e);
/**
 *	@brief
 *	@note       Activate Interrupt line 
 *
 *
 *	@param[in] 
 *	@param[in]
 *	 
 *
 *
 */
static t_eReturnCode s_FMKFDCAN_PreOpe(void);
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
static t_eReturnCode s_FMKFDCAN_CopyBspTxItem(t_sFMKFDCAN_TxItemCfg f_TxItemCfg_s, FDCAN_TxHeaderTypeDef *f_bspTxItem_ps);
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
static t_eReturnCode s_FMKFDCAN_SetHwBspCallbackStatus(t_eFMKFDCAN_NodeList f_Node_e ,
                                                        t_eFMKFDCAN_BspCallbackList f_bspCb_e,
                                                        t_eFMKFDCAN_BspStatusCb f_status_e);
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
static t_eReturnCode s_FMKFDCAN_SetHwFifoOpeMode(t_eFMKFDCAN_NodeList f_Node_e ,t_eFMKFDCAN_FifoOpeMode f_fifoMode_e);
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
static t_eReturnCode s_FMKFDCAN_GetBspCallbackId(t_eFMKFDCAN_BspCallbackList f_Callback_e, t_uint32 *f_bspCallback_u32);
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
static t_eReturnCode s_FMKFDCAN_GetBspFifoId(t_eFMKFDCAN_HwRxFifoList f_FifoId_e, t_uint32 *f_bspFifoId_u32);
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
static t_eReturnCode s_FMKFDCAN_GetBspFramePurpose(t_eFMKFDCAN_FramePurpose f_frameType_e, t_uint32 *f_bspFramePurpose_pu32);
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
static t_eReturnCode s_FMKFDCAN_GetBspQueueType(t_eFMKFDCAN_HwTxQueueType f_queueType_e, t_uint32 *f_bspQueueType_pu32);
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
static t_eReturnCode s_FMKFDCAN_GetBspFifoOpeMode(t_eFMKFDCAN_FifoOpeMode f_fifoOpeMode , t_uint32 *f_bspfifoOpeMode_e);
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
static t_eReturnCode s_FMKFDCAN_GetBspHwFifo(t_eFMKFDCAN_HwRxFifoList f_RxFifo_e , t_uint32 *f_bspRxFifo_pu32);
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
static t_eReturnCode s_FMKFDCAN_GetBspIdType(t_eFMKFDCAN_IdentifierType f_IdType, t_uint32 *f_bspIdType_pu32);
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
static t_eReturnCode s_FMKFDCAN_GetBspBitRateStatus(t_eFMKFDCAN_BitRateSwitchStatus f_BitRate_e, t_uint32 *f_BspBitRate_pu32);
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
static t_eReturnCode s_FMKFDCAN_GetBspDlc(t_eFMKFDCAN_BitRateSwitchStatus f_Dlc_e, t_uint32 *f_BspDlc_pu32);
//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*******************
* FMKFDCAN_Init
******************/
t_eReturnCode FMKFDCAN_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    RCC_PeriphCLKInitTypeDef periphNodeInit_s;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_uint8 idxBspCallback_u8;
    t_uint8 idxTxCb_u8;
    t_uint8 idxNode_u8 = (t_uint8)0;
    t_uint8 LLI_u8 = (t_uint8)0;
    t_uint8 LLI2_u8 = (t_uint8)0;
    t_sLIBQUEUE_QueueCfg TxBufferCfg_s = {
        .bufferSize_u8 = FMKFDCAN_TX_SOFT_BUFF_SIZE,
        .elementSize_u8 = sizeof(t_sFMKFDCAN_TxItemBuffer),
        .enableOverwrite_b = False,
    };
    t_sLIBQUEUE_QueueCfg RxBufferCfg_s = {
        .bufferSize_u8 = FMKFDCAN_RX_SOFT_BUFF_SIZE,
        .elementSize_u8 = sizeof(t_sFMKFDCAN_RxItemBuffer),
        .enableOverwrite_b = False,
    };
    

    for (idxNode_u8 = (t_uint8)0 ; (idxNode_u8 < FMKFDCAN_NODE_NB) && (Ret_e == RC_OK) ; idxNode_u8++)
    {   
        // init bufferHead_pv
        RxBufferCfg_s.bufferHead_pv = (void *)NULL;
        // init Node Global Inforamtion
        g_NodeInfo_as[idxNode_u8].Flag_s.ErrorDetected_b      = (t_bool)False;
        g_NodeInfo_as[idxNode_u8].Flag_s.RxQueuePending_b     = (t_bool)False;
        g_NodeInfo_as[idxNode_u8].Flag_s.TxQueuePending_b     = (t_bool)False;
        g_NodeInfo_as[idxNode_u8].Flag_s.TxFramePrioPending_b = (t_bool)False;
        g_NodeInfo_as[idxNode_u8].isNodeActive_b              = (t_bool)False;
        g_NodeInfo_as[idxNode_u8].isNodeConfigured_b          = (t_bool)False;
        
        // Init countor register 
        g_CounterUserRegister_ua8[idxNode_u8] = (t_uint8)0;

        // Init Rx, Tx Management 
        for(idxBspCallback_u8 = (t_uint8)0 ; idxBspCallback_u8 < FMKFDCAN_BSP_CB_NB ; idxBspCallback_u8++)
        {
            g_BspCbMngmt_ae[idxNode_u8][idxBspCallback_u8] = FMKFDCAN_CALLBACK_STATUS_DEACTIVATE;
        }

        // Init Tx, Rx Software Queue
        for(LLI_u8 = (t_uint8)0 ; LLI_u8 < FMKFDCAN_RX_SOFT_BUFF_SIZE ; LLI_u8++)
        {// Rx buffer
            g_RxSoftBuffer_as[idxNode_u8][LLI_u8].BitRateSwitch = (t_uint32)0;
            g_RxSoftBuffer_as[idxNode_u8][LLI_u8].DataLength = (t_uint32)0;
            g_RxSoftBuffer_as[idxNode_u8][LLI_u8].ErrorStateIndicator = (t_uint32)0;
            g_RxSoftBuffer_as[idxNode_u8][LLI_u8].FDFormat = (t_uint32)0;
            g_RxSoftBuffer_as[idxNode_u8][LLI_u8].Identifier = (t_uint32)0;
            g_RxSoftBuffer_as[idxNode_u8][LLI_u8].IdType = (t_uint32)0;
            g_RxSoftBuffer_as[idxNode_u8][LLI_u8].IsFilterMatchingFrame = (t_uint32)0;
            g_RxSoftBuffer_as[idxNode_u8][LLI_u8].RxFrameType = (t_uint32)0;
            g_RxSoftBuffer_as[idxNode_u8][LLI_u8].RxTimestamp = (t_uint32)0;
        }

        for(LLI_u8 = (t_uint8)0 ; LLI_u8 < FMKFDCAN_TX_SOFT_BUFF_SIZE ; LLI_u8++)
        {// TxBuffer
            g_TxSoftBuffer_as[idxNode_u8][LLI_u8].bspTxItem_s.BitRateSwitch = (t_uint32)0;
            g_TxSoftBuffer_as[idxNode_u8][LLI_u8].bspTxItem_s.DataLength = (t_uint32)0;
            g_TxSoftBuffer_as[idxNode_u8][LLI_u8].bspTxItem_s.ErrorStateIndicator = (t_uint32)0;
            g_TxSoftBuffer_as[idxNode_u8][LLI_u8].bspTxItem_s.FDFormat = (t_uint32)0;
            g_TxSoftBuffer_as[idxNode_u8][LLI_u8].bspTxItem_s.Identifier = (t_uint32)0;
            g_TxSoftBuffer_as[idxNode_u8][LLI_u8].bspTxItem_s.IdType = (t_uint32)0;
            g_TxSoftBuffer_as[idxNode_u8][LLI_u8].bspTxItem_s.MessageMarker = (t_uint32)0;
            g_TxSoftBuffer_as[idxNode_u8][LLI_u8].bspTxItem_s.TxEventFifoControl = (t_uint32)0;
            g_TxSoftBuffer_as[idxNode_u8][LLI_u8].bspTxItem_s.TxFrameType = (t_uint32)0;
            // init buffer data
            for (LLI2_u8 = (t_uint8)0; LLI2_u8 < FMKFDCAN_DLC_8 ; LLI2_u8++)
            {
                g_TxSoftBuffer_as[idxNode_u8][LLI_u8].data_ua8[LLI2_u8] = (t_uint8)0;
            }
        }
        // Initialize RxItem Registration 
        for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)FMKFDCAN_RX_NUM_REGISTRATION ; LLI_u8++)
        {
            g_UserRegister_as[idxNode_u8][LLI_u8].itemId_s.Identifier_u32 = (t_uint32)0;
            g_UserRegister_as[idxNode_u8][LLI_u8].itemId_s.FramePurpose_e = FMKFDCAN_FRAME_TYPE_NB;
            g_UserRegister_as[idxNode_u8][LLI_u8].itemId_s.IdType_e = FMKFDCAN_IDTYPE_NB;
            g_UserRegister_as[idxNode_u8][LLI_u8].maskId_u32 = (t_uint32)0;
            g_UserRegister_as[idxNode_u8][LLI_u8].rcvItem_cb = (t_cbFMKFDCAN_RcvItem *)NULL_FONCTION;
        }
        // Configure the Rx, Tx Queue
        RxBufferCfg_s.bufferHead_pv = g_RxSoftBuffer_as[idxNode_u8];
        // Configure Rx Buffer Queue
        Ret_e = LIBQUEUE_Create(&g_RxSoftQueue_as[idxNode_u8], RxBufferCfg_s);
        // Configure Tx Buffer Queue
        if(Ret_e == RC_OK)
        {
            TxBufferCfg_s.bufferHead_pv = g_TxSoftBuffer_as[idxNode_u8];
            Ret_e = LIBQUEUE_Create(&g_TxSoftQueue_as[idxNode_u8], TxBufferCfg_s);
        }

        // Configure FDCAN Clock
    }
    
    // Initialize the FDCAN clock 
    periphNodeInit_s.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
    periphNodeInit_s.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL;
    bspRet_e = HAL_RCCEx_PeriphCLKConfig(&periphNodeInit_s);
    if(bspRet_e != HAL_OK)
    {
        Ret_e = RC_ERROR_WRONG_RESULT;
    }

    return Ret_e;
}

/***********************
* FMKFDCAN_InitDriver
***********************/
t_eReturnCode FMKFDCAN_InitDriver(t_eFMKFDCAN_NodeList f_Node_e, t_sFMKFDCAN_DrvNodeCfg f_NodeCfg_s)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;

    if(f_Node_e > FMKFDCAN_NODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKFDCAN_SetBspNodeInit(&g_NodeInfo_as[f_Node_e].bspNode_s, f_NodeCfg_s);
        if(Ret_e == RC_OK)
        {
            Ret_e = FMKCPU_Set_HwClock(g_NodeInfo_as[f_Node_e].c_Clock_e, FMKCPU_CLOCKPORT_OPE_ENABLE);
        }
        if(Ret_e == RC_OK)
        {
            bspRet_e = HAL_FDCAN_Init(&g_NodeInfo_as[f_Node_e].bspNode_s);
        }
        if(bspRet_e == HAL_OK)
        {
            Ret_e = s_FMKFDCAN_SetHwFifoOpeMode(f_Node_e, f_NodeCfg_s.FifoMode_e);
        }
    }
    if(bspRet_e != HAL_OK)
    {
        Ret_e = RC_ERROR_WRONG_RESULT;
    }
    
    return Ret_e;
}

/*********************************
* FMKFDCAN_ConfigureRxItemEvent
*********************************/
t_eReturnCode FMKFDCAN_ConfigureRxItemEvent(t_eFMKFDCAN_NodeList f_Node_e, t_sFMKFDCAN_RxItemEventCfg f_RxItemCfg_s)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxCounter_u8 = (t_uint8)0;

    if((f_Node_e > FMKFDCAN_NODE_NB)
    || (f_RxItemCfg_s.callback_cb == (t_cbFMKFDCAN_RcvItem *)NULL_FONCTION))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_NodeInfo_as[f_Node_e].isNodeConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }
    if(g_CounterUserRegister_ua8[f_Node_e] >= FMKFDCAN_RX_NUM_REGISTRATION)
    {
        Ret_e = RC_ERROR_LIMIT_REACHED;
    }
    if(Ret_e == RC_OK)
    {
        idxCounter_u8 = g_CounterUserRegister_ua8[f_Node_e];
        g_UserRegister_as[f_Node_e][idxCounter_u8].itemId_s.Identifier_u32 = f_RxItemCfg_s.ItemId_s.Identifier_u32;
        g_UserRegister_as[f_Node_e][idxCounter_u8].itemId_s.FramePurpose_e = f_RxItemCfg_s.ItemId_s.FramePurpose_e;
        g_UserRegister_as[f_Node_e][idxCounter_u8].itemId_s.IdType_e = f_RxItemCfg_s.ItemId_s.IdType_e;
        g_UserRegister_as[f_Node_e][idxCounter_u8].maskId_u32 = f_RxItemCfg_s.maskId_u32;
        g_UserRegister_as[f_Node_e][idxCounter_u8].rcvItem_cb = f_RxItemCfg_s.callback_cb;

        // update countor Register
        g_CounterUserRegister_ua8[f_Node_e] += (t_uint8)1;
    }

    return Ret_e;
}

/*********************************
* FMKFDCAN_SendTxItem
*********************************/
t_eReturnCode FMKFDCAN_SendTxItem(t_eFMKFDCAN_NodeList f_Node_e, t_sFMKFDCAN_TxItemCfg f_TxItemCfg_s)
{
    t_eReturnCode Ret_e = RC_OK;
    FDCAN_TxHeaderTypeDef bspTxItem_s;
    t_sFMKFDCAN_TxItemBuffer SoTxitem_s;
    HAL_StatusTypeDef bspRet_e = HAL_OK;

    t_uint32 fifoLevel_u32 = 0;


    if(f_Node_e > FMKFDCAN_NODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_Modulestate_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_BUSY;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKFDCAN_CopyBspTxItem(f_TxItemCfg_s, &bspTxItem_s);
        if(Ret_e == RC_OK)
        {
            fifoLevel_u32 = HAL_FDCAN_GetTxFifoFreeLevel(&g_NodeInfo_as[f_Node_e].bspNode_s);

            // if the buffer is not full, add directly the message 
            // else put it in the software buffer onmy if there <= DLC_8 Bytes
            //and activate notification to send from HAL Callback
            if(fifoLevel_u32 > (t_uint32)0)
            {
                bspRet_e = HAL_FDCAN_AddMessageToTxFifoQ(&g_NodeInfo_as[f_Node_e].bspNode_s,
                                                        &bspTxItem_s,
                                                        f_TxItemCfg_s.CanMsg_s.data_pu8);
            }
            // if hardware fifo Tx full, put in in software fifo if dlc <= 8
            else if (f_TxItemCfg_s.CanMsg_s.Dlc_e <= FMKFDCAN_DLC_8)
            {
                // copy structure into SoTxitem_s
                Ret_e = LIBQUEUE_WriteElement(&g_TxSoftQueue_as[f_Node_e], &SoTxitem_s);
                // update flag Tx Item to send
                if(Ret_e == RC_OK)
                {
                    g_NodeInfo_as[f_Node_e].Flag_s.TxQueuePending_b |= True;
                    // Activate Notification 
                    Ret_e = s_FMKFDCAN_SetHwBspCallbackStatus(f_Node_e, 
                                                            FMKFDCAN_BSP_TX_CB_BUFFER_COMPLETE,
                                                            FMKFDCAN_CALLBACK_STATUS_ACTIVATE);
                }
            }
            else 
            {
                Ret_e = RC_WARNING_BUSY;
            }
        }
        
    }
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*****************************
* s_FMKFDCAN_BspTxEventCb
******************************/
static void s_FMKFDCAN_BspTxEventCb(FDCAN_HandleTypeDef *f_bspInfo_ps, 
                                              t_uint32 f_EvntCbInfo_u32, 
                                              t_eFMKFDCAN_BspStatusCb f_bspTxCallback_e)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_uint8 TxQueueSize_u8;
    t_uint8 idxNode_u8;
    t_uint8 msgSendCount_u8 = (t_uint8)0;
    t_sFMKFDCAN_TxItemBuffer SoftTxItem_s;

    if(f_bspInfo_ps == (FDCAN_HandleTypeDef *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        for(idxNode_u8 = (t_uint8)0 ; idxNode_u8 < FMKFDCAN_NODE_NB ; idxNode_u8++)
        {
            if(&g_NodeInfo_as[idxNode_u8].bspNode_s == f_bspInfo_ps)
            {
                break;
            }
        }
        if(idxNode_u8 != FMKFDCAN_NODE_NB)
        {

        
            switch(f_bspTxCallback_e)
            {
                case FMKFDCAN_BSP_TX_CB_EVENT:
                {
                    break;
                }
                case FMKFDCAN_BSP_TX_CB_BUFFER_COMPLETE:
                case FMKFDCAN_BSP_TX_CB_FIFO_EMPTY:
                {
                    // Check if there are messages pending in the queue
                    if (g_NodeInfo_as[idxNode_u8].Flag_s.TxQueuePending_b == (t_bool)True)
                    {
                        LIBQUEUE_GetActualSize(&g_TxSoftQueue_as[idxNode_u8], &TxQueueSize_u8);

                        // Process messages from the queue, respecting the maximum limit per interrupt
                        t_uint8 msgProcessed_u8 = 0;
                        while ((TxQueueSize_u8 > 0) 
                            && (msgProcessed_u8 < (t_uint8)FMKFDCAN_MAX_TX_ITEM_SEND_PER_IT))
                        {
                            // Read an element from the queue
                            Ret_e = LIBQUEUE_ReadElement(&g_TxSoftQueue_as[idxNode_u8], &SoftTxItem_s);
                            if (Ret_e != RC_OK)
                            {
                                // Exit loop on read failure
                                break;
                            }

                            // Attempt to send the message to the hardware buffer
                            bspRet_e = HAL_FDCAN_AddMessageToTxFifoQ(&g_NodeInfo_as[idxNode_u8].bspNode_s,
                                                                    &SoftTxItem_s.bspTxItem_s,
                                                                    SoftTxItem_s.data_ua8);
                            if (bspRet_e != HAL_OK)
                            {
                                Ret_e = RC_ERROR_WRONG_RESULT;
                                break;
                            }

                            // Increment processed message count
                            msgProcessed_u8++;

                            // Update the queue size
                            LIBQUEUE_GetActualSize(&g_TxSoftQueue_as[idxNode_u8], &TxQueueSize_u8);
                        }

                        // If the queue is empty, deactivate the callback and update the flag
                        if (TxQueueSize_u8 == 0)
                        {
                            Ret_e = s_FMKFDCAN_SetHwBspCallbackStatus(idxNode_u8, 
                                                                    FMKFDCAN_BSP_TX_CB_BUFFER_COMPLETE,
                                                                    FMKFDCAN_CALLBACK_STATUS_DEACTIVATE);
                            g_NodeInfo_as[idxNode_u8].Flag_s.TxQueuePending_b = (t_bool)False;
                        }
                    }
                        
                        
                        break;
                }
                case FMKFDCAN_BSP_TX_CB_BUFFER_ABORT:
                    break;

                case FMKFDCAN_BSP_RX_CB_FIFO_0:
                case FMKFDCAN_BSP_RX_CB_FIFO_1:
                default:
                    break;
            }
        }
    }
}

/*****************************
* s_FMKFDCAN_BspRxEventCb
******************************/
static void s_FMKFDCAN_BspRxEventCb(FDCAN_HandleTypeDef *f_bspInfo_ps, 
                                    t_uint32 f_EvntCbInfo_u32, 
                                    t_eFMKFDCAN_BspStatusCb f_bspRxCallback_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxNode_u8;

    if(f_bspInfo_ps == (FDCAN_HandleTypeDef *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        for(idxNode_u8 = (t_uint8)0 ; idxNode_u8 < FMKFDCAN_NODE_NB ; idxNode_u8++)
        {
            if(&g_NodeInfo_as[idxNode_u8].bspNode_s == f_bspInfo_ps)
            {
                break;
            }
        }
        if(idxNode_u8 != FMKFDCAN_NODE_NB)
        {
            switch(f_bspRxCallback_e)
            {
                case FMKFDCAN_BSP_RX_CB_FIFO_0:
                case FMKFDCAN_BSP_RX_CB_FIFO_1:
                {

                    break;
                }
                case FMKFDCAN_BSP_TX_CB_EVENT:
                case FMKFDCAN_BSP_TX_CB_BUFFER_COMPLETE:
                case FMKFDCAN_BSP_TX_CB_BUFFER_ABORT:
                case FMKFDCAN_BSP_TX_CB_FIFO_EMPTY:
                case FMKFDCAN_BSP_CB_NB:
                default: 
                    break;
            }
            
        }

    }
}
/*****************************
* s_FMKFDCAN_SetBspNodeInit
******************************/
static t_eReturnCode s_FMKFDCAN_SetBspNodeInit(FDCAN_HandleTypeDef *f_bspInit_ps, t_sFMKFDCAN_DrvNodeCfg f_NodeCfg_s)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKFDCAN_Baudrate dataBaudrate_e;
    t_eFMKFDCAN_Baudrate frameBaudrate_e;
    t_uint32 bspTxQueueType_u32;

    if(f_bspInit_ps == (FDCAN_HandleTypeDef *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        // copy information 
        dataBaudrate_e = f_NodeCfg_s.DataBaudrate_e;
        frameBaudrate_e = f_NodeCfg_s.FrameBaudrate_e;
        // Get the  Type
        Ret_e = s_FMKFDCAN_GetBspQueueType(f_NodeCfg_s.QueueType_e, &bspTxQueueType_u32);

        // Global configuration Init 
        f_bspInit_ps->Init.ClockDivider = (t_uint32)f_NodeCfg_s.clockDivider_u32;
        f_bspInit_ps->Init.Mode = FMKFDCAN_NODE_MODE;
        f_bspInit_ps->Init.AutoRetransmission = ENABLE;
        f_bspInit_ps->Init.TransmitPause = DISABLE;
        f_bspInit_ps->Init.ProtocolException = ENABLE;
        f_bspInit_ps->Init.StdFiltersNbr = (t_uint32)0;
        f_bspInit_ps->Init.ExtFiltersNbr = (t_uint32)0;
        f_bspInit_ps->Init.TxFifoQueueMode = bspTxQueueType_u32;

        // Init for nominal baudrate
        f_bspInit_ps->Init.NominalPrescaler = c_FmkCan_BspBaudrateCfg_as[frameBaudrate_e].prescaler_u16;
        f_bspInit_ps->Init.NominalSyncJumpWidth = c_FmkCan_BspBaudrateCfg_as[frameBaudrate_e].syncSeg_u8;
        f_bspInit_ps->Init.NominalTimeSeg1 = c_FmkCan_BspBaudrateCfg_as[frameBaudrate_e].timeSeg1_u8;
        f_bspInit_ps->Init.NominalTimeSeg2 = c_FmkCan_BspBaudrateCfg_as[frameBaudrate_e].timeSeg2_u8;

        // depending on complete configuration 
        switch(f_NodeCfg_s.ProtocolUse_e)
        {
            case FMKFDCAN_PROTOCOL_CAN2_0B:
                f_bspInit_ps->Init.FrameFormat = FDCAN_FRAME_CLASSIC;
                break;

            case FMKFDCAN_PROTOCOL_FDCAN_BRS:
                f_bspInit_ps->Init.FrameFormat = FDCAN_FRAME_FD_BRS;
                // Init for Data Baudrate
                f_bspInit_ps->Init.DataPrescaler = c_FmkCan_BspBaudrateCfg_as[dataBaudrate_e].prescaler_u16;
                f_bspInit_ps->Init.DataSyncJumpWidth = c_FmkCan_BspBaudrateCfg_as[dataBaudrate_e].syncSeg_u8;
                f_bspInit_ps->Init.DataTimeSeg1 = c_FmkCan_BspBaudrateCfg_as[dataBaudrate_e].timeSeg1_u8;
                f_bspInit_ps->Init.DataTimeSeg2 = c_FmkCan_BspBaudrateCfg_as[dataBaudrate_e].timeSeg2_u8;
                break;

            case  FMKFDCAN_PROTOCOL_FDCAN_NO_BRS:
                f_bspInit_ps->Init.FrameFormat = FDCAN_FRAME_FD_NO_BRS;
                break;

            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }
    return Ret_e;
}

/*********************************
* FMKFDCAN_SendTxItem
*********************************/
static t_eReturnCode s_FMKFDCAN_CopyBspTxItem(t_sFMKFDCAN_TxItemCfg f_TxItemCfg_s, FDCAN_TxHeaderTypeDef *f_bspTxItem_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspFramePurpose_u32;
    t_uint32 bspDlc_u32;
    t_uint32 bspFDFormat_u32;
    t_uint32 bspIdType_u32;
    t_uint32 bspBitRateStatus_u32;

    if (f_bspTxItem_ps == (FDCAN_TxHeaderTypeDef *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {   
        Ret_e = s_FMKFDCAN_GetBspDlc(f_TxItemCfg_s.CanMsg_s.Dlc_e, &bspDlc_u32);
        if(Ret_e = RC_OK)
        {
            Ret_e = s_FMKFDCAN_GetBspFDFormat(f_TxItemCfg_s.frameFormat_e, &bspFDFormat_u32);
        }
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKFDCAN_GetBspIdType(f_TxItemCfg_s.ItemId_s.IdType_e, &bspIdType_u32);
        }
        if(Ret_e == RC_OK)
        {
            s_FMKFDCAN_GetBspFramePurpose(f_TxItemCfg_s.ItemId_s.FramePurpose_e, &bspFramePurpose_u32);
        }
        if(Ret_e == RC_OK)
        {
            s_FMKFDCAN_GetBspBitRateStatus(f_TxItemCfg_s.BitRate_e, &bspBitRateStatus_u32);
        }
        if(Ret_e == RC_OK)
        {
            f_bspTxItem_ps->Identifier          = (t_uint32)f_TxItemCfg_s.ItemId_s.Identifier_u32;
            f_bspTxItem_ps->IdType              = (t_uint32)bspIdType_u32;
            f_bspTxItem_ps->BitRateSwitch       = (t_uint32)bspBitRateStatus_u32;
            f_bspTxItem_ps->DataLength          = (t_uint32)bspDlc_u32;
            f_bspTxItem_ps->FDFormat            = (t_uint32)bspFDFormat_u32;
            f_bspTxItem_ps->TxEventFifoControl  = (t_uint32)FDCAN_NO_TX_EVENTS;
            f_bspTxItem_ps->TxFrameType         = (t_uint32)bspFramePurpose_u32;
            f_bspTxItem_ps->MessageMarker       = (t_uint32)0;
            f_bspTxItem_ps->ErrorStateIndicator = (t_uint32)0;
        }
        
    }

    return Ret_e;
}

/************************************
* s_FMKFDCAN_SetHwBspCallbackStatus
***********************************/
static t_eReturnCode s_FMKFDCAN_SetHwBspCallbackStatus(t_eFMKFDCAN_NodeList f_Node_e ,
                                                        t_eFMKFDCAN_BspCallbackList f_bspCb_e,
                                                        t_eFMKFDCAN_BspStatusCb f_status_e)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_uint32 bspCbId_u32;
    t_uint32 bspFifo_u32;
    t_uint8 idxTxFifo_u8;

    if((f_bspCb_e > FMKFDCAN_BSP_CB_NB)
    || (f_status_e > FMKFDCAN_CALLBACK_STATUS_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKFDCAN_GetBspCallbackId(f_bspCb_e, &bspCbId_u32);
    }
    if(Ret_e == RC_OK)
    {
        if ((g_BspCbMngmt_ae[f_Node_e][f_bspCb_e] & f_status_e) == 0)
        {
            
            switch(f_status_e)
            {
                case FMKFDCAN_CALLBACK_STATUS_ACTIVATE:
                {
                    // according datasheet, if IT_Tx is in the loop, 
                    // specify the TxFifo 
                    // Here we activate interruption on all Fifo
                    if((bspCbId_u32 == FDCAN_IT_TX_COMPLETE)
                    || bspCbId_u32 == FDCAN_IT_TX_ABORT_COMPLETE)
                    {
                        for(idxTxFifo_u8 = (t_uint8)0 ; idxTxFifo_u8 < FMKFDCAN_HW_TX_FIFO_NB ; idxTxFifo_u8++)
                        {
                            Ret_e = s_FMKFDCAN_GetBspTxFifoId(idxTxFifo_u8, &bspFifo_u32);
                            if(Ret_e == RC_OK)
                            {
                                bspRet_e = HAL_FDCAN_ActivateNotification(&g_NodeInfo_as[f_Node_e].bspNode_s,
                                                                        (t_uint32)bspCbId_u32,
                                                                        (t_uint32)bspFifo_u32);
                            }
                        }  
                    }
                    else
                    {
                        bspRet_e = HAL_FDCAN_ActivateNotification(&g_NodeInfo_as[f_Node_e].bspNode_s,
                                                                        (t_uint32)bspCbId_u32,
                                                                        (t_uint32)NULL);
                    }
                    break;
                }
                case FMKFDCAN_CALLBACK_STATUS_DEACTIVATE:
                {
                    bspRet_e = HAL_FDCAN_DeactivateNotification(&g_NodeInfo_as[f_Node_e].bspNode_s,
                                                                bspCbId_u32);
                    break;
                }
                case FMKFDCAN_CALLBACK_STATUS_NB:
                default:
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;
            }
        }
    }

    return Ret_e;
}
/*****************************
* s_FMKFDCAN_GetBspFramePurpose
******************************/
static t_eReturnCode s_FMKFDCAN_GetBspFramePurpose(t_eFMKFDCAN_FramePurpose f_frameType_e, t_uint32 *f_bspFramePurpose_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_frameType_e > FMKFDCAN_FRAME_TYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspFramePurpose_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_frameType_e)
        {
            case FMKFDCAN_FRAME_TYPE_DATA:
                *f_bspFramePurpose_pu32 = FDCAN_DATA_FRAME;
                break;

            case FMKFDCAN_FRAME_TYPE_REMOTE:
                *f_bspFramePurpose_pu32 = FDCAN_REMOTE_FRAME;
                break;

            case FMKFDCAN_FRAME_TYPE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }
    
    return Ret_e;
}
/*****************************
* s_FMKFDCAN_GetBspIdType
******************************/
static t_eReturnCode s_FMKFDCAN_GetBspIdType(t_eFMKFDCAN_IdentifierType f_IdType, t_uint32 *f_bspIdType_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_IdType > FMKFDCAN_IDTYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspIdType_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_IdType)
        {
            case FMKFDCAN_IDTYPE_STANDARD:
                *f_bspIdType_pu32 = FDCAN_STANDARD_ID;
                break;

            case FMKFDCAN_IDTYPE_EXTENDED:
                *f_bspIdType_pu32 = FDCAN_EXTENDED_ID;
                break;

            case FMKFDCAN_FRAME_TYPE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }
    
    return Ret_e;
}

/********************************
* s_FMKFDCAN_GetBspBitRateStatus
********************************/
static t_eReturnCode s_FMKFDCAN_GetBspBitRateStatus(t_eFMKFDCAN_BitRateSwitchStatus f_BitRate_e, t_uint32 *f_BspBitRate_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_BitRate_e > FMKFDCAN_BITRATE_SWITCH_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_BspBitRate_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_BitRate_e)
        {
            case FMKFDCAN_BITRATE_SWITCH_ON:
                *f_BspBitRate_pu32 = FDCAN_BRS_ON;
                break;

            case FMKFDCAN_BITRATE_SWITCH_OFF:
                *f_BspBitRate_pu32 = FDCAN_BRS_OFF;
                break;

            case FMKFDCAN_FRAME_TYPE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }
    
    return Ret_e;
}

/*****************************
* s_FMKFDCAN_GetBspDlc
******************************/
static t_eReturnCode s_FMKFDCAN_GetBspDlc(t_eFMKFDCAN_BitRateSwitchStatus f_Dlc_e, t_uint32 *f_BspDlc_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_Dlc_e > FMKFDCAN_DLC_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_BspDlc_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_Dlc_e)
        {
            case FMKFDCAN_DLC_0:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_0;
                break;
            case FMKFDCAN_DLC_1:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_1;
                break;
            case FMKFDCAN_DLC_2:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_2;
                break;
            case FMKFDCAN_DLC_3:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_3;
                break;
            case FMKFDCAN_DLC_4:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_4;
                break;
            case FMKFDCAN_DLC_5:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_5;
                break;
            case FMKFDCAN_DLC_6:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_6;
                break;
            case FMKFDCAN_DLC_7:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_7;
                break;
            case FMKFDCAN_DLC_8:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_8;
                break;
            case FMKFDCAN_DLC_16:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_16;
                break;
            case FMKFDCAN_DLC_20:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_20;
                break;
            case FMKFDCAN_DLC_24:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_24;
                break;
            case FMKFDCAN_DLC_32:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_32;
                break;
            case FMKFDCAN_DLC_48:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_48;
                break;
            case FMKFDCAN_DLC_64:
                *f_BspDlc_pu32 = FDCAN_DLC_BYTES_64;
                break;

            case FMKFDCAN_DLC_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }
    
    return Ret_e;
}

static t_eReturnCode s_FMKFDCAN_GetBspCallbackId(t_eFMKFDCAN_BspCallbackList f_Callback_e, t_uint32 *f_bspCallback_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_Callback_e > FMKFDCAN_FRAME_FORMAT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspCallback_u32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_Callback_e)
        {
            case FMKFDCAN_BSP_TX_CB_EVENT: 
                *f_bspCallback_u32 =FDCAN_IT_LIST_TX_FIFO_ERROR;
                break;
            case FMKFDCAN_BSP_TX_CB_BUFFER_COMPLETE:
                *f_bspCallback_u32 =FDCAN_IT_TX_COMPLETE;
                break;
            case FMKFDCAN_BSP_TX_CB_BUFFER_ABORT:
                *f_bspCallback_u32 =FDCAN_IT_TX_ABORT_COMPLETE;
                break;
            case FMKFDCAN_BSP_TX_CB_FIFO_EMPTY:
                *f_bspCallback_u32 =FDCAN_IT_TX_FIFO_EMPTY;
                break;
            case FMKFDCAN_BSP_RX_CB_FIFO_0:
                *f_bspCallback_u32 =FDCAN_IT_LIST_RX_FIFO0;
                break;
            case FMKFDCAN_BSP_RX_CB_FIFO_1:
                *f_bspCallback_u32 =FDCAN_IT_LIST_RX_FIFO1;
                break;
            case FMKFDCAN_BSP_CB_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }
    
    return Ret_e;
}

/*****************************
* s_FMKFDCAN_GetBspFifoId
********************************/
static t_eReturnCode s_FMKFDCAN_GetBspFifoId(t_eFMKFDCAN_HwRxFifoList f_FifoId_e, t_uint32 *f_bspFifoId_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_FifoId_e > FMKFDCAN_HW_RX_FIFO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspFifoId_u32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_FifoId_e)
        {
            case FMKFDCAN_HW_RX_FIFO_1: 
                *f_bspFifoId_u32 =FDCAN_RX_FIFO0;
                break;

            case FMKFDCAN_HW_RX_FIFO_2:
                *f_bspFifoId_u32 =FDCAN_RX_FIFO1;
                break;

            case FMKFDCAN_HW_RX_FIFO_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }
    
    return Ret_e;
}

/*****************************
* s_FMKFDCAN_GetBspFDFormat
******************************/
static t_eReturnCode s_FMKFDCAN_GetBspFDFormat(t_eFMKFDCAN_FrameFormat f_formatType_e, t_uint32 *f_BspFormatType_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_formatType_e > FMKFDCAN_FRAME_FORMAT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_BspFormatType_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_formatType_e)
        {
            case FMKFDCAN_FRAME_FORMAT_CLASSIC:
                *f_BspFormatType_pu32 = FDCAN_CLASSIC_CAN;
                break;

            case FMKFDCAN_FRAME_FORMAT_FDCAN:
                *f_BspFormatType_pu32 = FDCAN_FD_CAN;
                break;

            case FMKFDCAN_FRAME_TYPE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }
    
    return Ret_e;
}
/*****************************
* s_FMKFDCAN_GetBspQueueType
******************************/
static t_eReturnCode s_FMKFDCAN_GetBspQueueType(t_eFMKFDCAN_HwTxQueueType f_queueType_e, t_uint32 *f_bspQueueType_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_queueType_e > FMKFDCAN_HWQUEUE_TYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspQueueType_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_queueType_e)
        {
            case FMKFDCAN_HWQUEUE_TYPE_NORMAL:
                *f_bspQueueType_pu32 = FDCAN_TX_QUEUE_OPERATION;
                break;

            case FMKFDCAN_HWQUEUE_TYPE_FIFO:
                *f_bspQueueType_pu32 = FDCAN_TX_FIFO_OPERATION;
                break;
            
            case FMKFDCAN_HWQUEUE_TYPE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }
    
    return Ret_e;
}

/*****************************
* s_FMKFDCAN_GetBspQueueType
*****************************/
static t_eReturnCode s_FMKFDCAN_GetBspFifoOpeMode(t_eFMKFDCAN_FifoOpeMode f_fifoOpeMode , t_uint32 *f_bspfifoOpeMode_e)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_fifoOpeMode > FMKFDCAN_FIFO_OPEMODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspfifoOpeMode_e == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_fifoOpeMode)
        {
            case FMKFDCAN_FIFO_OPEMODE_OVERWRITE:
                *f_bspfifoOpeMode_e = FDCAN_RX_FIFO_OVERWRITE;
                break;

            case FMKFDCAN_FIFO_OPEMODE_BLOCKING:
                *f_bspfifoOpeMode_e = FDCAN_RX_FIFO_BLOCKING;
                break;
            
            case FMKFDCAN_FIFO_OPEMODE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }
    
    return Ret_e;
}

/*****************************
* s_FMKFDCAN_GetBspHwFifo
*****************************/
static t_eReturnCode s_FMKFDCAN_GetBspHwFifo(t_eFMKFDCAN_HwRxFifoList f_RxFifo_e , t_uint32 *f_bspRxFifo_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_RxFifo_e > FMKFDCAN_HW_RX_FIFO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspRxFifo_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_RxFifo_e)
        {
            case FMKFDCAN_HW_RX_FIFO_1:
                *f_bspRxFifo_pu32 = FDCAN_RX_FIFO0;
                break;

            case FMKFDCAN_HW_RX_FIFO_2:
                *f_bspRxFifo_pu32 = FDCAN_RX_FIFO1;
                break;
            
            case FMKFDCAN_HW_RX_FIFO_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }
    return Ret_e;
}

/*****************************
* s_FMKFDCAN_SetHwFifoOpeMode
******************************/
static t_eReturnCode s_FMKFDCAN_SetHwFifoOpeMode(t_eFMKFDCAN_NodeList f_Node_e ,t_eFMKFDCAN_FifoOpeMode f_fifoMode_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxFifo_u8 = 0;
    t_uint32 bspFifo_u32;
    t_uint32 bspFifoOpeMode_u32;
    HAL_StatusTypeDef bspRet_e = HAL_OK;

    if(f_fifoMode_e > FMKFDCAN_FIFO_OPEMODE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        for (idxFifo_u8 = (t_uint8)0 ; (idxFifo_u8 < FMKFDCAN_HW_RX_FIFO_NB) && (Ret_e == RC_OK); idxFifo_u8++)    
        {
            Ret_e = s_FMKFDCAN_GetBspHwFifo(idxFifo_u8, &bspFifo_u32);
            if(Ret_e == RC_OK)
            {
                Ret_e = s_FMKFDCAN_GetBspFifoOpeMode(f_fifoMode_e, &bspFifoOpeMode_u32);
                
            }
            if(Ret_e == RC_OK)
            {
                bspRet_e = HAL_FDCAN_ConfigRxFifoOverwrite(&g_NodeInfo_as[f_Node_e].bspNode_s, bspFifo_u32, bspFifoOpeMode_u32);
            }
            if(bspRet_e != HAL_OK)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
        }
    }
    return Ret_e;
}
//********************************************************************************
//                      Hardware Callback Management
//********************************************************************************
/**********************************
* HAL_FDCAN_TxEventFifoCallback
**********************************/
void HAL_FDCAN_TxEventFifoCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t TxEventFifoITs)
{
    s_FMKFDCAN_BspTxEventCb(hfdcan, TxEventFifoITs, FMKFDCAN_BSP_TX_CB_EVENT);
}
/**********************************
* HAL_FDCAN_TxFifoEmptyCallback
**********************************/
void HAL_FDCAN_TxFifoEmptyCallback(FDCAN_HandleTypeDef *hfdcan)
{
    s_FMKFDCAN_BspTxEventCb(hfdcan, NULL, FMKFDCAN_BSP_TX_CB_FIFO_EMPTY);
}
/**********************************
* HAL_FDCAN_TxBufferCompleteCallback
**********************************/
void HAL_FDCAN_TxBufferCompleteCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes)
{
    s_FMKFDCAN_BspTxEventCb(hfdcan, BufferIndexes, FMKFDCAN_BSP_TX_CB_BUFFER_COMPLETE);
}
/**********************************
* HAL_FDCAN_TxBufferAbortCallback
**********************************/
void HAL_FDCAN_TxBufferAbortCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t BufferIndexes)
{
    s_FMKFDCAN_BspTxEventCb(hfdcan, BufferIndexes, FMKFDCAN_BSP_TX_CB_BUFFER_ABORT);
}

/**********************************
* HAL_FDCAN_RxFifo1Callback
**********************************/
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
    s_FMKFDCAN_BspRxEventCb(hfdcan, RxFifo1ITs, FMKFDCAN_BSP_RX_CB_FIFO_0);
}
/**********************************
* HAL_FDCAN_RxFifo0Callback
**********************************/
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    s_FMKFDCAN_BspRxEventCb(hfdcan, RxFifo0ITs, FMKFDCAN_BSP_RX_CB_FIFO_0);
}
//************************************************************************************
// End of File
//************************************************************************************

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
