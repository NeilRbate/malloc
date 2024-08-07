#include "../include/include.h"

s_ptr
*init_small()
{

	void		*small;
	uint64_t	i = 1, block_start = 0;
	s_ptr		*current;

	getrlimit(RLIMIT_DATA, &mmstruct.rlim);
    	if (mmstruct.small_length > mmstruct.rlim.rlim_max)
        	goto failure;

	small = mmap(NULL, mmstruct.small_length, 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);

	if (small == MAP_FAILED)
		goto failure;

	current = (s_ptr *)small;
	block_start = (uint64_t)current + sizeof(s_ptr) * 101;
	while (i <= 100) {
		current->block_ptr = block_start;
		current->size = 0;
		current->next = (void *)((uint64_t)current) + sizeof(s_ptr);
		block_start += SMALL_BLOCK_SIZE;
		i++;
		if (i <= 100)
			current = current->next;
	}

	current->next = NULL;

	return small;

failure:
	return ALLOC_FAILURE;
}

s_ptr
*init_tiny()
{
	void		*tiny;
	uint64_t	i = 1, block_start = 0;
	s_ptr		*current;

	getrlimit(RLIMIT_DATA, &mmstruct.rlim);
    	if (mmstruct.tiny_length > mmstruct.rlim.rlim_max)
        	goto failure;

	if(mmstruct.rlim.rlim_max < mmstruct.tiny_length)
		goto failure;

	tiny = mmap(NULL, mmstruct.tiny_length, 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);

	if (tiny == MAP_FAILED)
		goto failure;

	current = (s_ptr *)tiny;
	block_start = (uint64_t)current + sizeof(s_ptr) * 101;
	while (i <= 100) {
		current->block_ptr = block_start;
		current->size = 0;
		current->next = (void *)((uint64_t)current) + sizeof(s_ptr);
		block_start += TINY_BLOCK_SIZE;
		i++;
		if (i <= 100)
			current = current->next;
	}

	current->next = NULL;

	return tiny;

failure:
	return ALLOC_FAILURE;
}

int
init_mmstruct()
{	

	if (getrlimit(RLIMIT_DATA, &mmstruct.rlim) != 0)
		return INIT_FAILURE;

	mmstruct.tiny_sysconf = sysconf(_SC_PAGESIZE) * 7; //256Bytes blocks 
							   //100 Blocks per allocations + 100 s_ptr
							   //28672 Bytes allocated
							   //7 Pages reclaimed
	mmstruct.tiny_length = mmstruct.tiny_sysconf;
	mmstruct.tiny_block_size = (uint64_t)TINY_BLOCK_SIZE + (uint64_t)sizeof(s_ptr);


	mmstruct.small_sysconf = sysconf(_SC_PAGESIZE) * 26; //1024Bytes blocks
							     //100 Blocks per allocations + 100 s_ptr
							     //106496 Bytes allocated
							     //26 pages reclaimed
	mmstruct.small_length = mmstruct.small_sysconf;
	mmstruct.small_block_size = (uint64_t)SMALL_BLOCK_SIZE + (uint64_t)sizeof(s_ptr);

	mmstruct.tiny_ptr = NULL;
	mmstruct.small_ptr = NULL;
	mmstruct.large_ptr = NULL; 
	mmstruct.is_init = IS_INIT;

	return SUCCESS;
}
