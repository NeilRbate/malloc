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
#define ALLOC_FAILURE	NULL

#define NOT_ALLOCATED 0
#define IS_ALLOCATED 1 << 32
#define IS_INIT 1 << 1
#define INIT_FAILURE	1 << 2

#define	STRUCT_SIZE		sizeof(l_ptr)
#define TINY_BLOCK_SIZE		256
#define	SMALL_BLOCK_SIZE	1024


/******************************PROTO*********************************/

//Large allocation struct
typedef struct {

	uint64_t	size;
	void		*next;
	void		*alloc_ptr;

}	l_ptr;

typedef struct {
	uint64_t	block_ptr;
	void		*next;
	size_t		size;
}	s_ptr;

//Memory_struct
typedef	struct {

	short	is_init;

	struct rlimit	rlim;

	uint	tiny_sysconf; 
	uint	tiny_block_size;
	uint	tiny_length;
	uint64_t	tiny_max;

	uint	small_sysconf; 
	uint	small_block_size;
	uint	small_length;
	uint64_t	small_max;

	s_ptr	*tiny_ptr;
	s_ptr	*small_ptr;
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
void	
free(void *ptr);


s_ptr	
*init_tiny();

s_ptr
*init_small();

int
init_mmstruct();

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
