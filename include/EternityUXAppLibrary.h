#ifndef ETERNITYUXAPPLIBRARY_H
#define ETERNITYUXAPPLIBRARY_H

#include "PredefinedExternityInitDeployerValues.h"
#include <iostream>
#include <unistd.h>
#include <shlwapi.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tlhelp32.h>
#pragma comment(lib, "Shlwapi.lib")

// Define if whether this application build will run on init or desktop
// we should have to do it to get things working but we can use any value except 0 to 
// get the non-gui elements to work.
// This is the entry point for a GUI-based Windows application.
extern int DoiHaveGUIElementSupport;

std::string toLower(const std::string& input) {
    std::string result = input;
    for (char& c : result) {
        c = std::tolower(c);
    }
    return result;
}

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
    if (DoiHaveGUIElementSupport == 0) {
        int theReturnOfTheMist = MessageBox(NULL, whoTheFuckKnows, "EternityUX", MB_ICONINFORMATION);
        return theReturnOfTheMist == IDOK;  // Compare against IDOK (value 1)
    }
    else {
        std::cout << whoTheFuckKnows << "\n";
        return true;
    }
}

void executeInternalSystemCommands(const char* command, const char* arguments) {
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

void warnTexts(const char* message, const char* activity) {
    char dawnThatWasQuick[1048];
    snprintf(dawnThatWasQuick, sizeof(dawnThatWasQuick), ": [%s] - %s :", activity, message);
    std::cout << "\033[33m " << dawnThatWasQuick << "\033[0m" << "\n";
}

void taskKill(const char* theExecutableName) {
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

bool manageReg(const std::string& argument, const std::string& key, const std::string& valueName, const std::string& valueType, const std::string& valueData) {
    // Check if the essential arguments are empty
    if(argument.empty() || key.empty()) {
        WindowsMessageToastBox("Not Enough arguments to parse, please report this to the developer!");
        exit(1);
    }
    if(argument == "add") {
        if(valueType.empty() || valueData.empty()) {
            WindowsMessageToastBox("Not Enough arguments to parse, please report this to the developer!");
            exit(1);
        }
        std::string command = "reg add \"" + key + "\" /v " + valueName + " /t " + valueType + " /d " + valueData + " /f";
        executeInternalSystemCommands(command.c_str(), nullptr);  // No need for separate command and arguments
    }
    else if(argument == "delete") {
        std::string commandArgument = "reg delete \"" + key + "\" /v " + valueName + " /f";
        executeInternalSystemCommands(commandArgument.c_str(), nullptr);
    }
    else if(argument == "check") {
        HKEY hKey;
        LONG result = RegOpenKeyExA(HKEY_LOCAL_MACHINE, key.c_str(), 0, KEY_READ, &hKey);  // Corrected to &hKey
        if(result == ERROR_SUCCESS){
            return true;
        }
        return false;
    }
    else {
        WindowsMessageToastBox("Invalid Arguments, please report this to the developer if this error persists.");
    }
}

#endif
