#include "file_operations.h"
#include "directory_operations.h"
#include "permissions.h"
#include "logger.h"
#include "file_operations.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

int main() {
    char command[256];
    char arg1[256], arg2[256];

    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        if (sscanf(command, "slist %s", arg1) == 1) {
            list_directory(arg1);
        } else if (sscanf(command, "screatefile %s", arg1) == 1) {
            create_file(arg1);
        } else if (sscanf(command, "screatedir %s", arg1) == 1) {
            create_directory(arg1);
        } else if (sscanf(command, "sremove %s", arg1) == 1) {
            delete_file(arg1);
        } else if (sscanf(command, "srmdir %s", arg1) == 1) {
            delete_directory(arg1);
        } else if (sscanf(command, "scopy %s %s", arg1, arg2) == 2) {
            copy_file(arg1, arg2);
        } else if (sscanf(command, "smove %s %s", arg1, arg2) == 2) {
            move_file(arg1, arg2);
        } else if (sscanf(command, "sdisplay %s", arg1) == 1) {
            display_file(arg1);
        } else if (sscanf(command, "ssearch %s %s", arg1, arg2) == 2) {
            search_file(arg1, arg2);
        }  else if (sscanf(command, "schmod %s %o", arg1, (unsigned int*)&arg2) == 2) {
            change_permissions(arg1, strtoul(arg2, NULL, 8));
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    return 0;
}

