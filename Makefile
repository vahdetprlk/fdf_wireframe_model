# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 14:36:10 by vparlak           #+#    #+#              #
#    Updated: 2023/09/21 23:05:20 by vparlak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC =   src/fdf.c \
		src/ft_atoi_hex.c \
		src/ft_atoi.c \
		src/ft_calloc.c \
		src/ft_check_map.c \
		src/ft_draw_line.c \
		src/ft_draw.c \
		src/ft_error.c \
		src/ft_hooks.c\
		src/ft_math.c \
		src/ft_projection.c \
		src/ft_read_map.c \
		src/ft_split.c \
		src/ft_vars_init.c

OBJ =  $(SRC:.c=.o)

LIBMLX_DIR = include/libmlx
LIBMLX = $(LIBMLX_DIR)/libmlx.a
LIBMLX_INC = -I$(LIBMLX_DIR)

GNL_DIR = include/get_next_line
GNL = $(GNL_DIR)/libgetnextline.a
GNL_INC = -I$(GNL_DIR)

$(NAME): $(OBJ) $(GNL) $(LIBMLX) $(SALL)
	@$(CC) $(CFLAGS) $(OBJ) -L$(GNL_DIR) -L$(LIBMLX_DIR) -lgetnextline -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(GNL):
	@make -C $(GNL_DIR)

$(LIBMLX):
	@make -C $(LIBMLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(GNL_INC) $(LIBMLX_INC) -c $< -o $@

all: $(NAME)

clean:
	@make -C $(LIBMLX_DIR) clean
	@make -C $(GNL_DIR) clean
	@rm -f $(OBJ)


fclean: clean
	@make -C $(LIBMLX_DIR) clean
	@make -C $(GNL_DIR) fclean

	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
