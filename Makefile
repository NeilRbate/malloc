CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

HOST = $(HOSTTYPE)

ifeq ($(HOSTTYPE),)
HOST := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_${HOST}.so

LINKNAME = libft_malloc.so

SRCS = src/malloc.c \
       src/init.c

MAIN = src/main.c

LIBFT = -L. libft/libft.a 

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c -fpic $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@make -C libft all
	${CC} -shared ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}
	ln -s ${NAME} ${LINKNAME}


clean:
	@rm -f ${OBJS}
	@rm -f src/main.o
	@make -C libft clean
	@rm -f test

fclean: clean
	@rm -f ${NAME}
	@rm -f ${LINKNAME}
	@make -C libft fclean

re: fclean all

test:	
	${CC} -L/libft_malloc ${CFLAGS} -o test ${MAIN} ${LIBFT}  -L/libft_malloc	

.PHONY: all clean fclean re
