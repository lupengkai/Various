#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
int main() {
	char yourmsg[20]={"test open"};
    int h = open("/dev/rwbuf", O_WRONLY);
    if (h<0) return -1;
	int n = write (h, yourmsg, sizeof(yourmsg)+1);
	getchar();
}
