#include "../include/include.h"

void
*large_mmap(size_t size)
{
	void	*mmap_ptr = NULL;
	s_ptr	*large;
	mmap_ptr = mmap(NULL, size + (sizeof(s_ptr) + 8), 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);

	if (mmap_ptr == MAP_FAILED)
		goto failure;

	large = (s_ptr *)mmap_ptr;
	large->block_ptr = ((uint64_t)mmap_ptr) + (sizeof(s_ptr) + 8);
	large->next = NULL;
	large->size = size;

	return mmap_ptr;
failure:
	return ALLOC_FAILURE;
}
