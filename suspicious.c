#include <windows.h>
#include <stdio.h>
#include <psapi.h>

int main() {
    //process snapshot
    HANDLE processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (processSnapshot == INVALID_HANDLE_VALUE) {
        printf("Could not create process snapshot.\n");
        return 1;
    }

  
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(processEntry);
    if (Process32First(processSnapshot, &processEntry)) {
        do {
            //processHandle-->open process
            HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processEntry.th32ProcessID);
            if (processHandle == NULL) {
                continue;
            }


            PROCESS_MEMORY_COUNTERS pmc;
            if (!GetProcessMemoryInfo(processHandle, &pmc, sizeof(pmc))) {
                printf("%-8lu%-32sCould not get process memory usage.\n", processEntry.th32ProcessID, processEntry.szExeFile);
                CloseHandle(processHandle);
                continue;
            }


            if (pmc.WorkingSetSize > 50000000 && pmc.WorkingSetSize / pmc.PagefileUsage < 2 && pmc.PagefileUsage / pmc.PagefileUsagePeak < 2) {
                printf("%-8lu%-32s%lu\n", processEntry.th32ProcessID, processEntry.szExeFile, pmc.WorkingSetSize);
            }


            CloseHandle(processHandle);
        } while (Process32Next(processSnapshot, &processEntry));
    }


    CloseHandle(processSnapshot);

    return 0;
}
