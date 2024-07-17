#include "../include/include.h"

static int
fill_mempage(memory_struct *mmstruct)
{
	//Fill tiny mem_page
	for (size_t i = 0; i < mmstruct->tiny_size; i++) {
		mmstruct->tiny[i].is_allocated = NOT_ALLOCATED;
		mmstruct->tiny[i].alloc_size = 0;
		mmstruct->tiny[i].alloc_ndx = i;
		mmstruct->tiny[i].alloc_ptr = mmstruct->tiny_ptr + (TINY_SIZE * i);
	}

	//Fill small mem_page
	for (size_t i = 0; i < mmstruct->small_size; i++) {
		mmstruct->small[i].is_allocated = NOT_ALLOCATED;
		mmstruct->small[i].alloc_size = 0;
		mmstruct->small[i].alloc_ndx = i;
		mmstruct->small[i].alloc_ptr = mmstruct->small_ptr + (SMALL_SIZE * i);
	}

	return SUCCESS;
}

static int
init_mempage(memory_struct *mmstruct)
{
	memory_page	*tiny, *small;

	tiny = mmap(NULL, sizeof(memory_page) 
			* mmstruct->tiny_size, 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);
	if (tiny == MAP_FAILED)
		goto failure;

	small = mmap(NULL, sizeof(memory_page) 
			* mmstruct->small_size, 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);
	if (small == MAP_FAILED) {
		munmap(tiny, sizeof(memory_page) 
			* mmstruct->tiny_size);
		goto failure;
	}

	mmstruct->tiny = tiny;
	mmstruct->small = small;

	return SUCCESS;

failure:
	return INIT_FAILURE;

}

static int	
init_mmap(memory_struct *mmstruct)
{
	void	*tiny, *small;

	tiny = mmap(NULL, TINY_LENGTH, 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);

	if (tiny == MAP_FAILED)
		goto failure;

	small = mmap(NULL, SMALL_LENGTH,
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);

	if (small == MAP_FAILED) {
		munmap(tiny, TINY_LENGTH);
		goto failure;
	}

	ft_printf("size of tiny -> %d\n", mmstruct->tiny_size);
	mmstruct->tiny_size = (TINY_LENGTH / sysconf(_SC_PAGESIZE));
	mmstruct->small_size = (SMALL_LENGTH / sysconf(_SC_PAGESIZE));
	mmstruct->tiny_ptr = tiny;
	mmstruct->small_ptr = small;

	return SUCCESS;

failure:
	return INIT_FAILURE;

}

int	
init_memory_page(memory_struct *mmstruct)
{
	//Init mmap for tiny and small
	if (init_mmap(mmstruct) == INIT_FAILURE)
		goto failure;
	if (init_mempage(mmstruct) == INIT_FAILURE)
		goto failure;
	if (fill_mempage(mmstruct) == INIT_FAILURE)
		goto failure;

	return SUCCESS;

failure:
	return INIT_FAILURE;
}
