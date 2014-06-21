#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <libw.h>

int main(int argc, char *argv[])
{
    int fd = open("./readn.c", O_RDONLY);

#define SIZE 32
    char *buf = malloc(sizeof(char) * SIZE);
    buf[3] = '1';
    int n;
    while ((n = w_readn(fd, buf, SIZE)) > 0) {
        printf("%s", buf);
    }

    return 0;
}
