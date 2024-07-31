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

static void
*small_alloc(size_t size)
{
	(void)size;
	return ALLOC_FAILURE;
}


static void
*tiny_alloc(size_t size)
{
	(void)size;
	return ALLOC_FAILURE;
}

void	
*malloc(size_t size)
{
	if (size < 1)
		goto failure;

	if (mmstruct.is_init != IS_INIT)
		if (init_mmstruct() != SUCCESS)
			goto failure;

	if (size <= mmstruct.tiny_sysconf) {
		if (mmstruct.tiny_ptr == NULL)
			mmstruct.tiny_ptr = init_tiny();
		return tiny_alloc(size);
	} else if (size <= mmstruct.small_sysconf) {
		if (mmstruct.small_ptr == NULL)
			mmstruct.small_ptr = init_small();
		return small_alloc(size);
	} else {
		uint64_t	large_ptr = large_alloc(size);
		return (large_ptr != FAILURE ? (void *)large_ptr : NULL);
	}

failure:
	return MALLOC_FAIL;
}
