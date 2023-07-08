NAME	= libft.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g

FILES	= $(shell find . -type f -name "ft_*.c")
OBJ		= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
