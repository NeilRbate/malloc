#include "../include/include.h"

static	void
show_large_alloc()
{
	//TODO
}

static	void
show_small_alloc()
{
	uint64_t	i = 0;
	while(i < mmstruct.small_length) {
		uint64_t	*flag = (uint64_t *)((char *)mmstruct.small_ptr + i);
		if (*flag != NOT_ALLOCATED) {
			if (i == 0) 
				ft_printf("SMALL : %p\n", flag);
			uint64_t	alloc_start = (uint64_t)mmstruct.small_ptr + i + sizeof(uint64_t);
			uint64_t	alloc_end	= (uint64_t)mmstruct.small_ptr + i + sizeof(uint64_t) + *flag;
			ft_printf("[%p] - [%p] : %d bytes\n", alloc_start, alloc_end, alloc_end - alloc_start);
		}
		i += (sizeof(uint64_t) + *flag + 1);
	}
}

static	void
show_tiny_alloc()
{

	uint64_t	i = 0;
	while(i < mmstruct.tiny_length) {
		uint64_t	*flag = (uint64_t *)((char *)mmstruct.tiny_ptr + i);
		if (*flag != NOT_ALLOCATED) {
			if (i == 0) 
				ft_printf("TINY : %p\n", flag);
			uint64_t	alloc_start = (uint64_t)mmstruct.tiny_ptr + i + sizeof(uint64_t);
			uint64_t	alloc_end	= (uint64_t)mmstruct.tiny_ptr + i + sizeof(uint64_t) + *flag;
			ft_printf("[%p] - [%p] : %d bytes\n", alloc_start, alloc_end, alloc_end - alloc_start);
		}
		i += (sizeof(uint64_t) + *flag + 1);
	}
}

void
show_alloc_mem()
{
	if (mmstruct.is_init != IS_INIT)
		ft_printf("no allocation\n");
	show_tiny_alloc();
  show_small_alloc();
  show_large_alloc();
}
