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

#include "./APP_LGC.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
#include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
#include "FMK_HAL/FMK_CAN/Src/FMK_FDCAN.h"
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
static t_eCyclicFuncState g_state_e = STATE_CYCLIC_PREOPE;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
static t_eReturnCode s_APPLGC_Operational(void);
static t_eReturnCode s_APPLGC_PreOperational(void);

static t_eReturnCode s_APPLGC_callback(t_sFMKFDCAN_RxItemEvent f_rxEvent_s, t_eFMKFDCAN_NodeStatus f_status);
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

    switch (g_state_e)
    {
    case STATE_CYCLIC_PREOPE:
    {
        Ret_e = s_APPLGC_PreOperational();
        if(Ret_e == RC_OK)
        {
            g_state_e = STATE_CYCLIC_WAITING;
        }
        break;
    }

    case STATE_CYCLIC_WAITING:
    {
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_OPE:
    {
        Ret_e = s_APPLGC_Operational();
        if(Ret_e < RC_OK)
        {
            g_state_e = STATE_CYCLIC_ERROR;
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
t_eReturnCode APPLGC_GetState(t_eCyclicFuncState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicFuncState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_state_e;
    }

    return Ret_e;
}

/*********************************
 * APPLGC_SetState
 *********************************/
t_eReturnCode APPLGC_SetState(t_eCyclicFuncState f_State_e)
{

    g_state_e = f_State_e;

    return RC_OK;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
static t_eReturnCode s_APPLGC_callback(t_sFMKFDCAN_RxItemEvent f_rxEvent_s, t_eFMKFDCAN_NodeStatus f_status)
{
    t_eReturnCode Ret_e = RC_OK;

    t_uint8 data_ua[8];
    if (f_status == 0)
    {
        data_ua[0] = f_rxEvent_s.CanMsg_s.data_pu8[0];
        data_ua[1] = f_rxEvent_s.CanMsg_s.data_pu8[2];
        data_ua[2] = f_rxEvent_s.CanMsg_s.data_pu8[1];
        data_ua[3] = f_rxEvent_s.CanMsg_s.data_pu8[3];
    }
    return Ret_e;
}

/*********************************
 * s_APPLGC_PreOperational
 *********************************/
static t_eReturnCode s_APPLGC_PreOperational(void)
{
    t_eReturnCode Ret_e = RC_OK;

    t_sFMKFDCAN_RxItemEventCfg caca = 
    {
        .callback_cb = s_APPLGC_callback, 
        .Dlc_e = FMKFDCAN_DLC_8,
        .ItemId_s = {
            .FramePurpose_e = FMKFDCAN_FRAME_PURPOSE_DATA,
            .Identifier_u32 = 0x123,
            .IdType_e = FMKFDCAN_IDTYPE_STANDARD,
        },
        .maskId_u32 = 0xFF0,
    };
    Ret_e = FMKFDCAN_ConfigureRxItemEvent(FMKFDCAN_NODE_1, caca);
   
    return Ret_e;
}

/*********************************
 * s_APPLGC_Operational
 *********************************/
static t_eReturnCode s_APPLGC_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sFMKFDCAN_RxItemEvent rxItem_s;
    t_uint8 datapue[8] = {0,1,3,4,5,6,7,2};
    t_sFMKFDCAN_TxItemCfg Txitem_s = {
        .BitRate_e = FMKFDCAN_BITRATE_SWITCH_OFF,
        .frameFormat_e = FMKFDCAN_FRAME_FORMAT_CLASSIC,

        .ItemId_s.Identifier_u32 = 0x123,
        .ItemId_s.FramePurpose_e = FMKFDCAN_FRAME_PURPOSE_DATA,
        .ItemId_s.IdType_e = FMKFDCAN_IDTYPE_STANDARD,

        .CanMsg_s.Direction_e = FMKFDCAN_NODE_DIRECTION_TX,
        .CanMsg_s.Dlc_e = FMKFDCAN_DLC_8,
        .CanMsg_s.data_pu8 = datapue

    };
    Ret_e = FMKFDCAN_SendTxItem(FMKFDCAN_NODE_1, Txitem_s);
    Ret_e = FMKFDCAN_GetRxItem(FMKFDCAN_NODE_1, &rxItem_s);
    if(Ret_e == RC_OK)
    {
        rxItem_s.timeStamp_32 = 45;
    }
    return RC_OK;
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

