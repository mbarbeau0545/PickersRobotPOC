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
#include "./FMK_CAN.h"
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKCAN_ConfigPrivate.h"
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
typedef struct 
{
    CAN_HandleTypeDef bspCan_s;
    const t_eFMKCPU_IRQNType c_IRQNType_e;
    const t_eFMKCPU_ClockPort c_clock_e;  
    t_eFMKCAN_Errostatus Error_e;
    t_eFMKCAN_FifoStatus fifoState_ae[FIFO_NB];
    t_eFMKCAN_FifoStatus mailBoxState_ae[MAILBOX_NB];
    t_bool isConfigured_b;
    t_bool isActibe_b
}
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
//                      Local functions - Implementation
//********************************************************************************

/******************************************
 * BSP CALLBACK IMPLEMENTATION
 *****************************************/
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
