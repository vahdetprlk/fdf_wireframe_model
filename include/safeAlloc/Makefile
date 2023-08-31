CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.

SRCS = safeAlloc.c
OBJS = $(SRCS:%.c=%.o)
NAME = libsafeAlloc.a

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rc $(NAME) $(OBJS)


clean:
	@rm -rf $(OBJS)

fclean:
	@rm -rf $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
