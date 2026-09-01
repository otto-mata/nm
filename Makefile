NAME:=nm
CC:=clang
CFLAGS:=-Wall -Wextra -Werror -g 
SRC:=parse.c main.c elf32.c elf64.c elfxx.c archive.c
OBJ:=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
