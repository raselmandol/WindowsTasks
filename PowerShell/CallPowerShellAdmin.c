#include <Windows.h>
#include <Shlwapi.h>
#include <stdio.h>

int main()
{
    LPCWSTR command = L"powershell.exe";
    LPCWSTR arguments = L"-Command \"Start-Process powershell -Verb RunAs\"";

    SHELLEXECUTEINFO shellInfo = { sizeof(SHELLEXECUTEINFO) };
    shellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shellInfo.lpFile = command;
    shellInfo.lpParameters = arguments;
    shellInfo.nShow = SW_HIDE;

    if (ShellExecuteEx(&shellInfo))
    {
        WaitForSingleObject(shellInfo.hProcess, INFINITE);
        CloseHandle(shellInfo.hProcess);
        printf("PowerShell opened in admin mode.\n");
    }
    else
    {
        printf("Failed to open PowerShell in admin mode.\n");
    }

    return 0;
}
