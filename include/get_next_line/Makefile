# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparlak <vparlak@student.42kocaeli.com.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 14:35:44 by vparlak           #+#    #+#              #
#    Updated: 2023/07/22 14:35:45 by vparlak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
