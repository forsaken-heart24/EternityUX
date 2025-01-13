#include "PredefinedExternityInitDeployerValues.h"
#include "EternityUXAppLibrary.h"
#include <iostream>
#include <unistd.h>
#include <shlwapi.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tlhelp32.h>
#pragma comment(lib, "Shlwapi.lib")

// GUI bs
int DoiHaveGUIElementSupport = 0;

void Eternity(const char *argvOne, const char *argvTwo) {
    if(std::string(argvOne) == "--disable") {
        if(std::string(argvTwo) == "-animations") {
            manageReg("add", "HKCU\\Control Panel\\Desktop", "UserPreferencesMask", "REG_BINARY", "9E 3E 5F 7F 3F 00 00 00");
            WindowsMessageToastBox("The System Animations have been disabled, please reboot the system if the settings haven't applied yet.");
        }
        else if(std::string(argvTwo) == "-background-apps") {
            manageReg("add", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\BackgroundAccessApplications", "GlobalUserDisabled", "DWORD", "0");
            manageReg("add", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search", "BackgroundAppGlobalToggle", "DWORD", "0");
            WindowsMessageToastBox("The background app services have been disabled, please reboot the system if the settings haven't applied yet.");
        }
        else if(std::string(argvTwo) == "-troubleshooting") {
            executeInternalSystemCommands("EternityUXHelperBatchScript.bat", "--Disable-TroubleShooting");
            WindowsMessageToastBox("The basic troubleshooting services have been disabled, please reboot the system if the settings haven't applied yet.");
        }
        else if(std::string(argvTwo) == "-windows-updates") {
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
        else if(std::string(argvTwo) == "-gamebar") {
            manageReg("add", "HKEY_CURRENT_USER\\Software\\Microsoft\\GameBar", "ShowStartupPanel", "REG_DWORD", "0");
            manageReg("add", "HKEY_CURRENT_USER\\Software\\Microsoft\\GameBar", "GamePanelStartupTipIndex", "REG_DWORD", "3");
            manageReg("add", "HKEY_CURRENT_USER\\Software\\Microsoft\\GameBar", "AllowAutoGameMode", "REG_DWORD", "0");
            manageReg("add", "HKEY_CURRENT_USER\\Software\\Microsoft\\GameBar", "AutoGameModeEnabled", "REG_DWORD", "0");
            manageReg("add", "HKEY_CURRENT_USER\\Software\\Microsoft\\GameBar", "UseNexusForGameBarEnabled", "REG_DWORD", "0");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_Enabled", "REG_DWORD", "0");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_FSEBehaviorMode", "REG_DWORD", "2");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_FSEBehavior", "REG_DWORD", "2");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_HonorUserFSEBehaviorMode", "REG_DWORD", "1");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_DXGIHonorFSEWindowsCompatible", "REG_DWORD", "1");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_EFSEFeatureFlags", "REG_DWORD", "0");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_DSEBehavior", "REG_DWORD", "2");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows\\GameDVR", "AllowGameDVR", "REG_DWORD", "0");
            manageReg("add", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\GameDVR", "AppCaptureEnabled", "REG_DWORD", "0");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\BcastDVRUserService", "Start", "REG_DWORD", "4");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment", "__COMPAT_LAYER", "REG_SZ", "~ DISABLEDXMAXIMIZEDWINDOWEDMODE");
        }
        else if(std::string(argvTwo) == "-game-mode") {
            manageReg("add", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\GameBar", "AllowAutoGameMode", "DWORD", "00000000");
            manageReg("add", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\GameBar", "AutoGameModeEnabled", "DWORD", "00000000");
        }
        else if(std::string(argvTwo) == "-copilot") {
            taskKill("explorer.exe");
            manageReg("add", "HKEY_CURRENT_USER\\Software\\Policies\\Microsoft\\Windows\\WindowsCopilot", "TurnOffWindowsCopilot", "DWORD", "00000001");
            executeInternalSystemCommands("start", "explorer.exe");
        }
        else if(std::string(argvTwo) == "-edge") {
            for (int i = 0; i < edgeExecutablesArraySize; i++) {
                taskKill(edgeExecutables[i]);
            }
            for (int i = 0; i < edgeRegistryKeysToTinkerArraySize; i++) {
                executeInternalSystemCommands("reg", edgeRegistryKeysToTinker[i]);
            }
            for(int i = 0; i < edgeInitServicesArraySize; i++) {
                executeInternalSystemCommands("net stop", edgeInitServices[i]);
            }
            for(int i = 0; i < edgeInitServicesArraySize; i++) {
                executeInternalSystemCommands("sc delete", edgeInitServices[i]);
            }
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
        }
    } 
    else if(std::string(argvOne) == "--enable") {
        if(std::string(argvTwo) ==  "-animations") {
            manageReg("add", "HKCU\\Control Panel\\Desktop", "UserPreferencesMask", "REG_BINARY", "90 1E 03 80 10 00 00 00");
            WindowsMessageToastBox("The System Animations have been enabled, please reboot the system if the settings haven't applied yet.");
        }
        else if(std::string(argvTwo) ==  "-background-apps") {
            manageReg("delete", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\BackgroundAccessApplications", "GlobalUserDisabled", " ", " ");
            manageReg("delete", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search", "BackgroundAppGlobalToggle", " ", " ");
            WindowsMessageToastBox("The background app services have been enabled, please reboot the system to apply the changes.");
        }
        else if(std::string(argvTwo) ==  "-background-apps") {
            executeInternalSystemCommands("EternityUXHelperBatchScript.bat", "--Enable-TroubleShooting");
            WindowsMessageToastBox("The basic troubleshooting services have been enabled, please reboot the system to apply the changes.");
        }
        else if(std::string(argvTwo) ==  "-windows-updates") {
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
        else if(std::string(argvTwo) ==  "-gamebar") {
            manageReg("delete", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\GameBar", "GamePanelStartupTipIndex", "", "");
            manageReg("delete", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\GameBar", "AllowAutoGameMode", "", "");
            manageReg("delete", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\GameBar", "AutoGameModeEnabled", "", "");
            manageReg("add", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\GameBar", "UseNexusForGameBarEnabled", "REG_DWORD", "00000001");
            manageReg("add", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\GameBar", "ShowStartupPanel", "REG_DWORD", "00000001");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_Enabled", "REG_DWORD", "00000001");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_FSEBehavior", "REG_DWORD", "00000000");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_FSEBehaviorMode", "REG_DWORD", "00000002");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_HonorUserFSEBehaviorMode", "REG_DWORD", "00000000");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_DXGIHonorFSEWindowsCompatible", "REG_DWORD", "00000000");
            manageReg("add", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_EFSEFeatureFlags", "REG_DWORD", "00000001");
            manageReg("delete", "HKEY_CURRENT_USER\\System\\GameConfigStore", "GameDVR_DSEBehavior", "", "");
            manageReg("delete", "HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows\\GameDVR", "AllowgameDVR", "", "");
            manageReg("add", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\GameDVR", "AppCaptureEnabled", "REG_DWORD", "00000001");
            manageReg("add", "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\BcastDVRUserService", "Start", "REG_DWORD", "00000003");
            manageReg("delete", "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment", "__COMPAT_LAYER", "", "");
        }
        else if(std::string(argvTwo) ==  "-game-mode") {
            manageReg("delete", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\GameBar", "AllowAutoGameMode", " ", " ");
            manageReg("delete", "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\GameBar", "AutoGameModeEnabled", " ", " ");
        }
        else if(std::string(argvTwo) ==  "-copilot") {
            taskKill("explorer.exe");
            manageReg("add", "HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", "ShowCopilotButton", "REG_DWORD", "1");
            manageReg("delete", "HKCU\\Software\\Policies\\Microsoft\\Windows\\WindowsCopilot", "TurnOffWindowsCopilot", " ", " ");
            executeInternalSystemCommands("start", "explorer.exe");
        }
    }
    else if(std::string(argvOne) == "--gui") {
        if(std::string(argvTwo) == "--old-alt-tab") {
            manageReg("add", "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", "AltTabSettings", "REG_DWORD", "1");
            WindowsMessageToastBox("The Alt-Tab have reverted to the old windows 7 style, please reboot the system if the settings haven't applied yet.");
        }
        else if(std::string(argvTwo) == "--new-alt-tab") {
            manageReg("add", "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", "AltTabSettings", "REG_DWORD", "1");
            WindowsMessageToastBox("The Alt-Tab have reverted back to the windows 10 style, please reboot the system if the settings haven't applied yet.");
        }
    }
}

void helpText(char *ExecutableName) {
    if(DoiHaveGUIElementSupport == 1) {
        std::cout << "#######################################################################################" << std::endl;
        std::cout << "d88888b d888888b d88888b d8888b. d8b   db d888888b d888888b db    db db    db db    db " << std::endl;
        std::cout << "88'     `~~88~~' 88'     88  `8D 888o  88   `88'   `~~88~~' `8b  d8' 88    88 `8b  d8' " << std::endl;
        std::cout << "88ooooo    88    88ooooo 88oobY' 88V8o 88    88       88     `8bd8'  88    88  `8bd8'  " << std::endl;
        std::cout << "88~~~~~    88    88~~~~~ 88`8b   88 V8o88    88       88       88    88    88  .dPYb.  " << std::endl;
        std::cout << "88.        88    88.     88 `88. 88  V888   .88.      88       88    88b  d88 .8P  Y8." << std::endl;
        std::cout << "Y88888P    YP    Y88888P 88   YD VP   V8P Y888888P    YP       YP    ~Y8888P' YP    YP " << std::endl;
        std::cout << "#######################################################################################" << std::endl;
        std::cout << "Usage " << ExecutableName << ":" << std::endl;
        std::cout << "\nOptions:" << std::endl;
        std::cout << "\t\t--disable : Disables a specified option" << std::endl;
        std::cout << "\t\t--enable : Enables a specified option" << std::endl;
        std::cout << "\nParameters / Option (Only works with --disable or --enable):";
        std::cout << "\t\t-copilot" << std::endl;
        std::cout << "\t\t-gamebar" << std::endl;
        std::cout << "\t\t-windows-updates" << std::endl;
        std::cout << "\t\t-background-apps" << std::endl;
        std::cout << "\t\t-troubleshooting" << std::endl;
        std::cout << "That's it, please put a like to my github project: github.com/forsaken-heart24/EternityUX\nThanks for showing love and using this tool!" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    // initial checks.
    if (argc < 3) {
        std::cerr << "Insufficient arguments provided." << std::endl;
        return 1;
    }

    // prepare arguments
    std::string One = toLower(std::string(argv[1]));
    std::string Two = toLower(std::string(argv[2]));

    // retarded.
    if(One == "--disable" || One == "--enable" || One == "--gui") {
        if(Two == "--old-alt-tab" || Two == "--new-alt-tab" || Two == "-game-mode" || Two == "-copilot" || Two == "-gamebar" || Two == "-windows-updates" || Two == "-background-apps" || Two == "-animations" || Two == "-troubleshooting") {
            Eternity(argv[1], argv[2]);
        }
    }
    else if(One == "--init") {
        if(manageReg("check", "HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment\\WinEternityStage", " ", " ", " ")) {
            for(int i = 0; i < ishaj; i++) {
                Eternity("--disable", ThingsToDisable[i]);
            }
        }
    }
    else {
        WindowsMessageToastBox("Hola amigo!");
        helpText(argv[0]);
    }
}