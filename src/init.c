#include "../include/include.h"

small_zone_ptr
*init_small()
{

	void		*small = NULL;
	small_zone_ptr	*header = NULL;
	uint64_t	i = 0, block_start = 0;

	getrlimit(RLIMIT_DATA, &mmstruct.rlim);
    	if (mmstruct.small_length > mmstruct.rlim.rlim_max)
        	goto failure;

	small = mmap(NULL, mmstruct.small_length, 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);


	if (small == MAP_FAILED)
		goto failure;

	header = (small_zone_ptr *)small;
	header->next = NULL;
	block_start += (uint64_t)header + 3072;
	while (i < 125) {
		header->block_ptr[i] = (void *)block_start;
		block_start += SMALL_BLOCK_SIZE;
		i++;
	}

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
	block_start = (uint64_t)current + (((uint64_t)STRUCT_SIZE * 116) + 32);
	while (i < 116) {
		current->block_ptr = block_start;
		current->next = (void *)((uint64_t)current) + (uint64_t)STRUCT_SIZE;
		block_start += TINY_BLOCK_SIZE;
		i++;
		if (i < 116)
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
	mmstruct.tiny_length = (sysconf(_SC_PAGESIZE) * 8); //256Bytes blocks 
							   //116 Blocks 29696 Bytes
							   //116 s_ptr 2784 Bytes
							   //32768 Bytes allocated
							   //8 Pages reclaimed
	mmstruct.tiny_block_size = (uint64_t)TINY_BLOCK_SIZE;


	mmstruct.small_length = (sysconf(_SC_PAGESIZE) * 32); 
									 //1024Bytes blocks
							     //125 Blocks 128000 Bytes
							     //125 s_ptr = 3000 Bytes
							     //32 pages reclaimed
	mmstruct.small_block_size = (uint64_t)SMALL_BLOCK_SIZE;

	mmstruct.tiny_ptr = NULL;
	mmstruct.small_ptr = NULL;
	mmstruct.large_ptr = NULL; 
	mmstruct.is_init = IS_INIT;

	return SUCCESS;
}
