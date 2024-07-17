#ifndef __MALLOC__
#define __MALLOC__


/*********************************************************************
 *                                                                   *
 *                                                                   *
 *								     *                     *
 *		        	MALLOC 				     *
 *                                                                   *
 *                                                                   *
 *                                                                   *
 ********************************************************************/ 

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

#define TINY_SIZE	sysconf(_SC_PAGESIZE)
#define TINY_LENGTH	TINY_SIZE * 150
#define SMALL_SIZE	sysconf(_SC_PAGESIZE) * 10
#define SMALL_LENGTH	SMALL_SIZE * 150

#define SUCCESS	0xff


#define MALLOC_FAIL	NULL
#define INIT_FAILURE	1 << 3
#define ALLOC_FAILURE	NULL

#define NOT_ALLOCATED 1 << 1
#define IS_ALLOCATED 1 << 2
#define IS_INIT 1 << 8



/******************************PROTO*********************************/


//Memory_page
typedef struct {

	unsigned short	is_allocated;
	size_t	alloc_size;
	size_t	alloc_ndx;
	void	*alloc_ptr;

}	memory_page;

//Memory_struct
typedef	struct {

	size_t	is_init;
	size_t	tiny_size;
	void	*tiny_ptr;
	memory_page *tiny;

	size_t	small_size;
	void	*small_ptr;
	memory_page *small;

	size_t	large_size;
	memory_page *large;

}	memory_struct;


/*
 * Malloc Prototype
 */
void
*malloc(size_t size);

/*
 * Init memory structure and page
 */
int	
init_memory_page(memory_struct *mmstruct);


#endif
