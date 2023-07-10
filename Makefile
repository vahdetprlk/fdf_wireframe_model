NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC =   src/fdf.c


OBJ =  $(SRC:.c=.o)

LIBFT_DIR = include/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

PRINTF_DIR = include/libftprintf
PRINTF = $(PRINTF_DIR)/libftprintf.a
PRINTF_INC = -I$(PRINTF_DIR)

LIBMLX_DIR = include/libmlx
LIBMLX = $(LIBMLX_DIR)/libmlx.a
LIBMLX_INC = -I$(LIBMLX_DIR)

GNL_DIR = include/libftgetnextline
GNL = $(GNL_DIR)/libftgetnextline.a
GNL_INC = -I$(GNL_DIR)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF) $(LIBMLX) $(GNL)
	@$(CC) $(CFLAGS) $(OBJ) -L$(PRINTF_DIR) -L$(LIBFT_DIR) -L$(LIBMLX_DIR) -L$(GNL_DIR) -lftprintf -lft -lmlx -lftgetnextline -framework OpenGL -framework AppKit -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(LIBMLX):
	@make -C $(LIBMLX_DIR)

$(GNL):
	@make -C $(GNL_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFT_INC) $(PRINTF_INC) $(LIBMLX_INC) $(GNL_INC) -c $< -o $@

all: $(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean
	@make -C $(LIBMLX_DIR) clean
	@make -C $(GNL_DIR) clean
	@rm -f $(OBJ)


fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean
	@make -C $(LIBMLX_DIR) clean
	@make -C $(GNL_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
