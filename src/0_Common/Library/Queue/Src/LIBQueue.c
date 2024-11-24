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
#include "./LIBQueue.h"
#include "string.h"
#include "./Library/SafeMem/SafeMem.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define LIBQUEUE_QUEUE_NEXT_INDEX(index, capacity) (((index) + 1) % (capacity))
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
// LIBQUEUE_Create
//**********************
t_eReturnCode LIBQUEUE_Create(t_sLIBQUEUE_QueueCore *f_Queue_ps, t_sLIBQUEUE_QueueCfg f_QueueCfg_s)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_Queue_ps == (t_sLIBQUEUE_QueueCore *)NULL
    || f_QueueCfg_s.bufferHead_pv == (void *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(f_QueueCfg_s.bufferSize_u8 == (t_uint8)0 
    || f_QueueCfg_s.elementSize_u8 == (t_uint8)0)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {// copy configuration in element structure
        f_Queue_ps->QueueCfg_s.bufferHead_pv = (void *)f_QueueCfg_s.bufferHead_pv;
        f_Queue_ps->QueueCfg_s.bufferSize_u8 = f_QueueCfg_s.bufferSize_u8;
        f_Queue_ps->QueueCfg_s.elementSize_u8 = f_QueueCfg_s.elementSize_u8;
        f_Queue_ps->QueueCfg_s.enableOverwrite_b = (t_bool)f_QueueCfg_s.enableOverwrite_b;
        f_Queue_ps->head_u8       = (t_uint8)0;
        f_Queue_ps->tail_u8       = (t_uint8)0;
        f_Queue_ps->actualSize_u8 = (t_uint8)0;
    }

    return Ret_e;
}

//**************************
// LIBQUEUE_WriteElement
//**************************
t_eReturnCode LIBQUEUE_WriteElement(t_sLIBQUEUE_QueueCore *f_Queue_ps, const void *f_element_pv)
{
    t_eReturnCode Ret_e = RC_OK;
    void * startWrite_pv = NULL;

    if(f_Queue_ps == (t_sLIBQUEUE_QueueCore *)NULL
    || f_element_pv == (const void *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(f_Queue_ps->actualSize_u8 >= f_Queue_ps->QueueCfg_s.bufferSize_u8 
    && f_Queue_ps->QueueCfg_s.enableOverwrite_b == (t_bool)False)
    {
        Ret_e = RC_WARNING_LIMIT_REACHED;
    }
    if(Ret_e == RC_OK)
    {
        startWrite_pv = (void *)((t_uint8 *)f_Queue_ps->QueueCfg_s.bufferHead_pv + 
                         (t_uint32)(f_Queue_ps->tail_u8 * f_Queue_ps->QueueCfg_s.elementSize_u8));

        Ret_e = SafeMem_memcpy((void *)startWrite_pv, 
                                    (const void *)f_element_pv, 
                                    (t_uint16)f_Queue_ps->QueueCfg_s.elementSize_u8);
        if(Ret_e == RC_OK)
        {
            f_Queue_ps->tail_u8 = LIBQUEUE_QUEUE_NEXT_INDEX(f_Queue_ps->tail_u8, f_Queue_ps->QueueCfg_s.bufferSize_u8);
            f_Queue_ps->actualSize_u8 += (t_uint8)1;
        }
    }

    return Ret_e;
}

//**************************
// LIBQUEUE_ReadElement
//**************************
t_eReturnCode LIBQUEUE_ReadElement(t_sLIBQUEUE_QueueCore *f_Queue_ps, void * f_element_pv)
{
    t_eReturnCode Ret_e = RC_OK;
    void * startRead_pv  = NULL;

    if(f_Queue_ps == (t_sLIBQUEUE_QueueCore *)NULL
    || f_element_pv == (void *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        startRead_pv = (t_uint32 *)(f_Queue_ps->QueueCfg_s.bufferHead_pv + (t_uint32)(f_Queue_ps->head_u8 * f_Queue_ps->QueueCfg_s.elementSize_u8));

        Ret_e = SafeMem_memcpy(f_element_pv, startRead_pv, f_Queue_ps->QueueCfg_s.elementSize_u8);
        if(Ret_e == RC_OK)
        {
            // reset the element to null
            memset(startRead_pv, 0, f_Queue_ps->QueueCfg_s.elementSize_u8);
            f_Queue_ps->head_u8 = LIBQUEUE_QUEUE_NEXT_INDEX(f_Queue_ps->head_u8, f_Queue_ps->QueueCfg_s.bufferSize_u8);
            f_Queue_ps->actualSize_u8 -= (t_uint8)1;
        }
        else 
        {
            f_element_pv = (void *)NULL;
        }
    }

    return Ret_e;
}   

//**************************
// LIBQUEUE_GetQueueSize
//**************************
void LIBQUEUE_GetSizeLeft(t_sLIBQUEUE_QueueCore *f_Queue_ps, t_uint8 *f_SizeLeft_u8)
{
    *f_SizeLeft_u8 =  (t_uint8)(f_Queue_ps->QueueCfg_s.bufferSize_u8 - f_Queue_ps->actualSize_u8);

    return;
}
//**************************
// LIBQUEUE_GetQueueSize
//**************************
void LIBQUEUE_GetActualSize(t_sLIBQUEUE_QueueCore *f_Queue_ps, t_uint8 *f_acutalSize_u8)
{
    *f_acutalSize_u8 =  f_Queue_ps->actualSize_u8;

    return;
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
