/**
 * @file        FMK_MAC.h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKMAC_H_INCLUDED
#define FMKMAC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "FMK_CFG/FMKCFG_ConfigFiles/FMKMAC_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
    /**< Enum for Dma channel state */
    //-----------------------------TYPEDEF TYPES---------------------------//
    
    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    typedef t_eReturnCode (t_cbFMKMAC_DmaError)(t_uint8 debugInfo1, t_uint8 debugInfo2);
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************



    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    /**
    *
    *	@brief      Perform all Init action for this module.\n
    *	@note       Set to default value all globals structure that
    *                store information for each signals.\n
    *
    */
    t_eReturnCode FMKMAC_Init(void);
    /**
    *
    *	@brief      Perform all Cyclic action for this module.\n
    *	@note       In ope mode this module makes diag on input currently used, and 
    *               called the appropriate callback if an error occured + call APPDEM
    *               to reference error.\n
    *
    */
    t_eReturnCode FMKMAC_Cyclic(void);
    /**
    *
    *	@brief Function to know the module state 
    *	@param[in]  f_State_pe : store the value, value from @ref t_eCyclicModState
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
    */
    t_eReturnCode FMKMAC_GetState(t_eCyclicModState *f_State_pe);
    /**
    *
    *	@brief Function to update the module state 
    *	@param[in]  f_State_e : the new value, value from @ref t_eCyclicModState
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
    */
    t_eReturnCode FMKMAC_SetState(t_eCyclicModState f_State_e);
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
    t_eReturnCode FMKMAC_RqstDmaInit(t_eFMKMAC_DmaRqst f_DmaType, void *f_ModuleHandle_pv);
#endif // FMKMAC_H_INCLUDED           
//************************************************************************************
// End of File
//************************************************************************************

/**************************************************************************
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
