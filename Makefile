CC = gcc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -g

HOST = $(HOSTTYPE)

ifeq ($(HOSTTYPE),)
HOST := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_${HOST}.so

LINKNAME = libft_malloc.so

SRCS = src/malloc.c \
       src/init.c \
       src/tools.c \
       src/largealloc.c \
       src/free.c \
       src/realloc.c \
       src/calloc.c \
       src/memory_dump.c

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
	@make -C libft clean
	@rm -f test

fclean: clean
	@rm -f ${NAME}
	@rm -f ${LINKNAME}
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
