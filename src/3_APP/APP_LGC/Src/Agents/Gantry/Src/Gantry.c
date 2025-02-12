/*********************************************************************
 * @file        Gantry.c
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

#include "./Gantry.h"
#include "APP_CFG/ConfigFiles/Gantry_ConfigPrivate.h"
#include "APP_LGC/Src/APP_LGC.h"
#include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"
#include "APP_CFG/ConfigFiles/APPSNS_ConfigPublic.h"
#include "APP_CTRL/APP_SDM/Src/APP_SDM.h"
#include "APP_CTRL/APP_ACT/Src/APP_ACT.h"
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
static t_eGTRY_FSMProduction g_FSM_ProdMode_e = GTRY_FSM_PROD_SEO;
static t_eGTRY_FSMProduction g_FSM_RsqtProdMode_e = GTRY_FSM_PROD_SEO;
static t_eGTRY_FSMGantry g_FSM_GtryMode_e = GTRY_SFM_GANTRY_PAUSE;
static t_eGTRY_FSMGantry g_FSM_RqstGtryMode_e = GTRY_SFM_GANTRY_PAUSE;

static t_float32 * g_snsValues_paf32;
static t_sAPPLGC_ServiceInfo * g_SrvInfo_pas;
static t_sAPPLGC_ActInfo * g_actInfo_pas;
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
static t_eReturnCode s_GTRY_StateMachineMngmt(void);
/**
*
*	@brief      Check Limit switch Status, and check movement of the Gantry.\n
*	@note   
*
*
*	@param[in] 
*	@param[out]
*	 
*
*
*/
static t_eReturnCode s_GTRY_SafetyMngmt(void);
/**
*
*	@brief      Check Limit switch Status, and check movement of the Gantry.\n
*	@note   
*
*
*	@param[in] 
*	@param[out]
*	 
*
*
*/
static void s_GTR_SetGantryOff(void);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * Gantry_Init
 *********************************/
t_eReturnCode Gantry_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    return Ret_e;
}

/*********************************
 * APPLGC_Init
 *********************************/
t_eReturnCode Gantry_Cyclic(t_float32 *f_snsValues_paf32, 
                            t_sAPPLGC_ServiceInfo *f_SrvInfo_pas,
                            t_sAPPLGC_ActInfo * f_actInfo_pas)
{
    t_eReturnCode Ret_e = RC_OK;
    

    //----- Initialize Pointor to data -----//
    g_snsValues_paf32 = (t_float32 *)f_snsValues_paf32;
    g_SrvInfo_pas = (t_sAPPLGC_ServiceInfo *)f_SrvInfo_pas;
    g_actInfo_pas = (t_sAPPLGC_ActInfo *)f_actInfo_pas;

    //----- Check Gantry Mvmt Security and Update State-----//
    Ret_e = s_GTRY_SafetyMngmt();

    //----- Get New Mode from Application -----//
    Ret_e = s_GTRY_StateMachineMngmt();


    if(Ret_e == RC_OK)
    {
        switch (g_FSM_GtryMode_e)
        {
            case GTRY_SFM_GANTRY_PRE_PRODUCTION:
            {
                Ret_e = c_Gtry_SFMProdFunc_as[g_FSM_ProdMode_e].Enter_pcb();

                if(Ret_e == RC_OK)
                {
                    g_FSM_GtryMode_e = GTRY_SFM_GANTRY_PRODUCTION;
                }
                break;
            }
            case GTRY_SFM_GANTRY_PRODUCTION:
            {
                if(g_FSM_RsqtProdMode_e != g_FSM_ProdMode_e)
                {
                    Ret_e = c_Gtry_SFMProdFunc_as[g_FSM_ProdMode_e].Exit_pcb();

                    if(Ret_e == RC_OK)
                    {
                        Ret_e = c_Gtry_SFMProdFunc_as[g_FSM_RsqtProdMode_e].Enter_pcb();

                        if(Ret_e == RC_OK)
                        {
                            g_FSM_ProdMode_e = g_FSM_RsqtProdMode_e;
                        }
                    }
                }
                if(Ret_e == RC_OK)
                {
                    Ret_e = c_Gtry_SFMProdFunc_as[g_FSM_ProdMode_e].Cyclic_pcb( g_snsValues_paf32,
                                                                                g_SrvInfo_pas,
                                                                                g_actInfo_pas);
                }
                
                if(Ret_e != RC_OK)
                {
                    g_FSM_GtryMode_e = GTRY_SFM_GANTRY_DEFAULT;
                }
                break;
            }
            case GTRY_SFM_GANTRY_PAUSE:
            {
                s_GTR_SetGantryOff();
                break;
            }
            case GTRY_SFM_GANTRY_DEFAULT:
            {
                break;
            }
            case GTRY_SFM_GANTRY_NB:
            default:
            {
                break;
            }
        }
    }
    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_GTRY_StateMachineMngmt
 *********************************/
static t_eReturnCode s_GTRY_StateMachineMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eGTRY_FSMGantry FSMGtryRqstMode_e;
    t_uint8 FSMRqstProdMode_u8;
    t_uAPPLGC_CmdValues appCmd_u;

    Ret_e = APPLGC_GetAppCmd(APPLGC_RCV_CMD_ID_DATA_MODE, &appCmd_u);

    //----- if Ret_e = WARNING_NO_OPE it means not new mode 
    //      has been set by application else new mode -----//
    if(Ret_e == RC_OK)
    {
        g_FSM_RqstGtryMode_e = appCmd_u.SFMModeInfo_s.mainMode_u8;
        g_FSM_RsqtProdMode_e = appCmd_u.SFMModeInfo_s.prodMode_u8;
    }

    if(Ret_e == RC_OK)
    {
        if(g_FSM_RqstGtryMode_e != g_FSM_GtryMode_e)
        {
            if(g_FSM_GtryMode_e == GTRY_SFM_GANTRY_PRODUCTION)
            {
                Ret_e = c_Gtry_SFMProdFunc_as[g_FSM_ProdMode_e].Exit_pcb();
            }

            g_FSM_GtryMode_e = g_FSM_RsqtProdMode_e;
        }
    }
    if(Ret_e == RC_WARNING_NO_OPERATION)
    {
        Ret_e = RC_OK;
    }
    
    return Ret_e;
}

/*********************************
 * s_GTRY_SafetyMngmt
 *********************************/
static t_eReturnCode s_GTRY_SafetyMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxLimSw_u8;
    t_uint8 idxSnsLimSw_u8 = 0;
    t_bool reportDiag_b = False;

    //----- check limit switch -----//
    //----- In GMCR (Referencment) let this mode deal with
    //      limit switch -----//
    if(g_FSM_ProdMode_e != GTRY_FSM_PROD_SEO)
    {
        for(idxLimSw_u8 == (t_uint8)0 ; idxLimSw_u8 < GTRY_SNS_LIMSWITCH_NB ; idxLimSw_u8++)
        {
            idxSnsLimSw_u8 = c_Gtry_LimSwitchIdx_ae[idxLimSw_u8];
            if(g_snsValues_paf32[idxSnsLimSw_u8] == APPSNS_LIM_SWCH_NC_CONTACT)
            {
                //---- Problem, call APPSDM -----//
                Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_GANTRY_SWITCH_LIMIT,
                                                APPSDM_DIAG_ITEM_REPORT_FAIL,
                                                (t_uint16)idxSnsLimSw_u8,
                                                (t_uint16)0);

                g_FSM_GtryMode_e = GTRY_SFM_GANTRY_DEFAULT;
                reportDiag_b = (t_bool)True;
                break;
            }
        }   
    }
    if(reportDiag_b == False)
    {
        Ret_e = APPSDM_ReportDiagEvnt(  APPSDM_DIAG_ITEM_GANTRY_SWITCH_LIMIT,
                                        APPSDM_DIAG_ITEM_REPORT_PASS,
                                        (t_uint16)idxSnsLimSw_u8,
                                        (t_uint16)0);
    }

    return Ret_e ;
}

/*********************************
 * s_GTR_SetGantryOff
 *********************************/
static void s_GTR_SetGantryOff(void)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- set All Pulses to Off -----//
    g_actInfo_pas[APPACT_ACTUATOR_MTR_Y_PULSE].setValue_f32 = (t_float32)0.0;
    g_actInfo_pas[APPACT_ACTUATOR_MTR_Z_PULSE].setValue_f32 = (t_float32)0.0;
    g_actInfo_pas[APPACT_ACTUATOR_MTR_X_L_PULSE].setValue_f32 = (t_float32)0.0;
    g_actInfo_pas[APPACT_ACTUATOR_MTR_X_R_PULSE].setValue_f32 = (t_float32)0.0;

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

