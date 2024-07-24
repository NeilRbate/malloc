#include "../include/include.h"

memory_struct mmstruct;

static int
small_alloc(size_t size)
{
	(void)size;
	return FAILURE;
}


static int
tiny_alloc(size_t size)
{
	ulong	i = 0;
	while(i < mmstruct.tiny_length) {
		if (((memory_page *)mmstruct.tiny_ptr + i)->is_allocated == NOT_ALLOCATED) {
			((memory_page *)mmstruct.tiny_ptr + i)->is_allocated = IS_ALLOCATED;
			((memory_page *)mmstruct.tiny_ptr + i)->alloc_size = size;
			((memory_page *)mmstruct.tiny_ptr + i)->alloc_ptr = 
				mmstruct.tiny_ptr + i + sizeof(memory_page);
			//ft_printf("m_p_size -> [%d] i -> [%d]  mmstruct->tiny_ptr[%p]\n",
			//	       sizeof(memory_page),	
			//		i,
			//		((memory_page *)mmstruct->tiny_ptr + i)->alloc_ptr);
			return (i + sizeof(memory_page));
		}
		i += (sizeof(memory_page) + 
		((memory_page *)mmstruct.tiny_ptr + i)->alloc_size + 1);

	}

	return FAILURE;
}

void	*malloc(size_t size)
{
	if (mmstruct.is_init != IS_INIT)
		if (init_memory_page() != SUCCESS)
			goto failure;
	
	int	alloc_ndx = 0;

	if (size <= mmstruct.tiny_sysconf) {
		alloc_ndx = tiny_alloc(size);
		return (alloc_ndx != FAILURE ? mmstruct.tiny_ptr + alloc_ndx: NULL);
	} else if (size <= mmstruct.small_sysconf) {
		alloc_ndx = small_alloc(size);
		//return (alloc_ndx != FAILURE ? mmstruct->small[alloc_ndx].alloc_ptr : NULL);
	} else {
		//goto large alloc
		ft_printf("Large alloc\n");
	}


failure:
	return MALLOC_FAIL;
}
