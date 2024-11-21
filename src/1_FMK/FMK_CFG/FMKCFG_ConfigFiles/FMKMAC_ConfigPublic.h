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
    #include "stm32g4xx_hal.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKMAC_ADC_DMA_MODE DMA_CIRCULAR /**< DMA Mode for adc's */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------TYPEDEF TYPES---------------------------//
    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    // Flag automatic generate code 
    /**< Enum for the different request available for DMA service */
    typedef enum 
    {
        FMKMAC_DMA_RQSTYPE_ADC1 = 0,    /**< Reference to bsp dma request for ADC1 */
        FMKMAC_DMA_RQSTYPE_SPI1,        /**< Reference to bsp dma request for SPI1 */
        FMKMAC_DMA_RQSTYPE_SPI2,        /**< Reference to bsp dma request for SPI2 */
        FMKMAC_DMA_RQSTYPE_UART1,       /**< Reference to bsp dma request for UART1 */

        FMKMAC_DMA_RQSTYPE_NB,

    } t_eFMKMAC_DmaRqstType;


    // Flag automatic generate code
    /**< Enum for Dma Number */
    typedef enum
    {
        FMKMAC_DMA_CTRL_1 = 0x0U, 

        FMKMAC_DMA_CTRL_NB
    } t_eFMKMAC_DmaController;

    // Flag automatic generate code
    /**< Enum for number of channel in DMA */
    typedef enum 
    {
        FMKMAC_DMA_CHANNEL_1 = 0x0U,
        FMKMAC_DMA_CHANNEL_2, 
        FMKMAC_DMA_CHANNEL_3, 
        FMKMAC_DMA_CHANNEL_4,
        FMKMAC_DMA_CHANNEL_5,

        FMKMAC_DMA_CHANNEL_NB, 
    } t_eFMKMAC_DmaChnl;

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
