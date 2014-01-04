#include "glib.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
	GList *list=NULL;
    list= g_list_append(list, "hello world");
    list= g_list_append(list, "hello iskey");
    printf("The first element in list is %s\n", g_list_first(list)->data);

    gint ele_num;
    ele_num= g_list_length(list);
    printf("The number of list is %d\n", ele_num);

    GSList *s_list= NULL;
    s_list= g_slist_append(s_list, "hello world");
    s_list= g_slist_append(s_list, "hello iskey");
    printf("The last element in slist is %s\n", g_slist_last(s_list)->data);

    exit(0);
}