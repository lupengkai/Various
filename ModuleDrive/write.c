#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
	char yourmsg[2000];
	int i = 0;
	for (i=0;i<1024;i++) {
		yourmsg[i]='a';
	}
	for (i=1024;i<2000;i++) {
		yourmsg[i]='b';
	}
	int h = open("/dev/rwbuf", O_WRONLY);
	int n = write (h, yourmsg, sizeof(yourmsg));
	close(h);
}
