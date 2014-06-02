#include <libwl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	/*int fd = open("/var/log/syslog.1", O_RDONLY);*/
	int fd = open("./hashtable.c", O_RDONLY);
	char buf[1024];
	int n;
	int l=0;
	while ((n = w_readline(fd, buf, 1024))>0) {
		/*buf[n]='\0'; */
		printf("%s", buf);
		if(++l==10)
		   break;
		/*printf("!\n"); */
	}

	while((n=w_readline_buffer(buf,1024))>0){
		printf("%s",buf);
	}
	while ((n = w_readline(fd, buf, 1024))>0) {
		/*buf[n]='\0'; */
		printf("%s", buf);
		if(++l==10)
		   break;
		/*printf("!\n"); */
	}


	return 0;
}
