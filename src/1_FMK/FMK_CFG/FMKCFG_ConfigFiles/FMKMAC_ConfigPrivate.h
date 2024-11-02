/*********************************************************************
 * @file        FMKMAC_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKMAC_CONFIGPRIVATE_H_INCLUDED
#define FMKMAC_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./FMKMAC_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    /* CAUTION : Automatic generated code section for DMA channels number: Start */
    #define FMKMAC_DMA_1_MAX_CHANNELS ((t_uint8)5)
    /* CAUTION : Automatic generated code section for DMA channels number: End */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------TYPEDEF TYPES---------------------------//

    //-----------------------------STRUCT TYPES---------------------------//
    /**< Structure for Hardware Dma Configuration for a request type */
    typedef struct 
    {
        t_eFMKMAC_DmaController         Ctrl_e;
        t_eFMKMAC_DmaChnl               Chnl_e;
        t_eFMKMAC_DmaTransferPriority   transfPrio_e;
    } t_sFMKMAC_DmaRqstCfg;

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
    // Flag generate code
    const t_sFMKMAC_DmaRqstCfg c_FmkMac_DmaRqstCfg_as[FMKMAC_DMA_RQSTYPE_NB] = {
        {FMKMAC_DMA_CTRL_1        ,FMKMAC_DMA_CHANNEL_1,     FMKMAC_DMA_TRANSPRIO_HIGH},  // FMKMAC_DMA_RQSTYPE_ADC1
        {FMKMAC_DMA_CTRL_1        ,FMKMAC_DMA_CHANNEL_2,     FMKMAC_DMA_TRANSPRIO_HIGH},  // FMKMAC_DMA_RQSTYPE_SPI1
        {FMKMAC_DMA_CTRL_1        ,FMKMAC_DMA_CHANNEL_4,     FMKMAC_DMA_TRANSPRIO_HIGH},  // FMKMAC_DMA_RQSTYPE_SPI2
        {FMKMAC_DMA_CTRL_1        ,FMKMAC_DMA_CHANNEL_3,     FMKMAC_DMA_TRANSPRIO_HIGH}   // FMKMAC_DMA_RQSTYPE_UART1
    };
    // Flag generate code
    const t_uint8 c_FmkMac_DmaMaxChnl_ua8[FMKMAC_DMA_CTRL_NB] = {
        (t_uint8)FMKMAC_DMA_1_MAX_CHANNELS,
    };

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
