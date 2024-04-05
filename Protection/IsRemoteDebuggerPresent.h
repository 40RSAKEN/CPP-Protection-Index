#pragma once

int remote_is_present()
{
    int debugger_present = false;

    CheckRemoteDebuggerPresent(
        GetCurrentProcess, &debugger_present
    );

    return debugger_present;
    bsod();

}