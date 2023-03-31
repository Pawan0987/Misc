#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {

    // Create 4 files with some sample content
    system("echo 'This is file 1.' > file1.txt");
    system("echo 'This is file 2.' > file2.txt");
    system("echo 'This is file 3.' > file3.txt");
    system("echo 'This is file 4.' > file4.txt");

    // Open the output file for writing
    int output_file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    //Copy 1/4 of the content of each file into the output file
    for (int i = 1; i <= 4; i++) {
        // Open the input file for reading
        char filename[10];
        sprintf(filename, "file%d.txt", i);
        int input_file = open(filename, O_RDONLY);
       //Copy 1/4 of the content of the input file into the output file
        char buffer[BUFFER_SIZE];
        int total_bytes_read = 0;
        int bytes_to_read = 0;
        int bytes_read = 0;
        int bytes_written = 0;
        off_t file_size = lseek(input_file, 0, SEEK_END);
        bytes_to_read = file_size / 4;
        lseek(input_file, 0, SEEK_SET);
        while (total_bytes_read < bytes_to_read &&( bytes_read=read(input_file , buffer , file_size/4))>0 ) {
            bytes_written = write(output_file, buffer, bytes_read);
            total_bytes_read += bytes_read;
        }

        
    }

   
    return 0;
}
