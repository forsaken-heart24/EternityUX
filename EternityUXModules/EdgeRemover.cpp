#include "EternityUXApplibrary.h"
#include <windows.h>
#include <shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

int main() {
        const char *edgeExecutables[] = {
            "msedge.exe",
            "MicrosoftEdgeUpdate.exe",
            "msedgewebview2.exe"
        };
        char *edgeRegistryKeysToTinker[] = {
            "delete HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft Edge /f",
            "delete HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft Edge Update /f",
            "delete HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft EdgeWebView /f",
            "add HKLM\\Software\\Microsoft\\EdgeUpdate /v DoNotUpdateToEdgeWithChromium /t REG_DWORD /d 1 /f",
            "add HKLM\\Software\\WOW6432Node\\Microsoft\\EdgeUpdate /v DoNotUpdateToEdgeWithChromium /t REG_DWORD /d 1 /f"
        };
    if (WindowsMessageQuestionBox("Do you really want to uninstall Microsoft Edge?")) {
        for(i = 0; i < 3; i++) {
            taskKill(edgeExecutables[i]);
        }
        for(i = 0; i < 6; i++) {
            executeInternalSystemCommands("reg", edgeRegistryKeysToTinker[i]);
        }
        executeInternalSystemCommands("net", "stop MicrosoftEdgeElevationService");
        executeInternalSystemCommands("sc", "delete MicrosoftEdgeElevationService");
        executeInternalSystemCommands("net", "stop edgeupdate");
        executeInternalSystemCommands("sc", "delete edgeupdate");
        executeInternalSystemCommands("net", "stop edgeupdatem");
        executeInternalSystemCommands("sc", "delete edgeupdatem");
        executeInternalSystemCommands("Senorita-companion.bat", "--remove-edge-leftovers");
        if(WindowsMessageQuestionBox("Microsoft Edge uninstalled, please select \'yes\' to reboot and keep the changes")) {
            executeInternalSystemCommands("shutdown", "-r -t 0");
        }
    }
}