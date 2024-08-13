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

#define TINY_BLOCK_SIZE		256
#define	SMALL_BLOCK_SIZE	1024

#define TINY_BLOCK_COUNT	116
#define SMALL_BLOCK_COUNT	125


/******************************PROTO*********************************/

typedef struct {
	uint64_t	block_ptr;
	void		*next;
	size_t		size;
}	s_ptr;

typedef struct small_zone {
	void		*block_ptr[SMALL_BLOCK_COUNT];
	uint64_t		size[SMALL_BLOCK_COUNT];
	struct small_zone	*next;
} small_zone_ptr;

typedef struct tiny_zone {
	void		*block_ptr[TINY_BLOCK_COUNT];
	uint64_t		size[TINY_BLOCK_COUNT];
	struct tiny_zone	*next;
} tiny_zone_ptr;

//Memory_struct
typedef	struct {

	short	is_init;

	struct rlimit	rlim;

	uint	tiny_length;
	uint64_t	tiny_max;

	uint	small_length;
	uint64_t	small_max;

	tiny_zone_ptr	*tiny_ptr;
	small_zone_ptr	*small_ptr;
	s_ptr	*large_ptr;

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


tiny_zone_ptr	
*init_tiny();

small_zone_ptr
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
s_ptr
*get_last_alloc();

/*
 * Return number of block allocated per zone
 */
size_t	
get_alloc_number(s_ptr *alloc);


/******************************TOOLS*********************************/

#endif
