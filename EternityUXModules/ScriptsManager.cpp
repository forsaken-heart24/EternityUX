#include <iostream>
#include <windows.h>
#include <shlwapi.h>
#include "EternityUXAppExternValues.h"
#pragma comment(lib, "Shlwapi.lib")

std::string toLower(const std::string& input) {
    std::string result = input;
    for (char& c : result) {
        c = std::tolower(c);
    }
    return result;
}

int main(int argc, char *argv[]) {
    HMODULE hDll = LoadLibrary("EternityUXAppLibrary.dll");
    if (!hDll) {
        fprintf(stderr, "Executable name must be provided to kill it\n");
        exit(1);
    }
    // load functions
    IsDebugFunc is_debug = (IsDebugFunc)GetProcAddress(hDll, "is_debug");
    IsDebugFunc manageReg = (IsDebugFunc)GetProcAddress(hDll, "manageReg");
    IsDebugFunc WindowsMessageToastBox = (IsDebugFunc)GetProcAddress(hDll, "WindowsMessageToastBox");
    // i'd be cooked if it doesn't work 💀
    if(toLower(argv[1]) == "--disable") { 
        if(toLower(argv[2]) == "-animations") {
            manageReg("add", "HKCU\\Control Panel\\Desktop", "UserPreferencesMask", "REG_BINARY", "9E 3E 5F 7F 3F 00 00 00");
            WindowsMessageToastBox("The System Animations have been disabled, please reboot the system if the settings haven't applied yet.");
        }
        else if(toLower(argv[2]) == "-background-apps") {
            manageReg("add", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\BackgroundAccessApplications", "GlobalUserDisabled", "DWORD", "0");
            manageReg("add", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search", "BackgroundAppGlobalToggle", "DWORD", "0");
            WindowsMessageToastBox("The background app services have been disabled, please reboot the system if the settings haven't applied yet.");
        }
        else if(toLower(argv[2]) == "-troubleshooting") {
            executeInternalSystemCommands("EternityUXHelperBatchScript.bat", "--Disable-TroubleShooting");
            WindowsMessageToastBox("The basic troubleshooting services have been disabled, please reboot the system if the settings haven't applied yet.");
        }
        else if(toLower(argv[2]) == "-windows-updates") {
            manageReg("add", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\PolicyManager\\current\\device\\Update", "ExcludeWUDriversInQualityUpdate", "REG_DWORD", "1");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\PolicyManager\\default\\Update", "ExcludeWUDriversInQualityUpdate", "REG_DWORD", "1");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", "ExcludeWUDriversInQualityUpdate", "REG_DWORD", "1");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "ExcludeWUDriversInQualityUpdate", "REG_DWORD", "1");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\PolicyManager\\default\\Update\\ExcludeWUDriversInQualityUpdate", "value", "REG_DWORD", "1");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Device Metadata", "PreventDeviceMetadataFromNetwork", "REG_DWORD", "1");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DriverSearching", "SearchOrderConfig", "REG_DWORD", "0");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DriverSearching", "DontSearchWindowsUpdate", "REG_DWORD", "1");
            WindowsMessageToastBox("The Windows Update services have been disabled, please reboot the system to apply the changes.");
        }
    }
    else if(toLower(argv[1]) == "--enable") { 
        else if(toLower(argv[2]) == "-animations") {
            manageReg("add", "HKCU\\Control Panel\\Desktop", "UserPreferencesMask", "REG_BINARY", "90 1E 03 80 10 00 00 00");
            WindowsMessageToastBox("The System Animations have been enabled, please reboot the system if the settings haven't applied yet.");
        }
        else if(toLower(argv[2]) == "-background-apps") {
            manageReg("delete", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\BackgroundAccessApplications", "GlobalUserDisabled", " ", " ");
            manageReg("delete", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search", "BackgroundAppGlobalToggle", " ", " ");
            WindowsMessageToastBox("The background app services have been enabled, please reboot the system to apply the changes.");
        }
        else if(toLower(argv[2]) == "-background-apps") {
            executeInternalSystemCommands("EternityUXHelperBatchScript.bat", "--Enable-TroubleShooting");
            WindowsMessageToastBox("The basic troubleshooting services have been enabled, please reboot the system to apply the changes.");
        }
        else if(toLower(argv[2]) == "-windows-updates") {
            manageReg("delete", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\PolicyManager\\current\\device\\Update", "ExcludeWUDriversInQualityUpdate", "", "");
            manageReg("delete", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\PolicyManager\\default\\Update", "ExcludeWUDriversInQualityUpdate", "", "");
            manageReg("delete", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", "ExcludeWUDriversInQualityUpdate", "", "");
            manageReg("delete", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "ExcludeWUDriversInQualityUpdate", "", "");
            manageReg("delete", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Device Metadata", "PreventDeviceMetadataFromNetwork", "", "");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\PolicyManager\\default\\Update\\ExcludeWUDriversInQualityUpdate", "value", "REG_DWORD", "0");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DriverSearching", "SearchOrderConfig", "REG_DWORD", "1");
            manageReg("delete", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DriverSearching", "DontSearchWindowsUpdate", "", "");
            WindowsMessageToastBox("The Windows Update services have been enabled, please reboot the system to apply the changes.");
        }
    }
    else if(toLower(argv[1]) == "--gui") {
        if(toLower(argv[2]) == "--old-alt-tab") {
            manageReg("add", "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", "AltTabSettings", "REG_DWORD", "1");
            WindowsMessageToastBox("The Alt-Tab have reverted to the old windows 7 style, please reboot the system if the settings haven't applied yet.");
        }
        else if(toLower(argv[2]) == "--new-alt-tab"){
            manageReg("add", "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", "AltTabSettings", "REG_DWORD", "1");
            WindowsMessageToastBox("The Alt-Tab have reverted back to the windows 10 style, please reboot the system if the settings haven't applied yet.");
        }
    }
    // Unload the DLL
    FreeLibrary(hDll);
}