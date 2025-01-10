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
from .FMK_PATH import *
from PyCodeGene import LoadConfig_FromExcel as LCFE, TARGET_T_END_LINE,TARGET_T_ENUM_END_LINE, \
                                                    TARGET_T_ENUM_START_LINE,TARGET_T_START_LINE,TARGET_T_VARIABLE_START_LINE,\
                                                    TARGET_T_VARIABLE_END_LINE,TARGET_T_STRUCT_START_LINE,\
                                                    TARGET_T_STRUCT_END_LINE, TARGET_VARIABLE_END_LINE, TARGET_VARIABLE_START_LINE
#------------------------------------------------------------------------------
#                                       CONSTANT
#------------------------------------------------------------------------------
ENUM_FMKMAC_DMA_CHANNEL = 'FMKMAC_DMA_CHANNEL'
ENUM_FMKMAC_DMA_CTRL    = 'FMKMAC_DMA_CTRL'
ENUM_FMKMAC_DMA_MUX     = 'FMKMAC_DMA_MUX'
ENUM_FMKMAC_DMARQST     = 'FMKMAC_DMA_RQSTYPE' 
ENUM_FMKMAC_DMATYPE     = 'FMKMAC_DMA_TYPE'
ENUM_FMKMAC_DMA_TRANSPRIO          = 'FMKMAC_DMA_TRANSPRIO'

TARGET_FMKMAC_IRQN_HANDLER_START = '/* CAUTION : Automatic generated code section for DMA_Channel IRQHandler: Start */\n'
TARGET_FMKMAC_IRQN_HANDLER_END   = '/* CAUTION : Automatic generated code section for DMA_Channel IRQHandler: End */\n'
TARGET_FMKMAC_SWITCH_RQST_START  = '            /* CAUTION : Automatic generated code section for Request Dma: Start */\n'
TARGET_FMKMAC_SWITCH_RQST_END    = '            /* CAUTION : Automatic generated code section for Request Dma: End */\n'
TARGET_FMKMAC_SWITCH_DMATYPE_START = '            /* CAUTION : Automatic generated code section for Dma Type: Start */\n'
TARGET_FMKMAC_SWITCH_DMATYPE_END = '            /* CAUTION : Automatic generated code section for Dma Type: End */\n'

FMKMAC_CFGSPEC_C   = 'src\\1_FMK\FMK_CFG\FMKCFG_ConfigSpecific\FMKMAC_ConfigSpecific.c'
FMKMAC_CFGPUBLIC   = 'src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKMAC_ConfigPublic.h'
FMKMAC_CFGPRIVATE  = 'src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKMAC_ConfigPrivate.h'
FMKMAC_CFILE       = 'src\\1_FMK\FMK_HAL\FMK_MAC\Src\FMK_MAC.c'
# CAUTION : Automatic generated code section: Start #

# CAUTION : Automatic generated code section: End #
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------
class DMA_Chnl_AlreadyConfgigured(Exception):
    pass

class DMA_ConfigError(Exception):
    pass
class FMKMAC_CodeGen():
    """
        Make code generation for FMKMAC module which include 
        file FMKMAC_ConfigPublic.h : 
            - Enum avec tout les request types                               
            - Enum avec les DMA 
            - Enum avec les DMA channels         
            - enum adc internal TS_CAL_1, SUPPLY_VOLTAGE etc                   
        
        file FMKMAC_ConfigPrivate.h :
            - variable pour chaque RqstType, leur association avec Dma + Channel


        file  FMKMAC.c
            - variable DmaInfo
    """
    code_gen = LCFE()

    @classmethod
    def code_genration(cls, f_hw_cfg) -> None:

        # load array needed
        cls.code_gen.load_excel_file(f_hw_cfg)

        info_array = cls.code_gen.get_array_from_excel('GI_DMA')[1:]
        cfg_array = cls.code_gen.get_array_from_excel('FMKMAC_Cfg')[1:]
        irqn_list = cls.code_gen.get_array_from_excel('FMKMAC_IRQN')[1:]
        dmamux_list = cls.code_gen.get_array_from_excel('FMKMAC_DMAMUX')[1:]
        dmachnl_used = []
        rqstype_list = []
        
        """
            'DMA1' : [ADC1,USART1_RX, USART1_TX,,,,,],
            'DMA2  : [FDCAN1_RX, FDCAN_TX, etc],
        """
        var_info = ''
        cst_cfg = ''
        enm_rqst = ''
        switch_rqst = ''
        irqn_hdler = ''
        enm_channel = ''
        enm_dmamux = ''
        cst_dmamux_mapp = ''
        enm_dma = ''
        max_channel = 0

        for dma_info in info_array:
            max_channel = max(max_channel, int(dma_info[1]))
        
        max_channel += 1
        #----------------------------------------------------------------
        #-------------------------------Make Enum -----------------------
        #----------------------------------------------------------------

        dmamux_nb = len(dmamux_list)
        enm_dmamux = cls.code_gen.make_enum_from_variable(ENUM_FMKMAC_DMA_MUX, [(idx + 1) for idx in range(0, dmamux_nb)],
                                                        't_eFMKMAC_DmaMux', 0,
                                                        "Enum for Number of Dma Multiplexage Controler",
                                                        [f'Reference to DMAMUX {(idx + 1)}' for idx in range(0, dmamux_nb)])
            
        enm_channel = cls.code_gen.make_enum_from_variable(ENUM_FMKMAC_DMA_CHANNEL, [idx for idx in range(1, max_channel)],
                                                            't_eFMKMAC_DmaChnl', 0,
                                                            "Enum for number of channel in DMA",
                                                            [f'Reference to Channel {idx}' for idx in range(1, max_channel)])
        
        enm_dma = cls.code_gen.make_enum_from_variable(ENUM_FMKMAC_DMA_CTRL, [dma_info[0][-1] for dma_info in info_array],
                                                            't_eFMKMAC_DmaController', 0,
                                                            "Enum for Number of Dma",
                                                            [f'Reference to DMA {str(dma[0])[-1]}' for dma in info_array])
        
        enm_rqst = cls.code_gen.make_enum_from_variable(ENUM_FMKMAC_DMARQST, [rqst_cfg[0] for rqst_cfg in cfg_array],
                                                        't_eFMKMAC_DmaRqst', 0,
                                                        'Enum for the different request available for DMA service',
                                                        [f'Reference to Bsp Dma Request for {rqst_cfg[0]}' for rqst_cfg in cfg_array])
        
        #----------------------------------------------------------------
        #----------------------------Make Mapping Variable --------------
        #----------------------------------------------------------------
        cst_cfg += '    /**< Variable to mapp every Dma Request to a Dma Channel */\n' \
                + f'    const t_sFMKMAC_DmaRqstCfg c_FmkMac_DmaRqstCfg_as[{ENUM_FMKMAC_DMARQST}_NB] =' + '{\n'
        
        cst_dmamux_mapp += '    /**< Variable to mapp every Dma Mux to a Rcc Clock */\n' \
                + f'    const t_eFMKCPU_ClockPort c_FmkMac_DmaMuxRccMapp_ae[{ENUM_FMKMAC_DMA_MUX}_NB] =' + '{\n'
        
        cst_dmamux_mapp += ''.join(f'           {ENUM_FMKCPU_RCC_ROOT}_DMAMUX{idx + 1}\n' for idx in range(0, dmamux_nb))
        cst_dmamux_mapp += '    };\n\n'
        for rqst_info in cfg_array:

            if (str(rqst_info[1]) + str(rqst_info[2])) in dmachnl_used:
                raise DMA_Chnl_AlreadyConfgigured('Dma & Channel Already configured, please check your Excel Configuration')
            
            # update information
            dmachnl_used.append((str(rqst_info[1]) + str(rqst_info[2])))
            rqstype_list.append(rqst_info[0])
            # store to the right idx in Dma1 or Dma2 the RqstType

            cst_cfg += '        {' \
                    + f'{ENUM_FMKMAC_DMA_CTRL}_{rqst_info[1][-1]},' \
                    + ' ' * (SPACE_VARIABLE - len(f'{ENUM_FMKMAC_DMA_CTRL}_{rqst_info[0][-1]}')) \
                    + f'{ENUM_FMKMAC_DMA_CHANNEL}_{rqst_info[2][-1]},' \
                    + ' ' * (SPACE_VARIABLE - len(f'{ENUM_FMKMAC_DMA_CHANNEL}_{rqst_info[2][-1]}')) \
                    + f'{ENUM_FMKMAC_DMA_TRANSPRIO}_{rqst_info[3]}' \
                    + '},' \
                    + ' ' * (SPACE_VARIABLE - len(f'{ENUM_FMKMAC_DMA_TRANSPRIO}_{rqst_info[3]}')) \
                    + f'// {ENUM_FMKMAC_DMARQST}_{rqst_info[0]}\n'
            
            # switch case rqst
            switch_rqst += f'            case {ENUM_FMKMAC_DMARQST}_{rqst_info[0]}:\n' \
                            + f'                f_bspDma_ps->Init.Request = DMA_REQUEST_{rqst_info[0]};\n' \
                            +  '                break;\n'

        cst_cfg += '    };\n\n'
        #----------------------------------------------------------------
        #----------------------------Make IRQN Handler -----------------
        #----------------------------------------------------------------
        for irqn_info in irqn_list:
            if irqn_info[1] != None :
                # reach the DMA idx & channel 
                try:
                    idx_dma = int(str(irqn_info[0])[3])
                except (TypeError):
                    raise DMA_ConfigError('Cannot reach the DMA Idx')
                

                irqn_hdler +='/**\n' \
                            + f'* @brief This function handles {str(irqn_info[0])[:3]} {str(irqn_info[0])[5:-11]} interrupt.\n' \
                            + '*/\n' \
                            + f'void {irqn_info[0]}(void)\n' \
                            + '{\n'
                # Look for channel Idx
                for char in str(irqn_info[0][5:]):
                    if char.isdigit():
                        irqn_hdler    += f'    if(g_DmaInfo_as[{ENUM_FMKMAC_DMA_CTRL}_{idx_dma}].channel_as[{ENUM_FMKMAC_DMA_CHANNEL}_{char}].isChnlConfigured_b == (t_bool)True)\n'\
                                        + '    {\n' \
                                        + f'       HAL_DMA_IRQHandler(&(g_DmaInfo_as[{ENUM_FMKMAC_DMA_CTRL}_{idx_dma}].channel_as[{ENUM_FMKMAC_DMA_CHANNEL}_{char}].bspDma_ps));\n' \
                                        + '    }\n'

                irqn_hdler += '    return;\n}\n\n'
        #----------------------------------------------------------------
        #----------------------------Make Variable Info -----------------
        #----------------------------------------------------------------
        var_info += '/**< Variable to store information about the Dma and the Channel */\n' \
                    + f't_sFMKMAC_DmaInfo g_DmaInfo_as[{ENUM_FMKMAC_DMA_CTRL}_NB] = ' \
                    + '{\n'
        
        for dma_info in  info_array:
            
            var_info += '     {'\
                    + f'//------- {dma_info[2]}_CONTROLLER -------//\n' \
                    + f'        .c_clock_e = {ENUM_FMKCPU_RCC_ROOT}_{dma_info[2]},\n' \
                    +  '        .channel_as = {\n\n\n'
            
            for idx_cnhl in range(1, (dma_info[1]  + 1)):
                 var_info += f'            [{ENUM_FMKMAC_DMA_CHANNEL}_{idx_cnhl}] = ' \
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
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<Start code generation for FMFMAC Module>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print('\t- For Config Public File ')
        cls.code_gen.change_target_balise(TARGET_T_ENUM_START_LINE, TARGET_T_ENUM_END_LINE)

        print('\t\t- For Dma Multiplexage')
        cls.code_gen._write_into_file(enm_dmamux, FMKMAC_CFGPUBLIC)

        print('\t\t- For Dma Channel')
        cls.code_gen._write_into_file(enm_channel, FMKMAC_CFGPUBLIC)
                                      
        print('\t\t- For Dma Controller')
        cls.code_gen._write_into_file(enm_dma, FMKMAC_CFGPUBLIC)

        print('\t\t- For Dma RqstType')
        cls.code_gen._write_into_file(enm_rqst, FMKMAC_CFGPUBLIC)


        print('\t- For Config Private File ')
        cls.code_gen.change_target_balise(TARGET_T_VARIABLE_START_LINE, TARGET_T_VARIABLE_END_LINE)

        print('\t\t- For Mapping Rqst Type / Dma Controller')
        cls.code_gen._write_into_file(cst_cfg, FMKMAC_CFGPRIVATE)

        print('\t\t- For Mapping Dma Mux Rcc Mapping')
        cls.code_gen._write_into_file(cst_dmamux_mapp, FMKMAC_CFGPRIVATE)


        print('\t- For FMKMAC.c File ')
        cls.code_gen.change_target_balise(TARGET_VARIABLE_START_LINE, TARGET_VARIABLE_END_LINE)

        print('\t\t- For Dma Info variable')
        cls.code_gen._write_into_file(var_info, FMKMAC_CFILE)

        print('\t\tFor IRQN Handler')
        cls.code_gen.change_target_balise(TARGET_FMKMAC_IRQN_HANDLER_START, TARGET_FMKMAC_IRQN_HANDLER_END)
        cls.code_gen._write_into_file(irqn_hdler, FMKMAC_CFILE)

        print('\t- For FMKMAC_ConfigSpecific.c File ')
        print('\t\tFor Switch case for Request Dma')
        cls.code_gen.change_target_balise(TARGET_FMKMAC_SWITCH_RQST_START, TARGET_FMKMAC_SWITCH_RQST_END)
        cls.code_gen._write_into_file(switch_rqst, FMKMAC_CFGSPEC_C)
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<End code generation for FMFMAC Module>>>>>>>>>>>>>>>>>>>>")
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

