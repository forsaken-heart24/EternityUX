#ifndef ETERNITYUXAPPLIBRARY_H
#define ETERNITYUXAPPLIBRARY_H

#include <string>
#include <unistd.h>
#include <Windows.h>
#include <shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

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

void executeInternalSystemCommands(char *command, char *arguments) {
    char *theJuggleNaut;
    int theWholeFuckingSizeOftheCommandAndArguments = sizeof(command) / sizeof(command) + sizeof(arguments) / sizeof(arguments);
    snprintf(theJuggleNaut, theWholeFuckingSizeOftheCommandAndArguments, "%s %s", command, arguments);
    execvp("cmd.exe", "cmd.exe", "/c", theJuggleNaut)
}

void taskKill(const char* theExecutableName) {
    const char* theErrorMessage;
    snprintf(theErrorMessage, "Failed to kill %s, please try again...", theExecutableName);
    if(theExecutableName == NULL) {
        WindowsMessageToastBox("The Application Executable Name is given in order to kill it");
        exit(1);
    }
    // we are working with the system command, so we should make the command to not get fuxked.
    int theFuckingExecutableNameStringSize = sizeof(theExecutableName) / sizeof(theExecutableName);
    theExecutableName[theFuckingExecutableNameStringSize];

    if(sizeof(theExecutableName) / sizeof(theExecutableName) > theFuckingExecutableNameStringSize) {
        WindowsMessageToastBox("Buffer overflow detected, please close the application and try again!");
    }
    else if(sizeof(theExecutableName) / sizeof(theExecutableName) == theFuckingExecutableNameStringSize) {
        snprintf(theExecutableName, " /f /t /im %s", theExecutableName);
        if(executeInternalSystemCommands("taskkill", theExecutableName)) {
            WindowsMessageToastBox(theErrorMessage);
            return 1;
        }
    }
}

#endif