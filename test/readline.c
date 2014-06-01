#include <libwl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd = open("./hashtable.c", O_RDONLY);
	char buf[1024];
	int n;
	while ((n = w_readline(fd, buf, 1024))) {
		/*buf[n]='\0'; */
		printf("%s", buf);
		/*printf("!\n"); */
	}
	return 0;
}
