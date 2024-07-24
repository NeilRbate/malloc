#ifndef __MALLOC__
#define __MALLOC__


/*********************************************************************
 *                                                                   *
 *                                                                   *
 *								     *      *                                                                   *
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


//Memory_page
typedef struct {

	short	is_allocated;
	uint	alloc_size;
	void	*alloc_ptr;

}	memory_page;

//Memory_struct
typedef	struct {

	short	is_init;
	short	page_quantity;

	uint	tiny_sysconf; 
	uint	tiny_page_size;
	uint	tiny_length;

	uint	small_sysconf; 
	uint	small_page_size;
	uint	small_length;



	void	*tiny_ptr;

	void	*small_ptr;

	size_t	large_size;
	memory_page *large;

}	memory_struct;

extern	memory_struct mmstruct;

/*
 * Malloc Prototype
 */
void
*malloc(size_t size);

/*
 * Init memory structure and page
 */
int	
init_memory_page();


void
show_alloc_mem();


/******************************TOOLS*********************************/

#endif
