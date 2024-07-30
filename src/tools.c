#include "../include/include.h"

static	void
show_large_alloc()
{
	//TODO
}

static	void
show_small_alloc()
{
	uint64_t	i = 0, 
			alloc_start = 0, 
			alloc_end = 0, 
			*flag;

	while(i < mmstruct.small_length) {
		flag = (uint64_t *)((char *)mmstruct.small_ptr + i);

		if (*flag == NOT_ALLOCATED) {
			if (i != 0)
				ft_printf("Total used: [%d Bytes/ %d Bytes]\n", 
					i,
					(mmstruct.small_max - (uint64_t)mmstruct.small_ptr));
			return;
		}

		if (i == 0) 
			ft_printf("SMALL : [%p] - [%p] : [%dMBytes]\n\n", mmstruct.small_ptr
					, mmstruct.small_max,
					(mmstruct.small_max - (uint64_t)mmstruct.small_ptr)
					/ 100000);

		alloc_start = (uint64_t)mmstruct.small_ptr + i + sizeof(uint64_t);
		alloc_end	= (uint64_t)mmstruct.small_ptr + i + sizeof(uint64_t) + *flag;

		ft_printf("        [%p] - [%p] : %d bytes\n", 
				alloc_start, 
				alloc_end, 
				alloc_end - alloc_start);

		i += (sizeof(uint64_t) + *flag + 1);
	}
}

static	void
show_tiny_alloc()
{

	uint64_t	i = 0, 
			alloc_start = 0, 
			alloc_end = 0, 
			*flag;

	while(i < mmstruct.tiny_length) {
		flag = (uint64_t *)((char *)mmstruct.tiny_ptr + i);
		if (*flag == NOT_ALLOCATED) {
			if (i != 0)
				ft_printf("Total used: [%d Bytes/ %d Bytes]\n", 
					i,
					(mmstruct.tiny_max - (uint64_t)mmstruct.tiny_ptr));
			return;
		}
		if (i == 0) 
			ft_printf("TINY  : [%p] - [%p] : [%dMBytes]\n", 
					mmstruct.tiny_ptr, 
					mmstruct.tiny_max,
					(mmstruct.tiny_max - (uint64_t)mmstruct.tiny_ptr)
					/ 100000);

		alloc_start = (uint64_t)mmstruct.tiny_ptr + i + sizeof(uint64_t);
		alloc_end = (uint64_t)mmstruct.tiny_ptr + i + sizeof(uint64_t) + *flag;

		ft_printf("        [%p] - [%p] : [%dBytes]\n", 
				alloc_start, 
				alloc_end, 
				alloc_end - alloc_start);

		i += (sizeof(uint64_t) + *flag + 1);
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
