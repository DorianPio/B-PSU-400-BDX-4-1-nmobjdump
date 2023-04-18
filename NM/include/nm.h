/*
** EPITECH PROJECT, 2021
** NM
** File description:
** nm
*/

#ifndef NM_H_
#define NM_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define DIRECTORY_ERROR 1
#define BINARY_ERROR 2
#define NO_FILE_ERROR 3
#define ERROR_FILE -1
#define ERROR_RETURN 84
#define SUCCESS_RETURN 0

typedef struct info_s {
    char *buffer;
    char *shstrtab;
    char *strtab;
    char letter;
    Elf64_Ehdr *buffer_bin;
    Elf64_Sym **buffer_sym;
    Elf64_Shdr **buffer_sec;
} info_t;

int simple_nm(char *file);
int print_info(info_t *info);
void last_print(info_t *info, int i);
void error_print(char *file, int error);
int get_info_of_buff(info_t *info, int reader);
info_t *my_cmp(info_t *info, Elf64_Sym *sort, int i, int f);
int parse_file(int error, char *file, struct stat buffer, int nb_arg);

#endif /* !NM_H_ */
