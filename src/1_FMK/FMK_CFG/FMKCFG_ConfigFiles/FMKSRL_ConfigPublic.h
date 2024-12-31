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
    
    /**
     * @brief Serial Line Available on CPU
     */
    typedef enum __t_eFMKSRL_SerialLine
    {
        FMKSRL_SERIAL_LINE_1 = 0x00, /**< Reference to USART 2 */
        FMKSRL_SERIAL_LINE_2,        /**< Reference to UART 4 */

        FMKSRL_SERIAL_LINE_NB,
    } t_eFMKSRL_SerialLine;

    /**
     * @brief Hardware Protocol Manage by the module
     */
    typedef enum __t_eFMKSRL_HwProtocolType
    {
        FMKSRL_HW_PROTOCOL_UART = 0x00,     /**< Reference to hardware protocol UART */
        FMKSRL_HW_PROTOCOL_USART,           /**< Reference to hardware protocol USART */
        FMKSRL_HW_PROTOCOL_NB,              /**< Number of hardware protocol UART */
    } t_eFMKSRL_HwProtocolType;
    
    /**
     * @brief Transmit/ Receive Actions Mode
     */
    typedef enum __t_eFMKSRL_LineRunMode
    {
        FMKSRL_LINE_RUNMODE_POLL = 0x00,    /**< Transmit Receive Actions are done in Polling Mode 
                                            /!\/!\ On Embeded System -> not recommended */
        FMKSRL_LINE_RUNMODE_IT,             /**< Transmit Receive Actions are done in Interrupt Mode 
                                            /!\/!\ On Embeded System -> Better than polling but use CPU charged */
        FMKSRL_LINE_RUNMODE_DMA,            /**< Transmit Receive Actions are done in DMA Mode 
                                            /!\/!\ On Embeded System -> Highly recommended */
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
