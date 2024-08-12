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

	s_ptr	*current = NULL;
	uint64_t	i = 0;

	current = mmstruct.tiny_ptr;

	while (current) {
		if (current && current->block_ptr == (uint64_t)ptr) {
			current->size = NOT_ALLOCATED;
			//TODO Defrag
			return SUCCESS;
		}
		current = current->next;
	}

	small_zone_ptr	*header = mmstruct.small_ptr;

	while (i < 125) {
		if (header->block_ptr[i] == ptr) {
			header->size[i] = NOT_ALLOCATED;
			//TODO Defrag
			return SUCCESS;
		}
		i++;
		if(i == 125 && header->next != NULL) {
			i = 0;
			header = header->next;
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
