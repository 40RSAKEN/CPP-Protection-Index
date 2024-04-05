#pragma once

#include "../Protection/BSOD.h"

#include <iostream>
#include <windows.h>


void DetectDrivers() {
    
    const LPCTSTR kernelDrivers[] = {
        TEXT("\\\\.\\kdstinker"),
        TEXT("\\\\.\\NiGgEr"),
        TEXT("\\\\.\\KsDumper"),
        TEXT("\\\\.\\kprocesshacker")
    };


    for (const auto& driverName : kernelDrivers) {
        HANDLE hDevice = CreateFile(driverName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        if (hDevice != INVALID_HANDLE_VALUE) {

            // std::cerr << "Detected kernel driver: " << driverName << std::endl;
            
            bsod();
            CloseHandle(hDevice);
        }
    }
}


void CheckDevices() {
    const char DebuggingDrivers[][20] = {
        "\\\\.\\EXTREM", "\\\\.\\ICEEXT",
        "\\\\.\\NDBGMSG.VXD", "\\\\.\\RING0",
        "\\\\.\\SIWVID", "\\\\.\\SYSER",
        "\\\\.\\TRW", "\\\\.\\SYSERBOOT",
        "\\\\.\\VMSNPX", "\\\\.\\VBoxGuest",
        "\\\\.\\VBoxMouse", "\\\\.\\VBoxSF",
        "\\\\.\\VBoxVideo"
    };

    for (int i = 0; i < sizeof(DebuggingDrivers) / sizeof(DebuggingDrivers[0]); ++i) {
        HANDLE h = CreateFileA(DebuggingDrivers[i], 0, 0, 0, OPEN_EXISTING, 0, 0);
        if (h != INVALID_HANDLE_VALUE) {
            CloseHandle(h);
            bsod();
            exit(0);
        }
    }
}


