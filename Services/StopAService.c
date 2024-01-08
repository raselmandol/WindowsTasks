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

    SC_HANDLE hService = OpenService(hSCManager, "MyServiceName", SERVICE_STOP);
    if (hService == NULL)
    {
        printf("Failed to open service.\n");
        CloseServiceHandle(hSCManager);
        return 1;
    }

    //service status
    SERVICE_STATUS serviceStatus;
    if (ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus))
    {
        printf("Service stopped successfully.\n");
    }
    else
    {
        printf("Failed to stop the service.\n");
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);

    return 0;
}
