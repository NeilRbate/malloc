#include "../include/include.h"

int main()
{
	char	*ptr;
	int i = 0;
	while (i < 1024) {
		ptr = malloc(1024);
		ptr[0] = 'B';
		i++;
		free(ptr);
	}
}
