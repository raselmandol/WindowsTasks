#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

void printDirectoryContents(const char* path, int level) {
    DIR* directory = opendir(path);
    if (directory == NULL) {
        printf("Failed to open directory: %s\n", path);
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            // Indent based on the level
            for (int i = 0; i < level; i++) {
                printf("  ");
            }

            printf("|- %s [Directory]\n", entry->d_name);

            //recursive call for subdirectory
            char newPath[256];
            snprintf(newPath, sizeof(newPath), "%s/%s", path, entry->d_name);
            printDirectoryContents(newPath, level + 1);
        } else {
            for (int i = 0; i < level; i++) {
                printf("  ");
            }

            //file information
            char filePath[256];
            snprintf(filePath, sizeof(filePath), "%s/%s", path, entry->d_name);
            struct stat fileStat;
            if (stat(filePath, &fileStat) < 0) {
                printf("|- %s [Unknown]\n", entry->d_name);
                continue;
            }

            //file modification time
            struct tm* modifiedTime = localtime(&fileStat.st_mtime);
            char modifiedTimeString[20];
            strftime(modifiedTimeString, sizeof(modifiedTimeString), "%Y-%m-%d %H:%M:%S", modifiedTime);

            printf("|- %s [File]\n", entry->d_name);
            printf("   |- Created: %s\n", ctime(&fileStat.st_ctime));
            printf("   |- Modified: %s", modifiedTimeString);
            printf("   |- Size: %lld bytes\n", (long long)fileStat.st_size);
        }
    }

    closedir(directory);
}

int main() {
    const char* path = "/path/to/directory";  //your drive path here
    printf("Contents of Directory:\n");
    printDirectoryContents(path, 0);
    return 0;
}
