NAME:=nm
CC:=gcc
CFLAGS:=-Wall -Wextra -Werror

mtrace.so: mtrace.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^
