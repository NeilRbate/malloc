#include "../include/include.h"

int	main()
{
	ft_printf("sizeof(s_ptr) %d\n", sizeof(s_ptr));
	char *str;
	int i = 0;
	while (i < 100)
	{
		str = (char*)malloc(1);
		str[0] = 42;
		i++;
	}
	//show_alloc_mem();
}
