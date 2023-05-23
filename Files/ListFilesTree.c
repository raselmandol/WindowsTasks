#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

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

            for (int i = 0; i < level; i++) {
                printf("  ");
            }

            printf("|- %s\n", entry->d_name);

            //recursive call for subdirectories
            char newPath[256];
            snprintf(newPath, sizeof(newPath), "%s/%s", path, entry->d_name);
            printDirectoryContents(newPath, level + 1);
        } else {
            for (int i = 0; i < level; i++) {
                printf("  ");
            }

            printf("|- %s\n", entry->d_name);
        }
    }

    closedir(directory);
}

int main() {
    const char* path = "/path/to/drive";  //Your drive path here
    printf("Contents of Drive: \n");
    printDirectoryContents(path, 0);
    return 0;
}
