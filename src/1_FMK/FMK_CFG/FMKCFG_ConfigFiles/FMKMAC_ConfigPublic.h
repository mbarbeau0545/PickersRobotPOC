/*********************************************************************
 * @file        FMKCDA_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKMAC_CONFIGPUBLIC_H_INCLUDED
#define FMKMAC_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "./FMKCPU_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKMAC_ADC_DMA_MODE         (DMA_CIRCULAR)      /**< DMA Mode for adc's */
    #define FMKMAC_UART_RX_DMA_MODE     (DMA_CIRCULAR)        /**< DMA Mode Uart for Rx */
    #define FMKMAC_UART_TX_DMA_MODE     (DMA_NORMAL)      /**< DMA Mode Uart for Tx */
    #define FMKMAC_USART_RX_DMA_MODE    (DMA_CIRCULAR)      /**< DMA Mode Uart for Rx */
    #define FMKMAC_USART_TX_DMA_MODE    (DMA_NORMAL)      /**< DMA Mode Uart for Tx */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    /* CAUTION : Automatic generated code section for Enum: Start */
    /* Enum for the different request available for DMA service */
    typedef enum
    {
        FMKMAC_DMA_RQSTYPE_ADC1 = 0x0,               /**< Reference to Bsp Dma Request for ADC1 */
        FMKMAC_DMA_RQSTYPE_SPI1,                     /**< Reference to Bsp Dma Request for SPI1 */
        FMKMAC_DMA_RQSTYPE_SPI2,                     /**< Reference to Bsp Dma Request for SPI2 */
        FMKMAC_DMA_RQSTYPE_UART4_RX,                 /**< Reference to Bsp Dma Request for UART4_RX */
        FMKMAC_DMA_RQSTYPE_UART4_TX,                 /**< Reference to Bsp Dma Request for UART4_TX */
        FMKMAC_DMA_RQSTYPE_USART1_RX,                /**< Reference to Bsp Dma Request for USART1_RX */
        FMKMAC_DMA_RQSTYPE_USART1_TX,                /**< Reference to Bsp Dma Request for USART1_TX */
        FMKMAC_DMA_RQSTYPE_USART2_RX,                /**< Reference to Bsp Dma Request for USART2_RX */
        FMKMAC_DMA_RQSTYPE_USART2_TX,                /**< Reference to Bsp Dma Request for USART2_TX */
    
        FMKMAC_DMA_RQSTYPE_NB,
    } t_eFMKMAC_DmaRqst;

    /* Enum for Number of Dma */
    typedef enum
    {
        FMKMAC_DMA_CTRL_1 = 0x0,                  /**< Reference to DMA 1 */
        FMKMAC_DMA_CTRL_2,                        /**< Reference to DMA 2 */
    
        FMKMAC_DMA_CTRL_NB,
    } t_eFMKMAC_DmaController;

    /* Enum for number of channel in DMA */
    typedef enum
    {
        FMKMAC_DMA_CHANNEL_1 = 0x0,                  /**< Reference to Channel 1 */
        FMKMAC_DMA_CHANNEL_2,                        /**< Reference to Channel 2 */
        FMKMAC_DMA_CHANNEL_3,                        /**< Reference to Channel 3 */
        FMKMAC_DMA_CHANNEL_4,                        /**< Reference to Channel 4 */
        FMKMAC_DMA_CHANNEL_5,                        /**< Reference to Channel 5 */
        FMKMAC_DMA_CHANNEL_6,                        /**< Reference to Channel 6 */
        FMKMAC_DMA_CHANNEL_7,                        /**< Reference to Channel 7 */
        FMKMAC_DMA_CHANNEL_8,                        /**< Reference to Channel 8 */
    
        FMKMAC_DMA_CHANNEL_NB,
    } t_eFMKMAC_DmaChnl;

    /* CAUTION : Automatic generated code section for Enum: End */

    /**< Reference to Dma Priority */
    typedef enum
    {
        FMKMAC_DMA_TRANSPRIO_LOW = 0x0U,
        FMKMAC_DMA_TRANSPRIO_MEDIUM,
        FMKMAC_DMA_TRANSPRIO_HIGH,
        FMKMAC_DMA_TRANSPRIO_VERY_HIGH,

        FMKMAC_DMA_TRANSPRIO_NB,
    } t_eFMKMAC_DmaTransferPriority;

    /**< Reference for Dma Transfer Direction */
    typedef enum
    {
        FMKMAC_DMA_TRANSDIR_MEM_TO_MEM = 0x0U,
        FMKMAC_DMA_TRANSDIR_PERIPH_TO_MEM,
        FMKMAC_DMA_TRANSDIR_MEM_TO_PERIPH,

        FMKMAC_DMA_TRANSDIR_NB
    } t_eFMKMAC_DmaTransferDir;
    //-----------------------------TYPEDEF TYPES---------------------------//
    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // *******************************************************************

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKMAC_CONFIGPUBLIC_H_INCLUDED           
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
