#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // Creating process P1
    pid_t pid1 = fork();
    if (pid1 == 0) {
        printf("P1 (PID: %d) created\n", getpid());
        // Creating process P2
        pid_t pid2 = fork();
        if (pid2 == 0) {
            printf("P2 (PID: %d) created, parent PID: %d\n", getpid(), getppid());
            // Creating process P4
            pid_t pid4 = fork();
            if (pid4 == 0) {
                printf("P4 (PID: %d) created, parent PID: %d\n", getpid(), getppid());
                sleep(10); // P4 sleeps for 10 seconds
                printf("P4 (PID: %d) wakes up, parent PID: %d\n", getpid(), getppid());
            }
            exit(0); // P2 exits after creating P4
        } else {
            wait(NULL); // P1 waits for P2 to complete
            // Creating process P3
            pid_t pid3 = fork();
            if (pid3 == 0) {
                printf("P3 (PID: %d) created, parent PID: %d\n", getpid(), getppid());
            }
        }
    } else {
        wait(NULL); // Parent process waits for P1 to complete
        // Creating process P5
        pid_t pid5 = fork();
        if (pid5 == 0) {
            printf("P5 (PID: %d) created, parent PID: %d\n", getpid(), getppid());
            exit(0); // P5 exits immediately after creation, becoming a zombie process
        }
    }

    // Parent process prints a message
    printf("Parent process (PID: %d) completed\n", getpid());

    return 0;
}
