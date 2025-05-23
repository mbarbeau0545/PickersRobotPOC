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
import sys,os

from FMK_CodeGen.FMKCPU_CodeGen import FMKCPU_CodeGen as FMKCPU
from FMK_CodeGen.FMKTIM_CodeGen import FMKTIM_CodeGen as FMKTIM
from FMK_CodeGen.FMKIO_CodeGen  import FMKIO_CodeGen as FMKIO
from FMK_CodeGen.FMKCDA_CodeGen  import FMKCDA_CodeGen as FMKCDA
from FMK_CodeGen.FMKCPU_CodeGen  import FMKCPU_CodeGen as FMKCPU
from FMK_CodeGen.FMKSRL_CodeGen  import FMKSRL_CodeGen as FMKSRL
from App_CodeGen.AppSns_CodeGen import AppSns_CodeGen as APPSNS
from App_CodeGen.AppAct_CodeGen import AppAct_CodeGen as APPACT
from App_CodeGen.AppSdm_CodeGen import AppSdm_CodeGen as APPSDM
from App_CodeGen.AppLgc_CodeGen import AppLgc_CodeGen as APPLGC
#------------------------------------------------------------------------------
#                                       CONSTANT
#------------------------------------------------------------------------------
# CAUTION : Automatic generated code section: Start #

# CAUTION : Automatic generated code section: End #
#------------------------------------------------------------------------------
#                                       CLASS
#------------------------------------------------------------------------------
class PythonToolArgError(Exception):
    def __init__(self, message):
        super().__init__(message)

#------------------------------------------------------------------------------
#                             FUNCTION IMPLMENTATION
#------------------------------------------------------------------------------
def main()-> None:
    if not len(sys.argv) == 3:
        raise PythonToolArgError(f"Expected two argument : hardware configuration and software.\n Get {len(sys.argv)} instead")
    hardware_cfg_path = str(sys.argv[1])
    software_cfg_path = str(sys.argv[2])

    if not (os.path.isfile(hardware_cfg_path) 
        or  os.path.isfile(software_cfg_path)):
        FileNotFoundError("Expected two argument, hardware configuration and software.")

    print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
    print('Start Python tool with')
    print(f'\tHardware Confiougration Path -> {hardware_cfg_path}')
    print(f'\tSoftware Confiougration Path -> {software_cfg_path}')
    print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")

    FMKCPU.code_generation(hardware_cfg_path)
    FMKTIM.code_generation(hardware_cfg_path)
    FMKCDA.code_genration(hardware_cfg_path)
    FMKSRL.code_genration(hardware_cfg_path)
    FMKIO.code_generation(hardware_cfg_path)
    APPSNS.code_generation(software_cfg_path)
    APPACT.code_generation(software_cfg_path)
    APPSDM.code_generation(software_cfg_path)
    APPLGC.code_generation(software_cfg_path)

    print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
    print("<<<<<<<<<<<<<<<<<Successfuly made code generation for project>>>>>>>>>>>>>>>>>")
    print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>")
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

