CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

HOST = $(HOSTTYPE)

ifeq ($(HOSTTYPE),)
HOST := $(shell uname -m)_$(shell uname -s)
endif


NAME = libft_malloc_${HOST}.so

SRCS = src/main.c

#gcc -shared -o libhello.so -fPIC hello.c
LIBFT = -L. libft/libft.a 

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@make -C libft all
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -shared -o ${NAME}


clean:
	@rm -f ${OBJS}
	@make -C libft clean

fclean: clean
	@rm -f ${NAME}
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
