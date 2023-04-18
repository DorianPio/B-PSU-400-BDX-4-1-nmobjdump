/*
** EPITECH PROJECT, 2021
** OBJDUMP
** File description:
** objdump_s
*/

#include "include/objdump.h"
#include <string.h>

static void print_me_a_space(int i, int bool)
{
    if (bool == 1) {
        for (; i % 16 != 0; i++) {
            printf(" ");
        }
        printf("\n");
    } else {
        for (; i % 16 != 0;) {
            printf(" ");
            i++;
            if (i % 4 == 0) {
                printf(" ");
            }
            if (i % 16 == 0) {
                printf(" ");
            }
        }
    }
}

static void display_hexa_value(Elf64_Shdr shdr, char *content, int i)
{
    for (; i < shdr.sh_size;) {
        printf("%02x", (unsigned char)(content + shdr.sh_offset)[i]);
        i++;
        if (i % 16 == 0) {
            printf("  ");
            break;
        }
        if (i % 4 == 0) {
            printf(" ");
        }
        if (i >= shdr.sh_size && i % 16 != 0)
            print_me_a_space(i, 0);
    }
}

static void print_above(char display)
{
    if (display >= 32 && display <= 126) {
        printf("%c", display);
    } else {
        printf(".");
    }
}

static void display_objdump_section(Elf64_Shdr shdr, char *content)
{
    int save = shdr.sh_addr;
    char display = 0;
    int i = 0;

    for (; i < shdr.sh_size;) {
        if (i % 16 == 0) {
            printf(" %04x ", save);
            save += 16;
            display_hexa_value(shdr, content, i);
        }
        display = (content + shdr.sh_offset)[i];
        print_above(display);
        i++;
        if (i % 16 == 0) {
            printf("\n");
        }
    }
    if (i >= shdr.sh_size && i % 16 != 0)
        print_me_a_space(i, 1);
}

void my_objdump_s(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, char *tmp, char *content)
{
    for (int i = 0; i < ehdr->e_shnum; i++) {
        if ((tmp + shdr[i].sh_name)[0] != '\0' &&
        strcmp(tmp + shdr[i].sh_name, ".bss") != 0 &&
        strcmp(tmp + shdr[i].sh_name, ".shstrtab") != 0 &&
        strcmp(tmp + shdr[i].sh_name, ".symtab") != 0 &&
        strcmp(tmp + shdr[i].sh_name, ".strtab") != 0) {
            printf("Contents of section %s:\n", tmp + shdr[i].sh_name);
            display_objdump_section(shdr[i], content);
        }
    }
}