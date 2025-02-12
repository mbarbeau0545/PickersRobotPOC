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
#include "FMK_HAL/FMK_SRL/Src/FMK_SRL.h"
#include "APP_CFG/ConfigFiles/APPACT_ConfigPublic.h"

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
static t_sAPPLGC_ActInfo * g_actInfo_pas;
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
t_eReturnCode GMCR_Cyclic(  t_float32 *f_snsValues_paf32, 
                            t_sAPPLGC_ServiceInfo *f_SrvInfo_pas,
                            t_sAPPLGC_ActInfo * f_g_actInfo_pas)
{
    t_eReturnCode Ret_e = RC_OK;
    //----- Initialize Pointor to data -----//
    g_snsValues_paf32 = (t_float32 *)f_snsValues_paf32;
    g_SrvInfo_pas = (t_sAPPLGC_ServiceInfo *)f_SrvInfo_pas;

    switch (g_FSMReference_e)
    {
        case GMCR_FSM_REF_AXE_X:
        {
            if(g_SrvInfo_pas[APPLGC_SRV_GTRY_X].state_e != APPLGC_SRV_STATE_STOPPED
            || (g_SrvInfo_pas[APPLGC_SRV_GTRY_X].health_e == APPLGC_SRV_HEALTH_OK))
            {
                Ret_e = RC_WARNING_BUSY;
            }
            else
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
            if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].state_e != APPLGC_SRV_STATE_STOPPED
            || (g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].health_e != APPLGC_SRV_HEALTH_OK))
            {
                Ret_e = RC_WARNING_BUSY;
            }
            else
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
            if(g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].state_e != APPLGC_SRV_STATE_STOPPED
            || (g_SrvInfo_pas[APPLGC_SRV_GTRY_Y].health_e != APPLGC_SRV_HEALTH_OK))
            {
                Ret_e = RC_WARNING_BUSY;
            }
            else
            {
                Ret_e = s_GMCR_ReferenceAxeZ();

                if(Ret_e == RC_OK)
                {
                    //----- Send Message Application -----//
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
    t_eReturnCode Ret_e = RC_WARNING_BUSY;
    static t_bool s_setMvmt_b = False;

    //----- Check Contact -----//
    if((g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_X_L_MAX] == APPSNS_LIM_SWCH_NC_CONTACT)
    || (g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_X_L_MIN] == APPSNS_LIM_SWCH_NC_CONTACT)
    || (g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_X_R_MIN] == APPSNS_LIM_SWCH_NC_CONTACT)
    || (g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_X_R_MAX] == APPSNS_LIM_SWCH_NC_CONTACT))
    {
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_L_PULSE].setValue_f32 = (t_float32)0.0;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_R_PULSE].setValue_f32 = (t_float32)0.0;
        Ret_e == RC_OK;
    }

    //----- Set Actuators for reference -----//
    if(s_setMvmt_b == (t_bool)False);
    {
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_L_PULSE].setValue_f32 = (t_float32)GMCR_PULSE_REFERENCE;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_R_PULSE].setValue_f32 = (t_float32)GMCR_PULSE_REFERENCE;

        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_L_SPEED].setValue_f32 =  (t_float32)GMCR_REF_FREQ_NOMINAL; 
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_R_SPEED].setValue_f32 =  (t_float32)GMCR_REF_FREQ_NOMINAL; 


        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_L_DIR].setValue_f32 = (t_float32)GMCR_DIR_X_REFERENCE; 
        g_actInfo_pas[APPACT_ACTUATOR_MTR_X_R_DIR].setValue_f32 = (t_float32)GMCR_DIR_X_REFERENCE; 

        Ret_e = RC_WARNING_BUSY;
        s_setMvmt_b = (t_bool)True;
    }

    return Ret_e;
}

/*********************************
 * s_GMCR_ReferenceAxeY
 *********************************/
static t_eReturnCode s_GMCR_ReferenceAxeY(void)
{
    t_eReturnCode Ret_e = RC_WARNING_BUSY;
    static t_bool s_setMvmt_b = False;

    //----- Check Contact -----//
    if((g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_Y_MAX] == APPSNS_LIM_SWCH_NC_CONTACT)
    || (g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_Y_MIN] == APPSNS_LIM_SWCH_NC_CONTACT))
    {
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Y_PULSE].setValue_f32 = (t_float32)0.0;
        Ret_e == RC_OK;
    }

    //----- Set Actuators for reference -----//
    if(s_setMvmt_b == (t_bool)False);
    {
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Y_PULSE].setValue_f32 = (t_float32)GMCR_PULSE_REFERENCE;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Y_SPEED].setValue_f32 =  (t_float32)GMCR_REF_FREQ_NOMINAL; 
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Y_DIR].setValue_f32 =  (t_float32)GMCR_DIR_Y_REFERENCE; 
        Ret_e = RC_WARNING_BUSY;
        s_setMvmt_b = (t_bool)True;
    }

    return Ret_e;
}
 /*********************************
 * s_GMCR_ReferenceAxeZ
 *********************************/
static t_eReturnCode s_GMCR_ReferenceAxeZ(void)
{
    t_eReturnCode Ret_e = RC_WARNING_BUSY;
    static t_bool s_setMvmt_b = False;

    //----- Check Contact -----//
    if((g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_Z_MAX] == APPSNS_LIM_SWCH_NC_CONTACT)
    || (g_snsValues_paf32[APPSNS_SENSOR_LIM_SWCH_Z_MIN] == APPSNS_LIM_SWCH_NC_CONTACT))
    {
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Z_PULSE].setValue_f32 = (t_float32)0.0;
        Ret_e == RC_OK;
    }

    //----- Set Actuators for reference -----//
    if(s_setMvmt_b == (t_bool)False);
    {
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Z_PULSE].setValue_f32 = (t_float32)GMCR_PULSE_REFERENCE;
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Z_SPEED].setValue_f32 =  (t_float32)GMCR_REF_FREQ_NOMINAL; 
        g_actInfo_pas[APPACT_ACTUATOR_MTR_Z_DIR].setValue_f32 =  (t_float32)GMCR_DIR_Z_REFERENCE; 
        Ret_e = RC_WARNING_BUSY;
        s_setMvmt_b = (t_bool)True;
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

