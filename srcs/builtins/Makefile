# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arohani <arohani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 13:46:45 by arohani           #+#    #+#              #
#    Updated: 2018/02/21 16:45:00 by arohani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -g -Wall -Werror -Wextra -I srcs/includes

SRC = srcs/shell.c \
	  srcs/ash_exec.c \
	  srcs/main.c \
	  srcs/env_exec.c \
	  srcs/env.c \
	  srcs/path.c \
	  srcs/bin.c \
	  srcs/setenv.c \
	  srcs/unsetenv.c \
	  srcs/env_setup.c \
	  srcs/env_mod.c \
	  srcs/add_to_mod.c \
	  srcs/pwd.c \
	  srcs/cd.c \
	  srcs/cd_options.c \
	  srcs/free.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C libft
	@gcc $(CFLAGS) -o $(NAME) $(OBJ) -I libft/includes/libft.h libft/libft.a
	@echo "\n\t$(NAME) executable created\n"

clean :
	make -C libft clean
	rm -f $(OBJ)
	@echo "\n\t.o files deleted\n"

fclean : clean
	rm -f $(NAME)
	make -C libft fclean
	@echo "\n\t$(NAME) executable deleted\n"

re: fclean all

.PHONY: all clean fclean re
