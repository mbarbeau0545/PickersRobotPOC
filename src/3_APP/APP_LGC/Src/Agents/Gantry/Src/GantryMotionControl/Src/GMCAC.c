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
#include "APP_LGC/Src/Agents/Gantry/Src/Gantry.h"
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
    GMCMAC_FSM_MVMT, 
    GMCMAC_FSM_GET_MVMT,
    GMCMAC_FSM_SAFETY,
} t_eGMCAC_FSMMvmt;
/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
typedef struct 
{
    t_sint32  Pulse_s32;
    t_uint32  Speed_u32;
} t_sGMCAC_MvmtInfo;

typedef struct 
{
    t_bool setAxeXMvmt_b;
    t_bool setAxeYMvmt_b;
    t_bool setAxeZMvmt_b;
} t_sGMCAC_AxeMvmtInfo;
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

static t_sGMCAC_MvmtInfo g_axeXMvmtInfo_s;
static t_sGMCAC_MvmtInfo g_axeYMvmtInfo_s;
static t_sGMCAC_MvmtInfo g_axeZMvmtInfo_s;
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
static t_eReturnCode s_GMCAC_SetAxesMvmt(t_sGMCAC_AxeMvmtInfo  f_axeMvmtInfo_s);
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
static t_eReturnCode s_GMCAC_GetInfoMvmt(t_sGMCAC_AxeMvmtInfo * f_axeMvmtInfo_ps);
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
static void s_GMCAC_ResetAxesValues(t_sGMCAC_AxeMvmtInfo * f_axeMvmtInfo_ps);

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
                            t_sAPPLGC_ServiceInfo *f_SrvInfo_pas)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_sGMCAC_AxeMvmtInfo s_axeMvmtInfo_s;

    //----- Initialize Pointor to data -----//
    g_snsValues_paf32 = (t_float32 *)f_snsValues_paf32;
    g_SrvInfo_pas = (t_sAPPLGC_ServiceInfo *)f_SrvInfo_pas;

    switch (g_FSMMvmt_e)
    {
        case GMCMAC_FSM_MVMT:
        {
            Ret_e = s_GMCAC_SetAxesMvmt(s_axeMvmtInfo_s);

            if(Ret_e == RC_OK)
            {
                s_GMCAC_ResetAxesValues(&s_axeMvmtInfo_s);
                Ret_e = Gantry_InformAppMissionState(GTRY_MISSION_READY);
            }
            break;
        }
        case GMCMAC_FSM_GET_MVMT:
        {
            Ret_e = s_GMCAC_GetInfoMvmt(&s_axeMvmtInfo_s);

            if((Ret_e == RC_OK)
            && (   (s_axeMvmtInfo_s.setAxeXMvmt_b == (t_bool)True)
                || (s_axeMvmtInfo_s.setAxeYMvmt_b == (t_bool)True)
                || (s_axeMvmtInfo_s.setAxeZMvmt_b == (t_bool)True)))
            {
                g_FSMMvmt_e = GMCMAC_FSM_MVMT;
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
static t_eReturnCode s_GMCAC_SetAxesMvmt(t_sGMCAC_AxeMvmtInfo f_axeMvmtInfo_s)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uAPPACT_SetValue * actgtrXL_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_X].actVal_pau[APPLGC_ACT_MTR_X_L]);
    t_uAPPACT_SetValue * actgtrXR_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_X].actVal_pau[APPLGC_ACT_MTR_X_R]);
    t_uAPPACT_SetValue * actgtrY_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].actVal_pau[APPLGC_ACT_MTR_Y]);
    t_uAPPACT_SetValue * actgtrZ_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].actVal_pau[APPLGC_ACT_MTR_Z]);

    //----- Copy Data -----//
    if(f_axeMvmtInfo_s.setAxeXMvmt_b == (t_bool)True)
    {
        if(g_SrvInfo_pas[APPLGC_SRV_GTRY_X].health_e == APPLGC_SRV_HEALTH_OK)
        {
            actgtrXL_u->Motor_s.frequency_u32 = (t_uint32)g_axeXMvmtInfo_s.Speed_u32;
            actgtrXL_u->Motor_s.nbPulses_s32  = (t_sint32)g_axeXMvmtInfo_s.Pulse_s32;

            actgtrXR_u->Motor_s.frequency_u32 = (t_uint32)g_axeXMvmtInfo_s.Speed_u32;
            actgtrXR_u->Motor_s.nbPulses_s32  = (t_sint32)g_axeXMvmtInfo_s.Pulse_s32;
        }
        else 
        {
            actgtrXL_u->Motor_s.nbPulses_s32 = (t_sint32)0;
            actgtrXR_u->Motor_s.nbPulses_s32 = (t_sint32)0;

            actgtrXL_u->Motor_s.stopPulse_b = (t_bool)True;
            actgtrXR_u->Motor_s.stopPulse_b = (t_bool)True;

            actgtrXL_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
            actgtrXR_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
        }
    }
    if(f_axeMvmtInfo_s.setAxeYMvmt_b == (t_bool)True)
    {   
        if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].health_e == APPLGC_SRV_HEALTH_OK)
        {
            actgtrY_u->Motor_s.frequency_u32 = (t_uint32)g_axeYMvmtInfo_s.Speed_u32;
            actgtrY_u->Motor_s.nbPulses_s32  = (t_sint32)g_axeYMvmtInfo_s.Pulse_s32;    
        }
        else 
        {
            actgtrY_u->Motor_s.nbPulses_s32 = (t_sint32)0;
            actgtrY_u->Motor_s.stopPulse_b = (t_bool)True;
            actgtrY_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
        }
    }
    if(f_axeMvmtInfo_s.setAxeZMvmt_b == (t_bool)True)
    {
        if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].health_e == APPLGC_SRV_HEALTH_OK)
        {
            actgtrZ_u->Motor_s.frequency_u32 = (t_uint32)g_axeZMvmtInfo_s.Speed_u32;
            actgtrZ_u->Motor_s.nbPulses_s32  = (t_sint32)g_axeZMvmtInfo_s.Pulse_s32;
        }
        else 
        {
            actgtrZ_u->Motor_s.nbPulses_s32 = (t_sint32)0;
            actgtrZ_u->Motor_s.stopPulse_b = (t_bool)True;
            actgtrZ_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
        }  
    }
    return Ret_e;
}
/*********************************
 * s_GMCAC_GetInfoMvmt
 *********************************/
static t_eReturnCode s_GMCAC_GetInfoMvmt(t_sGMCAC_AxeMvmtInfo * f_axeMvmtInfo_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uAPPLGC_CmdValues appAxeX_u;
    t_uAPPLGC_CmdValues appAxeY_u;
    t_uAPPLGC_CmdValues appAxeZ_u;
    
    Ret_e = APPLGC_GetAppCmd(APPLGC_RCV_CMD_ID_GTRY_X, &appAxeX_u);
    if(Ret_e == RC_OK)
    {
        f_axeMvmtInfo_ps->setAxeXMvmt_b = (t_bool)True;
        g_axeXMvmtInfo_s.Pulse_s32 = (t_sint32)appAxeX_u.axe_s.pulse_s32;
        g_axeYMvmtInfo_s.Speed_u32 = (t_uint32)appAxeX_u.axe_s.speed_u16;
    }

    Ret_e = APPLGC_GetAppCmd(APPLGC_RCV_CMD_ID_GTRY_Y, &appAxeY_u);
    if(Ret_e == RC_OK)
    {
        f_axeMvmtInfo_ps->setAxeYMvmt_b = (t_bool)True;
        g_axeYMvmtInfo_s.Pulse_s32 = (t_sint32)appAxeY_u.axe_s.pulse_s32;
        g_axeYMvmtInfo_s.Speed_u32 = (t_uint32)appAxeY_u.axe_s.speed_u16;
    }

    Ret_e = APPLGC_GetAppCmd(APPLGC_RCV_CMD_ID_GTRY_Z, &appAxeZ_u);
    if(Ret_e == RC_OK)
    {
        f_axeMvmtInfo_ps->setAxeZMvmt_b = (t_bool)True;
        g_axeZMvmtInfo_s.Pulse_s32 = (t_sint32)appAxeZ_u.axe_s.pulse_s32;
        g_axeZMvmtInfo_s.Speed_u32 = (t_uint32)appAxeZ_u.axe_s.speed_u16;
    }

    return Ret_e;
}

/*********************************
 * s_GMCAC_ResetAxesValues
 *********************************/
static void s_GMCAC_ResetAxesValues(t_sGMCAC_AxeMvmtInfo * f_axeMvmtInfo_ps)
{
     
    g_axeXMvmtInfo_s.Pulse_s32 = (t_sint32)0;
    g_axeXMvmtInfo_s.Speed_u32 = (t_uint32)0;

    g_axeYMvmtInfo_s.Pulse_s32 = (t_sint32)0;
    g_axeYMvmtInfo_s.Speed_u32 = (t_uint32)0;

    g_axeZMvmtInfo_s.Pulse_s32 = (t_sint32)0;
    g_axeZMvmtInfo_s.Speed_u32 = (t_uint32)0;

    f_axeMvmtInfo_ps->setAxeXMvmt_b = (t_bool)False;
    f_axeMvmtInfo_ps->setAxeYMvmt_b = (t_bool)False;
    f_axeMvmtInfo_ps->setAxeZMvmt_b = (t_bool)False;

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

