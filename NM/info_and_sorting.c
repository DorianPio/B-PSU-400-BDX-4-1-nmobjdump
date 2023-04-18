/*
** EPITECH PROJECT, 2021
** NM
** File description:
** info_and_sorting
*/

#include "include/nm.h"

static info_t *sorting(info_t *info)
{
    Elf64_Sym *sort = NULL;
    int find = 0;

    for (; info->buffer_sym[find]; find++);
    for (int i = 0; i < find; i++) {
        for (int f = i + 1; f < find; f++) {
            info = my_cmp(info, sort, i, f);
        }
    }
    return info;
}

static int get_str_info(info_t *info, int reader)
{
    for (reader = 0; info->buffer_sec[reader]; reader++) {
        if (strcmp(&info->shstrtab[info->buffer_sec[reader]->sh_name],
        ".strtab") == 0)
            break;
    }
    info->strtab = malloc(sizeof(char) * info->buffer_sec[reader]->sh_size);
    if (!info->strtab)
        return ERROR_RETURN;
    info->strtab = memcpy(info->strtab, &info->buffer[info->buffer_sec[reader]
    ->sh_offset], info->buffer_sec[reader]->sh_size);
    info = sorting(info);
    if (print_info(info) == ERROR_RETURN)
        return ERROR_RETURN;
    return SUCCESS_RETURN;
}

static info_t *copy_system(info_t *info, int reader, int i)
{
    info->buffer_sym[i] = malloc(sizeof(Elf64_Sym));
    if (!info->buffer_sym[i])
        return NULL;
    info->buffer_sym[i] = memcpy(info->buffer_sym[i], &info->buffer[info->
    buffer_sec[reader]->sh_offset + (i * info->buffer_sec[reader]->
    sh_entsize)], info->buffer_sec[reader]->sh_entsize);
    return info;
}

int get_info_of_buff(info_t *info, int reader)
{
    for (; info->buffer_sec[reader]; reader++) {
        if (strcmp(&info->shstrtab[info->buffer_sec[reader]->sh_name],
        ".symtab") == SUCCESS_RETURN)
            break;
    }
    info->buffer_sym = malloc(sizeof(Elf64_Sym *) *
    ((info->buffer_sec[reader]->sh_size /info->buffer_sec[reader]->sh_entsize)
    + 1));
    info->buffer_sym[(info->buffer_sec[reader]->sh_size /
    info->buffer_sec[reader]->sh_entsize)] = NULL;
    for (size_t i = 0; i < (info->buffer_sec[reader]->sh_size /
    info->buffer_sec[reader]->sh_entsize); i++) {
        info = copy_system(info, reader, i);
    }
    if (get_str_info(info, reader) == ERROR_RETURN)
        return ERROR_RETURN;
    return SUCCESS_RETURN;
}