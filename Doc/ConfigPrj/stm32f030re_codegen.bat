@echo off
REM Spécifiez le chemin vers l'exécutable Python si nécessaire
set PYTHON_PATH=python

cd /d %~dp0\..\..

REM Exécuter le script Python avec des arguments fixes
%PYTHON_PATH% Doc/ConfigPrj/PythonTool/main.py Doc\ConfigPrj\ExcelCfg\STM32F030R8\STM32F030R8_HwCfg.xlsx Doc\ConfigPrj\ExcelCfg\STM32F030R8\STM32F030R8_SwCfg.xlsm

echo Press any key to continue...
pause