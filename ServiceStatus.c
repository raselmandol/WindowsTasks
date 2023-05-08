//used GCC -V 12.2.0
//By_Rasel_mandol

#include <windows.h>
#include <stdio.h>
#include <winsvc.h>

int main() {
  
  
    SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    if (scm == NULL) {
        printf("Could not open service control manager.\n");
        return 1;
    }

    DWORD numServices, bytesNeeded;
    EnumServicesStatus(scm, SERVICE_WIN32, SERVICE_STATE_ALL, NULL, 0, &bytesNeeded, &numServices, NULL);
    if (GetLastError() != ERROR_MORE_DATA) {
        printf("Could not enumerate services.\n");
        CloseServiceHandle(scm);
        return 1;
    }

    LPENUM_SERVICE_STATUS services = (LPENUM_SERVICE_STATUS)LocalAlloc(LPTR, bytesNeeded);
    if (services == NULL) {
        printf("Could not allocate memory for services.\n");
        CloseServiceHandle(scm);
        return 1;
    }

    if (!EnumServicesStatus(scm, SERVICE_WIN32, SERVICE_STATE_ALL, services, bytesNeeded, &bytesNeeded, &numServices, NULL)) {
        printf("Could not enumerate services.\n");
        LocalFree(services);
        CloseServiceHandle(scm);
        return 1;
    }

    
    printf("Service Name\t\tService Display Name\t\tService Status.\n");
    for (DWORD i = 0; i < numServices; i++) {
       
        SC_HANDLE service = OpenService(scm, services[i].lpServiceName, SERVICE_QUERY_STATUS);
        if (service == NULL) {
            printf("%-32s%-32sCould not open service\n", services[i].lpServiceName, services[i].lpDisplayName);
            continue;
        }

        
        SERVICE_STATUS status;
        if (!QueryServiceStatus(service, &status)) {
            printf("%-32s%-32sCould not get service status.\n", services[i].lpServiceName, services[i].lpDisplayName);
            CloseServiceHandle(service);
            continue;
        }

        
        char statusText[32];
        switch (status.dwCurrentState) {
            case SERVICE_RUNNING:
                sprintf(statusText, "Running");
                break;
            case SERVICE_STOPPED:
                sprintf(statusText, "Stopped");
                break;
            case SERVICE_PAUSED:
                sprintf(statusText, "Paused");
                break;
            case SERVICE_START_PENDING:
                sprintf(statusText, "Starting");
                break;
            case SERVICE_STOP_PENDING:
                sprintf(statusText, "Stopping");
                break;
            case SERVICE_CONTINUE_PENDING:
                sprintf(statusText, "Resuming");
                break;
            case SERVICE_PAUSE_PENDING:
                sprintf(statusText, "Pausing");
                break;
            default:
                sprintf(statusText, "Unknown");
                break;
        }
        printf("%-32s%-32s%s\n", services[i].lpServiceName, services[i].lpDisplayName, statusText);

       
        CloseServiceHandle(service);
    }

    
    LocalFree(services);
    CloseServiceHandle(scm);

    return 0;
}
