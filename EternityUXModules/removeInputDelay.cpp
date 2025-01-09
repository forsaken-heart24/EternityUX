#include <string>
#include <Windows.h>
#include <shlwapi.h>
#include "EternityUXApplibrary.h"
#pragma comment(lib, "Shlwapi.lib")

void manageRegistry() {
    std::string variableZero;
    std::string variableOne;
    const char *pCIELatencyTweaker[] = {    
        "HKLM\\SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000 /v D3PCLatency /t REG_DWORD /d 1 /f",
        "HKLM\\SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000 /v F1TransitionLatency /t REG_DWORD /d 1 /f",
        "HKLM\\SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000 /v LOWLATENCY /t REG_DWORD /d 1 /f",
        "HKLM\\SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000 /v PciLatencyTimerControl /t REG_DWORD /d 20 /f",
        "HKLM\\SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000 /v RMDeepL1EntryLatencyUsec /t REG_DWORD /d 1 /f"
    };
    const char *uSBLatencyTweaker[] = { 
        "HKLM\\SYSTEM\\CurrentControlSet\\Enum\\%%a\\Device Parameters /v SelectiveSuspendOn /t REG_DWORD /d 0 /f",
        "HKLM\\SYSTEM\\CurrentControlSet\\Enum\\%%a\\Device Parameters /v SelectiveSuspendEnabled /t REG_BINARY /d 00 /f",
        "HKLM\\SYSTEM\\CurrentControlSet\\Enum\\%%a\\Device Parameters\\WDF /v IdleInWorkingState /t REG_DWORD /d 0 /f"
    };
    
    if(WindowsMessageQuestionBox("Do you want to Tweak PCIE Device Latency??")) {
        for(int i = 0; i < sizeof(pCIELatencyTweaker) / sizeof(pCIELatencyTweaker[0]); i++) {
            if(is_debug) {
                variableZero = "echo reg add " + std::string(pCIELatencyTweaker[i]);
            }
            else {
                variableZero = "reg add " + std::string(pCIELatencyTweaker[i]);
            }
            system(variableZero.c_str());
        }
    }
    if(WindowsMessageQuestionBox("Do you want to Tweak USB Device Latency??")) {
        for(int i = 0; i < sizeof(uSBLatencyTweaker) / sizeof(uSBLatencyTweaker[0]); i++) {
            if(is_debug) {
                variableOne = "echo reg add " + std::string(uSBLatencyTweaker[i]);
            }
            else {
                variableOne = "reg add " + std::string(uSBLatencyTweaker[i]);
            }
            system(variableOne.c_str());
        }
    }
}

// Define if whether this application build will run on init or desktop
// we should have to do it to get things working but we can use any value except 0 to 
// get the non-gui elements to work.
// This is the entry point for a GUI-based Windows application built using EternityUXApplibrary.h
int DoiHaveGUIElementSupport = 0;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // no
    if (!isAdmin()) {
        WindowsMessageToastBox("Please run this application with administrator privilages!");
        exit(1);
    }
    // ok
    if (WindowsMessageQuestionBox("This might trigger a security issue, Do you want to proceed?")) {
        manageRegistry();
    }
    WindowsMessageToastBox("Thank you for using EternityUX!");
} 