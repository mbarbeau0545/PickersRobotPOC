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
static t_eGTRY_FSMProduction g_FSM_ProdMode_e = GTRY_SFM_PROD_NB;
static t_eGTRY_FSMGantry g_FSM_GtryMode_e = GTRY_SFM_GANTRY_PRE_PAUSE;
static t_float32 * g_snsValues_paf32;
static t_sAPPLGC_ServiceInfo * g_SrvInfo_pas;
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
static t_eReturnCode s_GTRY_StateMachineMngmt(t_eGTRY_FSMGantry * f_rqstGtryMode_pe);

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
t_eReturnCode Gantry_Cyclic(t_float32 * f_snsValues_paf32, t_sAPPLGC_ServiceInfo * f_SrvInfo_pas)
{
    t_eReturnCode Ret_e = RC_OK;
    

    //----- Initialize Pointor to data -----//
    g_snsValues_paf32 = (t_float32 *)f_snsValues_paf32;
    g_SrvInfo_pas = (t_sAPPLGC_ServiceInfo *)f_SrvInfo_pas;

    //----- Get New Mode from Application -----//
    
    switch (g_FSM_GtryMode_e)
    {
        case GTRY_SFM_GANTRY_PRE_PRODUCTION:
        {
            break;
        }
        case GTRY_SFM_GANTRY_PRODUCTION:
        {
            break;
        }
        case GTRY_SFM_GANTRY_PRE_PAUSE:
        {
            break;
        }
        case GTRY_SFM_GANTRY_PAUSE:
        {
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
        FSMGtryRqstMode_e = appCmd_u.SFMModeInfo_s.mainMode_u8;
        FSMRqstProdMode_u8 = appCmd_u.SFMModeInfo_s.prodMode_u8;

        //----- Find out if it's a change gantry -----//
        if(FSMGtryRqstMode_e != g_FSM_GtryMode_e)
        {
            //------ also update the new sub mode -----//
            switch(g_FSM_GtryMode_e)
            {
                case GTRY_SFM_GANTRY_PRE_PRODUCTION:
                case GTRY_SFM_GANTRY_PRODUCTION:
                {
                    Ret_e = c_Gtry_SFMProdFunc_as[g_FSM_ProdMode_e].Exit_pcb();
                    break;
                }
                case GTRY_SFM_GANTRY_PRE_PAUSE:
                case GTRY_SFM_GANTRY_PAUSE:
                case GTRY_SFM_GANTRY_DEFAULT:
                case GTRY_SFM_GANTRY_NB:
                default:
                {
                    break;
                }
            }
            g_FSM_GtryMode_e = FSMGtryRqstMode_e;
    
        }

        //----- Find out if it's a change of sub Mode -----//
        if(FSMRqstProdMode_u8 != (t_uint8)g_FSM_ProdMode_e)
        {
            switch()
        }
        

        
    }
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

