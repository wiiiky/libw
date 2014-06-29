#include <libw.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    WString *string = w_string_new();
    w_string_append(string, "hello");
    w_string_append_char(string, ' ');
    w_string_append(string, "world");
    w_string_append_char(string, '\n');
    printf("%s", w_string_free(string));
    string = w_string_new_with_data("hello all!\n");
    printf("%s", w_string_free(string));
    return 0;
}
