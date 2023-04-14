#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void simulate_fork(int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        if (fork() == 0) {
            printf("Child process #%d (pid=%d)\n", i+1, getpid());
            simulate_fork(i);
            exit(0);
        }
    }

    for (j = 0; j < n; j++) {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);

    simulate_fork(n);

    return 0;
}
