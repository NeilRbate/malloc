#include "../include/include.h"

int	main()
{

	int tiny_size = 20;
	//int small_size = sysconf(_SC_PAGESIZE) + 1;

	char *str = malloc(tiny_size);
	char *str1 = malloc(tiny_size);
	char *str2 = malloc(tiny_size);
	//char *str2 = malloc(small_size);

	for(int i = 0; i < tiny_size; i++) {
		str[i] = 'A';
		str1[i] = 'B';
		str2[i] = 'C';
	}

	ft_printf("str[%s]\nstr1[%s]\nstr2[%s]\n", str, str1, str2);
	//str[tiny_size + 60] = 'E';
	//show_alloc_mem();
	return 0;
}
