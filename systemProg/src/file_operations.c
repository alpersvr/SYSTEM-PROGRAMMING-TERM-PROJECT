#include "file_operations.h"
#include "logger.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void create_file(const char *path) {
    int fd = creat(path, 0644);
    if (fd == -1) {
        perror("creat");
        log_operation("screatefile", strerror(errno));
    } else {
        printf("File created: %s\n", path);
        log_operation("screatefile", "File created successfully");
        close(fd);
    }
}

void delete_file(const char *path) {
    if (unlink(path) == -1) {
        perror("unlink");
        log_operation("sremove", strerror(errno));
    } else {
        printf("File deleted: %s\n", path);
        log_operation("sremove", "File deleted successfully");
    }
}

void copy_file(const char *source, const char *destination) {
    int src_fd, dest_fd;
    ssize_t nread;
    char buffer[4096];

    src_fd = open(source, O_RDONLY);
    if (src_fd == -1) {
        perror("open source");
        log_operation("scopy", strerror(errno));
        return;
    }

    dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("open destination");
        log_operation("scopy", strerror(errno));
        close(src_fd);
        return;
    }

    while ((nread = read(src_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, nread) == -1) {
            perror("write");
            log_operation("scopy", strerror(errno));
            close(src_fd);
            close(dest_fd);
            return;
        }
    }

    close(src_fd);
    close(dest_fd);
    printf("File copied from %s to %s\n", source, destination);
    log_operation("scopy", "File copied successfully");
}

void move_file(const char *source, const char *destination) {
    if (rename(source, destination) == -1) {
        perror("rename");
        log_operation("smove", strerror(errno));
    } else {
        printf("File moved from %s to %s\n", source, destination);
        log_operation("smove", "File moved successfully");
    }
}

void display_file(const char *path) {
    int fd;
    ssize_t nread;
    char buffer[4096];

    fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        log_operation("sdisplay", strerror(errno));
        return;
    }

    while ((nread = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, nread) == -1) {
            perror("write");
            log_operation("sdisplay", strerror(errno));
            close(fd);
            return;
        }
    }

    close(fd);
    log_operation("sdisplay", "File displayed successfully");
}

