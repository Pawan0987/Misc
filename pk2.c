#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
// Created the code 
int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc != 3) {
        printf("Usage: %s <source_dir> <dest_dir>\n", argv[0]);
        return 1;
    }

    // Open the source directory
    DIR *source_dir = opendir(argv[1]);
    if (source_dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Create the destination directory
    if (mkdir(argv[2], 0777) != 0) {
        perror("mkdir");
        return 1;
    }

    // Loop through the source directory and copy each file to the destination directory
    struct dirent *entry;
    while ((entry = readdir(source_dir)) != NULL) {
        // Ignore "." and ".." directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the source and destination paths
        char src_path[1024];
        char dest_path[1024];
        snprintf(src_path, sizeof(src_path), "%s/%s", argv[1], entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", argv[2], entry->d_name);

        // Copy the file using the system call
        if (link(src_path, dest_path) != 0) {
            perror("link");
            return 1;
        }
    }

    // Close the source directory
    closedir(source_dir);

    // Delete the original directory
    if (rmdir(argv[1]) != 0) {
        perror("rmdir");
        return 1;
    }

    return 0;
}
