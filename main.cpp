
#include "Protection/ProcessTerminate.h"
#include "Protection/IsKernelPresent.h"
#include "Protection/IsRemoteDebuggerPresent.h"
#include "Protection/AntiDebug.h"
#include "Protection/KillDebuggersExtra.h"
#include "Protection/AntiDump.h"


#include <iostream>
#include <thread>
#include <chrono>


int main() {
    
    while (true) {
        
        OPD();
        remote_is_present();
        HardwareRegisters();
        CheckDevices();
        DetectDrivers();
        AntiDEBUG::Tick();
        TerminateProcesses();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    }

    bool result = CheckProcessesRunning([]() {
        std::cout << "A suspicious process was found.\n";
        
        });

    if (result) {
        std::cout << "Suspicious process found and handled.\n";
    }
    else {
        std::cout << "No suspicious processes found.\n";
    }

    std::cout << "Sleeping for 100 seconds..." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(100));

    std::cout << "Woke up after 100 seconds." << std::endl;

    return 0;
}
