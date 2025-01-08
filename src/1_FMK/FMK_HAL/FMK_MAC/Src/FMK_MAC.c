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
#include "./FMK_MAC.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKMAC_ConfigPrivate.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//
typedef enum 
{
    FMKMAC_ERRSTATE_OK = 0x000U,                     /**< No error detected */
    FMKMAC_ERRSTATE_TRANSFER_COMPLETE = 0x001,       /**< THe transfer is completed with an error */
    FMKMAC_ERRSTATE_TRANSFER_ERROR = 0x002,          /**< THe transfer is incomplete with an error */
    FMKMAC_ERRSTATE_FIFO = 0x004,                    /**< FIFO error, over/under debit from FIFO to DMA */
    FMKMAC_ERRSTATE_DIRECT_MODE = 0x008,             /**< An error with direct mode DMA has been detected*/
    FMKMAC_ERRSTATE_INVALID_CHANNEL = 0x010,         /**< DMA cannal invalid */
    FMKMAC_ERRSTATE_CONFIGURATION = 0x020,           /**< A configuration error has been detected */
    FMKMAC_ERRSTATE_PRIORITY = 0x040,                /**< Priority DMA has not been respected */
    FMKMAC_ERRSTATE_MEM_ALLOCATION = 0x080,          /**< Error allocation memory (FIFO not allowed) */
    FMKMAC_ERRSTATE_TIMEOUT = 0x100                  /**< Timeout delay (transfer has take too many time)*/
} t_eFMKMAC_DmaChnlErr;


/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//

typedef struct
{
    DMA_HandleTypeDef bspDma_ps;            /**< @ref  DMA_HandleTypeDef*/
    const t_eFMKCPU_IRQNType c_IRQNType_e;                   /**< NVIC channel interruption config*/
    t_eFMKMAC_DmaChnlErr chnlErr_e;         /**< @ref t_eFMKMAC_DmaChnlErr*/
    t_bool isChnlConfigured_b;
} t_sFMKMAC_DmaChnlInfo;

typedef struct 
{
    t_sFMKMAC_DmaChnlInfo channel_as[FMKMAC_DMA_CHANNEL_NB];        /**< @ref  t_sFMKMAC_DmaChnlInfo*/
    const t_eFMKCPU_ClockPort c_clock_e;                              /**< constant to store the clock for each ADC */                                         /**< Flag channel is configured */
} t_sFMKMAC_DmaInfo;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
t_eFMKCPU_ClockPortOpe g_DmaMuxState_ae[FMKMAC_DMA_MUX_NB];
t_eFMKCPU_ClockPortOpe g_DmaCtrlState_ae[FMKMAC_DMA_CTRL_NB];
/* CAUTION : Automatic generated code section for Variable: Start */
/**< Variable to store information about the Dma and the Channel */
t_sFMKMAC_DmaInfo g_DmaInfo_as[FMKMAC_DMA_CTRL_NB] = {
     {//------- DMA1_CONTROLLER -------//
        .c_clock_e = FMKCPU_RCC_CLK_DMA1,
        .channel_as = {


            [FMKMAC_DMA_CHANNEL_1] = {
                .bspDma_ps = {.Instance = DMA1_Channel1},
               .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL1_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_2] = {
                .bspDma_ps = {.Instance = DMA1_Channel2},
               .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL2_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_3] = {
                .bspDma_ps = {.Instance = DMA1_Channel3},
               .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL3_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_4] = {
                .bspDma_ps = {.Instance = DMA1_Channel4},
               .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL4_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_5] = {
                .bspDma_ps = {.Instance = DMA1_Channel5},
               .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL5_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_6] = {
                .bspDma_ps = {.Instance = DMA1_Channel6},
               .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL6_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_7] = {
                .bspDma_ps = {.Instance = DMA1_Channel7},
               .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL7_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_8] = {
                .bspDma_ps = {.Instance = DMA1_Channel8},
               .c_IRQNType_e = FMKCPU_NVIC_DMA1_CHANNEL8_IRQN,
            },

        }
    },
     {//------- DMA2_CONTROLLER -------//
        .c_clock_e = FMKCPU_RCC_CLK_DMA2,
        .channel_as = {


            [FMKMAC_DMA_CHANNEL_1] = {
                .bspDma_ps = {.Instance = DMA2_Channel1},
               .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL1_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_2] = {
                .bspDma_ps = {.Instance = DMA2_Channel2},
               .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL2_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_3] = {
                .bspDma_ps = {.Instance = DMA2_Channel3},
               .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL3_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_4] = {
                .bspDma_ps = {.Instance = DMA2_Channel4},
               .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL4_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_5] = {
                .bspDma_ps = {.Instance = DMA2_Channel5},
               .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL5_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_6] = {
                .bspDma_ps = {.Instance = DMA2_Channel6},
               .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL6_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_7] = {
                .bspDma_ps = {.Instance = DMA2_Channel7},
               .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL7_IRQN,
            },

            [FMKMAC_DMA_CHANNEL_8] = {
                .bspDma_ps = {.Instance = DMA2_Channel8},
               .c_IRQNType_e = FMKCPU_NVIC_DMA2_CHANNEL8_IRQN,
            },

        }
    },
};

/* CAUTION : Automatic generated code section for Variable: End */


static t_eCyclicModState g_FmkMac_ModState_e = STATE_CYCLIC_CFG;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
*
*	@brief      Function to get the bsp dma channel
*
*	@param[in]  f_channel_e              : enum value for the channel, value from @ref t_eFMKCPU_InterruptChnl
*	@param[in]  f_bspChnl_pu32           : storage for bsp channel.\n
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
*  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
*
*/
static t_eReturnCode s_FMKMAC_Set_DmaBspCfg(t_eFMKMAC_DmaRqst f_RqstType_e,
                                            t_eFMKMAC_DmaType f_Type_e,
                                            DMA_HandleTypeDef * f_bspDma_ps,
                                            t_eFMKMAC_DmaTransferPriority f_dmaPrio_e,
                                            t_uFMKMAC_DmaHandleType * f_modHandle_pu);

/**
*
*	@brief      Link Dma Depending on the Request Type
*
*	@param[in]  f_channel_e              : enum value for the channel, value from @ref t_eFMKCPU_InterruptChnl
*	@param[in]  f_bspChnl_pu32           : storage for bsp channel.\n
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
*  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
*
*/
static t_eReturnCode s_FMKMAC_SetDmaHwInit(t_eFMKMAC_DmaController f_dmaCtrl_e);

/**
*
*	@brief      Link Dma Depending on the Request Type
*
*	@param[in]  f_channel_e              : enum value for the channel, value from @ref t_eFMKCPU_InterruptChnl
*	@param[in]  f_bspChnl_pu32           : storage for bsp channel.\n
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
*  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
*
*/
static t_eReturnCode s_FMKMAC_LinkDma(  t_eFMKMAC_DmaType f_DmaType_e,
                                        DMA_HandleTypeDef * f_bspDma_ps,
                                        t_uFMKMAC_DmaHandleType * f_modHandle_pu);

/**
*
*	@brief      Function to get the bsp dma priority
*
*	@param[in]  f_channel_e              : enum value for the channel, value from @ref t_eFMKCPU_InterruptChnl
*	@param[in]  f_bspPriority_pu32       : storage for bsp prioirty.\n
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
*  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
*
*/
static t_eReturnCode s_FMKMAC_Get_DmaBspPriority(t_eFMKMAC_DmaTransferPriority f_priority_e, t_uint32 * f_bspPriority_pu32);
//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * FMKMAC_Init
 *********************************/
t_eReturnCode FMKMAC_Init(void)
{
    t_uint8 idxDma_u8;
    t_uint8 idxChnl_u8;
    t_uint8 idxDmaMux_u8;

    //--------- Loop on every Dma ---------//
    for(idxDma_u8 = (t_uint8)0 ; idxDma_u8 < FMKMAC_DMA_CTRL_NB ; idxDma_u8++)
    {

        //--------- Loop on every Channel ---------//
        for(idxChnl_u8 = (t_uint8)0 ; idxChnl_u8 < FMKMAC_DMA_CHANNEL_NB ; idxChnl_u8++)
        {
            g_DmaInfo_as[idxDma_u8].channel_as[idxDma_u8].isChnlConfigured_b = (t_bool)False;
            g_DmaInfo_as[idxDma_u8].channel_as[idxDma_u8].chnlErr_e = FMKMAC_ERRSTATE_OK;
        }

        g_DmaCtrlState_ae[idxDma_u8] = FMKCPU_CLOCKPORT_OPE_DISABLE;
    }

    //--------- Loop on every Dma Mux ---------//
    for(idxDmaMux_u8 = (t_uint8)0 ; idxDmaMux_u8 < FMKMAC_DMA_MUX_NB ; idxDmaMux_u8++)
    {
        g_DmaMuxState_ae[idxDmaMux_u8] = FMKCPU_CLOCKPORT_OPE_DISABLE;
    }

    return RC_OK;
}
/*********************************
 * FMKMAC_Cyclic
 *********************************/
t_eReturnCode FMKMAC_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch (g_FmkMac_ModState_e)
    {
        case STATE_CYCLIC_CFG:
    {
        g_FmkMac_ModState_e = STATE_CYCLIC_WAITING;
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_WAITING:
    {
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_PREOPE:
    {
        g_FmkMac_ModState_e = STATE_CYCLIC_OPE;
        break;
    }
    case STATE_CYCLIC_OPE:
    {
        if(Ret_e < RC_OK)
        {
            g_FmkMac_ModState_e = STATE_CYCLIC_ERROR;
        }
        break;
    }
    case STATE_CYCLIC_ERROR:
    {
        break;
    }
    case STATE_CYCLIC_BUSY:
    default:
        Ret_e = RC_OK;
        break;
    }
    return Ret_e;
}
/*********************************
 * FMKMAC_GetState
 *********************************/
t_eReturnCode FMKMAC_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    
    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_FmkMac_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * FMKMAC_SetState
 *********************************/
t_eReturnCode FMKMAC_SetState(t_eCyclicModState f_State_e)
{
    g_FmkMac_ModState_e = f_State_e;
    return RC_OK;
}

/***********************************
 * FMKMAC_RqstDmaInit
 ***********************************/
t_eReturnCode FMKMAC_RqstDmaInit(   t_eFMKMAC_DmaRqst f_DmaRqstType,
                                    t_eFMKMAC_DmaType f_Type_e,
                                    void *f_ModuleHandle_pv)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_eFMKMAC_DmaChnl channel_e;
    t_eFMKMAC_DmaController dmaCtrl_e;
    t_sFMKMAC_DmaChnlInfo * DmaChnl_ps;

    if (f_DmaRqstType >= FMKMAC_DMA_RQSTYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    } 
    if(f_ModuleHandle_pv == (void *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //--------- Reach Information ---------//
        dmaCtrl_e = c_FmkMac_DmaRqstCfg_as[f_DmaRqstType].Ctrl_e;
        channel_e = c_FmkMac_DmaRqstCfg_as[f_DmaRqstType].Chnl_e;
        DmaChnl_ps = &g_DmaInfo_as[dmaCtrl_e].channel_as[channel_e];

        //--------- Check validity ---------//
        if(DmaChnl_ps->isChnlConfigured_b == (t_bool)True)
        {
            Ret_e = RC_ERROR_ALREADY_CONFIGURED;
        }
        if(Ret_e == RC_OK)
        {
            //--------- configure hardware clock to access register ---------//
            Ret_e = s_FMKMAC_SetDmaHwInit(dmaCtrl_e);

            if(Ret_e == RC_OK)
            {
                //--------- Configure Dma channel NVIC priority ---------//
                Ret_e = FMKCPU_Set_NVICState(   DmaChnl_ps->c_IRQNType_e, 
                                                FMKCPU_NVIC_OPE_ENABLE);
            }
            if(Ret_e == RC_OK)
            {   
                //--------- Configure Dma Channel ---------//
                Ret_e = s_FMKMAC_Set_DmaBspCfg( f_DmaRqstType, 
                                                f_Type_e,
                                                &DmaChnl_ps->bspDma_ps,
                                                c_FmkMac_DmaRqstCfg_as[f_DmaRqstType].transfPrio_e,
                                                (t_uFMKMAC_DmaHandleType *)f_ModuleHandle_pv);
            }
            if(Ret_e == RC_OK)
            {
                //---------call Bsp Init ---------//
                bspRet_e = HAL_DMA_Init(&DmaChnl_ps->bspDma_ps);
                if(bspRet_e == HAL_OK)
                {
                    //------ Link DMA Management ------//
                    Ret_e = s_FMKMAC_LinkDma( f_Type_e,
                                            &DmaChnl_ps->bspDma_ps,
                                            (t_uFMKMAC_DmaHandleType *)f_ModuleHandle_pv);

                    if(Ret_e == RC_OK)
                    {
                        DmaChnl_ps->isChnlConfigured_b = (t_bool)True;
                        //--------- Enable The Complete Callback ---------//
                        __HAL_DMA_ENABLE_IT(&DmaChnl_ps->bspDma_ps, DMA_IT_TC); // transfer-complete
                    }
                }
                else
                {   
                    Ret_e = RC_ERROR_WRONG_RESULT;
                }
            }
        }   
    }

    return Ret_e;
}

//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/***********************************
 * s_FMKMAC_SetDmaHwInit
 ***********************************/
static t_eReturnCode s_FMKMAC_SetDmaHwInit(t_eFMKMAC_DmaController f_dmaCtrl_e)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_bool s_isDmaMuxCfgDone_b = False;

    t_uint8 idxDmaMux_u8;
    
    //--------- Set Dma Mux Hardware Clock ---------//
    if(s_isDmaMuxCfgDone_b == (t_bool)False)
    {
        for(idxDmaMux_u8 = (t_uint8)0 ; 
             (idxDmaMux_u8 < FMKMAC_DMA_MUX_NB) 
         &&  (Ret_e == RC_OK) ; 
            idxDmaMux_u8++)
        {
            Ret_e = FMKCPU_Set_HwClock(c_FmkMac_DmaMuxRccMapp_ae[idxDmaMux_u8], FMKCPU_CLOCKPORT_OPE_ENABLE);
        }
        if(Ret_e == RC_OK)
        {
            s_isDmaMuxCfgDone_b = True;
        }
    }

    //--------- Set Dma Controller Hardware Clock ---------//
    if(Ret_e == RC_OK)
    {
        if(g_DmaCtrlState_ae[f_dmaCtrl_e] == FMKCPU_CLOCKPORT_OPE_DISABLE)
        {
            Ret_e = FMKCPU_Set_HwClock(g_DmaInfo_as[f_dmaCtrl_e].c_clock_e, FMKCPU_CLOCKPORT_OPE_ENABLE);
            if(Ret_e == RC_OK)
            {
                g_DmaCtrlState_ae[f_dmaCtrl_e] = FMKCPU_CLOCKPORT_OPE_ENABLE;
            }
        }
    }

    return Ret_e;
}
/***********************************
 * s_FMKMAC_SetDmaBspCfg
 ***********************************/
static t_eReturnCode s_FMKMAC_Set_DmaBspCfg(t_eFMKMAC_DmaRqst f_RqstType_e,
                                                t_eFMKMAC_DmaType f_Type_e,
                                                DMA_HandleTypeDef * f_bspDma_ps,
                                                t_eFMKMAC_DmaTransferPriority f_dmaPrio_e,
                                                t_uFMKMAC_DmaHandleType * f_modHandle_pu)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspPriority_u32 = 0;

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
        Ret_e = s_FMKMAC_Get_DmaBspPriority(f_dmaPrio_e, &bspPriority_u32);
    }
    if(Ret_e == RC_OK)
    {
        //------ Set Priority ------//
        f_bspDma_ps->Init.Priority = bspPriority_u32;
        
        //------ Set request dma Init ------//
        Ret_e = FMKMAC_SetRequestType(f_RqstType_e, f_bspDma_ps);

        //------ Set Init Depending On Dma Type ------//
        if(Ret_e == RC_OK)
        {
            switch (f_Type_e)
            {
                case FMKMAC_DMA_TYPE_ADC:
                {
                    f_bspDma_ps->Init.Direction = DMA_PERIPH_TO_MEMORY;
                    f_bspDma_ps->Init.Mode      = FMKMAC_ADC_DMA_MODE;
                    f_bspDma_ps->Init.PeriphInc = DMA_PINC_DISABLE;
                    f_bspDma_ps->Init.MemInc    = DMA_MINC_ENABLE;
                    f_bspDma_ps->Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
                    f_bspDma_ps->Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
                
                    break;
                }
                case FMKMAC_DMA_TYPE_UART_RX:
                {
                    f_bspDma_ps->Init.Direction = DMA_PERIPH_TO_MEMORY;
                    f_bspDma_ps->Init.Mode      = FMKMAC_UART_RX_DMA_MODE;
                    f_bspDma_ps->Init.PeriphInc = DMA_PINC_DISABLE;
                    f_bspDma_ps->Init.MemInc    = DMA_MINC_ENABLE;
                    f_bspDma_ps->Init.MemDataAlignment     = DMA_MDATAALIGN_BYTE;
                    f_bspDma_ps->Init.PeriphDataAlignment  = DMA_PDATAALIGN_BYTE;
                    
                    break;
                }
                case FMKMAC_DMA_TYPE_UART_TX:
                {
                    f_bspDma_ps->Init.Direction = DMA_MEMORY_TO_PERIPH;
                    f_bspDma_ps->Init.Mode      = FMKMAC_UART_TX_DMA_MODE;
                    f_bspDma_ps->Init.PeriphInc = DMA_PINC_DISABLE;
                    f_bspDma_ps->Init.MemInc    = DMA_MINC_ENABLE;
                    f_bspDma_ps->Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
                    f_bspDma_ps->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
                    break;
                }
                case FMKMAC_DMA_TYPE_USART_RX:
                {
                    //DMA_PERIPH_TO_MEMORY
                    Ret_e = RC_ERROR_MISSING_CONFIG;
                    break;
                }
                case FMKMAC_DMA_TYPE_USART_TX:
                {
                    //DMA_MEMORY_TO_PERIPH
                    Ret_e = RC_ERROR_MISSING_CONFIG;
                    break;
                }
                case FMKMAC_DMA_TYPE_SPI:
                {
                    Ret_e = RC_ERROR_MISSING_CONFIG;
                    break;
                }
                case FMKMAC_DMA_TYPE_NB:
                default:
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;
                }
            }
        }
    }

    return Ret_e;
}

/***********************************
 * s_FMKMAC_Get_DmaBspPriority
 ***********************************/
static t_eReturnCode s_FMKMAC_Get_DmaBspPriority(t_eFMKMAC_DmaTransferPriority f_priority_e, t_uint32 * f_bspPriority_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_priority_e > FMKMAC_DMA_TRANSPRIO_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspPriority_pu32 == (t_uint32 *)0)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_priority_e)
        {
            case FMKMAC_DMA_TRANSPRIO_LOW:
                *f_bspPriority_pu32 = DMA_PRIORITY_LOW;
                break;
            case FMKMAC_DMA_TRANSPRIO_MEDIUM:
                *f_bspPriority_pu32 = DMA_PRIORITY_MEDIUM;
                break;
            case FMKMAC_DMA_TRANSPRIO_HIGH:
                *f_bspPriority_pu32 = DMA_PRIORITY_HIGH;
                break;
            case FMKMAC_DMA_TRANSPRIO_VERY_HIGH:
                *f_bspPriority_pu32 = DMA_PRIORITY_VERY_HIGH;
                break;
            case FMKMAC_DMA_TRANSPRIO_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }
    return Ret_e;
}

/***********************************
 * s_FMKMAC_LinkDma
 ***********************************/
static t_eReturnCode s_FMKMAC_LinkDma(  t_eFMKMAC_DmaType f_DmaType_e,
                                        DMA_HandleTypeDef * f_bspDma_ps,
                                        t_uFMKMAC_DmaHandleType * f_modHandle_pu)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_DmaType_e > FMKMAC_DMA_TYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if((f_modHandle_pu == (t_uFMKMAC_DmaHandleType *)NULL)
    || (f_bspDma_ps == (DMA_HandleTypeDef *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_DmaType_e)
        {   
            case FMKMAC_DMA_TYPE_ADC:
                __HAL_LINKDMA(&f_modHandle_pu->adcHandle_s, DMA_Handle, *f_bspDma_ps);
                break;
          
            case FMKMAC_DMA_TYPE_UART_RX:
                __HAL_LINKDMA((&f_modHandle_pu->uartHandle_s), hdmarx, *f_bspDma_ps);
                break;

            case FMKMAC_DMA_TYPE_UART_TX:
                __HAL_LINKDMA((&f_modHandle_pu->uartHandle_s), hdmatx, *f_bspDma_ps);
                break;
            
            case FMKMAC_DMA_TYPE_USART_RX:
                __HAL_LINKDMA((&f_modHandle_pu->usartHandle_s), hdmarx, *f_bspDma_ps);
                break;
            
            case FMKMAC_DMA_TYPE_USART_TX:
                __HAL_LINKDMA((&f_modHandle_pu->usartHandle_s), hdmatx, *f_bspDma_ps);
                break;

            case FMKMAC_DMA_TYPE_SPI:
            case FMKMAC_DMA_TYPE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }

    return Ret_e;
}
/******************************************
 * BSP CALLBACK IMPLEMENTATION
 *****************************************/
/* CAUTION : Automatic generated code section for DMA_Channel IRQHandler: Start */
/**
* @brief This function handles DMA Channel1 interrupt.
*/
void DMA2_Channel1_IRQHandler(void)
{
    if(g_DmaInfo_as[FMKMAC_DMA_CTRL_2].channel_as[FMKMAC_DMA_CHANNEL_1].isChnlConfigured_b == (t_bool)True)
    {
       HAL_DMA_IRQHandler(&(g_DmaInfo_as[FMKMAC_DMA_CTRL_2].channel_as[FMKMAC_DMA_CHANNEL_1].bspDma_ps));
    }
    return;
}

/**
* @brief This function handles DMA Channel2 interrupt.
*/
void DMA2_Channel2_IRQHandler(void)
{
    if(g_DmaInfo_as[FMKMAC_DMA_CTRL_2].channel_as[FMKMAC_DMA_CHANNEL_2].isChnlConfigured_b == (t_bool)True)
    {
       HAL_DMA_IRQHandler(&(g_DmaInfo_as[FMKMAC_DMA_CTRL_2].channel_as[FMKMAC_DMA_CHANNEL_2].bspDma_ps));
    }
    return;
}

/**
* @brief This function handles DMA Channel3 interrupt.
*/
void DMA2_Channel3_IRQHandler(void)
{
    if(g_DmaInfo_as[FMKMAC_DMA_CTRL_2].channel_as[FMKMAC_DMA_CHANNEL_3].isChnlConfigured_b == (t_bool)True)
    {
       HAL_DMA_IRQHandler(&(g_DmaInfo_as[FMKMAC_DMA_CTRL_2].channel_as[FMKMAC_DMA_CHANNEL_3].bspDma_ps));
    }
    return;
}

/**
* @brief This function handles DMA Channel4 interrupt.
*/
void DMA2_Channel4_IRQHandler(void)
{
    if(g_DmaInfo_as[FMKMAC_DMA_CTRL_2].channel_as[FMKMAC_DMA_CHANNEL_4].isChnlConfigured_b == (t_bool)True)
    {
       HAL_DMA_IRQHandler(&(g_DmaInfo_as[FMKMAC_DMA_CTRL_2].channel_as[FMKMAC_DMA_CHANNEL_4].bspDma_ps));
    }
    return;
}

/**
* @brief This function handles DMA Channel5 interrupt.
*/
void DMA2_Channel5_IRQHandler(void)
{
    if(g_DmaInfo_as[FMKMAC_DMA_CTRL_2].channel_as[FMKMAC_DMA_CHANNEL_5].isChnlConfigured_b == (t_bool)True)
    {
       HAL_DMA_IRQHandler(&(g_DmaInfo_as[FMKMAC_DMA_CTRL_2].channel_as[FMKMAC_DMA_CHANNEL_5].bspDma_ps));
    }
    return;
}

/**
* @brief This function handles DMA Channel1 interrupt.
*/
void DMA1_Channel1_IRQHandler(void)
{
    if(g_DmaInfo_as[FMKMAC_DMA_CTRL_1].channel_as[FMKMAC_DMA_CHANNEL_1].isChnlConfigured_b == (t_bool)True)
    {
       HAL_DMA_IRQHandler(&(g_DmaInfo_as[FMKMAC_DMA_CTRL_1].channel_as[FMKMAC_DMA_CHANNEL_1].bspDma_ps));
    }
    return;
}

/**
* @brief This function handles DMA Channel2 interrupt.
*/
void DMA1_Channel2_IRQHandler(void)
{
    if(g_DmaInfo_as[FMKMAC_DMA_CTRL_1].channel_as[FMKMAC_DMA_CHANNEL_2].isChnlConfigured_b == (t_bool)True)
    {
       HAL_DMA_IRQHandler(&(g_DmaInfo_as[FMKMAC_DMA_CTRL_1].channel_as[FMKMAC_DMA_CHANNEL_2].bspDma_ps));
    }
    return;
}

/**
* @brief This function handles DMA Channel3 interrupt.
*/
void DMA1_Channel3_IRQHandler(void)
{
    if(g_DmaInfo_as[FMKMAC_DMA_CTRL_1].channel_as[FMKMAC_DMA_CHANNEL_3].isChnlConfigured_b == (t_bool)True)
    {
       HAL_DMA_IRQHandler(&(g_DmaInfo_as[FMKMAC_DMA_CTRL_1].channel_as[FMKMAC_DMA_CHANNEL_3].bspDma_ps));
    }
    return;
}

/**
* @brief This function handles DMA Channel4 interrupt.
*/
void DMA1_Channel4_IRQHandler(void)
{
    if(g_DmaInfo_as[FMKMAC_DMA_CTRL_1].channel_as[FMKMAC_DMA_CHANNEL_4].isChnlConfigured_b == (t_bool)True)
    {
       HAL_DMA_IRQHandler(&(g_DmaInfo_as[FMKMAC_DMA_CTRL_1].channel_as[FMKMAC_DMA_CHANNEL_4].bspDma_ps));
    }
    return;
}

/* CAUTION : Automatic generated code section for DMA_Channel IRQHandler: End */

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
