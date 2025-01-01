reg.exe add HKLM\SYSTEM\CurrentControlSet\Control\Class\{4d36e968-e325-11ce-bfc1-08002be10318}\0000 /v VRDirectFlipDPCDelayUs /t REG_DWORD /d 1 /f
reg.exe add HKLM\SYSTEM\CurrentControlSet\Control\Class\{4d36e968-e325-11ce-bfc1-08002be10318}\0000 /v VRDirectFlipTimingMarginUs /t REG_DWORD /d 1 /f
reg.exe add HKLM\SYSTEM\CurrentControlSet\Control\Class\{4d36e968-e325-11ce-bfc1-08002be10318}\0000 /v VRDirectJITFlipMsHybridFlipDelayUs /t REG_DWORD /d 1 /f
reg.exe add HKLM\SYSTEM\CurrentControlSet\Enum\%%a\Device Parameters /v SelectiveSuspendOn /t REG_DWORD /d 0 /f
reg.exe add HKLM\SYSTEM\CurrentControlSet\Enum\%%a\Device Parameters /v SelectiveSuspendEnabled /t REG_BINARY /d 00 /f
reg.exe add HKLM\SYSTEM\CurrentControlSet\Enum\%%a\Device Parameters\WDF /v IdleInWorkingState /t REG_DWORD /d 0 /f
reg.exe add HKLM\SYSTEM\CurrentControlSet\Control\Class\{4d36e968-e325-11ce-bfc1-08002be10318}\0000 /v D3PCLatency /t REG_DWORD /d 1 /f
reg.exe add HKLM\SYSTEM\CurrentControlSet\Control\Class\{4d36e968-e325-11ce-bfc1-08002be10318}\0000 /v F1TransitionLatency /t REG_DWORD /d 1 /f
reg.exe add HKLM\SYSTEM\CurrentControlSet\Control\Class\{4d36e968-e325-11ce-bfc1-08002be10318}\0000 /v LOWLATENCY /t REG_DWORD /d 1 /f
reg.exe add HKLM\SYSTEM\CurrentControlSet\Control\Class\{4d36e968-e325-11ce-bfc1-08002be10318}\0000 /v PciLatencyTimerControl /t REG_DWORD /d 20 /f
reg.exe add HKLM\SYSTEM\CurrentControlSet\Control\Class\{4d36e968-e325-11ce-bfc1-08002be10318}\0000 /v RMDeepL1EntryLatencyUsec /t REG_DWORD /d 1 /f
