#include <Windows.h>
#include <stdio.h>

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
            printf("%s\\%s\n", subKey, keyName);
            index++;
            keyNameSize = sizeof(keyName);
        }

        RegCloseKey(hSubKey);
    }
}

int main()
{
    HKEY hRootKey = HKEY_CURRENT_USER;
    const char* subKey = "SOFTWARE";
    PrintRegistryKeys(hRootKey, subKey);
    return 0;
}
