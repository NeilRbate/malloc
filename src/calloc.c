#include "../include/include.h"

void
*calloc(size_t nmemb, size_t size)
{
	if (pthread_mutex_lock(&mutex) != 0)
		return ALLOC_FAILURE;
	if (nmemb == 0 || size == 0) {
		write_log("nmemb/size invalid", CALLOC, 0);
		pthread_mutex_unlock(&mutex);
		return ALLOC_FAILURE;
	}
	size_t	total_size = size * nmemb;
	void *ret = thread_malloc(total_size);
	if (!ret) {
		write_log("FAILURE", CALLOC, 0);
		pthread_mutex_unlock(&mutex);
		return ALLOC_FAILURE;
	}

	ft_bzero(ret, total_size);
	write_log(NULL, CALLOC, 0);
	pthread_mutex_unlock(&mutex);

	return ret; 
}
