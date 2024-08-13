#include "../include/include.h"

static	void
show_large_alloc()
{
	uint64_t	i = 0;
	s_ptr	*ptr = mmstruct.large_ptr;

	while(ptr) {
		if (ptr && ptr->block_ptr) {
			if (i == 0)
				ft_printf(" LARGE:\n");
			i++;
			ft_printf("        [%p] : [%p] - [%p] : %u Bytes\n", 
				ptr,
				ptr->block_ptr, 
				ptr->block_ptr + ptr->size, 
				(ptr->block_ptr + ptr->size) - 
				ptr->block_ptr);
		}
		ptr = ptr->next;
	}
}

static	void
show_small_alloc()
{
	uint	i = 0;
	small_zone_ptr	*current;

	if (!mmstruct.small_ptr)
		return;

	current = mmstruct.small_ptr;

	while (i < SMALL_BLOCK_COUNT) {
		if (current->size[i] != NOT_ALLOCATED) {
			if (i == 0) {
				ft_printf(" SMALL: [%p]\n", mmstruct.small_ptr);
			}

			ft_printf("                           [%p] - [%p] : %u Bytes\n", 
				current->block_ptr[i], 
				current->block_ptr[i] + current->size[i], 
				current->block_ptr[i] + current->size[i] - current->block_ptr[i]);
		}
		i++;
		if (i == SMALL_BLOCK_COUNT && current->next != NULL) {
			i = 0;
			current = current->next;
		}
	}
}

static	void
show_tiny_alloc()
{

	uint	i = 0;
	tiny_zone_ptr	*current;

	current = mmstruct.tiny_ptr;

	if (!mmstruct.tiny_ptr)
		return;

	while (i < TINY_BLOCK_COUNT) {
		if (current->size[i] != NOT_ALLOCATED) {
			if (i == 0) {
				ft_printf(" TINY : [%p]\n", mmstruct.tiny_ptr);
			}
			ft_printf("                           [%p] - [%p] : %u Bytes\n", 
				current->block_ptr[i], 
				current->block_ptr[i] + current->size[i], 
				current->block_ptr[i] + current->size[i] - current->block_ptr[i]);
		}
		i++;
		if (i == TINY_BLOCK_COUNT && current->next != NULL) {
			i = 0;
			current = current->next;
		}
	}
}

void
show_alloc_mem()
{
	if (pthread_mutex_lock(&mutex) != 0)
		return;

	if (mmstruct.is_init != IS_INIT) {
		pthread_mutex_unlock(&mutex);
		return;
	}
	ft_printf(" ZONE |     METADATA     |    DATA START    |     DATA END     |  SIZE (Bytes)\n");
	show_tiny_alloc();
  	show_small_alloc();
  	show_large_alloc();
	pthread_mutex_unlock(&mutex);

}

size_t	
get_alloc_number(s_ptr *alloc) 
{
	size_t	size = 0;

	while(alloc) {
		if (alloc->size != NOT_ALLOCATED)
			size++;
		else
			return size;
		alloc = alloc->next;
	}
	return size;
}

s_ptr
*get_last_alloc()
{
	s_ptr	*current;

	current = mmstruct.large_ptr;
	while(current->next) {
		current = current->next;
	}
	return current;
}

static s_ptr
*find_large_alloc(void * ptr)
{
	s_ptr	*current = mmstruct.large_ptr;

	while(current) {
		if (current->block_ptr == (uint64_t)ptr) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}


alloc_zone
find_alloc_zone(void *ptr)
{
	alloc_zone	zone;
	tiny_zone_ptr	*tiny_header = mmstruct.tiny_ptr;
	uint64_t	i = 0;


	while (tiny_header && i < TINY_BLOCK_COUNT) {
		if (tiny_header->block_ptr[i] == ptr) {
			zone.zone = TINY_FLAG;
			zone.size = tiny_header->size[i];
			zone.ptr = ptr;
			return zone;
		}
		i++;
		if (i == TINY_BLOCK_COUNT && tiny_header->next != NULL) {
			i = 0;
			tiny_header = tiny_header->next;
		}
	}

	small_zone_ptr	*small_header = mmstruct.small_ptr;
	i = 0;

	while (small_header && i < SMALL_BLOCK_COUNT) {
		if (small_header->block_ptr[i] == ptr) {
			zone.zone = SMALL_FLAG;
			zone.size = small_header->size[i];
			zone.ptr = ptr;
			return zone;
		}
		i++;
		if(i == SMALL_BLOCK_COUNT && small_header->next != NULL) {
			i = 0;
			small_header = small_header->next;
		}
	}

	s_ptr	*large = find_large_alloc(ptr);
	if (large) {
		zone.zone = LARGE_FLAG;
		zone.size = large->size;
		zone.ptr = (void *)large->block_ptr;
		return zone;
	}
	zone.zone = NO_ZONE;
	return zone;
}
