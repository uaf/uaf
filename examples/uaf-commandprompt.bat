@echo off

echo This Windows script (uaf-commandprompt.bat) should be executed in Command prompt
echo and does the following:
echo  - it appends the uaf\lib directory to the PATH environment variable
echo  - it appends the uaf\lib directory to the PYTHONPATH environment variable
echo
:: =============================================================================

cd /d %~dp0
set PATH=%PATH%;%~dp0..\lib
set PYTHONPATH=%PYTHONPATH%;%~dp0..\lib

echo.
echo New PATH: 
echo %PATH%

echo.
echo New PYTHONPATH:
echo %PYTHONPATH%