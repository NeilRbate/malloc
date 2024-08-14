#include "../include/include.h"

memory_struct mmstruct;
pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

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

	while(i < SMALL_BLOCK_COUNT) {

		if (current->size[i] == NOT_ALLOCATED) {
			current->size[i] = size;
			return current->block_ptr[i];
		}
		i++;
	  if (i == SMALL_BLOCK_COUNT) {
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

	tiny_zone_ptr	*current = mmstruct.tiny_ptr;
	size_t		i = 0;

	while(i < TINY_BLOCK_COUNT) {

		if (current->size[i] == NOT_ALLOCATED) {
			current->size[i] = size;
			return current->block_ptr[i];
		}
		i++;
	  	if (i == TINY_BLOCK_COUNT) {
			if (current->next == NULL && !(current->next = init_tiny()))
				return ALLOC_FAILURE;
			i = 0;
			current = current->next;
		}
	}

	return ALLOC_FAILURE;
}

void
*thread_malloc(size_t size)
{
	if (size < 1)
		goto failure;

	if (mmstruct.is_init != IS_INIT)
		if (init_mmstruct() != SUCCESS)
			goto failure;

	getrlimit(RLIMIT_DATA, &mmstruct.rlim);

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
		if (large_ptr == FAILURE)
			return NULL;
		return (void *)large_ptr;
	}

failure:
	return MALLOC_FAIL;
}

void	
*malloc(size_t size)
{
	void *ptr = NULL;

	if (pthread_mutex_lock(&mutex) != 0)
		return MALLOC_FAIL;
	if (size < 1)
		goto failure;

	if (mmstruct.is_init != IS_INIT)
		if (init_mmstruct() != SUCCESS)
			goto failure;

	getrlimit(RLIMIT_DATA, &mmstruct.rlim);

	if (size <= TINY_BLOCK_SIZE) {

		if (mmstruct.tiny_ptr == NULL)
			mmstruct.tiny_ptr = init_tiny();

		ptr = tiny_alloc(size);
		write_log(NULL, MALLOC, size);
		pthread_mutex_unlock(&mutex);

		return ptr;

	} else if (size <= SMALL_BLOCK_SIZE) {

		if (mmstruct.small_ptr == NULL)
			mmstruct.small_ptr = init_small();

		ptr = small_alloc(size);
		write_log(NULL, MALLOC, size);
		pthread_mutex_unlock(&mutex);

		return ptr;
	} else {
		uint64_t	large_ptr = large_alloc(size);

		if (large_ptr == FAILURE)
			goto failure;

		write_log(NULL, MALLOC, size);
		pthread_mutex_unlock(&mutex);

		return (void *)large_ptr;
	}

failure:
	write_log("FAILURE", MALLOC, size);
	pthread_mutex_unlock(&mutex);
	return MALLOC_FAIL;
}
