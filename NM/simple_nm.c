/*
** EPITECH PROJECT, 2021
** NM
** File description:
** simple_nm
*/

#include "include/nm.h"

int simple_nm(char *file)
{
    struct stat st;
    size_t error = 0;

    if (stat(file, &st) == ERROR_RETURN) {
        error_print(file, 3);
        error = ERROR_RETURN;
    } else {
        if (parse_file(error, file, st, 0) == ERROR_RETURN) {
            error = ERROR_RETURN;
        }
    }
    return error == SUCCESS_RETURN ? SUCCESS_RETURN:ERROR_RETURN;
}