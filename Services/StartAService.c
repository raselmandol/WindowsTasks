#include <Windows.h>
#include <stdio.h>

int main()
{
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (hSCManager == NULL)
    {
        printf("Failed to open service control manager.\n");
        return 1;
    }

    //openService
    SC_HANDLE hService = OpenService(hSCManager, "MyServiceName", SERVICE_START);
    if (hService == NULL)
    {
        printf("Failed to open service.\n");
        CloseServiceHandle(hSCManager);
        return 1;
    }

    if (StartService(hService, 0, NULL))
    {
        printf("Service started successfully.\n");
    }
    else
    {
        printf("Failed to start the service.\n");
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);

    return 0;
}
