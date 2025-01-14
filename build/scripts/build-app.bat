@echo off
setlocal

:: Function to build the source code
:buildTheSourceCode
set filename=%1
set arg=%2
for %%f in (%filename%) do (
    set "name=%%~nf"
    set "extension=%%~xf"
)

:: Check if the extension is .c or .cpp
if /I "%extension%"==".c" (
    gcc -I../../include %filename% %arg%
) else if /I "%extension%"==".cpp" (
    g++ -I../../include %filename% %arg%
)
goto :eof

:: Save the current directory
set "olPWD=%cd%"

:: Change to the script's directory
cd /d "%~dp0" || (
    timeout /t 1 >nul
    exit /b 1
)

:: Call the build function
call :buildTheSourceCode %1 %2

:: Change back to the original directory
cd /d "%olPWD%"

endlocal