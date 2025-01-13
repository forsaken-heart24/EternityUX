#ifndef PREDEFINED_EXTERNITY_INIT_DEPLOYER_VALUES_H
#define PREDEFINED_EXTERNITY_INIT_DEPLOYER_VALUES_H

#include <iostream>

// hi kids!
const char *edgeExecutables[] = {
    "msedge.exe",
    "MicrosoftEdgeUpdate.exe",
    "msedgewebview2.exe"
};
const char *edgeRegistryKeysToTinker[] = {
    "delete HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft Edge /f",
    "delete HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft Edge Update /f",
    "delete HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft EdgeWebView /f",
    "add HKLM\\Software\\Microsoft\\EdgeUpdate /v DoNotUpdateToEdgeWithChromium /t REG_DWORD /d 1 /f",
    "add HKLM\\Software\\WOW6432Node\\Microsoft\\EdgeUpdate /v DoNotUpdateToEdgeWithChromium /t REG_DWORD /d 1 /f"
};
const char *edgeInitServices[] = {
    "MicrosoftEdgeElevationService",
    "edgeupdate",
    "edgeupdatem"
};
const char *ThingsToDisable[] = {
    "-game-mode",
    "-gamebar",
    "-copilot",
    "-background-apps",
    "-animations",
    "-troubleshooting"
};

// size of the array distributions.
int edgeExecutablesArraySize = sizeof(edgeExecutables) / sizeof(edgeExecutables[0]);
int edgeRegistryKeysToTinkerArraySize = sizeof(edgeRegistryKeysToTinker) / sizeof(edgeRegistryKeysToTinker[0]);
int edgeInitServicesArraySize = sizeof(edgeInitServices) / sizeof(edgeInitServices[0]);
int ishaj = sizeof(ThingsToDisable) / sizeof(ThingsToDisable[0]);

#endif