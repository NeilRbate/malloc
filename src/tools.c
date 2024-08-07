#include "../include/include.h"

static	void
show_large_alloc()
{
	uint64_t	i = 0;
	l_ptr	*ptr = mmstruct.large_ptr;

	while(ptr) {
		if (ptr && ptr->alloc_ptr) {
			if (i == 0)
				ft_printf("LARGE :\n\n");
			i++;
			ft_printf("        [%p]: [%p] - [%p] : %d Bytes\n", 
				ptr,
				ptr->alloc_ptr, 
				ptr->alloc_ptr + ptr->size, 
				ptr->alloc_ptr + ptr->size - ptr->alloc_ptr - 32);
		}
		ptr = ptr->next;
	}
}

static	void
show_small_alloc()
{
	uint	i = 0;
	s_ptr	*current;

	current = mmstruct.small_ptr;

	while (current) {
		if (current && current->size == NOT_ALLOCATED)
			break;
		if (current && current->size != NOT_ALLOCATED) {
			if (i == 0) {
				ft_printf("SMALL : [%p]\n", mmstruct.small_ptr);
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

static	void
show_tiny_alloc()
{
	/*
	uint	i = 0;
	s_ptr	*current;

	current = mmstruct.tiny_ptr;
	while (current) {
		if (current && current->block[0] != 0) {
			if (i == 0) {
				ft_printf("TINY :  [%p]\n", mmstruct.tiny_ptr);
				i++;
			}
			ft_printf("        [%p]\n", current + sizeof(s_ptr));
		}
		current = current->next;
	}
	*/
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

l_ptr
*get_last_alloc()
{
	l_ptr	*current;

	current = mmstruct.large_ptr;
	while(current->next) {
		current = current->next;
	}
	return current;
}
