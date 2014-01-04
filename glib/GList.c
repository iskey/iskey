#include "glib.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
	GList *list=NULL;
    list= g_list_append(list, "hello world");
    list= g_list_append(list, "hello iskey");
    printf("The first element in list is %s\n", g_list_first(list)->data);

    exit(0);
}