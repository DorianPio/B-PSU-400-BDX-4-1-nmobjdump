/*
** EPITECH PROJECT, 2021
** OBJDUMP
** File description:
** first_flags
*/

#include "include/objdump.h"

size_t flag_not_found(size_t flag)
{
    if ((flag & VALUE1) != 0) {
        printf("NO_FLAGS");
        flag -= VALUE1;
    }
    return flag;
}

size_t flag_reloc(size_t flag)
{
    if ((flag & VALUE2) != 0) {
        printf("HAS_RELOC");
        flag -= VALUE2;
    }
    return flag;
}

size_t flag_exec(size_t flag)
{
    if ((flag & VALUE3) != 0) {
        printf("EXEC_P");
        flag -= VALUE3;
    }
    return flag;
}

size_t flag_debug(size_t flag)
{
    if ((flag & VALUE4) != 0) {
        printf("HAS_DEBUG");
        flag -= VALUE4;
    }
    return flag;
}

size_t flag_syms(size_t flag)
{
    if ((flag & VALUE5) != 0) {
        printf("HAS_SYMS");
        flag -= VALUE5;
    }
    return flag;
}
