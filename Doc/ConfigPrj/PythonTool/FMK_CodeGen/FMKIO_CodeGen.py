"""
#  @file        main.py
#  @brief       Template_BriefDescription.
#  @details     TemplateDetailsDescription.\n
#
#  @author      mba
#  @date        jj/mm/yyyy
#  @version     1.0
"""
#------------------------------------------------------------------------------
#                                       IMPORT
#------------------------------------------------------------------------------
from PyCodeGene import LoadConfig_FromExcel as LCFE, TARGET_T_END_LINE,TARGET_T_ENUM_END_LINE, \
                                                    TARGET_T_ENUM_START_LINE,TARGET_T_START_LINE,TARGET_T_VARIABLE_START_LINE,\
                                                    TARGET_T_VARIABLE_END_LINE,TARGET_T_STRUCT_START_LINE,\
                                                    TARGET_T_STRUCT_END_LINE

from typing import List, Dict
from .FMK_PATH import * 
from .FMKCPU_CodeGen import TimerCfg_alreadyUsed, FMKCPU_CodeGen
#------------------------------------------------------------------------------
#                                       CONSTANT
#------------------------------------------------------------------------------
TARGET_EXTI_X_IRQN_START = "/* CAUTION : Automatic generated code section for Exti IRQN_Handler: Start */\n"
TARGET_EXTI_X_IRQN_END   = "/* CAUTION : Automatic generated code section for Exti IRQN_Handler: End */\n"
TARGET_SWITCH_GPIO_RCC_START = "        /* CAUTION : Automatic generated code section for Switch Case GPIO to RCC: Start */\n"
TARGET_SWITCH_GPIO_RCC_END   = "        /* CAUTION : Automatic generated code section for Switch Case GPIO to RCC: End */\n"
# CAUTION : Automatic generated code section: Start #

# CAUTION : Automatic generated code section: End #
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------
class GPIO_AlreadyConfgigured(Exception):
    pass
class FMKIO_CodeGen():
    """
            Make code generation for FMKIO modules which include 
            file FMKIO_ConfigPublic.h : 
                - Signal Enum for all types   x
                - GPIO port enum              x
                - GPIO pin enum               x
            file FMKIO_ConfigPublic.h :
                - Bsp Pin mapping             x
                - configuration for all pin   x
            file  FMK_IO.c
                - g_IsGpioClockEnable_ae      x
                - switch case GPIO port       x
        """
    code_gen = LCFE()
    @classmethod
    def code_generation(cls, f_hw_cfg) -> None:
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<Start code generation for FmkIO Module>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        TARGET_BALISE_SWITCH_GPIO_START = "            /* CAUTION : Automatic generated code section for GPIO switch case: Start */\n"
        TARGET_BALISE_SWITCH_GPIO_END   = "            /* CAUTION : Automatic generated code section for GPIO switch case: End */\n"
        
        cls.code_gen.load_excel_file(f_hw_cfg)
        
        # load the needed array 
        gpio_astr        = cls.code_gen.get_array_from_excel("GI_GPIO")[1:]
        InDig_astr       = cls.code_gen.get_array_from_excel("FMKIO_InputDig")
        InAna_astr       = cls.code_gen.get_array_from_excel("FMKIO_InputAna")
        InEvnt_astr      = cls.code_gen.get_array_from_excel("FMKIO_InputEvnt")
        InFreq_astr      = cls.code_gen.get_array_from_excel("FMKIO_InputFreq")
        OutPWM_astr      = cls.code_gen.get_array_from_excel("FMKIO_OutputPwm")
        OutDig_astr      = cls.code_gen.get_array_from_excel("FMKIO_OutputDig")
        SigCan_astr      = cls.code_gen.get_array_from_excel('FMKIO_CanCfg')
        SigSerial_astr   = cls.code_gen.get_array_from_excel('FMKIO_SerialCfg')[1:]
        list_irqn_hdler  = cls.code_gen.get_array_from_excel('FMKIO_IRQNHandler')
        Descitpion_pwm_freq = ['GPIO_name','Pin_name','alternate function', 'Interrupt Line' ]

        sig_in_ana =  []
        sig_in_dig =  []
        sig_out_dig = []
        sig_out_pwm = []
        sig_in_freq = []
        sig_in_evnt = []
        enum_can = ''
        const_can = ''
        enum_serial = ''
        const_serial = ''
        enum_gpio = ""
        enum_pin = ""
        enum_InDig = ""
        enum_InAna = ""
        enum_InEvnt = ""
        enum_InFreq = ""
        enum_OutPWM = ""
        enum_OutDig = ""
        var_bsp_pin_map = ""
        var_InAna: str = ""
        var_InDig = ""
        var_InFreq = ""
        var_InEvnt= ""
        var_OutDig = ""
        var_OutPWM = ""
        switch_gpio = ""
        switch_gpio_rcc  = ""
        func_irqn = ''
        gpio_enable_clk = "/**< Variable to store the state of GPIO Clock */\nt_eFMKCPU_ClockPortOpe g_IsGpioClockEnable_ae[FMKIO_GPIO_PORT_NB] = {\n"

        enum_suffix_a: List[str] = []
        enum_description = ""
        element_description_a:  List[str] = []
        # this pin are usually used by hardware
        stm_pin = ["PC14", "PC15"]
        stm_tim_chnl:List = FMKCPU_CodeGen.get_tim_chnl_used()
        max_pin_per_gpio: int = 0
        #---------------------------------------------------
        #-----------------make GPIO enum--------------------
        #---------------------------------------------------
        enum_description += "List of gpio port available on this board"
        for gpio_a in gpio_astr:
            #                  only take the gpio letter
            gpio_letter = str(gpio_a[0])[5:]
            enum_suffix_a.append(gpio_letter)
            element_description_a.append(f"Reference to bsp gpio {gpio_letter} register")
            # find the max pin in gpio register
            try:
                if(int(gpio_a[1]) > max_pin_per_gpio):
                    max_pin_per_gpio = int(gpio_a[1])
            except:
                raise TypeError("An error occured -> Number of pin column must be a integer")
            
            # Make switch case GPIO
            switch_gpio += f"            case {ENUM_GPIO_PORT_ROOT}_{gpio_letter}:\n" \
                            + f"                *f_BspGpio_ps = GPIO{gpio_letter};\n" \
                            + f"                break;\n"

            # Make switch case to found Rcc Clock from gpio Enum
            switch_gpio_rcc += f'            case {ENUM_GPIO_PORT_ROOT}_{gpio_letter}:\n' \
                            + f'                gpioClkPort_e = {ENUM_FMKCPU_RCC_ROOT}_GPIO{str(gpio_letter).upper()};\n' \
                            + '                break;\n'
            
            # Make GPIO clock default value
            gpio_enable_clk += f"    FMKCPU_CLOCKPORT_OPE_DISABLE, // {ENUM_GPIO_PORT_ROOT}_{gpio_letter}\n"
        gpio_enable_clk += "};\n\n"
        enum_gpio = cls.code_gen.make_enum_from_variable(ENUM_GPIO_PORT_ROOT, enum_suffix_a, 
                                                          "t_eFMKIO_GpioPort", 0, enum_description, 
                                                           element_description_a)
        
        enum_suffix_a = []
        #---------------------------------------------------
        #-----------------make Pin enum---------------------
        #---------------------------------------------------
        pin_list = [value for value in range(0, max_pin_per_gpio)]
        enum_pin = cls.code_gen.make_enum_from_variable(ENUM_GPIO_PIN_ROOT, pin_list,
                                                            "t_eFMKIO_BspGpioPin", 0,
                                                              "List of Pin available for each GPIO on this board", 
                                                              [f"Reference to bsp gpio pin {pin}" for pin in pin_list])
    
        #----------------------------------------------------------------
        #-----------------------------Make IRQNHandler-------------------
        #----------------------------------------------------------------
        for exti_irqn in list_irqn_hdler[1:]:
            func_irqn += '/*********************************\n' \
                        + f' * {exti_irqn[0]}\n' \
                        + '*********************************/\n' \
                        + f'void {exti_irqn[0]}(void)' \
                        + " " * (42 - len(f'void {exti_irqn[0]}(void)')) \
                        + '{' + 'return s_FMKIO_BspRqst_InterruptMngmt();' + '}\n\n'
                        

        #---------------------------------------------------------------
        #-----------------make Pin mapping variable---------------------
        #---------------------------------------------------------------
        var_bsp_pin_map += "    /**< Variable for bsp_enum pin mapping */\n" \
                            + "    const t_uint32 c_BspPinMapping_ua16[FMKIO_GPIO_PIN_NB] = {\n"
        for idx,pin in enumerate(pin_list):
            var_bsp_pin_map += f"        GPIO_PIN_{pin},"  \
                                + " " * (SPACE_VARIABLE - len(f"    GPIO_PIN_{pin},")) \
                                + f"// {ENUM_GPIO_PIN_ROOT}_{idx}\n"

        var_bsp_pin_map += "    };\n\n"

        
        #-----------------------------------------------------------
        #-----------------make InAna cfg variable-------------------
        #-----------------------------------------------------------
        var_InAna += "    /**< Variable for bsp_Gpio_Pin, adc coonfig Analog input signal mapping */\n" \
                    + "    const t_sFMKIO_AnaAdcCfg c_InAnaSigBspMap_as[FMKIO_INPUT_SIGANA_NB] = {\n"
        # make description 
        var_InAna += "        //" 
        for elem_desc in InAna_astr[0]:
            var_InAna += f"{elem_desc}" + " " * (SPACE_VARIABLE - len(elem_desc))
        var_InAna += "\n"

        for idx, pin_ana_cfg in enumerate(InAna_astr[1:]):
            sig_name = f'P{pin_ana_cfg[0][5:]}{pin_ana_cfg[1][4:]}'
            if sig_name in stm_pin:
                raise GPIO_AlreadyConfgigured(f"{sig_name} has already been configured") 

            sig_in_ana.append(sig_name)
            stm_pin.append(sig_name)
            # make const variable     
            var_InAna += "        {{" \
                        + f"{ENUM_GPIO_PORT_ROOT}_{pin_ana_cfg[0][5:]}," \
                        + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{pin_ana_cfg[0][5:]}")) \
                        + f"{ENUM_GPIO_PIN_ROOT}_{pin_ana_cfg[1][4:]}" + "}," \
                        + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PIN_ROOT}_{pin_ana_cfg[1][5:]}")) \
                        + f"{ENUM_ADC_ISCT_ROOT}_{pin_ana_cfg[2][4:]}," \
                        + " " * (SPACE_VARIABLE - len(f"{ENUM_ADC_ISCT_ROOT}_{pin_ana_cfg[2][4:]}")) \
                        + f"{ENUM_ADC_CHNL_ROOT}_{pin_ana_cfg[3][12:]}" \
                        + "}," + " " * (5 - len(f"{pin_ana_cfg[3][9:]}")) \
                        + f"// {ENUM_INSIGANA_ROOT}_{idx + 1};\n"
        var_InAna += "    };\n\n"
        #-----------------------------------------------------------
        #-----------------make InDig cfg variable-------------------
        #-----------------------------------------------------------
        var_InDig += "    /**< Variable for bsp_Gpio_Pin Digital input signal mapping */\n" \
                    + "    const t_sFMKIO_BspSigCfg c_InDigSigBspMap_as[FMKIO_INPUT_SIGDIG_NB] = {\n"
        # make description 
        var_InDig += "        //" 
        for elem_desc in InDig_astr[0]:
            var_InDig += f"{elem_desc}" + " " * (SPACE_VARIABLE - len(elem_desc))
        var_InDig += "\n"

        for idx, pin_dig_cfg in enumerate(InDig_astr[1:]):
            sig_name = f'P{pin_dig_cfg[0][5:]}{pin_dig_cfg[1][4:]}'
            if sig_name in stm_pin:
                raise GPIO_AlreadyConfgigured(f"{sig_name} has already been configured") 
            
            sig_in_dig.append(sig_name)
            stm_pin.append(sig_name)
            var_InDig +="        {"\
                        + f"{ENUM_GPIO_PORT_ROOT}_{pin_dig_cfg[0][5:]}," \
                        + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{pin_dig_cfg[0][5:]}")) \
                        + f"{ENUM_GPIO_PIN_ROOT}_{pin_dig_cfg[1][4:]}" + "}," \
                        + " " * (5 - len(f"{pin_dig_cfg[1][4:]}")) \
                        + f"// {ENUM_INSIGDIG_ROOT}_{idx + 1},\n"
        var_InDig += "    };\n\n"
        #-----------------------------------------------------------
        #-----------------make InFreq cfg variable-------------------
        #-----------------------------------------------------------
        var_InFreq += "    /**< Variable for bsp_Gpio_Pin frequency input signal mapping */\n" \
                    + "    const t_sFMKIO_BspTimerSigCfg c_InFreqSigBspMap_as[FMKIO_INPUT_SIGFREQ_NB] = {\n"
        # make description 
        var_InFreq += "        //" 
        
        for elem_desc in Descitpion_pwm_freq:
            var_InFreq += f"{elem_desc}" + " " * (SPACE_VARIABLE - len(elem_desc))
        var_InFreq += "\n"

        for idx, pin_freq_cfg in enumerate(InFreq_astr[1:]):
            sig_name = f'P{pin_freq_cfg[0][5:]}{pin_freq_cfg[1][4:]}'
            if sig_name in stm_pin:
                raise GPIO_AlreadyConfgigured(f"{pin_freq_cfg[5]} has already been configured")
            
            if str(pin_freq_cfg[3] + pin_freq_cfg[4]) in stm_tim_chnl:
                raise TimerCfg_alreadyUsed(f" the timer {pin_freq_cfg[3]} and his channel {pin_freq_cfg[4]} has already been configured")

            sig_in_freq.append(sig_name)
            stm_tim_chnl.append(str(pin_freq_cfg[3]+pin_freq_cfg[4]))
            stm_pin.append(sig_name)
            # get IT Line                                     FMKCPU_TIMER_X                                         FMKCPU_CHANNEL_X
            itline = FMKCPU_CodeGen.get_itline_from_timcnl(f'{ENUM_FMKCPU_TIMER_ROOT}_{pin_freq_cfg[3][6:]}', f'{ENUM_FMKCPU_CHANNEL_ROOT}_{pin_freq_cfg[4][8:]}')
            var_InFreq += "        {" + "{" \
                    + f"{ENUM_GPIO_PORT_ROOT}_{pin_freq_cfg[0][5:]}," \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{pin_freq_cfg[0][5:]}")) \
                    + f"{ENUM_GPIO_PIN_ROOT}_{pin_freq_cfg[1][4:]}" + "}," \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PIN_ROOT}_{pin_freq_cfg[1][4:]}")) \
                    + f"{pin_freq_cfg[2]}," \
                    + " " * (SPACE_VARIABLE - len(f"{pin_freq_cfg[2]}")) \
                    + str(itline) \
                    + "}," +  " " * (5 - len(f"{pin_freq_cfg[4][8:]}")) \
                    + f"// {ENUM_INSIGFREQ_ROOT}_{idx + 1},\n" 
        var_InFreq += "    };\n\n" 
        #-----------------------------------------------------------
        #-----------------make InEvnt cfg variable-------------------
        #-----------------------------------------------------------
        var_InEvnt += "    /**< Variable for bsp_Gpio_Pin frequency input signal mapping */\n" \
                    + "    const t_sFMKIO_BspEvntSigCfg c_InEvntSigBspMap_as[FMKIO_INPUT_SIGEVNT_NB] = {\n"
        # make description 
        var_InEvnt += "        //" 
        for elem_desc in InEvnt_astr[0]:
            var_InEvnt += f"{elem_desc}" + " " * (SPACE_VARIABLE - len(elem_desc))
        var_InEvnt += "\n"

        for idx, pin_evnt_cfg in enumerate(InEvnt_astr[1:]):
            sig_name = f'P{pin_evnt_cfg[0][5:]}{pin_evnt_cfg[1][4:]}'
            if sig_name in stm_pin:
                raise GPIO_AlreadyConfgigured(f"{pin_evnt_cfg[3]} has already been configured")
            
            sig_in_evnt.append(sig_name)
            stm_pin.append(sig_name)
            var_InEvnt += "        {" + "{" \
                    + f"{ENUM_GPIO_PORT_ROOT}_{pin_evnt_cfg[0][5:]}," \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{pin_evnt_cfg[0][5:]}")) \
                    + f"{ENUM_GPIO_PIN_ROOT}_{pin_evnt_cfg[1][4:]}" + "}," \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PIN_ROOT}_{pin_evnt_cfg[1][4:]}")) \
                    + f"{ENUM_FMKCPU_NVIC_ROOT}_{str(pin_evnt_cfg[2]).upper()}" \
                    + "}," +  " " * (25 - len(f"{pin_evnt_cfg[2]}")) \
                    + f"// {ENUM_INSIGEVNT_ROOT}_{idx + 1},\n"
        var_InEvnt += "    };\n\n"

        #-----------------------------------------------------------
        #-----------------make OutPWM cfg variable-------------------
        #-----------------------------------------------------------
        var_OutPWM += "    /**< Variable for bsp_Gpio_Pin PWM output signal mapping */\n" \
                    + "    const t_sFMKIO_BspTimerSigCfg c_OutPwmSigBspMap_as[FMKIO_OUTPUT_SIGPWM_NB] = {\n"
        # make description 
        var_OutPWM += "        //" 
        for elem_desc in Descitpion_pwm_freq:
            var_OutPWM += f"{elem_desc}" + " " * (SPACE_VARIABLE - len(elem_desc))
        var_OutPWM += "\n"

        for idx, pin_pwm_cfg in enumerate(OutPWM_astr[1:]):
            sig_name = f'P{pin_pwm_cfg[0][5:]}{pin_pwm_cfg[1][4:]}'
            if sig_name in stm_pin:
                raise GPIO_AlreadyConfgigured(f"{pin_pwm_cfg[5]} has already been configured")
            if str(pin_pwm_cfg[3]+pin_pwm_cfg[4]) in stm_tim_chnl:
                raise TimerCfg_alreadyUsed(f" the timer {pin_pwm_cfg[3]} and his channel {pin_pwm_cfg[4]} has already been configured")

            itline = FMKCPU_CodeGen.get_itline_from_timcnl(f'{ENUM_FMKCPU_TIMER_ROOT}_{pin_pwm_cfg[3][6:]}', f'{ENUM_FMKCPU_CHANNEL_ROOT}_{pin_pwm_cfg[4][8:]}')

            sig_out_pwm.append(sig_name)
            stm_tim_chnl.append(str(pin_pwm_cfg[3]+pin_pwm_cfg[4]))
            stm_pin.append(sig_name)

            var_OutPWM += "        {" + "{" \
                    + f"{ENUM_GPIO_PORT_ROOT}_{pin_pwm_cfg[0][5:]}," \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{pin_pwm_cfg[0][5:]}")) \
                    + f"{ENUM_GPIO_PIN_ROOT}_{pin_pwm_cfg[1][4:]}" + "}," \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PIN_ROOT}_{pin_pwm_cfg[1][4:]}")) \
                    + f"{pin_pwm_cfg[2]}," \
                    + " " * (SPACE_VARIABLE - len(f"{pin_pwm_cfg[2]}")) \
                    + str(itline) \
                    + "}," +  " " * (5 - len(f"{pin_pwm_cfg[4][8:]}")) \
                    + f"// {ENUM_OUTSIGPWM_ROOT}_{idx + 1},\n"
        var_OutPWM += "    };\n\n" 
        #-----------------------------------------------------------
        #-----------------make OutDig cfg variable-------------------
        #-----------------------------------------------------------
        var_OutDig += "    /**< Variable for bsp_Gpio_Pin Digital ouput signal mapping */\n" \
                    + "    const t_sFMKIO_BspSigCfg c_OutDigSigBspMap_as[FMKIO_OUTPUT_SIGDIG_NB] = {\n"
        # make description 
        var_OutDig += "        //" 
        for elem_desc in OutDig_astr[0]:
            var_OutDig += f"{elem_desc}" + " " * (SPACE_VARIABLE - len(elem_desc))
        var_OutDig += "\n"
        for idx, pin_dig_cfg in enumerate(OutDig_astr[1:]):
            sig_name = f'P{pin_dig_cfg[0][5:]}{pin_dig_cfg[1][4:]}'
            if sig_name in stm_pin:
                    raise GPIO_AlreadyConfgigured(f"{pin_dig_cfg[2]} has already been configured")
            
            sig_out_dig.append(sig_name)
            stm_pin.append(sig_name)
            var_OutDig += "        {"\
                        + f"{ENUM_GPIO_PORT_ROOT}_{pin_dig_cfg[0][5:]}," \
                        + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{pin_dig_cfg[0][5:]}")) \
                        + f"{ENUM_GPIO_PIN_ROOT}_{pin_dig_cfg[1][4:]}" + "}," \
                        + " " * (5 - len(f"{pin_dig_cfg[1][4:]}")) \
                        + f"// {ENUM_OUTSIGDIG_ROOT}_{idx + 1},\n"
        var_OutDig += "    };\n\n"
        #-----------------------------------------------------------
        #-----------------make Serial cfg--------------------------
        #-----------------------------------------------------------
        const_serial += '    /**< Variable for RxTx Reference for Serial Line */\n'
        const_serial += f'    const t_sFMKIO_RxTxComCfg c_FmkIo_SerialSigCfg_as[{ENUM_FMKIO_SERIAL_ROOT}_NB] =' + '{\n'
        const_serial += '        // Rx Gpio Port                        Rx Pin                       Tx Gpio Port                      Tx Pin                    Alternate Function\n'
        serial_sig = []

        for idx, serial_cfg in enumerate(SigSerial_astr):
            RxPin = str(f"P{serial_cfg[0][5:]}{serial_cfg[1][4:]}")
            TxPin = str(f"P{serial_cfg[2][5:]}{serial_cfg[3][4:]}")
            if (RxPin in stm_pin 
            or TxPin in stm_pin):
                raise GPIO_AlreadyConfgigured(f"{RxPin} or {TxPin} has already been configured")
            
            serial_sig.append([RxPin, TxPin])
            stm_pin.append(TxPin)
            stm_pin.append(RxPin)

            const_serial += '        {' + '{' + f'{ENUM_GPIO_PORT_ROOT}_{serial_cfg[0][5:]},' \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{serial_cfg[0][5:]}")) \
                    + f"{ENUM_GPIO_PIN_ROOT}_{serial_cfg[1][4:]}" + "}," \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PIN_ROOT}_{serial_cfg[1][4:]}")) \
                    + '{' + f'{ENUM_GPIO_PORT_ROOT}_{serial_cfg[2][5:]},'\
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{serial_cfg[2][5:]}")) \
                    + f"{ENUM_GPIO_PIN_ROOT}_{serial_cfg[3][4:]}" + "}," \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{serial_cfg[3][5:]}")) \
                    + f'{serial_cfg[4]}' + '},' + f' // {ENUM_FMKIO_SERIAL_ROOT}_{(idx + 1)}' \
                    + '\n'
        const_serial += '    };\n'
        #-----------------------------------------------------------
        #-----------------make can cfg------------------------------
        #-----------------------------------------------------------
        const_can += '    /**< Variable for RxTx Reference for Can Node */\n'
        const_can += f'    const t_sFMKIO_RxTxComCfg c_FmkIo_CanSigCfg_as[{ENUM_FMKIO_CAN_ROOT}_NB] =' + '{\n'
        const_can += '        // Rx Gpio Port                        Rx Pin                       Tx Gpio Port                      Tx Pin                    Alternate Function\n'
        can_sig = []
        for idx, can_cfg in enumerate(SigCan_astr[1:]):
            RxPin = str(f"P{can_cfg[0][5:]}{can_cfg[1][4:]}")
            TxPin = str(f"P{can_cfg[2][5:]}{can_cfg[3][4:]}")
            if (RxPin in stm_pin 
            or TxPin in stm_pin):
                raise GPIO_AlreadyConfgigured(f"{RxPin} or {TxPin} has already been configured")
            
            can_sig.append([RxPin, TxPin])
            stm_pin.append(TxPin)
            stm_pin.append(RxPin)
            
            const_can += '        {' + '{' + f'{ENUM_GPIO_PORT_ROOT}_{can_cfg[0][5:]},' \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{can_cfg[0][5:]}")) \
                    + f"{ENUM_GPIO_PIN_ROOT}_{can_cfg[1][4:]}" + "}," \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PIN_ROOT}_{can_cfg[1][4:]}")) \
                    + '{' + f'{ENUM_GPIO_PORT_ROOT}_{can_cfg[2][5:]},'\
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{can_cfg[2][5:]}")) \
                    + f"{ENUM_GPIO_PIN_ROOT}_{can_cfg[3][4:]}" + "}," \
                    + " " * (SPACE_VARIABLE - len(f"{ENUM_GPIO_PORT_ROOT}_{can_cfg[3][5:]}")) \
                    + f'{can_cfg[4]}' + '},' + f' // {ENUM_FMKIO_CAN_ROOT}_{(idx + 1)}' \
                    + '\n'
        const_can += '    };\n'
        #-----------------------------------------------------------
        #----------------------make enum signal---------------------
        #-----------------------------------------------------------
        enum_can = cls.code_gen.make_enum_from_variable(ENUM_FMKIO_CAN_ROOT, [str(idx+1) for idx in range(len(SigCan_astr[1:]))],
                                                        't_eFMKIO_ComSigCan', 0, 'List of signals used for CAN communication',
                                                        [f'Rx -> {value[0]}, Tx -> {value[1]}, Reference to CAN {idx}' for idx,value in enumerate(can_sig)])
        
        enum_serial = cls.code_gen.make_enum_from_variable(ENUM_FMKIO_SERIAL_ROOT, [str(idx+1) for idx in range(len(SigSerial_astr))],
                                                        't_eFMKIO_ComSigSerial', 0, 'List of signals used for Serial communication',
                                                        [f'Rx -> {value[0]}, Tx -> {value[1]}, Reference to Serial {SigSerial_astr[idx][5]}' for idx,value in enumerate(serial_sig)])
        
        enum_InAna = cls.code_gen.make_enum_from_variable(ENUM_INSIGANA_ROOT, [str(idx + 1) for idx in range((len(InAna_astr[1:])))],
                                                            "t_eFMKIO_InAnaSig", 0, "List of input Analog pin available on this board",
                                                            [f'Reference to {sig_name}' for sig_name in sig_in_ana])
        
        enum_InDig = cls.code_gen.make_enum_from_variable(ENUM_INSIGDIG_ROOT, [str(idx + 1) for idx in range((len(InDig_astr[1:])))],
                                                            "t_eFMKIO_InDigSig", 0, "/List of input digital pin available on this board",
                                                            [f'Reference to {sig_name}' for sig_name in sig_in_dig])
        
        enum_InFreq = cls.code_gen.make_enum_from_variable(ENUM_INSIGFREQ_ROOT, [str(idx + 1) for idx in range((len(InFreq_astr[1:])))],
                                                            "t_eFMKIO_InFreqSig", 0, "List of input frequency pin available on this board",
                                                            [f'Reference to {sig_name}' for sig_name in sig_in_freq])
        
        enum_InEvnt = cls.code_gen.make_enum_from_variable(ENUM_INSIGEVNT_ROOT, [str(idx + 1) for idx in range((len(InEvnt_astr[1:])))],
                                                            "t_eFMKIO_InEvntSig", 0, "List of input event pin available on this board",
                                                            [f'Reference to {sig_name}' for sig_name in sig_in_evnt])
        
        enum_OutDig = cls.code_gen.make_enum_from_variable(ENUM_OUTSIGDIG_ROOT, [str(idx + 1) for idx in range((len(OutDig_astr[1:])))],
                                                            "t_eFMKIO_OutDigSig", 0, "List of output digital pin available on this board",
                                                            [f'Reference to {sig_name}' for sig_name in sig_out_dig])
        
        enum_OutPWM = cls.code_gen.make_enum_from_variable(ENUM_OUTSIGPWM_ROOT, [str(idx + 1) for idx in range((len(OutPWM_astr[1:])))],
                                                            "t_eFMKIO_OutPwmSig", 0, "List of output PWM pin available on this board",
                                                            [f'Reference to {sig_name}' for sig_name in sig_out_pwm])
       
        #-----------------------------------------------------------
        #------------code genration for FMKIO module----------------
        #-----------------------------------------------------------
        # for FMKIO Config Private 
        print("\t- For configPrivate file")
        cls.code_gen.change_target_balise(TARGET_T_VARIABLE_START_LINE,TARGET_T_VARIABLE_END_LINE)
        print('\t\t- configuration for Serial signals')
        cls.code_gen._write_into_file(const_serial, FMKIO_CONFIGPRIVATE_PATH)
        print('\t\t- configuration for CAN signals')
        cls.code_gen._write_into_file(const_can, FMKIO_CONFIGPRIVATE_PATH)
        print("\t\t- configuration for PWN output signal")
        cls.code_gen._write_into_file(var_OutPWM, FMKIO_CONFIGPRIVATE_PATH)
        print("\t\t- configuration for Digital output signal")
        cls.code_gen._write_into_file(var_OutDig, FMKIO_CONFIGPRIVATE_PATH)
        print("\t\t- configuration for event Input signal")
        cls.code_gen._write_into_file(var_InEvnt, FMKIO_CONFIGPRIVATE_PATH)
        print("\t\t- configuration for Frequency Input signal")
        cls.code_gen._write_into_file(var_InFreq, FMKIO_CONFIGPRIVATE_PATH)
        print("\t\t- configuration for Analog Input signal")
        cls.code_gen._write_into_file(var_InAna, FMKIO_CONFIGPRIVATE_PATH)
        print("\t\t- configuration for Digital Input signal")
        cls.code_gen._write_into_file(var_InDig, FMKIO_CONFIGPRIVATE_PATH)
        print("\t\t- variable for stm32_framework pin mapping")
        cls.code_gen._write_into_file(var_bsp_pin_map, FMKIO_CONFIGPRIVATE_PATH)
        print("\t- For configPublic file")
        # for FMKIO Config public
        cls.code_gen.change_target_balise(TARGET_T_ENUM_START_LINE, TARGET_T_ENUM_END_LINE)
        print('\t\t- enum for Serial Communication')
        cls.code_gen._write_into_file(enum_serial, FMKIO_ConfigPublic_PATH)
        print('\t\t- enum for CAN Communication')
        cls.code_gen._write_into_file(enum_can, FMKIO_ConfigPublic_PATH)
        print("\t\t- enum for PWM output signal")
        cls.code_gen._write_into_file(enum_OutPWM, FMKIO_ConfigPublic_PATH)
        print("\t\t- enum for Digital output signal")
        cls.code_gen._write_into_file(enum_OutDig, FMKIO_ConfigPublic_PATH)
        print("\t\t- enum for Event input signal")
        cls.code_gen._write_into_file(enum_InEvnt, FMKIO_ConfigPublic_PATH)
        print("\t\t- enum for Frequency input signal")
        cls.code_gen._write_into_file(enum_InFreq, FMKIO_ConfigPublic_PATH)
        print("\t\t- enum for Analog input signal")
        cls.code_gen._write_into_file(enum_InAna, FMKIO_ConfigPublic_PATH)
        print("\t\t- enum for Digital input signal")
        cls.code_gen._write_into_file(enum_InDig, FMKIO_ConfigPublic_PATH)
        print("\t\t- enum for pin signal")
        cls.code_gen._write_into_file(enum_pin, FMKIO_ConfigPublic_PATH)
        print("\t\t- enum for GPIO available for this stm")
        cls.code_gen._write_into_file(enum_gpio, FMKIO_ConfigPublic_PATH)

        # for FMKIO
        print("\t- For FMKIO.c file")
        cls.code_gen.change_target_balise(TARGET_BALISE_SWITCH_GPIO_START, TARGET_BALISE_SWITCH_GPIO_END)
        print("\t\t- switch case to found stm GPIO from enum")
        cls.code_gen._write_into_file(switch_gpio, FMKIO_PATH)

        cls.code_gen.change_target_balise(TARGET_SWITCH_GPIO_RCC_START, TARGET_SWITCH_GPIO_RCC_END)
        print("\t\t- switch case to found Rcc clock for a GPIO")
        cls.code_gen._write_into_file(switch_gpio_rcc, FMKIO_PATH)

        cls.code_gen.change_target_balise(TARGET_T_VARIABLE_START_LINE[4:], TARGET_T_VARIABLE_END_LINE[4:])
        print("\t\t- variable for GPIO enum")
        cls.code_gen._write_into_file(gpio_enable_clk, FMKIO_PATH)

        print('\t\t- Exti IRQN Handler')
        cls.code_gen.change_target_balise(TARGET_EXTI_X_IRQN_START, TARGET_EXTI_X_IRQN_END)
        cls.code_gen._write_into_file(func_irqn, FMKIO_PATH)
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<End code generation for FMFIO Module>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
#------------------------------------------------------------------------------
#                             FUNCTION IMPLMENTATION
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#			                MAIN
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#		                    END OF FILE
#------------------------------------------------------------------------------
#--------------------------
# Function_name
#--------------------------

"""
    @brief
    @details

    @params[in]
    @params[out]
    @retval
"""

