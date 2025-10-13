#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork error");
        return -1;
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d)\n", getpid());
        sleep(2); // Simulate some work in child
        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(77);
    } else {
        // Parent process
        printf("Parent process (PID: %d) waiting for child (PID: %d)...\n", getpid(), pid);
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid error");
            return -1;
        }
        if (WIFEXITED(status)) {
            printf("Child process (PID: %d) exited with status: %d\n", pid, WEXITSTATUS(status));
        } else {
            printf("Child process (PID: %d) did not exit normally.\n", pid);
        }
    }

    return 0;
}