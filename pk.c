#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc != 4) {
        printf("Usage: %s <file1> <file2> <file3>\n", argv[0]);
        return 1;
    }

    // Get the size of each file and compare them
    struct stat file_stat;
    char *largest_file_name = NULL;
    off_t largest_file_size = 0;

    for (int i = 1; i <= 3; i++) {
        if (stat(argv[i], &file_stat) != 0) {
            perror("stat");
            return 1;
        }

        if (file_stat.st_size > largest_file_size) {
            largest_file_name = argv[i];
            largest_file_size = file_stat.st_size;
        }
    }

    // Print the largest file name
    printf("The largest file is: %s\n", largest_file_name);

    return 0;
}
