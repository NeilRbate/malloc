#include "../include/include.h"

memory_struct mmstruct;

static uint64_t
large_alloc(size_t size)
{
	//Check heap limit
	getrlimit(RLIMIT_DATA, &mmstruct.rlim);
    	if (size > mmstruct.rlim.rlim_max)
        	return FAILURE;

	if(mmstruct.large_ptr == NULL) {
		mmstruct.large_ptr = large_mmap(size);
		return mmstruct.large_ptr ? (uint64_t)mmstruct.large_ptr->alloc_ptr : FAILURE;
	} else {
		void	*alloc = get_last_alloc();
		if (!alloc)
			return FAILURE;
		((l_ptr *)alloc)->next = large_mmap(size);
		alloc = ((l_ptr *)alloc)->next;
		return alloc ? (uint64_t)((l_ptr *)alloc)->alloc_ptr : FAILURE;
	}
	
	return FAILURE;
}

static int
small_alloc(size_t size)
{
	uint64_t	i = 0,
		       	*flag = 0;

	while(i < mmstruct.small_length) {
		flag = (uint64_t *)((char *)mmstruct.small_ptr + i);
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
	uint64_t	i = 0, 
		       	*flag = 0;

	while(i < mmstruct.tiny_length) {
		flag = (uint64_t *)((char *)mmstruct.tiny_ptr + i);
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
	int	alloc_ndx = 0;

	if (mmstruct.is_init != IS_INIT)
		if (init_memory_page() != SUCCESS)
			goto failure;
	if (size < 1)
		goto failure;

	if (size <= mmstruct.tiny_sysconf) {
		alloc_ndx = tiny_alloc(size);
		return (alloc_ndx != FAILURE ? mmstruct.tiny_ptr + alloc_ndx : NULL);
	} else if (size <= mmstruct.small_sysconf) {
		alloc_ndx = small_alloc(size);
		return (alloc_ndx != FAILURE ? mmstruct.small_ptr + alloc_ndx : NULL);
	} else {
		uint64_t	large_ptr = large_alloc(size);
		return (large_ptr != FAILURE ? (void *)large_ptr : NULL);
	}


failure:
	return MALLOC_FAIL;
}
