#include "../include/include.h"

void
*large_mmap(size_t size)
{
	void	*mmap_ptr = NULL;
	l_ptr	*large_ptr;
	mmap_ptr = mmap(NULL, size + sizeof(l_ptr), 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);

	if (mmap_ptr == MAP_FAILED)
		goto failure;

	large_ptr = (l_ptr *)mmap_ptr;
	large_ptr->alloc_ptr = mmap_ptr + sizeof(l_ptr);
	large_ptr->next = NULL;
	large_ptr->size = size + sizeof(l_ptr);

	return mmap_ptr;
failure:
	return ALLOC_FAILURE;
}
