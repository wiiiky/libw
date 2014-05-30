#include <whashtable.h>
#include <wstring.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	WHashTable *h =
		w_hash_table_new(12, w_str_hash, w_str_equal, NULL, free);
	w_hash_table_insert(h, "hello", w_strdup("world"));
	w_hash_table_insert(h, "what", w_strdup("is it"));
	w_hash_table_insert(h, "abc", w_strdup("123"));
	w_hash_table_insert(h, "good", w_strdup("bad"));
	w_hash_table_print(h);

	printf("============================\n");

	w_hash_table_insert(h, "good", w_strdup("no!!!"));
	w_hash_table_insert(h, "abc", w_strdup("321"));
	w_hash_table_insert(h, "doyou", w_strdup("loveme"));
	w_hash_table_print(h);

	printf("============================\n");
	char *value;
	value = w_hash_table_find(h, "good");
	printf("good:%s\n", value);
	value = w_hash_table_find(h, "what");
	printf("what:%s\n", value);
	value = w_hash_table_find(h, "what!");
	printf("what!:%s\n", value);

	w_hash_table_free_full(h);
	return 0;
}
