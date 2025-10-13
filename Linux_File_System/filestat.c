//#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

struct stat file_stats;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return -1;
    }

    const char *file_path = argv[1];
    if (lstat(file_path, &file_stats) == -1) {
        perror("lstat");
        return -1;
    }

    char *last_modified = ctime(&file_stats.st_mtime);

    printf("File path: %s\nFile type: %s\nFile size: %ld bytes\nLast modified: %s\n", file_path,
        S_ISREG(file_stats.st_mode) ? "Regular File" :
        S_ISDIR(file_stats.st_mode) ? "Directory" :
        S_ISCHR(file_stats.st_mode) ? "Character Device" :
        S_ISBLK(file_stats.st_mode) ? "Block Device" :
        S_ISFIFO(file_stats.st_mode) ? "FIFO" :
        S_ISLNK(file_stats.st_mode) ? "Symbolic Link" : "Unknown",
        file_stats.st_size,
        last_modified);
    return 0;
}