/*
** EPITECH PROJECT, 2021
** OBJDUMP
** File description:
** openfiles
*/

#include "include/objdump.h"

int open_files(char *filename, char *binary)
{
    struct stat st;
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
        return ERROR_RETURN;
    if (fstat(fd, &st) == -1)
        return ERROR_RETURN;
    if (check_error(st, fd, filename, binary) == ERROR_RETURN)
        return ERROR_RETURN;
    if (get_content(fd, filename, binary, st) == ERROR_RETURN) {
        close(fd);
        return ERROR_RETURN;
    }
    close(fd);
    return SUCCESS_RETURN;
}