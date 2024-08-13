#include "include/include.h"

int main()
{
	int i = 0;
	char *ptr;
	while(i < 1) {
		ptr = malloc(1000);
		ptr[0] = 'A';
		i++;
	}

	show_alloc_mem();
	show_memory_dump(SMALL_ZONE);
	return 0 ;
}
