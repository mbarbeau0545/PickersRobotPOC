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
from .APP_PATH import *
import os
import shutil
from .AppLgc_CodeGen import APPLGC_ENUM_SRV
from PyCodeGene import LoadConfig_FromExcel as LCFE, TARGET_T_END_LINE,TARGET_T_ENUM_END_LINE, \
                                                    TARGET_T_ENUM_START_LINE,TARGET_T_START_LINE,TARGET_T_VARIABLE_START_LINE,\
                                                    TARGET_T_VARIABLE_END_LINE,TARGET_T_STRUCT_START_LINE,\
                                                    TARGET_T_STRUCT_END_LINE,TARGET_T_INCLUDE_START, TARGET_T_INCLUDE_END
#------------------------------------------------------------------------------
#                                       CONSTANT
#------------------------------------------------------------------------------
APPSDM_ENUM_ROOT_DIAG_ITEM = "APPSDM_DIAG_ITEM"
APPSDM_ENM_DIAG_STRAT = "APPSDM_DIAG_STRAT"

TARGET_T_DIAG_STRAT_DECL_START_LINE = "    /* CAUTION : Automatic generated code section for Diag Strategy Function Declaration: Start */\n"
TARGET_T_DIAG_STRAT_DECL_END_LINE =   "    /* CAUTION : Automatic generated code section for Diag Strategy Function Declaration: End */\n"
TARGET_T_DIAG_STRAT_IMPL_START_LINE = "/* CAUTION : Automatic generated code section for Diag Strategy Function Implementation: Start */\n"
TARGET_T_DIAG_STRAT_IMPL_END_LINE =   "/* CAUTION : Automatic generated code section for Diag Strategy Function Implementation: End */\n"
# CAUTION : Automatic generated code section: Start #

# CAUTION : Automatic generated code section: End #
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------
class AppSdm_CodeGen():
    """
        Make code generation for FMKCDA module which include 
        file FMKSDM_ConfigPublic.h : 
            - Enum Item
            - Enum Strategy              
        
        file FMKSDM_ConfigPrivate.h :
            - variable for item diagnostic info 
            - varaible Strategy Applied Function

    """
    code_gen = LCFE()

    @classmethod
    def code_generation(cls, f_software_cfg) -> None:
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<Start code generation for AppAct Module>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        # Load needed excel arrays
        cls.code_gen.load_excel_file(f_software_cfg)
        items_cfg_a = cls.code_gen.get_array_from_excel("AppSdm_DiagItemInfo")[1:]
        strat_func_a = cls.code_gen.get_array_from_excel("AppSdm_ItemDiag")[1:]

        # make python varaible 
        enum_item = ""
        enum_strat = ""
        var_item_info = ""
        var_strat_cb = ""

        decl_strat_func = ""
        impl_strat_func = ""
        #-----------------------------------------------------------------
        #-----------------------------make all enum-----------------------
        #-----------------------------------------------------------------
        enum_item += "    /**\n" + "    * @brief Enum Diagnostic Item\n" + "    */\n"\
                    + "    typedef enum ____t_eAPPSDM_DiagnosticItem\n"\
                    + "    {\n"
        var_item_info += "    /**\n" + "    * @brief Diagnostic Item Configuration\n" + "    */\n"\
                    + f'    t_sAPPSM_DiagItemCfg c_AppSdm_DiagItemCfg_as[{APPSDM_ENUM_ROOT_DIAG_ITEM}_NB] =' + '{\n'\
                    + '        // DebuncerValueMs                        NotifyUser                     Log Error                      Applied Startegy\n'
        var_item_info += "    /**\n" + "    * @brief Variable for Diagnostic Item Information\n" + "    */\n"
        for idx, item_info in enumerate(items_cfg_a):
            if idx == 0:
                enum_item += f'        {APPSDM_ENUM_ROOT_DIAG_ITEM}_{str(item_info[1]).upper()} = 0x00,'
            else:
                enum_item += f'        {APPSDM_ENUM_ROOT_DIAG_ITEM}_{str(item_info[1]).upper()},'

            enum_item += " " * ((SPACE_VARIABLE) - len(f"{APPSDM_ENUM_ROOT_DIAG_ITEM}_{item_info[1]}"))\
                        + f'// {str(item_info[-1])}\n'
            
            var_item_info += '        {'\
                        + f'(t_uint16){item_info[2]},'\
                        + " " * ((SPACE_VARIABLE) - len(f"(t_uint16){item_info[2]},"))\
                        + f'(t_bool){item_info[3]},'\
                        + " " * ((SPACE_VARIABLE) - len(f"(t_bool){item_info[3]},"))\
                        + f'(t_bool){item_info[4]},'\
                        + " " * ((SPACE_VARIABLE) - len(f"(t_bool){item_info[4]},"))
            if str(item_info[5]) == 'None':
                var_item_info += f'{APPSDM_ENM_DIAG_STRAT}_NONE'
            else:
                var_item_info += f'{APPSDM_ENM_DIAG_STRAT}_{item_info[5]}'

            var_item_info += '},'\
                            + " " * ((SPACE_VARIABLE) - len(f"{APPSDM_ENM_DIAG_STRAT}_{str(item_info[5]).upper()}"))\
                            + f'// {item_info[1]}\n'
        
        enum_item += f'\n        {APPSDM_ENUM_ROOT_DIAG_ITEM}_NB,\n'
        enum_item += '    } t_eAPPSDM_DiagnosticItem;\n'
        var_item_info += '    };\n\n'
        
    
        #-----------------------------------------------------------------
        #------------------------make Strategy-----------------------------
        #-----------------------------------------------------------------
        var_strat_cb += "    /**\n" + "    * @brief Diagnostic Item Configuration\n" + "    */\n"\
                    + f'    t_cbAPPSDM_AppliedDiagStrategy * c_AppSdm_DiagStragies_apf[{APPSDM_ENM_DIAG_STRAT}_NB]' + '= {\n'
        enum_strat += "    /**\n" + "    * @brief Enum Diagnostic Strategy\n" + "    */\n"\
                    + "    typedef enum ____t_eAPPSDM_DiagnosticStrat\n"\
                    + "    {\n"
        for idx, strat_info in enumerate(strat_func_a):
            if strat_info[0] != None:
                if idx == 0:
                    enum_strat += f'        {APPSDM_ENM_DIAG_STRAT}_{str(strat_info[0]).upper()} = 0x00,'
                else:
                    enum_strat += f'        {APPSDM_ENM_DIAG_STRAT}_{str(strat_info[0]).upper()},'

                enum_strat += " " * ((SPACE_VARIABLE) - len(f"{APPSDM_ENUM_ROOT_DIAG_ITEM}_{strat_info[0]}"))\
                            + f'// {str(strat_info[-1])}\n'

                var_strat_cb += f'        APPSDM_SPEC_DiagStrat_{str(strat_info[0]).upper()},\n'

                decl_strat_func +=  "    /**\n" + f"    * @brief Stratefy Function : {strat_info[1]}\n" + "    */\n"\
                    + f'     APPSDM_SPEC_DiagStrat_{str(strat_info[0])}(t_eAPPSDM_DiagStratOpe f_stratOpe_e);\n\n'
                
                impl_strat_func += AppSdm_CodeGen.make_diag_strat_impl(strat_info)
        var_strat_cb += '    };\n\n'

        enum_strat += f'\n        {APPSDM_ENM_DIAG_STRAT}_NB,\n'
        enum_strat += f'\n        {APPSDM_ENM_DIAG_STRAT}_NONE,\n'
        enum_strat += '    } t_eAPPSDM_DiagnosticStrat;\n'

        
        #-----------------------------------------------------------------
        #------------------------make drivers-----------------------------
        #-----------------------------------------------------------------
       
        #-----------------------------------------------------------------
        #------------------------make code gen----------------------------
        #-----------------------------------------------------------------
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<Start code generation for AppSdm Module>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("\t- For configPublic file")
        print("\t\t- Write enum item and strategy")
        cls.code_gen.change_target_balise(TARGET_T_ENUM_START_LINE,TARGET_T_ENUM_END_LINE)
        cls.code_gen._write_into_file(enum_strat, APPSDM_CONFIGPUBLIC_PATH)
        cls.code_gen._write_into_file(enum_item, APPSDM_CONFIGPUBLIC_PATH)

        
        print("\t- For configPrivate file")
        cls.code_gen.change_target_balise(TARGET_T_VARIABLE_START_LINE,TARGET_T_VARIABLE_END_LINE)
        cls.code_gen._write_into_file(var_item_info, APPSDM_CONFIGPRIVATE_PATH)
        cls.code_gen._write_into_file(var_strat_cb, APPSDM_CONFIGPRIVATE_PATH)

        print("\t Config Specific")
        cls.code_gen.change_target_balise(TARGET_T_DIAG_STRAT_DECL_START_LINE, TARGET_T_DIAG_STRAT_DECL_END_LINE)
        cls.code_gen._write_into_file(decl_strat_func, APPSDM_CONGSPECIFIC_H)

        cls.code_gen.change_target_balise(TARGET_T_DIAG_STRAT_IMPL_START_LINE, TARGET_T_DIAG_STRAT_IMPL_END_LINE)
        cls.code_gen._write_into_file(impl_strat_func, APPSDM_CONGSPECIFIC_C)
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<End code generation for AppSdm Module>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n")
        
    @classmethod
    def make_diag_strat_impl(self, f_strat_info):
        retval = ''
        retval += '/*********************************\n'\
                + f'APPSDM_SPEC_DiagStrat_{str(f_strat_info[0])}\n'\
                + ' *********************************/\n'
        retval +=  f'APPSDM_SPEC_DiagStrat_{str(f_strat_info[0])}(t_eAPPSDM_DiagStratOpe f_stratOpe_e)\n' + '{\n'\
                + '    t_eAPPLGC_SrvHealth srvHealth_e;\n'\
                + '    t_eReturnCode Ret_e = RC_OK;\n\n'\
                + '    Ret_e = s_APPSDM_SPEC_GetHealthFromStratOpe(f_stratOpe_e, &srvHealth_e);\n\n'\
                
        for srv_implied in f_strat_info[2:]:
            if str(srv_implied) != 'None':
                retval +='    if(Ret_e == RC_OK)\n'\
                        + '    {\n'\
                        + f'        Ret_e = APPLGC_SetServiceHealth({APPLGC_ENUM_SRV}_{str(srv_implied).upper()}, srvHealth_e);\n'\
                        + '    }\n'
        retval += '\n' + '    return;\n' + '}\n\n'
        return retval
                

        
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

