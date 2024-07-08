#include <stdio.h>
#include <windows.h>

int main() {
    // define path
    LPCSTR keyPath = "SOFTWARE\\software\\Settings";

    HKEY hKey;
    LONG regOpenResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, keyPath, 0, KEY_ALL_ACCESS, &hKey);

    if (regOpenResult != ERROR_SUCCESS) {
        printf("error opening registry key. error code: %ld\n", regOpenResult); //check
        return 1;
    }

    //delete
    LONG regDeleteResult = RegDeleteTree(hKey, NULL);

    if (regDeleteResult == ERROR_SUCCESS) {
        printf("Registry key deleted successfully.\n");
    } else {
        printf("error deleting registry key. error code: %ld\n", regDeleteResult);
    }

    RegCloseKey(hKey);

    return 0;
}
