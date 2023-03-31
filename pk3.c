#include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #include <unistd.h> 
 #include <fcntl.h> 
 #include <errno.h> 
 #include <sys/stat.h> 
  
 #define MAX_FILENAME_LENGTH 256 
  
 int main() { 
     // Define the five file names 
     char* filenames[5] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"}; 
  
     // Initialize the maximum file size and file name 
     off_t max_file_size = 0; 
     char max_file_name[MAX_FILENAME_LENGTH]; 
  
     // Find the largest file size and file name among the five files 
     for (int i = 0; i < 5; i++) { 
         // Get the file size using the stat() function 
         struct stat st; 
         if (stat(filenames[i], &st) == -1) { 
             printf("Error: could not get file size for %s. %s\n", filenames[i], strerror(errno)); 
             return 1; 
         } 
         off_t file_size = st.st_size; 
  
         // Check if this file is larger than the current maximum 
         if (file_size > max_file_size) { 
             max_file_size = file_size; 
             strncpy(max_file_name, filenames[i], MAX_FILENAME_LENGTH); 
         } 
     } 
  
     // Print the largest file name 
     printf("The largest file name (size-wise) is %s with a size of %ld bytes.\n", max_file_name, max_file_size); 
  
     // Done 
     return 0; 
 }
