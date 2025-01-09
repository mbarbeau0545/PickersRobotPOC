"""
#  @file        FMKSRL_CodeGen.py
#  @brief       Make Code Generation for the Module FMKSRL.
#
#  @author      mba
#  @date        08/01/2025
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

from .FMKMAC_CodeGen import ENUM_FMKMAC_DMARQST
#------------------------------------------------------------------------------
#                                       CONSTANT
#------------------------------------------------------------------------------
ENUM_FMKSRL_LINE = 'FMKSRL_SERIAL_LINE'
ENUM_FMKSRL_HW_PROT = 'FMKSRL_HW_PROTOCOL'

TARGET_BUFF_MAPP_START = '    /* CAUTION : Automatic generated code section for Buffer Mapping: Start */\n'
TARGET_BUFF_MAPP_END =   '    /* CAUTION : Automatic generated code section for Buffer Mapping: End */\n'
TARGET_IRQN_HDLR_START = '/* CAUTION : Automatic generated code section for UART/USART IRQHandler: Start */\n'
TARGET_IRQN_HDLR_END = '/* CAUTION : Automatic generated code section for UART/USART IRQHandler: End */\n'
FMKSRL_CFGSPEC_C   = 'src\\1_FMK\FMK_CFG\FMKCFG_ConfigSpecific\FMKSRL_ConfigSpecific.c'
FMKSRL_CFGPUBLIC   = 'src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKSRL_ConfigPublic.h'
FMKSRL_CFGPRIVATE  = 'src\\1_FMK\FMK_CFG\FMKCFG_ConfigFiles\FMKSRL_ConfigPrivate.h'
FMKSRL_CFILE       = 'src\\1_FMK\FMK_HAL\FMK_SRL\Src\FMK_SRL.c'
# CAUTION : Automatic generated code section: Start #

# CAUTION : Automatic generated code section: End #
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------

class FMKSRL_CodeGen():
    """
        Make code generation for FMKMAC module which include 
        file FMKSRL_ConfigPublic.h : 
            - Enum pour toutes les serial Lines UART/USART                               
            
        file FMKSRL_ConfigPrivate.h :
            - Mapping between Serial Line and Instance


        file  FMKSRL.c
            - variable SrlInfo
            - Rx/Tx buffer for each serial Line
            - Link between Rx/Tx Buffer and Serial Line
            - Irqn Handler
    """
    code_gen = LCFE()

    @classmethod
    def code_genration(cls, f_hw_cfg) -> None:

        # load array needed
        cls.code_gen.load_excel_file(f_hw_cfg)

        info_array = cls.code_gen.get_array_from_excel('FMKSRL_INFO')[1:]
       
        enm_srline = ''
        cst_mapp_istnc = ''
        var_srl_info = ''
        irqn_hdlr = ''
        var_RxTx_buffer = ''
        mapp_buffer = ''
        #----------------------------------------------------------------
        #-------------------------------Make Enum -----------------------
        #----------------------------------------------------------------
        max_line = len(info_array)
        print(max_line)
        enm_srline = cls.code_gen.make_enum_from_variable(ENUM_FMKSRL_LINE, [idx for idx in range(1, (max_line + 1))],
                                                            't_eFMKSRL_SerialLine', 0,
                                                            "Enum for Serial Line Available on CPU",
                                                            [f'Reference to Hardware Instance {info_line[0]}' for info_line in info_array])
        
        #----------------------------------------------------------------
        #----------------------------Make Mapping LINE to UART/USART --------------
        #----------------------------------------------------------------
        cst_mapp_istnc += '    /**\n' \
                        +    '    * @brief Mapping between Serial Line And Bsp Handle Typedef\n' \
                        +    '    */\n' \
                        + f'    USART_TypeDef * c_FmkSrl_BspInitIstcMapp_pas[{ENUM_FMKSRL_LINE}_NB]' +  ' = {\n'
        var_srl_info += '/**< Store the Serial Info for all lines */\n' \
                     + f'static t_sFMKSRL_SerialInfo g_SerialInfo_as[{ENUM_FMKSRL_LINE}_NB]' + ' = {'
        
        tx_size_buff = 0
        rx_size_buff = 0
        is_istce_used = True
        for idx, line_info  in enumerate(info_array):
            idx_line = int(idx+1)

            # code generation for Var Tx/Rx Buffer
            # Buffer Size equals 0 if user didn't set it
            if line_info[2] == None or str(line_info[3]) == '0':
                rx_size_buff = 0
                is_istce_used = False
            else:
                is_istce_used = True
                rx_size_buff = line_info[2]

            if line_info[3] == None or str(line_info[3]) == '0':
                tx_size_buff = 0
                is_istce_used = False
            else:
                is_istce_used = True
                tx_size_buff = line_info[3]

            var_RxTx_buffer += f'//--------- Tx, Rx Buffer for Serial Line {idx_line} ---------//\n' \
                            + f'static t_uint8 g_SrlLine_{idx_line}_RxBuffer_ua8[{rx_size_buff}];\n' \
                            + f'static t_uint8 g_SrlLine_{idx_line}_TxBuffer_ua8[{tx_size_buff}];\n' \
                            + '\n'
            
            # code generation for mapping instance
            cst_mapp_istnc += f'        {line_info[0]},' \
                            + ' ' * (SPACE_VARIABLE - len(f'{line_info[0]}')) \
                            + f' // Reference to Serial Line {idx_line} \n'
                            
            # code generation for Serial info
            var_srl_info += f'    [{ENUM_FMKSRL_LINE}_{idx_line}]' + ' = {\n' \
                            + f'        .c_clockPort_e = {ENUM_FMKCPU_RCC_ROOT}_{line_info[0]},\n' \
                            + f'        .c_HwType_e    = {ENUM_FMKSRL_HW_PROT}_{str(line_info[0])[:-1]},\n' \
                            + f'        .c_IRQNType_e  = {ENUM_FMKCPU_NVIC_ROOT}_{line_info[0]}_IRQN,\n'
            
            if is_istce_used:
                var_srl_info +=  f'        .c_DmaRqstRx   = {ENUM_FMKMAC_DMARQST}_{line_info[0]}_RX,\n' \
                                + f'        .c_DmaRqstTx   = {ENUM_FMKMAC_DMARQST}_{line_info[0]}_TX,\n' 
            else: 
                var_srl_info +=  f'        .c_DmaRqstRx   = (t_eFMKMAC_DmaRqst)NULL,\n' \
                             + f'        .c_DmaRqstTx   = (t_eFMKMAC_DmaRqst)NULL,\n' 
                
            var_srl_info   +=  '    },\n\n'
            
            
            #code generation for IRQN Handler
            irqn_hdlr += '/*********************************\n' \
                        + f'* {line_info[1]}\n' \
                        +'*********************************/\n' \
                        + f'void {line_info[1]}(void)\n' \
                        + '{\n' + f'    if(g_SerialInfo_as[FMKSRL_SERIAL_LINE_{idx_line}].isLineConfigured_b == (t_bool)True)\n' \
                        + '    {\n' + f'        if(g_SerialInfo_as[FMKSRL_SERIAL_LINE_{idx_line}].SoftType_e == FMKSRL_HW_PROTOCOL_UART)\n' \
                        + '            {\n' + f'            HAL_UART_IRQHandler((UART_HandleTypeDef *)(&g_SerialInfo_as[FMKSRL_SERIAL_LINE_{idx_line}].bspHandle_u));\n' + '        }\n' \
                        + f'        else if(g_SerialInfo_as[FMKSRL_SERIAL_LINE_{idx_line}].SoftType_e == FMKSRL_HW_PROTOCOL_USART)\n' \
                        + '        {\n' + f'            HAL_USART_IRQHandler((USART_HandleTypeDef *)(&g_SerialInfo_as[FMKSRL_SERIAL_LINE_{idx_line}].bspHandle_u));\n' + '        }\n' \
                        + '    }\n' + '}\n\n'
            
            # code generation for buffer-serial_line mapping
            mapp_buffer +=  f'    //--------- Buffer Mapping for Serial Line {idx_line} ---------//\n' \
                        +  '    //--------- Rx Buffer ---------//\n' \
                        + f'    g_SerialInfo_as[FMKSRL_SERIAL_LINE_{idx_line}].RxInfo_s.Buffer_s.bufferAdd_pu8 = (t_uint8 *)(&g_SrlLine_{idx_line}_RxBuffer_ua8);\n' \
                        + f'    g_SerialInfo_as[FMKSRL_SERIAL_LINE_{idx_line}].RxInfo_s.Buffer_s.buffferSize_u16 = (t_uint16){rx_size_buff};\n' \
                        +  '    //--------- Tx Buffer ---------//\n' \
                        + f'    g_SerialInfo_as[FMKSRL_SERIAL_LINE_{idx_line}].TxInfo_s.Buffer_s.bufferAdd_pu8 = (t_uint8 *)(&g_SrlLine_{idx_line}_TxBuffer_ua8);\n' \
                        + f'    g_SerialInfo_as[FMKSRL_SERIAL_LINE_{idx_line}].TxInfo_s.Buffer_s.buffferSize_u16 = (t_uint16){rx_size_buff};\n' \
                        + '\n'
                        
        var_srl_info += '};\n'
        cst_mapp_istnc += '    };\n\n'
                 
        #-----------------------------------------------------------
        #------------code genration for FMKCPU module---------------
        #-----------------------------------------------------------
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<Start code generation for FMFSRL Module>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print('\t- For Config Public File ')
        cls.code_gen.change_target_balise(TARGET_T_ENUM_START_LINE, TARGET_T_ENUM_END_LINE)

        print('\t\t- For Serial Line')
        cls.code_gen._write_into_file(enm_srline, FMKSRL_CFGPUBLIC)

        print('\t- For Config Private File ')
        cls.code_gen.change_target_balise(TARGET_T_VARIABLE_START_LINE, TARGET_T_VARIABLE_END_LINE)

        print('\t\t- For constant mapping instance')
        cls.code_gen._write_into_file(cst_mapp_istnc, FMKSRL_CFGPRIVATE)

        print('\t- For FMKMAC.c File ')

        print('\t\t- For Srl Info variable')
        cls.code_gen.change_target_balise(TARGET_VARIABLE_START_LINE, TARGET_VARIABLE_END_LINE)
        cls.code_gen._write_into_file(var_srl_info, FMKSRL_CFILE)
        cls.code_gen._write_into_file(var_RxTx_buffer, FMKSRL_CFILE)

        print('\t\tFor IRQN Handler')
        cls.code_gen.change_target_balise(TARGET_BUFF_MAPP_START, TARGET_BUFF_MAPP_END)
        cls.code_gen._write_into_file(mapp_buffer, FMKSRL_CFILE)

        print('\t\tFor IRQN Handler')
        cls.code_gen.change_target_balise(TARGET_IRQN_HDLR_START, TARGET_IRQN_HDLR_END)
        cls.code_gen._write_into_file(irqn_hdlr, FMKSRL_CFILE)

      
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<End code generation for FMFSRL Module>>>>>>>>>>>>>>>>>>>>")
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

