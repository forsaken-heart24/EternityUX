#include <iostream>
#include <string>
#include <windows.h>
#include <shlwapi.h>
#include "EternityUXApplibrary.h"


std::string toLower(const std::string& input) {
    std::string result = input;
    for (char& c : result) {
        c = std::tolower(c);
    }
    return result;
}

int DoiHaveGUIElementSupport = 0;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::string upperCaseArgs = toLower(lpCmdLine);
    if (upperCaseArgs == "--reg") {
        // i want to prep for school bye :D
    }
}