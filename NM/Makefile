##
## EPITECH PROJECT, 2021
## NM
## File description:
## Makefile
##


SRC_NM =	main.c 					\
			parse.c					\
			print.c					\
			simple_nm.c				\
			sorting_and_comparing.c	\
			info_and_sorting.c		\

OBJ_NM = $(SRC_NM:.c=.o)

CFLAGS = -std=gnu11 -Wall -Wextra -I./include

NAME	=	my_nm

all:	$(NAME)

$(NAME):	$(OBJ_NM)
		gcc -g -c -Wall -Werror -g3 $(SRC_NM)
		gcc -o $(NAME) $(OBJ_NM)


clean:
		rm -f $(OBJ_NM)

fclean: clean
		rm -f my_nm

re:		fclean all
		make

.PHONY: all clean fclean re