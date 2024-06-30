#include <windows.h>
#include <stdio.h>

int main() {
    const char *taskName = "task-name";
    char command[512];
    snprintf(command, sizeof(command), "powershell.exe Start-ScheduledTask -TaskName '%s'", taskName);
    HINSTANCE result = ShellExecute(
        NULL,              
        "open",        
        "powershell.exe",
        command,  
        NULL, 
        SW_SHOWNORMAL 
    );

    if ((int)result <= 32) {
        printf("Unable to start the scheduled task. Error code: %ld\n", (long)result);
    } else {
        printf("task started successfully.\n");
    }

    return 0;
}
