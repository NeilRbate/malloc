#include "../include/include.h"

memory_struct mmstruct;

static uint64_t
large_alloc(size_t size)
{
	getrlimit(RLIMIT_DATA, &mmstruct.rlim);
    	if (size > mmstruct.rlim.rlim_max)
        	return FAILURE;

	if(mmstruct.large_ptr == NULL) {
		mmstruct.large_ptr = large_mmap(size);
		return mmstruct.large_ptr ? (uint64_t)mmstruct.large_ptr->block_ptr : FAILURE;
	} else {
		void	*alloc = get_last_alloc();
		if (!alloc)
			return FAILURE;
		((s_ptr *)alloc)->next = large_mmap(size);
		alloc = ((s_ptr *)alloc)->next;
		return alloc ? (uint64_t)((s_ptr *)alloc)->block_ptr : FAILURE;
	}
	
	return FAILURE;
}

static void
*small_alloc(size_t size)
{
	small_zone_ptr	*current = mmstruct.small_ptr;
	size_t		i = 0;

	while(i < 125) {

		if (current->size[i] == NOT_ALLOCATED) {
			current->size[i] = size;
			return current->block_ptr[i];
		}
		i++;
	  if (i == 125) {
			if (current->next == NULL && !(current->next = init_small()))
				return ALLOC_FAILURE;
			i = 0;
			current = current->next;
		}
	}

	return ALLOC_FAILURE;
}


static void
*tiny_alloc(size_t size)
{
	s_ptr	*current = mmstruct.tiny_ptr;

	while(1) {

		if (current->size == NOT_ALLOCATED) {
			current->size = size;
			return (void *)current->block_ptr;
		} else if (!current->next) {
			if (!(current->next = init_tiny()))
				return ALLOC_FAILURE;
		}

		current = current->next;
	}

	return ALLOC_FAILURE;
}

void	
*malloc(size_t size)
{
	if (size < 1)
		goto failure;

	size = (size + 15) & ~15;

	if (mmstruct.is_init != IS_INIT)
		if (init_mmstruct() != SUCCESS)
			goto failure;

	if (size <= TINY_BLOCK_SIZE) {
		if (mmstruct.tiny_ptr == NULL)
			mmstruct.tiny_ptr = init_tiny();
		return tiny_alloc(size);
	} else if (size <= SMALL_BLOCK_SIZE) {
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
