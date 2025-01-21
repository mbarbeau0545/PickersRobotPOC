/**
 * @file        CL42T.c
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
// ********************************************************************
// *                      Includes
// ********************************************************************
#include "TypeCommon.h"
#include "APP_CFG/ConfigFiles/CL42T_ConfigPrivate.h"
#include "APP_CFG/ConfigFiles/CL42T_ConfigPublic.h"
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
    t_uint8 IOsignal_u8;
    t_float32 signalValue_f32;
} t_sCL42T_MotorSigInfo;

typedef struct
{
    t_sCL42T_MotorSigInfo sigInfo_as[CL42T_MOTOR_SIGTYPE_NB];
    t_cbCL42T_DiagEvent * diagEvnt_pcb;
    t_eCL42T_HealthMotor health_e;
    t_bool isCongigured_b;
    t_bool FlagErrorDete
} t_sCL42T_MotorInfo;

//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************


//********************************************************************************
//                      Public functions - Implementation
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
