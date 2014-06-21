#include <libw.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int datas[] = { 1, -5, 2, 3, 5, 7, 13, -34, 53, 66, 2, 42, -3 };
    w_quick_sort_int(datas, 13);

    int i;
    for (i = 0; i < 13; i++) {
        printf("%d\n", datas[i]);
    }

    printf("===========STRING============\n");
    char *str[] = {
        "hello",
        "world",
        "very",
        "good",
        "Z",
        "linux",
        "ubuntu",
        "well"
    };
    w_quick_sort_string(str, 8);

    for (i = 0; i < 8; i++) {
        printf("%s\n", str[i]);
    }
    return 0;
}
