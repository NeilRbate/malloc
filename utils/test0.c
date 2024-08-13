#include "../include/include.h"

int main()
{
	int i = 0;
	char *tiny, *small, *large;
	while (i < 120) {
		tiny = malloc(256);
		small = malloc(1024);
		large = malloc (4096);
		i++;
	}
	show_alloc_mem();

}
