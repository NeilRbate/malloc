#include "include/include.h"

int main()
{
	char *ptr;
		ptr = malloc(100);
		ptr[0] = 'A';

	show_alloc_mem();
	show_memory_dump(SMALL_ZONE);
	return 0 ;
}
