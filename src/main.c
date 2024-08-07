#include "../include/include.h"
#include <stdio.h>
int	main()
{
	char *str;
	int i = 0;
	while (i < 1024)
	{
		str = (char*)malloc(1024);
		str[0] = 42;

		i++;
	}
	struct rusage r_usage;
 	getrusage(RUSAGE_SELF,&r_usage);
  	printf("Memory usage: %ld kilobytes  %ld page reclaims\n",
			r_usage.ru_maxrss, 
			r_usage.ru_minflt);
}
