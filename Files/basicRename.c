#include <stdio.h>
#include <string.h>

int main() {
    char oldPath[100], newPath[100];

    printf("Enter the file location: ");
    scanf("%s", oldPath);

    printf("Enter the new file name: ");
    scanf("%s", newPath);

    char* directory = strrchr(oldPath, '/');
    if (directory != NULL) {
        *directory = '\0';
        directory++;
    } else {
        directory = ".";
    }

    char newLocation[100];
    snprintf(newLocation, sizeof(newLocation), "%s/%s", directory, newPath);

    if (rename(oldPath, newLocation) == 0) {
        printf("File renamed successfully.\n");
    } else {
        printf("Failed to rename the file.\n");
    }

    return 0;
}
