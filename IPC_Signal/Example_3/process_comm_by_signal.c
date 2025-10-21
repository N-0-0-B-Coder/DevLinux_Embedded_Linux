#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t received = 0;

void child_handler(int sig) {
    (void)sig;
    received++;
    printf("Child: Received signal from parent (%d)\n", received);
}

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // ---- Child ----
        signal(SIGUSR1, child_handler);
        printf("Child PID: %d waiting for SIGUSR1...\n", getpid());
        // Wait until we’ve printed 5 messages (or parent exits)
        while (received < 5) {
            pause();  // sleep until a signal arrives
        }
        printf("Child: done.\n");
        exit(0);
    } else {
        // ---- Parent ----
        printf("Parent PID: %d; Child PID: %d\n", getpid(), pid);
        for (int i = 1; i <= 5; i++) {
            sleep(2);                      // 2-second interval
            printf("Parent: sending SIGUSR1 (%d/5)\n", i);

            // We use kill to send a specific signal to a specific process (the child), identified by its PID.
            if (kill(pid, SIGUSR1) == -1) {
                perror("kill");
                break;
            }
        }
        // Clean up child
        waitpid(pid, NULL, 0);
        printf("Parent: done.\n");
        exit(0);
    }
    return 0;
}
