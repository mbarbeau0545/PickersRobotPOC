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





# CAUTION : Automatic generated code section: Start #

# CAUTION : Automatic generated code section: End #
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------

class FMKCPU_CodeGen():
    """
        Make code generation for FMKCPU module which include 
        file FMKCPU_ConfigPublic.h : 
            - Enum avec tout les request types                               
            - Enum avec les DMA 
            - Enum avec les DMA channels         
            - enum adc internal TS_CAL_1, SUPPLY_VOLTAGE etc                   
        
        file FMKCPU_ConfigPrivate.h :
            - variable pour chaque RqstType, leur association avec Dma + Channel


        file  FMKCPU.c
            - variable DmaInfo
    """
    code_gen = LCFE()

    @classmethod
    def code_genration(cls, f_hw_cfg) -> None:

        # load array needed
        cls.code_gen.load_excel_file(f_hw_cfg)

        
        dma_cfg_array = cls.code_gen.get_array_from_excel('FMKCPU_Cfg')[1:]
        dma_irqn_list = cls.code_gen.get_array_from_excel('FMKCPU_IRQN')[1:]
        dmamux_list = cls.code_gen.get_array_from_excel('FMKCPU_DMAMUX')[1:]
        
        
        """
            'DMA1' : [ADC1,USART1_RX, USART1_TX,,,,,],
            'DMA2  : [FDCAN1_RX, FDCAN_TX, etc],
        """
       
        
        #----------------------------------------------------------------
        #-------------------------------Make Enum -----------------------
        #----------------------------------------------------------------

        
        
        
        
        
                 
                 
        #-----------------------------------------------------------
        #------------code genration for FMKCPU module---------------
        #-----------------------------------------------------------
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<Start code generation for FMFMAC Module>>>>>>>>>>>>>>>>>>>>")
        print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
        print('\t- For Config Public File ')
        cls.code_gen.change_target_balise(TARGET_T_ENUM_START_LINE, TARGET_T_ENUM_END_LINE)

        


        print('\t- For Config Private File ')
        


        print('\t- For FMKCPU.c File ')
        

        

        print('\t- For FMKCPU_ConfigSpecific.c File ')
        
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

