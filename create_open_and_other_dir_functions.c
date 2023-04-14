#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main()
{
    char *desktop_path = getenv("HOME");
    desktop_path = strcat(desktop_path, "/Desktop");

    // Create directory
    int dir_result = mkdir(desktop_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (dir_result == -1) {
        printf("Error creating directory\n");
        return 1;
    }

    // Change working directory to the newly created directory
    chdir(desktop_path);

    // Create file inside directory
    FILE *fp = fopen("test.txt", "w");
    if (fp == NULL) {
        printf("Error creating file\n");
        return 1;
    }
    fprintf(fp, "Hello, World!");
    fclose(fp);

    // List contents of directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        printf("Error opening directory\n");
        return 1;
    }
    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        printf("%s\n", ent->d_name);
    }
    closedir(dir);

    return 0;
}
