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

//For memory_dump
#include <stdio.h>

//For log file (open + time)
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



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
#define	TINY_FLAG	1 << 0
#define	SMALL_FLAG	1 << 1
#define	LARGE_FLAG	1 << 2
#define	NO_ZONE		1 << 3
#define	TINY_ZONE	1 << 4
#define SMALL_ZONE	1 << 5
#define LARGE_ZONE	1 << 6
#define	ALL_ZONE	1 << 7
#define MALLOC	1 << 0
#define CALLOC	1 << 1
#define REALLOC 1 << 2
#define FREE    1 << 3
#define SECURE_FREE 1 << 4

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

typedef	struct {
	short	zone;
	size_t	size;
	void	*ptr;
	void	*header;
	int	ndx;
}	alloc_zone;

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

/* GLOBAL */
extern	memory_struct	mmstruct;
extern	pthread_mutex_t    mutex;

/*
 * Malloc Prototype
 */
void
*malloc(size_t size);

/*
 * no thread-safe malloc, using with realloc because realloc is thread-safe
 */
void
*thread_malloc(size_t size);


/*
 * Free Prototype
 */
void	
free(void *ptr);

/*
 * no thread safe free, using with realloc because realloc is thread-safe
 */
void
thread_free(void *ptr);

/*
 * realloc prototype
 */
void	
*realloc(void *ptr, size_t size);

/*
 * Calloc bonus 
 */
void
*calloc(size_t nmemb, size_t size);

/*
 * Show memory block in hexa
 */
void
show_memory_dump(void *ptr);

/*
 * Erase all data on ptr and free them, it's a secure process 
 * who destroy the possibility to reed data from freed pointer
 */
void
secure_free(void *ptr);

/*
 * Create log file and add informations for each actions
 */
void	
write_log(char * options, short process, size_t size);





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

/*
 * Find the zone of ptr
 */
alloc_zone
find_alloc_zone(void *ptr);



/******************************TOOLS*********************************/

#endif
