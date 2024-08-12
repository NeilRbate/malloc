#include "../include/include.h"

static	void
show_large_alloc()
{
	uint64_t	i = 0;
	s_ptr	*ptr = mmstruct.large_ptr;

	while(ptr) {
		if (ptr && ptr->block_ptr) {
			if (i == 0)
				ft_printf("LARGE :\n\n");
			i++;
			ft_printf("        [%p]: [%p] - [%p] : %d Bytes\n", 
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

	current = mmstruct.small_ptr;

	while (i < 125) {
		if (current->size[i] == NOT_ALLOCATED)
			break;
		if (current->size[i] != NOT_ALLOCATED) {
			if (i == 0) {
				ft_printf("SMALL : [%p]\n", mmstruct.small_ptr);
			}
			ft_printf("        [%p]: [%p] - [%p] : %d Bytes\n", 
				current,
				current->block_ptr[i], 
				current->block_ptr[i] + current->size[i], 
				current->block_ptr[i] + current->size[i] - current->block_ptr[i]);
		}
		i++;
		if (i == 125 && current->next != NULL) {
			i = 0;
			current = current->next;
		}
	}
}

static	void
show_tiny_alloc()
{

	uint	i = 0;
	s_ptr	*current;

	current = mmstruct.tiny_ptr;

	while (current) {
		if (current && current->size == NOT_ALLOCATED)
			break;
		if (current && current->size != NOT_ALLOCATED) {
			if (i == 0) {
				ft_printf("TINY  : [%p]\n", mmstruct.tiny_ptr);
				i++;
			}
			ft_printf("        [%p]: [%p] - [%p] : %d Bytes\n", 
				current,
				current->block_ptr, 
				current->block_ptr + current->size, 
				current->block_ptr + current->size - current->block_ptr);
		}
		current = current->next;
	}
}

void
show_alloc_mem()
{
	if (mmstruct.is_init != IS_INIT)
		return;
	show_tiny_alloc();
  	show_small_alloc();
  	show_large_alloc();
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
