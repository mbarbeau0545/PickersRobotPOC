# STM32 Template Project 
This project purpose is to offers a framework/interface that works with any stm32.
The main idea of this project is no matter the MCU used the logic will always works because it is not directly related to a hardware MPU/CPU
## Summary 
- [Get Started](#Get Started)
- Annexe 1, Hardware Configuration tutorial
- Annexe 2, Software Configuration tutorial

## Get Started
- First, install all dependencies needed :
    - Draw.io (to see Architecture Documentation of Module)
    - Visual Studio Code
    - On Visual Studio Code, install Platform.io
    - On platflorm.io install the framework of stm32 "ST STM32" on the tab PIO Home/Platforms
- Then, clone the branch Dev on your local disk
- Go in file platform.ini and choose the right nucleo board, the one you're using. To do so, all the board managed by platform io are in PIO Home/Board, find your nucleo or the MCU name, that will generate some code
- Look the documentation on Doc/InfoPrj for more documentation on this project. Each module has a Draw.io documentation, Click on it and look the tab 'Spec' for global Information about what does the module.
For the doxygen documentation search the file "index.html"
- Once it is done, you have to configure the Excel in Doc/ConfigPrj/ExcelCfg/Hardware_Configuration, see in Annexe 1 how to do so.
- Do the same for the Software_Configuration, Annexe 2. (not a restriction if user just want to test signal)
- To generate configuration in files from Excel (Hardware and Software) configuration, go to Doc/ConfigPrj/PythonTool and launch the main.py file. To do so wether the CPU you're using is already in stm32xxxx_code_gen.bat if not, create by copying one of the .bat and change the path for Excel Hardware/Software Configuration.\n
- Now you can Build/Flash you're project using platform.io framework
- Put your code in the file APP_LGC.c, in function APPLGC_Init to run once and APPLGC_Cyclic to run cyclically


## Annexe 1
- Take te datasheet of your stm32 microcontrôler
- Open the Hardware_Configuration file
- Go to the General Info sheet
- Put the hardware configuration as ask by the arrays on this sheet, the first array, you just have to copied/pasted the enum IRQn_Type in file stm32fXXYY
- For RCC Clock, go to the stm32_hal_rcc.h file and find 'RCC_Exported_Macros', copy every clock in the excel array.
- For timer/adc/dac/dma etc put the right information and keep it as so for example for timers it's 'timer' + '_' + 'number'
- Go to the sheet FMKIO and filled all tables as asking, Find The alternate Function in Datasheet, alll information are in the array
	for PWM purpose be careful on which timer you choose, some of them are not meant to make pwm signal
- Go to the sheet CPU and inform the timer used for event timers whhich means periodic timer
- Save and Generate code from Doc/ConfigPrj/PythonToolmain.py file.

## Left to do
- Faire un module Diagnostic Event Management
- Faire un module Supply Voltage Control
- Faire l'intégration MatLab du projet
- Faire un module USART
- Mettre à jour la documentation 
