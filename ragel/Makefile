CC= gcc

all: atoi.o
	$(CC) -o atoi $<

%.o:%.c
	$(CC) -c -o $@ $<

atoi.c:atoi.rl
	ragel -L $<
