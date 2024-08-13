#include "../include/include.h"

int main()
{
	char	*addr1 = malloc(200);
	addr1[0] = 'A';
	char	*addr2 = malloc(200);
	addr2[0] = 'B';
	char	*addr3 = malloc(200);
	addr3[0] = 'C';

	char	*addr4 = malloc(200);
	addr4[0] = 'D';
	char	*addr5 = malloc(200);
	addr5[0] = 'E';
	char	*addr6 = malloc(200);
	addr6[0] = 'F';




	show_alloc_mem();

	free(addr2);

	show_alloc_mem();

	free(addr5);

	ft_printf("%s\n%s\n%s\n%s\n",addr1, addr3, addr4, addr6);

	show_alloc_mem();

	//show_memory_dump(ptr);
}
