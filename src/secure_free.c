#include "../include/include.h"

void
secure_free(void *ptr)
{
	if (pthread_mutex_lock(&mutex) != 0)
		return;


	if (!ptr) {
		pthread_mutex_unlock(&mutex);
		return;
	}

	alloc_zone	zone = find_alloc_zone(ptr);

	if (zone.zone == NO_ZONE) {
		ft_printf("secure_free(): invalid pointer\n");
		write_log("FAILURE", REALLOC, 0);
		pthread_mutex_unlock(&mutex);
	}

	ft_bzero(zone.ptr, zone.size);
	thread_free(ptr);
	write_log(NULL, SECURE_FREE, 0);
	pthread_mutex_unlock(&mutex);
}
