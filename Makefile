CC = gcc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -g

HOST = $(HOSTTYPE)

ifeq ($(HOSTTYPE),)
HOST := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_${HOST}.so

LINKNAME = libft_malloc.so


MAIN = utils/main.c

SRCS = src/malloc.c \
       src/init.c \
       src/tools.c \
       src/largealloc.c \
       src/free.c \
       src/realloc.c \
       src/calloc.c \
       src/memory_dump.c \
			 src/log.c

LIBFT = -L. libft/libft.a

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c -fPIC $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@make -C libft all
	${CC} -shared ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}
	ln -s ${NAME} ${LINKNAME}


clean:
	@rm -f ${OBJS}
	@rm -f utils/main.o
	@make -C libft clean
	@rm -f test

fclean: clean
	@rm -f ${NAME}
	@rm -f ${LINKNAME}
	@make -C libft fclean

re: fclean test #all

test:	all
	${CC} -g -o test ${MAIN} ${LIBFT} -Wl,-rpath=./ft_malloc -lft_malloc

.PHONY: all clean fclean re
