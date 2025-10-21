#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int sigint_count = 0;  // Global counter for SIGINT

void handle_sigint(int sig) {
    sigint_count++;
    printf("SIGINT received (%d time%s)\n",
           sigint_count, sigint_count > 1 ? "s" : "");

    if (sigint_count >= 3) {
        printf("Received SIGINT 3 times. Exiting now.\n");
        exit(0);
    }
}

int main(void) {
    // Register signal handler
    signal(SIGINT, handle_sigint);

    printf("Program running. Press Ctrl+C to send SIGINT.\n");

    // Keep running until 3 signals are received
    while (1) {
        pause();  // Wait for signals
    }

    return 0;
}
