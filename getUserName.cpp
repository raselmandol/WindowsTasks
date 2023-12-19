//simple to use, simple to get
#include <iostream>
#include <Windows.h>

int main() {
    //getting username
    char username[UNLEN + 1];
    DWORD size = UNLEN + 1;
    if (GetUserNameA(username, &size)) {
        std::cout << "current User: " << username << std::endl;
    } else {
        std::cerr << "failed to get the current user's name. error code: " << GetLastError() << std::endl;
    }

    return 0;
}
