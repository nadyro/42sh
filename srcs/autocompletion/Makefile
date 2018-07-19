# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/18 13:56:26 by nsehnoun          #+#    #+#              #
#    Updated: 2018/07/18 16:17:35 by nsehnoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES = autocompletion.c \
			cmpltn_utils.c \
			fetch_utils.c \

INC_FILES = autocompletion.h \

NAME ?= acmpltn

LIB = -Llibft -lft
INCLUDES = autocompletion.h
OBJS = $(SRC_FILES:.c=.o)

CC ?= gcc
CCFLAGS ?= -Wall -Werror -Wextra -fsanitize=address -g3

all: $(NAME) 

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CCFLAGS) -o $(NAME) $(OBJS) $(LIB) -I $(INCLUDES)

clean:
	/bin/rm -f $(OBJS)
	@make -C libft fclean

fclean: clean
	/bin/rm -f $(NAME)
	@make -C libft fclean

re: fclean all

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $^
