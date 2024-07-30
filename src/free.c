#include "../include/include.h"

static uint
free_zone(void *ptr, void *mmap, uint64_t zone_size)
{
	uint64_t	i = 0,
		       	*flag = 0;

	while(i < zone_size) {
		flag = (uint64_t *)((char *)mmap + i);
		if (*flag != NOT_ALLOCATED) {
			if ((uint64_t)flag + sizeof(uint64_t) == (uint64_t)ptr) {
				ft_printf("free\n");
				i += (sizeof(uint64_t) + *flag + 1);
				if (i < zone_size)
					ft_memmove((void *)flag
							, mmap + i
							, zone_size - i);
				ft_printf("mmmouv\n");
				return SUCCESS;
			}
			i += (sizeof(uint64_t) + *flag + 1);
		} 
		else
			return FAILURE;
	}
	return FAILURE;
}

void	
free(void *ptr)
{
	if (!ptr)
		return;
	if((uint64_t)ptr >= (uint64_t)mmstruct.tiny_ptr && (uint64_t)ptr < mmstruct.tiny_max) {
		free_zone(ptr, mmstruct.tiny_ptr, mmstruct.tiny_length);
		//tiny zone
	} else if (ptr >= mmstruct.small_ptr && (uint64_t)ptr < mmstruct.small_max) {
		//small zone
	} else {
		//large zone
	}


}
