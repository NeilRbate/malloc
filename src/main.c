#include "../include/include.h"

int	main()
{
	char *a;
	a = malloc(10);
	(void)a;
	ft_printf("tiny size -> %d small_size -> %d\n", TINY_SIZE, SMALL_SIZE);
	return 0;
}
