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
	char *addr1;
	char *addr2;
	char *addr3;
	char *addr4;
	char *addr5;
	/*
while (i < 1)
{
addr = (char*)malloc(1024);
addr[0] = 42;
i++;
}
i = 0;
*/
addr1 = malloc(102400);
addr2 = malloc(102400);
addr3 = malloc(102400);
addr4 = malloc(102400);
addr5 = malloc(102400);
addr1[0] = 'A';
addr2[0] = 'B';
addr3[0] = 'C';
addr4[0] = 'D';
addr5[0] = 'E';
show_alloc_mem();
//ft_printf("%s\n%s\n%s\n%s\n", addr1, addr3, addr4, addr5);
free(addr5);
show_alloc_mem();
int i = 0;
while (i < 2000) {
	char *a = malloc(1020000);
	a[0] = 'B';
	i++;
}
show_alloc_mem();
//ft_printf("%s\n%s\n%s\n%s\n", addr1, addr3, addr4, addr5);
/*
char *addr = malloc(100000);
char *addr2 = malloc(100000);
char *addr3 = malloc(100000);
char *addr4 = malloc(100000);
char *addr5 = malloc(1000000);
for(size_t i = 0; i < 26; i++) {
	addr[i] = i + 'a';
	addr2[i] = i + 'A';
	addr3[i] = i + 'A';
	addr4[i] = i + 'A';
	addr5[i] = i + 'A';
}
addr[26] = 0;
addr2[26] = 0;
addr3[26] = 0;
addr4[26] = 0;
addr5[26] = 0;

ft_printf("%s\n%s\n%s\n%s\n%s\n", addr, addr2, addr3, addr4, addr5);
*/
	return 0;
}
