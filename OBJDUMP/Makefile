##
## EPITECH PROJECT, 2021
## NM
## File description:
## Makefile
##


SRC_OBJ =	main.c 				\
			check_error.c		\
			check_files.c		\
			first_flags.c		\
			get_content.c		\
			objdump_f.c			\
			objdump_s.c			\
			openfiles.c			\
			seconds_flags.c		\

OBJ_OBJ = $(SRC_OBJ:.c=.o)

CFLAGS = -I./include

NAME	=	my_objdump

all:	$(NAME)

$(NAME):	$(OBJ_OBJ)
		gcc $(SRC_OBJ)
		gcc -o $(NAME) $(OBJ_OBJ)


clean:
		rm -f $(OBJ_OBJ)

fclean: clean
		rm -f my_objdump

re:		fclean all
		make

.PHONY: all clean fclean re