/*
** EPITECH PROJECT, 2021
** NM
** File description:
** print_error
*/

#include "include/nm.h"

void error_print(char *file, int error)
{
    if (error == DIRECTORY_ERROR)
        printf("nm: Warning: '%s' is a directory\n", file);
    if (error == BINARY_ERROR)
        printf("nm: %s: File format not recognized\n", file);
    if (error == NO_FILE_ERROR)
        printf("nm: '%s': No such file\n", file);
}

static void print_header(info_t *info, int i)
{
    if (strcmp(&info->strtab[info->buffer_sym[i]->st_name], "_DYNAMIC") == 0)
        info->letter = 'd';
    if (strcmp(&info->strtab[info->buffer_sym[i]->st_name],
    "__init_array_end") == 0)
        info->letter = 't';
    if (strcmp(&info->strtab[info->buffer_sym[i]->st_name],
    "__init_array_start") == 0)
        info->letter = 't';
}

static void other_print(info_t *info, int i)
{
    long unsigned int test1 = SHF_ALLOC + SHF_EXECINSTR;
    long unsigned int test2 = SHF_ALLOC + SHF_WRITE;
    long unsigned int test3 = SHF_ALLOC;

    if (info->buffer_sec[info->buffer_sym[i]->st_shndx]->sh_flags == test1)
        info->letter = 't';
    if (info->buffer_sec[info->buffer_sym[i]->st_shndx]->sh_flags == test2)
        info->letter = 'd';
    if (info->buffer_sec[info->buffer_sym[i]->st_shndx]->sh_flags == test3)
        info->letter = 'r';
}

static void print_sys(info_t *info, int i)
{
    if (info->buffer_sym[i]->st_value == 0)
        info->letter = 'U';
    if (info->buffer_sym[i]->st_shndx > info->buffer_bin->e_shnum)
        return;
    if (info->buffer_sec[info->buffer_sym[i]->st_shndx]->sh_type == SHT_NOBITS
    && info->buffer_sec[info->buffer_sym[i]->st_shndx]->sh_flags == SHF_ALLOC
    + SHF_WRITE)
        info->letter = 'b';
    if (info->buffer_sec[info->buffer_sym[i]->st_shndx]->sh_type ==
    SHT_PROGBITS)
        other_print(info, i);
    if (ELF64_ST_BIND(info->buffer_sym[i]->st_info) == STB_GLOBAL &&
    info->letter != 'U')
        info->letter -= 32;
    print_header(info, i);
    last_print(info, i);
}

int print_info(info_t *info)
{
    for (int i = 0; info->buffer_sym[i] != NULL; i++) {
        if (strcmp(&info->strtab[info->buffer_sym[i]->st_name], "") != 0) {
            print_sys(info, i);
            if (ELF64_ST_TYPE(info->buffer_sym[i]->st_info) != STT_FILE) {
                if (info->buffer_sym[i]->st_value == 0 && (info->letter == 'U'
                || info->letter == 'u' || info->letter == 'w'))
                    printf("                 ");
                else
                    printf("%016lx ", info->buffer_sym[i]->st_value);
                printf("%c ", info->letter);
                printf("%s\n", &info->strtab[info->buffer_sym[i]->st_name]);
            }
        }
    }
    return SUCCESS_RETURN;
}