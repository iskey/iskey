#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0

char comm_buf[300]= {0};

void buffer(char cc)
{
	static flag= 0;
	comm_buf[flag++]= cc;
	printf("%c ", cc);
}

void iskey(char *str)
{
	char *p = str, *pe = str + strlen( str );
	char *eof= pe;
	int cs;
	
	%%{
	machine iskey;
	
	action comm{
		buffer(*fpc);
	}
	action hello{
		printf("comment is %s\n", comm_buf);
	}
	
	action hello1{
		printf("start 1");
	}
	action hello2{
		printf("start 2");
		fbreak;
	}
	action hello3{
		printf("start 3\n");
	}
	action hello4{
		printf("start 4");
	}
	action hello5{
		printf("start 5");
	}
	
	comment= ('he'@hello1 :>> any* 'llo') @hello2;
	comment1= ('he'@hello1 :> any* 'llo') @hello2;
	comment2= ('he'@hello1 any* 'llo') @hello2;
	
	comment3= 'he'@hello1 :> (any* 'llo')>hello2;
	comment4= 'he'@hello1 (any* 'llo')%hello2;
	main= comment4 ' ';
	
	write data;
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


//dot -Tpng out.dot -o out.png

//test1
//	comment= ('/*' any @comm)* '*/';
//	comment1= '/*' ((any @comm)* - (any* '*/' any*)) '*/';
//	commnet2= '/*' (any @comm)* :>> '*/';
//	main= (comment)>hello1 >hello @hello2 $hello3 $hello %hello4;