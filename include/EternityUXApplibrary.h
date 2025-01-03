#ifndef ETERNITYUXAPPLIBRARY_H
#define ETERNITYUXAPPLIBRARY_H

#include <string>
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

#endif