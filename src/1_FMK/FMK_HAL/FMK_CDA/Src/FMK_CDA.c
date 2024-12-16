/**
 * @file        FMK_IO.c
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./FMK_CDA.h"
#include "FMK_HAL/FMK_MAC/Src/FMK_MAC.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKCDA_ConfigPrivate.h"
#include "stm32g4xx_hal.h"

// ********************************************************************
// *                      Defines
// ********************************************************************

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

/**< Structure for store and manage analog value in Scan_Dma mode */
typedef struct
{
    t_uint32 rawValue_au32[FMKCDA_ADC_CHANNEL_NB];                  /**< Array for analog value for all channel */
    t_uint16 savedVal_ua16[FMKCDA_ADC_CHANNEL_NB];
    t_eFMKCDA_AdcChannel BspChnlmapp_ae[FMKCDA_ADC_CHANNEL_NB];      /**< Mapping with raywvalue array and channelINfo structure abalog value */    
    t_bool flagReadBuffer_b;                                        /**< Flag reading buffer  */
    t_uint32 lastUpate_u32;                                       /**< time between the last update */
} t_sFMKCDA_AdcBuffer;

/**< Structure for adc channel information*/
typedef struct
{
    t_uint16 rawValue_u16;              /**< the analog value for this channel */
    t_bool FlagValueUpdated_b;          /**< Flag to know when the rawvalue is available */
    t_bool IsChnlConfigured_b;          /**< Flag to know if the channel if configured well */
} t_sFMKCDA_ChnlInfo;

/**< Structure for adc information*/
typedef struct
{
    ADC_HandleTypeDef BspInit_s;                            /**< Store the bsp information needed */
    t_eFMKCDA_HwAdcCfg HwCfg_e;                             /**< Store in which mode the ADC is currently set */
    t_sFMKCDA_ChnlInfo Channel_as[FMKCDA_ADC_CHANNEL_NB];   /**< Structure channel information for each channel */
    const t_eFMKCPU_ClockPort c_clock_e;                      /**< constant to store the clock for each ADC */
    const t_eFMKCPU_IRQNType c_IRQNType_e;                    /**< constant to store the IRQN for each ADC */
    t_bool IsAdcConfigured_b;                               /**< Flag to know if the ADC is configured */
    t_bool IsAdcRunning_b;                                  /**< Flag to know if the Adc is running a conversion */
    t_bool flagErrDetected_b;                               /**< Flag in DMA/Interrupt mode Error Callback has been call */                 
    t_eFMKCDA_ChnlErrState Error_e;                         /**< Store the adc error status */
} t_sFMKCDA_AdcInfo;

typedef struct
{
    t_float32 cabliValue_f32;                               /**< Store the calibration tension for an adc */
    t_bool isValueSet_b;                                    /**< Store wether or not hte calibration has been set */
} t_sFMKCDA_AdcCalibInfo;
// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
/* CAUTION : Automatic generated code section for Variable: Start */
/**< Store the Adc Info variable*/
t_sFMKCDA_AdcInfo g_AdcInfo_as[FMKCDA_ADC_NB] = {
    {
        // ADC_1
        .BspInit_s.Instance = ADC1,
        .c_clock_e = FMKCPU_RCC_CLK_ADC12,
        .c_IRQNType_e = FMKCPU_NVIC_ADC1_2_IRQN,
    },
    {
        // ADC_2
        .BspInit_s.Instance = ADC2,
        .c_clock_e = FMKCPU_RCC_CLK_ADC12,
        .c_IRQNType_e = FMKCPU_NVIC_ADC1_2_IRQN,
    },
    {
        // ADC_3
        .BspInit_s.Instance = ADC3,
        .c_clock_e = FMKCPU_RCC_CLK_ADC345,
        .c_IRQNType_e = FMKCPU_NVIC_ADC3_IRQN,
    },
    {
        // ADC_4
        .BspInit_s.Instance = ADC4,
        .c_clock_e = FMKCPU_RCC_CLK_ADC345,
        .c_IRQNType_e = FMKCPU_NVIC_ADC4_IRQN,
    },
    {
        // ADC_5
        .BspInit_s.Instance = ADC5,
        .c_clock_e = FMKCPU_RCC_CLK_ADC345,
        .c_IRQNType_e = FMKCPU_NVIC_ADC5_IRQN,
    },
};

/**< Rank for each channel add for ADC */
t_uint8 g_counterRank_au8[FMKCDA_ADC_NB] = {
    (t_uint8)0,
    (t_uint8)0,
    (t_uint8)0,
    (t_uint8)0,
    (t_uint8)0,
};

/* CAUTION : Automatic generated code section for Variable: End */
// flag automatatic generated code 
/**< Store calibration information for each adc */
t_sFMKCDA_AdcCalibInfo g_adcCalibInfo_as[FMKCDA_ADC_NB];
/**< store the raw value for each channel of each adc converter*/
t_sFMKCDA_AdcBuffer g_AdcBuffer_as[FMKCDA_ADC_NB];

static t_eCyclicModState g_FmkCda_ModState_e = STATE_CYCLIC_CFG;

//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
 *
 *	@brief      Function to get the bsp channel based on the value of f_channel_e.\n
 *
 *	@param[in]  f_channel_e           : enum adc channel, value from @ref t_eFMKCDA_AdcChannel
 *	@param[in]  f_bspChannel_32       : bsp adc channel uint32
 *
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_PARAM_NOT_SUPPORTED      @ref RC_ERROR_PARAM_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKCDA_Get_BspChannel(t_eFMKCDA_AdcChannel f_channel_e, t_uint32 *f_bspChannel_32);
/**
 *
 *	@brief      Function to set the bsp adc Init.\n
 *  @note       Depending on f_HwAdcCfg_e this function set the bsp Init with the right 
 *              element and call hal_adc_init and set the rcc clock enable.\n 
 *              
 *
 *	@param[in]  f_Adc_e               : enum adc, value from @ref t_eFMKCDA_Adc
 *	@param[in]  f_HwAdcCfg_e          : enum for adc configuration, value from @ref t_eFMKCDA_HwAdcCfg
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 * @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
 *
 */
static t_eReturnCode s_FMKCDA_Set_BspAdcCfg(t_eFMKCDA_Adc f_Adc_e,
                                             t_eFMKCDA_HwAdcCfg f_HwAdcCfg_e);
/**
 *
 *	@brief      Function to set the bsp channel Init.\n
 *  @note       The ADC config must be set before calling this function.n
 *              This function allow user to configure a adc_channel -> f_channel_e from 
 *              an ADC -> f_Adc_e.\n This function call hal_set_adc_channel.\n
 *              If hardware failed, this function return retcode Wrong_State
 *              
 *
 *	@param[in]  f_Adc_e               : enum adc, value from @ref t_eFMKCDA_Adc
 *	@param[in]  f_channel_e           : enum adc channel, value from @ref t_eFMKCDA_AdcChannel
 *
 * @retval RC_OK                             @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 * @retval RC_ERROR_ALREADY_CONFIGURED           @ref RC_ERROR_ALREADY_CONFIGURED
 * @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
 *
 */
static t_eReturnCode s_FMKCDA_Set_BspChannelCfg(t_eFMKCDA_Adc f_Adc_e, t_eFMKCDA_AdcChannel f_channel_e);
/**
 *
 *	@brief      Perform cyclic operation for this module.\n
 *  @note       Every Cycle in OPE_MODE, this function start Adc conversion 
 *              if the adc is config as so (Interruption or Dma). If a previous conversion 
 *              is finished, this function store the value in the right channel and update 
 *              flag in consequence.\n This function also perform cyclic diagnostic on channel
 *              every x seconds, parameter reference in configPrivate.\n
 *              
 * @retval RC_OK                               @ref RC_OK
 * @retval RC_WARNING_WRONG_STATE              @ref RC_ERROR_WARNING_STATE
 * @retval RC_WARNING_BUSY                     @ref RC_WARNING_BUSY
 *
 */
static t_eReturnCode s_FMKCDA_Operational(void);
/**
 *
 *	@brief      Perform cyclic pre-operation for this module.\n
 *  @note       Make configuration for vref and vtemperature adc channel\n
 *              
 * @retval RC_OK                               @ref RC_OK
 * @retval RC_WARNING_WRONG_STATE              @ref RC_ERROR_WARNING_STATE
 * @retval RC_WARNING_BUSY                     @ref RC_WARNING_BUSY
 *
 */
static t_eReturnCode s_FMKCDA_ConfigurationState(void);
/**
 *
 *	@brief      Perform Diagnostic on adc & dac
 *  @note       In basic mode we call HAL_Function to know 
 *              Diag already handle in harware lawyer and HAL_ADC_ErrorCallback implementation 
 *              Manage error.\n
 * 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE

 */
static t_eReturnCode s_FMKCDA_PerformDiagnostic(t_eFMKCDA_Adc f_adc_e);
/**
 *
 *	@brief      Start adc ocnversion
 *  @note       Depending on hardware configuration, start on adc conversion
 *              either on interrupt either on dma 
 * 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE

 */
static t_eReturnCode s_FMKCDA_StartAdcConversion(t_eFMKCDA_Adc f_Adc_e, t_eFMKCDA_HwAdcCfg f_hwAdc_e);
/**
 *
 *	@brief      Perform cyclic pre-operation for this module.\n
 *  @note       Make configuration for vref and vtemperature adc channel\n
 *              
 * @retval RC_OK                               @ref RC_OK
 * @retval RC_WARNING_WRONG_STATE              @ref RC_ERROR_WARNING_STATE
 * @retval RC_WARNING_BUSY                     @ref RC_WARNING_BUSY
 *
 */
static t_eReturnCode s_FMKCDA_UpdateChannelValue(t_eFMKCDA_Adc f_Adc_e);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * FMKCDA_Init
 *********************************/
t_eReturnCode FMKCDA_Init(void)
{
    t_uint8 adcIndex_u8 = 0;
    t_uint8 chnlIndex_u8 = 0;

    // initiate to default value variable structure
    for (adcIndex_u8 = (t_uint8)0; adcIndex_u8 < (t_uint8)FMKCDA_ADC_NB; adcIndex_u8++)
    { // all adc
        g_AdcInfo_as[adcIndex_u8].IsAdcConfigured_b    = (t_bool)False;
        g_AdcInfo_as[adcIndex_u8].IsAdcRunning_b       = (t_bool)False;
        g_AdcInfo_as[adcIndex_u8].flagErrDetected_b    = (t_bool)False;
        g_AdcInfo_as[adcIndex_u8].Error_e = FMKCDA_ERRSTATE_OK;
        
        g_adcCalibInfo_as[adcIndex_u8].cabliValue_f32 = (t_float32)0.0;
        g_adcCalibInfo_as[adcIndex_u8].isValueSet_b = (t_bool)False;
        
        g_AdcBuffer_as[adcIndex_u8].lastUpate_u32 = (t_uint32)0;
        g_AdcBuffer_as[adcIndex_u8].flagReadBuffer_b = (t_bool)False;

        g_counterRank_au8[adcIndex_u8] = (t_uint8)0;

        for (chnlIndex_u8 = (t_uint8)0; chnlIndex_u8 < (t_uint8)FMKCDA_ADC_CHANNEL_NB; chnlIndex_u8++)
        { // all channel for a adc
            g_AdcInfo_as[adcIndex_u8].Channel_as[chnlIndex_u8].IsChnlConfigured_b = (t_bool)False;
            g_AdcInfo_as[adcIndex_u8].Channel_as[chnlIndex_u8].rawValue_u16 = (t_uint16)0;

            g_AdcBuffer_as[adcIndex_u8].BspChnlmapp_ae[chnlIndex_u8] = FMKCDA_ADC_CHANNEL_NB;
            g_AdcBuffer_as[adcIndex_u8].rawValue_au32[chnlIndex_u8] = (t_uint32)0;
            
        }
    }

    return RC_OK;
}

/*********************************
 * FMKCDA_Init
 *********************************/
t_eReturnCode FMKCDA_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch (g_FmkCda_ModState_e)
    {
        case STATE_CYCLIC_CFG:
        {
            Ret_e = s_FMKCDA_ConfigurationState();
            if(Ret_e  == RC_OK)
            {
                g_FmkCda_ModState_e = STATE_CYCLIC_WAITING;
            }
            break;
        }
        case STATE_CYCLIC_WAITING:
        {
            // nothing to do just wait AppSys Signal
            break;
        }
        case STATE_CYCLIC_PREOPE:
        {
            g_FmkCda_ModState_e = STATE_CYCLIC_OPE;
            break;
        }
        case STATE_CYCLIC_OPE:
        {
            Ret_e = s_FMKCDA_Operational();
            if(Ret_e < RC_OK)
            {
                g_FmkCda_ModState_e = STATE_CYCLIC_ERROR;
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
 * FMKCDA_GetState
 *********************************/
t_eReturnCode FMKCDA_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;
    
    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_FmkCda_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * FMKCDA_SetState
 *********************************/
t_eReturnCode FMKCDA_SetState(t_eCyclicModState f_State_e)
{

    g_FmkCda_ModState_e = f_State_e;
    return RC_OK;
}

/*********************************
 * FMKCDA_Set_AdcChannelCfg
 *********************************/
t_eReturnCode FMKCDA_Set_AdcChannelCfg(t_eFMKCDA_Adc f_Adc_e,
                                        t_eFMKCDA_AdcChannel f_channel_e,
                                        t_eFMKCDA_HwAdcCfg f_hwAdcCfg_e)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_Adc_e > FMKCDA_ADC_NB 
    || f_channel_e > c_FmkCda_AdcMaxChnl_ua8[f_Adc_e])
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_AdcInfo_as[f_Adc_e].IsAdcConfigured_b == (t_bool)False)
    {
        Ret_e = s_FMKCDA_Set_BspAdcCfg((t_eFMKCDA_Adc)f_Adc_e,
                                           f_hwAdcCfg_e);
    }
    if(g_AdcInfo_as[f_Adc_e].IsAdcConfigured_b == (t_bool)True
    && f_hwAdcCfg_e != g_AdcInfo_as[f_Adc_e].HwCfg_e)
    {
        Ret_e = RC_ERROR_WRONG_CONFIG;
    }
    if (Ret_e == RC_OK)
    {// depending on hardware configuration make some configuration
        #warning "Only Scan/DMA mode is trreated for AdcChannel Configuration"
        // Configure Channel
        Ret_e = s_FMKCDA_Set_BspChannelCfg(f_Adc_e, f_channel_e);
    }
    
    return Ret_e;
}

/*********************************
 * FMKCDA_Get_AnaChannelMeasure
 *********************************/
t_eReturnCode FMKCDA_Get_AnaChannelMeasure(t_eFMKCDA_Adc f_Adc_e, t_eFMKCDA_AdcChannel f_channel_e, t_uint16 *f_AnaMeasure_u16)
{
    t_eReturnCode Ret_e = RC_OK;

    if (f_Adc_e > FMKCDA_ADC_NB 
    || f_channel_e > c_FmkCda_AdcMaxChnl_ua8[f_Adc_e])
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_AnaMeasure_u16 == (t_uint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_FmkCda_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_ERROR_WRONG_STATE;
    }
    if(g_AdcInfo_as[f_Adc_e].IsAdcConfigured_b == (t_bool)False
    || g_AdcInfo_as[f_Adc_e].Channel_as[f_channel_e].IsChnlConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if(g_AdcInfo_as[f_Adc_e].Error_e != FMKCDA_ERRSTATE_OK)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    if (Ret_e == RC_OK)
    {
        // give the last raw analog value if value is updated
        if (g_AdcInfo_as[f_Adc_e].Channel_as[f_channel_e].FlagValueUpdated_b == (t_bool)True)
        {
            *f_AnaMeasure_u16 = g_AdcInfo_as[f_Adc_e].Channel_as[f_channel_e].rawValue_u16;
            // update flag for this channel 
            g_AdcInfo_as[f_Adc_e].Channel_as[f_channel_e].FlagValueUpdated_b = (t_bool)False;
        }
        else
        {
            *f_AnaMeasure_u16 = (t_uint16)0;
            Ret_e = RC_WARNING_NO_OPERATION;
        }
    }
    return Ret_e;
}

/*********************************
 * FMKCDA_Get_AnaChannelMeasure
 *********************************/
t_eReturnCode FMKCDA_Get_AdcError(t_eFMKCDA_Adc f_adc_e, t_eFMKCDA_ChnlErrState *f_chnlErrInfo_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_adc_e > FMKCDA_ADC_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_chnlErrInfo_pe == (t_eFMKCDA_ChnlErrState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_chnlErrInfo_pe = g_AdcInfo_as[f_adc_e].Error_e;
    }
    
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_FMKCDA_Operational
 *********************************/
static t_eReturnCode s_FMKCDA_ConfigurationState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 AdcIndex_u8 = 0;

    // set configuration channel for Adc Internal Signal
    for(AdcIndex_u8 = (t_uint8)0 ; (AdcIndex_u8 < FMKCDA_ADC_NB) && (Ret_e == RC_OK); AdcIndex_u8++)
    {
        Ret_e = FMKCDA_Set_AdcChannelCfg(c_FmkCda_HwVrefCfg[AdcIndex_u8].adc_e,
                                         c_FmkCda_HwVrefCfg[AdcIndex_u8].chnl_e,
                                         FMKCDA_ADC_CFG_SCAN_DMA);
    }
    

    return Ret_e;
}
/*********************************
 * s_FMKCDA_Operational
 *********************************/
static t_eReturnCode s_FMKCDA_Operational(void)
{
    static t_uint32 s_SavedTime_u32 = 0;

    t_eReturnCode Ret_e = RC_OK;
    t_uint32 currentTime_u32 = 0;
    t_uint8 adcIndex_u8 = 0;

   FMKCPU_Get_Tick(&currentTime_u32);

    // For every adc in stm32
    for(adcIndex_u8 = (t_uint8)0 ; (adcIndex_u8 < (t_uint8)FMKCDA_ADC_NB) && (g_AdcInfo_as[adcIndex_u8].IsAdcConfigured_b == (t_bool)true) ; adcIndex_u8++)
    {// if the adc is running
        if((g_AdcInfo_as[adcIndex_u8].flagErrDetected_b == True)
        ||((currentTime_u32 - s_SavedTime_u32) > (t_uint32)FMKCDA_TIME_BTWN_DIAG_MS))
        {
            s_SavedTime_u32 = currentTime_u32;
            Ret_e = s_FMKCDA_PerformDiagnostic((t_eFMKCDA_Adc)adcIndex_u8);
        }
        // if the adc is not running and the adc is configured, launch a conversion only if error_state = NO_ERROR or PRESENTS
        if ((g_AdcInfo_as[adcIndex_u8].IsAdcRunning_b == (t_bool)False)
        &&( (g_AdcInfo_as[adcIndex_u8].Error_e == FMKCDA_ERRSTATE_OK)
        || (g_AdcInfo_as[adcIndex_u8].Error_e == FMKCDA_ERRSTATE_PRESENTS)))
        {
            //Ret_e = s_FMKCDA_StartAdcConversion((t_eFMKCDA_Adc)adcIndex_u8, g_AdcInfo_as[adcIndex_u8].HwCfg_e);
            if(Ret_e == RC_OK) 
            {
                g_AdcInfo_as[adcIndex_u8].IsAdcRunning_b = True;
                g_AdcInfo_as[adcIndex_u8].Error_e &= ~FMKCDA_ERRSTATE_PRESENTS; // reset present bit
            }
        }
        else
        {// check last time update to make actions if there is no update from adc
            FMKCPU_Get_Tick(&currentTime_u32); // recharge current_time in case of interruption occured during cycle and value will be negative => ~ 65500
            // also add 5ms in case interrutpion occured during getting the Tick
            if((t_uint32)((currentTime_u32 + (t_uint32)5) - g_AdcBuffer_as[adcIndex_u8].lastUpate_u32) > (t_uint32)FMKCDA_OVR_CONVERSION_MS)
            {
                // update information 
                g_AdcInfo_as[adcIndex_u8].IsAdcRunning_b = False;
                g_AdcInfo_as[adcIndex_u8].Error_e |= FMKCDA_ERRSTATE_PRESENTS;
            }
            else
            {// put the buffer into adc channel block
                Ret_e = s_FMKCDA_UpdateChannelValue((t_eFMKCDA_Adc)adcIndex_u8);
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKCDA_PerformDiagnostic
 *********************************/
static t_eReturnCode s_FMKCDA_StartAdcConversion(t_eFMKCDA_Adc f_Adc_e, t_eFMKCDA_HwAdcCfg f_hwAdc_e)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;


    if(f_Adc_e > FMKCDA_ADC_NB
    || f_hwAdc_e > FMKCDA_ADC_CFG_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_hwAdc_e)
        {
            case FMKCDA_ADC_CFG_SCAN_DMA:
            {
                bspRet_e = HAL_ADC_Start_DMA(&g_AdcInfo_as[f_Adc_e].BspInit_s,
                                            (t_uint32 *)g_AdcBuffer_as[f_Adc_e].rawValue_au32,
                                            (t_uint32)(g_counterRank_au8[f_Adc_e])); // corresponing to the number of channel 
                                                                        //configured for this adc
                break;                                                        
            }
            case FMKCDA_ADC_CFG_PERIODIC_DMA:
            case FMKCDA_ADC_CFG_TRIGGERED_DMA:
            default:
            {
                Ret_e = RC_WARNING_NO_OPERATION;
            }
                break;
        }
        // sometimes adc is doing something else just wait a sec
        if(bspRet_e == HAL_BUSY)
        {
            Ret_e = RC_WARNING_BUSY;
        }
        else if(bspRet_e != HAL_OK)
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKCDA_PerformDiagnostic
 *********************************/
static t_eReturnCode s_FMKCDA_PerformDiagnostic(t_eFMKCDA_Adc f_adc_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 adcErr_u32 = HAL_ADC_ERROR_NONE;
    t_sFMKCDA_AdcInfo * adcInfo_ps;

    adcInfo_ps = (t_sFMKCDA_AdcInfo *)&g_AdcInfo_as[f_adc_e];
    adcErr_u32 = HAL_ADC_GetError(&adcInfo_ps->BspInit_s);
    
    if(adcErr_u32 != HAL_ADC_ERROR_NONE)
    {// mng mapping error with enum
        if((adcErr_u32 & HAL_ADC_ERROR_OVR) == HAL_ADC_ERROR_OVR)
        {
            adcInfo_ps->Error_e |= FMKCDA_ERRSTATE_ERR_OVR;
        }
        if((adcErr_u32 & HAL_ADC_ERROR_DMA) == HAL_ADC_ERROR_DMA)
        {
            adcInfo_ps->Error_e |= FMKCDA_ERRSTATE_ERR_DMA;
        }
        if((adcErr_u32 & HAL_ADC_ERROR_INTERNAL) == HAL_ADC_ERROR_INTERNAL)
        {
            adcInfo_ps->Error_e |= FMKCDA_ERRSTATE_UNKNOWN;
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKCDA_Get_BspChannel
 *********************************/
static t_eReturnCode s_FMKCDA_Get_BspChannel(t_eFMKCDA_AdcChannel f_channel_e, t_uint32 *f_bspChannel_32)
{
    t_eReturnCode Ret_e = RC_OK;
    if (f_channel_e > FMKCDA_ADC_CHANNEL_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_bspChannel_32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if (Ret_e == RC_OK)
    {
        switch (f_channel_e)
        {
            /* CAUTION : Automatic generated code section for switch_case ADC channel: Start */
            case FMKCDA_ADC_CHANNEL_0:
                *f_bspChannel_32 = ADC_CHANNEL_0;
                break;
            case FMKCDA_ADC_CHANNEL_1:
                *f_bspChannel_32 = ADC_CHANNEL_1;
                break;
            case FMKCDA_ADC_CHANNEL_2:
                *f_bspChannel_32 = ADC_CHANNEL_2;
                break;
            case FMKCDA_ADC_CHANNEL_3:
                *f_bspChannel_32 = ADC_CHANNEL_3;
                break;
            case FMKCDA_ADC_CHANNEL_4:
                *f_bspChannel_32 = ADC_CHANNEL_4;
                break;
            case FMKCDA_ADC_CHANNEL_5:
                *f_bspChannel_32 = ADC_CHANNEL_5;
                break;
            case FMKCDA_ADC_CHANNEL_6:
                *f_bspChannel_32 = ADC_CHANNEL_6;
                break;
            case FMKCDA_ADC_CHANNEL_7:
                *f_bspChannel_32 = ADC_CHANNEL_7;
                break;
            case FMKCDA_ADC_CHANNEL_8:
                *f_bspChannel_32 = ADC_CHANNEL_8;
                break;
            case FMKCDA_ADC_CHANNEL_9:
                *f_bspChannel_32 = ADC_CHANNEL_9;
                break;
            case FMKCDA_ADC_CHANNEL_10:
                *f_bspChannel_32 = ADC_CHANNEL_10;
                break;
            case FMKCDA_ADC_CHANNEL_11:
                *f_bspChannel_32 = ADC_CHANNEL_11;
                break;
            case FMKCDA_ADC_CHANNEL_12:
                *f_bspChannel_32 = ADC_CHANNEL_12;
                break;
            case FMKCDA_ADC_CHANNEL_13:
                *f_bspChannel_32 = ADC_CHANNEL_13;
                break;
            case FMKCDA_ADC_CHANNEL_14:
                *f_bspChannel_32 = ADC_CHANNEL_14;
                break;
            case FMKCDA_ADC_CHANNEL_15:
                *f_bspChannel_32 = ADC_CHANNEL_15;
                break;
            case FMKCDA_ADC_CHANNEL_16:
                *f_bspChannel_32 = ADC_CHANNEL_16;
                break;
            case FMKCDA_ADC_CHANNEL_17:
                *f_bspChannel_32 = ADC_CHANNEL_17;
                break;
            /* CAUTION : Automatic generated code section for switch_case ADC channel: End */
            case FMKCDA_ADC_CHANNEL_NB:
            default:
                Ret_e = RC_ERROR_PARAM_NOT_SUPPORTED;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCDA_Set_BspAdcCfg
 *********************************/
static t_eReturnCode s_FMKCDA_Set_BspAdcCfg(t_eFMKCDA_Adc f_Adc_e,
                                             t_eFMKCDA_HwAdcCfg f_HwAdcCfg_e)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef BspRet_e = HAL_OK;
    ADC_InitTypeDef *bspAdcInit_s;

    if (f_Adc_e > FMKCDA_ADC_NB || f_HwAdcCfg_e > FMKCDA_ADC_CFG_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (Ret_e == RC_OK)
    {
        bspAdcInit_s = &g_AdcInfo_as[f_Adc_e].BspInit_s.Init;

        // Configuration générique
        bspAdcInit_s->ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
        bspAdcInit_s->Overrun = ADC_OVR_DATA_OVERWRITTEN;
        bspAdcInit_s->Resolution = ADC_RESOLUTION_12B;
        bspAdcInit_s->DataAlign = ADC_DATAALIGN_RIGHT;
        bspAdcInit_s->EOCSelection = ADC_EOC_SEQ_CONV;

        // Configuration spécifique aux familles
        #ifdef FMKCPU_STM32_ECU_FAMILY_F
            bspAdcInit_s->ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
            bspAdcInit_s->SamplingTimeCommon = ADC_SAMPLETIME_55CYCLES_5; // Valeur par défaut
        #elif defined FMKCPU_STM32_ECU_FAMILY_G
            bspAdcInit_s->ScanConvMode = ADC_SCAN_ENABLE;
            bspAdcInit_s->LowPowerAutoWait = DISABLE; // Désactiver l'attente automatique par défaut
            bspAdcInit_s->OversamplingMode = DISABLE; // Désactiver le suréchantillonnage par défaut
            bspAdcInit_s->SamplingMode = ADC_SAMPLING_MODE_NORMAL; // Mode d'échantillonnage normal
            bspAdcInit_s->GainCompensation = 0; // Pas de compensation de gain par défaut

            // Over samppling parameter
            bspAdcInit_s->OversamplingMode = ENABLE;
            bspAdcInit_s->Oversampling.Ratio = ADC_OVERSAMPLING_RATIO_16; // Exemple : suréchantillonnage x16
            bspAdcInit_s->Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_4;
            bspAdcInit_s->Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
        #else
            #error("Famille STM32 non supportée. Vérifiez la configuration.")
        #endif

        // Gestion du mode DMA
        if (FMKMAC_ADC_DMA_MODE == DMA_CIRCULAR) {
            bspAdcInit_s->DMAContinuousRequests = ENABLE;
        } 
        else 
        {
            bspAdcInit_s->DMAContinuousRequests = DISABLE;
        }

        // Gestion des modes ADC
        switch (f_HwAdcCfg_e) 
        {
            case FMKCDA_ADC_CFG_PERIODIC_DMA:
                bspAdcInit_s->ContinuousConvMode = ENABLE;
                bspAdcInit_s->ExternalTrigConv = ADC_SOFTWARE_START;
                bspAdcInit_s->ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
                break;

            case FMKCDA_ADC_CFG_SCAN_DMA:
                bspAdcInit_s->ContinuousConvMode = ENABLE;
                bspAdcInit_s->ExternalTrigConv = ADC_SOFTWARE_START;
                bspAdcInit_s->ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
                break;

            case FMKCDA_ADC_CFG_TRIGGERED_DMA:
                bspAdcInit_s->DiscontinuousConvMode = DISABLE;

                #ifdef FMKCPU_STM32_ECU_FAMILY_F
                    bspAdcInit_s->ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC4; // Exemple de déclencheur
                #elif defined FMKCPU_STM32_ECU_FAMILY_G
                    //bspAdcInit_s->ExternalTrigConv = ADC_EXTERNALTRIG1_T21_CC2; // Exemple de déclencheur
                #else
                    #error("Famille STM32 non supportée. Vérifiez la configuration.")
                #endif
                
                bspAdcInit_s->ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
                break;

            default:
                Ret_e = RC_WARNING_NO_OPERATION;
                break;
        }

        // Set hardware clock register to enable
        Ret_e = FMKCPU_Set_HwClock(g_AdcInfo_as[f_Adc_e].c_clock_e, FMKCPU_CLOCKPORT_OPE_ENABLE);
        if(Ret_e == RC_OK)
        {
            Ret_e = FMKCPU_Set_NVICState(g_AdcInfo_as[f_Adc_e].c_IRQNType_e, FMKCPU_NVIC_OPE_ENABLE);
        }
        if(Ret_e == RC_OK)
        {// set NVIC state and Dma Request if DMA is in hardware config
            #warning("Only ADC1 managed in DMARequest")
            Ret_e = FMKMAC_RqstDmaInit(FMKMAC_DMA_RQSTYPE_ADC1, (void *)&g_AdcInfo_as[f_Adc_e].BspInit_s);
        }
        if (Ret_e == RC_OK)
        {// Init hardware ADC
            BspRet_e = HAL_ADC_Init(&g_AdcInfo_as[f_Adc_e].BspInit_s);

            if (BspRet_e == HAL_OK)
            {
                g_AdcInfo_as[f_Adc_e].HwCfg_e = f_HwAdcCfg_e;
                g_AdcInfo_as[f_Adc_e].IsAdcConfigured_b = (t_bool)True;
            }
            else 
            {
                Ret_e = RC_ERROR_WRONG_STATE;
            }
        }
        else
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
    }
    return Ret_e;
}

/*********************************
 * s_FMKCDA_Set_BspChannelCfg
 *********************************/
static t_eReturnCode s_FMKCDA_Set_BspChannelCfg(t_eFMKCDA_Adc f_Adc_e, t_eFMKCDA_AdcChannel f_channel_e)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef BspRet_e = HAL_OK;
    t_uint32 bspChannel_u32 = 0;
        
    #ifdef FMKCPU_STM32_ECU_FAMILY_F
        ADC_ChannelConfTypeDef BspChannelInit_s = {
            .SamplingTime = ADC_SAMPLETIME_13CYCLES_5, // Configuration spécifique à la famille F
            .SingleDiff = ADC_SINGLE_ENDED,           // Single-ended par défaut
            .OffsetNumber = ADC_OFFSET_NONE,         // Pas d'offset initial
            .Offset = 0,                             // Offset à 0
            .OffsetSign = ADC_OFFSET_SIGN_POSITIVE,  // Offset positif par défaut
            .OffsetSaturation = DISABLE              // Saturation désactivée
        };
    #elif defined FMKCPU_STM32_ECU_FAMILY_G
        ADC_ChannelConfTypeDef BspChannelInit_s = {
            .SamplingTime = ADC_SAMPLETIME_47CYCLES_5, // Configuration spécifique à la famille G
            .SingleDiff = ADC_SINGLE_ENDED,           // Single-ended par défaut
            .OffsetNumber = ADC_OFFSET_NONE,         // Pas d'offset initial
            .Offset = 0,                             // Offset à 0
            .OffsetSign = ADC_OFFSET_SIGN_POSITIVE,  // Offset positif par défaut
            .OffsetSaturation = DISABLE              // Saturation désactivée
        };
    #else
        #error("Famille STM32 non supportée. Vérifiez la configuration.")
    #endif
    

    if (f_Adc_e > FMKCDA_ADC_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_AdcInfo_as[f_Adc_e].IsAdcConfigured_b == (t_bool)False)
    {
        Ret_e = RC_ERROR_MISSING_CONFIG;
    }
    if (Ret_e == RC_OK)
    {
        // configure channel
        Ret_e = s_FMKCDA_Get_BspChannel(f_channel_e, &bspChannel_u32);

        if (Ret_e == RC_OK)
        {
            // For mapping 
            g_counterRank_au8[f_Adc_e] += (t_uint8)1;
            BspChannelInit_s.Channel = bspChannel_u32;
            BspChannelInit_s.Rank = g_counterRank_au8[f_Adc_e];
            // configure adc channel
            BspRet_e = HAL_ADC_ConfigChannel(&g_AdcInfo_as[f_Adc_e].BspInit_s,
                                             &BspChannelInit_s);

            if (BspRet_e == HAL_OK)
            {
                // update mapping for dma
                g_AdcBuffer_as[f_Adc_e].BspChnlmapp_ae[(g_counterRank_au8[f_Adc_e] - 1)] = f_channel_e;
                // update info
                g_AdcInfo_as[f_Adc_e].Channel_as[f_channel_e].IsChnlConfigured_b = (t_bool)True;
            }
            else
            {
                Ret_e = RC_ERROR_WRONG_STATE;
            }
        }
    }
    return Ret_e;
}

/******************************************
 * s_FMKCDA_UpdateChannelValue
 *****************************************/
static t_eReturnCode s_FMKCDA_UpdateChannelValue(t_eFMKCDA_Adc f_Adc_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKCDA_AdcChannel chnl_e = FMKCDA_ADC_CHANNEL_NB;
    t_uint8 LLI_u8 = 0;
    t_uint8 reverseLLI_u8 = 0;
    t_uint8 idxChnl_u8 = 0; 
    static t_uint32 lastTime_u32 = 0;
    t_uint32 currentTime_u32= 0;
    
    FMKCPU_Get_Tick(&currentTime_u32);
    // update calibration point for this adc if needed
    if((currentTime_u32 - lastTime_u32) > (t_uint32)FMKCDA_CYCLIC_CALIB
    || g_adcCalibInfo_as[f_Adc_e].isValueSet_b == (t_bool)False)
    {
        lastTime_u32 = currentTime_u32;
        chnl_e = c_FmkCda_HwVrefCfg[f_Adc_e].chnl_e;
        for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)(g_counterRank_au8[f_Adc_e]) ; LLI_u8++)
        {
            if(chnl_e == g_AdcBuffer_as[f_Adc_e].BspChnlmapp_ae[LLI_u8])
            {
                break;
            }
        }
        if(chnl_e != FMKCDA_ADC_CHANNEL_NB)
        {//                         max rank in buffer, cause it's in reverse
            idxChnl_u8 = (t_uint8)((g_counterRank_au8[f_Adc_e] - (t_uint8)1) - (t_uint8)LLI_u8);
            g_adcCalibInfo_as[f_Adc_e].cabliValue_f32 = (t_float32)(g_AdcBuffer_as[f_Adc_e].savedVal_ua16[idxChnl_u8] 
                                                            / (t_float32)(*c_FmkCda_VrefCalibAddress_pas16[f_Adc_e]));
            g_adcCalibInfo_as[f_Adc_e].isValueSet_b = (t_bool)True;

        }
    }

    // update flag reading 
    g_AdcBuffer_as[f_Adc_e].flagReadBuffer_b = (t_bool)True;
    //  here the dma load the buffer with FILO method, first in last out.
    reverseLLI_u8 = (t_uint8)(g_counterRank_au8[f_Adc_e] - 1);

    for (LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)(g_counterRank_au8[f_Adc_e]) ; LLI_u8++)
    {
        chnl_e = g_AdcBuffer_as[f_Adc_e].BspChnlmapp_ae[reverseLLI_u8];
        g_AdcInfo_as[f_Adc_e].Channel_as[chnl_e].rawValue_u16 = 
            (t_uint16)((t_float32)g_AdcBuffer_as[f_Adc_e].savedVal_ua16[LLI_u8] * 
                            g_adcCalibInfo_as[f_Adc_e].cabliValue_f32);
        // Update flag 
        g_AdcInfo_as[f_Adc_e].Channel_as[chnl_e].FlagValueUpdated_b = (t_bool)True;
        reverseLLI_u8 -= (t_uint8)1;
    }  
    // update flag reading 
    g_AdcBuffer_as[f_Adc_e].flagReadBuffer_b = (t_bool)False; 

    return Ret_e;          

}

//********************************************************************************
//                      HAL_Callback Implementation
//********************************************************************************
/******************************************
 * BSP CALLBACK IMPLEMENTATION
 *****************************************/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    t_uint8 adcIndex_u8 = 0;
    t_uint8 LLI_u8 = 0;
    t_eFMKCDA_Adc IT_Adc_e = FMKCDA_ADC_NB;
    for (adcIndex_u8 = (t_uint8)0; adcIndex_u8 < (t_uint8)FMKCDA_ADC_NB; adcIndex_u8++)
    {
        if (&g_AdcInfo_as[adcIndex_u8].BspInit_s == (ADC_HandleTypeDef *)hadc)
        {
            IT_Adc_e = (t_eFMKCDA_Adc)adcIndex_u8;
            break;
        }
    }
    
    if (IT_Adc_e < FMKCDA_ADC_NB)
    {
        // update saved value only if cyclic is not reading it
        if(g_AdcBuffer_as[IT_Adc_e].flagReadBuffer_b == (t_bool)False)
        {
            //                                      number of channel configured
            for(LLI_u8 = (t_uint8)0 ; LLI_u8 < (t_uint8)(g_counterRank_au8[IT_Adc_e]) ; LLI_u8++)
            {
                g_AdcBuffer_as[IT_Adc_e].savedVal_ua16[LLI_u8] = (t_uint16)g_AdcBuffer_as[IT_Adc_e].rawValue_au32[LLI_u8];
            }
        }
        // update last time the value has been changed and reset bit present error
        FMKCPU_Get_Tick(&g_AdcBuffer_as[IT_Adc_e].lastUpate_u32);
        g_AdcInfo_as[IT_Adc_e].Error_e &= ~FMKCDA_ERRSTATE_PRESENTS; // reset present bit
    }
    return;
}
/**
 *
 *	@brief      CallBack function called when adc in DMA or Interrupt in HalfDma.
 *  @note       Update flag error detected.\n
 *             
 */
/*********************************
 * HAL_ADC_ConvHalfCpltCallback
 *********************************/
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc) {
    // Update the last update for adc channel 
    t_uint8 adcIndex_u8 = 0;
    t_eFMKCDA_Adc IT_Adc_e = FMKCDA_ADC_NB;
    for (adcIndex_u8 = (t_uint8)0; adcIndex_u8 < (t_uint8)FMKCDA_ADC_NB; adcIndex_u8++)
    {
        if (&g_AdcInfo_as[adcIndex_u8].BspInit_s == (ADC_HandleTypeDef *)hadc)
        {
            IT_Adc_e = (t_eFMKCDA_Adc)adcIndex_u8;
            break;
        }
    }
    if (IT_Adc_e < FMKCDA_ADC_NB)
    {
        // update last time the value has been changed 
        FMKCPU_Get_Tick(&g_AdcBuffer_as[IT_Adc_e].lastUpate_u32);
    }
    return;
}
/**
 *
 *	@brief      CallBack function called when adc in DMa or Interrupt mdode
 *  @note       Update flag error detected.\n
 *             
 */
/*********************************
 * HAL_ADC_ErrorCallback
 *********************************/
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{
    t_uint8 LLI_u8;

    // find enum adc corresponding
    for(LLI_u8 = (t_uint8)0 ; LLI_u8 < FMKCDA_ADC_NB ; LLI_u8++)
    {
        if(&g_AdcInfo_as[LLI_u8].BspInit_s == hadc)
        {
            break;
        }
    }
    if(LLI_u8 < FMKCDA_ADC_NB)
    {
        g_AdcInfo_as[LLI_u8].flagErrDetected_b = (t_bool)True;
    }
    return;
}
/**
 *
 *	@brief      CallBack function called for adc interruption (including DMA)
 *             
 */
/*********************************
 * HAL_ADC_ErrorCallback
 *********************************/
#ifdef FMKCPU_STM32_ECU_FAMILY_F
    /*********************************
     * HAL_ADC_ErrorCallback
     *********************************/
    void ADC1_IRQHandler(void) 
    {
        HAL_ADC_IRQHandler(&g_AdcInfo_as[FMKCDA_ADC_1].BspInit_s);
    }
#elif defined FMKCPU_STM32_ECU_FAMILY_G
    /*********************************
     * ADC1_2_IRQHandler
     *********************************/
    void ADC1_2_IRQHandler(void) 
    {
        HAL_ADC_IRQHandler(&g_AdcInfo_as[FMKCDA_ADC_1].BspInit_s);
        HAL_ADC_IRQHandler(&g_AdcInfo_as[FMKCDA_ADC_2].BspInit_s);
    }
    /*********************************
     * ADC3_IRQHandler
     *********************************/
    void ADC3_IRQHandler(void) 
    {
        HAL_ADC_IRQHandler(&g_AdcInfo_as[FMKCDA_ADC_3].BspInit_s);
    }
    /*********************************
     * ADC4_IRQHandler
     *********************************/
    void ADC4_IRQHandler(void) 
    {
        HAL_ADC_IRQHandler(&g_AdcInfo_as[FMKCDA_ADC_4].BspInit_s);
    }
    /*********************************
     * ADC5_IRQHandler
     *********************************/
    void ADC5_IRQHandler(void) 
    {
        HAL_ADC_IRQHandler(&g_AdcInfo_as[FMKCDA_ADC_5].BspInit_s);
    }
#else 
    #error("Famille STM32 non supportée. Vérifiez la configuration.")

#endif



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
