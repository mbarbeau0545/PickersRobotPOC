/**
 * @file        FMK_MAC.h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef SAFEMEM_H_INCLUDED
#define SAFEMEM_H_INCLUDED





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
     * @brief Performs a secure memory copy.
     * @param[in] f_destination_pv Pointer to the destination buffer.
     * @param[in] f_src_pv Pointer to the source buffer.
     * @param[in] f_size_u16 Size of the data to copy (in bytes).
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SafeMem_memcpy(void *f_destination_pv, const void *f_src_pv, t_uint16 f_size_u16);

    /**
     * @brief Initializes a memory region with a given value.
     * @param[in] f_destination_pv Pointer to the memory to initialize.
     * @param[in] f_value_i Value to write to the memory.
     * @param[in] f_size_u16 Size of the memory to initialize (in bytes).
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SafeMem_memset(void *f_destination_pv, t_uint16 f_value_u16, t_uint16 f_size_u16);

    /**
     * @brief Moves a memory region safely (supports overlapping regions).
     * @param[in] f_destination_pv Pointer to the destination buffer.
     * @param[in] f_src_pv Pointer to the source buffer.
     * @param[in] f_size_u16 Size of the data to move (in bytes).
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SafeMem_memmove(void *f_destination_pv, const void *f_src_pv, t_uint16 f_size_u16);

    /**
     * @brief Compares two memory regions.
     * @param[in] f_buffer1_pv Pointer to the first buffer.
     * @param[in] f_buffer2_pv Pointer to the second buffer.
     * @param[in] f_size_u16 Size of the data to compare (in bytes).
     * @param[out] f_result_pi Result of the comparison (-1, 0, 1).
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SafeMem_memcmp(const void *f_buffer1_pv, const void *f_buffer2_pv, t_uint16 f_size_u16, t_uint32 *f_result_pi);

    /**
     * @brief Clears a memory region securely (useful for sensitive data).
     * @param[in] f_buffer_pv Pointer to the memory to clear.
     * @param[in] f_size_u16 Size of the memory to clear (in bytes).
     * @return t_eReturnCode Return code indicating success or failure.
     */
    t_eReturnCode SafeMem_memclear(void *f_buffer_pv, t_uint16 f_size_u16);
#endif // SAFEMEM_H_INCLUDED           
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
