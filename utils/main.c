#include "../include/include.h"

int main() 
{
	char	*ptr, *ptr1, *tiny, *small, *large;


	/*
	ft_printf("\n====== Test page usage() ======\n\n");

	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
	struct rusage r_usage;
 	getrusage(RUSAGE_SELF,&r_usage);
  	ft_printf("Memory usage: %u kilobytes  %u page reclaims\n",
			r_usage.ru_maxrss,
			r_usage.ru_minflt);
	*/

	/*
	ft_printf("\n====== Test malloc() ======\n\n");

	tiny = malloc(256);
	small = malloc(1024);
	large = malloc(50000);
	show_alloc_mem();
	*/



	/*
	ft_printf("\n====== Test free() ======\n\n");
	ft_printf("=== Alloc 3 ptr for the 3 zones ===\n");

	tiny = malloc(256);
	small = malloc(1024);
	large = malloc(50000);
	show_alloc_mem();

	ft_printf("=== free() the 3 ptr ===\n");
	free(tiny);
	free(small);
	free(large);
	show_alloc_mem();

	ft_printf("=== free() invalid ptr ===\n");
	free(large);
	*/

	/*
	ft_printf("\n====== Test realloc() ======\n\n");
	ft_printf("=== Realloc 8 bytes to 1024 bytes zone ===\n");
	ptr = malloc(8);
	ft_strlcpy(ptr,"barbate", 8);
	ptr1 = realloc(ptr, 1024);
	ptr1[10] = 'U';
	show_alloc_mem();
	ft_printf("=== Realloc 1024 bytes to 2048 bytes zone ===\n");
	ptr = realloc(ptr1, 2048);
	show_alloc_mem();
	ft_printf("=== Realloc 2048 bytes to 1024 bytes zone ===\n");
	ptr1 = realloc(ptr, 1024);
	show_alloc_mem();
	ft_printf("=== Realloc 1024 bytes to 16 bytes zone ===\n");
	ptr = realloc(ptr1, 16);
	show_alloc_mem();
	show_memory_dump(ptr);
	*/
/*


	ft_printf("\n====== Test show_alloc_mem() ======\n\n");
	tiny = malloc(256);
	small = malloc(1024);
	large = malloc(2048);
	show_alloc_mem();
	free(tiny);
	free(small);
	free(large);


	ft_printf("\n====== Test show_memory_dump() ======\n\n");
	ft_printf("=== alloc 1024 bytes and put alpha on it ===\n");
	ptr = malloc(1024);
	for(int i = 0; i < 1024; i++)
		ptr[i] = (i % 26) + 'A';
	show_memory_dump(ptr);
	secure_free(ptr);


	ft_printf("\n====== Test secure_free() ======\n\n");
	ptr = malloc(26);
	for(int i = 0; i < 26; i++)
		ptr[i] = i + 'a';
	ft_printf("=== alloc 26 bytes and put alpha on it ===\n");
	show_memory_dump(ptr);
	ft_printf("=== free() ptr and alloc new ptr (take same memory space) ===\n");
	free(ptr);
	ptr = malloc(24);
	ft_printf("=== show ptr content ===\n");
	show_memory_dump(ptr);
	ft_printf("=== secure_free() ptr and alloc new ptr (take same memory space) ===\n");
	secure_free(ptr);
	ptr = malloc(24);
	show_memory_dump(ptr);
	free(ptr);
	
	ft_printf("\n====== Test calloc() ======\n\n");
	ft_printf("=== alloc 26 bytes and put alpha on it ===\n");
	ptr = calloc(26, sizeof(char));
	for(int i = 0; i < 26; i++)
		ptr[i] = i + 'a';
	show_memory_dump(ptr);
	ft_printf("=== free() ptr and alloc new ptr with same memory emplacement ===\n");
	free(ptr);
	ptr = calloc(26, sizeof(char));
	show_memory_dump(ptr);
	free(ptr);
	*/
	return 0;

}
