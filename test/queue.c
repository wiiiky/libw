#include <libwl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define S(str)	strdup(str)


int main(int argc, char *argv[])
{
    WQueue *queue = w_queue_new();

    void *data = NULL;

    w_queue_push(queue, "hello");
    w_queue_push(queue, "world");
    w_queue_push(queue, "ubuntu");
    w_queue_push(queue, "fedora");

    while (w_queue_length(queue)) {
        data = w_queue_pop(queue);
        printf("%s:%u\n", (char *) data, w_queue_length(queue));
    }

    w_queue_free_full(queue, free);

    WAsyncQueue *aqueue = w_async_queue_new();
    w_async_queue_set_destroy(aqueue, free);

    w_async_queue_push(aqueue, S("I love her"));

    w_async_queue_lock(aqueue);
    w_async_queue_push_unlocked(aqueue, S("wikileaks"));
    w_async_queue_push_unlocked(aqueue, S("free software fundation"));
    w_async_queue_unlock(aqueue);

    w_async_queue_lock(aqueue);
    while (data = w_async_queue_try_pop_unlocked(aqueue)) {
        printf("%s\n", (char *) data);
    }
    w_async_queue_unlock(aqueue);

    w_async_queue_free(aqueue);
    return 0;
}
