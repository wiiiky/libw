#include <libwl.h>
#include <stdio.h>


static int compare(const void *a,const void *b)
{
	int A=(int)(long)a;
	int B=(int)(long)b;
	return B-A;
}

int main(int argc, char *argv[])
{
	WList *list=w_list_new();
	list=w_list_append(list,(void*)(long)3);
	list=w_list_append(list,(void*)(long)2);
	list=w_list_append(list,(void*)(long)1);
	list=w_list_append(list,(void*)(long)4);
	list=w_list_append(list,(void*)(long)6);
	list=w_list_append(list,(void*)(long)5);
	list=w_list_append(list,(void*)(long)-5);
	list=w_list_append(list,(void*)(long)5);
	list=w_list_append(list,(void*)(long)1);
	list=w_list_append(list,(void*)(long)7);
	list=w_list_append(list,(void*)(long)7);

	WList *ptr=list;
	while(ptr){
		printf("%d\n",(int)(long)w_list_data(ptr));
		ptr=w_list_next(ptr);
	}
	list=w_list_sort_bubble(list,compare);

	printf("===================================\n");

	ptr=list;
	while(ptr){
		printf("%d\n",(int)(long)w_list_data(ptr));
		ptr=w_list_next(ptr);
	}

	w_list_free(list);
	return 0;
}
