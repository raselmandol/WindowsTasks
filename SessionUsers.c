#include <Windows.h>
#include <stdio.h>
#include <WtsApi32.h>

#pragma comment(lib, "Wtsapi32.lib")

int main() {
    //getting session info
    PWTS_SESSION_INFO sessionInfo;
    DWORD sessionCount;
    if (WTSEnumerateSessions(WTS_CURRENT_SERVER_HANDLE, 0, 1, &sessionInfo, &sessionCount)) {
        for (DWORD i = 0; i < sessionCount; i++) {
            if (sessionInfo[i].State == WTSActive) {
                printf("User %d is logged on\n", sessionInfo[i].SessionId);
                printf("    Station name: %S\n", sessionInfo[i].pWinStationName);
                printf("    Session name: %S\n", sessionInfo[i].pSessionName);
                printf("    Session ID: %d\n", sessionInfo[i].SessionId);
                printf("    State: %d\n", sessionInfo[i].State);
                printf("    Logon time: %s", ctime(&sessionInfo[i].LogonTime));
            }
        }
        WTSFreeMemory(sessionInfo);
    } else {
        printf("Could not enumerate sessions.\n");
        return 1;
    }

    return 0;
}
