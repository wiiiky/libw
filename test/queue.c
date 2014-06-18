#include <libwl.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    WQueue *queue = w_queue_new();

    w_queue_unref(queue);
    return 0;
}
