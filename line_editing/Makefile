# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azybert <azybert@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/04 19:24:34 by azybert           #+#    #+#              #
#    Updated: 2018/03/04 18:04:50 by azybert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
FILES = 21sh.c ft_prompt.c term.c prompt_manage_data.c cursor_motion.c \
		advanced_cursor_motion.c
OBJ = $(FILES:.c=.o)
LIB = ../Libft/libft.a
CC = gcc
FLAG = -Werror -Wall -Wextra

all: $(NAME)

$(NAME):
	cd ../Libft && make
	$(CC) -c $(FLAG) $(FILES) -g3
	$(CC) -o $(NAME) -ltermcap $(OBJ) $(LIB) -g3

clean:
	cd ../Libft && make clean
	rm -f $(OBJ)

fclean: clean
	cd ../Libft && make fclean
	rm -f $(NAME)

re: fclean all
