#include "../include/include.h"
#include <stdio.h>

void memory_dump(void *addr, int len)
{
	int i;
	unsigned char buffer[17];
	unsigned char *pc = (unsigned char*)addr;

	for (i = 0; i < len; i++) {
		if ((i % 16) == 0) {
			if (i != 0)
				printf ("  %s\n", buffer);

			printf ("  %04x ", i);
		}

		printf (" %02x", pc[i]);

		if ((pc[i] < 0x20) || (pc[i] > 0x7e))
			buffer[i % 16] = '.';
		else
			buffer[i % 16] = pc[i];
		buffer[(i % 16) + 1] = '\0';
	}

	while ((i % 16) != 0) {
		printf ("   ");
		i++;
	}

	printf ("  %s\n", buffer);
}

static void
select_small_memory()
{
	uint64_t i = 0;
	small_zone_ptr	*ptr = mmstruct.small_ptr;

	if (mmstruct.small_ptr == NULL)
		return;

	while (i < SMALL_BLOCK_COUNT) {
		if (ptr->size[i] != NOT_ALLOCATED) {
			if (i == 0)
				ft_printf("SMALL:\n");
			ft_printf("%p\n", ptr->block_ptr[i]);
			memory_dump(ptr->block_ptr[i], ptr->size[i]);
		}
		i++;
		if (i == SMALL_BLOCK_COUNT && ptr->next != NULL) {
			i = 0;
			ptr = ptr->next;
		}
	}
}

static void
select_tiny_memory()
{
	int i = 0;
	tiny_zone_ptr	*ptr = mmstruct.tiny_ptr;

	if (mmstruct.tiny_ptr == NULL)
		return;

	while (i < TINY_BLOCK_COUNT) {
		if (ptr->size[i] != NOT_ALLOCATED) {
			if (i == 0)
				ft_printf("TINY :\n");
			ft_printf("%p\n", ptr->block_ptr[i]);
			memory_dump(ptr->block_ptr[i], ptr->size[i]);
		}
		i++;
		if (i == TINY_BLOCK_COUNT && ptr->next != NULL) {
			i = 0;
			ptr = ptr->next;
		}

	}
}

	void
show_memory_dump(short zone_type)
{
	if (mmstruct.is_init != IS_INIT)
		return;

	switch(zone_type) {
		case TINY_ZONE:
			select_tiny_memory();
			break;
		case SMALL_ZONE:
			select_small_memory();
			break;
		case LARGE_ZONE:
			//select_large_memory(mmstruct.large_ptr)
			break;
	}
}
