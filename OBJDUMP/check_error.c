/*
** EPITECH PROJECT, 2021
** OBJDUMP
** File description:
** check_error
*/

#include "include/objdump.h"

int error_size_of_file(struct stat st, int fd, char *filename, char *binary)
{
    Elf64_Ehdr elf;
    int size = 0;

    if (read(fd, &elf, sizeof(elf)) == -1)
        return ERROR_RETURN;
    size = elf.e_shoff + elf.e_shentsize * elf.e_shnum;
    if (size != st.st_size) {
        printf("objdump: %s: File truncated\n", filename);
        return ERROR_RETURN;
    }
    return SUCCESS_RETURN;
}

static int check_identity(const char *identity)
{
    if (sizeof(identity) == 8 &&
    identity[EI_MAG0] == ELFMAG0 && identity[EI_MAG1] == ELFMAG1
    && identity[EI_MAG2] == ELFMAG2 && identity[EI_MAG3] == ELFMAG3
    && identity[EI_CLASS] == ELFCLASS64
    && identity[EI_DATA] != ELFDATANONE
    && identity[EI_VERSION] == EV_CURRENT)
        return SUCCESS_RETURN;
    return ERROR_RETURN;
}

int check_errors(Elf64_Ehdr *ehdr, char *filename, char *binary)
{
    if (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_REL &&
    ehdr->e_type != ET_DYN || check_identity(ehdr->e_ident) == ERROR_RETURN) {
        printf("objdump: %s: File format not recognized\n", filename);
        return ERROR_RETURN;
    }
    return SUCCESS_RETURN;
}

int check_error(struct stat st, int fd, char *filename, char *binary)
{
    if (!S_ISREG(st.st_mode)) {
        printf("objdump: %s: File format not recognized\n", filename);
        close(fd);
        return ERROR_RETURN;
    }
    return SUCCESS_RETURN;
}