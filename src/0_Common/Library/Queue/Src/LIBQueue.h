/**
 * @file        FMK_MAC.h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef LIBQUEUE_H_INCLUDED
#define LIBQUEUE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//

    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
   
    //-----------------------------STRUCT TYPES---------------------------//
    typedef struct 
    {
        void     *bufferHead_pv;        /**< Head of the buffer */
        t_uint8   elementSize_u8;       /**< Size of one element in the Queue */
        t_uint8   bufferSize_u8;        /**< How many element maximum the  buffer will stock*/
        t_bool    enableOverwrite_b;     /**< Allow library to overwritten an element if buffer full */
    } t_sLIBQUEUE_QueueCfg;

    typedef struct 
    {
        t_sLIBQUEUE_QueueCfg QueueCfg_s;     /**< Configuration of the Queue */
        t_uint8   head_u8;                  /**< Index of the first element */
        t_uint8   tail_u8;                  /**< Index of the Next element */
        t_uint8   actualSize_u8;            /**< How many element in the current queue */

    } t_sLIBQUEUE_QueueCore;
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

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
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[in]
    *	 
    *
    *
    */
    t_eReturnCode LIBQUEUE_Create(t_sLIBQUEUE_QueueCore *f_Queue_ps, t_sLIBQUEUE_QueueCfg f_QueueCfg_s);
    /**
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[in]
    *	 
    *
    *
    */
    t_eReturnCode LIBQUEUE_WriteElement(t_sLIBQUEUE_QueueCore *f_Queue_ps, const void * f_element_pv);
    /**
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[in]
    *	 
    *
    *
    */
    t_eReturnCode LIBQUEUE_ReadElement(t_sLIBQUEUE_QueueCore *f_Queue_ps, void * f_element_pv);
    /**
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[in]
    *	 
    *
    *
    */
    t_eReturnCode LIBQUEUE_ClearAll(void);
    /**
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[in]
    *	 
    *
    *
    */
    t_eReturnCode LIBQUEUE_GetSizeLeft(t_sLIBQUEUE_QueueCore *f_Queue_ps, t_uint8 *f_SizeLeft_u8);
    /**
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[in]
    *	 
    *
    *
    */
    void LIBQUEUE_GetActualSize(t_sLIBQUEUE_QueueCore *f_Queue_ps, t_uint8 *f_acutalSize_u8);
#endif // LIBQUEUE_H_INCLUDED
//************************************************************************************
// End of File
//************************************************************************************

/**
 *	@brief
 *	@note   
 *
 *
 *	@param[in] 
 *	@param[in]
 *	 
 *
 *
 */
