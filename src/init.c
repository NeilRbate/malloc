#include "../include/include.h"

s_ptr
*init_small()
{
	void	*small;
	uint64_t	i = 0;

	if(mmstruct.rlim.rlim_max < mmstruct.small_length)
		goto failure;

	small = mmap(NULL, mmstruct.small_length,
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);

	if (small == MAP_FAILED)
		goto failure;

	while (i < mmstruct.small_length) {
		if (((small + i) + mmstruct.small_page_size) 
				>= small + mmstruct.small_length)
			((s_ptr *)(small + i))->next = NULL;
		else
			((s_ptr *)(small + i))->next = (small + i) + mmstruct.small_page_size;
		for(int j = 0; j < 16; j++) 
			((s_ptr *)(small + i))->block[j] = 0;
		i += mmstruct.small_page_size;
	}

	return small;

failure:
	return ALLOC_FAILURE;
}

s_ptr
*init_tiny()
{
	void	*tiny;
	uint64_t	i = 0;

	if(mmstruct.rlim.rlim_max < mmstruct.tiny_length)
		goto failure;

	tiny = mmap(NULL, mmstruct.tiny_length, 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);

	if (tiny == MAP_FAILED)
		goto failure;

	while (i < mmstruct.tiny_length) {
		if (((tiny + i) + mmstruct.tiny_page_size) 
				>= tiny + mmstruct.tiny_length)
			((s_ptr *)(tiny + i))->next = NULL;
		else
			((s_ptr *)(tiny + i))->next = (tiny + i) + mmstruct.tiny_page_size;
		for(int j = 0; j < 16; j++) 
			((s_ptr *)(tiny + i))->block[j] = 0;
		i += mmstruct.tiny_page_size;
	}

	return tiny;

failure:
	return ALLOC_FAILURE;

}

int
init_mmstruct()
{	

	if (getrlimit(RLIMIT_DATA, &mmstruct.rlim) != 0)
		return INIT_FAILURE;

	mmstruct.tiny_sysconf = sysconf(_SC_PAGESIZE) * 4;
	mmstruct.tiny_page_size = mmstruct.tiny_sysconf + sizeof(s_ptr);
	mmstruct.tiny_length = mmstruct.tiny_page_size * 100;

	mmstruct.small_sysconf = sysconf(_SC_PAGESIZE) * 16;
	mmstruct.small_page_size = mmstruct.small_sysconf + sizeof(s_ptr);
	mmstruct.small_length = mmstruct.small_page_size * 100;

	mmstruct.tiny_ptr = NULL;
	mmstruct.small_ptr = NULL;
	mmstruct.large_ptr = NULL; 
	mmstruct.is_init = IS_INIT;

	return SUCCESS;
}
