// exec_env_demo.c
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(void) {
    if (setenv("MY_COMMAND", "ls", 1) != 0) {
        perror("setenv");
        return -1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        // --- Child process ---
        const char *cmd = getenv("MY_COMMAND");
        if (!cmd || *cmd == '\0') {
            fprintf(stderr, "MY_COMMAND is not set or empty\n");
            exit(99);
        }

        printf("[child %d] Executing command from env: %s\n", getpid(), cmd);
        execlp(cmd, cmd, (char *)NULL);

        // This line is only reached if execlp fails
        fprintf(stderr, "execlp(%s) failed: %s\n", cmd, strerror(errno));
        exit(99);
    }
    else {
        // --- Parent process ---
        int status = 0;
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid");
            return -1;
        }

        if (WIFEXITED(status)) {
            printf("[parent] Child exited with code %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("[parent] Child killed by signal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
