# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 14:36:10 by vparlak           #+#    #+#              #
#    Updated: 2023/09/15 01:44:28 by vparlak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC =   src/fdf.c \
		src/ft_split.c \
		src/ft_atoi.c


OBJ =  $(SRC:.c=.o)

PRINTF_DIR = include/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
PRINTF_INC = -I$(PRINTF_DIR)

LIBMLX_DIR = include/libmlx
LIBMLX = $(LIBMLX_DIR)/libmlx.a
LIBMLX_INC = -I$(LIBMLX_DIR)

GNL_DIR = include/get_next_line
GNL = $(GNL_DIR)/libgetnextline.a
GNL_INC = -I$(GNL_DIR)

$(NAME): $(OBJ) $(PRINTF) $(GNL) $(LIBMLX) $(SALL)
	@$(CC) $(CFLAGS) $(OBJ) -L$(PRINTF_DIR) -L$(GNL_DIR) -L$(LIBMLX_DIR) -lftprintf -lgetnextline -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(PRINTF):
	@make -C $(PRINTF_DIR)

$(GNL):
	@make -C $(GNL_DIR)

$(LIBMLX):
	@make -C $(LIBMLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(PRINTF_INC) $(GNL_INC) $(LIBMLX_INC) -c $< -o $@

all: $(NAME)

clean:
	@make -C $(PRINTF_DIR) clean
	@make -C $(LIBMLX_DIR) clean
	@make -C $(GNL_DIR) clean
	@rm -f $(OBJ)


fclean: clean
	@make -C $(PRINTF_DIR) fclean
	@make -C $(LIBMLX_DIR) clean
	@make -C $(GNL_DIR) fclean

	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
