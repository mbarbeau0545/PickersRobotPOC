/**
 * @file        CL42T_ConfigPublic.h
 * @brief       Driver Module for Driver CL42T.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        21/01/2025
 * @version     1.0
 */
  
#ifndef CL42T_CONFIGPUBLIC_H_INCLUDED
#define CL42T_CONFIGPUBLIC_H_INCLUDED

    // ********************************************************************
    // *                      Includes
    // ********************************************************************

    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    typedef enum 
    {
        CL42T_MOTOR_SIGTYPE_PULSE = 0x00,
        CL42T_MOTOR_SIGTYPE_DIR,
        CL42T_MOTOR_SIGTYPE_STATE,
        CL42T_MOTOR_SIGTYPE_DEFAULT,

        CL42T_MOTOR_SIGTYPE_NB
    } t_eCL42T_MotorSigType;
    
    typedef enum 
    {
        CL42T_MOTOR_1 = 0x00,
        CL42T_MOTOR_2,
        CL42T_MOTOR_3,

        CL42T_MOTOR_NB,
    } t_eCL42T_MotorId;
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
    
#endif // CL42T_CONFIGPUBLIC_H_INCLUDED
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
