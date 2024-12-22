/*********************************************************************
 * @file        FMK_SRL.c
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
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
#include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
#include "./FMK_SRL.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKSRL_ConfigPrivate.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
typedef union __t_uFMKSRL_HardwareSerial
{
    UART_HandleTypeDef  uartH_s;
    USART_HandleTypeDef usartH_s;
} t_uFMKSRL_HardwareHandle;
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */

//-----------------------------ENUM TYPES-----------------------------//
typedef enum __t_eFMKSRL_BufferStatus
{
    FMKSRL_HEALTH_LINE_OK = 0x00,
} t_eFMKSRL_BufferStatus;
typedef enum __t_eFMKSRL_BufferHealth
{
    FMKSRL_HEALTH_LINE_OK = 0x00,
} t_eFMKSRL_BufferHealth;
/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
typedef struct __t_sFMKSRL_BufferInfo
{
    t_uint8 * bufferAdd_pu8;
    t_uint16 buffferSize_u16;
    t_uint16 bytePending_u16;
    t_uint16 writeIdx_u16;
    t_uint16 readIdx_u16;
    t_eFMKSRL_BufferStatus status_e; 
    t_eFMKSRL_BufferHealth health_e; 
} t_sFMKSRL_BufferInfo;

typedef struct __t_sFMKSRL_TxMngmt
{
    t_eFMKSRL_TxOpeMode                 OpeMode_e;
    t_eFMKSRL_BspTransmitOpe            TxOpe_e;
    t_sFMKSRL_BufferInfo                * Buffer_ps;
    t_cbFMKSRL_TransmitMsgEvent         *TxUserCb_pcb;
} t_sFMKSRL_TxMngmt;

typedef struct __t_sFMKSRL_RxMngmt
{
    t_eFMKSRL_RxOpeMode         OpeMode_e;
    t_eFMKSRL_BspReceiveOpe     TxOpe_e;
    t_sFMKSRL_BufferInfo        * Buffer_ps;
    t_cbFMKSRL_RcvMsgEvent      * RxUserCb_pcb;
} t_sFMKSRL_RxMngmt;

typedef struct __t_sFMKSRL_SerialInfo
{
    t_uFMKSRL_HardwareHandle            bspHandle_u;
    const t_eFMKCPU_ClockPort           c_clockPort_e;
    const t_eFMKCPU_IRQNType            c_IRQNType_e;
    const t_eFMKSRL_HwProtocolType      c_HwType_e;
    t_eFMKSRL_HwProtocolType            SoftType_e;
    t_eFMKSRL_LineRunMode               runMode_e;
    t_sFMKSRL_TxMngmt                   TxInfo_s;
    t_sFMKSRL_RxMngmt                   RxInfo_s;
    t_bool                              isLineRunning_b;
    t_bool                              isLineConfigured_b;
} t_sFMKSRL_SerialInfo;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//

// ********************************************************************
// *                      Prototypes
// ********************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************
static t_eCyclicModState g_FmkSrl_ModState_e = STATE_CYCLIC_CFG;

static t_sFMKSRL_SerialInfo g_SerialInfo_as[FMKSRL_SERIAL_LINE_NB];

static t_uint8 g_MProcessIdUsed[FMKSRL_SERIAL_LINE_NB];
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
*
*	@brief      Check User Configuration Acceptance
*   @note       Each Serial Line correpond to a USART, UART instance.\n
*               Therefore, user cannot use USART protocol on UART instance, 
*               but it cans use UART protocol on USART instance.\n
* 
*	@param[in]  f_hwCfg_e               : UART/USART type imposed by hardware
*	@param[in]  f_softCfg_e             : UART/USART type protocol choosen by user to

*   @retval RC_OK                               @ref RC_OK
*   @retval RC_ERROR_NOT_ALLOWED                @ref RC_ERROR_NOT_ALLOWED
*/
static t_eReturnCode s_FMKSRL_CheckConfiguration(t_eFMKSRL_HwProtocolType f_hwCfg_e, t_eFMKSRL_HwProtocolType f_softCfg_e);

/**
*
*	@brief      Set Serial Driver Init Configuration.\n
*   @note       This function redirect the Init depending on the protocol Used.\n
* 
*	@param[in]  f_SrlInfo_ps               : pointor to Serial Info 
*	@param[in]  f_DrvSrlCfg_ps             : pointor to Serial Configuration 
*
*   @retval RC_OK                               @ref RC_OK
*   @retval RC_ERROR_NOT_ALLOWED                @ref RC_ERROR_NOT_ALLOWED
*/
static t_eReturnCode s_FMKSRL_SetBspSerialInit(t_eFMKSRL_SerialLine f_srlLine_e, t_sFMKSRL_DrvSerialCfg *f_DrvSrlCfg_ps);

/**
*
*	@brief      Set Uart Driver Init Configuration.\n
*   @note       Configure the Hardware Driver to use it with Uart Protocol.\n
* 
*	@param[in]  f_SrlLine_e                : pointor to Serial Info 
*	@param[in]  f_DrvSrlCfg_ps             : pointor to Serial Configuration 
*
*   @retval RC_OK                               @ref RC_OK
*   @retval RC_ERROR_NOT_ALLOWED                @ref RC_ERROR_NOT_ALLOWED
*/
static t_eReturnCode s_FMKSRL_SetUartBspInit(   t_eFMKSRL_SerialLine      f_SrlLine_e, 
                                                t_sFMKSRL_UartCfgSpec   * f_UartCfg_ps,
                                                t_sFMKSRL_HwProtocolCfg * f_HwProtCfg_ps);

/**
*
*	@brief      Set Uart Driver Init Configuration.\n
*   @note       Configure the Hardware Driver to use it with Uart Protocol.\n
* 
*	@param[in]  f_SrlInfo_ps               : pointor to Serial Info 
*	@param[in]  f_DrvSrlCfg_ps             : pointor to Serial Configuration 
*
*   @retval RC_OK                               @ref RC_OK
*   @retval RC_ERROR_NOT_ALLOWED                @ref RC_ERROR_NOT_ALLOWED
*/
static t_eReturnCode s_FMKSRL_SetUsartBspInit(  t_sFMKSRL_SerialInfo     * f_SrlInfo_ps, 
                                                t_sFMKSRL_UsartCfgSpec   * f_UsartCfg_ps,
                                                t_sFMKSRL_HwProtocolCfg  * f_HwProtCfg_ps);
#ifdef FMKCPU_STM32_ECU_FAMILY_G

    /**
     *	@brief          Configure Advance Feature Init for UART\n
    *
    *	@param[in]      f_AdvInit_ps               : bsp Advance Structure
    *	@param[out]     f_SoftAdvCfg_ps            : Software Advance Configuration.\n
    *
    *   @retval RC_OK                               @ref RC_OK
    *   @retval RC_ERROR_NOT_ALLOWED                @ref RC_ERROR_NOT_ALLOWED
    */
    static t_eReturnCode s_FMKSRL_SetUartAdvanceCfg(UART_AdvFeatureInitTypeDef * f_AdvInit_ps, t_sFMKSRL_UartAdvProtCfg * f_SoftAdvCfg_ps);
#endif
/**
 *	@brief          Get the Bsp baudrate from Software enum.\n
 *
 *	@param[in]      f_lineBaudrate_e  : enum value for line baudrate, value from @ref t_eFMKSRL_LineBaudrate.\n
 *	@param[out]     f_bspLineBaudrate : Storage for Bsp baudrate.\n
 *	 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_NOT_SUPPORTED            @ref RC_ERROR_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKSRL_GetBspLineBaudrate(t_eFMKSRL_LineBaudrate f_lineBaudrate_e, t_uint32 *f_bspLineBaudrate_pu32);

/**
 *	@brief          Get the Bsp Stopbit from Software enum.\n
 *
 *	@param[in]      f_HwProtUsed_e        : enum value for protocol used, value from @ref t_eFMKSRL_HwProtocolType.\n
 *	@param[in]      f_lineStopbit_e       : enum value for line Stopbit, value from @ref t_eFMKSRL_LineSoptbit.\n
 *	@param[out]     f_bspLineStopbit_pu32 : Storage for Bsp Stopbit.\n
 *	 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_NOT_SUPPORTED            @ref RC_ERROR_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKSRL_GetBspLineStopbit(    t_eFMKSRL_HwProtocolType f_HwProtUsed_e,
                                                    t_eFMKSRL_LineSoptbit f_lineStopbit_e, 
                                                    t_uint32 *f_bspLineStopbit_pu32);

/**
 *	@brief          Get the Bsp line parity from Software enum.\n
 *
 *	@param[in]      f_HwProtUsed_e       : enum value for protocol used, value from @ref t_eFMKSRL_HwProtocolType.\n
 *	@param[in]      f_lineParity_e       : enum value for line parity, value from @ref t_eFMKSRL_LineSoptbit.\n
 *	@param[out]     f_bspLineParity_pu32 : Storage for Bsp parity.\n
 *	 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_NOT_SUPPORTED            @ref RC_ERROR_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKSRL_GetBspLineParity( t_eFMKSRL_HwProtocolType f_HwProtUsed_e,
                                                t_eFMKSRL_LineParity f_lineParity_e,
                                                t_uint32 *f_bspLineParity_pu32);

/**
 *	@brief          Get the Bsp Mode from Software enum.\n
 *
 *	@param[in]      f_HwProtUsed_e      : enum value for protocol used, value from @ref t_eFMKSRL_HwProtocolType.\n
 *	@param[in]      f_lineMode_e        : enum value for line Mode, value from @ref t_eFMKSRL_LineMode.\n
 *	@param[out]     f_bspLineMode_pu32  : Storage for Bsp mode.\n
 *	 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_NOT_SUPPORTED            @ref RC_ERROR_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKSRL_GetBspLineMode(   t_eFMKSRL_HwProtocolType f_HwProtUsed_e,
                                                t_eFMKSRL_LineMode f_lineMode_e,
                                                t_uint32 *f_bspLineMode_pu32);

/**
 *	@brief          Get the Bsp Word Lenght from Software enum.\n
 *
 *	@param[in]      f_HwProtUsed_e             : enum value for protocol used, value from @ref t_eFMKSRL_HwProtocolType.\n
 *	@param[in]      f_lineWordLenght_e         : enum value for line Word lenght, value from @ref t_eFMKSRL_LineWordLenght.\n
 *	@param[out]     f_bspLineWordLenght_pu32   : Storage for Bsp baudrate.\n
 *	 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
 *  @retval RC_ERROR_NOT_SUPPORTED            @ref RC_ERROR_NOT_SUPPORTED
 *
 */
static t_eReturnCode s_FMKSRL_GetBspWordLenght( t_eFMKSRL_HwProtocolType f_HwProtUsed_e,
                                                t_eFMKSRL_LineWordLenght f_lineWordLenght_e, 
                                                t_uint32 *f_bspLineWordLenght_pu32);

/**
 *	@brief          Get the Bsp Uart Flow Ctrl from Software enum.\n
 *
 *	@param[in]      f_HwProtUsed_e             : enum value for protocol used, value from @ref t_eFMKSRL_HwProtocolType.\n
 *	@param[in]      f_lineWordLenght_e         : enum value for line Word lenght, value from @ref t_eFMKSRL_LineWordLenght.\n
 *	@param[out]     f_bspLineWordLenght_pu32   : Storage for Bsp baudrate.\n
*
*   @retval RC_OK                               @ref RC_OK
*   @retval RC_ERROR_NOT_ALLOWED                @ref RC_ERROR_NOT_ALLOWED
*/
static t_eReturnCode s_FMKSRL_GetUartBspHwFlowCtrl(t_eFMKSRL_UartHwFlowCtrl f_HwFlowCtrl_e, t_uint32 * f_bspHwFlowCtrl_pu32);

/**
 *	@brief          Get the Bsp LIN Break Detection Value.\n
 *
 *	@param[in]      f_BreakLenght_e             : enum value for LIN break detection lenght, value from @ref t_eFMKSRL_LinBreakLenght.\n
 *	@param[out]     f_bspLineWordLenght_pu32   : Storage for Bsp baudrate.\n
*
*   @retval RC_OK                               @ref RC_OK
*   @retval RC_ERROR_NOT_ALLOWED                @ref RC_ERROR_NOT_ALLOWED
*/
static t_eReturnCode s_FMMKSRL_GetBspLinBreakLen(t_eFMKSRL_LinBreakLenght f_BreakLenght_e, t_uint32 * f_bspBreakLenght_pu32);

/**
 *	@brief          Get the Bsp Uart Multi-Processor WakeUp Method\n
 *
 *	@param[in]      f_WakeUpMeth_e             : enum value for MProccess WakeUp Method, value from @ref t_eFMKSRL_LinBreakLenght.\n
 *	@param[out]     f_bspWakeUpMeth_pu32       : Storage for Bsp baudrate.\n
*
*   @retval RC_OK                               @ref RC_OK
*   @retval RC_ERROR_NOT_ALLOWED                @ref RC_ERROR_NOT_ALLOWED
*/
static t_eReturnCode s_FMKSRL_GetBspMProcessWakeUpMethod(t_eFMKSRL_LinBreakLenght f_WakeUpMeth_e, t_uint32 * f_bspWakeUpMeth_pu32);

/**
 *	@brief          Get the Bsp Uart Multi-Processor WakeUp Method\n
 *
 *	@param[in]      f_ClkPolarity_e             : enum value for Usart Clock Polarity, value from @ref t_eFMKSRL_UsartClkPolaritys.\n
 *	@param[out]     f_bspClkPolarity_pu32       : Storage for Bsp Usart Clock Polarity.\n
*
*   @retval RC_OK                               @ref RC_OK
*   @retval RC_ERROR_NOT_ALLOWED                @ref RC_ERROR_NOT_ALLOWED
*/
static t_eReturnCode s_FMKSRL_GetUsartBspClkPolarity(t_eFMKSRL_UsartClkPolarity f_ClkPolarity_e, t_uint32 * f_bspClkPolarity_pu32);

/**
 *	@brief          Get the Bsp Uart Multi-Processor WakeUp Method\n
 *
 *	@param[in]      f_LastBit_e             : enum value for Usart Clock Phase, value from @ref t_eFMKSRL_UsartLastBit.\n
 *	@param[out]     f_bspLastbit_pu32       : Storage for Bsp Usart Clock Phase.\n
*
*   @retval RC_OK                               @ref RC_OK
*   @retval RC_ERROR_NOT_ALLOWED                @ref RC_ERROR_NOT_ALLOWED
*/
static t_eReturnCode s_FMKSRL_GetUsartBspLastbit(t_eFMKSRL_UsartLastBit f_LastBit_e, t_uint32 * f_bspLastbit_pu32);

/**
 *	@brief          Get the Bsp Uart Multi-Processor WakeUp Method\n
 *
 *	@param[in]      f_ClkPhase_e             : enum value for Clock Last Bit, value from @ref t_eFMKSRL_UsartClockPhase.\n
 *	@param[out]     f_bspClkPhase_pu32       : Storage for Bsp for Clock Last Bit.\n
*
*   @retval RC_OK                               @ref RC_OK
*   @retval RC_ERROR_NOT_ALLOWED                @ref RC_ERROR_NOT_ALLOWED
*/
static t_eReturnCode s_FMKSRL_GetUsartBspClkPhase(t_eFMKSRL_UsartClockPhase f_ClkPhase_e, t_uint32 * f_bspClkPhase_pu32);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * FMKSRL_Cyclic
 *********************************/
t_eReturnCode FMKSRL_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch (g_FmkSrl_ModState_e)
    {
        case STATE_CYCLIC_CFG:
        {
            g_FmkSrl_ModState_e = STATE_CYCLIC_WAITING;
            break;
        }
        case STATE_CYCLIC_WAITING:
        {
            // nothing to do, just wait all module are Ope
            break;
        }
        case STATE_CYCLIC_PREOPE:
        {
            g_FmkSrl_ModState_e = STATE_CYCLIC_OPE;
            break; 
        }
        case STATE_CYCLIC_OPE:
        {
            Ret_e = s_FMKSRL_Operational();
            if(Ret_e < RC_OK)
            {
                g_FmkSrl_ModState_e = STATE_CYCLIC_ERROR;
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
 * FMKSRL_GetState
 *********************************/
t_eReturnCode FMKSRL_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_FmkSrl_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * FMKSRL_SetState
 *********************************/
t_eReturnCode FMKSRL_SetState(t_eCyclicModState f_State_e)
{

    g_FmkSrl_ModState_e = f_State_e;

    return RC_OK;
}


/*********************************
 * FMKSRL_InitDrv
 *********************************/
t_eReturnCode FMKSRL_InitDrv(   t_eFMKSRL_SerialLine f_SrlLine_e, 
                                    t_sFMKSRL_DrvSerialCfg f_SerialCfg_s,
                                    t_cbFMKSRL_RcvMsgEvent * f_rcvMsgEvnt_pcb,
                                    t_cbFMKSRL_TransmitMsgEvent * f_txMsgEvnt_pcb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sFMKSRL_SerialInfo * srlInfo_ps;
    if(f_SrlLine_e >= FMKSRL_SERIAL_LINE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(  (f_rcvMsgEvnt_pcb == (t_cbFMKSRL_RcvMsgEvent *)NULL_FONCTION)
    ||   (f_txMsgEvnt_pcb == (t_cbFMKSRL_TransmitMsgEvent *)NULL_FONCTION))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(g_SerialInfo_as[f_SrlLine_e].isLineConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if(Ret_e == RC_OK)
    {
        //------ Point to the Info Structure ------//
        srlInfo_ps = (t_sFMKSRL_SerialInfo *)&g_SerialInfo_as[f_SrlLine_e];

        //------ Check user configuration ------//
        Ret_e = s_FMKSRL_CheckConfiguration(srlInfo_ps->c_HwType_e, f_SerialCfg_s.hwProtType_e);

        //------ Active Hardware Clock ------//
        if(Ret_e == RC_OK)
        {
            Ret_e = FMKCPU_Set_HwClock(srlInfo_ps->c_clockPort_e, FMKCPU_CLOCKPORT_OPE_ENABLE);
        }
        //------ Set NVIC State ------//
        if(Ret_e == RC_OK)
        {
            Ret_e = FMKCPU_Set_NVICState(srlInfo_ps->c_IRQNType_e, FMKCPU_NVIC_OPE_ENABLE);
        }
        //------ Call Serial Init Management ------//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKSRL_SetBspSerialInit(f_SrlLine_e, &f_SerialCfg_s);
        }
        //------ Copy Information ------//
        if(Ret_e = RC_OK)
        {
            srlInfo_ps->RxInfo_s.RxUserCb_pcb = (t_cbFMKSRL_RcvMsgEvent *)(&f_rcvMsgEvnt_pcb);
            srlInfo_ps->TxInfo_s.TxUserCb_pcb = (t_cbFMKSRL_TransmitMsgEvent *)(&f_txMsgEvnt_pcb);
            srlInfo_ps->runMode_e = f_SerialCfg_s.runMode_e;
            srlInfo_ps->SoftType_e = f_SerialCfg_s.hwProtType_e;
        }
    }

    return Ret_e;
}

/*********************************
 * FMKSRL_Transmit
 *********************************/
t_eReturnCode FMKSRL_Transmit(  t_eFMKSRL_SerialLine f_SrlLine_e, 
                                    t_eFMKSRL_TxOpeMode f_OpeMode_e,
                                    t_uint8 * f_msgData_pu8,
                                    t_uint16 f_dataSize_u16,
                                    t_uint16 f_InfoMode_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e;
    t_sFMKSRL_SerialInfo * srlInfo_ps;
    t_uint32 Timeout_u32 = (t_uint32)0;

    if( (f_SrlLine_e >= FMKSRL_SERIAL_LINE_NB)
    ||  (f_OpeMode_e >= FMKSRL_TX_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_msgData_pu8 == (t_uint8 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }

    //------ Check that Serial Line is in the right state ------//
    if( (Ret_e == RC_OK)
    &&  (g_SerialInfo_as[f_SrlLine_e].isLineConfigured_b == (t_bool)False))
    {
        Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
    }

    if(Ret_e == RC_OK)
    {
        //------ Process logic transmit Depending on f_OpeMode_e ------//
        srlInfo_ps = (t_sFMKSRL_SerialInfo *)(&g_SerialInfo_as[f_SrlLine_e]);
        switch (f_OpeMode_e)
        {
            case FMKSRL_TX_RX_SIZE:
            {
                //------ Configure a Reception Msg with Callback Control base on Sized ------//
                if(srlInfo_ps->SoftType_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    Ret_e = s_FMKSRL_BspRxOpeMngmt( FMKSRL_BSP_RX_OPE_RECEIVE,
                                                    srlInfo_ps,
                                                    f_InfoMode_u16);

                    //------ Transmit msg ------//
                    if(Ret_e == RC_OK)
                    {
                        s_FMKSRL_BspTxOpeMngmt( FMKSRL_BSP_TX_OPE_TRANSMIT,
                                                f_msgData_pu8,
                                                f_dataSize_u16);
                    }
                }
                else if(srlInfo_ps->SoftType_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    //------ In USART Mode A function already exists to transmit & receive ------//
                    s_FMKSRL_BspTxOpeMngmt( FMKSRL_BSP_TX_OPE_TRANSMIT_RECEIVE,
                                                f_msgData_pu8,
                                                f_dataSize_u16);
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;
            }
            case FMKSRL_TX_RX_IDLE:
            {
                //------ Just transmit msg and leave Function ------//
                Ret_e = s_FMKSRL_BspRxOpeMngmt( FMKSRL_BSP_RX_OPE_RECEIVE_IDLE,
                                                srlInfo_ps,
                                                0);
                break;
            }
#ifdef FMKCPU_STM32_ECU_FAMILY_G
            case FMKSRL_TX_RX_TIMEOUT:
            {
                //------ Check that Software Type is UART ------//
                if(srlInfo_ps->SoftType_e != FMKSRL_HW_PROTOCOL_UART)
                {
                    Ret_e = RC_ERROR_NOT_ALLOWED;
                }
                if(Ret_e == RC_OK)
                {
                    //------Convert timeOut ms to unity wanted by BSP Function ------//
                    Ret_e = s_FMKSRL_ConvertTimeout(f_InfoMode_u16, &Timeout_u32);
                }

                //------Configure and Activate Reception Timeout Trigger ------//
                if(Ret_e == RC_OK)
                {
                    HAL_UART_ReceiverTimeout_Config(    &srlInfo_ps->bspHandle_u.uartH_s,
                                                        Timeout_u32);
                    bspRet_e = HAL_UART_EnableReceiverTimeout(&srlInfo_ps->bspHandle_u.uartH_s);
                    if(bspRet_e != HAL_OK)
                    {
                        Ret_e = RC_WARNING_BUSY;
                    }
                }
                break;
            }
#endif
            //------ Nothing more to do for this case ------//
            case FMKSRL_TX_ONESHOT:
                break;
            case FMKSRL_TX_NB:
            default:
            {
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
            }
        }
        //------ Transmit msg ------//
        if(Ret_e == RC_OK)
        {
            s_FMKSRL_BspTxOpeMngmt( FMKSRL_BSP_TX_OPE_TRANSMIT,
                                    f_msgData_pu8,
                                    f_dataSize_u16);
        }
    }

}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_FMKSRL_CheckConfiguration
 *********************************/
static t_eReturnCode s_FMKSRL_CheckConfiguration(t_eFMKSRL_HwProtocolType f_hwCfg_e, t_eFMKSRL_HwProtocolType f_softCfg_e)
{
    t_eReturnCode Ret_e = RC_OK;

    if( (f_hwCfg_e   >= FMKSRL_HW_PROTOCOL_NB)
     || (f_softCfg_e >= FMKSRL_HW_PROTOCOL_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        if( (f_softCfg_e == FMKSRL_HW_PROTOCOL_USART) 
        &&  (f_hwCfg_e == FMKSRL_HW_PROTOCOL_UART))
        {
            Ret_e = RC_ERROR_NOT_ALLOWED;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKSRL_SetBspSerialInit
 *********************************/
static t_eReturnCode s_FMKSRL_SetBspSerialInit(t_eFMKSRL_SerialLine f_SrlLine_e,  t_sFMKSRL_DrvSerialCfg *f_DrvSrlCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    UART_InitTypeDef * bspUartInit_ps;
    USART_InitTypeDef * bspUsartInit_ps;
    t_sFMKSRL_SerialInfo * srlInfo_ps;
    t_uint32 bspLineBaudrate_u32 = (t_uint32)0;
    t_uint32 bspLineParity_u32 = (t_uint32)0;
    t_uint32 bspLineStopbit_u32 = (t_uint32)0;
    t_uint32 bspLineMode_u32 = (t_uint32)0;
    t_uint32 bspLineWordLenght_u32 = (t_uint32)0;

    if(f_SrlLine_e >= FMKSRL_SERIAL_LINE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_DrvSrlCfg_ps == (t_sFMKSRL_DrvSerialCfg *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        srlInfo_ps = (t_sFMKSRL_SerialInfo *)(&g_SerialInfo_as[f_SrlLine_e]);
        //--------- Fistly Configure All Common variable to Uart and Usart ---------//
        //--------- Get Bsp Line Baudrate ---------//
        Ret_e = s_FMKSRL_GetBspLineBaudrate(f_DrvSrlCfg_ps->hwCfg_s.Baudrate_e, &bspLineBaudrate_u32);

        //--------- Get Bsp Line Mode ---------//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKSRL_GetBspLineMode(    &srlInfo_ps->c_HwType_e,
                                                f_DrvSrlCfg_ps->hwCfg_s.Mode_e,
                                                &bspLineMode_u32);
        }
        
        //--------- Get Bsp Line Parity ---------//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKSRL_GetBspLineParity(  &srlInfo_ps->c_HwType_e,
                                                f_DrvSrlCfg_ps->hwCfg_s.Parity_e,
                                                &bspLineParity_u32);
        }
        
        //--------- Get Bsp Line Word Lenght ---------//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKSRL_GetBspLineMode(    &srlInfo_ps->c_HwType_e,
                                                f_DrvSrlCfg_ps->hwCfg_s.wordLenght_e,
                                                &bspLineWordLenght_u32);
        }
        
        //--------- Get Bsp Line Stop Bit ---------//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKSRL_GetBspLineStopbit( &srlInfo_ps->c_HwType_e,
                                                f_DrvSrlCfg_ps->hwCfg_s.Stopbit_e,
                                                &bspLineStopbit_u32);
        }
        switch (srlInfo_ps->c_HwType_e)
        {
            case FMKSRL_HW_PROTOCOL_UART:
            {
                //-------- Copy data in Uart Init --------//
                bspUartInit_ps = &srlInfo_ps->bspHandle_u.uartH_s.Init;

                bspUartInit_ps->BaudRate   = bspLineBaudrate_u32;
                bspUartInit_ps->Mode       = bspLineMode_u32;
                bspUartInit_ps->Parity     = bspLineParity_u32;
                bspUartInit_ps->StopBits   = bspLineStopbit_u32;
                bspUartInit_ps->WordLength = bspLineWordLenght_u32;
                
                //-------- Call Uart Bsp Init Managment --------//
                Ret_e = s_FMKSRL_SetUartBspInit(    f_SrlLine_e, 
                                                    &f_DrvSrlCfg_ps->CfgSpec_u.uartCfg_s,
                                                    &f_DrvSrlCfg_ps->hwCfg_s);
                break;
            }

            case FMKSRL_HW_PROTOCOL_USART:
            {
                //-------- Copy data in Usart Init --------//
                bspUsartInit_ps = &srlInfo_ps->bspHandle_u.usartH_s.Init;

                bspUsartInit_ps->BaudRate   = bspLineBaudrate_u32;
                bspUsartInit_ps->Mode       = bspLineMode_u32;
                bspUsartInit_ps->Parity     = bspLineParity_u32;
                bspUsartInit_ps->StopBits   = bspLineStopbit_u32;
                bspUsartInit_ps->WordLength = bspLineWordLenght_u32;
                //-------- Call Usart Bsp Init Managment --------//
                Ret_e = s_FMKSRL_SetUsartBspInit(   srlInfo_ps,
                                                    &f_DrvSrlCfg_ps->CfgSpec_u.usartCfg_s,
                                                    &f_DrvSrlCfg_ps->hwCfg_s);
                break;
            }
            case FMKSRL_HW_PROTOCOL_NB:
            default:
            {
                Ret_e = RC_ERROR_NOT_SUPPORTED;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKSRL_SetUartBspInit
 *********************************/
static t_eReturnCode s_FMKSRL_SetUartBspInit(   t_eFMKSRL_SerialLine      f_SrlLine_e, 
                                                t_sFMKSRL_UartCfgSpec   * f_UartCfg_ps,
                                                t_sFMKSRL_HwProtocolCfg * f_HwProtCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    UART_InitTypeDef * bspUartInit_ps;
    t_sFMKSRL_SerialInfo * srlInfo_ps;
    t_uint32 bspLineHwFlowCtrl_u32 = (t_uint32)0;
    t_uint32 bspLINBreakLen_u32 = (t_uint32)0;
    t_uint32 bspWakeUpMethod_u32 = (t_uint32)0;
    t_uint8 idxIdUsed_u8;
    t_uint8 MProcessId_u8;

    if( (f_UartCfg_ps == (t_sFMKSRL_UartCfgSpec *)NULL)
    ||  (f_HwProtCfg_ps == (t_sFMKSRL_HwProtocolCfg *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        srlInfo_ps = (t_sFMKSRL_SerialInfo *)(&g_SerialInfo_as[f_SrlLine_e]);
        bspUartInit_ps = (UART_InitTypeDef *)(&srlInfo_ps->bspHandle_u.uartH_s);

        #ifdef FMKCPU_STM32_ECU_FAMILY_G
            
            if(Ret_e == RC_OK)
            {
                //--------- Get Bsp Hardware Flow Control ---------//
                Ret_e = s_FMKSRL_GetUartBspHwFlowCtrl( f_UartCfg_ps->hwFlowCtrl_e, &bspLineHwFlowCtrl_u32);
                bspUartInit_ps->HwFlowCtl  = bspLineHwFlowCtrl_u32;
                //--------- Set Advance Configuration ---------//
                Ret_e = s_FMKSRL_SetUartAdvanceCfg( &srlInfo_ps->bspHandle_u.uartH_s.AdvancedInit,
                                                &f_UartCfg_ps->advProtCfg_s);
            }
        #endif
        if(Ret_e == RC_OK)
        {
            //--------- As The Clock Freq is about 40-50 MHz, 
            // This configuration support all configuration ---------//
            bspUartInit_ps->OverSampling = UART_OVERSAMPLING_8;
            bspUartInit_ps->ClockPrescaler = UART_PRESCALER_DIV1;
            //--------- Change to Enable if Noise on line is expected ---------//
            bspUartInit_ps->OneBitSampling = DISABLE;  
        }

        if(Ret_e == RC_OK)
        {
            //--------- Now Call Specfic Init Function Depending On User Cfg ---------//
            switch (f_UartCfg_ps->Type_e)
            {
                //--------- Configure Uart Instance as Normal Set Up ---------//
                case FMKSRL_UART_TYPECFG_UART:
                {
                    bspRet_e = HAL_UART_Init(&srlInfo_ps->bspHandle_u.uartH_s);
                    break;
                }
                //--------- Configure Uart Instance as Half Duplex Set Up ---------//
                case FMKSRL_UART_TYPECFG_HALF_DUPLEX:
                {
                    bspRet_e = HAL_HalfDuplex_Init(&srlInfo_ps->bspHandle_u.uartH_s);
                    break;
                }
                //--------- Configure Uart Instance as LIN Set Up ---------//
                case FMKSRL_UART_TYPECFG_LIN:
                {
                    //--------- Get Bsp LIN break Detection Lenght ---------//
                    Ret_e = s_FMMKSRL_GetBspLinBreakLen(    f_UartCfg_ps->typeCfg_u.linCfg_s.BreakLen_e,
                                                            &bspLINBreakLen_u32);
                    if(Ret_e == RC_OK)
                    {
                        bspRet_e = HAL_LIN_Init(&srlInfo_ps->bspHandle_u.uartH_s, bspLINBreakLen_u32);
                    }
                    break;
                }
                //--------- Configure Uart Instance as Multi Process Set Up ---------//
                case FMKSRL_UART_TYPECFG_MULTI_PROCESS:
                {
                    //--------- Get Bsp Multi Proccesor Wake Up method ---------//
                    Ret_e = s_FMKSRL_GetBspMProcessWakeUpMethod(    f_UartCfg_ps->typeCfg_u.MProcessCfg_s.WakeUpMethod_e,
                                                                    &bspWakeUpMethod_u32);

                    MProcessId_u8 = f_UartCfg_ps->typeCfg_u.MProcessCfg_s.IstcIdentifer_u8;
                    //--------- Check ID validity ---------//
                    for (idxIdUsed_u8 = (t_uint8)0; idxIdUsed_u8 < FMKSRL_SERIAL_LINE_NB ; idxIdUsed_u8++)
                    {
                        if(MProcessId_u8 == g_MProcessIdUsed[idxIdUsed_u8])
                        {
                            Ret_e = RC_ERROR_ALREADY_CONFIGURED;
                            break;
                        }
                    }

                    if(Ret_e == RC_OK)
                    {
                        bspRet_e = HAL_MultiProcessor_Init( &srlInfo_ps->bspHandle_u.uartH_s,
                                                            MProcessId_u8,
                                                            bspWakeUpMethod_u32);
                
                        //--------- Update ID Used ---------//
                        g_MProcessIdUsed[f_SrlLine_e] = MProcessId_u8;
                    }
                    break;
                }
                case FMKSRL_UART_TYPECFG_NB:
                default:
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
            }
            if(bspRet_e != HAL_OK)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKSRL_SetUsartBspInit
 *********************************/
static t_eReturnCode s_FMKSRL_SetUsartBspInit(  t_sFMKSRL_SerialInfo *    f_SrlInfo_ps, 
                                                t_sFMKSRL_UsartCfgSpec *  f_UsartCfg_ps,
                                                t_sFMKSRL_HwProtocolCfg * f_HwProtCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    USART_InitTypeDef * bspUsartInit_ps;
    t_uint32 bspClkPolarity_u32 = (t_uint32)0;
    t_uint32 bspClkPhase_u32 = (t_uint32)0;
    t_uint32 bspClkLastBit_u32 = (t_uint32)0;

    if( (f_SrlInfo_ps == (t_sFMKSRL_SerialInfo *)NULL)
    ||  (f_UsartCfg_ps == (t_sFMKSRL_UsartCfgSpec *)NULL)
    ||  (f_HwProtCfg_ps == (t_sFMKSRL_HwProtocolCfg *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //--------- Get Bsp Clock Polarity ---------//
        Ret_e = s_FMKSRL_GetUsartBspClkPolarity(f_UsartCfg_ps->clkPolarity_e, bspClkPolarity_u32);

        //--------- Get Bsp Clock Phase ---------//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKSRL_GetUsartBspClkPhase(f_UsartCfg_ps->clockPhase_e, bspClkPhase_u32);
        }
        //--------- Get Bsp Clock Last Bit ---------//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKSRL_GetUsartBspLastbit(f_UsartCfg_ps->lastBit_e, bspClkLastBit_u32);
        }

        
        if(Ret_e == RC_OK)
        {
            bspUsartInit_ps = (USART_HandleTypeDef *)(&f_SrlInfo_ps->bspHandle_u.usartH_s);

            //--------- Copy Data ---------//
            bspUsartInit_ps->CLKLastBit = bspClkLastBit_u32;
            bspUsartInit_ps->CLKPhase = bspClkPhase_u32;
            bspUsartInit_ps->CLKPolarity = bspClkPolarity_u32;
            bspUsartInit_ps->ClockPrescaler = USART_PRESC_PRESCALER_0;

            //--------- Get Bsp Usart Init Function Depending on User Cfg ---------//
            switch (f_UsartCfg_ps->Type_e)
            {
                case FMKSRL_USART_TYPECFG_USART:
                {
                    bspRet_e = HAL_USART_Init(&f_SrlInfo_ps->bspHandle_u.usartH_s);
                }
                case FMKSRL_USART_TYPECFG_NB:
                default:
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    break;
                }
            }
            if(bspRet_e != HAL_OK)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKSRL_GetBspLineBaudrate
 *********************************/
static t_eReturnCode s_FMKSRL_GetBspLineBaudrate(t_eFMKSRL_LineBaudrate f_lineBaudrate_e, t_uint32 *f_bspLineBaudrate_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_lineBaudrate_e >= FMKSRL_LINE_BAUDRATE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspLineBaudrate_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e = RC_OK)
    {
        switch (f_lineBaudrate_e)
        {
            case FMKSRL_LINE_BAUDRATE_300:
                *f_bspLineBaudrate_pu32 = (t_uint32)300;
                break;
            case FMKSRL_LINE_BAUDRATE_1200:
                *f_bspLineBaudrate_pu32 = (t_uint32)1200;
                break;
            case FMKSRL_LINE_BAUDRATE_2400:
                *f_bspLineBaudrate_pu32 = (t_uint32)2400;
                break;
            case FMKSRL_LINE_BAUDRATE_4800:
                *f_bspLineBaudrate_pu32 = (t_uint32)4800;
                break;
            case FMKSRL_LINE_BAUDRATE_9600:
                *f_bspLineBaudrate_pu32 = (t_uint32)9600;
                break;
            case FMKSRL_LINE_BAUDRATE_19200:
                *f_bspLineBaudrate_pu32 = (t_uint32)19200;
                break;
            case FMKSRL_LINE_BAUDRATE_38400:
                *f_bspLineBaudrate_pu32 = (t_uint32)38400;
                break;  
            case FMKSRL_LINE_BAUDRATE_57600:
                *f_bspLineBaudrate_pu32 = (t_uint32)57600;
                break;
            case FMKSRL_LINE_BAUDRATE_74880:
                *f_bspLineBaudrate_pu32 = (t_uint32)74880;
                break;
            case FMKSRL_LINE_BAUDRATE_115200:
                *f_bspLineBaudrate_pu32 = (t_uint32)115200;
                break;
            case FMKSRL_LINE_BAUDRATE_230400:
                *f_bspLineBaudrate_pu32 = (t_uint32)230400;
                break;
            case FMKSRL_LINE_BAUDRATE_250000:
                *f_bspLineBaudrate_pu32 = (t_uint32)250000;
                break;
            case FMKSRL_LINE_BAUDRATE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKSRL_GetBspLineStopbit
 *********************************/
static t_eReturnCode s_FMKSRL_GetBspLineStopbit(    t_eFMKSRL_HwProtocolType f_HwProtUsed_e,
                                                    t_eFMKSRL_LineSoptbit f_lineStopbit_e, 
                                                    t_uint32 *f_bspLineStopbit_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    // Validation des paramètres d'entrée
    if ((f_HwProtUsed_e >= FMKSRL_HW_PROTOCOL_NB) 
        || (f_lineStopbit_e >= FMKSRL_LINE_STOPBIT_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_bspLineStopbit_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }

    if (Ret_e == RC_OK)
    {
        //--------- Switch on Software Stop Bit Used ---------//
        switch (f_lineStopbit_e)
        {
            case FMKSRL_LINE_STOPBIT_0_5:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineStopbit_pu32 = (t_uint32)UART_STOPBITS_0_5;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineStopbit_pu32 = (t_uint32)USART_STOPBITS_0_5;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;

            case FMKSRL_LINE_STOPBIT_1:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineStopbit_pu32 = (t_uint32)UART_STOPBITS_1;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineStopbit_pu32 = (t_uint32)USART_STOPBITS_1;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;

            case FMKSRL_LINE_STOPBIT_1_5:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineStopbit_pu32 = (t_uint32)UART_STOPBITS_1_5;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineStopbit_pu32 = (t_uint32)USART_STOPBITS_1_5;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;

            case FMKSRL_LINE_STOPBIT_2:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineStopbit_pu32 = (t_uint32)UART_STOPBITS_2;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineStopbit_pu32 = (t_uint32)USART_STOPBITS_2;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;

            case FMKSRL_LINE_STOPBIT_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                break;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKSRL_GetBspLineParity
 *********************************/
static t_eReturnCode s_FMKSRL_GetBspLineParity( t_eFMKSRL_HwProtocolType f_HwProtUsed_e,
                                                t_eFMKSRL_LineParity f_lineParity_e,
                                                t_uint32 *f_bspLineParity_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    // Validation des paramètres d'entrée
    if ((f_HwProtUsed_e >= FMKSRL_HW_PROTOCOL_NB) 
        || (f_lineParity_e >= FMKSRL_LINE_PARITY_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_bspLineParity_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }

    if (Ret_e == RC_OK)
    {
        //--------- Switch on Software Stop Bit Used ---------//
        switch (f_lineParity_e)
        {
            case FMKSRL_LINE_PARITY_NONE:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineParity_pu32 = (t_uint32)UART_PARITY_NONE;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineParity_pu32 = (t_uint32)USART_PARITY_NONE;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;

            case FMKSRL_LINE_PARITY_EVEN:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineParity_pu32 = (t_uint32)UART_PARITY_EVEN;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineParity_pu32 = (t_uint32)USART_PARITY_EVEN;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;

            case FMKSRL_LINE_PARITY_ODD:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineParity_pu32 = (t_uint32)UART_PARITY_EVEN;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineParity_pu32 = (t_uint32)USART_PARITY_EVEN;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;

            case FMKSRL_LINE_PARITY_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                break;
        }
    }

    return Ret_e;
} 

/*********************************
 * s_FMKSRL_GetBspLineParity
 *********************************/
static t_eReturnCode s_FMKSRL_GetBspLineMode(   t_eFMKSRL_HwProtocolType f_HwProtUsed_e,
                                                t_eFMKSRL_LineMode f_lineMode_e,
                                                t_uint32 *f_bspLineMode_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    // Validation des paramètres d'entrée
    if ((f_HwProtUsed_e >= FMKSRL_HW_PROTOCOL_NB) 
        || (f_lineMode_e >= FMKSRL_LINE_MODE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_bspLineMode_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }

    if (Ret_e == RC_OK)
    {
        //--------- Switch on Software Stop Bit Used ---------//
        switch (f_lineMode_e)
        {
            case FMKSRL_LINE_MODE_RX:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineMode_pu32 = (t_uint32)UART_MODE_RX;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineMode_pu32 = (t_uint32)USART_MODE_RX;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;

            case FMKSRL_LINE_MODE_TX:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineMode_pu32 = (t_uint32)UART_MODE_TX;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineMode_pu32 = (t_uint32)USART_MODE_TX;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;

            case FMKSRL_LINE_MODE_RX_TX:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineMode_pu32 = (t_uint32)UART_MODE_TX_RX;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineMode_pu32 = (t_uint32)USART_MODE_TX_RX;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;

            case FMKSRL_LINE_MODE_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                break;
        }
    }

    return Ret_e;
}

#ifdef FMKCPU_STM32_ECU_FAMILY_G
    /*********************************
     * s_FMKSRL_SetUartAdvanceCfg
     *********************************/
    static t_eReturnCode s_FMKSRL_SetUartAdvanceCfg(UART_AdvFeatureInitTypeDef * f_AdvInit_ps, t_sFMKSRL_UartAdvProtCfg * f_SoftAdvCfg_ps)
    {
        t_eReturnCode Ret_e = RC_OK;
        //--------- For now, we don't use it ---------//
        f_AdvInit_ps->AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

        return Ret_e;
    }
#endif
/*********************************
 * s_FMKSRL_GetBspLineParity
 *********************************/
static t_eReturnCode s_FMKSRL_GetBspWordLenght( t_eFMKSRL_HwProtocolType f_HwProtUsed_e,
                                                t_eFMKSRL_LineWordLenght f_lineWordLenght_e, 
                                                t_uint32 *f_bspLineWordLenght_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if ((f_HwProtUsed_e >= FMKSRL_HW_PROTOCOL_NB) 
        || (f_lineWordLenght_e >= FMKSRL_LINE_WORDLEN_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if (f_bspLineWordLenght_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }

    if (Ret_e == RC_OK)
    {
        //--------- Switch on Software Stop Bit Used ---------//
        switch (f_lineWordLenght_e)
        {
            case FMKSRL_LINE_WORDLEN_9BITS:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineWordLenght_pu32 = (t_uint32)USART_WORDLENGTH_9B;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineWordLenght_pu32 = (t_uint32)UART_WORDLENGTH_9B;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;

            case FMKSRL_LINE_WORDLEN_8BITS:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineWordLenght_pu32 = (t_uint32)UART_WORDLENGTH_8B;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineWordLenght_pu32 = (t_uint32)USART_WORDLENGTH_8B;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;
#ifdef FMKCPU_STM32_ECU_FAMILY_G
            case FMKSRL_LINE_WORDLEN_7BITS:
                //--------- Depend on Hardware Protocol Used ---------//
                if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_UART)
                {
                    *f_bspLineWordLenght_pu32 = (t_uint32)UART_WORDLENGTH_7B;
                }
                else if (f_HwProtUsed_e == FMKSRL_HW_PROTOCOL_USART)
                {
                    *f_bspLineWordLenght_pu32 = (t_uint32)USART_WORDLENGTH_7B;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                }
                break;
#endif
            case FMKSRL_LINE_MODE_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                break;
        }
    }

    return Ret_e;
} 

/*********************************
 * s_FMKSRL_GetUartBspHwFlowCtrl
 *********************************/
static t_eReturnCode s_FMKSRL_GetUartBspHwFlowCtrl(t_eFMKSRL_UartHwFlowCtrl f_HwFlowCtrl_e, t_uint32 * f_bspHwFlowCtrl_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_HwFlowCtrl_e >= FMKSRL_UART_HW_FLOW_CTRL_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspHwFlowCtrl_pu32 == (t_uint32 * )NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_HwFlowCtrl_e)
        {
            case FMKSRL_UART_HW_FLOW_CTRL_NONE:
                *f_bspHwFlowCtrl_pu32 = (t_uint32)UART_HWCONTROL_NONE;
                break;

            case FMKSRL_UART_HW_FLOW_CTRL_RTS:
                *f_bspHwFlowCtrl_pu32 = (t_uint32)UART_HWCONTROL_RTS;
                break;

            case FMKSRL_UART_HW_FLOW_CTRL_CTS:
                *f_bspHwFlowCtrl_pu32 = (t_uint32)UART_HWCONTROL_CTS;
                break;

            case FMKSRL_UART_HW_FLOW_CTRL_RTS_CTS:
                *f_bspHwFlowCtrl_pu32 = (t_uint32)UART_HWCONTROL_RTS_CTS;
                break;

            case FMKSRL_UART_HW_FLOW_CTRL_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMMKSRL_GetBspLinBreakLen
 *********************************/
static t_eReturnCode s_FMMKSRL_GetBspLinBreakLen(t_eFMKSRL_LinBreakLenght f_BreakLenght_e, t_uint32 * f_bspBreakLenght_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_BreakLenght_e >= FMKSRL_LIN_BREAK_LENGHT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspBreakLenght_pu32 == (t_uint32 * )NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_BreakLenght_e)
        {
            case FMKSRL_LIN_BREAK_LENGHT_10B:
                *f_bspBreakLenght_pu32 = (t_uint32)UART_LINBREAKDETECTLENGTH_10B;
                break;

            case FMKSRL_LIN_BREAK_LENGHT_11B:
                *f_bspBreakLenght_pu32 = (t_uint32)UART_LINBREAKDETECTLENGTH_11B;
                break;

            case FMKSRL_LIN_BREAK_LENGHT_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }

    return Ret_e;
}

/***************************************
 * s_FMKSRL_GetBspMProcessWakeUpMethod
 ***************************************/
static t_eReturnCode s_FMKSRL_GetBspMProcessWakeUpMethod(t_eFMKSRL_LinBreakLenght f_WakeUpMeth_e, t_uint32 * f_bspWakeUpMeth_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_WakeUpMeth_e >= FMKSRL_MPROCESS_WAKEUP_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspWakeUpMeth_pu32 == (t_uint32 * )NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_WakeUpMeth_e)
        {
            case FMKSRL_MPROCESS_WAKEUP_IDLE:
                *f_bspWakeUpMeth_pu32 = (t_uint32)UART_WAKEUPMETHOD_IDLELINE;
                break;

            case FMKSRL_MPROCESS_WAKEUP_ADDMARK:
                *f_bspWakeUpMeth_pu32 = (t_uint32)UART_WAKEUPMETHOD_ADDRESSMARK;
                break;

            case FMKSRL_MPROCESS_WAKEUP_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }

    return Ret_e;
}

/***************************************
 * s_FMKSRL_GetUsartBspClkPolarity
 ***************************************/
static t_eReturnCode s_FMKSRL_GetUsartBspClkPolarity(t_eFMKSRL_UsartClkPolarity f_ClkPolarity_e, t_uint32 * f_bspClkPolarity_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_ClkPolarity_e >= FMKSRL_USART_CLK_POLARITY_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspClkPolarity_pu32 == (t_uint32 * )NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_ClkPolarity_e)
        {
            case FMKSRL_USART_CLK_POLARITY_HIGH:
                *f_bspClkPolarity_pu32 = (t_uint32)USART_POLARITY_HIGH;
                break;

            case FMKSRL_USART_CLK_POLARITY_LOW:
                *f_bspClkPolarity_pu32 = (t_uint32)USART_POLARITY_LOW;
                break;

            case FMKSRL_USART_CLK_POLARITY_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }

    return Ret_e;
}

/***************************************
 * s_FMKSRL_GetUsartBspLastbit
 ***************************************/
static t_eReturnCode s_FMKSRL_GetUsartBspLastbit(t_eFMKSRL_UsartLastBit f_LastBit_e, t_uint32 * f_bspLastbit_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_LastBit_e >= FMKSRL_USART_LAST_BIT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspLastbit_pu32 == (t_uint32 * )NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_LastBit_e)
        {
            case FMKSRL_USART_LAST_BIT_ENABLE:
                *f_bspLastbit_pu32 = (t_uint32)USART_LASTBIT_ENABLE;
                break;

            case FMKSRL_USART_LAST_BIT_DISABLE:
                *f_bspLastbit_pu32 = (t_uint32)USART_LASTBIT_DISABLE;
                break;

            case FMKSRL_USART_LAST_BIT_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }

    return Ret_e;
}

static t_eReturnCode s_FMKSRL_GetUsartBspClkPhase(t_eFMKSRL_UsartClockPhase f_ClkPhase_e, t_uint32 * f_bspClkPhase_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_ClkPhase_e >= FMKSRL_USART_PHASE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspClkPhase_pu32 == (t_uint32 * )NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_ClkPhase_e)
        {
            case FMKSRL_USART_PHASE_1EDGE:
                *f_bspClkPhase_pu32 = (t_uint32)USART_PHASE_1EDGE;
                break;

            case FMKSRL_USART_PHASE_2EDGE:
                *f_bspClkPhase_pu32 = (t_uint32)USART_PHASE_2EDGE;
                break;

            case FMKSRL_USART_PHASE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
        }
    }

    return Ret_e;
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
