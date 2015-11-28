#include <stdio.h>
int main()
{
	printf("The return value is: %d.\n", syscall(223, 135));
	return 0;
}
