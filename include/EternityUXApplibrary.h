#ifndef ETERNITYUXAPPLIBRARY_H
#define ETERNITYUXAPPLIBRARY_H

#include <iostream>
#include <unistd.h>
#include <Windows.h>
#include <shlwapi.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tlhelp32.h>
#pragma comment(lib, "Shlwapi.lib")

// acts as a switch to fucking toggle the GUI and non-GUI
extern int DoiHaveGUIElementSupport;

bool is_debug() {
    return false;
}

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

bool IsExecutedFromCMD() {
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

bool WindowsMessageQuestionBox(const char* whoTheFuckKnows) {
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

bool WindowsMessageToastBox(const char* whoTheFuckKnows) {
    if(DoiHaveGUIElementSupport == 0) {
        int theReturnOfTheMist = MessageBox(NULL, whoTheFuckKnows, "EternityUX", MB_ICONINFORMATION);
        if(theReturnOfTheMist == 6) {
            return true;
        }
        return false;
    }
    else {
        std::cout << whoTheFuckKnows << "\n";
    }
}

void executeInternalSystemCommands(const char *command, const char *arguments) {
    if (!command || !arguments) {
        fprintf(stderr, "Invalid command or arguments\n");
        return;
    }
    int size = strlen(command) + strlen(arguments) + 2;
    char *theJuggleNaut = new char[size];
    snprintf(theJuggleNaut, size, "%s %s", command, arguments);
    char *const execArgs[] = {
        (char*)"cmd.exe", 
        (char*)"/c",
        theJuggleNaut,
        nullptr
    };
    execvp("cmd.exe", execArgs);
    perror("execvp failed");
    delete[] theJuggleNaut;
    exit(1);
}

void warnTexts(const char *message, const char *activity) {
    char dawnThatWasQuick[1048];
    snprintf(dawnThatWasQuick, sizeof(dawnThatWasQuick), ": [%s] - %s :", activity, message);
    std::cout << "\033[33m " << dawnThatWasQuick << "\033[0m" << "\n";
}

void taskKill(const char *theExecutableName) {
    if (!theExecutableName) {
        fprintf(stderr, "Executable name must be provided to kill it\n");
        return;
    }
    char theCommand[256];
    snprintf(theCommand, sizeof(theCommand), "taskkill /f /t /im %s", theExecutableName);
    if (system(theCommand) != 0) {
        fprintf(stderr, "Failed to kill %s, please try again...\n", theExecutableName);
        warnTexts("Failed to kill %s, please try again...\n", theExecutableName);
    }
}

#endif