#include <stdlib.h>
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
	int cs, top, stack;
	
	%%{
	action return { fret; }
	action call_date { fcall date; }
	action call_name { fcall name; }
	# A parser for date strings.
	date := [0-9][0-9] '/'
			[0-9][0-9] '/'
			[0-9][0-9][0-9][0-9] '\n' @return;
	# A parser for name strings.
	name := ( [a-zA-Z]+ | ' ' )** '\n' @return;
	# The main parser.
	headers =
		( 'from' | 'to' ) ':' @call_name |
		( 'departed' | 'arrived' ) ':' @call_date;
	main := headers*;
	}%%

	%%write init;
	%%write exec;

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
