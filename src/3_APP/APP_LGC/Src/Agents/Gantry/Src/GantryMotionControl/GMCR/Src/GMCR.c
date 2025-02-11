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


#include "./GMCR.h"
#include "APP_LGC/Src/APP_LGC.h"
#include "APP_CFG/ConfigFiles/APPSNS_ConfigPublic.h"
#include "APP_CFG/ConfigFiles/GMCR_ConfigPrivate.h"

// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
typedef enum
{
    GMCR_FSM_REF_AXE_X = 0x00,
    GMCR_FSM_REF_AXE_Y,
    GMCR_FSM_REF_AXE_Z,

    GMCR_FSM_NB
} t_eGMCR_FSMReference;


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
static t_eGMCR_FSMReference g_FSMReference_e = GMCR_FSM_REF_AXE_X;
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
static t_eReturnCode s_GMCR_ReferenceAxeX(void);
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
static t_eReturnCode s_GMCR_ReferenceAxeY(void);
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
static t_eReturnCode s_GMCR_ReferenceAxeZ(void);

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * GMCR_Init
 *********************************/
t_eReturnCode GMCR_Init(void)
{

}

/*********************************
 * GMCR_EnterMode
 *********************************/
t_eReturnCode GMCR_EnterMode(void)
{

}

/*********************************
 * GMCR_ExitMode
 *********************************/
t_eReturnCode GMCR_ExitMode(void)
{

}

/*********************************
 * GMCR_Cyclic
 *********************************/
t_eReturnCode GMCR_Cyclic(t_float32 * f_snsValues_paf32, t_sAPPLGC_ServiceInfo *f_SrvInfo_pas)
{
    t_eReturnCode Ret_e = RC_OK;
    //----- Initialize Pointor to data -----//
    g_snsValues_paf32 = (t_float32 *)f_snsValues_paf32;
    g_SrvInfo_pas = (t_sAPPLGC_ServiceInfo *)f_SrvInfo_pas;

    switch (g_FSMReference_e)
    {
        case GMCR_FSM_REF_AXE_X:
        {
            if(g_SrvInfo_pas[APPLGC_SRV_GTRY_X].state_e != APPLGC_SRV_STATE_STOPPED)
            {
                Ret_e = RC_WARNING_BUSY;
            }
            if((g_SrvInfo_pas[APPLGC_SRV_GTRY_X].health_e == APPLGC_SRV_HEALTH_OK)
            && (Ret_e == RC_OK))
            {
                Ret_e = s_GMCR_ReferenceAxeX();

                if(Ret_e == RC_OK)
                {
                    g_FSMReference_e = GMCR_FSM_REF_AXE_Y;
                }
            }
            break;
        }
        case GMCR_FSM_REF_AXE_Y:
        {
            if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].state_e != APPLGC_SRV_STATE_STOPPED)
            {
                Ret_e = RC_WARNING_BUSY;
            }
            if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].health_e == APPLGC_SRV_HEALTH_OK)
            {
                Ret_e = s_GMCR_ReferenceAxeY();

                if(Ret_e == RC_OK)
                {
                    g_FSMReference_e = GMCR_FSM_REF_AXE_Z;
                }
            }
            break;
        }
        case GMCR_FSM_REF_AXE_Z:
        {
            if((g_SrvInfo_pas[APPLGC_SRV_GTRY_Z].state_e != APPLGC_SRV_STATE_STOPPED)
            && (Ret_e == RC_OK))
            {
                Ret_e = RC_WARNING_BUSY;
            }
            if((g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].health_e == APPLGC_SRV_HEALTH_OK)
            && (Ret_e == RC_OK))
            {
                Ret_e = s_GMCR_ReferenceAxeZ();

                if(Ret_e == RC_OK)
                {
                    g_FSMReference_e = GMCR_FSM_REF_AXE_X;
                }
            }
            break;
        }
    }

}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * GMCR_Cyclic
 *********************************/
static t_eReturnCode s_GMCR_ReferenceAxeX(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_bool s_setMvmt_b = False;
    t_float32 * actValGtryX_paf32 = (t_float32 *)(g_SrvInfo_pas[APPLGC_SRV_GTRY_X].actValues_paf32);

    //----- Check Contact -----//
    if((g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_X_L_MAX] == APPSNS_LIM_SWCH_NC_CONTACT)
    || (g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_X_L_MIN] == APPSNS_LIM_SWCH_NC_CONTACT))
    {
        actValGtryX_paf32[APPLGC_SRV_GTRY_X_ACT_MTR_X_L_PULSE] = (t_float32)0.0;
        actValGtryX_paf32[APPLGC_SRV_GTRY_X_ACT_MTR_X_R_PULSE] = (t_float32)0.0;
        Ret_e == RC_OK;
    }

    //----- Set Actuators for reference -----//
    if(s_setMvmt_b == (t_bool)False);
    {
        actValGtryX_paf32[APPLGC_SRV_GTRY_X_ACT_MTR_X_L_PULSE] = (t_float32)GMCR_PULSE_REFERENCE;
        actValGtryX_paf32[APPLGC_SRV_GTRY_X_ACT_MTR_X_R_PULSE] = (t_float32)GMCR_PULSE_REFERENCE;
        actValGtryX_paf32[APPLGC_SRV_GTRY_X_ACT_MTR_X_L_SEED] =  (t_float32)GMCR_REF_FREQ_NOMINAL; 
        actValGtryX_paf32[APPLGC_SRV_GTRY_X_ACT_MTR_X_L_SEED] =  (t_float32)GMCR_REF_FREQ_NOMINAL; 
        actValGtryX_paf32[APPLGC_SRV_GTRY_X_ACT_MTR_X_L_DIR] =  (t_float32)GMCR_DIR_REFERENCE; 
        actValGtryX_paf32[APPLGC_SRV_GTRY_X_ACT_MTR_X_R_DIR] =  (t_float32)GMCR_DIR_REFERENCE;
        s_setMvmt_b = (t_bool)True; 
    }

    
}

/*********************************
 * GMCR_Cyclic
 *********************************/
static t_eReturnCode s_GMCR_ReferenceAxeY(void)
{

}

 /*********************************
 * GMCR_Cyclic
 *********************************/
static t_eReturnCode s_GMCR_ReferenceAxeZ(void)
{
    t_eReturnCode Ret_e = RC_OK;
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

