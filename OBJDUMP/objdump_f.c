/*
** EPITECH PROJECT, 2021
** OBJDUMP
** File description:
** objdump_f
*/

#include "include/objdump.h"

all_flags_s flag_info[8] =
{
    {&flag_not_found},
    {&flag_reloc},
    {&flag_exec},
    {&flag_debug},
    {&flag_syms},
    {&flag_locals},
    {&flag_dynamic},
    {&flag_paged}
};

static int get_flags_by_section_in_file(Elf64_Shdr *shdr, Elf64_Ehdr *ehdr,
int result)
{
    for (int i = 0; i < ehdr->e_shnum; i++) {
        if (shdr[i].sh_type == SHT_SYMTAB) {
            result += 0x10;
        }
    }
    return result;
}

static int get_flags(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr)
{
    int result = 0;

    if (ehdr->e_type == ET_EXEC)
        result += 0x02 + 0x100;
    else if (ehdr->e_type == ET_DYN)
        result += 0x100 + 0x40;
    else if (ehdr->e_type == ET_REL)
        result += 0x01;
    result = get_flags_by_section_in_file(shdr, ehdr, result);
}

static void display_info_of_flags(int flags)
{
    int tmp = 0;

    for (int i = 0; i < 8; i++) {
        tmp = flags;
        flags = flag_info[i].func(flags);
        if (i != 0 && flags != 0 && flags != tmp)
            printf(", ");
    }
    printf("\n");
}

void my_objdump_f(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr,
char *filename, Elf64_Addr start)
{
    int have_flags = get_flags(ehdr, shdr);

    printf("\n%s:     file format elf64-x86-64\n", filename);
    printf("architecture: i386:x86-64, flags %010p:\n", have_flags);
    display_info_of_flags(have_flags);
    if (start != 0) {
        printf("start address %018p\n\n", start);
    } else {
        printf("start adress 0x0000000000000000\n\n");
    }
}