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
#------------------------------------------------------------------------------
#                                       CONSTANT
#------------------------------------------------------------------------------
TARGET_TIMER_INFO_START = "/* CAUTION : Automatic generated code section for Timer Configuration: Start */\n"
TARGET_TIMER_INFO_END   = "/* CAUTION : Automatic generated code section for Timer Configuration: End */\n"
TARGET_TIMER_NVIC_NB_START = "    /* CAUTION : Automatic generated code section for NVIC Number: Start */\n"
TARGET_TIMER_NVIC_NB_END   = "    /* CAUTION : Automatic generated code section for NVIC Number: End */\n"
TARGET_c_clock_eNABLE_IMPL_START  = "/* CAUTION : Automatic generated code section for Enable Clk Implementation: Start */\n"
TARGET_c_clock_eNABLE_IMPL_END    = "/* CAUTION : Automatic generated code section for Enable Clk Implementation: End */\n"
TARGET_CLOCK_DISABLE_IMPL_START = "/* CAUTION : Automatic generated code section for Disable Clk Implementation: Start */\n"
TARGET_CLOCK_DISABLE_IMPL_END   = "/* CAUTION : Automatic generated code section for Disable Clk Implementation: End */\n"
TARGET_c_clock_eNABLE_DECL_START  = "    /* CAUTION : Automatic generated code section for Enable Clk Declaration: Start */\n"
TARGET_c_clock_eNABLE_DECL_END    = "    /* CAUTION : Automatic generated code section for Enable Clk Declaration: End */\n"
TARGET_CLOCK_DISABLE_DECL_START = "    /* CAUTION : Automatic generated code section for Disable Clk Declaration: Start */\n"
TARGET_CLOCK_DISABLE_DECL_END   = "    /* CAUTION : Automatic generated code section for Disable Clk Declaration: End */\n"
TARGET_SWITCH_NVIC_START = "            /* CAUTION : Automatic generated code section for IRQNType switch case: Start */\n"
TARGET_SWITCH_NVIC_END   = "            /* CAUTION : Automatic generated code section for IRQNType switch case: End */\n"
TARGET_TIMER_CHNLNB_START = "    /* CAUTION : Automatic generated code section for Timer channels number: Start */\n"
TARGET_TIMER_CHNLNB_END   = "    /* CAUTION : Automatic generated code section for Timer channels number: End */\n"
TARGET_TIMER_X_IRQH_START = "/* CAUTION : Automatic generated code section for TIMx IRQHandler: Start */\n"
TARGET_TIMER_X_IRQH_END = "/* CAUTION : Automatic generated code section for TIMx IRQHandler: End */\n"
TARGET_CPU_CFG_START = "    /* CAUTION : Automatic generated code section for CPU Configuration: Start */\n"
TARGET_CPU_CFG_END = "    /* CAUTION : Automatic generated code section for CPU Configuration: End */\n"
# CAUTION : Automatic generated code section: Start #

# CAUTION : Automatic generated code section: End #
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------
class TimerCfg_alreadyUsed(Exception):
    pass

class FMKCPU_CodeGen():
    """
            Make code generation for FMKCPU module which include 
            file FMKCPU_ConfigPublic.h : 
               - Enum nUmber max of channel timer  x
               - Enum timer list                   x
               - Enum Event channel                x
               - Enum Rcc Clock                    x
               - Enum NVIC                         x
            
            file FMKCPU_ConfigPrivate.h :
                - variable NVIC prioirty           x
                - define number of IRQN            x
                - Variable clock enable            x
                - Variable Event timer cfg         x
            
            file  FMK_CPU_ConfigSpecififc.c
                - enable/ disable clock implementation  x

            file  FMK_CPU_ConfigSpecififc.h
                - -enable/ disable clock declaration    x

            file  FMK_CPU.c
                - variable g_timerInfo_as init          x  
                - switch case IRQN to bsp IRQN          x
                - hardware IRQNHandler for timer        
        """
    itline_timchnl_mapping:Dict[str, List[str]] = {}
    code_gen = LCFE()
    stm_tim_chnl = []
    #-------------------------
    # code_generation
    #-------------------------
    @classmethod
    def code_generation(cls, f_hw_cfg) -> None:
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<Start code generation for FmkCpu Module>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        cls.code_gen.load_excel_file(f_hw_cfg)
        irqn_cfg_a    = cls.code_gen.get_array_from_excel("GI_IRQN")
        timer_cfg_a   = cls.code_gen.get_array_from_excel("GI_Timer")
        rcclock_cfg_a = cls.code_gen.get_array_from_excel("GI_RCC_CLOCK")
        evnt_cfg_a    = cls.code_gen.get_array_from_excel("FMKCPU_EvntTimer")
        cpu_cfg       = cls.code_gen.get_array_from_excel("CPU_Config")[1][0]

        print(cpu_cfg)
        
        enum_channel = ""
        enum_timer = ""
        enum_rcc = ""
        enum_nvic = ""
        enum_evnt = ""
        var_nvic_prio = ""
        var_clk_state = ""
        var_evntcfg   = ""
        rcc_ena_imple = ""
        rcc_dis_imple = ""
        rcc_ena_decl = ""
        rcc_dis_decl  = ""
        var_timinfo = ""
        const_mapp_evnt_tim = ""
        const_mapp_gp_tim = ""
        const_mapp_dac_tim = ""
        enum_it_lines_gp = ""
        enum_it_lines_dac = ""
        enum_it_lines_evnt = ""
        func_imple = ""
        def_tim_max_chnl = ""
        var_tim_max_chnl = ""
        switch_irqn = ""
        max_channel: int = 0
        include_cpu = ""
        nb_evnt_channel = len(evnt_cfg_a[1:])
        timer_number_a = []
        #----------------------------------------------------------------
        #-----------------------------make cpu include-------------------
        #----------------------------------------------------------------
        # only takes tha family for include function
        cpu_function = f'    #include "{str(cpu_cfg)[:7]}xx_hal.h"\n'
        include_cpu_hw = f'    #include "{cpu_cfg}.h"\n'
        include_cpu = cpu_function + include_cpu_hw
        #----------------------------------------------------------------
        #-----------------------------make rcc enum----------------------
        #-----------------------------------------------------------------
        enum_rcc = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_RCC_ROOT, [str(rcclock_cfg[0]) for rcclock_cfg in rcclock_cfg_a[1:]], 
                                                            "t_eFMKCPU_ClockPort", 0, 
                                                            "Enum for rcc clock state reference",
                                                            [f'Reference to RCC Clock {rcclock_cfg[0]}' for rcclock_cfg in rcclock_cfg_a[1:]])
        #----------------------------------------------------------------
        #----------make rcc implementation/Declaration--------------------
        #-----------------------------------------------------------------
        var_clk_state += "    /**< Referencing all Enable/Disable Rcc clock function */\n" \
                        + "    const t_sFMKCPU_ClkFunc c_FMKCPU_ClkFunctions_apcb[FMKCPU_NVIC_NB] = {\n"
        var_clk_state += "      //" 
        for elem_desc in evnt_cfg_a[0]:
            var_clk_state += f"{elem_desc}" + " " * (SPACE_VARIABLE - len(elem_desc))
        var_clk_state += "\n"
        for rccclock_cfg in rcclock_cfg_a[1:]:
            rcc_ena_imple += f"/**< Function to enable {rccclock_cfg[0]} rcc clock*/\n"
            rcc_ena_imple += f"void FMKCPU_Enable_{rccclock_cfg[0]}_Clock(void) " \
                            + "{" + f"__HAL_RCC_{rccclock_cfg[0]}_CLK_ENABLE();" + "}\n"
            
            
            rcc_dis_imple += f"/**< Function to disable {rccclock_cfg[0]} rcc clock*/\n"
            rcc_dis_imple += f"void FMKCPU_Disable_{rccclock_cfg[0]}_Clock(void) " \
                            + "{" + f"__HAL_RCC_{rccclock_cfg[0]}_CLK_DISABLE();" + "}\n"
            
            rcc_ena_decl += f"    /**< Function to enable  {rccclock_cfg[0]} rcc clock*/\n"
            rcc_ena_decl +=  f"    void FMKCPU_Enable_{rccclock_cfg[0]}_Clock(void);\n"

            rcc_dis_decl += f"    /**< Function to disable {rccclock_cfg[0]} rcc clock*/\n"
            rcc_dis_decl  +=  f"    void FMKCPU_Disable_{rccclock_cfg[0]}_Clock(void);\n"

            var_clk_state += "        {" \
                            + f"FMKCPU_Enable_{rccclock_cfg[0]}_Clock," \
                            + " " * (SPACE_VARIABLE - len(f"FMKCPU_Enable_{rccclock_cfg[0]}_Clock")) \
                            + f"FMKCPU_Disable_{rccclock_cfg[0]}_Clock" \
                            + "}," + " " * (SPACE_VARIABLE - len(f"FMKCPU_Disable_{rccclock_cfg[0]}_Clock")) \
                            + f"// {ENUM_FMKCPU_RCC_ROOT}_{rccclock_cfg[0]}\n"
            
        var_clk_state += "    };\n\n"
        #----------------------------------------------------------------
        #-----------------------------make timer enum--------------------
        #-----------------------------------------------------------------
        suffix_dac_tim = []
        suffix_evnt_tim = []
        idx_tim_pg = 1
        idx_tim_evnt = 1
        idx_dac_tim = 1
        description_pg_tim   = []
        description_dac_tim  = []
        description_evnt_tim = []
        suffix_pg_tim = []
        var_timinfo += "/**< timer information variable */\n" \
                    + "t_sFMKCPU_TimerInfo g_TimerInfo_as[FMKCPU_TIMER_NB] = {\n"
        var_tim_max_chnl += "    /**< timer max channel variable */\n" \
                            + "    const t_uint8 c_FMKCPU_TimMaxChnl_ua8[FMKCPU_TIMER_NB] = {\n"
        
        const_mapp_gp_tim += "    /**< General Purpose Timer Channel Mapping */\n" \
                            + f"    t_sFMKCPU_BspTimerCfg c_FmkCpu_ITLineIOMapp_as[{ENUM_FMKCPU_IT_GP_ROOT}_NB] = " \
                            + "{\n"
        const_mapp_evnt_tim += "    /**< Event Purpose Timer Channel Mapping */\n" \
                            + f"    t_sFMKCPU_BspTimerCfg c_FmkCpu_ITLineEvntMapp_as[{ENUM_FMKCPU_IT_EVNT_ROOT}_NB] = " \
                            + "{\n"
        const_mapp_dac_tim += "    /**< Dac Purpose Timer Channel Mapping */\n" \
                            + f"    t_sFMKCPU_BspTimerCfg c_FmkCpu_ITLineDacMapp_as[{ENUM_FMKCPU_IT_DAC_ROOT}_NB] = " \
                            + "{\n"

        for idx, timer_cfg in enumerate(timer_cfg_a[1:]):
            idx_timer = str(timer_cfg[0][6:])
            timer_number_a.append(idx_timer)
            if (timer_cfg[1] > max_channel):
                max_channel = timer_cfg[1]

            var_timinfo += "    {\n" \
                        + f"        // Timer_{idx_timer}\n" \
                        + f"        .BspTimer_ps.Instance = TIM{idx_timer},\n" \
                        + f"        .c_clock_e = {ENUM_FMKCPU_RCC_ROOT}_TIM{idx_timer},\n" \
                        + f"        .c_IRQNType_e = {ENUM_FMKCPU_NVIC_ROOT}_{str(timer_cfg[2]).upper()}" \
                        + "},\n"
            
            # make defines timer channel
            def_tim_max_chnl += f"    #define FMKCPU_MAX_CHNL_TIMER_{idx_timer} ((t_uint8){timer_cfg[1]})\n"

            # make varialble max timer channel 
            var_tim_max_chnl += f"        (t_uint8)FMKCPU_MAX_CHNL_TIMER_{idx_timer}," \
                                + " " * (SPACE_VARIABLE - len(f"FMKCPU_MAX_CHNL_TIMER_{idx_timer},")) \
                                + f"// {ENUM_FMKCPU_TIMER_ROOT}_{idx_timer}\n"  
                
            # Make hardware IRQ handler function impleementation  
            func_imple += f"void TIM{idx_timer}_IRQHandler(void)" \
                        + "{return HAL_TIM_IRQHandler(&g_TimerInfo_as" \
                        + f"[{ENUM_FMKCPU_TIMER_ROOT}_{idx_timer}].BspTimer_ps);" \
                        + "}\n"
            # make timer public enum 
            match  timer_cfg[3]:
                case 'PWM/IC/OC/OP':
                    
                    suffix_pg_tim.extend([f"{idx_tim_pg}{i}" for i in range(1, (timer_cfg[1] +1))])
                    description_pg_tim.extend(f"General Purpose Timer, Reference to Timer {idx_timer} Channel {channel}" for channel in range(1, (timer_cfg[1] +1)))
                    
                    for channel in range(1, (timer_cfg[1] +1)):
                        const_mapp_gp_tim += "        {" + f"{ENUM_FMKCPU_TIMER_ROOT}_{idx_timer},"  \
                                        + " " * (SPACE_VARIABLE - len(f"{ENUM_FMKCPU_TIMER_ROOT}_{idx_timer}")) \
                                        + f"        {ENUM_FMKCPU_CHANNEL_ROOT}_{channel}" \
                                            + "}," + f"    // {ENUM_FMKCPU_IT_GP_ROOT}_{idx_tim_pg}{channel}\n"
                        # for fmkio
                        cls.itline_timchnl_mapping[str(f"{ENUM_FMKCPU_TIMER_ROOT}_{idx_timer}{ENUM_FMKCPU_CHANNEL_ROOT}_{channel}")] =  f"{ENUM_FMKCPU_IT_GP_ROOT}_{idx_tim_pg}{channel}"
                    # update idx   
                    idx_tim_pg +=1
                    
                case 'DAC':
                    suffix_dac_tim.extend(f"{int(idx_dac_tim + i)}" for i in range(0, (timer_cfg[1])))
                    description_dac_tim.extend(f"Dac Purpose Timer, Reference to Timer {idx_timer} Channel {channel}" for channel in range(1, (timer_cfg[1] +1)))

                    for channel in range(1, (timer_cfg[1] +1)):
                        const_mapp_dac_tim += "        {" + f"{ENUM_FMKCPU_TIMER_ROOT}_{idx_timer},"  \
                                            + " " * (SPACE_VARIABLE - len(f"{ENUM_FMKCPU_TIMER_ROOT}_{idx_timer}")) \
                                            + f"        {ENUM_FMKCPU_CHANNEL_ROOT}_{channel}" \
                                            + "}," + f"    // {ENUM_FMKCPU_IT_DAC_ROOT}_{idx_dac_tim}\n"
                        # for fmkio
                        cls.itline_timchnl_mapping[str(f"{ENUM_FMKCPU_TIMER_ROOT}_{idx_timer}{ENUM_FMKCPU_CHANNEL_ROOT}_{channel}")] =  f"{ENUM_FMKCPU_IT_DAC_ROOT}_{idx_dac_tim}"
                    idx_dac_tim = idx_dac_tim + timer_cfg[1]

                case 'EVENT':
                    suffix_evnt_tim.extend(f"{int(idx_tim_evnt + i)}" for i in range(0, (timer_cfg[1])))
                    description_evnt_tim.extend(f"Event Purpose Timer, Reference to Timer {idx_timer} Channel {channel}" for channel in range(1, (timer_cfg[1] +1)))
                    for channel in range(1, (timer_cfg[1] +1)):
                        const_mapp_evnt_tim += "        {" + f"{ENUM_FMKCPU_TIMER_ROOT}_{idx_timer},"  \
                                            + " " * (SPACE_VARIABLE - len(f"{ENUM_FMKCPU_TIMER_ROOT}_{idx_timer}")) \
                                            + f"        {ENUM_FMKCPU_CHANNEL_ROOT}_{channel}"\
                                            + "}," + f"    // {ENUM_FMKCPU_IT_EVNT_ROOT}_{idx_tim_evnt}\n"
                        # for fmkio
                        cls.itline_timchnl_mapping[str(f"{ENUM_FMKCPU_TIMER_ROOT}_{idx_timer}{ENUM_FMKCPU_CHANNEL_ROOT}_{channel}")] =  f"{ENUM_FMKCPU_IT_EVNT_ROOT}_{idx_tim_evnt}"
                    idx_tim_evnt = idx_tim_evnt + timer_cfg[1]
            

        var_tim_max_chnl += "    };\n\n"
        var_timinfo += "};\n\n"
        const_mapp_gp_tim += "    };\n\n"
        const_mapp_evnt_tim += "    };\n\n"
        const_mapp_dac_tim += "    };\n\n"

        enum_it_lines_gp = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_IT_GP_ROOT, suffix_pg_tim,
                                                                't_eFMKCPU_InterruptLineIO', 0, "Number of General Purpose Interrupt Line, for PWM, Input-Compare, Output Compare, One sPulse",
                                                                description_pg_tim)
        
        enum_it_lines_evnt = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_IT_EVNT_ROOT, suffix_evnt_tim,
                                                                't_eFMKCPU_InterruptLineEvnt', 0, "Number of Event Purpose Interrupt Line",
                                                                description_evnt_tim)
        
        enum_it_lines_dac = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_IT_DAC_ROOT, suffix_dac_tim,
                                                                't_eFMKCPU_InterruptLineDAC', 0, "Number of DAC Purpose Interrupt Line",
                                                                description_dac_tim)

        enum_timer = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_TIMER_ROOT, timer_number_a,
                                                           "t_eFMKCPU_Timer", 0, "Number of timer enable in smt32xxx board",
                                                           [f"Reference for HAL timer{timer_cfg[0][5:]}, this timer has {timer_cfg[1]} channel(s)" for timer_cfg in timer_cfg_a][1:])
        enum_channel = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_CHANNEL_ROOT, [str(int(idx + 1)) for idx in range(max_channel)],
                                                             "t_eFMKCPU_InterruptChnl", 0, "Number max of channel enable by timer",
                                                             [f"Reference to HAL channel {idx}" for idx in range(max_channel)])

        #----------------------------------------------------------------
        #-----------------------------make var evnt cfg------------------
        #-----------------------------make eenum evnt channel------------
        #----------------------------------------------------------------
        var_evntcfg += "    /**< Hardware configuration for Event Period Timer */\n" \
                        + "    const t_sFMKCPU_BspTimerCfg c_FMKCPU_EvntTimerCfg_as[FMKCPU_EVENT_CHANNEL_NB] = {\n"
        var_evntcfg += "      //" 
        for elem_desc in evnt_cfg_a[0]:
            var_evntcfg += f"{elem_desc}" + " " * (SPACE_VARIABLE - len(elem_desc))
        var_evntcfg += "\n"
        for idx, evnt_cfg in enumerate(evnt_cfg_a[1:]):
            if str(evnt_cfg[0] + evnt_cfg[1]) in cls.stm_tim_chnl:
                raise TimerCfg_alreadyUsed(f" the timer {evnt_cfg[0]} and his channel {evnt_cfg[1]} has already been configured")
            
            cls.stm_tim_chnl.append(str(evnt_cfg[0] + evnt_cfg[1]))
            var_evntcfg += "    {" \
                        + f"{ENUM_FMKCPU_TIMER_ROOT}_{evnt_cfg[0][6:]}," \
                        +" " * (SPACE_VARIABLE - len(f"{ENUM_FMKCPU_TIMER_ROOT}_{evnt_cfg[0][5:]}")) \
                        + f"{ENUM_FMKCPU_CHANNEL_ROOT}_{evnt_cfg[1][8:]}" + "}," \
                        + f"  // {ENUM_FMKCPU_EVENT_ROOT}_{idx+1}\n"
        var_evntcfg += "    };\n\n"

        enum_evnt += cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_EVENT_ROOT, [str(int(idx + 1)) for idx in range(nb_evnt_channel)],
                                                           "t_eFMKCPU_EventChannel", 0, "Number of cannel channel dedicate for timer_event configuration",
                                                           [f"Event channel {idx}" for idx in range(nb_evnt_channel)])

        #----------------------------------------------------------------
        #-----------------------------make var NVIC priority-------------
        #-----------------------------------------------------------------
        var_nvic_prio += "    /**< Set the NVIC Priority for all NVIC_IRqn Priority */\n" \
                        + f"    const t_eFMKCPU_NVICPriority c_FMKCPU_IRQNPriority_ae[{ENUM_FMKCPU_NVIC_ROOT}_NB] = " + "{\n" 
        var_nvic_prio += "      //" 
        for elem_desc in evnt_cfg_a[0]:
            var_nvic_prio += f"{elem_desc}" + " " * (SPACE_VARIABLE - len(elem_desc))
        var_nvic_prio += "\n"
        for nvic_cfg  in irqn_cfg_a[1:]:
            # make nvic variable
            var_nvic_prio += f"        {ENUM_FMKCPU_NVIC_PRIO_ROOT}_{nvic_cfg[1]}," \
                            + " " * (50 - len(f"{ENUM_FMKCPU_NVIC_PRIO_ROOT}_{nvic_cfg[1]},")) \
                            + f"//  {nvic_cfg[0]}\n"
            # make nvic switch case
            switch_irqn += f"            case {ENUM_FMKCPU_NVIC_ROOT}_{str(nvic_cfg[0]).upper()}:\n" \
                            + f"                *f_bspIRQN_pe = {nvic_cfg[0]};\n" \
                            + f"                break;\n" 
        var_nvic_prio += "    };\n\n"
        enum_nvic = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_NVIC_ROOT, [str(nvic_cfg[0]).upper() for nvic_cfg in irqn_cfg_a[1:]],
                                                          "t_eFMKCPU_IRQNType", 0, "Enum for NVIC list",
                                                          [f"Reference to HAL nvic {nvic_cfg[0]}" for nvic_cfg in irqn_cfg_a[1:] ])

        #-----------------------------------------------------------
        #------------code genration for FMKCPU module---------------
        #-----------------------------------------------------------
        #---------------------For FMKCPU_Config Public---------------------#
        print("\t- For configPublic file")
        cls.code_gen.change_target_balise(TARGET_T_ENUM_START_LINE,TARGET_T_ENUM_END_LINE)

        print("\t\t- enum for NVIC available in this stm")
        cls.code_gen._write_into_file(enum_nvic, FMKCPU_CONFIGPUBLIC)

        print("\t\t- enum for RCC clock available in this stm")
        cls.code_gen._write_into_file(enum_rcc, FMKCPU_CONFIGPUBLIC)

        print('\t\t- enum for dac purpose timer')
        cls.code_gen._write_into_file(enum_it_lines_dac, FMKCPU_CONFIGPUBLIC)

        print('\t\t- enum for event purpose timer')
        cls.code_gen._write_into_file(enum_it_lines_evnt, FMKCPU_CONFIGPUBLIC)

        print('\t\t- enum for general purpose timer')
        cls.code_gen._write_into_file(enum_it_lines_gp, FMKCPU_CONFIGPUBLIC)

        

        print("\t\t include for cpu")
        cls.code_gen.change_target_balise(TARGET_CPU_CFG_START,TARGET_CPU_CFG_END)


        cls.code_gen._write_into_file(include_cpu,FMKCPU_CONFIGPUBLIC)
        print("\t- For configPrivate file")
        #---------------------For FMKCPU_Config Private---------------------#
        cls.code_gen.change_target_balise(TARGET_T_ENUM_START_LINE,TARGET_T_ENUM_END_LINE)

        print("\t\t- enum for timer channel")
        cls.code_gen._write_into_file(enum_channel, FMKCPU_CONFIGPRIVATE)

        print("\t\t- enum for timer")
        cls.code_gen._write_into_file(enum_timer, FMKCPU_CONFIGPRIVATE)

        cls.code_gen.change_target_balise(TARGET_TIMER_CHNLNB_START, TARGET_TIMER_CHNLNB_END)
        print("\t\t- Define for max channel per timer")
        cls.code_gen._write_into_file(def_tim_max_chnl, FMKCPU_CONFIGPRIVATE)

        cls.code_gen.change_target_balise(TARGET_T_VARIABLE_START_LINE, TARGET_T_VARIABLE_END_LINE)

        print("\t\t- Variable for max channel per timer")
        cls.code_gen._write_into_file(var_tim_max_chnl, FMKCPU_CONFIGPRIVATE)

        print("\t\t- Variable for clock state functions")
        cls.code_gen._write_into_file(var_clk_state, FMKCPU_CONFIGPRIVATE)

        print("\t\t- Configuration for nvic priority")
        cls.code_gen._write_into_file(var_nvic_prio, FMKCPU_CONFIGPRIVATE)

        print("DAC Purpose Timer_Channel Mapping")
        cls.code_gen._write_into_file(const_mapp_dac_tim, FMKCPU_CONFIGPRIVATE)

        print("Event Purpose Timer_Channel Mapping")
        cls.code_gen._write_into_file(const_mapp_evnt_tim, FMKCPU_CONFIGPRIVATE)

        print("General Purpose Timer_Channel Mapping")
        cls.code_gen._write_into_file(const_mapp_gp_tim, FMKCPU_CONFIGPRIVATE)

        
        cls.code_gen.change_target_balise(TARGET_c_clock_eNABLE_IMPL_START, TARGET_c_clock_eNABLE_IMPL_END)
        #---------------------For FMKCPU_Config Spec---------------------#
        print("\t\t- Function for enable/disable RCC clock")
        cls.code_gen._write_into_file(rcc_ena_imple, FMKCPU_CONFIGSPECIFIC_C)

        cls.code_gen.change_target_balise(TARGET_CLOCK_DISABLE_IMPL_START, TARGET_CLOCK_DISABLE_IMPL_END)
        cls.code_gen._write_into_file(rcc_dis_imple, FMKCPU_CONFIGSPECIFIC_C)
        cls.code_gen.change_target_balise(TARGET_c_clock_eNABLE_DECL_START, TARGET_c_clock_eNABLE_DECL_END)
        cls.code_gen._write_into_file(rcc_ena_decl, FMKCPU_CONFIGSPECIFIC_H)
        cls.code_gen.change_target_balise(TARGET_CLOCK_DISABLE_DECL_START, TARGET_CLOCK_DISABLE_DECL_END)
        cls.code_gen._write_into_file(rcc_dis_decl, FMKCPU_CONFIGSPECIFIC_H)
        #---------------------For FMKCPU.c---------------------#
        print("\t- For FMKCPU.c file")
        cls.code_gen.change_target_balise(TARGET_TIMER_INFO_START, TARGET_TIMER_INFO_END)
        print("\t\t- variable for timer information")
        cls.code_gen._write_into_file(var_timinfo, FMKCPU)
        cls.code_gen.change_target_balise(TARGET_SWITCH_NVIC_START, TARGET_SWITCH_NVIC_END)
        print("\t\t- switch case to find stm NVIC from enum")
        cls.code_gen._write_into_file(switch_irqn, FMKCPU)
        cls.code_gen.change_target_balise(TARGET_TIMER_X_IRQH_START, TARGET_TIMER_X_IRQH_END)
        cls.code_gen._write_into_file(func_imple, FMKCPU)
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<End code generation for FmkCpu Module>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")

    #-------------------------
    # get_tim_chnl_used
    #-------------------------
    @classmethod
    def get_tim_chnl_used(cls)->List:
        return cls.stm_tim_chnl
    
    #-------------------------
    # get_tim_chnl_used
    #-------------------------
    @classmethod
    def get_itline_from_timcnl(cls, enum_timer:str, enum_channel:str)->str:
        timer_chnl = enum_timer + enum_channel

        try: 
            retval_itline = cls.itline_timchnl_mapping[timer_chnl]
        except(KeyError):
            raise KeyError(f'Cannot found Interrupt line for {enum_timer} and {enum_channel}')
        
        return retval_itline
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

