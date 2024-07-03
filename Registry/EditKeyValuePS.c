#include <Windows.h>
#include <stdio.h>
#include <string.h>

void EditRegistryValue(HKEY hKey, const char* subKey, const char* valueName, const char* newValue)
{
    HKEY hSubKey;
    LONG result;

    result = RegOpenKeyExA(hKey, subKey, 0, KEY_SET_VALUE, &hSubKey);
    if (result == ERROR_SUCCESS)
    {
        result = RegSetValueExA(hSubKey, valueName, 0, REG_SZ, (const BYTE*)newValue, strlen(newValue) + 1);
        if (result == ERROR_SUCCESS)
        {
            printf("Registry value updated successfully.\n");
        }
        else
        {
            printf("Failed to update registry value. Error code: %d\n", result);
        }

        RegCloseKey(hSubKey);
    }
    else
    {
        printf("Failed to open registry subkey. Error code: %d\n", result);
    }
}

int main()
{
    HKEY hRootKey = HKEY_CURRENT_USER;
    const char* subKey = "SOFTWARE\\Application";
    const char* valueName = "ValueName";
    char newValue[256];

    //prompt user for new value
    printf("Enter the new value: ");
    scanf("%s", newValue);

    //call function to edit registry value
    EditRegistryValue(hRootKey, subKey, valueName, newValue);

    return 0;
}
