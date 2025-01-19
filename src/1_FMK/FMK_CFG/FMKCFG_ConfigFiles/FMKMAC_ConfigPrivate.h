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
    #include "../FMKCFG_ConfigSpecific/FMKMAC_ConfigSpecific.h"
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
    /**< Variable to mapp every Dma Mux to a Rcc Clock */
    const t_eFMKCPU_ClockPort c_FmkMac_DmaMuxRccMapp_ae[FMKMAC_DMA_MUX_NB] ={
           FMKCPU_RCC_CLK_DMAMUX1
    };

    /**< Variable to mapp every Dma Request to a Dma Channel */
    const t_sFMKMAC_DmaRqstCfg c_FmkMac_DmaRqstCfg_as[FMKMAC_DMA_RQSTYPE_NB] ={
        {FMKMAC_DMA_CTRL_1,             FMKMAC_DMA_CHANNEL_5,          FMKMAC_DMA_TRANSPRIO_MEDIUM},   // FMKMAC_DMA_RQSTYPE_ADC1
        {FMKMAC_DMA_CTRL_1,             FMKMAC_DMA_CHANNEL_4,          FMKMAC_DMA_TRANSPRIO_MEDIUM},   // FMKMAC_DMA_RQSTYPE_ADC2
        {FMKMAC_DMA_CTRL_1,             FMKMAC_DMA_CHANNEL_3,          FMKMAC_DMA_TRANSPRIO_MEDIUM},   // FMKMAC_DMA_RQSTYPE_ADC3
        {FMKMAC_DMA_CTRL_2,             FMKMAC_DMA_CHANNEL_1,          FMKMAC_DMA_TRANSPRIO_MEDIUM},   // FMKMAC_DMA_RQSTYPE_UART4_RX
        {FMKMAC_DMA_CTRL_2,             FMKMAC_DMA_CHANNEL_2,          FMKMAC_DMA_TRANSPRIO_MEDIUM},   // FMKMAC_DMA_RQSTYPE_UART4_TX
        {FMKMAC_DMA_CTRL_1,             FMKMAC_DMA_CHANNEL_6,          FMKMAC_DMA_TRANSPRIO_MEDIUM},   // FMKMAC_DMA_RQSTYPE_USART1_RX
        {FMKMAC_DMA_CTRL_1,             FMKMAC_DMA_CHANNEL_7,          FMKMAC_DMA_TRANSPRIO_MEDIUM},   // FMKMAC_DMA_RQSTYPE_USART1_TX
        {FMKMAC_DMA_CTRL_1,             FMKMAC_DMA_CHANNEL_2,          FMKMAC_DMA_TRANSPRIO_MEDIUM},   // FMKMAC_DMA_RQSTYPE_USART2_RX
        {FMKMAC_DMA_CTRL_1,             FMKMAC_DMA_CHANNEL_1,          FMKMAC_DMA_TRANSPRIO_MEDIUM},   // FMKMAC_DMA_RQSTYPE_USART2_TX
        {FMKMAC_DMA_CTRL_2,             FMKMAC_DMA_CHANNEL_3,          FMKMAC_DMA_TRANSPRIO_MEDIUM},   // FMKMAC_DMA_RQSTYPE_TIM8_CH1
    };

    /* CAUTION : Automatic generated code section for Variable: End */

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
