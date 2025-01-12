whoami /user | find /i "S-1-5-18" > nul 2>&1 || (
    schtasks /create /tn "RunMeAsSystem" /tr  "%~f0" %* /sc onstart /rl highest
    schtasks /run /tn "RunMeAsSystem"
    schtasks /delete /tn "RunMeAsSystem" /f
    exit /b
)

if %1 == --Disable-TroubleShooting (
    sc config WdiServiceHost start= disabled
    sc config WdiSystemHost start= disabled
    sc config DPS start= disabled
) else if "%1" == "--Enable-TroubleShooting" (
    sc config WdiServiceHost start= auto
    sc config WdiSystemHost start= auto
) else (
    echo "Unknown option: %1"
    echo "Usage: scriptname [--Disable-TroubleShooting | who]"
)