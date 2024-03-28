#include <windows.h>
#include <stdio.h>
#include <psapi.h>

int main() {
  
    HANDLE currentProcess = GetCurrentProcess();

    
    PROCESS_MEMORY_COUNTERS pmc;
    if (!GetProcessMemoryInfo(currentProcess, &pmc, sizeof(pmc))) {
        printf("Could not get process memory usage\n");
        return 1;
    }

   
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);
    GlobalMemoryStatusEx(&memStatus);
    DWORDLONG totalPhysMem = memStatus.ullTotalPhys;

    
    DWORDLONG highMemThreshold = (DWORDLONG)(totalPhysMem * 0.75);

    
    HANDLE processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (processSnapshot == INVALID_HANDLE_VALUE) {
        printf("Could not create process snapshot\n");
        return 1;
    }

   
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(processEntry);
    if (Process32First(processSnapshot, &processEntry)) {
        do {
            HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, processEntry.th32ProcessID);
            if (processHandle == NULL) {
                continue;
            }

           
            if (!GetProcessMemoryInfo(processHandle, &pmc, sizeof(pmc))) {
                printf("%-8lu%-32sCould not get process memory usage\n", processEntry.th32ProcessID, processEntry.szExeFile);
                CloseHandle(processHandle);
                continue;
            }

          
            if (pmc.WorkingSetSize > highMemThreshold) {
                printf("%-8lu%-32s%lu\n", processEntry.th32ProcessID, processEntry.szExeFile, pmc.WorkingSetSize);

                
                if (TerminateProcess(processHandle, 0)) {
                    printf("    Terminated\n");
                } else {
                    printf("Could not terminate process (error code: %lu)\n", GetLastError());
                }
            }

           
            CloseHandle(processHandle);
        } while (Process32Next(processSnapshot, &processEntry));
    }

    CloseHandle(processSnapshot);
    return 0;
}
