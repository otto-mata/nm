NAME:=nm
CC:=clang
CFLAGS:=-Wall -Wextra -Werror
SRC:=parse.c main.c
OBJ:=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

mtrace.so: mtrace.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^
