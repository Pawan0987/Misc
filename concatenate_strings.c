#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 10
#define MAX_STRING_LEN 100

void *concatenate_strings(void *arg);

int main()
{
    pthread_t thread_id;
    char strings[MAX_STRINGS][MAX_STRING_LEN];
    char result[MAX_STRINGS * MAX_STRING_LEN] = {0};

    // Prompt the user to enter strings
    printf("Enter up to %d strings of length up to %d characters each (empty string to finish):\n", MAX_STRINGS, MAX_STRING_LEN - 1);
    int num_strings = 0;
    do {
        fgets(strings[num_strings], MAX_STRING_LEN, stdin);
        strings[num_strings][strcspn(strings[num_strings], "\n")] = '\0'; // remove newline character from input
        num_strings++;
    } while (num_strings < MAX_STRINGS && strlen(strings[num_strings - 1]) > 0);

    // Create a thread to concatenate the strings
    pthread_create(&thread_id, NULL, concatenate_strings, (void *)strings);

    // Wait for the thread to complete
    void *thread_result;
    pthread_join(thread_id, &thread_result);

    // Print the concatenated string
    printf("Concatenated string: %s\n", (char *)thread_result);

    return 0;
}

void *concatenate_strings(void *arg)
{
    char (*strings)[MAX_STRING_LEN] = (char (*)[MAX_STRING_LEN])arg; // cast the void pointer to an array of strings
    char *result = malloc(MAX_STRINGS * MAX_STRING_LEN); // allocate memory for the concatenated string

    result[0] = '\0'; // initialize the result string to an empty string

    for (int i = 0; i < MAX_STRINGS; i++) {
        if (strlen(strings[i]) == 0) {
            break; // exit the loop if we encounter an empty string
        }
        strcat(result, strings[i]); // concatenate the current string to the result string
    }

    return (void *)result;
}
