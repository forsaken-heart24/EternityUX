#include <iostream>
#include <unistd.h>
#include <Windows.h>
#include <shlwapi.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tlhelp32.h>
#include "EternityUXAppExternValues.h"
#pragma comment(lib, "Shlwapi.lib")

// Acts as a switch to toggle the GUI and non-GUI
__declspec(dllexport) extern int DoiHaveGUIElementSupport;

__declspec(dllexport) bool is_debug() {
    return false;
}

__declspec(dllexport) bool isAdmin() {
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

__declspec(dllexport) bool IsExecutedFromCMD() {
    DWORD currentProcessId = GetCurrentProcessId();
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return false;
    PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
    DWORD parentProcessId = 0;
    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (pe32.th32ProcessID == currentProcessId) {
                parentProcessId = pe32.th32ParentProcessID;
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }
    if (parentProcessId == 0) {
        CloseHandle(hSnapshot);
        return false;
    }
    bool isFromCMD = false;
    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (pe32.th32ProcessID == parentProcessId) {
                isFromCMD = (std::string(pe32.szExeFile) == "cmd.exe");
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }
    CloseHandle(hSnapshot);
    return isFromCMD;
}

__declspec(dllexport) bool WindowsMessageQuestionBox(const char* whoTheFuckKnows) {
    if (DoiHaveGUIElementSupport == 0) {
        int theReturnOfTheMist = MessageBox(NULL, whoTheFuckKnows, "EternityUX", MB_YESNO);
        return theReturnOfTheMist == IDYES;
    }
    else {
        std::string ptrGrepString;
        std::cout << whoTheFuckKnows << " (y/n): ";
        std::cin >> ptrGrepString;
        return ptrGrepString == "y" || ptrGrepString == "Y";
    }
}

__declspec(dllexport) bool WindowsMessageToastBox(const char* whoTheFuckKnows) {
    if (DoiHaveGUIElementSupport == 0) {
        int theReturnOfTheMist = MessageBox(NULL, whoTheFuckKnows, "EternityUX", MB_ICONINFORMATION);
        return theReturnOfTheMist == 6;
    }
    else {
        std::cout << whoTheFuckKnows << "\n";
        return true;
    }
}

__declspec(dllexport) void executeInternalSystemCommands(const char* command, const char* arguments) {
    if (!command || !arguments) {
        fprintf(stderr, "Invalid command or arguments\n");
        return;
    }
    int size = strlen(command) + strlen(arguments) + 2;
    char* theJuggleNaut = new char[size];
    snprintf(theJuggleNaut, size, "%s %s", command, arguments);
    char* execArgs[] = {
        theJuggleNaut,
        nullptr
    };
    execvp("cmd.exe", execArgs);
    perror("execvp failed");
    delete[] theJuggleNaut;
    exit(1);
}

__declspec(dllexport) void warnTexts(const char* message, const char* activity) {
    char dawnThatWasQuick[1048];
    snprintf(dawnThatWasQuick, sizeof(dawnThatWasQuick), ": [%s] - %s :", activity, message);
    std::cout << "\033[33m " << dawnThatWasQuick << "\033[0m" << "\n";
}

__declspec(dllexport) void taskKill(const char* theExecutableName) {
    if (!theExecutableName) {
        fprintf(stderr, "Executable name must be provided to kill it\n");
        return;
    }
    char theCommand[256];
    snprintf(theCommand, sizeof(theCommand), "taskkill /f /t /im %s", theExecutableName);
    if (system(theCommand) != 0) {
        warnTexts("Failed to kill %s, please try again...\n", theExecutableName);
    }
}

__declspec(dllexport) void manageReg(const std::string& argument, const std::string& key, const std::string& valueName, const std::string& valueType, const std::string& valueData) {
    // Check if the essential arguments are empty
    if (argument.empty() || key.empty() || valueName.empty()) {
        WindowsMessageToastBox("Not Enough arguments to parse, please report this to the developer!");
        exit(1);
    }
    if (argument == "add") {
        if (valueType.empty() || valueData.empty()) {
            WindowsMessageToastBox("Not Enough arguments to parse, please report this to the developer!");
            exit(1);
        }
        std::string command = "reg add \"" + key + "\" /v " + valueName + " /t " + valueType + " /d " + valueData + " /f";
        executeInternalSystemCommands(command.c_str(), nullptr);  // No need for separate command and arguments
    }
    else if (argument == "delete") {
        std::string commandArgument = "\"" + key + "\" /v " + valueName + " /f";
        executeInternalSystemCommands("reg delete", commandArgument.c_str());
    }
    else {
        WindowsMessageToastBox("Invalid Arguments, please report this to the developer if this error persists.");
    }
}