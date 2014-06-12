#include <libwl.h>
#include <stdio.h>

static int compare1(const void *a, const void *b)
{
    int A = (int) (long) a;
    int B = (int) (long) b;
    return A - B;
}

static int compare2(const void *a, const void *b)
{
    int A = (int) (long) a;
    int B = (int) (long) b;
    return B - A;
}

int main(int argc, char *argv[])
{
    WList *list = w_list_new();
    list = w_list_append(list, (void *) (long) 3);
    list = w_list_append(list, (void *) (long) 2);
    list = w_list_append(list, (void *) (long) 1);
    list = w_list_append(list, (void *) (long) 4);
    list = w_list_append(list, (void *) (long) 6);
    list = w_list_append(list, (void *) (long) 5);
    list = w_list_append(list, (void *) (long) -5);
    list = w_list_append(list, (void *) (long) 5);
    list = w_list_append(list, (void *) (long) 1);
    list = w_list_append(list, (void *) (long) 7);
    list = w_list_append(list, (void *) (long) 7);

    WList *ptr = list;
    while (ptr) {
        printf("%d\n", (int) (long) w_list_data(ptr));
        ptr = w_list_next(ptr);
    }

    printf("==============sort by bubble sort==================\n");

    list = w_list_sort_bubble(list, compare1);
    ptr = list;
    while (ptr) {
        printf("%d\n", (int) (long) w_list_data(ptr));
        ptr = w_list_next(ptr);
    }

    printf("==============sort by insertion sort==================\n");

    list = w_list_sort(list, compare2);
    ptr = list;
    while (ptr) {
        printf("%d\n", (int) (long) w_list_data(ptr));
        ptr = w_list_next(ptr);
    }

    w_list_free(list);

    list = w_list_new();
    list = w_list_insert_sorted(list, (void *) (long) 3, compare1);
    list = w_list_insert_sorted(list, (void *) (long) 2, compare1);
    list = w_list_insert_sorted(list, (void *) (long) 4, compare1);
    list = w_list_insert_sorted(list, (void *) (long) -1, compare1);
    list = w_list_insert_sorted(list, (void *) (long) 123, compare1);
    list = w_list_insert_sorted(list, (void *) (long) -10, compare1);
    list = w_list_insert_sorted(list, (void *) (long) -1, compare1);
    list = w_list_insert_sorted(list, (void *) (long) 3, compare1);
    list = w_list_insert_sorted(list, (void *) (long) 6, compare1);
    list = w_list_insert_sorted(list, (void *) (long) 0, compare1);
    list = w_list_insert_sorted(list, (void *) (long) 4, compare1);
    list = w_list_insert_sorted(list, (void *) (long) 7, compare1);

    printf("==============sort inserting ==================\n");
    ptr = list;
    while (ptr) {
        printf("%d\n", (int) (long) w_list_data(ptr));
        ptr = w_list_next(ptr);
    }
    w_list_free(list);
    return 0;
}
