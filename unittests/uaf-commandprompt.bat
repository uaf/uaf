@echo off

echo This Windows script (uaf-commandprompt.bat) should be executed in Command prompt
echo and does the following:
echo  - it prepends the uaf\lib directory to the PATH environment variable
echo  - it prepends the uaf\lib directory to the PYTHONPATH environment variable
echo
:: =============================================================================

cd /d %~dp0
set PATH=%~dp0..\lib;%PATH%
set PYTHONPATH=%~dp0..\lib;%PYTHONPATH%

echo.
echo New PATH: 
echo %PATH%

echo.
echo New PYTHONPATH:
echo %PYTHONPATH%
