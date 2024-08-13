#include "../include/include.h"

static void
write_alloc(char *str, int fd, size_t size)
{
	ft_putstr_fd(str, fd);
	if (size != 0) {
		ft_putstr_fd(" ", fd);
		ft_putnbr_fd(size, fd);
		ft_putendl_fd(" Bytes", fd);
	} else {
		ft_putendl_fd("", fd);
	}
}

void	
write_log(short process, size_t size)
{

	int fd = open("log_file", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return;

	switch(process) {
		case MALLOC:
			write_alloc("malloc", fd, size);
			break;
		case CALLOC:
			write_alloc("calloc", fd, size);
			break;
		case REALLOC:
			write_alloc("realloc", fd, size);
			break;
		case FREE:
			write_alloc("free", fd, size);
			break;
		case SECURE_FREE:
			write_alloc("secure_free", fd, size);
			break;
	}

	close(fd);
}
