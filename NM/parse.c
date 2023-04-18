/*
** EPITECH PROJECT, 2021
** NM
** File description:
** parse
*/

#include "include/nm.h"

void last_print(info_t *info, int i)
{
    if (ELF64_ST_BIND(info->buffer_sym[i]->st_info) == STB_WEAK &&
    info->buffer_sym[i]->st_value != SUCCESS_RETURN)
        info->letter = 'W';
    else if (ELF64_ST_BIND(info->buffer_sym[i]->st_info) == STB_WEAK &&
    info->buffer_sym[i]->st_value == SUCCESS_RETURN)
        info->letter = 'w';
}

static int get_all_info(info_t *in)
{
    Elf64_Shdr *tmp = NULL;
    int reader = 0;

    in->buffer_sec = malloc(sizeof(Elf64_Shdr *) * in->buffer_bin->e_shnum);
    for (int i = 0; i < in->buffer_bin->e_shnum; i++) {
        in->buffer_sec[i] = malloc(sizeof(Elf64_Shdr));
        if (!in->buffer_sec[i])
            return ERROR_RETURN;
        in->buffer_sec[i] = memcpy(in->buffer_sec[i],
        &in->buffer[in->buffer_bin->e_shoff + (i *
        in->buffer_bin->e_shentsize)], in->buffer_bin->e_shentsize);
    }
    tmp = in->buffer_sec[in->buffer_bin->e_shstrndx];
    in->shstrtab = malloc(sizeof(char) * tmp->sh_size);
    if (!in->shstrtab)
        return ERROR_RETURN;
    in->shstrtab = memcpy(in->shstrtab, &in->buffer[tmp->sh_offset],
    tmp->sh_size);
    return get_info_of_buff(in, reader) == ERROR_RETURN ? 84 : 0;
}

static int check_elf(char *buffer)
{
    if (buffer[0] != ELFMAG0 || buffer[1] != ELFMAG1 ||
    buffer[2] != ELFMAG2 || buffer[3] != ELFMAG3 ||
    buffer[4] == ELFCLASSNONE) {
        return ERROR_RETURN;
    }
    return SUCCESS_RETURN;
}

static int parse_elf(struct stat buffer, int fd, char *file, int nb_args)
{
    info_t *info = malloc(sizeof(info_t));

    if (nb_args > 2)
        printf("\n%s:\n", file);
    if (!info)
        return ERROR_RETURN;
    info->buffer = malloc(sizeof(char) * buffer.st_size);
    if (!info->buffer)
        return ERROR_RETURN;
    if (read(fd, info->buffer, buffer.st_size) == -1)
        return ERROR_RETURN;
    info->buffer_bin = malloc(sizeof(Elf64_Ehdr) * buffer.st_size);
    if (!info->buffer_bin)
        return ERROR_RETURN;
    info->buffer_bin = memcpy(info->buffer_bin, info->buffer, buffer.st_size);
    if (check_elf(info->buffer) == ERROR_RETURN) {
        error_print(file, BINARY_ERROR);
        return ERROR_RETURN;
    }
    return get_all_info(info);
}

int parse_file(int error, char *file, struct stat buffer, int nb_arg)
{
    int fd = open(file, O_RDONLY);

    if (error == 84)
        return error;
    if (fd == -1) {
        error_print(file, NO_FILE_ERROR);
        error = ERROR_RETURN;
    }
    if (parse_elf(buffer, fd, file, nb_arg) == ERROR_RETURN)
        return ERROR_RETURN;
    return SUCCESS_RETURN;
}