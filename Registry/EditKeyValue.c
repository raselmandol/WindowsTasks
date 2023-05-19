#include <Windows.h>
#include <stdio.h>

void EditRegistryValue(HKEY hKey, const char* subKey, const char* valueName, const char* newValue)
{
    HKEY hSubKey;
    if (RegOpenKeyExA(hKey, subKey, 0, KEY_SET_VALUE, &hSubKey) == ERROR_SUCCESS)
    {
        if (RegSetValueExA(hSubKey, valueName, 0, REG_SZ, (const BYTE*)newValue, strlen(newValue) + 1) == ERROR_SUCCESS)
        {
            printf("Registry value updated successfully.\n");
        }
        else
        {
            printf("failed to update registry value.\n");
        }

        RegCloseKey(hSubKey);
    }
    else
    {
        printf("failed to open registry subkey.\n");
    }
}

int main()
{
    //registry hive, subkey, value name and new value
    HKEY hRootKey = HKEY_CURRENT_USER;
    const char* subKey = "SOFTWARE\\Application";
    const char* valueName = "ValueName";
    char newValue[256];
    printf("Enter the new value: ");
    scanf("%s", newValue);
    EditRegistryValue(hRootKey, subKey, valueName, newValue);
    return 0;
}
