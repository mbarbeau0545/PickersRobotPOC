/*********************************************************************
 * @file        APPSYS_ConfigPublic.h
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
#include "./APPSDM_ConfigSpecific.h"
#include "APP_LGC/Src/APP_LGC.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//
/**< enum for module list */

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

//****************************************************************************
//                      Local functions - Prototypes
//****************************************************************************
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
t_eReturnCode s_APPSDM_SPEC_GetHealthFromStratOpe(t_eAPPSDM_DiagStratOpe f_stratOpe_e, t_eAPPLGC_SrvHealth * f_health_pe);

//****************************************************************************
//                      Public functions - Implementation
//****************************************************************************
/* CAUTION : Automatic generated code section for Diag Strategy Function Implementation: Start */
/*********************************
APPSDM_SPEC_DiagStrat_Gantry_Off
 *********************************/
APPSDM_SPEC_DiagStrat_Gantry_Off(t_eAPPSDM_DiagStratOpe f_stratOpe_e)
{
    t_eAPPLGC_SrvHealth srvHealth_e;
    t_eReturnCode Ret_e = RC_OK;

    Ret_e = s_APPSDM_SPEC_GetHealthFromStratOpe(f_stratOpe_e, &srvHealth_e);

    if(Ret_e == RC_OK)
    {
        Ret_e = APPLGC_SetServiceHealth(APPLGC_SRV_GANTRY_X, srvHealth_e);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPLGC_SetServiceHealth(APPLGC_SRV_GANTRY_Y, srvHealth_e);
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = APPLGC_SetServiceHealth(APPLGC_SRV_GANTRY_Z, srvHealth_e);
    }

    return;
}

/*********************************
APPSDM_SPEC_DiagStrat_Gantry_Axe_X_Off
 *********************************/
APPSDM_SPEC_DiagStrat_Gantry_Axe_X_Off(t_eAPPSDM_DiagStratOpe f_stratOpe_e)
{
    t_eAPPLGC_SrvHealth srvHealth_e;
    t_eReturnCode Ret_e = RC_OK;

    Ret_e = s_APPSDM_SPEC_GetHealthFromStratOpe(f_stratOpe_e, &srvHealth_e);

    if(Ret_e == RC_OK)
    {
        Ret_e = APPLGC_SetServiceHealth(APPLGC_SRV_GANTRY_X, srvHealth_e);
    }

    return;
}

/*********************************
APPSDM_SPEC_DiagStrat_Gantry_Axe_Y_Off
 *********************************/
APPSDM_SPEC_DiagStrat_Gantry_Axe_Y_Off(t_eAPPSDM_DiagStratOpe f_stratOpe_e)
{
    t_eAPPLGC_SrvHealth srvHealth_e;
    t_eReturnCode Ret_e = RC_OK;

    Ret_e = s_APPSDM_SPEC_GetHealthFromStratOpe(f_stratOpe_e, &srvHealth_e);

    if(Ret_e == RC_OK)
    {
        Ret_e = APPLGC_SetServiceHealth(APPLGC_SRV_GANTRY_Y, srvHealth_e);
    }

    return;
}

/*********************************
APPSDM_SPEC_DiagStrat_Gantry_Axe_Z_Off
 *********************************/
APPSDM_SPEC_DiagStrat_Gantry_Axe_Z_Off(t_eAPPSDM_DiagStratOpe f_stratOpe_e)
{
    t_eAPPLGC_SrvHealth srvHealth_e;
    t_eReturnCode Ret_e = RC_OK;

    Ret_e = s_APPSDM_SPEC_GetHealthFromStratOpe(f_stratOpe_e, &srvHealth_e);

    if(Ret_e == RC_OK)
    {
        Ret_e = APPLGC_SetServiceHealth(APPLGC_SRV_GANTRY_Z, srvHealth_e);
    }

    return;
}

/* CAUTION : Automatic generated code section for Diag Strategy Function Implementation: End */

//*****************************************************************************
//                      Local functions - Implementation
//*****************************************************************************
t_eReturnCode s_APPSDM_SPEC_GetHealthFromStratOpe(t_eAPPSDM_DiagStratOpe f_stratOpe_e, t_eAPPLGC_SrvHealth * f_health_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_stratOpe_e >= APPSDM_DIAG_STRAT_INHIBIT_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_stratOpe_e)
        {
            case  APPSDM_DIAG_STRAT_INHIBIT_OFF:
            {
                *f_health_pe = APPLGC_SRV_HEALTH_OK;
                break;
            }
            case  APPSDM_DIAG_STRAT_INHIBIT_ON:
            {
                *f_health_pe = APPLGC_SRV_HEALTH_ERROR;
                break;
            }
            break;
        case APPSDM_DIAG_STRAT_INHIBIT_NB:
        default:
            *f_health_pe = APPLGC_SRV_HEALTH_ERROR;
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
 *	@params[in] 
 *	@params[out]
 *	 
 *
 *
 */
