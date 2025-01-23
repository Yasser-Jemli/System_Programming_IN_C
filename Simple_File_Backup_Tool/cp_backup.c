#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void copyFile(const char* src, const char* dest);
void copyDirectory(const char* src, const char* dest);
void logMessage(const char* message);


void copyFile(const char* src, const char* dest) {
    int srcFd, destFd;
    ssize_t bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];
    struct stat srcStat;

    // Open source file
    srcFd = open(src, O_RDONLY);
    if (srcFd == -1) {
        logMessage("Error: Failed to open source file.");
        return;
    }

    // Get source file metadata
    if (fstat(srcFd, &srcStat) == -1) {
        logMessage("Error: Failed to get source file metadata.");
        close(srcFd);
        return;
    }

    // Open destination file
    destFd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, srcStat.st_mode);
    if (destFd == -1) {
        logMessage("Error: Failed to open destination file.");
        close(srcFd);
        return;
    }

    // Copy file contents
    while ((bytesRead = read(srcFd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(destFd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            logMessage("Error: Failed to write to destination file.");
            close(srcFd);
            close(destFd);
            return;
        }
    }

    // Close files
    close(srcFd);
    close(destFd);

    // Set file permissions
    if (chmod(dest, srcStat.st_mode) == -1) {
        logMessage("Error: Failed to set destination file permissions.");
    }

    logMessage("File copied successfully.");
}

void copyDirectory(const char* src, const char* dest) {
    DIR* dir;
    struct dirent* entry;
    struct stat srcStat;
    char srcPath[PATH_MAX], destPath[PATH_MAX];

    // Open source directory
    if ((dir = opendir(src)) == NULL) {
        logMessage("Error: Failed to open source directory.");
        return;
    }

    // Create destination directory
    if (mkdir(dest, 0777) == -1 && errno != EEXIST) {
        logMessage("Error: Failed to create destination directory.");
        closedir(dir);
        return;
    }

    // Traverse source directory
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; // Skip "." and ".."
        }

        // Construct full paths
        snprintf(srcPath, PATH_MAX, "%s/%s", src, entry->d_name);
        snprintf(destPath, PATH_MAX, "%s/%s", dest, entry->d_name);

        // Get file/directory metadata
        if (lstat(srcPath, &srcStat) == -1) {
            logMessage("Error: Failed to get file/directory metadata.");
            continue;
        }

        // Copy files or directories
        if (S_ISDIR(srcStat.st_mode)) {
            copyDirectory(srcPath, destPath); // Recursive call for directories
        } else {
            copyFile(srcPath, destPath); // Copy files
        }
    }

    closedir(dir);
    logMessage("Directory copied successfully.");
}

void logMessage(const char* message) {
    FILE* logFile = fopen("backup.log", "a");
    if (logFile == NULL) {
        perror("Error: Failed to open log file.");
        return;
    }

    fprintf(logFile, "%s\n", message);
    fclose(logFile);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_directory> <destination_directory>\n", argv[0]);
        return 1;
    }

    const char* srcDir = argv[1];
    const char* destDir = argv[2];

    // Check if source directory exists
    struct stat srcStat;
    if (stat(srcDir, &srcStat) == -1 || !S_ISDIR(srcStat.st_mode)) {
        printf("Error: Source directory does not exist or is not a directory.\n");
        return 1;
    }

    // Start backup
    copyDirectory(srcDir, destDir);

    printf("Backup completed. Check backup.log for details.\n");
    return 0;
}