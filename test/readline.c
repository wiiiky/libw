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

	printf("----------------------------------------\n");
	if(w_is_fd_socket(fd)){
		printf("socket!\n");
	}else{
		printf("file!\n");
	}

	return 0;
}
