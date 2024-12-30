/*********************************************************************
 * @file        FMK_SRL.h
 * @brief       UART/USART Module.
 * @details     This module allows user to Transmit and Receive messages
 *              using UART/USART protocol.\n
 *              Configuration Private File.\n
 *              
 *
 * @author      mba
 * @date        21/12/2024
 * @version     1.0
 */
  
#ifndef FMKSRL_CONFIGPRIVATE_H_INCLUDED
#define FMKSRL_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./FMKSRL_ConfigPublic.h"
    #include "FMK_CFG/FMKCFG_ConfigSpecific/FMKSRL_ConfigSpecific.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKSRL_TIMEOUT_POLLING ((t_uint32)0x0000FFFF)

    #define FMKSRL_MAX_BYTES_TO_SEND ((t_uint16)256)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    typedef enum __t_eFMKSRL_BspTransmitOpe
    {
        FMKSRL_BSP_TX_OPE_TRANSMIT = 0x00,
        FMKSRL_BSP_TX_OPE_TRANSMIT_RECEIVE,

        FMKSRL_BSP_TX_OPE_NB
    } t_eFMKSRL_BspTransmitOpe;

    typedef enum __t_eFMKSRL_BspReceiveOpe
    {
        FMKSRL_BSP_RX_OPE_RECEIVE = 0x00,
        FMKSRL_BSP_RX_OPE_RECEIVE_IDLE,
#ifdef FMKCPU_STM32_ECU_FAMILY_G
        FMKSRL_BSP_RX_OPE_RECEIVE_TIMEOUT,
#endif
        FMKSRL_BSP_RX_OPE_NB
    } t_eFMKSRL_BspReceiveOpe;

    typedef enum __t_eFMKSRL_BspAbortOpe
    {
        FMKSRL_OPE_ABORT_RECEPTION = 0x00,
        FMKSRL_OPE_ABORT_TRANSMISSION,
        FMKSRL_OPE_ABORT_BOTH,

        FMKSRL_OPE_ABORT_NB
    } t_eFMKSRL_BspAbortOpe;
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------TYPEDEF TYPES---------------------------//
    /**
    *
    *	@brief      HAL UART.USART function to Receive/ TRansmit in Polling Mode
    *               is used in blocking mode 
    *
    *	@param[in]      bspHandle_pv        : the UART/USART Handle_TypeDef
    *	@param[out]     f_data_pu8          : the pointer to the data
    *	@param[out]     f_dataSize_u16      : the data size
    *	@param[out]     f_timeOut_u32       : tiume out in polling mode
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef HAL_StatusTypeDef (t_cbFMKSRL_BspRxTx_Poll)(   void * bspHandle_pv, 
                                                    t_uint8 *f_data_pu8, 
                                                    t_uint16 f_dataSize_u16,
                                                    t_uint32 f_timeOut_u32);

    /**
    *
    *	@brief      HAL UART.USART function to Receive/ TRansmit in Polling Mode
    *               is used in blocking mode 
    *
    *	@param[in]      bspHandle_pv        : the UART/USART Handle_TypeDef
    *	@param[out]     f_data_pu8          : the pointer to the data
    *	@param[out]     f_dataSize_u16      : the data size
    *	@param[out]     f_timeOut_u32       : tiume out in polling mode
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */

    /**
    *
    *	@brief      HAL UART.USART function to Receive/ TRansmit in Interrupt Mode
    *
    *	@param[in]      bspHandle_pv        : the UART/USART Handle_TypeDef
    *	@param[out]     f_data_pu8          : the pointer to the data
    *	@param[out]     f_dataSize_u16      : the data size
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef HAL_StatusTypeDef (t_cbFMKSRL_BspRxTx_IT)(   void * bspHandle_pv, 
                                                    t_uint8 *f_data_pu8, 
                                                    t_uint16 f_dataSize_u16);

    /**
    *
    *	@brief      HAL UART.USART function to Receive/ TRansmit in Dma Mode 
    *
    *	@param[in]      bspHandle_pv        : the UART/USART Handle_TypeDef
    *	@param[out]     f_data_pu8          : the pointer to the data
    *	@param[out]     f_dataSize_u16      : the data size
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef HAL_StatusTypeDef (t_cbFMKSRL_BspRxTx_DMA)(   void * bspHandle_pv, 
                                                    t_uint8 *f_data_pu8, 
                                                    t_uint16 f_dataSize_u16);

    /**
    *
    *	@brief      HAL UART.USART function Abort Polling Mode
    *
    *	@param[in]      bspHandle_pv        : the UART/USART Handle_TypeDef
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef HAL_StatusTypeDef (t_cbFMKSRL_BspAbort)(void * bspHandle_pv);
    /**
    *
    *	@brief      HAL UART.USART function Abort Interrupt Mode
    *
    *	@param[in]      bspHandle_pv        : the UART/USART Handle_TypeDef
    *
    *   @retval HAL_OK                     @ref HAL_OK
    *   @retval HAL_ERROR                  @ref HAL_ERROR
    */
    typedef HAL_StatusTypeDef (t_cbFMKSRL_BspAbort_IT)(void * bspHandle_pv);
    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    typedef struct __t_sFMKSRL_BspRxTxFunc
    {
        t_cbFMKSRL_BspRxTx_Poll *       bspRxTxPoll_pcb;
        t_cbFMKSRL_BspRxTx_IT   *       bspRxTxIT_pcb;
        t_cbFMKSRL_BspRxTx_DMA  *       bspRxTxDMA_pcb;
    } t_sFMKSRL_BspRxTxFunc;

    typedef struct __t_sFMKSRL_BspAbortFunc
    {
        t_cbFMKSRL_BspAbort    *       bspAbortPoll_pcb;
        t_cbFMKSRL_BspAbort_IT *       bspAbortIT_pcb;
        t_cbFMKSRL_BspAbort_IT *       bspAbortDMA_pcb;
    } t_sFMKSRL_BspAbortFunc;
    
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    //flag automatic generated code 
    USART_TypeDef * c_FmkSrl_BspInitIstcMapp_pas[FMKSRL_SERIAL_LINE_NB] = {
        USART2,
        UART4,
    };
    const t_sFMKSRL_BspRxTxFunc c_FmkSrl_RxBspFunc_apf[FMKSRL_HW_PROTOCOL_NB] = {
        {FMKSRL_HAL_UART_Receive,      FMKSRL_HAL_UART_Receive_IT ,        FMKSRL_HAL_UART_Receive_DMA},   // FMKSRL_HW_PROTOCOL_UART
        {FMKSRL_HAL_USART_Receive,     FMKSRL_HAL_USART_Receive_IT,        FMKSRL_HAL_USART_Receive_DMA},  // FMKSRL_HW_PROTOCOL_USART
        
    };

    const t_sFMKSRL_BspRxTxFunc c_FmkSrl_TxBspFunc_apf[FMKSRL_HW_PROTOCOL_NB] = {
        {FMKSRL_HAL_UART_Transmit,      FMKSRL_HAL_UART_Transmit_IT ,        FMKSRL_HAL_UART_Transmit_DMA},   // FMKSRL_HW_PROTOCOL_UART
        {FMKSRL_HAL_USART_Transmit,     FMKSRL_HAL_USART_Transmit_IT,        FMKSRL_HAL_USART_Transmit_DMA},  // FMKSRL_HW_PROTOCOL_USART
    };    
    const t_sFMKSRL_BspAbortFunc c_FmkSrl_AbortBspFunc_apf[FMKSRL_HW_PROTOCOL_NB] = {
        {FMKSRL_HAL_UART_Abort,        FMKSRL_HAL_UART_Abort_IT,      FMKSRL_HAL_UART_Abort_IT},         // FMKSRL_HW_PROTOCOL_UART    
        {FMKSRL_HAL_USART_Abort,       FMKSRL_HAL_USART_Abort_IT,     FMKSRL_HAL_USART_Abort_IT},        // FMKSRL_HW_PROTOCOL_USART
    };

    const t_sFMKSRL_BspAbortFunc c_FmkSrl_AbortRxBspFunc_apf[FMKSRL_HW_PROTOCOL_NB] = {
        {FMKSRL_HAL_UART_AbortReceive,              FMKSRL_HAL_UART_AbortReceive_IT,         FMKSRL_HAL_UART_AbortReceive_IT},   // FMKSRL_HW_PROTOCOL_UART    
        {NULL_FONCTION,                             NULL_FONCTION,                           NULL_FONCTION},                     // FMKSRL_HW_PROTOCOL_USART
    };

    const t_sFMKSRL_BspAbortFunc c_FmkSrl_AbortTxBspFunc_apf[FMKSRL_HW_PROTOCOL_NB] = {
        {FMKSRL_HAL_UART_AbortTransmit,             FMKSRL_HAL_UART_AbortTransmit_IT,         FMKSRL_HAL_UART_AbortTransmit_IT},   // FMKSRL_HW_PROTOCOL_UART    
        {NULL_FONCTION,                             NULL_FONCTION,                            NULL_FONCTION},                      // FMKSRL_HW_PROTOCOL_USART
    };
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKSRL_CONFIGPRIVATE_H_INCLUDED           
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
