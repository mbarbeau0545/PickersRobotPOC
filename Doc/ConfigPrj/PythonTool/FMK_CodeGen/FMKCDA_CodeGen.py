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
                                                    TARGET_T_STRUCT_END_LINE
#------------------------------------------------------------------------------
#                                       CONSTANT
#------------------------------------------------------------------------------
TARGET_ADC_SWITCH_START = "            /* CAUTION : Automatic generated code section for switch_case ADC channel: Start */\n"
TARGET_ADC_SWITCH_END   = "            /* CAUTION : Automatic generated code section for switch_case ADC channel: End */\n"
TARGET_ADC_CHNLNB_START = "    /* CAUTION : Automatic generated code section for ADC channels number: Start */\n"
TARGET_ADC_CHNLNB_END   = "    /* CAUTION : Automatic generated code section for ADC channels number: End */\n"

# CAUTION : Automatic generated code section: Start #

# CAUTION : Automatic generated code section: End #
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------
class FMKCDA_CodeGen():
    """
        Make code generation for FMKCDA module which include 
        file FMKCDA_ConfigPublic.h : 
            - Enum Adc Channel                                
            - Enum Adc                                 
        
        file FMKCDA_ConfigPrivate.h :
            define ADC_x max channel
            varaible ADCx max channel

        file  FMK_CDA.c
            - variable g_AdcInfo_as init 
            - varaible for scan mode counter rank              
            - switch case Adc channel to bsp channel 
    """
    code_gen = LCFE()

    @classmethod
    def code_genration(cls) -> None:
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<Start code generation for FmkCda Module>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        # load array needed
        cls.code_gen.load_excel_file(HARDWARE_CFG_PATH)
        #irqn_cfg_a = cls.code_gen.get_array_from_excel("GI_IRQN")
        adc_astr  = cls.code_gen.get_array_from_excel("GI_ADC")[1:]
        dac_astr  = cls.code_gen.get_array_from_excel("GI_DAC")[1:]

        enum_adc = ""
        enum_adc_channel = ""
        switch_adc_channel = ""
        var_adc_info = ""
        var_rank_counter = ""
        var_adc_max_channel =""
        def_adcx_max_channel = ""
        max_adc_channel: int = 0
        #----------------------------------------------------------------
        #-----------------------------make adc enum----------------------
        #-----------------------------------------------------------------
        enum_adc = cls.code_gen.make_enum_from_variable(ENUM_ADC_ISCT_ROOT, [str(adc_info[0][4:]) for adc_info in adc_astr],
                                                          "t_eFMKCDA_Adc", 0 , "NUmber of ADC in this harware",
                                                          [f"Reference to HAL ADC{adc_info[0][4:]}" for adc_info in adc_astr])
        #----------------------------------------------------------------
        #-----------------------------make adc channel enum--------------
        #--------------------------make adc channel max define-----------
        #-------------------------------make adc info--------------------
        #-----------------------------------------------------------------
        var_adc_info += "/**< Store the Adc Info variable*/\n" \
                        +"t_sFMKCDA_AdcInfo g_AdcInfo_as[FMKCDA_ADC_NB] = {\n"
        var_rank_counter += "/**< Rank for each channel add for ADC */\n"\
                            + "t_uint8 g_counterRank_au8[FMKCDA_ADC_NB] = {\n"
        var_adc_max_channel += "    /**< Variable for Adc Max channel*/\n" \
                            + "    const t_uint8 c_FmkCda_AdcMaxChnl_ua8[FMKCDA_ADC_NB] = {\n"
        for adc_info in adc_astr:
            adc_index = adc_info[0][4:]
            # know the max adc channel
            if(adc_info[1] > max_adc_channel):
                max_adc_channel = int(adc_info[1])
            # make define max ADCx channel
            def_adcx_max_channel += f"    #define FMKCDA_ADC_{adc_index}_MAX_CHANNELS ((t_uint8){adc_info[1]})\n"
            #make adc info
            var_adc_info += "    {\n" + f"        // ADC_{adc_index}\n" \
                        + f"        .BspInit_s.Instance = ADC{adc_index},\n" \
                        + f"        .c_clock_e = {ENUM_FMKCPU_RCC_ROOT}_ADC{adc_index},\n" \
                        + f"        .c_IRQNType_e = {ENUM_FMKCPU_NVIC_ROOT}_ADC{adc_index}_IRQN,\n" \
                        + "    }\n"
            #make rank coutner 
            var_rank_counter += "    (t_uint8)1,\n"
            # make variable adc maxchannel
            var_adc_max_channel += f"        (t_uint8)FMKCDA_ADC_{adc_index}_MAX_CHANNELS,\n"

        var_adc_max_channel += "    };\n\n"
        var_adc_info += "};\n\n"
        var_rank_counter += "};\n\n"
        enum_adc_channel = cls.code_gen.make_enum_from_variable(ENUM_ADC_CHNL_ROOT, [int(idx) for idx in range(max_adc_channel)],
                                                                "t_eFMKCDA_AdcChannel", 0 , " Number of channel in ADC Instances",
                                                                  [f"Reference to HAL adc channel {int(idx)}" for idx in range(max_adc_channel)])

        #----------------------------------------------------------------
        #-----------------------------make channel switch case-----------
        #-----------------------------------------------------------------
        for idx in range(max_adc_channel):
            switch_adc_channel += f"            case {ENUM_ADC_CHNL_ROOT}_{int(idx)}:\n" \
                                 + f"                *f_bspChannel_32 = ADC_CHANNEL_{idx};\n" \
                                 + f"                break;\n"
        
        #-----------------------------------------------------------
        #------------code genration for FMKADC module---------------
        #-----------------------------------------------------------
        print("\t- For configPublic file")
        cls.code_gen.change_target_balise(TARGET_T_ENUM_START_LINE, TARGET_T_ENUM_END_LINE)
        print("\t\t- Enum for adc cahnnel")
        cls.code_gen._write_into_file(enum_adc_channel, FMKCDA_CONFIGPUBLIC)
        print("\t\t- Enum for adc")
        cls.code_gen._write_into_file(enum_adc, FMKCDA_CONFIGPUBLIC)
        cls.code_gen.change_target_balise(TARGET_ADC_CHNLNB_START, TARGET_ADC_CHNLNB_END)
        print("\t\t- define for max channel per adc")
        cls.code_gen._write_into_file(def_adcx_max_channel, FMKCDA_CONFIGPRIVATE)
        cls.code_gen.change_target_balise(TARGET_T_VARIABLE_START_LINE, TARGET_T_VARIABLE_END_LINE)
        cls.code_gen._write_into_file(var_adc_max_channel, FMKCDA_CONFIGPRIVATE)
        cls.code_gen.change_target_balise(TARGET_ADC_SWITCH_START, TARGET_ADC_SWITCH_END)
        print("\t\t- swtich case to find stm channel from enum")
        cls.code_gen._write_into_file(switch_adc_channel, FMKCDA)
        cls.code_gen.change_target_balise(TARGET_T_VARIABLE_START_LINE[4:], TARGET_T_VARIABLE_END_LINE[4:])
        print("\t\t- variable for Adc Info")
        cls.code_gen._write_into_file(var_rank_counter, FMKCDA)
        cls.code_gen._write_into_file(var_adc_info, FMKCDA)
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<End code generation for FmkCda Module>>>>>>>>>>>>>>>>>>>")
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

