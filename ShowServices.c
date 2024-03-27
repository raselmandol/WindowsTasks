//Used GCC V- 12.2.0
//Made_simple_by_rasel_mandol

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

    
    printf("Service Name\t\tService Display Name\n");
    //iter_over_services
    for (DWORD i = 0; i < numServices; i++) {
        printf("%-32s%s\n", services[i].lpServiceName, services[i].lpDisplayName);
    }

    LocalFree(services);
    CloseServiceHandle(scm);

    return 0;
}
