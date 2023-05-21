#include <Windows.h>
#include <stdio.h>

int main()
{
    LPCWSTR command = L"powershell.exe -Command \"cd 'C:\\Windows'; Get-ChildItem\"";
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;

    ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
    startupInfo.cb = sizeof(STARTUPINFO);

    if (CreateProcess(NULL, (LPWSTR)command, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo))
    {
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    }
    else
    {
        printf("Failed to execute PowerShell command.\n");
    }

    return 0;
}
