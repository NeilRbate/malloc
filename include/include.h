#ifndef __MALLOC__
#define __MALLOC__


/*********************************************************************
 *                                                                   *
 *                                                                   *
 *								                                                   *
 *				                      MALLOC 				                       *
 *                                                                   *
 *                                                                   *
 *                                                                   *
 ********************************************************************/ 

/******************************INCLUDE ZONE**************************/

//For mmap and munmap
#include <sys/mman.h>

//For getrlimit
#include <sys/time.h>
#include <sys/resource.h>

//For sysconf
#include <unistd.h>

//For libft
#include "../libft/libft.h"

#include <pthread.h>


/******************************DEFINE ZONE***************************/

#define TINY_SIZE	10000
#define SMALL_SIZE	10000
#define	LARGE_SIZE	10000

#define NOT_ALLOCATED 1 << 1
#define IS_ALLOCATED 1 << 2


/******************************PROTO*********************************/

//TINY size struct
typedef struct {

	unsigned short	is_allocated;

	size_t	alloc_size;
	size_t	alloc_ndx;

	void	*alloc_ptr;

}	alloc_array;

void*
malloc(size_t size);

#endif
