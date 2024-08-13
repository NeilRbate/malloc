#include "../include/include.h"

static void
*mmove_and_free(void *ptr,alloc_zone zone)
{
	if (!ptr)
		return ALLOC_FAILURE;
	ft_memmove(ptr, zone.ptr, zone.size);
	thread_free(zone.ptr);
	return ptr;
}

static void
*realloc_tiny(alloc_zone zone, size_t size)
{
	void	*ptr = NULL;

	if (size < zone.size)
		zone.size = size;

	if (size <= TINY_BLOCK_SIZE)
		return zone.ptr;
	else if (size <= SMALL_BLOCK_SIZE) {
		if (!(ptr = thread_malloc(size)))
			goto failure;
		return mmove_and_free(ptr, zone);
	}
	
	if (!(ptr = thread_malloc(size)))
		goto failure;
	return mmove_and_free(ptr, zone);

failure:
	return ALLOC_FAILURE;
}

static void
*realloc_small(alloc_zone zone, size_t size)
{
	void	*ptr = NULL;

	if (size < zone.size)
		zone.size = size;

	if (size <= TINY_BLOCK_SIZE) {
		if (!(ptr = thread_malloc(size)))
			goto failure;
		return mmove_and_free(ptr, zone);
	}
	else if (size <= SMALL_BLOCK_SIZE)
		return zone.ptr;
	
	if (!(ptr = thread_malloc(size)))
		goto failure;
	return mmove_and_free(ptr, zone);

failure:
	return ALLOC_FAILURE;

}

static void
*realloc_large(alloc_zone zone, size_t size)
{
	void	*ptr = NULL;

	if (size < zone.size)
		zone.size = size;

	if (!(ptr = thread_malloc(size)))
		goto failure;
	return mmove_and_free(ptr, zone);

failure:
	return ALLOC_FAILURE;

}

void	
*realloc(void *ptr, size_t size)
{

	if (pthread_mutex_lock(&mutex) != 0)
		return ALLOC_FAILURE;
	alloc_zone	zone;
	void		*ret;

	if (!ptr)
		goto failure;
	else if (size == 0) {
		free(ptr);
		goto failure;
	}

	zone = find_alloc_zone(ptr);

	switch(zone.zone) {

		case NO_ZONE:
			goto failure;

		case TINY_FLAG:
			ret = realloc_tiny(zone, size);
			pthread_mutex_unlock(&mutex);
			return ret;
		
		case SMALL_FLAG:
			ret = realloc_small(zone, size);
			pthread_mutex_unlock(&mutex);
			return ret;

		case LARGE_FLAG:
			ret = realloc_large(zone, size);
			pthread_mutex_unlock(&mutex);
			return ret;
	}

failure:
	pthread_mutex_unlock(&mutex);
	return ALLOC_FAILURE;
}
