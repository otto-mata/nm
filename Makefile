NAME:=nm
CC:=clang
CFLAGS:=-Wall -Wextra -Werror
SRC:=parse.c main.c
OBJ:=$(SRC:.c=.o)

MT_SRC := mtrace.main.c
MT_OBJ := $(MT_SRC:.c=.o)
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

mtrace.so: mtrace.lib.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^

mtrace-bin: $(MT_OBJ)
	$(CC) $(CFLAGS) -o mtrace $^

mtrace: mtrace.so mtrace-bin