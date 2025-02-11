/*********************************************************************
 * @file        APPACT_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef GANTRY_CONFIGPRIVATE_H_INCLUDED
#define GANTRY_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "APP_CFG/ConfigFiles/APPLGC_ConfigPublic.h"
    #include "APP_CFG/ConfigFiles/Gantry_ConfigPublic.h"

    #include "APP_LGC/Src/Agents/Gantry/Src/GantryMotionControl/GMCAC/Src/GMCAC.h"
    #include "APP_LGC/Src/Agents/Gantry/Src/GantryMotionControl/GMCR/Src/GMCR.h"
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
	
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    const t_sAPPLGC_FSM_Func c_Gtry_SFMProdFunc_as[GTRY_SFM_PROD_NB] = 
    {// Init            Cyclic              EnterMode               ExitMode
        {GMCR_Init,      GMCR_Cyclic,        GMCR_EnterMode,         GMCR_ExitMode},
        {GMCAC_Init,     GMCAC_Cyclic,       GMCAC_EnterMode,        GMCAC_ExitMode},
    }
    /* CAUTION : Automatic generated code section for Variable: Start */

    /* CAUTION : Automatic generated code section for Variable: End */
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // GANTRY_CONFIGPRIVATE_H_INCLUDED           
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
