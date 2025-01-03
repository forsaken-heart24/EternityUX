#include <string>
#include <Windows.h>
#include <shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

bool isAdmin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        CheckTokenMembership(NULL, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }
    return isAdmin == TRUE;
}

bool is_debug() {
    return false;
}

bool WindowsMessageQuestionBox(const char* whoTheFuckKnows) {
    int theReturnOfTheMist = MessageBox(NULL, whoTheFuckKnows, "EternityUX", MB_YESNO);
    if(theReturnOfTheMist == 6) {
        return true;
    }
    return false;
}

bool WindowsMessageToastBox(const char* whoTheFuckKnows) {
    int theReturnOfTheMist = MessageBox(NULL, whoTheFuckKnows, "EternityUX", MB_ICONINFORMATION);
    if(theReturnOfTheMist == 6) {
        return true;
    }
    return false;
}

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

int main(int argc, char* argv[]) {
    // fak u
    SetConsoleTitle("EternityUX Log Console");
    if(argc > 1 && std::string(argv[1]) == "--test") {
        WindowsMessageToastBox("The compiled application works without any issues, debug using Visual Studio if you want.");
        exit(0);
    }
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