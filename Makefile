# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azybert <azybert@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/04 19:24:34 by azybert           #+#    #+#              #
#    Updated: 2018/03/12 14:52:30 by kernel_pa        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# To add a source file : Read all comments.

# Create a folder in srcs/ i.e "lexer" then add the source file. See if existing
# modules match your new file implementation before creating a new module folder.

# Add the source file path without "srcs/" down here.

SRCS = 	line_edit/advanced_cursor_motion.c \
	line_edit/basic_cursor_motion.c \
	line_edit/manage_data.c \
	line_edit/prompt.c \
	line_edit/quotes.c \
	line_edit/sh.c \
	line_edit/termanip.c \
	line_edit/utility_cursor_motion.c \

SRC_DIR = srcs
OBJ_DIR = objs
NAME = 42sh

LIB = -Llibft -lft

# Create the header file in includes/ if needed.
# (It is encouraged to create a header file for each big modules or group mate.
# We might need to discuss this when everybody will gather).

HEADERS = includes/sh_line_edit.h

# Creation of the object files in dynamically created folder "objs"

SRC = $(addprefix $(SRC_DIR)/, $(SRCS:.c=.c))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
CC = gcc

FLAG = -Werror -Wall -Wextra
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@make -C libft
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIB) -I $(HEADERS) -ltermcap

# Rule for object files creation
# Insert at the end of the rule the new module folder you need to add, do as below		  

$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)
	@/bin/mkdir -p $(OBJ_DIR)/line_edit
clean:
	@/bin/rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(FLAG) -c -o $@ $<
