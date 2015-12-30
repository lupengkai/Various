#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
int main() {
char yourmsg[2000];
int h = open("/dev/rwbuf", O_RDONLY);
int n = read (h, yourmsg, sizeof(yourmsg));
printf("%s",yourmsg);
close(h);
}

