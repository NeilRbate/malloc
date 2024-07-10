#include "../include/include.h"

int	main()
{
	alloc_array	tiny_alloc[TINY_SIZE] = { [0 ... TINY_SIZE - 1] = {NOT_ALLOCATED, 0, 0, NULL} };
	alloc_array	small_alloc[SMALL_SIZE] = { [0 ... SMALL_SIZE - 1] = {NOT_ALLOCATED, 0, 0, NULL} };
	alloc_array	large_alloc[LARGE_SIZE] = { [0 ... LARGE_SIZE - 1] = {NOT_ALLOCATED, 0, 0, NULL} };


	ft_printf("tiny_alloc ->%d alloc_size ->%d alloc_ndx->%d\n", sizeof(tiny_alloc), tiny_alloc[25].alloc_size, tiny_alloc[25].alloc_ndx);
	ft_printf("small_alloc ->%d\n", sizeof(small_alloc));
	ft_printf("large_alloc ->%d\n", sizeof(large_alloc));
	return 0;
}

