/*
 * Convert a string to an integer.
 */

//#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0

%%{
	machine iskey;
	write data;
}%%

void iskey(char *str)
{
	char *p = str, *pe = str + strlen( str );
	int cs;

	%%{
		action hello {
			printf("Hello world\n");
		}
		
		action hello2 {
			printf("Hello world2\n");
		}
		
		action hello3{
			printf("Hello world3\n");
		}

		main := 
			(([k][e][y]@hello)+ | ([abs]*$hello2)) "\n" @hello3;

		# Initialize and execute.
		write init;
		write exec;
	}%%

};


#define BUFSIZE 1024

int main()
{
	char buf[BUFSIZE];
	while ( fgets( buf, sizeof(buf), stdin ) != 0 ) {
		iskey(buf);
	}	
	return 0;
}
