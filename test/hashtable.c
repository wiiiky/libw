#include <libw.h>
#include <stdio.h>
#include <stdlib.h>

int node_func(void *key, void *value, void *user_data)
{
    printf("%d:%d\n", (int) (long) key, (int) (long) value);
}

int main(int argc, char *argv[])
{
    WHashTable *h =
        w_hash_table_new(12, w_str_hash, w_str_equal, NULL, free);
    w_hash_table_insert(h, "hello", w_strdup("world"));
    w_hash_table_insert(h, "what", w_strdup("is it"));
    w_hash_table_insert(h, "abc", w_strdup("123"));
    w_hash_table_insert(h, "good", w_strdup("bad"));

    printf("============================\n");

    w_hash_table_insert(h, "good", w_strdup("no!!!"));
    w_hash_table_insert(h, "abc", w_strdup("321"));
    w_hash_table_insert(h, "doyou", w_strdup("loveme"));

    printf("============================\n");
    char *value;
    value = w_hash_table_find(h, "good");
    printf("good:%s\n", value);
    value = w_hash_table_find(h, "what");
    printf("what:%s\n", value);
    value = w_hash_table_find(h, "what!");
    printf("what!:%s\n", value);
    printf("===============================\n");

    w_hash_table_remove_full(h, "good");
    w_hash_table_free_full(h);

    h = w_hash_table_new(4, w_int_hash, w_int_equal, NULL, NULL);
    w_hash_table_insert(h, (void *) (long) 123, (void *) (long) 234);
    w_hash_table_insert(h, (void *) (long) 234, (void *) (long) 456);
    w_hash_table_insert(h, (void *) (long) 123, (void *) (long) 1234567);
    w_hash_table_remove(h, (void *) (long) 234);
    w_hash_table_foreach(h, node_func, NULL);
    printf("\n");

    h = w_hash_table_new(2, w_str_hash, w_str_equal, NULL, NULL);
    w_hash_table_insert(h, "linux", "what?");
    w_hash_table_insert(h, "link", "C");
    w_hash_table_insert(h, "well", "done");
    w_hash_table_insert(h, "link", "CCCC");
    w_hash_table_insert(h, "very", "GOOD");
    w_hash_table_remove(h, "linux");
    WList *keys = w_hash_table_get_keys(h);
    printf("\n");
    while (keys) {
        value = w_hash_table_find(h, keys->data);
        printf("%s:%s\n", (char *) keys->data, value);
        keys = w_list_next(keys);
    }
    w_hash_table_free_full(h);

    return 0;
}
