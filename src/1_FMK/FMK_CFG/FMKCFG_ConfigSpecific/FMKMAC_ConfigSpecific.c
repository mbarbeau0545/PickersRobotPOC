/*********************************************************************
 * @file        FMKMAC_ConfigSpecific.h
 * @brief       Template_BriefDescription.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./FMKMAC_ConfigSpecific.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************

//-----------------------------ENUM TYPES-----------------------------//

//-----------------------------STRUCT TYPES---------------------------//

//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************

//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/***********************************
 * FMKMAC_SetRequestType
 ***********************************/
t_eReturnCode FMKMAC_SetRequestType(t_eFMKMAC_DmaRqst f_RqstType_e,
                                    DMA_HandleTypeDef * f_bspDma_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_RqstType_e > FMKMAC_DMA_RQSTYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspDma_ps == (DMA_HandleTypeDef *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_RqstType_e)
        {   
            /* CAUTION : Automatic generated code section for Request Dma: Start */
            case FMKMAC_DMA_RQSTYPE_ADC1:
                f_bspDma_ps->Init.Request = DMA_REQUEST_ADC1;
                break;
            case FMKMAC_DMA_RQSTYPE_ADC2:
                f_bspDma_ps->Init.Request = DMA_REQUEST_ADC2;
                break;
            case FMKMAC_DMA_RQSTYPE_ADC3:
                f_bspDma_ps->Init.Request = DMA_REQUEST_ADC3;
                break;
            case FMKMAC_DMA_RQSTYPE_UART4_RX:
                f_bspDma_ps->Init.Request = DMA_REQUEST_UART4_RX;
                break;
            case FMKMAC_DMA_RQSTYPE_UART4_TX:
                f_bspDma_ps->Init.Request = DMA_REQUEST_UART4_TX;
                break;
            case FMKMAC_DMA_RQSTYPE_USART1_RX:
                f_bspDma_ps->Init.Request = DMA_REQUEST_USART1_RX;
                break;
            case FMKMAC_DMA_RQSTYPE_USART1_TX:
                f_bspDma_ps->Init.Request = DMA_REQUEST_USART1_TX;
                break;
            case FMKMAC_DMA_RQSTYPE_USART2_RX:
                f_bspDma_ps->Init.Request = DMA_REQUEST_USART2_RX;
                break;
            case FMKMAC_DMA_RQSTYPE_USART2_TX:
                f_bspDma_ps->Init.Request = DMA_REQUEST_USART2_TX;
                break;
            /* CAUTION : Automatic generated code section for Request Dma: End */

            case FMKMAC_DMA_RQSTYPE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }

    return Ret_e;
}

//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
           
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
