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

## bugs
- Comprendre pourquoi HAL_Delay -> Infinite Loop
- Comprendre pourquoi FDCAN marche po lo
## Left to do
- Utiliser la LED builtin pour informer le Développer de l'état du µC
    - LED clignote lentement   -> Phase d'initialisation 
    - LED clignote rapidement  -> Phase d'initialisation échoué
    - LED clignote constamment -> L'application est lancé 
    - LED clignote plus        -> L'application est dans un état d'erreur

- Rendre automatique l'implémentation des TIM_IRQ_Handler et tous enfaite dans chaque fichier
- Faire un module Serial UART+USART
- Faire un module Diagnostic Event Management
- Faire un module Supply Voltage Control
- Faire l'intégration MatLab du projet

- Mettre à jour la documentation 
    - Mettre à jour la documentaiton drawio
    - Créer un script python qui fait une documentation générale du Projet avec toutes les API par Modules ?

- Dans le module FDCAN
    - Rendre InitDrv Public, ne pas supposer que tout le monde va l'utiliser 
    -  Inverser l'ordre de l'init, d'abord set Hw Clock et après Init
    - Update du flag FlagError Detected et gestion dans la cylic
    - Mettre la gestion du buffer dans t_sFMKFDCAN_CanInfo pour pouvoir géré pour chaque Node la Rx/Tx Software FiFo Size. en gros un pointeur vers une varaible qui est un tableau généré dynamiquemeent par la config EXcel
    - géré dynamiquement depuis la config Excel la software Fifo Rx/Tx.

Dans la Cfg FMKCPU
    - revoir la configuration des horloges et des prescalers de chaque module 
        la rendre  automatique en fonction des valeurs des fréquences de SYS_CLOCK

Dans FMKCPU, dans les fonctions de ChannelCfg
    Mettre l'initialisation du timer dans une autre fonction pour réduire la complexité de la fonction 'channelCfg'
    Appeler cette fonction (qui initialise le timer) dans channelCfg