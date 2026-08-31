NAME:=nm
CC:=clang
CFLAGS:=-Wall -Wextra -Werror -g
SRC:=parse.c main.c elf32.c elf64.c
OBJ:=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

i686-sample:
	gcc -m32 -Wall -Wextra read.mmap.c -o sample.i686
