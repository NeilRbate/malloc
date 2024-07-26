#include "../include/include.h"

static int
fill_mempage()
{
	ft_memset(mmstruct.tiny_ptr, 0, mmstruct.tiny_length);	

	ft_memset(mmstruct.small_ptr, 0, mmstruct.small_length);	

	return SUCCESS;
}

static int	
init_mmap()
{
	void	*tiny, *small;

	if(mmstruct.rlim.rlim_max < (mmstruct.tiny_length + mmstruct.small_length))
		goto failure;

	tiny = mmap(NULL, mmstruct.tiny_length, 
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);

	if (tiny == MAP_FAILED)
		goto failure;

	small = mmap(NULL, mmstruct.small_length,
			PROT_READ | PROT_WRITE , 
			MAP_PRIVATE | MAP_ANON, -1, 0);

	if (small == MAP_FAILED) {
		munmap(tiny, mmstruct.tiny_length);
		goto failure;
	}

	mmstruct.tiny_ptr = tiny;
	mmstruct.small_ptr = small;
	mmstruct.tiny_ptr = tiny;
	mmstruct.small_ptr = small;
			

	return SUCCESS;

failure:
	return INIT_FAILURE;

}

static int
init_mmstruct()
{	

	if (getrlimit(RLIMIT_DATA, &mmstruct.rlim) != 0)
		return INIT_FAILURE;

	mmstruct.page_quantity = 100;

	mmstruct.tiny_sysconf = sysconf(_SC_PAGESIZE) * 4;
	mmstruct.tiny_page_size = mmstruct.tiny_sysconf + sizeof(uint64_t);
	mmstruct.tiny_length = mmstruct.tiny_page_size * mmstruct.page_quantity;

	mmstruct.small_sysconf = sysconf(_SC_PAGESIZE) * 16;
	mmstruct.small_page_size = mmstruct.small_sysconf + sizeof(uint64_t);
	mmstruct.small_length = mmstruct.small_page_size * mmstruct.page_quantity;	

	return SUCCESS;
}

int	
init_memory_page()
{
	//Init mmap for tiny and small
	if (init_mmstruct() == INIT_FAILURE)
		goto failure;
	if (init_mmap() == INIT_FAILURE)
		goto failure;
	//if (init_mempage() == INIT_FAILURE)
	//	goto failure;
	if (fill_mempage() == INIT_FAILURE)
		goto failure;

	mmstruct.is_init = IS_INIT;
	mmstruct.large_ptr = NULL; 

	return SUCCESS;

failure:
	return INIT_FAILURE;
}
