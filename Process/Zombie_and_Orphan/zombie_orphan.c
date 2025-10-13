#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <zombie/orphan>\n", argv[0]);
        return -1;
    }
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process (PID: %d)\n", getpid());

        if (strcmp(argv[1], "orphan") == 0) {
            sleep(5); // Wait for parent to exit
        }
        else if (strcmp(argv[1], "zombie") == 0) {
            printf("Child process (PID: %d) turn zombie\n", getpid());
            exit(0); // Child exits immediately, becoming a zombie
        } else {
            printf("Invalid argument. Use 'orphan' or 'zombie'.\n");
            return -1;
        }

        while (1) {
            // Keep the child process running to observe orphan behavior
            sleep(1);
        }
    }
    else
    {
        // Parent process
        printf("Parent process (PID: %d) created child (PID: %d)\n", getpid(), pid);

        if (strcmp(argv[1], "orphan") == 0) {
            printf("Parent process (PID: %d) will exit, making child (PID: %d) an orphan\n", getpid(), pid);
            exit(0); // Parent exits, making the child an orphan
        }
        else if (strcmp(argv[1], "zombie") == 0) {
            printf("Parent process (PID: %d) will wait to observe the zombie child (PID: %d)\n", getpid(), pid);
            sleep(5); // Wait child to become a zombie
        }
        
        while (1) {
            // Keep the parent process running to observe zombie behavior
            sleep(1);
        }
    }

    return 0;
}