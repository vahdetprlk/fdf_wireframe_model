NAME	= libgetnextline.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g

FILES	= get_next_line.c \
		  get_next_line_utils.c

OBJ		= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rc $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
