#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <tlhelp32.h>

namespace AntiDEBUG {

    
    DWORD getProcID(const std::wstring& p_name) {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32W structprocsnapshot = { 0 };

        structprocsnapshot.dwSize = sizeof(PROCESSENTRY32W);

        if (snapshot == INVALID_HANDLE_VALUE) return 0;
        if (Process32FirstW(snapshot, &structprocsnapshot) == FALSE) return 0;

        while (Process32NextW(snapshot, &structprocsnapshot)) {
            if (!wcscmp(structprocsnapshot.szExeFile, p_name.c_str())) {
                CloseHandle(snapshot);
                return structprocsnapshot.th32ProcessID;
            }
        }
        CloseHandle(snapshot);
        return 0;
    }

    
    bool isProcRunning(const std::wstring& process) {
        return (getProcID(process) != 0);
    }

    
    void Tick() {
        if (isProcRunning(L"ida64.exe") || isProcRunning(L"dotPeek64.exe") || isProcRunning(L"ida32.exe") ||
            isProcRunning(L"ida.exe") || isProcRunning(L"reclass.net.exe") || isProcRunning(L"reclass.exe") ||
            isProcRunning(L"heyrays.exe") || isProcRunning(L"lighthouse.exe") || isProcRunning(L"cheatengine-x86_64.exe") ||
            isProcRunning(L"classinformer.exe") || isProcRunning(L"ida-x86emu.exe") || isProcRunning(L"cffexplorer.exe") ||
            isProcRunning(L"winhex.exe") || isProcRunning(L"hiew.exe") || isProcRunning(L"fiddler.exe") ||
            isProcRunning(L"httpdebugger.exe") || isProcRunning(L"httpdebuggerpro.exe") || isProcRunning(L"scylla.exe") ||
            isProcRunning(L"Cheat Engine.exe")) {
            MessageBoxW(NULL, L"Please close any reverse engineering tools and restart the program.", L"Error", MB_ICONERROR);
            bsod();
            ExitProcess(0);
        }
    }
}

