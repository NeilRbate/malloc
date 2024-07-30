#ifndef __MALLOC__
#define __MALLOC__

/*********************************MALLOC*****************************/

/******************************INCLUDE ZONE**************************/

//For libft
#include "../libft/libft.h"

//For thread
#include <pthread.h>

//For mmap and munmap
#include <sys/mman.h>

//For getrlimit
#include <sys/time.h>
#include <sys/resource.h>

//For sysconf
#include <unistd.h>


/******************************DEFINE ZONE***************************/

#define	STDOUT	1
#define	STDERR	2

#define SUCCESS	0xff
#define FAILURE 0xDEAD

#define MALLOC_FAIL	NULL
#define INIT_FAILURE	1 << 3
#define ALLOC_FAILURE	NULL

#define NOT_ALLOCATED 0
#define IS_ALLOCATED 1 << 0
#define IS_INIT 1 << 8

/******************************PROTO*********************************/

//Large allocation struct
typedef struct {

	void	*alloc_ptr;
	void	*next;
	size_t	size;

}	l_ptr;

//Memory_struct
typedef	struct {

	short	is_init;
	short	page_quantity;

	struct rlimit	rlim;

	uint	tiny_sysconf; 
	uint	tiny_page_size;
	uint	tiny_length;
	uint64_t	tiny_max;

	uint	small_sysconf; 
	uint	small_page_size;
	uint	small_length;
	uint64_t	small_max;

	void	*tiny_ptr;
	void	*small_ptr;

	l_ptr	*large_ptr;

}	memory_struct;

extern	memory_struct	mmstruct;

/*
 * Malloc Prototype
 */
void
*malloc(size_t size);

/*
 * Free Prototype
 */
/*
void	
free(void *ptr);
*/


/*
 * Init memory structure and page
 */
int	
init_memory_page();

/*
 * Display allocation zone memory address and map
 */
void
show_alloc_mem();

/*
 * Alloc memory for large zone
 */
void
*large_mmap(size_t size);

/*
 * Return last allocation struct on large zone
 */
l_ptr
*get_last_alloc();


/******************************TOOLS*********************************/

#endif
