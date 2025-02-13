/*********************************************************************
 * @file        Gantry.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef GANTRY_H_INCLUDED
#define GANTRY_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "APP_CFG/ConfigFiles/Gantry_ConfigPublic.h"



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
        GTRY_SFM_GANTRY_PRODUCTION = 0x00,
        GTRY_SFM_GANTRY_PAUSE,
        GTRY_SFM_GANTRY_DEFAULT,

        GTRY_SFM_GANTRY_NB,
    } t_eGTRY_FSMGantry;
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
    t_eReturnCode Gantry_Init(void);
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
    t_eReturnCode Gantry_Cyclic(t_float32 *f_snsValues_paf32, 
                                t_sAPPLGC_ServiceInfo *f_SrvInfo_pas);
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
    t_eReturnCode Gantry_RqstSFMState(t_eGTRY_FSMGantry f_rqstGtryMode_e);
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
    t_eReturnCode Gantry_GetFFMState(t_eGTRY_FSMGantry *f_rqstGtryMode_pe);
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
    t_eReturnCode Gantry_InformAppMissionState(t_eGTRY_MissionStatus f_missionStatue_e);
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
