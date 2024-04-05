#pragma once

#include "../Protection/BSOD.h"

#include <iostream>
#include <windows.h>


void HardwareRegisters() {
    BOOL found = FALSE;
    CONTEXT ctx = { 0 };
    HANDLE hThread = GetCurrentThread();

    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    if (GetThreadContext(hThread, &ctx)) {
        if ((ctx.Dr0 != 0x00) || (ctx.Dr1 != 0x00) || (ctx.Dr2 != 0x00) || (ctx.Dr3 != 0x00) || (ctx.Dr6 != 0x00) || (ctx.Dr7 != 0x00)) {
            found = TRUE;
        }
    }

    if (found) {
        bsod();
        exit(0);
    }
}

