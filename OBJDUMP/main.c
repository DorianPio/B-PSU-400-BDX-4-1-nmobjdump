/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** main
*/

#include "include/objdump.h"

int main(int argc, char **argv)
{
    return check_files(argc, argv) == ERROR_RETURN ?
    ERROR_RETURN : SUCCESS_RETURN;
}
