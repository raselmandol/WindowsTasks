#include <iostream>
#include <Windows.h>
#include <Wtsapi32.h>

#pragma comment(lib, "Wtsapi32.lib")

int main() {
    //getting session id
    DWORD sessionId = WTSGetActiveConsoleSessionId();
    //getting username
    WCHAR* username = nullptr;
    DWORD size;
    if (WTSQuerySessionInformationW(WTS_CURRENT_SERVER_HANDLE, sessionId, WTSUserName, &username, &size)) {
        std::wcout << "Session ID: " << sessionId << std::endl;
        std::wcout << "User for Session ID " << sessionId << ": " << username << std::endl;

        WTSFreeMemory(username);
    } else {
        std::cerr << "Failed to get session information. Error code: " << GetLastError() << std::endl;
    }

    return 0;
}
