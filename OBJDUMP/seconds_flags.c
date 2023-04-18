/*
** EPITECH PROJECT, 2021
** OBJDUMP
** File description:
** seconds_flags
*/

#include "include/objdump.h"

size_t flag_locals(size_t flag)
{
    if ((flag & VALUE6) != 0) {
        printf("HAS_LOCALS");
        flag -= VALUE6;
    }
    return flag;
}

size_t flag_dynamic(size_t flag)
{
    if ((flag & VALUE7) != 0) {
        printf("DYNAMIC");
        flag -= VALUE7;
    }
    return flag;
}

size_t flag_paged(size_t flag)
{
    if ((flag & VALUE8) != 0) {
        printf("D_PAGED");
        flag -= VALUE8;
    }
    return flag;
}