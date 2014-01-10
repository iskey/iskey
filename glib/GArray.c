#include "glib.h"
#include "stdio.h"

void prt(GArray* a) {
	int i;
	printf("Array holds: ");
	for (i = 0; i < a->len; i++)
	printf("%d ", g_array_index(a, int, i));
	printf("\n");
}

void byte_prt(GByteArray* a) {
	int i;
	printf("Array holds: ");
	for (i = 0; i < a->len; i++)
	printf("%d ", g_array_index(a, guint8, i));
	printf("\n");
}

int compare_ints(gpointer a, gpointer b)
{
	int* x= (int*)a;
	int* y= (int*)b;
	return *x - *y;
}

int main(int argc, char* argv[])
{
	GArray *array= NULL;

	array= g_array_new(FALSE, TRUE, sizeof(int));

	gint len= 0;
	gint i, j;
	for(i= 0; i< 15; i++){
		j= i+ 15;
		g_array_append_val(array, i);
		g_array_append_vals(array, &j, 1);
	}

	prt(array);
	g_array_sort(array, (GCompareFunc)compare_ints);
	prt(array);

	/* GByteArray samples */
	GByteArray *byte_array;
	byte_array= g_byte_array_new();
	guint8 x= 0xff;
	g_byte_array_append(byte_array, &x, sizeof(x));
	x= 0x01;
	g_byte_array_append(byte_array, &x, sizeof(x));
	guint8 tx[10]={0,1,2,3,4,5,6,7,8,9};
	g_byte_array_append(byte_array, tx, 10);
	printf("the sizeof Byte Array is %d\n", byte_array->len);
	byte_prt(byte_array);
}