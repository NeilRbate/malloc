#include "../include/include.h"

int	main()
{
	ft_printf("sideof(s_ptr) %d\n", sizeof(s_ptr));
	char *str;
	int i = 0;
	while (i < 1024)
	{
		str = (char*)malloc(1024);
		str[0] = 'B';
		i++;
	}
	//show_alloc_mem();
}
