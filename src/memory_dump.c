#include "../include/include.h"

void memory_dump(void *addr, int len)
{
	int i;
	char buffer[17];
	char *pc = (char*)addr;

	for(i = 0; i < len; i++) {
		if ((i % 16) == 0) {
			if (i != 0)
				printf("  %s\n", buffer);

			printf("  %04x ", i);
		}

		printf(" %02x", pc[i]);

		if ((pc[i] < 0x20) || (pc[i] > 0x7e))
			buffer[i % 16] = '.';
		else
			buffer[i % 16] = pc[i];
		buffer[(i % 16) + 1] = '\0';
	}

	while((i % 16) != 0) {
		printf("   ");
		i++;
	}

	printf("  %s\n", buffer);
}

void
show_memory_dump(void *ptr)
{
	if (mmstruct.is_init != IS_INIT || !ptr)
		return;

	alloc_zone	zone = find_alloc_zone(ptr);
	if (zone.zone == NO_ZONE)
		return;
	memory_dump(zone.ptr, zone.size);
	
}
