#include <Windows.h>
#include <stdio.h>

int main()
{
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    if (hSCManager == NULL)
    {
        printf("Failed to open service control manager.\n");
        return 1;
    }

    //set buffer size
    DWORD bufferSize = 0;
    DWORD servicesReturned = 0;
    DWORD resumeHandle = 0;
    EnumServicesStatusEx(
        hSCManager,
        SC_ENUM_PROCESS_INFO,
        SERVICE_WIN32,
        SERVICE_STATE_ALL,
        NULL,
        0,
        &bufferSize,
        &servicesReturned,
        &resumeHandle,
        NULL
    );

    if (bufferSize == 0)
    {
        printf("No services found.\n");
        CloseServiceHandle(hSCManager);
        return 0;
    }

    LPENUM_SERVICE_STATUS_PROCESS services = (LPENUM_SERVICE_STATUS_PROCESS)malloc(bufferSize);
    EnumServicesStatusEx(
        hSCManager,
        SC_ENUM_PROCESS_INFO,
        SERVICE_WIN32,
        SERVICE_STATE_ALL,
        (LPBYTE)services,
        bufferSize,
        &bufferSize,
        &servicesReturned,
        &resumeHandle,
        NULL
    );

    printf("Services found: %u\n", servicesReturned);
    printf("-----------------------------\n");

    for (DWORD i = 0; i < servicesReturned; i++)
    {
        printf("Service Name: %s\n", services[i].lpServiceName);
        printf("Display Name: %s\n", services[i].lpDisplayName);
        printf("Status: %s\n", (services[i].ServiceStatusProcess.dwCurrentState == SERVICE_RUNNING) ? "Running" : "Stopped");
        printf("-----------------------------\n");
    }

    free(services);
    CloseServiceHandle(hSCManager);

    return 0;
}
