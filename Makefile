##
## EPITECH PROJECT, 2021
## undefined
## File description:
## Makefile
##

NAME_TEST	=	unit_tests

NAME = my_nm_objdump

NAME_nm = my_nm

NAME_OBJDUMP = my_objdump

all:	$(NAME)

$(NAME):
		make -C ./NM
		mv ./NM/my_nm ./
		make -C ./OBJDUMP
		mv ./OBJDUMP/my_objdump ./
		
objdump:
		make -C ./OBJDUMP
		mv ./OBJDUMP/my_objdump ./

nm:
		make -C ./NM
		mv ./NM/my_nm ./

clean:
		make clean -C ./NM

fclean: clean
		rm -f $(NAME_nm)
		rm -f $(NAME_OBJDUMP)

re:		fclean all
		make

.PHONY: all clean fclean re