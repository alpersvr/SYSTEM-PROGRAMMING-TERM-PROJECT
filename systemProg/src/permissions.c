#include "permissions.h"
#include "logger.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void change_permissions(const char *path, mode_t mode) {
    if (chmod(path, mode) == -1) {
        perror("chmod");
        log_operation("schmod", strerror(errno));
    } else {
        printf("Permissions changed for %s\n", path);
        log_operation("schmod", "Permissions changed successfully");
    }
}

