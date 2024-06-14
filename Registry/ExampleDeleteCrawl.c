#include <Windows.h>

int main()
{
    //The path of the registry key to be deleted
    const char* keyPath = "SOFTWARE\\MyApplication"; //adjust this, may change
    // you can add this to vector, list
    LONG result = RegDeleteKeyA(HKEY_CURRENT_USER, keyPath);
    if (result == ERROR_SUCCESS)
    {
        printf("Registry key deleted successfully.\n");
    }
    else
    {
        printf("Failed to delete registry key. Error code: %ld\n", result);
    }

    return 0;
}
