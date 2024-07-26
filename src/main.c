#include "../include/include.h"

int	main()
{

	/*
	int tiny_size = 20;
	//int small_size = sysconf(_SC_PAGESIZE) + 1;

	char *str = malloc(tiny_size);
	char *str1 = malloc(tiny_size);
	char *str2 = malloc(tiny_size);
	//char *str2 = malloc(small_size);
	ft_printf("str[%p]\nstr1[%p]\nstr2[%p]\n", str, str1, str2);

	for(int i = 0; i < tiny_size; i++) {
		str[i] = 'A';
		str1[i] = 'B';
		str2[i] = 'C';
	}

	ft_printf("str[%s]\nstr1[%s]\nstr2[%s]\n", str, str1, str2);
	//str[tiny_size + 60] = 'E';
	//show_alloc_mem();

	*/
	int i = 0;
	char *addr;
while (i < 10)
{
addr = (char*)malloc(1024);
addr[0] = 42;
i++;
}
i = 0;
while (i < 10)
{
addr = (char*)malloc(17200);
addr[0] = 42;
i++;
} 
show_alloc_mem();
	return 0;
}
