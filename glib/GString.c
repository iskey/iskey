#include "glib.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
	GString *str=NULL;

    str= g_string_new("Hello ");
    str= g_string_append(str, "iskey ");

    g_printf("the string is %s\n", str->str);

    str= g_string_append(str, "ni ");
    str= g_string_append(str, "hao ");
    str= g_string_append(str, "world");

    gchar **str_array= g_strsplit(str->str, " ", NULL);
    gint i;
    for(i= 0; i< 100; i++)
    {
        if(str_array[i]== NULL){
            break;
        }
        else{
            printf("str_array[%d]= %s\n", i, str_array[i]);
        }
    }

    exit(0);
}