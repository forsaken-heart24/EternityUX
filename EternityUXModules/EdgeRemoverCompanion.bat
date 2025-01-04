if '%1' == '--remove-edge-leftovers' (
    rd /s /q "%ProgramFiles%\Microsoft\Edge" > nul
    rd /s /q "%ProgramFiles%\Microsoft\EdgeCore" > nul
    rd /s /q "%ProgramFiles%\Microsoft\EdgeUpdate" > nul
    rd /s /q "%ProgramFiles%\Microsoft\EdgeWebView" > nul
    rd /s /q "%ProgramFiles%\Microsoft\Temp" > nul
    del /f /q "%userprofile%\Desktop\Microsoft Edge.lnk" > nul
    del /f /q "%systemdrive%\Users\Public\Desktop\Microsoft Edge.lnk" > nul
    del /f /q "%ProgramData%\Microsoft\Windows\Start Menu\Programs\Microsoft Edge.lnk" > nul
    del /f /q "%appdata%\Microsoft\Windows\Start Menu\Programs\Microsoft Edge.lnk" > nul
    del /f /q "%appdata%\Microsoft\Internet Explorer\Quick Launch\User Pinned\TaskBar\Microsoft Edge.lnk" > nul
    del /f /q "%userprofile%\\Desktop\\Microsoft Edge.lnk"
    exit
)