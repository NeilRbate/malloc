#include "../include/include.h"

memory_struct *mmstruct;

void	*malloc(size_t size)
{
	if (mmstruct->is_init != IS_INIT)
		if (init_memory_page(mmstruct) != SUCCESS)
			goto failure;
	(void)size;
	ft_printf("sizeof(alloc_array) -> %d\n", sizeof(mmstruct));

failure:
	return MALLOC_FAIL;
}
