/*
** EPITECH PROJECT, 2021
** NM
** File description:
** sorting_and_comparing
*/

#include "include/nm.h"

char *my_remove(char *buffer)
{
    char *tmp = malloc(sizeof(char) * strlen(buffer) + 1);
    int f = 0;

    if (!tmp)
        return NULL;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if ((buffer[i] >= '0' && buffer[i] <= '9') ||
        (buffer[i] >= 'a' && buffer[i] <= 'z') ||
        (buffer[i] >= 'A' && buffer[i] <= 'Z')) {
            tmp[f] = buffer[i];
            f++;
        }
    }
    tmp[f] = '\0';
    return tmp;
}

info_t *my_cmp(info_t *info, Elf64_Sym *sort, int i, int f)
{
    if (strcasecmp(my_remove(&info->strtab[info->buffer_sym[i]->st_name]),
    my_remove(&info->strtab[info->buffer_sym[f]->st_name]))
    == SUCCESS_RETURN) {
        if (ELF64_ST_BIND(info->buffer_sym[i]->st_info) != STB_LOCAL) {
            sort = info->buffer_sym[f];
            info->buffer_sym[f] = info->buffer_sym[i];
            info->buffer_sym[i] = sort;
        }
    }
    else if (strcasecmp(my_remove(&info->strtab[info->buffer_sym[i]->st_name]),
    my_remove(&info->strtab[info->buffer_sym[f]->st_name])) > SUCCESS_RETURN) {
        sort = info->buffer_sym[f];
        info->buffer_sym[f] = info->buffer_sym[i];
        info->buffer_sym[i] = sort;
    }
    return info;
}