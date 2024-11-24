/**
 * @file        FMK_MAC.c
 * @brief       Framework Memory Access Control module.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        15/09/2024
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./SafeMem.h"
#include "string.h"
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

//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************

//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
//**********************
// SafeMem_memcpy
//**********************
t_eReturnCode SafeMem_memcpy(void *f_destination_pv, const void *f_src_pv, t_uint16 f_size_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 result_u32 = 0;
    // Vérification des pointeurs NULL
    if (f_destination_pv == NULL || f_src_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        // Effectuer la copie avec memcpy
        void *memcpy_pv = memcpy(f_destination_pv, f_src_pv, (size_t)f_size_u16);
        Ret_e = SafeMem_memcmp(f_destination_pv, f_src_pv, (t_uint16)f_size_u16, &result_u32);
        if(Ret_e == RC_OK)
        {
            // Vérification que memcpy renvoie bien le pointeur destination
            if((memcpy_pv != f_destination_pv)
            || (result_u32 != 0))
            {
                Ret_e = RC_WARNING_MEM_FAILED;
            }
        }
    }

    return Ret_e;
}

//**********************
// SafeMem_memset
//**********************
t_eReturnCode SafeMem_memset(void *f_destination_pv, t_uint16 f_value_u16, t_uint16 f_size_u16)
{
    t_eReturnCode Ret_e = RC_OK;

    // Vérification du pointeur NULL
    if (f_destination_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        // Effectuer l'opération avec memset
        void *memset_pv = memset(f_destination_pv, f_value_u16, (size_t)f_size_u16);

        // Vérification que memset renvoie bien le pointeur destination
        if (memset_pv != f_destination_pv)
        {
            Ret_e = RC_WARNING_MEM_FAILED;
        }
    }

    return Ret_e;
}

//**********************
// SafeMem_memmove
//**********************
t_eReturnCode SafeMem_memmove(void *f_destination_pv, const void *f_src_pv, t_uint16 f_size_u16)
{
    t_eReturnCode Ret_e = RC_OK;

    // Vérification des pointeurs NULL
    if (f_destination_pv == NULL || f_src_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        // Effectuer l'opération avec memmove
        void *memmove_pv = memmove(f_destination_pv, f_src_pv, (size_t)f_size_u16);

        // Vérification que memmove renvoie bien le pointeur destination
        if (memmove_pv != f_destination_pv)
        {
            Ret_e = RC_WARNING_MEM_FAILED;
        }
    }

    return Ret_e;
}

//**********************
// SafeMem_memcmp
//**********************
t_eReturnCode SafeMem_memcmp(const void *f_buffer1_pv, const void *f_buffer2_pv, t_uint16 f_size_u16, t_uint32 *f_result_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    // Vérification des pointeurs NULL
    if (f_buffer1_pv == NULL || f_buffer2_pv == NULL || f_result_u32 == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        // Comparaison avec memcmp
        *f_result_u32 = memcmp(f_buffer1_pv, f_buffer2_pv, (size_t)f_size_u16);

        // Vérification du résultat
        if (*f_result_u32 != 0)
        {
            Ret_e = RC_WARNING_MEM_FAILED;
        }
    }

    return Ret_e;
}

//**********************
// SafeMem_memclear
//**********************
t_eReturnCode SafeMem_memclear(void *f_buffer_pv, t_uint16 f_size_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    volatile unsigned char *ptr = NULL;

    // Vérification du pointeur NULL
    if (f_buffer_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        // Effacer la mémoire
        ptr = (volatile unsigned char *)f_buffer_pv;
        while (f_size_u16--)
        {
            *ptr++ = 0;
        }
    }

    return Ret_e;
}

//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************


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
