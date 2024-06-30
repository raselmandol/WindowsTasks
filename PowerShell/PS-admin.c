#include <windows.h>
#include <stdio.h>

int main() {
    const char *exePath = "C:\\path\\example.exe";
    char command[512];
    snprintf(command, sizeof(command), "powershell.exe Start-Process -FilePath '%s' -Verb runAs", exePath);

    //Execute the command
    HINSTANCE result = ShellExecute(
        NULL,            
        "open",          
        "powershell.exe",  
        command,     
        NULL,            
        SW_SHOWNORMAL
    );
    if ((int)result <= 32) {
        printf("unable to execute the program. error code: %ld\n", (long)result);
    } else {
        printf("Program executed successfully.\n");
    }

    return 0;
}
