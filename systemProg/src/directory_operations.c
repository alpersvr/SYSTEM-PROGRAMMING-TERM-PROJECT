#include "directory_operations.h"
#include "logger.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

void create_directory(const char *path) {
    if (mkdir(path, 0755) == -1) {
        perror("mkdir");
        log_operation("screatedir", strerror(errno));
    } else {
        printf("Directory created: %s\n", path);
        log_operation("screatedir", "Directory created successfully");
    }
}

void delete_directory(const char *path) {
    if (rmdir(path) == -1) {
        perror("rmdir");
        log_operation("srmdir", strerror(errno));
    } else {
        printf("Directory deleted: %s\n", path);
        log_operation("srmdir", "Directory deleted successfully");
    }
}

void list_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[512];

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        log_operation("slist", strerror(errno));
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &file_stat) == 0) {
            printf("%s\t%ld bytes\t%o\n", entry->d_name, file_stat.st_size, file_stat.st_mode & 0777);
        }
    }

    closedir(dir);
    log_operation("slist", "Directory listed successfully");
}

void search_file(const char *directory, const char *filename) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(directory)) == NULL) {
        perror("opendir");
        log_operation("ssearch", strerror(errno));
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, filename) != NULL) {
            printf("Found: %s/%s\n", directory, entry->d_name);
        }
    }

    closedir(dir);
    log_operation("ssearch", "Search completed");
}

void move_directory(const char *source, const char *destination) {
    if (rename(source, destination) == -1) {
        perror("rename");
        log_operation("smove", strerror(errno));
    } else {
        printf("Directory moved from %s to %s\n", source, destination);
        log_operation("smove", "Directory moved successfully");
    }
}

void copy_directory(const char *source, const char *destination) {
    DIR *dir;
    struct dirent *entry;
    char src_path[512], dest_path[512];

    if ((dir = opendir(source)) == NULL) {
        perror("opendir");
        log_operation("scopy", strerror(errno));
        return;
    }

    if (mkdir(destination, 0755) == -1) {
        perror("mkdir");
        log_operation("scopy", strerror(errno));
        closedir(dir);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(src_path, sizeof(src_path), "%s/%s", source, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", destination, entry->d_name);

        struct stat entry_stat;
        if (stat(src_path, &entry_stat) == -1) {
            perror("stat");
            log_operation("scopy", strerror(errno));
            continue;
        }

        if (S_ISDIR(entry_stat.st_mode)) {
            copy_directory(src_path, dest_path);
        } else {
            FILE *src_file = fopen(src_path, "rb");
            FILE *dest_file = fopen(dest_path, "wb");
            if (!src_file || !dest_file) {
                perror("fopen");
                log_operation("scopy", strerror(errno));
                if (src_file) fclose(src_file);
                if (dest_file) fclose(dest_file);
                continue;
            }

            char buffer[4096];
            size_t bytes;
            while ((bytes = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
                fwrite(buffer, 1, bytes, dest_file);
            }

            fclose(src_file);
            fclose(dest_file);
        }
    }

    closedir(dir);
    log_operation("scopy", "Directory copied successfully");
}

void list_directory(const char *path);

