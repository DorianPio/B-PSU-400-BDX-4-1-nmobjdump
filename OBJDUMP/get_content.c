/*
** EPITECH PROJECT, 2021
** OBJDUMP
** File description:
** get_content
*/

#include "include/objdump.h"
#include <string.h>

static Elf64_Addr get_start(Elf64_Shdr *shdr, Elf64_Ehdr *ehdr, char *tmp)
{
    for (int i = 0; i < ehdr->e_shnum; i++) {
        if (strcmp(tmp + shdr[i].sh_name, ".text") == 0) {
            return shdr[i].sh_addr;
        }
    }
    return SUCCESS_RETURN;
}

int get_content(int fd, char *filename, char *binary, struct stat st)
{
    void *content = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)content;
    Elf64_Shdr *shdr = (Elf64_Shdr *)(content + ehdr->e_shoff);
    char *tmp = content + shdr[ehdr->e_shstrndx].sh_offset;

    if (content == (void *)(-1))
        return ERROR_RETURN;
    if (check_error_file(ehdr, filename, binary) == ERROR_RETURN)
        return ERROR_RETURN;
    if (error_size_of_file(st, fd, filename, binary) == ERROR_RETURN)
        return ERROR_RETURN;
    my_objdump_f(ehdr, shdr, filename, get_start(shdr, ehdr, tmp));
    my_objdump_s(ehdr, shdr, tmp, content);
    if (munmap(content, st.st_size) == -1)
        return ERROR_RETURN;
    return SUCCESS_RETURN;
}