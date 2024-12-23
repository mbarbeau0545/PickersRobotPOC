/*********************************************************************
 * @file        FMK_SRL.h
 * @brief       UART/USART Module.
 * @details     This module allows user to Transmit and Receive messages
 *              using UART/USART protocol.\n
 *              
 *
 * @author      mba
 * @date        21/12/2024
 * @version     1.0
 */
  
#ifndef FMKSERIAL_INCLUDED
#define FMKSERIAL_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./FMK_CFG/FMKCFG_ConfigFiles/FMKSRL_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
	/* CAUTION : Automatic generated code section for Enum: Start */

	/* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//
    typedef enum __t_eFMKSRL_RxOpeMode
    {
        FMKSRL_OPE_RX_ONESHOT_SIZE = 0x00,
        FMKSRL_OPE_RX_ONESHOT_IDLE,
        FMKSRL_OPE_RX_CYCLIC_SIZE,
        FMKSRL_OPE_RX_CYCLIC_IDLE,

#ifdef FMKCPU_STM32_ECU_FAMILY_G
        FMKSRL_OPE_RX_ONESHOT_TIMEOUT,
        FMKSRL_OPE_RX_CYCLIC_TIMEOUT,
#endif

        FMKSRL_OPE_RX_NB,
    } t_eFMKSRL_RxOpeMode;

    typedef enum __t_eFMKSRL_TxOpeMode
    {
        FMKSRL_TX_ONESHOT = 0x00,
        FMKSRL_TX_RX_SIZE,
        FMKSRL_TX_RX_IDLE,

#ifdef FMKCPU_STM32_ECU_FAMILY_G
        FMKSRL_TX_RX_TIMEOUT,
#endif

        FMKSRL_TX_NB
    } t_eFMKSRL_TxOpeMode;

    typedef enum __t_eFMKSRL_UartType
    {
        FMKSRL_UART_TYPECFG_UART = 0x00,
        FMKSRL_UART_TYPECFG_HALF_DUPLEX,
        FMKSRL_UART_TYPECFG_LIN,
        FMKSRL_UART_TYPECFG_MULTI_PROCESS,

        FMKSRL_UART_TYPECFG_NB
    } t_eFMKSRL_UartType;

    typedef enum __t_eFMKSRL_UsartTypeCfg
    {
        FMKSRL_USART_TYPECFG_USART = 0x00,

        FMKSRL_USART_TYPECFG_NB
    } t_eFMKSRL_UsartType;

    typedef enum __t_eFMKSRL_UsartClockPhase
    {
        FMKSRL_USART_PHASE_1EDGE = 0x00,
        FMKSRL_USART_PHASE_2EDGE,

        FMKSRL_USART_PHASE_NB
    } t_eFMKSRL_UsartClockPhase;

    typedef enum __t_eFMKSRL_UsartLastBit
    {
        FMKSRL_USART_LAST_BIT_ENABLE= 0x00,
        FMKSRL_USART_LAST_BIT_DISABLE,

        FMKSRL_USART_LAST_BIT_NB
    } t_eFMKSRL_UsartLastBit;

    typedef enum __t_eFMKSRL_UsartClkPolarity
    {
        FMKSRL_USART_CLK_POLARITY_HIGH = 0x00,
        FMKSRL_USART_CLK_POLARITY_LOW,

        FMKSRL_USART_CLK_POLARITY_NB
    } t_eFMKSRL_UsartClkPolarity;

    typedef enum __t_eFMKSRL_LinBreakLenght
    {
        FMKSRL_LIN_BREAK_LENGHT_10B = 0x00,
        FMKSRL_LIN_BREAK_LENGHT_11B,

        FMKSRL_LIN_BREAK_LENGHT_NB,
    } t_eFMKSRL_LinBreakLenght;

    typedef enum __t_eFMKSRL_MProcessWakeUpMeth
    {
        FMKSRL_MPROCESS_WAKEUP_IDLE = 0x00,
        FMKSRL_MPROCESS_WAKEUP_ADDMARK,

        FMKSRL_MPROCESS_WAKEUP_NB
    } t_eFMKSRL_MProcessWakeUpMeth;
#ifdef FMKCPU_STM32_ECU_FAMILY_G
    typedef enum __t_eFMKSRL_UartHwFlowCtrl
    {
        FMKSRL_UART_HW_FLOW_CTRL_NONE = 0X00,
        FMKSRL_UART_HW_FLOW_CTRL_RTS,
        FMKSRL_UART_HW_FLOW_CTRL_CTS,
        FMKSRL_UART_HW_FLOW_CTRL_RTS_CTS,

        FMKSRL_UART_HW_FLOW_CTRL_NB
    } t_eFMKSRL_UartHwFlowCtrl;
#endif    

    typedef enum __t_eFMKSRL_LineMode
    {
        FMKSRL_LINE_MODE_RX = 0x00,
        FMKSRL_LINE_MODE_TX,
        FMKSRL_LINE_MODE_RX_TX,

        FMKSRL_LINE_MODE_NB
    } t_eFMKSRL_LineMode;

    typedef enum __t_eFMKSRL_LineParity
    {
        FMKSRL_LINE_PARITY_NONE = 0x00,
        FMKSRL_LINE_PARITY_EVEN,
        FMKSRL_LINE_PARITY_ODD,

        FMKSRL_LINE_PARITY_NB
    } t_eFMKSRL_LineParity;

    typedef enum __t_eFMKSRL_LineWordLenght
    {

        FMKSRL_LINE_WORDLEN_9BITS = 0x00,
        FMKSRL_LINE_WORDLEN_8BITS, 
#ifdef FMKCPU_STM32_ECU_FAMILY_G
        FMKSRL_LINE_WORDLEN_7BITS,
#endif
        FMKSRL_LINE_WORDLEN_NB
    } t_eFMKSRL_LineWordLenght;

    typedef enum __t_eFMKSRL_LineSoptbit
    {
        FMKSRL_LINE_STOPBIT_0_5 = 0x00,
        FMKSRL_LINE_STOPBIT_1,
        FMKSRL_LINE_STOPBIT_1_5,
        FMKSRL_LINE_STOPBIT_2,

        FMKSRL_LINE_STOPBIT_NB,
    }t_eFMKSRL_LineSoptbit;

    typedef enum __t_eFMKSRL_LineBaudrate
    {
        FMKSRL_LINE_BAUDRATE_300 = 0x00,
        FMKSRL_LINE_BAUDRATE_1200,
        FMKSRL_LINE_BAUDRATE_2400,
        FMKSRL_LINE_BAUDRATE_4800,
        FMKSRL_LINE_BAUDRATE_9600,
        FMKSRL_LINE_BAUDRATE_19200,
        FMKSRL_LINE_BAUDRATE_38400,
        FMKSRL_LINE_BAUDRATE_57600,
        FMKSRL_LINE_BAUDRATE_74880,
        FMKSRL_LINE_BAUDRATE_115200,
        FMKSRL_LINE_BAUDRATE_230400,
        FMKSRL_LINE_BAUDRATE_250000,

        FMKSRL_LINE_BAUDRATE_NB
    } t_eFMKSRL_LineBaudrate;

    typedef enum 
    {
        FMKSRL_CB_INFO_RECEIVE_ENDING = 0x00,
        FMKSRL_CB_INFO_RECEIVE_PENDING,
        FMKSRL_CB_INFO_TRANSMIT_OVERFLOW,
        FMKSRL_CB_INFO_RECEIVE_OVERFLOW,
        FMKSRL_CB_INFO_TRANSMIT_ERR,
        FMKSRL_CB_INFO_RECEIVE_ERR,

    } t_eFMKSRL_CallbackInfo;
    
	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    typedef struct _t_sFMKSRL_LinCfg
    {
        t_eFMKSRL_LinBreakLenght BreakLen_e;
    } t_sFMKSRL_LinCfg;

    typedef struct _t_sFMKSRL_MProcessCfg
    {
        t_eFMKSRL_MProcessWakeUpMeth WakeUpMethod_e;
        t_uint8 IstcIdentifer_u8;
    } t_sFMKSRL_MProcessCfg;

    typedef union __t_uFMKSRL_UartTypeCfgSpec
    {
        t_sFMKSRL_LinCfg linCfg_s;
        t_sFMKSRL_MProcessCfg MProcessCfg_s;
    } t_uFMKSRL_UartTypeCfgSpec;

    typedef struct __t_sFMKSRL_UartAdvProtCfg
    {
        t_uint8 None1_u8;
        t_uint8 None2_u8;
    } t_sFMKSRL_UartAdvProtCfg;

    typedef struct __t_sFMKSRL_UsartCfgSpec
    {
        t_eFMKSRL_UsartType          Type_e;
        t_eFMKSRL_UsartClockPhase       clockPhase_e;
        t_eFMKSRL_UsartLastBit          lastBit_e;
        t_eFMKSRL_UsartClkPolarity      clkPolarity_e;
    } t_sFMKSRL_UsartCfgSpec;

    typedef struct __t_sFMKSRL_UartCfgSpec
    {
        t_eFMKSRL_UartType Type_e;
        t_uFMKSRL_UartTypeCfgSpec typeCfg_u;
#ifdef FMKCPU_STM32_ECU_FAMILY_G
        t_sFMKSRL_UartAdvProtCfg    advProtCfg_s;
        t_eFMKSRL_UartHwFlowCtrl    hwFlowCtrl_e;
#endif
    } t_sFMKSRL_UartCfgSpec;

    typedef struct __t_sFMKSRL_HwProtocolCfg
    {
        t_eFMKSRL_LineBaudrate      Baudrate_e;
        t_eFMKSRL_LineMode          Mode_e;
        t_eFMKSRL_LineParity        Parity_e;
        t_eFMKSRL_LineSoptbit       Stopbit_e;
        t_eFMKSRL_LineWordLenght    wordLenght_e;
    } t_sFMKSRL_HwProtocolCfg;


    
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
	//-----------------------------TYPEDEF TYPES---------------------------//
    /**
    *
    *	@brief  Callback function to read a msg from UART/USART.\n
    *   @note   When the Serial line has started and user configure a receive mode,
    *           the module will call this function every time a message is received 
    *           and data match user configuration.\n
    *
    *	@param[in]  f_rxData_pu8          : the pointer to the data
    *	@param[in]  f_dataSize_u16        : the data size
    *	@param[in]  f_healthLine_e        : line status, value from @ref t_eFMKSRL_HealthLine
    *
    */
    typedef void (t_cbFMKSRL_RcvMsgEvent)(  t_uint8 * f_rxData_pu8, 
                                            t_uint16 f_dataSize_u16, 
                                            t_eFMKSRL_CallbackInfo f_InfoCb_e);

    /**
    *
    *	@brief  Callback function to know if a msg has been successfully transmit.\n
    *   @note   When the Serial line has started and user configure a receive mode,
    *           the module will call this function every time a message is received 
    *           and data match user configuration.\n
    *
    *	@param[in]  f_isMsgTransmit_b : Know id the message is transmited correctly.\n
    *	@param[in]  f_healthLine_e        : line status, value from @ref t_eFMKSRL_HealthLine
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
    */
    typedef void (t_cbFMKSRL_TransmitMsgEvent)(t_bool f_isMsgTransmit_b, t_eFMKSRL_CallbackInfo f_InfoCb_e);

    typedef union __t_uSerialCfgSpec
    {
        t_sFMKSRL_UartCfgSpec       uartCfg_s;
        t_sFMKSRL_UsartCfgSpec      usartCfg_s;
    } t_uFMKSRL_SerialCfgSpec;
    
    typedef struct __t_sFMKSRL_DrvSerialCfg
    {
        t_sFMKSRL_HwProtocolCfg     hwCfg_s;
        t_uFMKSRL_SerialCfgSpec     CfgSpec_u;
        t_eFMKSRL_LineRunMode       runMode_e;
        t_eFMKSRL_HwProtocolType    hwProtType_e;
    } t_sFMKSRL_DrvSerialCfg;
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
    t_eReturnCode FMKSRL_Init(void);
    /**
    *
    *	@brief      Perform all Cyclic action for this module.\n
    *	@note       
    *
    */
    t_eReturnCode FMKSRL_Cyclic(void);
    /**
    *
    *	@brief Function to know the module state.\n 
    *
    *	@param[in]  f_State_pe : store the value, value from @ref t_eCyclicModState
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
    */
    t_eReturnCode FMKSRL_GetState(t_eCyclicModState *f_State_pe);
    /**
    *
    *	@brief Function to update the module state.\n
    *
    *	@param[in]  f_State_e : the new value, value from @ref t_eCyclicModState
    *
    *   @retval RC_OK                             @ref RC_OK
    */
    t_eReturnCode FMKSRL_SetState(t_eCyclicModState f_State_e);

    /**
    *
    *	@brief Init an UART/ USART Driver for communication.\n 
    *   @note
    *
    *	@param[in]  f_State_pe : store the value, value from @ref t_eCyclicModState
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
    */
    t_eReturnCode FMKSRL_InitDrv(   t_eFMKSRL_SerialLine f_SrlLine_e, 
                                    t_sFMKSRL_DrvSerialCfg f_SerialCfg_s,
                                    t_cbFMKSRL_RcvMsgEvent * f_rcvMsgEvnt_pcb,
                                    t_cbFMKSRL_TransmitMsgEvent * f_txMsgEvnt_pcb);

    /**
    *
    *	@brief transmit a Msg CAN threw Serial Line
    *   @note
    *
    *	@param[in]  f_State_pe : store the value, value from @ref t_eCyclicModState
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
    */
    t_eReturnCode FMKSRL_Transmit(  t_eFMKSRL_SerialLine f_SrlLine_e, 
                                    t_eFMKSRL_TxOpeMode f_OpeMode_e,
                                    t_uint8 * _msgData_pu8,
                                    t_uint16 f_dataSize_u16,
                                    t_uint16 f_InfoMode_u16,
                                    t_bool   f_EnableTxCb_b);

    /**
    *
    *	@brief transmit a Msg CAN threw Serial Line
    *   @note
    *
    *	@param[in]  f_State_pe : store the value, value from @ref t_eCyclicModState
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
    */
    t_eReturnCode FMKSRL_ConfigureReception(  t_eFMKSRL_SerialLine f_SrlLine_e, 
                                              t_eFMKSRL_RxOpeMode f_OpeMode_e,
                                              t_uint16 f_InfoOpe_u16);
#endif // FMKSERIAL_INCLUDED           
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
