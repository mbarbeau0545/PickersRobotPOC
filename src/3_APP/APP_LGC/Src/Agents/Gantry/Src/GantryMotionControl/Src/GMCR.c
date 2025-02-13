/*********************************************************************
 * @file        GMCR.c
 * @brief       Gantry Motion Control Reference.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************


#include "./GMCR.h"
#include "APP_LGC/Src/APP_LGC.h"
#include "APP_CFG/ConfigFiles/APPSNS_ConfigPublic.h"
#include "APP_CFG/ConfigFiles/GMCR_ConfigPrivate.h"
#include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"
#include "APP_CFG/ConfigFiles/APPACT_ConfigPublic.h"
#include "APP_CFG/ConfigFiles/Gantry_ConfigPublic.h"
#include "APP_LGC/Src/Agents/Gantry/Src/Gantry.h"

// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
typedef enum
{
    
    GMCR_FSM_PRE_REF_AXE_X = 0x00,
    GMCR_FSM_REF_AXE_X,
    GMCR_FSM_PRE_REF_AXE_Y,
    GMCR_FSM_REF_AXE_Y,
    GMCR_FSM_PRE_REF_AXE_Z,
    GMCR_FSM_REF_AXE_Z,

    GMCR_FSM_NB
} t_eGMCR_FSMAxe;

typedef enum 
{
    GMCR_FSM_SEO_SET_MOVE = 0x00,
    GMCR_FSM_SEO_WAIT_CONTACT,
    GMCR_FSM_SEO_GO_REVERSE,
} t_eGMCR_FSMSeo;
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
static t_float32 * g_snsValues_paf32;
static t_sAPPLGC_ServiceInfo * g_SrvInfo_pas;
static t_eGMCR_FSMAxe g_FSMAxeRef_e = GMCR_FSM_REF_AXE_X;
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
static t_eReturnCode s_GMCR_ReferenceAxeX(t_bool * f_SEODone_);
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
static t_eReturnCode s_GMCR_ReferenceAxeY(t_bool * f_SEODone_pb);
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
static t_eReturnCode s_GMCR_ReferenceAxeZ(t_bool * f_SEODone_pb);

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * GMCR_Init
 *********************************/
t_eReturnCode GMCR_Init(void)
{
    return RC_OK;
}

/*********************************
 * GMCR_EnterMode
 *********************************/
t_eReturnCode GMCR_EnterMode(void)
{
    g_FSMAxeRef_e = GMCR_FSM_REF_AXE_X;
    return RC_OK;
}

/*********************************
 * GMCR_ExitMode
 *********************************/
t_eReturnCode GMCR_ExitMode(void)
{
    return RC_OK;
}

/*********************************
 * GMCR_Cyclic
 *********************************/
t_eReturnCode GMCR_Cyclic(  t_float32 *f_snsValues_paf32, 
                            t_sAPPLGC_ServiceInfo *f_SrvInfo_pas)
{
    t_eReturnCode Ret_e = RC_OK;
    t_bool SEODone_b = (t_bool)False;

    //----- Initialize Pointor to data -----//
    g_snsValues_paf32 = (t_float32 *)f_snsValues_paf32;
    g_SrvInfo_pas = (t_sAPPLGC_ServiceInfo *)f_SrvInfo_pas;
    
    switch (g_FSMAxeRef_e)
    {
        case GMCR_FSM_PRE_REF_AXE_X:
        {
            if(g_SrvInfo_pas[APPLGC_SRV_GTRY_X].state_e == APPLGC_SRV_STATE_STOPPED
            && (g_SrvInfo_pas[APPLGC_SRV_GTRY_X].health_e == APPLGC_SRV_HEALTH_OK))
            {
                g_FSMAxeRef_e = GMCR_FSM_REF_AXE_X;
            }
            break;
        }
        case GMCR_FSM_REF_AXE_X:
        {
            
            {
                Ret_e = s_GMCR_ReferenceAxeX(&SEODone_b);

                if((Ret_e == RC_OK)
                && (SEODone_b == (t_bool)True))
                {
                    g_FSMAxeRef_e = GMCR_FSM_REF_AXE_Y;
                }
            }
            break;
        }
        case GMCR_FSM_PRE_REF_AXE_Y:
        {
            if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].state_e == APPLGC_SRV_STATE_STOPPED)
            {
                g_FSMAxeRef_e = GMCR_FSM_REF_AXE_Y;
            }
            break;
        }
        case GMCR_FSM_REF_AXE_Y:
        {
            Ret_e = s_GMCR_ReferenceAxeY(&SEODone_b);

            if((Ret_e == RC_OK)
            && (SEODone_b == (t_bool)True))
            {
                g_FSMAxeRef_e = GMCR_FSM_REF_AXE_Z;
            }
            break;
        }
        case GMCR_FSM_PRE_REF_AXE_Z:
        {
            if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].state_e == APPLGC_SRV_STATE_STOPPED)
            {
                g_FSMAxeRef_e = GMCR_FSM_REF_AXE_Z;
            }
            break;
        }
        case GMCR_FSM_REF_AXE_Z:
        {
            Ret_e = s_GMCR_ReferenceAxeZ(&SEODone_b);

            if((Ret_e == RC_OK)
            && (SEODone_b == (t_bool)True))
            {
                //----- Send Message Application -----//
                Ret_e = Gantry_InformAppMissionState(GTRY_MISSION_SUCCEED);
                
                Ret_e = Gantry_RqstSFMState(GTRY_SFM_GANTRY_PAUSE);
                g_FSMAxeRef_e = GMCR_FSM_REF_AXE_X;
            }
            break;
        }
    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * GMCR_Cyclic
 *********************************/
static t_eReturnCode s_GMCR_ReferenceAxeX(t_bool * f_SEODone_pb)
{
    t_eReturnCode Ret_e = RC_OK; /**< reference Axe X on Going */
    static t_eGMCR_FSMSeo s_SFMSeo_e = GMCR_FSM_SEO_SET_MOVE;
    t_uAPPACT_SetValue * actgtrXR_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_X].actVal_pau[APPLGC_ACT_MTR_X_L]);
    t_uAPPACT_SetValue * actgtrXL_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_X].actVal_pau[APPLGC_ACT_MTR_X_R]);
    *f_SEODone_pb = (t_bool)False;
    
    if(g_SrvInfo_pas[APPLGC_SRV_GTRY_X].health_e == APPLGC_SRV_HEALTH_OK)
    {

        //----- Check Contact -----//
        if((g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_X_L_MAX] == APPSNS_LIM_SWCH_NC_CONTACT)
        || (g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_X_L_MIN] == APPSNS_LIM_SWCH_NC_CONTACT)
        || (g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_X_R_MIN] == APPSNS_LIM_SWCH_NC_CONTACT)
        || (g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_X_R_MAX] == APPSNS_LIM_SWCH_NC_CONTACT))
        {
            actgtrXR_u->Motor_s.stopPulse_b = (t_bool)True;
            actgtrXR_u->Motor_s.nbPulses_s32 = (t_sint32)0;

            actgtrXL_u->Motor_s.stopPulse_b = (t_bool)True;
            actgtrXR_u->Motor_s.nbPulses_s32 = (t_uint32)0;
            s_SFMSeo_e = GMCR_FSM_SEO_GO_REVERSE;
        }
        //----- State Machine -----//
        switch (s_SFMSeo_e)
        {
            case GMCR_FSM_SEO_SET_MOVE:
            {
                actgtrXR_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_PULSE_REFERENCE;
                actgtrXR_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_PULSE_REFERENCE;

                actgtrXL_u->Motor_s.frequency_u32 =  (t_sint32)GMCR_REF_FREQ_NOMINAL; 
                actgtrXL_u->Motor_s.frequency_u32 =  (t_sint32)GMCR_REF_FREQ_NOMINAL;

                s_SFMSeo_e = GMCR_FSM_SEO_WAIT_CONTACT;
                break;
            }
            case GMCR_FSM_SEO_WAIT_CONTACT:
            {
                // just wait
                actgtrXR_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                actgtrXR_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                break;
            }
            case GMCR_FSM_SEO_GO_REVERSE:
            {
                actgtrXR_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_NB_PULSE_REVERSE;
                actgtrXR_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_NB_PULSE_REVERSE;

                s_SFMSeo_e = GMCR_FSM_SEO_SET_MOVE;
                //----- Refereence Axe X done -----//
                *f_SEODone_pb = (t_bool)True;
            }
        }
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

    return Ret_e;
}

/*********************************
 * s_GMCR_ReferenceAxeY
 *********************************/
static t_eReturnCode s_GMCR_ReferenceAxeY(t_bool * f_SEODone_pb)
{
    t_eReturnCode Ret_e = RC_OK; /**< reference Axe Y on Going */
    static t_eGMCR_FSMSeo s_SFMSeo_e = GMCR_FSM_SEO_SET_MOVE;
    t_uAPPACT_SetValue * actgtrY_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].actVal_pau[APPLGC_ACT_MTR_Y]);
    *f_SEODone_pb = (t_bool)False; 

    if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].health_e == APPLGC_SRV_HEALTH_OK)
    {
        //----- Check Contact -----//
        if((g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_Y_MAX] == APPSNS_LIM_SWCH_NC_CONTACT)
        || (g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_Y_MIN] == APPSNS_LIM_SWCH_NC_CONTACT))
        {
            actgtrY_u->Motor_s.stopPulse_b = (t_bool)True;
            actgtrY_u->Motor_s.nbPulses_s32 = (t_sint32)0;
            s_SFMSeo_e = GMCR_FSM_SEO_GO_REVERSE;
        }

        switch (s_SFMSeo_e)
        {
            case GMCR_FSM_SEO_SET_MOVE:
            {
                actgtrY_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_PULSE_REFERENCE;
                actgtrY_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_PULSE_REFERENCE;

                actgtrY_u->Motor_s.frequency_u32 =  (t_sint32)GMCR_REF_FREQ_NOMINAL; 
                actgtrY_u->Motor_s.frequency_u32 =  (t_sint32)GMCR_REF_FREQ_NOMINAL;

                s_SFMSeo_e = GMCR_FSM_SEO_WAIT_CONTACT;      
                break;
            }
            case GMCR_FSM_SEO_WAIT_CONTACT:
            {
                // just wait
                actgtrY_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                actgtrY_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                break;
            }
            case GMCR_FSM_SEO_GO_REVERSE:
            {
                actgtrY_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_NB_PULSE_REVERSE;
                actgtrY_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_NB_PULSE_REVERSE;

                s_SFMSeo_e = GMCR_FSM_SEO_SET_MOVE;
                //----- Refereence Axe Y done -----//
                *f_SEODone_pb = (t_bool)True; 
            }
        }
    }
    else 
    {
        actgtrY_u->Motor_s.nbPulses_s32 = (t_sint32)0;
        actgtrY_u->Motor_s.stopPulse_b = (t_bool)True;
        actgtrY_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
    }

    return Ret_e;
}
 /*********************************
 * s_GMCR_ReferenceAxeZ
 *********************************/
static t_eReturnCode s_GMCR_ReferenceAxeZ(t_bool * f_SEODone_pb)
{
    t_eReturnCode Ret_e = RC_OK; /**< reference Axe Y on Going */
    static t_eGMCR_FSMSeo s_SFMSeo_e = GMCR_FSM_SEO_SET_MOVE;
    t_uAPPACT_SetValue * actgtrZ_u = (t_uAPPACT_SetValue *)(&g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].actVal_pau[APPLGC_ACT_MTR_Z]);
    *f_SEODone_pb = (t_bool)False;

    if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].health_e == APPLGC_SRV_HEALTH_OK)
    {
        //----- Check Contact -----//
        if((g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_Z_MAX] == APPSNS_LIM_SWCH_NC_CONTACT)
        || (g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_Z_MIN] == APPSNS_LIM_SWCH_NC_CONTACT))
        {
            actgtrZ_u->Motor_s.stopPulse_b = (t_bool)True;
            actgtrZ_u->Motor_s.nbPulses_s32 = (t_sint32)0;
            s_SFMSeo_e = GMCR_FSM_SEO_GO_REVERSE;

        }

        switch (s_SFMSeo_e)
        {
            case GMCR_FSM_SEO_SET_MOVE:
            {
                actgtrZ_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_PULSE_REFERENCE;
                actgtrZ_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_PULSE_REFERENCE;

                actgtrZ_u->Motor_s.frequency_u32 =  (t_sint32)GMCR_REF_FREQ_NOMINAL; 
                actgtrZ_u->Motor_s.frequency_u32 =  (t_sint32)GMCR_REF_FREQ_NOMINAL;

                s_SFMSeo_e = GMCR_FSM_SEO_WAIT_CONTACT;
                break;
            }
            case GMCR_FSM_SEO_WAIT_CONTACT:
            {
                // just wait
                actgtrZ_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                actgtrZ_u->Motor_s.nbPulses_s32 = (t_sint32)0;
                break;
            }
            case GMCR_FSM_SEO_GO_REVERSE:
            {
                actgtrZ_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_NB_PULSE_REVERSE;
                actgtrZ_u->Motor_s.nbPulses_s32 = (t_sint32)GMCR_NB_PULSE_REVERSE;

                s_SFMSeo_e = GMCR_FSM_SEO_SET_MOVE;
                //----- Refereence Axe Y done -----//
                *f_SEODone_pb = (t_bool)True;
            }
        }
    }
    else 
    {
        actgtrZ_u->Motor_s.nbPulses_s32 = (t_sint32)0;
        actgtrZ_u->Motor_s.stopPulse_b = (t_bool)True;
        actgtrZ_u->Motor_s.state_e = CL42T_MOTOR_STATE_OFF;
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

