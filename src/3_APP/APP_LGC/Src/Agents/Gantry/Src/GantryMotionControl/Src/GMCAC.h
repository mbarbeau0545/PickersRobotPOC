/*********************************************************************
 * @file        GMCAC.h
 * @brief       Gantry Motion Control Application Control.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef GMCAC_H_INCLUDED
#define GMCAC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
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
   t_eReturnCode GMCAC_Init(void);
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
    t_eReturnCode GMCAC_EnterMode(void);
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
    t_eReturnCode GMCAC_ExitMode(void);
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
    t_eReturnCode GMCAC_Cyclic( t_float32 *f_snsValues_paf32, 
                                t_sAPPLGC_ServiceInfo *f_SrvInfo_pas);

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APP_LGC_H_INCLUDED           
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
