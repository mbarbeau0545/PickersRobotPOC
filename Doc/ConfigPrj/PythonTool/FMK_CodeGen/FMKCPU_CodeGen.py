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
                                                    TARGET_T_STRUCT_END_LINE, TARGET_VARIABLE_START_LINE, TARGET_VARIABLE_END_LINE
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
TARGET_PERIP_PRESCALER_START = '            /* CAUTION : Automatic generated code section for Peripheric Prescaler switch case: Start */\n'
TARGET_PERIP_PRESCALER_END = '            /* CAUTION : Automatic generated code section for Peripheric Prescaler switch case: End */\n'
TARGET_FUNC_PERIPH_PRESC_START = '    /* CAUTION : Automatic generated code section for Function Prescaler Configuration: Start */\n'
TARGET_FUNC_PERIPH_PRESC_END   = '    /* CAUTION : Automatic generated code section for Function Prescaler Configuration: End */\n'
TARGET_SWITCH_PERIPH_CLK_CFG_START = '            /* CAUTION : Automatic generated code section for Periph Clock Cfg: Start */\n'
TARGET_SWITCH_PERIPH_CLK_CFG_END = '            /* CAUTION : Automatic generated code section for Periph Clock Cfg: End */\n'
TARGET_FMKCPU_IRQN_HANDLER_START = '/* CAUTION : Automatic generated code section for DMA_Channel IRQHandler: Start */\n'
TARGET_FMKCPU_IRQN_HANDLER_END   = '/* CAUTION : Automatic generated code section for DMA_Channel IRQHandler: End */\n'
TARGET_FMKCPU_SWITCH_RQST_START  = '            /* CAUTION : Automatic generated code section for Request Dma: Start */\n'
TARGET_FMKCPU_SWITCH_RQST_END    = '            /* CAUTION : Automatic generated code section for Request Dma: End */\n'
TARGET_FMKCPU_SWITCH_DMATYPE_START = '            /* CAUTION : Automatic generated code section for Dma Type: Start */\n'
TARGET_FMKCPU_SWITCH_DMATYPE_END = '            /* CAUTION : Automatic generated code section for Dma Type: End */\n'


ENUM_FMKCPU_DMA_CHANNEL = 'FMKCPU_DMA_CHANNEL'
ENUM_FMKCPU_DMA_CTRL    = 'FMKCPU_DMA_CTRL'
ENUM_FMKCPU_DMA_MUX     = 'FMKCPU_DMA_MUX'
ENUM_FMKCPU_DMARQST     = 'FMKCPU_DMA_RQSTYPE' 
ENUM_FMKCPU_DMATYPE     = 'FMKCPU_DMA_TYPE'
ENUM_FMKCPU_DMA_TRANSPRIO          = 'FMKCPU_DMA_TRANSPRIO'


PERIPH_CLOCK_NEED_PRESCALER = ['ADC', 'I2C', 'I2S', 'LPTIM', 'TIM', 'LPUART', 'QUADSPI', 'RNG', 'USB', 'SAI1', 'FDCAN', 'CAN', 'UART', 'USART', 'HRTIM']

PERIPH_TO_CLKSRC:Dict[str,str] = {
    'HSE'      :  'LSE',
    'HSI'      :  'HSI',
    'SYSTEM'   :  'SYSCLK',
    'HCLK1'    :   None,
    'AHB1'     :   None,
    'AHB2'     :   None,
    'APB1'     :  'PCLK1',
    'APB2'     :  'PCLK2',
    'PLLQ'     :  'PLL',
    'PLLP'     :  'PLL',

}
# CAUTION : Automatic generated code section: Start #

# CAUTION : Automatic generated code section: End #
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------
class DMA_Chnl_AlreadyConfgigured(Exception):
    pass

class DMA_ConfigError(Exception):
    pass

class PeriphClockCfgError(Exception):
    pass

class FMKCPU_CodeGen():
    """
            Make code generation for FMKCPU module which include 
            file FMKCPU_ConfigPublic.h : 
               - Enum Event channel                x
               - Enum Rcc Clock                    x
               - Enum NVIC                         x
            
            file FMKCPU_ConfigPrivate.h :
                - variable NVIC prioirty           x
                - define number of IRQN            x
                - Variable clock enable            x
            
            file  FMK_CPU_ConfigSpecififc.c
                - enable/ disable clock implementation  x

            file  FMK_CPU_ConfigSpecififc.h
                - -enable/ disable clock declaration    x

            file  FMK_CPU.c
                - switch case IRQN to bsp IRQN          x
        """
    itline_timchnl_mapping:Dict[str, List[str]] = {}
    code_gen = LCFE()
    stm_tim_chnl = []
    #-------------------------
    # code_generation
    #-------------------------
    @classmethod
    def code_generation(cls, f_hw_cfg) -> None:

        cls.code_gen.load_excel_file(f_hw_cfg)
        irqn_cfg_a      = cls.code_gen.get_array_from_excel("GI_IRQN")
        rcclock_cfg_a   = cls.code_gen.get_array_from_excel("GI_RCC_CLOCK")
        cpu_cfg         = cls.code_gen.get_array_from_excel("CPU_Config")[1][0]
        osc_clock_a     = cls.code_gen.get_array_from_excel('GI_OSCILLATOR')[1:]
        dma_cfg_array = cls.code_gen.get_array_from_excel('FMKMAC_Cfg')[1:]
        dma_irqn_list = cls.code_gen.get_array_from_excel('FMKMAC_IRQN')[1:]
        dmamux_list = cls.code_gen.get_array_from_excel('FMKMAC_DMAMUX')[1:]
        dma_info_array = cls.code_gen.get_array_from_excel('GI_DMA')[1:]
        dmachnl_used = []
        rqstype_list = []
        
        """
            'DMA1' : [ADC1,USART1_RX, USART1_TX,,,,,],
            'DMA2  : [FDCAN1_RX, FDCAN_TX, etc],
        """
    

        enum_osc_freq = ""       
        var_clk_state =''
        enum_rcc = ""
        enum_nvic = ""
        var_nvic_prio = ""
        var_clk_state = ""
        rcc_ena_imple = ""
        rcc_dis_imple = ""
        rcc_ena_decl = ""
        rcc_dis_decl  = ""
        const_osc_rcc_src = ""
        switch_rcc_prsc = ""
        switch_irqn = ""
        switch_clk_periph = ''
        include_cpu = ""

        var_info = ''
        cst_cfg = ''
        enm_rqst = ''
        switch_rqst = ''
        dma_irqn_hdler = ''
        enum_dma_channel = ''
        enm_dmamux = ''
        cst_dmamux_mapp = ''
        enm_dma = ''
        max_channel = 0
        dma_max_channel = 0

        for dma_info in dma_info_array:
            dma_max_channel = max(dma_max_channel, int(dma_info[1]))
        
        dma_max_channel += 1
        #----------------------------------------------------------------
        #-----------------------------make cpu include-------------------
        #----------------------------------------------------------------
        # only takes tha family for include function
        cpu_function =   f'    #include "{str(cpu_cfg)[:7]}xx_hal.h"\n'
        include_cpu_hw = f'    #include "{cpu_cfg}.h"\n'
        include_cpu = cpu_function + include_cpu_hw
        #----------------------------------------------------------------
        #-----------------------------make sysclock enum-----------------
        #-----------------------------------------------------------------
        enum_osc_freq = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_SYS_CLOCK, [osc_clock[0] for osc_clock in osc_clock_a], 
                                                            "t_eFMKCPU_SysClkOsc", 0, 
                                                            "Enum for System Oscillator Clock",
                                                            [f'Reference to Hardware Bus {osc_clock[0]}' for osc_clock in osc_clock_a])
        #----------------------------------------------------------------
        #-----------------------------make rcc enum----------------------
        #-----------------------------------------------------------------
        enum_rcc = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_RCC_ROOT, [str(rcclock_cfg[0]) for rcclock_cfg in rcclock_cfg_a[1:]], 
                                                            "t_eFMKCPU_ClockPort", 0, 
                                                            "Enum for rcc clock state reference",
                                                            [f'Reference to RCC Clock {rcclock_cfg[0]}' for rcclock_cfg in rcclock_cfg_a[1:]])
        
        dmamux_nb = len(dmamux_list)
        enm_dmamux = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_DMA_MUX, [(idx + 1) for idx in range(0, dmamux_nb)],
                                                        't_eFMKCPU_DmaMux', 0,
                                                        "Enum for Number of Dma Multiplexage Controler",
                                                        [f'Reference to DMAMUX {(idx + 1)}' for idx in range(0, dmamux_nb)])
            
        enum_dma_channel = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_DMA_CHANNEL, [idx for idx in range(1, dma_max_channel)],
                                                            't_eFMKCPU_DmaChnl', 0,
                                                            "Enum for number of channel in DMA",
                                                            [f'Reference to Channel {idx}' for idx in range(1, dma_max_channel)])
        
        enm_dma = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_DMA_CTRL, [dma_info[0][-1] for dma_info in dma_info_array],
                                                            't_eFMKCPU_DmaController', 0,
                                                            "Enum for Number of Dma",
                                                            [f'Reference to DMA {str(dma[0])[-1]}' for dma in dma_info_array])
        
        enm_rqst = cls.code_gen.make_enum_from_variable(ENUM_FMKCPU_DMARQST, [rqst_cfg[0] for rqst_cfg in dma_cfg_array],
                                                        't_eFMKCPU_DmaRqst', 0,
                                                        'Enum for the different request available for DMA service',
                                                        [f'Reference to Bsp Dma Request for {rqst_cfg[0]}' for rqst_cfg in dma_cfg_array])
        

        #-------------------make rcc variable bus & switch case & decl --
        #-----------------------------------------------------------------
        const_osc_rcc_src += f'    const t_eFMKCPU_SysClkOsc c_FmkCpu_RccClockOscSrc_ae[{ENUM_FMKCPU_RCC_ROOT}_NB] = ' + '{\n' 
        # Store the rcc clock enum that don't need Periph init
        periph_clk_brk = []
        for rcc_cfg in rcclock_cfg_a[1:]:
            const_osc_rcc_src += f'        {ENUM_FMKCPU_SYS_CLOCK}_{rcc_cfg[1]},' \
                              +  " " * (SPACE_VARIABLE - len(f"{ENUM_FMKCPU_SYS_CLOCK}_{rcc_cfg[1]}")) \
                              + f'   // {ENUM_FMKCPU_RCC_ROOT}_{rcc_cfg[0]}\n'
            # make  switch case for Periph Clock Init 

            if rcc_cfg[2] == 'No':
                periph_clk_brk.append(f'{ENUM_FMKCPU_RCC_ROOT}_{rcc_cfg[0]}')
            
            elif rcc_cfg[2] == 'Yes':

                preiph_clk_src = PERIPH_TO_CLKSRC.get(rcc_cfg[1], None)

                if preiph_clk_src == None:
                    PeriphClockCfgError(f'Cannot found periph clock Source for {rcc_cfg[1]}')

                switch_clk_periph +=  f'            case {ENUM_FMKCPU_RCC_ROOT}_{rcc_cfg[0]}:\n' \
                                    + f'                PeriphClkCfg_s.{str(rcc_cfg[0]).capitalize()}ClockSelection = ' \
                                    + f'RCC_PERIPHCLK_{str(rcc_cfg[0]).upper()};\n' \
                                    + f'                //------ Reference Clock  Source {rcc_cfg[1]} ------//\n' \
                                    + f'                PeriphClkCfg_s.PeriphClockSelection = RCC_{str(rcc_cfg[0]).upper()}CLKSOURCE_{preiph_clk_src.upper()};\n' \
                                    +  '                break;\n'
            else:
                PeriphClockCfgError(f'{rcc_cfg[2]} is not allowed, only Yes or No value allowed')
          
            
        switch_clk_periph += "".join(
            [f"            case {rcc_no_periph}:\n"
            for rcc_no_periph in periph_clk_brk]
        )
        switch_clk_periph += f'            case {ENUM_FMKCPU_RCC_ROOT}_NB:\n            default:\n                Ret_e = RC_WARNING_NO_OPERATION;\n                break;\n'
        switch_rcc_prsc + '\n'
        const_osc_rcc_src += '    };\n\n'
        #----------------------------------------------------------------
        #----------make rcc implementation/Declaration--------------------
        #-----------------------------------------------------------------
        var_clk_state += "    /**< Referencing all Enable/Disable Rcc clock function */\n" \
                        + "    const t_sFMKCPU_ClkFunc c_FMKCPU_ClkFunctions_apcb[FMKCPU_NVIC_NB] = {\n"
        
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


        var_clk_state += '    };\n\n'
    

        #----------------------------------------------------------------
        #-----------------------------make var NVIC priority-------------
        #-----------------------------------------------------------------
        var_nvic_prio += "    /**< Set the NVIC Priority for all NVIC_IRqn Priority */\n" \
                        + f"    const t_eFMKCPU_NVICPriority c_FMKCPU_IRQNPriority_ae[{ENUM_FMKCPU_NVIC_ROOT}_NB] = " + "{\n" 
    
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


        #----------------------------------------------------------------
        #----------------------------Make Mapping Variable --------------
        #----------------------------------------------------------------
        cst_cfg += '    /**< Variable to mapp every Dma Request to a Dma Channel */\n' \
                + f'    const t_sFMKCPU_DmaRqstCfg c_FMKCPU_DmaRqstCfg_as[{ENUM_FMKCPU_DMARQST}_NB] =' + '{\n'
        
        cst_dmamux_mapp += '    /**< Variable to mapp every Dma Mux to a Rcc Clock */\n' \
                + f'    const t_eFMKCPU_ClockPort c_FMKCPU_DmaMuxRccMapp_ae[{ENUM_FMKCPU_DMA_MUX}_NB] =' + '{\n'
        
        cst_dmamux_mapp += ''.join(f'           {ENUM_FMKCPU_RCC_ROOT}_DMAMUX{idx + 1}\n' for idx in range(0, dmamux_nb))
        cst_dmamux_mapp += '    };\n\n'
        for rqst_info in dma_cfg_array:

            if (str(rqst_info[1]) + str(rqst_info[2])) in dmachnl_used:
                raise DMA_Chnl_AlreadyConfgigured('Dma & Channel Already configured, please check your Excel Configuration')
            
            # update information
            dmachnl_used.append((str(rqst_info[1]) + str(rqst_info[2])))
            rqstype_list.append(rqst_info[0])
            # store to the right idx in Dma1 or Dma2 the RqstType

            cst_cfg += '        {' \
                    + f'{ENUM_FMKCPU_DMA_CTRL}_{rqst_info[1][-1]},' \
                    + ' ' * (SPACE_VARIABLE - len(f'{ENUM_FMKCPU_DMA_CTRL}_{rqst_info[0][-1]}')) \
                    + f'{ENUM_FMKCPU_DMA_CHANNEL}_{rqst_info[2][-1]},' \
                    + ' ' * (SPACE_VARIABLE - len(f'{ENUM_FMKCPU_DMA_CHANNEL}_{rqst_info[2][-1]}')) \
                    + f'{ENUM_FMKCPU_DMA_TRANSPRIO}_{rqst_info[3]}' \
                    + '},' \
                    + ' ' * (SPACE_VARIABLE - len(f'{ENUM_FMKCPU_DMA_TRANSPRIO}_{rqst_info[3]}')) \
                    + f'// {ENUM_FMKCPU_DMARQST}_{rqst_info[0]}\n'
            
            # switch case rqst
            switch_rqst += f'            case {ENUM_FMKCPU_DMARQST}_{rqst_info[0]}:\n' \
                            + f'                f_bspDma_ps->Init.Request = DMA_REQUEST_{rqst_info[0]};\n' \
                            +  '                break;\n'

        cst_cfg += '    };\n\n'

        #----------------------------------------------------------------
        #----------------------------Make IRQN Handler -----------------
        #----------------------------------------------------------------
        for irqn_info in dma_irqn_list:
            if irqn_info[1] != None :
                # reach the DMA idx & channel 
                try:
                    idx_dma = int(str(irqn_info[0])[3])
                except (TypeError):
                    raise DMA_ConfigError('Cannot reach the DMA Idx')
                

                dma_irqn_hdler +='/**\n' \
                            + f'* @brief This function handles {str(irqn_info[0])[:3]} {str(irqn_info[0])[5:-11]} interrupt.\n' \
                            + '*/\n' \
                            + f'void {irqn_info[0]}(void)\n' \
                            + '{\n'
                # Look for channel Idx
                for char in str(irqn_info[0][5:]):
                    if char.isdigit():
                        dma_irqn_hdler    += f'    if(g_DmaInfo_as[{ENUM_FMKCPU_DMA_CTRL}_{idx_dma}].channel_as[{ENUM_FMKCPU_DMA_CHANNEL}_{char}].isChnlConfigured_b == (t_bool)True)\n'\
                                        + '    {\n' \
                                        + f'       HAL_DMA_IRQHandler(&(g_DmaInfo_as[{ENUM_FMKCPU_DMA_CTRL}_{idx_dma}].channel_as[{ENUM_FMKCPU_DMA_CHANNEL}_{char}].bspDma_ps));\n' \
                                        + '    }\n'

                dma_irqn_hdler += '    return;\n}\n\n'
        
        #----------------------------------------------------------------
        #----------------------------Make Variable Info -----------------
        #----------------------------------------------------------------
        var_info += '/**< Variable to store information about the Dma and the Channel */\n' \
                    + f't_sFMKCPU_DmaInfo g_DmaInfo_as[{ENUM_FMKCPU_DMA_CTRL}_NB] = ' \
                    + '{\n'
        
        for dma_info in  dma_info_array:
            
            var_info += '     {'\
                    + f'//------- {dma_info[2]}_CONTROLLER -------//\n' \
                    + f'        .c_clock_e = {ENUM_FMKCPU_RCC_ROOT}_{dma_info[2]},\n' \
                    +  '        .channel_as = {\n\n\n'
            
            for idx_cnhl in range(1, (dma_info[1]  + 1)):
                 var_info += f'            [{ENUM_FMKCPU_DMA_CHANNEL}_{idx_cnhl}] = ' \
                            + '{\n' \
                            + '                .bspDma_ps = {' + f'.Instance = {dma_info[2]}_Channel{idx_cnhl}' + '},\n' \
                            + f'               .c_IRQNType_e = {ENUM_FMKCPU_NVIC_ROOT}_{str(f"{dma_info[2]}_Channel{idx_cnhl}").upper()}_IRQN,\n' \
                            + '            },\n\n'
            var_info += '        }\n'
            var_info += '    },\n'

        var_info += '};\n\n'
        #-----------------------------------------------------------
        #------------code genration for FMKCPU module---------------
        #-----------------------------------------------------------
        #---------------------For FMKCPU_Config Public---------------------#
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<Start code generation for FMFCPU Module>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("\t- For configPublic file")

        cls.code_gen.change_target_balise(TARGET_T_ENUM_START_LINE,TARGET_T_ENUM_END_LINE)
        print('\t\t- For Dma Multiplexage')
        cls.code_gen._write_into_file(enm_dmamux, FMKCPU_CONFIGPUBLIC)

        print('\t\t- For Dma Channel')
        cls.code_gen._write_into_file(enum_dma_channel, FMKCPU_CONFIGPUBLIC)
                                      
        print('\t\t- For Dma Controller')
        cls.code_gen._write_into_file(enm_dma, FMKCPU_CONFIGPUBLIC)

        print('\t\t- For Dma RqstType')
        cls.code_gen._write_into_file(enm_rqst, FMKCPU_CONFIGPUBLIC)
        

        print("\t\t- enum for NVIC available in this stm")
        cls.code_gen._write_into_file(enum_nvic, FMKCPU_CONFIGPUBLIC)

        print("\t\t- enum for RCC clock available in this stm")
        cls.code_gen._write_into_file(enum_rcc, FMKCPU_CONFIGPUBLIC)

        print('\t\t enum for oscillator management')
        cls.code_gen._write_into_file(enum_osc_freq, FMKCPU_CONFIGPUBLIC)

        print("\t\t include for cpu")
        cls.code_gen.change_target_balise(TARGET_CPU_CFG_START,TARGET_CPU_CFG_END)


        cls.code_gen._write_into_file(include_cpu,FMKCPU_CONFIGPUBLIC)
        #---------------------For FMKCPU_Config Private---------------------#
        print("\t- For configPrivate file")
        cls.code_gen.change_target_balise(TARGET_T_VARIABLE_START_LINE, TARGET_T_VARIABLE_END_LINE)
        
        cls.code_gen.change_target_balise(TARGET_T_VARIABLE_START_LINE, TARGET_T_VARIABLE_END_LINE)

        print('\t\t- For Mapping Rqst Type / Dma Controller')
        cls.code_gen._write_into_file(cst_cfg, FMKCPU_CONFIGPRIVATE)

        print('\t\t- For Mapping Dma Mux Rcc Mapping')
        cls.code_gen._write_into_file(cst_dmamux_mapp, FMKCPU_CONFIGPRIVATE)

        print('\t\t- varriable for oscillator management')
        cls.code_gen._write_into_file(const_osc_rcc_src, FMKCPU_CONFIGPRIVATE)
      

        print("\t\t- Variable for clock state functions")
        cls.code_gen._write_into_file(var_clk_state, FMKCPU_CONFIGPRIVATE)

        print("\t\t- Configuration for nvic priority")
        cls.code_gen._write_into_file(var_nvic_prio, FMKCPU_CONFIGPRIVATE)


        
        #---------------------For FMKCPU_Config Spec---------------------#
        print('\t For Config Specific File')
        print('\t\tFor Switch case for Request Dma')
        cls.code_gen.change_target_balise(TARGET_FMKCPU_SWITCH_RQST_START, TARGET_FMKCPU_SWITCH_RQST_END)
        cls.code_gen._write_into_file(switch_rqst, FMKCPU_CONFIGSPECIFIC_C)

        print("\t\t- Function for enable/disable RCC clock")
        cls.code_gen.change_target_balise(TARGET_c_clock_eNABLE_IMPL_START, TARGET_c_clock_eNABLE_IMPL_END)
        cls.code_gen._write_into_file(rcc_ena_imple, FMKCPU_CONFIGSPECIFIC_C)

        cls.code_gen.change_target_balise(TARGET_CLOCK_DISABLE_IMPL_START, TARGET_CLOCK_DISABLE_IMPL_END)
        cls.code_gen._write_into_file(rcc_dis_imple, FMKCPU_CONFIGSPECIFIC_C)

        cls.code_gen.change_target_balise(TARGET_c_clock_eNABLE_DECL_START, TARGET_c_clock_eNABLE_DECL_END)
        cls.code_gen._write_into_file(rcc_ena_decl, FMKCPU_CONFIGSPECIFIC_H)

        cls.code_gen.change_target_balise(TARGET_CLOCK_DISABLE_DECL_START, TARGET_CLOCK_DISABLE_DECL_END)
        cls.code_gen._write_into_file(rcc_dis_decl, FMKCPU_CONFIGSPECIFIC_H)

        print("\t\t- switch case to find stm NVIC from enum")
        cls.code_gen.change_target_balise(TARGET_SWITCH_NVIC_START, TARGET_SWITCH_NVIC_END)
        cls.code_gen._write_into_file(switch_irqn, FMKCPU_CONFIGSPECIFIC_C)

        print("\t\t- switch case to set Periph Clock Config")
        cls.code_gen.change_target_balise(TARGET_SWITCH_PERIPH_CLK_CFG_START, TARGET_SWITCH_PERIPH_CLK_CFG_END)
        cls.code_gen._write_into_file(switch_clk_periph, FMKCPU_CONFIGSPECIFIC_C)

        print('\t\t- Function for Prescaler Peripherique External Clock')
        #---------------------For FMKCPU.c---------------------#
        print("\t- For FMKCPU.c file")
        cls.code_gen.change_target_balise(TARGET_VARIABLE_START_LINE, TARGET_VARIABLE_END_LINE)
        print('\t\t- For Dma Info variable')
        cls.code_gen._write_into_file(var_info, FMKCPU)

        print('\t\tFor IRQN Handler')
        cls.code_gen.change_target_balise(TARGET_FMKCPU_IRQN_HANDLER_START, TARGET_FMKCPU_IRQN_HANDLER_END)
        cls.code_gen._write_into_file(dma_irqn_hdler, FMKCPU)

        

        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<End code generation for FmkCpu Module>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n")

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

