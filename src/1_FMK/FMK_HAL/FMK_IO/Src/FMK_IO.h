/**
 * @file        FMK_IO.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKIO_H_INCLUDED
#define FMKIO_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "FMK_HAL/FMK_TIM/Src/FMK_TIM.h"
    #include "FMK_CFG/FMKCFG_ConfigFiles/FMKIO_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKIO_ANALOG_OL_VALUE ((t_uint16)200)
    #define FMKIO_ANALOG_SC_VALUE ((t_uint16)4800)
    #define FMKIO_ANALOG_MIN_VALUE ((t_uint16)0)
    #define FMKIO_ANALOG_MAX_VALUE ((t_uint16)5000)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
    /**< Enum for signal hardware pull mode  */
    typedef enum 
    {
        FMKIO_PULL_MODE_DISABLE = 0x0U,     /**< There is no pull resisstance attached to the signal */
        FMKIO_PULL_MODE_DOWN,             /**< There is a pull down resistance attached to the signal */
        FMKIO_PULL_MODE_UP,             /**< There is a pull up resistance attached to the signal */

        FMKIO_PULL_MODE_NB              /**< Number of pull mode available */
    } t_eFMKIO_PullMode;

    /**< Enum for signal hardware speed mode  */
    typedef enum
    {
        FMKIO_SPD_MODE_LOW = 0x0U,         /**< The signal is checked not frequently by hardware */
        FMKIO_SPD_MODE_MEDIUM,          /**< The signal is checked frequently by hardware */
        FMKIO_SPD_MODE_HIGH,            /**< The signal is checked very frequently by hardware */

        FMKIO_SPD_MODE_NB,              /**< Number of signal speed mode available */
    } t_eFMKIO_SpdMode; 

    /**< Enum for Signal event trigger capture  */
    typedef enum
    {
        FMKIO_STC_RISING_EDGE = 0x0U,      /**< The signal is captured on rising edge */
        FMKIO_STC_FALLING_EDGE,         /**< The signal is captured on falling edge */
        FMKIO_STC_BOTH_EDGE,            /**< The signal is captured on rising and falling edge */

        FMKIO_STC_NB,                   /**< Number of signal trigger mode */
    } t_eFMKIO_SigTrigCptr;

    /**< Enum for input signal frequency value */
    typedef enum
    {
        FMKIO_FREQ_MEAS_FREQ = 0x0U,        /**< Freqency signal is a freqency in Hz */
        FMKIO_FREQ_MEAS_COUNT,          /**< Freqency signal is a counter of event detected (rise/fall or both) */
        FMKIO_FREQ_MEAS_PERIOD,         /**< Freqency signal is a period in ms */

        FMKIO_FREQ_MEAS_NB,             /**< Number of frequency value available */
    } t_eFMKIO_FreqMeas;

    typedef enum 
    {
        FMKIO_ECDR_MEAS_LAST,       /**< Get the last Raw Value from Position or Direction Buffer*/
        FMKIO_ECDR_MEAS_MEAN,       /**< Get the Mean Value from Position or Direction Buffer */
        FMKIO_ECDR_MEAS_NB,
    } t_eFMKIO_EcdrMeas;

    /**< Enum for signal type manage in this module */
    typedef enum 
    {
        FMKIO_SIGTYPE_INPUT_DIG = 0x0U,        /**< Signal are digital input */
        FMKIO_SIGTYPE_INPUT_FREQ,           /**< Signal are frequency input */
        FMKIO_SIGTYPE_INPUT_ANA,            /**< Signal are analog input */
        FMKIO_SIGTYPE_INPUT_EVNT,           /**< Signal are event input */
        FMKIO_SIGTYPE_INPUT_ECDR,           /**< Signal are event input */
        FMKIO_SIGTYPE_OUTPUT_DIG,           /**< Signal are digital output */
        FMKIO_SIGTYPE_OUTPUT_PWM,           /**< Signal are pwm ouptut */

        FMKIO_SIGTYPE_OUTPUT_NB,            /**< Number of signal type available*/
    } t_eFMKIO_SigType;

    /**< Enum for signal digital state */
    typedef enum 
    {
        FMKIO_DIG_VALUE_LOW = 0x0U,        /**< Signal digital state set to low, logic level 0 */
        FMKIO_DIG_VALUE_HIGH,           /**< Signal digital state set to high, logic level 1 */

        FMKIO_DIG_VALUE_NB              /**< Number of digital state */
    } t_eFMKIO_DigValue;
    
    /**< Enum for Encoder Mode  */
    typedef enum 
    {
        FMKIO_ENCODER_START_POS = 0x00, /**< Start the Encoder Position to reveice Information */
        FMKIO_ENCODER_START_DIR,        /**< Start the Encoder Direction  to reveice Information */
        FMKIO_ENCODER_START_BOTH,       /**< Start the Encoder Position/Direction to receive Information */

        FMKIO_ENCODER_START_NB,
    } t_eFMKIO_EcdrStartOpe;

    typedef enum 
    {
        FMKIO_ENCODER_DIR_FORWARD = 0x00,
        FMKIO_ENCODER_DIR_BACKWARD,

        FMKIO_ENCODER_DIR_NB,
    } t_eFMKIO_EcdrDir;

    enum 
    {
        FMKIO_ANALOG_SC_DETECTED = 0x0U,
        FMKIO_ANALOG_OL_DETECTED = 0x1U,
    };

    //-----------------------------TYPEDEF TYPES---------------------------//
    /**
    *
    *	@brief      This function is a callback function for event signal.\n
    *	@note       Once the trigger is detected this function callback should be
    *               called.\n
    *                store information for each signals.\n
    *
    */
    typedef t_eReturnCode (t_cbFMKIO_EventFunc)(void);
    /**
    *
    *	@brief      This function is a callback function for dignostic/ error
                    management.\n
    *	@note       FMKIO module ask FMKCPU & FMKCDA modules if there is any error 
    *               detected on respectively timer or channel and adc.\n
    *               If an error is repertory and a callback function is given during 
    *               FMKIO_cfg function, it will be called with debugging info from FMKCDA or 
    *               FMKCPU module.\n
    * 
    *	@param[in]      f_debugInfo1_u8 : Debug Info numero 1
    *                   For Pwm, Ana, Freq this varaible equals to the channel error status 
    *                   @ref t_eFMKCPU_ChnlErrorState or @ref t_eFMKCDA_ChnlErrState
    *	@param[in]      f_debugInfo2_u8 : Debug Info numero 2
    *                   UNUSED for now 
    *                store information for each signals.\n
    *
    */
    typedef void (t_cbFMKIO_SigErrorMngmt)( t_eFMKIO_SigType f_sigType_e,
                                            t_uint8 f_sigId_u8,
                                            t_uint16 f_debugInfo1_u16, 
                                            t_uint16 f_debugInfo2_u16);
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
    *
    *	@brief      Perform all Init action for this module.\n
    *	@note       Set to default value all globals structure that
    *                store information for each signals.\n
    *
    */
    t_eReturnCode FMKIO_Init(void);
    /**
    *
    *	@brief      Perform all Cyclic action for this module.\n
    *	@note       In ope mode this module makes diag on input currently used, and 
    *               called the appropriate callback if an error occured + call APPDEM
    *               to reference error.\n
    *
    */
    t_eReturnCode FMKIO_Cyclic(void);
    /**
    *
    *	@brief Function to know the module state 
    *	@param[in]  f_State_pe : store the value, value from @ref t_eCyclicModState
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
    */
    t_eReturnCode FMKIO_GetState(t_eCyclicModState *f_State_pe);
    /**
    *
    *	@brief Function to update the module state 
    *	@param[in]  f_State_e : the new value, value from @ref t_eCyclicModState
    *
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
    */
    t_eReturnCode FMKIO_SetState(t_eCyclicModState f_State_e);
    /**
    *
    *	@brief      Set an input in Digital configuration.\n
    *	@note       Allow the user to choose among digitals inputs.\n
    *               & a pullMode.\n This function configure bspInit and call HAL_function.\n
    *
    *
    *	@param[in]      f_signal_e : the input digital signal, value from @ref t_eFMKIO_InDigSig
    *	@param[in]      f_pull_e   : the input pull mode, value from @ref t_eFMKIO_PullMode
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *
    */
    t_eReturnCode FMKIO_Set_InDigSigCfg(t_eFMKIO_InDigSig f_signal_e, t_eFMKIO_PullMode f_pull_e);
    /**
    *
    *	@brief      Set an input in Analog configuration.\n
    *	@note       Allow the user to choose among analogs inputs.\n
    *               & a pullMode.\n 
    *               This function configure bspInit ,call HAL_function,
    *               call FMKCDA to configure an ADC_channel.\n
    *
    *
    *	@param[in]      f_signal_e     : the input analog signal, value from @ref t_eFMKIO_InAnaSig
    *	@param[in]      f_pull_e        : the input pull mode, value from @ref t_eFMKIO_PullMode
    *	@param[in]      f_sigErr_cb     : callbback function that will be called if an error occured,NULL_FONCTION if not used
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *
    */
    t_eReturnCode FMKIO_Set_InAnaSigCfg(t_eFMKIO_InAnaSig f_signal_e, 
                                            t_eFMKIO_PullMode f_pull_e,
                                            t_cbFMKIO_SigErrorMngmt *f_sigErr_cb);
    /**
    *
    *	@brief      Set an input in frequency configuration.\n
    *	@note       Allow the user to choose among frequencies inputs.\n 
    *               This function configure bspInit , call HAL_function,
    *               call FMKCPU to configure a timer in order to convert a digital signal
    *               into a frequency.\n
    *
    *
    *	@param[in]      f_signal_e     : the input frequency signal, a value from @ref t_eFMKIO_InFreqSig
    *	@param[in]      f_freqMeas_e    : the input pull mode, value from @ref t_eFMKIO_FreqMeas
    *	@param[in]      f_sigErr_cb     : callbback function that will be called if an error occured
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *
    */
    t_eReturnCode FMKIO_Set_InFreqSigCfg(t_eFMKIO_InFreqSig f_signal_e, 
                                            t_eFMKIO_SigTrigCptr f_trigger_e,
                                            t_eFMKIO_FreqMeas f_freqMeas_e,
                                            t_cbFMKIO_SigErrorMngmt *f_sigErr_cb);
    /**
    *
    *	@brief      Set an intput in event configuration.\n
    *	@note       Allow the user to choose among event inputs.\n 
    *               This function configure bspInit, call HAL_function, 
    *               configure a external Interrupt which from hal_library will call 
    *               f_Evnt_cb on f_trigger_e detection.\n
    *
    *
    *	@param[in]      f_signal_e          : the input frequency signal, a value from @ref t_eFMKIO_InEvntSig
    *	@param[in]      f_pull_e            : the input pull mode, value from @ref t_eFMKIO_PullMode
    *	@param[in]      f_debouncDelay_u32  : time in which interrupt will be ignore due to indertemine state
    *	@param[in]      f_trigger_e         : time in ms to ignore fluctuation from signal after a interruption happened
    *	@param[in]      f_Evnt_cb           : Function to call when the edge is detected by hardware
    *	@param[in]      f_sigErr_cb         : callbback function that will be called if an error occured, NULL_FONCTION if not used
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *
    */
    t_eReturnCode FMKIO_Set_InEvntSigCfg(t_eFMKIO_InEvntSig f_signal_e, 
                                          t_eFMKIO_PullMode f_pull_e,
                                          t_eFMKIO_SigTrigCptr f_trigger_e,
                                          t_uint32 f_debouncDelay_u32,
                                          t_cbFMKIO_EventFunc * f_Evnt_cb,
                                          t_cbFMKIO_SigErrorMngmt *f_sigErr_cb);
        /**
    *
    *	@brief      Set an intput in Encoder configuration.\n
    *	@note       Allow User to set Two Pin in Input Mode, Synchronize to 
    *               perform encoder Configuration.\n 
    *               This function initialize both pin and called FMKCPU for
    *               timers configuration.\n
    *               f_startOpe is used to know wether user wants to enable both 
    *               channel (know Position & Direction) or only one of them.\n
    *               
    *
    *   @warning    The encoder mode impose two use timer x CHANNEL 1 and 2 in order to perform
    *               configuration.\n
    *               Default RunMode configuration is polling 'cause it doesn't affect CPU speed : In
    *               encoder configuration, CPU is charged to put encoder position and direction directly in
    *               the right register. IT & DMA are used to get sample of position & direction which is not useful in 
    *               embeded system (I suppose).\n
    *
    *	@param[in]      f_InEncdr_e                 : the encoder input, value from @ref t_eFMKIO_InEcdrSignals
    *	@param[in]      f_PulsePerRevolution_u32    : Motor pulse per revolution (see datasheet of your motor)
    *	@param[in]      f_HwEcdrCfg_s               : Structure for encoder timer configuration
    *	@param[in]      f_pull_e                    : the input pull mode for both pins, value from @ref t_eFMKIO_PullMode
    *	@param[in]      f_spd_e                     : the input pull mode for both pins, value from @ref t_eFMKIO_SpdMode
    *	@param[in]      f_startOpe                  : Start operation mode, enum value from @ref t_eFMKIO_EcdrStartOpe
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *
    */
    t_eReturnCode FMKIO_Set_InEncoderSigCfg(t_eFMKIO_InEcdrSignals f_InEncdr_e,
                                            t_uint32 f_PulsePerRevolution_u32,
                                            t_sFMKTIM_EcdrCfg f_HwEcdrCfg_s,
                                            t_eFMKIO_PullMode f_pull_e,
                                            t_eFMKIO_SpdMode f_spd_e,
                                            t_eFMKIO_EcdrStartOpe f_startOpe);
    /**
    *
    *	@brief      Set an output in PWM configuration.\n
    *	@note       Allow the user to choose among pwm intputs.\n 
    *               This function configure bspInit , call HAL_function,
    *               call FMKCPU to configure a timer in order to convert generate
    *               the pwm period and dutycycle.\n
    *               IMPORTANT NOTE -> For SMT32, each signal has a timer and a channel
    *               based on hardware confifguration. A timer has multiple channel that shared the frequency
    *               f_frequency_u32, once the timer set with this frequency the other signal (channel) 
    *               will have the same frequency.\n If the frequency is changed, it will be changed for every signal.\n
    *
    *
    *	@param[in]      f_signal_e             : the input analog signal, a value from @ref t_eFMKIO_OutPwmSig
    *	@param[in]      f_pull_e               : the input pull mode, value from @ref t_eFMKIO_PullMode
    *	@param[in]      f_frequency_u32        : the PWM frequency 
    *	@param[in]      f_sigErr_cb             : callbback function that will be called if an error occured, NULL_FONCTION if not used
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *
    */
    t_eReturnCode FMKIO_Set_OutPwmSigCfg(t_eFMKIO_OutPwmSig        f_signal_e, 
                                          t_eFMKIO_PullMode        f_pull_e,
                                          t_uint32                 f_frequency_u32,
                                          t_cbFMKIO_SigErrorMngmt *f_sigErr_cb);
    /**
    *
    *	@brief      Set an output in digital configuration.\n
    *	@note       Allow the user to choose among digitals output.\n 
    *               This function configure bspInit & call HAL_function.\n
    *
    *
    *	@param[in]      f_signal_e     : the input frequency signal, a value from @ref t_eFMKIO_OutDigSig
    *	@param[in]      f_pull_e       : the input pull mode, value from @ref t_eFMKIO_PullMode
    *	@param[in]      f_spd_e        : the input speed mode, value from @ref t_eFMKIO_SpdMode
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_ALREADY_CONFIGURED       @ref RC_ERROR_ALREADY_CONFIGURED
    *
    */
    t_eReturnCode FMKIO_Set_OutDigSigCfg(t_eFMKIO_OutDigSig f_signal_e, 
                                          t_eFMKIO_PullMode  f_pull_e,
                                          t_eFMKIO_SpdMode   f_spd_e);
    /**
    *
    *	@brief      Set Signals configuration for CAN.\n
    *
    *
    *	@param[in]      f_SigCan_e     : which CAN configuration will be made, enum from @ref t_eFMKIO_ComSigCan
    *	 
    * @retval RC_OK                             @ref RC_OK
    * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *
    */
    t_eReturnCode FMKIO_Set_ComCanCfg(t_eFMKIO_ComSigCan f_SigCan_e);
    /**
    *
    *	@brief      Set Signals configuration for SERIAL com.\n
    *
    *
    *	@param[in]      f_SigSerial_e     : which Serial configuration will be made, enum from @ref t_eFMKIO_ComSigCan
    *	 
    * @retval RC_OK                             @ref RC_OK
    * @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *
    */
    t_eReturnCode FMKIO_Set_ComSerialCfg(t_eFMKIO_ComSigSerial f_SigSerial_e);
    /**
    *
    *	@brief      Update the digital output value.\n
    *	@note       Once the configuration is done, this function update the state of 
    *               the digital cycle with f_value_e.\n
    *
    *
    *	@param[in]      f_signal_e      : the input frequency signal, a value from @ref t_eFMKIO_OutDigSig
    *	@param[in]      f_value_e       : the update value, value from @ref t_eFMKIO_DigValue
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Set_OutDigSigValue(t_eFMKIO_OutDigSig f_signal_e, t_eFMKIO_DigValue f_value_e);
    /**
    *
    *	@brief      Get the digital input.\n
    *	@note       Once the configuration is done, this function call hal library to
                    know the state of the signal on store it into f_value_pe.\n
    *
    *
    *	@param[in]      f_signal_e       : the input frequency signal, a value from @ref t_eFMKIO_InDigSig
    *	@param[in]      f_value_pe       : storage for value value, value from @ref t_eFMKIO_DigValue
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Get_InDigSigValue(t_eFMKIO_InDigSig f_signal_e, t_eFMKIO_DigValue *f_value_pe);
    /**
    *
    *	@brief      Get the digital input.\n
    *	@note       Once the configuration is done, this function call hal library to
                    know the state of the signal on store it into f_value_pe.\n
    *
    *
    *	@param[in]      f_signal_e       : the input frequency signal, a value from @ref t_eFMKIO_InDigSig
    *	@param[in]      f_value_pe       : storage for value value, value from @ref t_eFMKIO_DigValue
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Get_InEcdrPositionValue(t_eFMKIO_InEcdrSignals f_signal_e, t_uint32 *f_value_pu32);
    /**
    *
    *	@brief      Get the digital input.\n
    *	@note       Once the configuration is done, this function call hal library to
                    know the state of the signal on store it into f_value_pe.\n
    *
    *
    *	@param[in]      f_signal_e       : the input frequency signal, a value from @ref t_eFMKIO_InDigSig
    *	@param[in]      f_value_pe       : storage for value value, value from @ref t_eFMKIO_DigValue
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Get_InEcdrDirectionValue(t_eFMKIO_InEcdrSignals f_signal_e, t_eFMKIO_EcdrDir *f_Dirvalue_pe);
    /**
    *
    *	@brief      Get the analog input.\n
    *	@note       Once the configuration is done, this function call the FMKCDA to know 
    *               the analog signal value.\n
    *               IMPORTANT -> Depending on FMKCDA scan mode (the one used on V0.1) it may be possible
    *               that the conversion of all analog is not finished, in this case, the value return is 0 and
    *               RetCode = RC_WARNING_NO_OPERATION
    *               If an error (shortcut or openload) is suspected errcallback function is called with debugInfo 1 =
    *               FMKIO_ANALOG_OL_DETECTED or FMKIO_ANALOG_SC_DETECTED
    *
    *
    *	@param[in]      f_signal_e       : the input frequency signal, a value from @ref t_eFMKIO_InAnaSig
    *	@param[in]      f_value_pu16     : storage for value
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_WARNING_NO_OPERATION           @ref RC_WARNING_NO_OPERATION
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Get_InAnaSigValue(t_eFMKIO_InAnaSig f_signal_e, t_uint16 *f_value_pu16);
    /**
    *
    *	@brief      Get the frequency input.\n
    *	@note       Once the configuration is done, a function is called based on the meas trigger
                    give in configuration function.\n
                    In the interrupt function we either increment a counter (count mode) or get the channel
                    capture value and store it.\n
                    In this function we either get this value or the last saved capture value if
                    an interruption is in progress and interruption function is writing in countainer "value".\n
                    If this happens retcode WARNING_BUSY is set and the calcul will be made on saved value.\n
    *               Depending on configuration, this value is either a coutner, a period (ms) or a frequency (Hz)
    *
    *	@param[in]      f_signal_e       : the input frequency signal, a value from @ref t_eFMKIO_InFreqSig
    *	@param[in]      f_value_pu32     : storage for value
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_WARNING_BUSY                   @ref RC_WARNING_BUSY
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Get_InFreqSigValue(t_eFMKIO_InFreqSig f_signal_e, t_uint32 *f_value_pu32);
    /**
    *
    *	@brief      Update the dutyCycle for a PWM.\n
    *	@note       Once the configuration is done, this function update the dutycyle of 
    *               the pwm. if the PWM is not started yet the framework automatically set ON the channel
    *               if the dutyCycle is set to 0 that will shut down the pulse generation.\n 
    *
    *
    *	@param[in]      f_signal_e        : the input pwm signal, a value from @ref t_eFMKIO_OutPwmSig
    *	@param[in]      f_dutyCycle_u16   : the dutycyle, value between 0 (0%) - 1000 (100%)
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Set_OutPwmSigDutyCycle(t_eFMKIO_OutPwmSig f_signal_e, t_uint16 f_dutyCycle_u16);
    /**
    *
    *	@brief      Update the dutyCycle for a PWM.\n
    *	@note       Once the configuration is done, this function update the dutycyle of 
    *               the pwm. if the PWM is not started yet the framework automatically set ON the channel
    *               if the dutyCycle is set to 0 that will shut down the pulse generation.\n 
    *
    *
    *	@param[in]      f_signal_e        : the input pwm signal, a value from @ref t_eFMKIO_OutPwmSig
    *	@param[in]      f_frequency_u16   : the frequency, value between 0 (0%) - 1000 (100%)
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Set_OutPwmSigFrequency(t_eFMKIO_OutPwmSig f_signal_e, t_uint32 f_frequency_u32);
            /**
    *
    *	@brief      Update the dutyCycle for a PWM.\n
    *	@note       Once the configuration is done, this function update the dutycyle of 
    *               the pwm. if the PWM is not started yet the framework automatically set ON the channel
    *               if the dutyCycle is set to 0 that will shut down the pulse generation.\n 
    *
    *
    *	@param[in]      f_signal_e        : the input pwm signal, a value from @ref t_eFMKIO_OutPwmSig
    *	@param[in]      f_frequency_u16   : the frequency, value between 0 (0%) - 1000 (100%)
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Set_OutPwmSigPulses(t_eFMKIO_OutPwmSig f_signal_e, t_uint16 f_pulses_u16);
        /**
    *
    *	@brief      Update the dutyCycle for a PWM.\n
    *	@note       Once the configuration is done, this function update the dutycyle of 
    *               the pwm. if the PWM is not started yet the framework automatically set ON the channel
    *               if the dutyCycle is set to 0 that will shut down the pulse generation.\n 
    *
    *
    *	@param[in]      f_signal_e        : the input pwm signal, a value from @ref t_eFMKIO_OutPwmSig
    *	@param[in]      f_dutyCycle_u16   : the dutycyle, value between 0 (0%) - 1000 (100%)
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Get_OutPwmSigDutyCycle(t_eFMKIO_OutPwmSig f_signal_e, t_uint16 * f_dutyCycle_pu16);
    /**
    *
    *	@brief      Update the dutyCycle for a PWM.\n
    *	@note       Once the configuration is done, this function update the dutycyle of 
    *               the pwm. if the PWM is not started yet the framework automatically set ON the channel
    *               if the dutyCycle is set to 0 that will shut down the pulse generation.\n 
    *
    *
    *	@param[in]      f_signal_e        : the input pwm signal, a value from @ref t_eFMKIO_OutPwmSig
    *	@param[in]      f_frequency_u16   : the frequency, value between 0 (0%) - 1000 (100%)
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Get_OutPwmSigFrequency(t_eFMKIO_OutPwmSig f_signal_e, t_uint32 * f_frequency_pu32);
    /**
    *
    *	@brief      Get the digital output.\n
    *	@note       Once the configuration is done, this function ask HAL_library 
    *               the value of the dedicate signal and store it in f_value_pu16
    *
    *	@param[in]      f_signal_e       : the input frequency signal, a value from @ref t_eFMKIO_OutPwmSig
    *	@param[in]      f_value_pe       : storage for value, value from @ref t_eFMKIO_DigValue
    *	 
    *   @retval RC_OK                             @ref RC_OK
    *   @retval RC_ERROR_MISSING_CONFIG           @ref RC_ERROR_MISSING_CONFIG
    *   @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
    *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NULL
    *   @retval RC_ERROR_BUSY                     @ref RC_ERROR_BUSY
    *
    */
    t_eReturnCode FMKIO_Get_OutDigSigValue(t_eFMKIO_OutDigSig f_signal_e, t_eFMKIO_DigValue *f_value_pe);

#endif // FMKIO_H_INCLUDED           
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
 *	@params[in]
 *	 
 *
 *
 */
