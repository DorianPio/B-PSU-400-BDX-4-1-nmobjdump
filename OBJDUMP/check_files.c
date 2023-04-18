/*
** EPITECH PROJECT, 2021
** OBJDUMP
** File description:
** check_files
*/

#include "include/objdump.h"

int check_error_file(Elf64_Ehdr *ehdr, char *filename, char *binary)
{
    if (check_errors(ehdr, filename, binary) == ERROR_RETURN)
        return ERROR_RETURN;
    if (ehdr->e_ident[EI_CLASS] != ELFCLASS64)
        return ERROR_RETURN;
    return SUCCESS_RETURN;
}

int check_files(int nb_args, char **files)
{
    if (nb_args < 2) {
        if (open_files("a.out", files[0]) == ERROR_RETURN) {
            printf("objdump: 'a.out': No such file\n");
            return ERROR_RETURN;
        }
    } else {
        for (int i = 1; i < nb_args; i++) {
            if (open_files(files[i], files[0]) == ERROR_RETURN) {
                printf("objdump: '%s': No such file\n", files[i]);
            }
        }
    }
    return SUCCESS_RETURN;
}