@echo off

echo This Windows script (uaf-powershell.bat) should be executed in Windows PowerShell
echo and does the following:
echo  - it prepends the uaf\lib directory to the PATH environment variable
echo  - it prepends the uaf\lib directory to the PYTHONPATH environment variable
:: =============================================================================

:: How it works:
::  - change the environment variables in the .bat (command prompt) environment
::  - from this environment, launch Windows PowerShell

cd /d %~dp0
set PATH=%~dp0..\lib;%PATH%
set PYTHONPATH=%~dp0..\lib;%PYTHONPATH%

echo.
echo New PATH: 
echo %PATH%

echo.
echo New PYTHONPATH:
echo %PYTHONPATH%

PowerShell
