/*********************************************************************
 * @file        GMCAC.h
 * @brief       Gantry Motion Control Application Control.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************


#include "./GMCAC.h"
#include "APP_CFG/ConfigFiles/APPACT_ConfigPublic.h"
#include "APP_CFG/ConfigFiles/APPLGC_ConfigPublic.h"
#include "Motor/CL42T/Src/CL42T.h"
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
    GMCMAC_FSM_PRE_MVMT = 0x00,
    GMCMAC_FSM_MVMT, 
    GMCMAC_FSM_GET_MVMT,
    GMCMAC_FSM_SAFETY,
} t_eGMCAC_FSMMvmt;
/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
typedef struct 
{
    t_uint16  Pulse_u16;
    t_uint8   Dir_u8;
    t_uint32  Speed_u32;
} t_sGMCAC_MvmtInfo;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
t_eGMCAC_FSMMvmt g_FSMMvmt_e = GMCMAC_FSM_GET_MVMT;

static t_float32 * g_snsValues_paf32;
static t_sAPPLGC_ServiceInfo * g_SrvInfo_pas;
static t_sAPPLGC_ActInfo * g_actInfo_pas;

static t_sGMCAC_MvmtInfo AxeXMvmtInfo_s;
static t_sGMCAC_MvmtInfo AxeYMvmtInfo_s;
static t_sGMCAC_MvmtInfo AxeZMvmtInfo_s;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
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
static t_eReturnCode s_GMCAC_SetAxesMvmt(void);
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
static t_eReturnCode s_GMCAC_GetInfoMvmt(t_bool * f_setMvmt_pb);
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
static void s_GMCAC_ResetAxesValues(void);

//****************************************************************************
//                      Public functions - Implementation
//****************************************************************************
/*********************************
 * GMCAC_Init
 *********************************/
t_eReturnCode GMCAC_Init(void)
{

}

/*********************************
 * GMCAC_EnterMode
 *********************************/
t_eReturnCode GMCAC_EnterMode(void)
{

}

/*********************************
 * GMCAC_ExitMode
 *********************************/
t_eReturnCode GMCAC_ExitMode(void)
{

}

/*********************************
 * GMCAC_Cyclic
 *********************************/
t_eReturnCode GMCAC_Cyclic( t_float32 *f_snsValues_paf32, 
                            t_sAPPLGC_ServiceInfo *f_SrvInfo_pas,
                            t_sAPPLGC_ActInfo * f_actInfo_pas)
{
    t_eReturnCode Ret_e = RC_OK;
    t_bool setMvmt_b = (t_bool)False;

    //----- Initialize Pointor to data -----//
    g_snsValues_paf32 = (t_float32 *)f_snsValues_paf32;
    g_SrvInfo_pas = (t_sAPPLGC_ServiceInfo *)f_SrvInfo_pas;
    g_actInfo_pas = (t_sAPPLGC_ActInfo *)f_actInfo_pas;

    switch (g_FSMMvmt_e)
    {
        case GMCMAC_FSM_PRE_MVMT:
        {
            break;
        }
        case GMCMAC_FSM_MVMT:
        {
            Ret_e = s_GMCAC_SetAxesMvmt();

            if(Ret_e == RC_OK)
            {
                s_GMCAC_ResetAxesValues();
            }
            break;
        }
        case GMCMAC_FSM_GET_MVMT:
        {
            Ret_e = s_GMCAC_GetInfoMvmt(&setMvmt_b);

            if((Ret_e == RC_OK)
            && (setMvmt_b == (t_bool)True))
            {
                g_FSMMvmt_e = GMCMAC_FSM_PRE_MVMT;
            }
            break;
        }
        case GMCMAC_FSM_SAFETY:
        default:
        {
            Ret_e = RC_OK;
        }
    }
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_GMCAC_SetAxesMvmt
 *********************************/
static t_eReturnCode s_GMCAC_SetAxesMvmt(void)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- check validity -----//
    if((AxeXMvmtInfo_s.Dir_u8 >= CL42T_MOTOR_DIRECTION_NB)
    || (AxeYMvmtInfo_s.Dir_u8 >= CL42T_MOTOR_DIRECTION_NB)
    || (AxeZMvmtInfo_s.Dir_u8 >= CL42T_MOTOR_DIRECTION_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //----- Copy Data -----//
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_L_DIR].setValue_f32     = (t_float32)AxeXMvmtInfo_s.Dir_u8;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_R_DIR].setValue_f32     = (t_float32)AxeXMvmtInfo_s.Dir_u8;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_L_PULSE].setValue_f32   = (t_float32)AxeXMvmtInfo_s.Pulse_u16;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_R_PULSE].setValue_f32   = (t_float32)AxeXMvmtInfo_s.Pulse_u16;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_L_SPEED].setValue_f32   = (t_float32)AxeXMvmtInfo_s.Speed_u32;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_R_SPEED].setValue_f32   = (t_float32)AxeXMvmtInfo_s.Speed_u32;

        g_actInfo_pas[APPACT_ACTUATOR_MTR_Y_DIR].setValue_f32       = (t_float32)AxeYMvmtInfo_s.Dir_u8;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Y_PULSE].setValue_f32     = (t_float32)AxeYMvmtInfo_s.Pulse_u16;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Y_SPEED].setValue_f32     = (t_float32)AxeYMvmtInfo_s.Speed_u32;

        g_actInfo_pas[APPACT_ACTUATOR_MTR_Z_DIR].setValue_f32       = (t_float32)AxeZMvmtInfo_s.Dir_u8;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Z_PULSE].setValue_f32     = (t_float32)AxeZMvmtInfo_s.Pulse_u16;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Z_SPEED].setValue_f32     = (t_float32)AxeZMvmtInfo_s.Speed_u32;
    }

    return Ret_e;
}
/*********************************
 * s_GMCAC_GetInfoMvmt
 *********************************/
static t_eReturnCode s_GMCAC_GetInfoMvmt(t_bool * f_setMvmt_pb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uAPPLGC_CmdValues appDirCmdValues_u;
    t_uAPPLGC_CmdValues appSpeedCmdValues_u;
    t_uAPPLGC_CmdValues appPulseCmdValues_u;
    
    Ret_e = APPLGC_GetAppCmd(APPLGC_RCV_CMD_ID_DATA_PULSE_XYZ, &appPulseCmdValues_u);    

    if(Ret_e == RC_OK)
    {
        Ret_e = APPLGC_GetAppCmd(APPLGC_RCV_CMD_ID_DATA_SPEED_XYZ, &appSpeedCmdValues_u);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPLGC_GetAppCmd(APPLGC_RCV_CMD_ID_DATA_DIR_XYZ, &appDirCmdValues_u);
    }
    if(Ret_e == RC_OK)
    {
        //----- if here, it means app ask new pulse ----// 
        //----- copy data -----//
        AxeXMvmtInfo_s.Dir_u8 = (t_uint8)appDirCmdValues_u.dirInfo_s.axeX_u16;
        AxeYMvmtInfo_s.Dir_u8 = (t_uint8)appDirCmdValues_u.dirInfo_s.axeY_u16;
        AxeZMvmtInfo_s.Dir_u8 = (t_uint8)appDirCmdValues_u.dirInfo_s.axeZ_u16;

        AxeXMvmtInfo_s.Speed_u32 = (t_uint32)appSpeedCmdValues_u.speedInfo_s.axeX_u16;
        AxeYMvmtInfo_s.Speed_u32 = (t_uint32)appSpeedCmdValues_u.speedInfo_s.axeY_u16;
        AxeZMvmtInfo_s.Speed_u32 = (t_uint32)appSpeedCmdValues_u.speedInfo_s.axeZ_u16;

        AxeYMvmtInfo_s.Pulse_u16 = appSpeedCmdValues_u.pulseInfo_s.axeX_u16;
        AxeXMvmtInfo_s.Pulse_u16 = appSpeedCmdValues_u.pulseInfo_s.axeY_u16;
        AxeZMvmtInfo_s.Pulse_u16 = appSpeedCmdValues_u.pulseInfo_s.axeZ_u16;

        //----- Set Mvmt ON -----//
        *f_setMvmt_pb = (t_bool)True; 
    }

    return Ret_e;
}

/*********************************
 * s_GMCAC_ResetAxesValues
 *********************************/
static void s_GMCAC_ResetAxesValues(void)
{
     
    AxeXMvmtInfo_s.Dir_u8     = (t_uint8)0;
    AxeXMvmtInfo_s.Pulse_u16  = (t_uint16)0;
    AxeXMvmtInfo_s.Speed_u32  = (t_uint32)0;

    AxeYMvmtInfo_s.Dir_u8     = (t_uint8)0; 
    AxeYMvmtInfo_s.Pulse_u16  = (t_uint16)0;  
    AxeYMvmtInfo_s.Speed_u32  = (t_uint32)0; 

    AxeZMvmtInfo_s.Dir_u8     = (t_uint8)0; 
    AxeZMvmtInfo_s.Pulse_u16  = (t_uint16)0; 
    AxeZMvmtInfo_s.Speed_u32  = (t_uint32)0; 

    return;
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

