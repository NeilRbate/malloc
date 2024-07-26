#include "../include/include.h"

memory_struct mmstruct;

static int
large_alloc(size_t size)
{
	//TOD()O
	(void)size;
	return FAILURE;
}

static int
small_alloc(size_t size)
{
	uint64_t	i = 0;
	while(i < mmstruct.small_length) {
		uint64_t	*flag = (uint64_t *)((char *)mmstruct.small_ptr + i);
		if (*flag == NOT_ALLOCATED) {
			*flag = size;
			return (i + sizeof(uint64_t));
		}
		i += (sizeof(uint64_t) + *flag + 1);
	}
	return FAILURE;
}


static int
tiny_alloc(size_t size)
{
	uint64_t	i = 0;
	while(i < mmstruct.tiny_length) {
		uint64_t	*flag = (uint64_t *)((char *)mmstruct.tiny_ptr + i);
		if (*flag == NOT_ALLOCATED) {
			*flag = size;
			return (i + sizeof(uint64_t));
		}
		i += (sizeof(uint64_t) + *flag + 1);
	}
	return FAILURE;
}

void	
*malloc(size_t size)
{
	if (mmstruct.is_init != IS_INIT)
		if (init_memory_page() != SUCCESS)
			goto failure;
	if (size < 1)
		return NULL;
	
	int	alloc_ndx = 0;

	if (size <= mmstruct.tiny_sysconf) {
		alloc_ndx = tiny_alloc(size);
		return (alloc_ndx != FAILURE ? mmstruct.tiny_ptr + alloc_ndx : NULL);
	} else if (size <= mmstruct.small_sysconf) {
		alloc_ndx = small_alloc(size);
		return (alloc_ndx != FAILURE ? mmstruct.small_ptr + alloc_ndx : NULL);
	} else {
		alloc_ndx = large_alloc(size);
		//TODO Change to large_array
		return (alloc_ndx != FAILURE ? mmstruct.small_ptr + alloc_ndx : NULL);
	}


failure:
	return MALLOC_FAIL;
}
