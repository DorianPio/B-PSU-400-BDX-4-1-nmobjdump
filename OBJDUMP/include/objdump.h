/*
** EPITECH PROJECT, 2021
** OBJDUMP
** File description:
** objdump
*/

#include <elf.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

#define VALUE1 0x00
#define VALUE2 0x01
#define VALUE3 0x02
#define VALUE4 0x08
#define VALUE5 0x10
#define VALUE6 0x20
#define VALUE7 0x40
#define VALUE8 0x100

typedef struct all_flags {
    size_t (*func)(size_t intflags);
} all_flags_s;

int check_files(int nb_args, char **files);
int open_files(char *filename, char *binary);
int check_errors(Elf64_Ehdr *ehdr, char *filename, char *binary);
int check_error_file(Elf64_Ehdr *ehdr, char *filename, char *binary);
int check_error(struct stat st, int fd, char *filename, char *binary);
int get_content(int fd, char *filename, char *binary, struct stat st);
int error_size_of_file(struct stat st, int fd, char *filename, char *binary);
void my_objdump_s(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr,
char *tmp, char *content);
void my_objdump_f(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr,
char *filename, Elf64_Addr start);

size_t flag_syms(size_t flag);
size_t flag_exec(size_t flag);
size_t flag_paged(size_t flag);
size_t flag_reloc(size_t flag);
size_t flag_debug(size_t flag);
size_t flag_locals(size_t flag);
size_t flag_dynamic(size_t flag);
size_t flag_not_found(size_t flag);

#define WITHOUT_FLAGS 128
#define SUCCESS_RETURN 0
#define ERROR_RETURN 84

#endif /* !OBJDUMP_H_ */
