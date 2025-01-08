/*********************************************************************
 * @file        APP_LGC.c
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
#include "stdio.h"
#include "string.h"

#include "./APP_LGC.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
#include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
#include "FMK_HAL/FMK_CAN/Src/FMK_FDCAN.h"
#include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//


/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
static t_eCyclicModState g_AppLgc_ModState_e = STATE_CYCLIC_CFG;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
static t_eReturnCode s_APPLGC_PreOperational(void);
static t_eReturnCode s_APPLGC_Operational(void);
static t_eReturnCode s_APPLGC_ConfigurationState(void);
static t_eReturnCode s_APPLGC_Callback(t_eFMKCPU_InterruptLineType f_InterruptType_e, t_uint8 f_InterruptLine_u8);
static void s_APPLGC_RcvSrlEvent(  t_uint8 * f_rxData_pu8, 
                                    t_uint16 f_dataSize_u16, 
                                    t_eFMKSRL_RxCallbackInfo f_InfoCb_e);

static void s_APPLGC_TranmistEvnt(t_bool f_isMsgTransmit_b, t_eFMKSRL_TxCallbackInfo f_InfoCb_e);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * APPLGC_Init
 *********************************/
t_eReturnCode APPLGC_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    
    return Ret_e;
}

/*********************************
 * APPLGC_Init
 *********************************/
t_eReturnCode APPLGC_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;
    // code to run every x milliseconds, config in APPSYS_ConfigPrivate.h

    switch (g_AppLgc_ModState_e)
    {
    case STATE_CYCLIC_CFG:
    {
        Ret_e = s_APPLGC_ConfigurationState();
        if(Ret_e == RC_OK)
        {
            g_AppLgc_ModState_e = STATE_CYCLIC_WAITING;
        }
        break;
    }

    case STATE_CYCLIC_WAITING:
    {
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_PREOPE:
    {
        Ret_e = s_APPLGC_PreOperational();
        if(Ret_e == RC_OK)
        {
            g_AppLgc_ModState_e = STATE_CYCLIC_OPE;
        }
        break;
    }
    case STATE_CYCLIC_OPE:
    {
        Ret_e = s_APPLGC_Operational();
        if(Ret_e < RC_OK)
        {
            g_AppLgc_ModState_e = STATE_CYCLIC_ERROR;
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
 * APPLGC_GetState
 *********************************/
t_eReturnCode APPLGC_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_AppLgc_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * APPLGC_SetState
 *********************************/
t_eReturnCode APPLGC_SetState(t_eCyclicModState f_State_e)
{

    g_AppLgc_ModState_e = f_State_e;

    return RC_OK;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
static void s_APPLGC_RcvSrlEvent(   t_uint8 * f_rxData_pu8, 
                                    t_uint16 f_dataSize_u16, 
                                    t_eFMKSRL_RxCallbackInfo f_InfoCb_e)
{
    t_eReturnCode Ret_e = RC_OK;
    char msgbuffer[20];
    sprintf(msgbuffer, "Got It\r\n");


    if(f_InfoCb_e == FMKSRL_CB_INFO_RECEIVE_ENDING)
    {
    }
    return;
}

static void s_APPLGC_TranmistEvnt(t_bool f_isMsgTransmit_b, t_eFMKSRL_TxCallbackInfo f_InfoCb_e)
{
    return;
}
/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_ConfigurationState(void)
{
    t_eReturnCode Ret_e = RC_OK;

    t_sFMKSRL_DrvSerialCfg SrlCfg_s;
    SrlCfg_s.runMode_e = FMKSRL_LINE_RUNMODE_DMA;
    SrlCfg_s.hwProtType_e = FMKSRL_HW_PROTOCOL_UART;

    SrlCfg_s.hwCfg_s.Baudrate_e = FMKSRL_LINE_BAUDRATE_9600,
    SrlCfg_s.hwCfg_s.Mode_e = FMKSRL_LINE_MODE_RX_TX;
    SrlCfg_s.hwCfg_s.Parity_e = FMKSRL_LINE_PARITY_NONE,
    SrlCfg_s.hwCfg_s.Stopbit_e = FMKSRL_LINE_STOPBIT_1,
    SrlCfg_s.hwCfg_s.wordLenght_e = FMKSRL_LINE_WORDLEN_8BITS,

    SrlCfg_s.CfgSpec_u.uartCfg_s.hwFlowCtrl_e = FMKSRL_UART_HW_FLOW_CTRL_NONE;
    SrlCfg_s.CfgSpec_u.uartCfg_s.Type_e = FMKSRL_UART_TYPECFG_UART,

    Ret_e = FMKSRL_InitDrv(FMKSRL_SERIAL_LINE_1, SrlCfg_s,
                            s_APPLGC_RcvSrlEvent,
                            s_APPLGC_TranmistEvnt);
    /*if(Ret_e == RC_OK)
    {
        Ret_e = FMKSRL_ConfigureReception(  FMKSRL_SERIAL_LINE_1,
                                            FMKSRL_OPE_RX_CYCLIC_SIZE,
                                            (t_uint16)9);
    }*/
    Ret_e = RC_OK;
    return Ret_e;
}

/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_PreOperational(void)
{
    t_eReturnCode Ret_e = RC_OK;

    return Ret_e;
}
/*********************************
 * s_APPLGC_Operational
 *********************************/
static t_eReturnCode s_APPLGC_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    char msgbuffer[20];
    sprintf(msgbuffer, "Hello World\r\n");

    Ret_e = FMKSRL_Transmit(FMKSRL_SERIAL_LINE_1,
                            FMKSRL_TX_ONESHOT,
                            (t_uint8 * )msgbuffer,
                            strlen(msgbuffer),
                            (t_uint16)0,
                            (t_bool)True);
    return RC_OK;
}

/*********************************
 * s_APPLGC_Operational
 *********************************/
static t_eReturnCode s_APPLGC_Callback(t_eFMKCPU_InterruptLineType f_InterruptType_e, t_uint8 f_InterruptLine_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_uint16 dutycycle = 0;
    dutycycle += 50;
    UNUSED(f_InterruptType_e);
    UNUSED(f_InterruptLine_u8);

    if(dutycycle >= 1000)
    {
        dutycycle = (t_uint16)0;
    }

    Ret_e = FMKIO_Set_OutPwmSigValue(FMKIO_OUTPUT_SIGPWM_2, dutycycle);
    //FMKCPU_Set_Delay(1000);
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
 *	@params[in] 
 *	@params[out]
 *	 
 *
 *
 */

