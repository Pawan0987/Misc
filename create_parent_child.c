#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    pid1 = getpid();
    printf("P1 created (pid=%d, parent=%d)\n", pid1, getppid());

    pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        pid_t pid3;

        pid3 = getpid();
        printf("P3 created (pid=%d, parent=%d)\n", pid3, getppid());
        exit(0);
    } else {
        printf("P2 created (pid=%d, parent=%d)\n", pid2, pid1);
        wait(NULL);
    }

    return 0;
}
