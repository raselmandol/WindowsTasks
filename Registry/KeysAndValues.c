#include <Windows.h>
#include <stdio.h>

void PrintRegistryKeysAndValues(HKEY hKey, const char* subKey)
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

            HKEY hValueKey;
            if (RegOpenKeyExA(hSubKey, keyName, 0, KEY_READ, &hValueKey) == ERROR_SUCCESS)
            {
                DWORD valueIndex = 0;
                char valueName[MAX_PATH];
                DWORD valueNameSize = sizeof(valueName);
                DWORD valueType;
                BYTE valueData[4096];
                DWORD valueDataSize = sizeof(valueData);

                while (RegEnumValueA(hValueKey, valueIndex, valueName, &valueNameSize, NULL, &valueType, valueData, &valueDataSize) == ERROR_SUCCESS)
                {
                    printf("\t%s - ", valueName);

                    switch (valueType)
                    {
                        case REG_SZ:
                            printf("%s\n", (char*)valueData);
                            break;
                        case REG_DWORD:
                            printf("%u\n", *(DWORD*)valueData);
                            break;

                        default:
                            printf("<Unsupported value type>\n");
                            break;
                    }

                    valueIndex++;
                    valueNameSize = sizeof(valueName);
                    valueDataSize = sizeof(valueData);
                }

                RegCloseKey(hValueKey);
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
    PrintRegistryKeysAndValues(hRootKey, subKey);
    return 0;
}
