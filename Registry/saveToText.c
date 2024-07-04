#include <Windows.h>
#include <stdio.h>

void SaveKeyValueToFile(FILE *file, const char *name, DWORD type, BYTE *data, DWORD dataSize) {
    fprintf(file, "[%s]\n", name);
    
    switch (type) {
        case REG_SZ:
        case REG_EXPAND_SZ:
            fprintf(file, "String: %s\n", (char *)data);
            break;
            
        case REG_DWORD:
            fprintf(file, "DWORD: %u\n", *(DWORD *)data);
            break;
            
        case REG_BINARY:
            fprintf(file, "Binary data:\n");
            for (DWORD i = 0; i < dataSize; i++) {
                fprintf(file, "%02X ", data[i]);
            }
            fprintf(file, "\n");
            break;
            
        default:
            fprintf(file, "unsupported\n");
    }
    
    fprintf(file, "\n");
}

void SaveRegistryToTextFile(HKEY hKey, const char *subKey, const char *fileName) {
    HKEY hOpenedKey;
    LONG result = RegOpenKeyExA(hKey, subKey, 0, KEY_READ, &hOpenedKey);
    
    if (result == ERROR_SUCCESS) {
        FILE *file = fopen(fileName, "w");
        if (file != NULL) {
            SaveKeyValueToFile(file, subKey, REG_SZ, NULL, 0);
            
            DWORD index = 0;
            char valueName[1024];
            DWORD valueNameSize = sizeof(valueName);
            DWORD valueType;
            BYTE valueData[4096]; //
            DWORD valueDataSize = sizeof(valueData);
            
            while (RegEnumValueA(hOpenedKey, index, valueName, &valueNameSize, NULL, &valueType, valueData, &valueDataSize) == ERROR_SUCCESS) {
                SaveKeyValueToFile(file, valueName, valueType, valueData, valueDataSize);
                
                index++;
                valueNameSize = sizeof(valueName);
                valueDataSize = sizeof(valueData);
            }
            
            fclose(file);
        } else {
            printf("unable to create or open file %s\n", fileName);
        }
        
        RegCloseKey(hOpenedKey);
    } else {
        printf("unable to open registry key %s\n", subKey);
    }
}

int main() {
    SaveRegistryToTextFile(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft", "registry_data.txt");
    
    return 0;
}
