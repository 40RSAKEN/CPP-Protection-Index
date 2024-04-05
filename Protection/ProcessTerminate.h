#pragma once

#include "../Protection/BSOD.h"

#include <iostream>
#include <string>
#include <windows.h>
#include <TlHelp32.h>
#include <tlhelp32.h>
#include <algorithm>
#include <vector>
#include <functional>
 

DWORD FindProcessId(const std::wstring& processName) {
    DWORD processId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry)) {
            do {
                if (_wcsicmp(procEntry.szExeFile, processName.c_str()) == 0) {
                    processId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
        CloseHandle(hSnap);
    }
    return processId;
}



void TerminateProcessById(DWORD processId) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processId);
    if (hProcess != NULL) {
        TerminateProcess(hProcess, 0);
        CloseHandle(hProcess);
    }
}



bool FindWindowWithTitle(const std::wstring& windowTitle) {
    return FindWindow(NULL, windowTitle.c_str()) != NULL;
}



void TerminateProcesses() {
    const std::wstring processNames[] = {
        L"ollydbg.exe", L"ProcessHacker.exe", L"Dump-Fixer.exe", L"kdstinker.exe",
        L"tcpview.exe", L"autoruns.exe", L"autorunsc.exe", L"filemon.exe",
        L"procmon.exe", L"regmon.exe", L"procexp.exe", L"ImmunityDebugger.exe",
        L"Wireshark.exe", L"dumpcap.exe", L"HookExplorer.exe", L"ImportREC.exe",
        L"PETools.exe", L"LordPE.exe", L"dumpcap.exe", L"SysInspector.exe",
        L"proc_analyzer.exe", L"sysAnalyzer.exe", L"sniff_hit.exe", L"windbg.exe",
        L"joeboxcontrol.exe", L"Fiddler.exe", L"joeboxserver.exe", L"ida64.exe",
        L"ida.exe", L"idaq64.exe", L" ", L"vboxservice.exe", L"vboxtray.exe",
        L"ReClass.NET.exe", L"x64dbg.exe", L"OLLYDBG.exe", L"Cheat Engine.exe",
        L"cheatengine-x86_64-SSE4-AVX2.exe", L"MugenJinFuu-i386.exe",
        L"Mugen JinFuu.exe", L"MugenJinFuu-x86_64-SSE4-AVX2.exe",
        L"MugenJinFuu-x86_64.exe", L"The Wireshark Network Analyzer",
        L"Progress Telerik Fiddler Web Debugger", L"x64dbg", L"KsDumper",
        L"KsDumper.exe", L"dnSpy", L"dnSpy.exe", L"cheatengine-i386.exe",
        L"cheatengine-x86_64.exe", L"Fiddler Everywhere.exe",
        L"Fiddler.WebUi.exe", L"", L"Fiddler Everywhere", L"Wireshark",
        L"Dumpcap", L"Fiddler.WebUi", L"", L"", L"ida64",
        L"IDA v7.0.170914", L"createdump.exe", L"MugenJinFuu-i386.exe",
        L"Mugen JinFuu.exe", L"MugenJinFuu-x86_64-SSE4-AVX2.exe",
        L"MugenJinFuu-x86_64.exe"
    };



    for (const auto& processName : processNames) {
        DWORD processId = FindProcessId(processName);
        if (processId != 0) {
            TerminateProcessById(processId);
            std::wcout << L"Terminated process: " << processName << std::endl;
            bsod();
        }
    }


    const std::wstring windowTitles[] = {
        L"cheatengine-x86_64-SSE4-AVX2.exe",
        L"MugenJinFuu-i386.exe",
        L"Mugen JinFuu.exe",
        L"MugenJinFuu-x86_64-SSE4-AVX2.exe",
        L"MugenJinFuu-x86_64.exe",
        L"The Wireshark Network Analyzer",
        L"Progress Telerik Fiddler Web Debugger",
        L"x64dbg",
        L"KsDumper",
        L"dnSpy",
        L"Fiddler Everywhere",
        L"Wireshark",
        L"Dumpcap",
        L"Fiddler.WebUi",
        L"ida64",
        L"IDA v7.0.170914"
    };


    for (const auto& windowTitle : windowTitles) {
        if (FindWindowWithTitle(windowTitle)) {
            std::wcout << L"Closed window: " << windowTitle << std::endl;
            bsod(); 
        }
    }
}

// vshost.exe removed for testing purposes.

std::vector<std::wstring> ProcessListToCheck = {
    L"processhacker.exe", L"procmon.exe", L"pestudio.exe", L"procmon64.exe", L"x32dbg.exe", L"x64dbg.exe", L"CFF Explorer.exe", L"procexp64.exe",
    L"procexp.exe", L"pslist.exe", L"tcpview.exe", L"tcpvcon.exe", L"dbgview.exe", L"RAMMap.exe", L"RAMMap64.exe", L"vmmap.exe", L"ollydbg.exe", L"agent.py", L"autoruns.exe",
    L"autorunsc.exe", L"filemon.exe", L"regmon.exe", L"idaq.exe", L"idaq64.exe", /*L"vshost.exe",*/ L"ImmunityDebugger.exe", L"Wireshark.exe", L"dumpcap.exe", L"HookExplorer.exe", L"ImportREC.exe", L"PETools.exe",
    L"LordPE.exe", L"SysInspector.exe", L"proc_analyzer.exe", L"sysAnalyzer.exe", L"sniff_hit.exe", L"windbg.exe", L"joeboxcontrol.exe", L"joeboxserver.exe", L"joeboxserver.exe", L"ResourceHacker.exe", L"Fiddler.exe",
    L"httpdebugger.exe"
};

bool CheckProcessesRunning(const std::function<void()>& callback)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return false;

    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(snapshot, &entry))
    {
        CloseHandle(snapshot);
        return false;
    }

    do
    {
        std::wstring processName = entry.szExeFile;
        if (std::find(ProcessListToCheck.begin(), ProcessListToCheck.end(), processName) != ProcessListToCheck.end())
        {
            bsod();
            CloseHandle(snapshot);
            return true;
        }
    } while (Process32NextW(snapshot, &entry));

    CloseHandle(snapshot);
    return false;
}
