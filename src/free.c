#include "../include/include.h"

static unsigned int
free_large(void *ptr) {

	s_ptr	*current = mmstruct.large_ptr, *next = NULL;
	if (current)
		next = mmstruct.large_ptr->next; 

	if (current && current->block_ptr == (uint64_t)ptr) {
		mmstruct.large_ptr = next;
		int ret = munmap(current
				, current->size);
		return ret == 0 ? SUCCESS : FAILURE;
	}

	while(next) {
		if (next->block_ptr == (uint64_t)ptr) {
			current->next = next->next;
			munmap(next, next->size);
			next = NULL;
			return SUCCESS;
		}
		current = next;
		next = next->next;
	}
	return FAILURE;
}

static unsigned int
find_zone(void *ptr) {

	tiny_zone_ptr	*tiny_header = mmstruct.tiny_ptr;
	uint64_t	i = 0;


	while (tiny_header && i < TINY_BLOCK_COUNT) {
		if (tiny_header->block_ptr[i] == ptr) {
			tiny_header->size[i] = NOT_ALLOCATED;
			//TODO Defrag
			return SUCCESS;
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
			small_header->size[i] = NOT_ALLOCATED;
			//TODO Defrag
			return SUCCESS;
		}
		i++;
		if(i == SMALL_BLOCK_COUNT && small_header->next != NULL) {
			i = 0;
			small_header = small_header->next;
		}
	}

	return free_large(ptr);
}


void	
free(void *ptr)
{
	//TODO Mutex lock
	if (!ptr)
		return;
	if (find_zone(ptr) != SUCCESS)
		ft_printf("free(): invalid pointer\n");
	//TODO Mutex unlock

}
