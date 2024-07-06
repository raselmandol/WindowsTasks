#include <stdio.h>
#include <Windows.h>

void filterRegistry(const char* keyPath, const char* filter) {
    HKEY hKey;
    LONG openResult = RegOpenKeyExA(HKEY_CURRENT_USER, keyPath, 0, KEY_READ, &hKey);
    
    if (openResult != ERROR_SUCCESS) {
        printf("Error opening registry key. Error code: %ld\n", openResult);
        return;
    }

    DWORD maxValueNameSize;
    DWORD maxValueDataSize;
    LONG enumResult = RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &maxValueNameSize, &maxValueDataSize, NULL, NULL);

    if (enumResult != ERROR_SUCCESS) {
        printf("querying registry key info error idk bro. error code: %ld\n", enumResult);
        RegCloseKey(hKey);
        return;
    }

    char* valueName = (char*)malloc(maxValueNameSize);
    DWORD valueNameSize = maxValueNameSize;
    BYTE* valueData = (BYTE*)malloc(maxValueDataSize);
    DWORD valueDataSize = maxValueDataSize;
    DWORD valueType;

    for (DWORD i = 0; ; i++) {
        valueDataSize = maxValueDataSize;
        valueNameSize = maxValueNameSize;
        enumResult = RegEnumValueA(hKey, i, valueName, &valueNameSize, NULL, &valueType, valueData, &valueDataSize);

        if (enumResult == ERROR_NO_MORE_ITEMS) {
            break;
        }

        if (enumResult != ERROR_SUCCESS) {
            printf("error while enumerating registry values. error code: %ld\n", enumResult);
            break;
        }

        // Example filter: check if the value name matches the filter string
        if (strstr(valueName, filter) != NULL) {
            printf("Name: %s, Type: %ld\n", valueName, valueType);

            if (valueType == REG_SZ || valueType == REG_EXPAND_SZ) {
                printf("data: %s\n", (char*)valueData);
            }
        }
    }

    free(valueName);
    free(valueData);
    RegCloseKey(hKey);
}

int main() {
    const char* keyPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const char* filter = "example";

    printf("Filtering registry entries with '%s' in path: %s\n", filter, keyPath);
    filterRegistry(keyPath, filter);

    return 0;
}
