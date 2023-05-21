#include <Windows.h>
#include <stdio.h>

int main()
{
    LPCWSTR command = L"powershell.exe";

    if (ShellExecute(NULL, L"open", command, NULL, NULL, SW_SHOWNORMAL) > (HINSTANCE)32)
    {
        printf("PowerShell opened in normal mode.\n");
    }
    else
    {
        printf("Failed to open PowerShell in normal mode.\n");
    }

    return 0;
}
