#include "../inc/libmx.h"

char *mx_file_to_str(const char *filename) {
    char temp;
    char *result;
    int count = 0;
    int fd = open (filename, O_RDONLY);
    if (fd == -1) 
        return NULL;
    while (read(fd, &temp, 1) > 0) 
        count++;
    result = mx_strnew(count);
    fd = open (filename, O_RDONLY);
    if (fd == -1) 
        return NULL;
    for (int i = 0; read (fd, &temp, 1) > 0; i++) 
        result[i] = temp;
    if (close (fd) != 0) 
        return NULL;
    close (fd);
    return result;
}

