#include <Windows.h>
#include <stdio.h>
#include <Aclapi.h>

void PrintRegistryKeys(HKEY hKey, const char* subKey)
{
    HKEY hSubKey;
    if (RegOpenKeyExA(hKey, subKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS)
    {
        DWORD index = 0;
        char keyName[MAX_PATH];
        DWORD keyNameSize = sizeof(keyName);

        while (RegEnumKeyExA(hSubKey, index, keyName, &keyNameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
        {
            FILETIME creationTime;
            if (RegQueryInfoKeyA(hSubKey, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &creationTime) == ERROR_SUCCESS)
            {
                SYSTEMTIME systemTime;
                if (FileTimeToSystemTime(&creationTime, &systemTime))
                {
                    printf("%s\\%s - Created on %02d/%02d/%04d %02d:%02d:%02d\n", subKey, keyName,
                        systemTime.wDay, systemTime.wMonth, systemTime.wYear,
                        systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
                }
            }

            index++;
            keyNameSize = sizeof(keyName);
        }

        RegCloseKey(hSubKey);
    }
}

int main()
{
    //Registry hive and subkey here
    HKEY hRootKey = HKEY_CURRENT_USER;
    const char* subKey = "SOFTWARE";

    PrintRegistryKeys(hRootKey, subKey);

    return 0;
}
