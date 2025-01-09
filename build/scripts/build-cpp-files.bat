@echo off
setlocal enabledelayedexpansion

:: Get the first argument
set "wrapperApplicationSourceCode=%1"

:compile_program
:: Function to compile the program
set "theDawnGivenValue=%1"
set "theDawnArguments=%2"

:: Return false if the argument is not available
if "%theDawnGivenValue%"=="" exit /b 1

:: Extract the file extension and compile based on it
set "fileExtension=!theDawnGivenValue:~-1,1!"
if "!fileExtension!"=="c" (
    gcc %theDawnArguments%
    exit /b 0
) else (
    set "fileExtension=!theDawnGivenValue:~-3!"
    if "!fileExtension!"=="cpp" (
        g++ %theDawnArguments%
        exit /b 0
    )
)

:: Return false if not C or C++
exit /b 1

:: Main script logic
if "%wrapperApplicationSourceCode%"=="" (
    echo No source code file provided.
    exit /b 1
)

if exist "%wrapperApplicationSourceCode%" (
    :: Get the executable name by stripping the extension
    set "wrapperApplicationSourceCodeIntoTheExecutable=%wrapperApplicationSourceCode:~0,-4%"
    echo Building %wrapperApplicationSourceCodeIntoTheExecutable%...

    :: Call the compile function
    call :compile_program "%wrapperApplicationSourceCode%" "-I../include %wrapperApplicationSourceCode% -o %wrapperApplicationSourceCodeIntoTheExecutable%"
    if errorlevel 1 (
        echo The build failed, please try again later!
        exit /b 1
    )

    echo Hit "Enter" to try testing the build!
    pause>0
    chmod 755 %wrapperApplicationSourceCodeIntoTheExecutable%
    .\%wrapperApplicationSourceCodeIntoTheExecutable% --test
)
