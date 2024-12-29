#include "logger.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

void log_operation(const char *operation, const char *result) {
    int fd = open("log/operations.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open log");
        fprintf(stderr, "Failed to open log file: %s\n", strerror(errno));
        return;
    }

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strcspn(timestamp, "\n")] = 0;

    if (dprintf(fd, "%s: %s - %s\n", timestamp, operation, result) < 0) {
        perror("dprintf");
        fprintf(stderr, "Failed to write to log file: %s\n", strerror(errno));
    }
    
    close(fd);
}

