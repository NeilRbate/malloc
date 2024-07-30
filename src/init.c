#include "../include/include.h"

static int
fill_mempage()
{
	ft_bzero(mmstruct.tiny_ptr, mmstruct.tiny_length);
	ft_bzero(mmstruct.small_ptr, mmstruct.small_length);

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

	mmstruct.small_ptr = small;
	mmstruct.small_max = (uint64_t)((char *)small + mmstruct.small_length);

	mmstruct.tiny_ptr = tiny;
	mmstruct.tiny_max = (uint64_t)((char *)tiny + mmstruct.tiny_length);

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

	mmstruct.tiny_sysconf = sysconf(_SC_PAGESIZE) * 4; // 4 * 4096 = 16384 Bytes
	mmstruct.tiny_page_size = mmstruct.tiny_sysconf + sizeof(uint64_t); // 16384 + 8 = 16392 Bytes
	mmstruct.tiny_length = mmstruct.tiny_page_size * mmstruct.page_quantity;// 1639200 Bytes

	mmstruct.small_sysconf = sysconf(_SC_PAGESIZE) * 16; // 16 * 4096 = 65536 Bytes
	mmstruct.small_page_size = mmstruct.small_sysconf + sizeof(uint64_t); // 65536 + 8 = 65544 Bytes
	mmstruct.small_length = mmstruct.small_page_size * mmstruct.page_quantity;// 6554400 Bytes

	return SUCCESS;
}

int	
init_memory_page()
{
	//Init mmap for tiny and small allocation
	if (init_mmstruct() == INIT_FAILURE)
		goto failure;
	if (init_mmap() == INIT_FAILURE)
		goto failure;
	if (fill_mempage() == INIT_FAILURE)
		goto failure;

	mmstruct.is_init = IS_INIT;
	mmstruct.large_ptr = NULL; 

	return SUCCESS;

failure:
	return INIT_FAILURE;
}
