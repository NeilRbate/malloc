#include "../include/include.h"

extern memory_struct *mmstruct;

void	test_link()
{
	ft_printf("LINK SUCESS !\n");
}

void	*amalloc(size_t size)
{
	ft_printf("coucou\n");
	if (mmstruct->is_init != IS_INIT)
		if (init_memory_page(mmstruct) != SUCCESS)
			goto failure;
	(void)size;
	ft_printf("sizeof(alloc_array) -> %d\n", sizeof(mmstruct));

failure:
	return MALLOC_FAIL;
}
