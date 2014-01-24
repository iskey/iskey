/*
* to parse a string started with “table” or “div”
*/

//#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0

%%{
                #状态机的名字(必须有一个名字而且必须符合命名规则,和变通的变量声明一样)
        machine par_str;
        write data;
}%%
//函数声明,用于在用户自定义行为中调用,用到了参数的传递,此函数也可以是类成员函数
void printtable(int len)
{
   printf("there is a table,length is:%d\n",len);
}

//另外一个函数,功能同上,只是参数传递用的是引用传递
void printdiv(char *p)
{
  printf("hello %s\n",(*p));
}
//主处理函数
void par_str( char *str,int len )
{
        char *p = str, *pe = str + strlen( str );
        int cs;        //状态机关键字,用于说明当明状态,以整型值标识(current status的缩写)
                //状态机自定义行为块
        %%{
                        #调用自定义函数
                        action see_table {
                                 printtable(len);
                }
               #invoke prindiv function to show the table information, as same as above
               action see_div {
                                  printdiv(p);
               }
               #正则表达式声明,用于在状态机初始化时,按照此规则匹配目标
               main :=
                                ([t][a][b][l][e]@see_table)([d][i][v]@see_div)+'E';
               # 初始化
               write init;
               write exec;
        }%%

                if ( cs < par_str_first_final )
                fprintf( stderr, "par_str: there was an error\n" );
};

#define BUFSIZE 1024
//主函数,用于测试生成的状态机
int main()
{
        char buf[BUFSIZE];
        while ( fgets( buf, sizeof(buf), stdin ) != 0 )
{
par_str(buf,10);
}
                return 0;
}