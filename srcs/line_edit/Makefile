# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azybert <azybert@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/04 19:24:34 by azybert           #+#    #+#              #
#    Updated: 2018/03/10 17:38:21 by azybert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh
FILES = 42sh.c prompt.c termanip.c manage_data.c \
		basic_cursor_motion.c advanced_cursor_motion.c utility_cursor_motion.c
OBJ = $(FILES:.c=.o)
LIB = ../../libft/libft.a
CC = gcc
FLAG = -Werror -Wall -Wextra

all: $(NAME)

$(NAME):
	cd ../../libft && make
	$(CC) -c $(FLAG) $(FILES)
	$(CC) -o $(NAME) $(OBJ) $(LIB) -ltermcap

clean:
	cd ../../libft && make clean
	rm -f $(OBJ)

fclean: clean
	cd ../../libft && make fclean
	rm -f $(NAME)

re: fclean all
