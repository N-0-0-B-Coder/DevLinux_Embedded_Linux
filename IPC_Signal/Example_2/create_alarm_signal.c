#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int seconds = 0; // global counter

void handle_alarm(int sig) {
    seconds++;
    printf("Timer: %d seconds\n", seconds);

    if (seconds >= 10) {
        printf("10 seconds reached. Exiting now.\n");
        exit(0);
    }

    /*
     * Re-arm the alarm for the next second
     * If we don’t call alarm(1) again inside the handler, the SIGALRM signal will be delivered only once.
    */ 
    alarm(1);
}

int main(void) {
    // Register the signal handler for SIGALRM
    signal(SIGALRM, handle_alarm);

    printf("Starting timer...\n");
    alarm(1); // Start the first alarm after 1 second

    // Wait for signals indefinitely
    while (1) {
        pause(); // sleep until next signal
    }

    return 0;
}
