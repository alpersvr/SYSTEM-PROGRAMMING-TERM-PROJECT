#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <sys/types.h>

void change_permissions(const char *path, mode_t mode);

#endif // PERMISSIONS_H

