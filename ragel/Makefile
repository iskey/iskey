CC= gcc

all:atoi params

atoi: atoi.o
	$(CC) -o $@ $<
	
#atoi.c:atoi.rl
#	ragel -L $<	
	
params:params.o
	$(CC) -o $@ $<

%.c:%.rl
	ragel -L $<	
	
%.o:%.c
	$(CC) -c -o $@ $<


.PHONY : clean
clean:
	@rm -fvr *.c
	@rm -fvr *.o
	@rm -fvr atoi
	@rm -fvr params