#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // Check if source directory and destination directory are provided
    if (argc != 3) {
        printf("Usage: %s <source_dir> <destination_dir>\n", argv[0]);
        return 1;
    }

    // Open source directory
    DIR *src_dir = opendir(argv[1]);
    if (src_dir == NULL) {
        printf("Error opening source directory\n");
        return 1;
    }

    // Create destination directory
    int ret = mkdir(argv[2], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (ret != 0) {
        printf("Error creating destination directory\n");
        return 1;
    }

    // Loop through source directory and copy files to destination directory
    struct dirent *entry;
    while ((entry = readdir(src_dir)) != NULL) {
        // Skip current directory and parent directory
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Get full path of source file
        char src_path[1024];
        snprintf(src_path, sizeof(src_path), "%s/%s", argv[1], entry->d_name);

        // Open source file for reading
        int src_fd = open(src_path, O_RDONLY);
        if (src_fd == -1) {
            printf("Error opening source file %s\n", src_path);
            continue;
        }

        // Get full path of destination file
        char dest_path[1024];
        snprintf(dest_path, sizeof(dest_path), "%s/%s", argv[2], entry->d_name);

        // Open destination file for writing
        int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (dest_fd == -1) {
            printf("Error creating destination file %s\n", dest_path);
            close(src_fd);
            continue;
        }

        // Copy contents of source file to destination file
        char buffer[1024];
        ssize_t nread;
        while ((nread = read(src_fd, buffer, sizeof(buffer))) > 0) {
            ssize_t nwritten = write(dest_fd, buffer, nread);
            if (nwritten != nread) {
                printf("Error writing to destination file %s\n", dest_path);
                close(src_fd);
                close(dest_fd);
                continue;
            }
        }

        // Close source and destination files
        close(src_fd);
        close(dest_fd);
    }

    // Close source directory
    closedir(src_dir);

    return 0;
}
