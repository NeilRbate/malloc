#include "../include/include.h"

/*
static	void
show_large_alloc()
{
	memory_page	*large = mmstruct->large;
	size_t	size = mmstruct->large_size;

	if (size == 0)
		return;
	for(size_t i = 0; i < size; i++) {
		ft_printf("[%p] - [%p] : %d bytes\n", 
				large[i].alloc_ptr,
				large[i].alloc_ptr + large[i].alloc_size,
				large[i].alloc_ptr + large[i].alloc_size - 
				large[i].alloc_ptr);
	}

}

static	void
show_small_alloc()
{
	memory_page	*small = mmstruct->small;
	int	flag = 0;

	for(size_t i = 0; i < PAGE_QUANTITY; i++) {
		if (small[i].is_allocated) {
			if (flag == 0) {
				ft_printf("SMALL : %p\n", mmstruct->small_ptr);
			}
			ft_printf("[%p] - [%p] : %d bytes\n", 
					small[i].alloc_ptr,
					small[i].alloc_ptr + small[i].alloc_size,
					small[i].alloc_ptr + small[i].alloc_size - 
					small[i].alloc_ptr);
		}
	}
}
*/
static	void
show_tiny_alloc()
{

	long int i = 0;
	while(i < mmstruct.tiny_length) {
		if (GET_ALLOCATED((uint64_t)mmstruct.tiny_ptr + i) == IS_ALLOCATED) {
			uint64_t	*ptr = (uint64_t *)((char *)mmstruct.tiny_ptr + i + sizeof(uint64_t));
			ft_printf("[%p] - [%p]\n", ptr, ptr + GET_ALLOCSIZE(*ptr));
			i += (sizeof(uint64_t) + 
					GET_ALLOCSIZE((uint64_t)mmstruct.tiny_ptr + i) + 1);
		}
		else
			break;
	}


/*
	ulong i = 0;
	memory_page	*page = NULL;
	while(i < TINY_LENGTH) {
		page = (memory_page *)mmstruct->tiny_ptr + i;
		if (page->is_allocated == IS_ALLOCATED) {
			ft_printf("[%p] - [%p]", page->alloc_ptr, page->alloc_ptr + page->alloc_size);
		} 
		else
			i += ((ulong) sizeof(memory_page) + page->alloc_size + 1);

	}
*/
	/*
	memory_page	*tiny = mmstruct->tiny;
	int	flag = 0;
	
	for(size_t i = 0; i < PAGE_QUANTITY; i++) {
		if (tiny[i].is_allocated) {
			if (flag == 0) {
				ft_printf("TINY : %p\n", mmstruct->tiny_ptr);
				flag ++;
			}
			ft_printf("[%p] - [%p] : %d bytes\n", 
					tiny[i].alloc_ptr,
					tiny[i].alloc_ptr + tiny[i].alloc_size,
					tiny[i].alloc_ptr + tiny[i].alloc_size - 
					tiny[i].alloc_ptr);
		}
	}
	*/
}

void
show_alloc_mem()
{
	if (mmstruct.is_init != IS_INIT)
		ft_printf("no allocation\n");
	show_tiny_alloc();
//	show_small_alloc();
//	show_large_alloc();
}
