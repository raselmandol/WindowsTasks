#include <iostream>
#include <Windows.h>

int main() {
    //the process token
    HANDLE hToken;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_SESSION_INFORMATION sessionInfo;
        DWORD size;
        if (GetTokenInformation(hToken, TokenSessionId, &sessionInfo, sizeof(sessionInfo), &size)) {
            std::cout << "session ID: " << sessionInfo.SessionId << std::endl;
        } else {
            std::cerr << "failed to get session information. Error code: " << GetLastError() << std::endl;
        }

        //the user name associated with the token
        char username[UNLEN + 1];
        if (GetUserNameA(username, &size)) {
            std::cout << "current User: " << username << std::endl;
        } else {
            std::cerr << "failed to get the current user's name. Error code: " << GetLastError() << std::endl;
        }

        CloseHandle(hToken);
    } else {
        std::cerr << "failed to open process token. Error code: " << GetLastError() << std::endl;
    }

    return 0;
}
