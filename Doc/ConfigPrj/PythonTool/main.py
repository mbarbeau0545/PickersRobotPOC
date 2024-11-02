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
from FMK_CodeGen.FMKCPU_CodeGen import FMKCPU_CodeGen as FMKCPU
from FMK_CodeGen.FMKIO_CodeGen  import FMKIO_CodeGen as FMKIO
from FMK_CodeGen.FMKCDA_CodeGen  import FMKCDA_CodeGen as FMKCDA
from App_CodeGen.AppSns_CodeGen import AppSns_CodeGen as APPSNS
from App_CodeGen.AppAct_CodeGen import AppAct_CodeGen as APPACT
#------------------------------------------------------------------------------
#                                       CONSTANT
#------------------------------------------------------------------------------
# CAUTION : Automatic generated code section: Start #

# CAUTION : Automatic generated code section: End #
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#                             FUNCTION IMPLMENTATION
#------------------------------------------------------------------------------
def main()-> None:
    
    FMKCPU.code_generation()
    FMKCDA.code_genration()
    FMKIO.code_generation()
    APPSNS.code_generation()
    APPACT.code_generation()
    return
#------------------------------------------------------------------------------
#			                MAIN
#------------------------------------------------------------------------------
if (__name__ == '__main__'):
    main()

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

