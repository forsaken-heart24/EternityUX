#include <windows.h>
#include "EternityUXApplibrary.h"
#pragma comment(lib, "Shlwapi.lib")

// This is the entry point for a GUI-based Windows application built using EternityUXApplibrary.h
int DoiHaveGUIElementSupport = 0;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if(!isAdmin()) 
        WindowsMessageToastBox("Please run this application with administrator privilages!");
        exit(1);

    const char *edgeExecutables[] = {
        "msedge.exe",
        "MicrosoftEdgeUpdate.exe",
        "msedgewebview2.exe"
    };
    const char *edgeRegistryKeysToTinker[] = {
        "delete HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft Edge /f",
        "delete HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft Edge Update /f",
        "delete HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft EdgeWebView /f",
        "add HKLM\\Software\\Microsoft\\EdgeUpdate /v DoNotUpdateToEdgeWithChromium /t REG_DWORD /d 1 /f",
        "add HKLM\\Software\\WOW6432Node\\Microsoft\\EdgeUpdate /v DoNotUpdateToEdgeWithChromium /t REG_DWORD /d 1 /f"
    };
    if (WindowsMessageQuestionBox("Do you really want to uninstall Microsoft Edge?")) {
        for (int i = 0; i < 3; i++) {
            taskKill(edgeExecutables[i]);
        }
        for (int i = 0; i < 6; i++) {
            executeInternalSystemCommands("reg", edgeRegistryKeysToTinker[i]);
        }
        executeInternalSystemCommands("net", "stop MicrosoftEdgeElevationService");
        executeInternalSystemCommands("sc", "delete MicrosoftEdgeElevationService");
        executeInternalSystemCommands("net", "stop edgeupdate");
        executeInternalSystemCommands("sc", "delete edgeupdate");
        executeInternalSystemCommands("net", "stop edgeupdatem");
        executeInternalSystemCommands("sc", "delete edgeupdatem");
        executeInternalSystemCommands("rd", "/s /q \"%ProgramFiles%\\Microsoft\\Edge\" > nul");
        executeInternalSystemCommands("rd", "/s /q \"%ProgramFiles%\\Microsoft\\EdgeCore\" > nul");
        executeInternalSystemCommands("rd", "/s /q \"%ProgramFiles%\\Microsoft\\EdgeUpdate\" > nul");
        executeInternalSystemCommands("rd", "/s /q \"%ProgramFiles%\\Microsoft\\EdgeWebView\" > nul");
        executeInternalSystemCommands("rd", "/s /q \"%ProgramFiles%\\Microsoft\\Temp\" > nul");
        executeInternalSystemCommands("del", "/f /q \"%userprofile%\\Desktop\\Microsoft Edge.lnk\" > nul");
        executeInternalSystemCommands("del", "/f /q \"%systemdrive%\\Users\\Public\\Desktop\\Microsoft Edge.lnk\" > nul");
        executeInternalSystemCommands("del", "/f /q \"%ProgramData%\\Microsoft\\Windows\\Start Menu\\Programs\\Microsoft Edge.lnk\" > nul");
        executeInternalSystemCommands("del", "/f /q \"%appdata%\\Microsoft\\Windows\\Start Menu\\Programs\\Microsoft Edge.lnk\" > nul");
        executeInternalSystemCommands("del", "/f /q \"%appdata%\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar\\Microsoft Edge.lnk\" > nul");
        executeInternalSystemCommands("del", "/f /q \"%userprofile%\\Desktop\\Microsoft Edge.lnk\" > nul");
        if (WindowsMessageQuestionBox("Microsoft Edge uninstalled, please select 'yes' to reboot and keep the changes")) {
            executeInternalSystemCommands("shutdown", "-r -t 0");
        }
    }
}