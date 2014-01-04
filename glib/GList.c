#include "glib.h"
#include "stdio.h"

void my_print(gpointer data_ptr, gpointer usr_data)
{
	g_print("%s\n", (gchar *)data_ptr);
}

int main(int argc, char *argv[])
{
	GList *list=NULL;
    list= g_list_append(list, "hello world");
    list= g_list_append(list, "hello iskey");
    printf("The first element in list is %s\n", g_list_first(list)->data);

    gint ele_num;
    ele_num= g_list_length(list);
    printf("The number of list is %d\n", ele_num);

    GList *find_list= g_list_find(list, "hello iskey");
    gint index= g_list_position(list, find_list);
    printf("The index of \"hello iskey\" is %d\n", index);

    GSList *s_list= NULL;
    s_list= g_slist_append(s_list, "hello world");
    s_list= g_slist_append(s_list, "hello iskey");
    printf("The last element in slist is %s\n", g_slist_last(s_list)->data);


    g_list_foreach(list, (GFunc)my_print, NULL);
    exit(0);
}