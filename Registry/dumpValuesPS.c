#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

void DumpRegistryKey(HKEY hKey, const TCHAR* subKey)
{
    HKEY hSubKey;
    LONG result;

    //open the registry subkey
    result = RegOpenKeyEx(hKey, subKey, 0, KEY_READ, &hSubKey);
    if (result != ERROR_SUCCESS)
    {
        printf("Failed to open registry key: %s. Error code: %d\n", subKey, result);
        return;
    }

    //enumerate subkeys
    DWORD index = 0;
    TCHAR subKeyName[255];
    DWORD subKeyNameSize = sizeof(subKeyName);
    while (RegEnumKeyEx(hSubKey, index, subKeyName, &subKeyNameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
    {
        printf("Subkey: %s\n", subKeyName);

        //recursively dump subkeys
        TCHAR newSubKey[512];
        _stprintf_s(newSubKey, _countof(newSubKey), _T("%s\\%s"), subKey, subKeyName);
        DumpRegistryKey(hSubKey, newSubKey);

        index++;
        subKeyNameSize = sizeof(subKeyName);
    }

    //enumerate values
    DWORD valueType;
    BYTE data[1024];
    DWORD dataSize = sizeof(data);
    TCHAR valueName[255];
    DWORD valueNameSize = sizeof(valueName);
    DWORD valueIndex = 0;

    while (RegEnumValue(hSubKey, valueIndex, valueName, &valueNameSize, NULL, &valueType, data, &dataSize) == ERROR_SUCCESS)
    {
        switch (valueType)
        {
        case REG_SZ:
            printf("Value: %s = %s\n", valueName, (TCHAR*)data);
            break;
        case REG_DWORD:
            printf("Value: %s = %d\n", valueName, *(DWORD*)data);
            break;
        default:
            printf("Value: %s (type %d)\n", valueName, valueType);
            break;
        }

        valueIndex++;
        valueNameSize = sizeof(valueName);
        dataSize = sizeof(data);
    }

    RegCloseKey(hSubKey);
}

int main()
{
    HKEY hRootKey = HKEY_CURRENT_USER;
    const TCHAR* subKey = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion");

    DumpRegistryKey(hRootKey, subKey);

    return 0;
}
