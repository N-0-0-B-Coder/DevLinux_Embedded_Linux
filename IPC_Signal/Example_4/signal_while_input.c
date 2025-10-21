#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/types.h>

static volatile sig_atomic_t sigint_flag = 0;
static volatile sig_atomic_t sigterm_flag = 0;

static void on_sigint(int sig)  { (void)sig; sigint_flag = 1; }
static void on_sigterm(int sig) { (void)sig; sigterm_flag = 1; }

int main(void) {
    // Register signal handlers
    struct sigaction sa = {0};

    sa.sa_handler = on_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; // Let select() be interrupted by signals (EINTR)
    if (sigaction(SIGINT, &sa, NULL) == -1) { perror("sigaction SIGINT"); return 1; }

    sa.sa_handler = on_sigterm;
    if (sigaction(SIGTERM, &sa, NULL) == -1) { perror("sigaction SIGTERM"); return 1; }

    printf("PID: %d\n", getpid());
    printf("Type something and press Enter (Ctrl+C prints a message, SIGTERM exits).\n");

    char line[1024];

    for (;;) {
        // 1) Wait for either stdin to be readable OR a signal to arrive
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);

        struct timeval tv;
        tv.tv_sec = 1;   // short timeout to periodically check signal flags
        tv.tv_usec = 0;

        int ret = select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv);

        if (ret == -1) {
            if (errno == EINTR) {
                // select() was interrupted by a signal — handle flags below
            } else {
                perror("select");
                break;
            }
        } else if (ret > 0 && FD_ISSET(STDIN_FILENO, &rfds)) {
            // 2) Stdin is ready — read a line and echo it
            if (fgets(line, sizeof(line), stdin) != NULL) {
                // Strip trailing newline for clean echo
                size_t n = strlen(line);
                if (n && line[n-1] == '\n') line[n-1] = '\0';
                printf("You typed: %s\n", line);
            } else {
                // EOF (Ctrl+D) or error
                if (feof(stdin)) {
                    printf("EOF on stdin. Exiting.\n");
                    break;
                } else {
                    perror("fgets");
                    break;
                }
            }
        }

        // 3) Handle pending signals (set by async handlers)
        if (sigint_flag) {
            sigint_flag = 0;
            printf("SIGINT received.\n");
        }
        if (sigterm_flag) {
            printf("SIGTERM received. Exiting.\n");
            break;
        }
    }

    return 0;
}
