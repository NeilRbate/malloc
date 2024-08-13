#include "../include/include.h"

small_zone_ptr
*init_small()
{

	small_zone_ptr	*header = NULL;
	uint64_t	i = 0, block_start = 0;

    	if (mmstruct.small_length > mmstruct.rlim.rlim_max)
        	goto failure;

	header = (small_zone_ptr *)mmap(NULL, mmstruct.small_length, 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);

	if (header == MAP_FAILED)
		goto failure;

	header->next = NULL;
	block_start = (uint64_t)header + sizeof(small_zone_ptr) + 40;
	while (i < SMALL_BLOCK_COUNT) {
		header->block_ptr[i] = (void *)block_start;
		header->size[i] = NOT_ALLOCATED;
		block_start += (uint64_t)SMALL_BLOCK_SIZE;
		i++;
	}

	return header;

failure:
	return ALLOC_FAILURE;
}

tiny_zone_ptr
*init_tiny()
{

	tiny_zone_ptr	*header = NULL;
	uint64_t	i = 0, block_start = 0;

    	if (mmstruct.tiny_length > mmstruct.rlim.rlim_max)
        	goto failure;

	header = (tiny_zone_ptr *)mmap(NULL, mmstruct.tiny_length, 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);


	if (header == MAP_FAILED)
		goto failure;

	header->next = NULL;
	block_start = (uint64_t)header + sizeof(tiny_zone_ptr) + 184;
	while (i < TINY_BLOCK_COUNT) {
		header->block_ptr[i] = (void *)block_start;
		header->size[i] = NOT_ALLOCATED;
		block_start += TINY_BLOCK_SIZE;
		i++;
	}

	return header;

failure:
	return ALLOC_FAILURE;


}

int
init_mmstruct()
{	
	mmstruct.tiny_length = (sysconf(_SC_PAGESIZE) * 8); //256Bytes blocks 
	mmstruct.small_length = (sysconf(_SC_PAGESIZE) * 32);  //1024Bytes blocks
							       
	mmstruct.tiny_ptr = NULL;
	mmstruct.small_ptr = NULL;
	mmstruct.large_ptr = NULL; 
	mmstruct.is_init = IS_INIT;

	return SUCCESS;
}
