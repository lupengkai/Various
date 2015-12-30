#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/ioctl.h>

#define  RWBUF_CLEAR   0x909090 

int main() {
int h = open("/dev/rwbuf", O_RDWR);
int n =ioctl(h, RWBUF_CLEAR, 0);
close(h);
char a[1];
a[0]=' ';
int fd = open("/dev/rwbuf", O_WRONLY);
	write (fd, a, 1);
	close(fd);
}
