#include <windows.h>
#include <stdio.h>
#include <psapi.h>

int main() {
    DWORD processes[1024], numProcesses;
    if (!EnumProcesses(processes, sizeof(processes), &numProcesses)) {
        printf("Could not enumerate processes.\n");
        return 1;
    }
    
    int numRunning = numProcesses / sizeof(DWORD);
    
    printf("Process Id\tMemory Usage (KB)\tProcess Name\n");

    for (int i = 0; i < numRunning; i++) {
        //getting a handle to the process
        //ForTheOpenProcess interact-->(1)
        HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);
        if (processHandle == NULL) {
            continue;
        }

        char processName[MAX_PATH] = "";
        if (!GetProcessImageFileNameA(processHandle, processName, MAX_PATH)) {
            continue;
        }

        PROCESS_MEMORY_COUNTERS_EX pmc;
        if (!GetProcessMemoryInfo(processHandle, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
            CloseHandle(processHandle);
            continue;
        }
        DWORD memoryUsageKB = pmc.PrivateUsage / 1024;

        printf("%u\t\t%u\t\t%s\n", processes[i], memoryUsageKB, processName);

        CloseHandle(processHandle);
    }

    return 0;
}

