/*
** EPITECH PROJECT, 2021
** NM
** File description:
** main
*/

#include "include/nm.h"

static int nm_system(int nb_args, char **arg)
{
    struct stat st;
    int end = 0;

    for (int i = 0; i < nb_args; i++) {
        if (stat(arg[i], &st) == ERROR_FILE) {
            error_print(arg[i], NO_FILE_ERROR);
            end = 84;
        }
        if (S_ISDIR(st.st_mode) == 1) {
            error_print(arg[i], DIRECTORY_ERROR);
            end = 84;
        }
        if (parse_file(end, arg[i], st, nb_args) == ERROR_RETURN)
            end = 84;
    }
    return end == ERROR_RETURN ? ERROR_RETURN : SUCCESS_RETURN;
}

static int my_nm(int nb_args, char **arg)
{
    if (nb_args == 1) {
        if (simple_nm("a.out") == ERROR_RETURN) {
            return ERROR_RETURN;
        }
    } else if (arg[1][0] == '-') {
        return SUCCESS_RETURN;
    } else {
        if (nm_system(nb_args, arg) == ERROR_RETURN) {
            return ERROR_RETURN;
        }
    }
    return SUCCESS_RETURN;
}

int main(int argc, char **argv)
{
    if (my_nm(argc, argv) == ERROR_RETURN) {
        return ERROR_RETURN;
    }
    return 0;
}
