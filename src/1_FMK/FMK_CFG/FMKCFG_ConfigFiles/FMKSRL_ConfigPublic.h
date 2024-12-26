/*********************************************************************
 * @file        FMK_SRL.h
 * @brief       UART/USART Module.
 * @details     This module allows user to Transmit and Receive messages
 *              using UART/USART protocol.\n
 *              Configuration Public File.\n
 *              
 *
 * @author      mba
 * @date        21/12/2024
 * @version     1.0
 */
  
  
#ifndef FMKSRL_CONFIGPUBLIC_H_INCLUDED
#define FMKSRL_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./FMK_CFG/FMKCFG_ConfigFiles/FMKCPU_ConfigPublic.h"    
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKSRL_TIMEOUT_RECEPTION ((t_uint32)60)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------TYPEDEF TYPES---------------------------//
    
    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    // Flag automatic 
    typedef enum __t_eFMKSRL_SerialLine
    {
        FMKSRL_SERIAL_LINE_1 = 0x00, /**< Reference to USART 2 */
        FMKSRL_SERIAL_LINE_2,        /**< Reference to UART 4 */

        FMKSRL_SERIAL_LINE_NB,
    } t_eFMKSRL_SerialLine;

    typedef enum __t_eFMKSRL_HwProtocolType
    {
        FMKSRL_HW_PROTOCOL_UART = 0x00,
        FMKSRL_HW_PROTOCOL_USART,
        FMKSRL_HW_PROTOCOL_NB,
    } t_eFMKSRL_HwProtocolType;
    
    typedef enum __t_eFMKSRL_LineRunMode
    {
        FMKSRL_LINE_RUNMODE_POLL = 0x00,
        FMKSRL_LINE_RUNMODE_IT,
        FMKSRL_LINE_RUNMODE_DMA,

        FMKSRL_LINE_RUNMODE_NB
    } t_eFMKSRL_LineRunMode;

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
   
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKSRL_CONFIGPUBLIC_H_INCLUDED           
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
