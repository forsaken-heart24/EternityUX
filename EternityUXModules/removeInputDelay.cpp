#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <cstdlib>
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

void warns(const std::string& message, const std::string& job) {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    std::cout << "\033[0;35m[" << std::put_time(localTime, "%d-%m-%Y") << " \033[0;37m- \033[0;32m" << std::put_time(localTime, "%I:%M%p") << "\033[0;37m] / [:" << "\033[0;36mWARN\033[0;37m:] / [:" << "\033[0;32m" << job << "\033[0;37m:] -" << "\e[0;31m " << message << "\033[0;37m" << std::endl;
}

void pauseConsole() {
    std::cin.get();
}

void manageRegistry() {
    std::string variableOne;
    const char *addTheseKeysIntoTheHIVE[] = {    
        "empty",
        "hive"
    };
    for(int i = 0; i < sizeof(addTheseKeysIntoTheHIVE) / sizeof(addTheseKeysIntoTheHIVE[0]); i++) {
        if(is_debug) {
            variableOne = "echo reg add " + std::string(addTheseKeysIntoTheHIVE[i]);
        }
        else {
            variableOne = "reg add " + std::string(addTheseKeysIntoTheHIVE[i]);
            std::cout << " not in debug mode, hit enter to execute!";
            pauseConsole();
        }
        system(variableOne.c_str());
    }
}

int main() {
    SetConsoleTitle("EternityUX Log Console");
    if (!isAdmin()) {
        AllocConsole();
        warns("Not running as administrator, hit enter to close the window!", "Privilege Tester");
        pauseConsole();
        exit(0);
    }
    MessageBox(NULL, "This might trigger a security issue, please review the code in our repo!", "Heyyy user!", MB_ICONWARNING | MB_OK);
    int result = MessageBox(
        nullptr,
        "Do you want to proceed?",
        "Confirmation",
        MB_YESNO | MB_ICONQUESTION
    );
    if (result == IDYES) {
        manageRegistry();
    }
    MessageBox(NULL, "Thank you for using my project", "EternityUX", MB_ICONWARNING | MB_OK);
    return 0;
}