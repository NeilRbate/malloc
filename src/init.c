#include "../include/include.h"

s_ptr
*init_small()
{
	void		*small;
	uint64_t	i = 0, block_start = 0;
	s_ptr		*current;

	getrlimit(RLIMIT_DATA, &mmstruct.rlim);
    	if (mmstruct.small_length > mmstruct.rlim.rlim_max)
        	goto failure;

	small = mmap(NULL, mmstruct.small_length, 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);


	if (small == MAP_FAILED)
		goto failure;

	current = (s_ptr *)small;
	block_start = (uint64_t)current + (sizeof(s_ptr)  * 100) + 1;
	while (i < 100) {
		current->block_ptr = block_start;
		current->size = 0;
		current->next = (void *)((uint64_t)current) + sizeof(s_ptr);
		block_start += SMALL_BLOCK_SIZE;
		i++;
		if (i < 100)
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
	uint64_t	i = 0, block_start = 0;
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
	block_start = (uint64_t)current + (sizeof(s_ptr) * 120) + 1;
	while (i < 120) {
		current->block_ptr = block_start;
		current->size = 0;
		current->next = (void *)((uint64_t)current) + sizeof(s_ptr);
		block_start += TINY_BLOCK_SIZE;
		i++;
		if (i < 120)
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

	mmstruct.tiny_sysconf = sysconf(_SC_PAGESIZE) * 8; //256Bytes blocks 
							   //120 Blocks 30720Bytes
							   //120 s_ptr + align = 3840
							   //32768 Bytes allocated
							   //34560 Bytes used
							   //8 Pages reclaimed
	mmstruct.tiny_length = mmstruct.tiny_sysconf;
	mmstruct.tiny_block_size = (uint64_t)TINY_BLOCK_SIZE;


	mmstruct.small_sysconf = sysconf(_SC_PAGESIZE) * 26; //1024Bytes blocks
							     //100 Blocks 102400Bytes
							     //100 s_ptr  = 2400
							     //106496 Bytes allocated
							     //105600 Bytes used
							     //26 pages reclaimed
	mmstruct.small_length = mmstruct.small_sysconf;
	mmstruct.small_block_size = SMALL_BLOCK_SIZE;

	mmstruct.tiny_ptr = NULL;
	mmstruct.small_ptr = NULL;
	mmstruct.large_ptr = NULL; 
	mmstruct.is_init = IS_INIT;

	return SUCCESS;
}
//281.25 pages pour 1024 alloc ->
