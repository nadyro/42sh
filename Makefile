# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arohani <arohani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/07 14:24:02 by antoipom          #+#    #+#              #
#    Updated: 2018/08/16 16:05:33 by arohani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_CLEAR		= \033[2K
COLOR_UP		= \033[A
COLOR_NOCOLOR	= \033[0m
COLOR_BOLD		= \033[1m
COLOR_UNDERLINE	= \033[4m
COLOR_BLINKING	= \033[5m
COLOR_BLACK		= \033[1;30m
COLOR_RED		= \033[1;31m
COLOR_GREEN		= \033[1;32m
COLOR_YELLOW	= \033[1;33m
COLOR_BLUE		= \033[1;34m
COLOR_VIOLET	= \033[1;35m
COLOR_CYAN		= \033[1;36m
COLOR_WHITE		= \033[1;37m

################################################################################

SRC_FILES = main.c \
			\
			lexer/lexer.c \
			\
			parser/parser.c \
			parser/execute.c \
			parser/parser_validation.c \
			parser/redirections.c \
			parser/redirect_implementation.c \
			parser/redirect_construct.c \
			parser/redirect_heredoc.c \
			parser/arg_table.c \
			parser/is_fd.c \
			parser/pipes.c \
			parser/token2str.c \
			parser/token2str_init.c \
			parser/ast_evaluate.c \
			parser/ast_construct.c \
			parser/ast_free.c \
			\
			builtins/add_to_mod.c \
			builtins/bin.c \
			builtins/cd.c \
			builtins/cd_canon.c \
			builtins/cd_canon_dotdot.c \
			builtins/cd_options.c \
			builtins/env.c \
			builtins/env_exec.c \
			builtins/env_mod.c \
			builtins/env_setup.c \
			builtins/error.c \
			builtins/free.c \
			builtins/path.c \
			builtins/pwd.c \
			builtins/setenv.c \
			builtins/unsetenv.c \
			builtins/history.c \
			builtins/history_builtins_0.c \
			builtins/history_builtins_1.c \
			builtins/history_builtins_2.c \
			builtins/history_builtins_3.c \
			builtins/history_builtins_4.c \
			builtins/history_builtins_5.c \
			builtins/history_options.c \
			builtins/history_flags.c \
			\
			line_edit/line_edit_main_loop.c \
			line_edit/termanip.c \
			line_edit/manage_data.c \
			line_edit/advanced_cursor_motion.c \
			line_edit/cursor_motion.c \
			line_edit/react.c \
			line_edit/history.c \
			line_edit/selection_mode.c \
			line_edit/struct_alloc.c \
			line_edit/signals_le.c \
			line_edit/signals_le_mode.c \
			line_edit/search_mode.c \
			line_edit/implem_complet.c \
			line_edit/write_data.c\
			line_edit/autocompletion.c \
			line_edit/cmpltn_utils.c \
			line_edit/fetch_utils.c \
			line_edit/cmplt_misc.c \
			line_edit/prompt_utils.c \
			line_edit/sig_ignore.c \
			\
			heredoc/heredoc.c \
			heredoc/heredoc_fill.c \
			\
			lexer/check_history_token.c \
			lexer/history_token.c \
			lexer/get_tokens_loop.c \

INC_FILES = lexer.h \
			parser.h \
			builtins.h \
			sh_line_edit.h \
			shell_structs.h \
			heredoc.h

NAME ?= 42sh

#ASAN =
#ifeq ($(ASAN), yes)
#	SANITIZER ?= -fsanitize=address -fno-omit-frame-pointer 
#endif

LIB_DIR = libft
SRC_DIR = srcs
OBJ_DIR = objs
LOCAL_INC = -Iinclude
LIB_INC = -I$(LIB_DIR)/include

OPTIMIZATION ?= -O0
CC ?= gcc
CCFLAGS ?= -g -Wall -Wextra -Werror -g3 -fsanitize=address -fno-omit-frame-pointer
LDFLAGS = -L$(LIB_DIR) -lft -ltermcap
INCLUDES = $(LOCAL_INC) $(LIB_INC)

INCLUDES_DEP = $(addprefix ./include/, $(INC_FILES))
SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILES:.c=.c))
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

################################################################################

.phony: all hello_word lib $(OBJ_DIR) $(NAME) clean fclean re

all: hello_word lib $(OBJ_DIR) $(NAME) $(INCLUDES_DEP)
	@printf "$(COLOR_CLEAR)$(COLOR_GREEN)successfully created $(COLOR_BLUE)$(NAME)$(COLOR_NOCOLOR)\n"

hello_word:
	@printf "$(COLOR_VIOLET)$(COLOR_UNDERLINE)compiling$(COLOR_NOCOLOR) $(COLOR_BLUE)$(NAME) ...$(COLOR_NOCOLOR)\n"

lib:
	@make -C $(LIB_DIR) APPEND="$(APPEND)" OPTIMIZATION="$(OPTIMIZATION)" CC="$(CC)"

$(NAME): $(OBJS)
	@printf "$(COLOR_GREEN)successfully created objects files for binary $(COLOR_BLUE)$(NAME)$(COLOR_NOCOLOR)\n"
	@printf "$(COLOR_VIOLET)creating $(NAME) ... $(COLOR_NOCOLOR)\n"
	@$(CC) $(CCFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(INCLUDES) $(SANITIZER) $(OPTIMIZATION)
	
$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)
	@/bin/mkdir -p $(OBJ_DIR)/lexer
	@/bin/mkdir -p $(OBJ_DIR)/parser
	@/bin/mkdir -p $(OBJ_DIR)/builtins
	@/bin/mkdir -p $(OBJ_DIR)/line_edit
	@/bin/mkdir -p $(OBJ_DIR)/heredoc

clean:
	@make -C $(LIB_DIR) clean
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME)

re: fclean all

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@printf "$(COLOR_VIOLET)creating objects files for library $(COLOR_BLUE)$(NAME) ... \n$(COLOR_CYAN)"
	$(CC) $(OPTIMIZATION) $(CCFLAGS) $(INCLUDES) $(SANITIZER) -c -o $@ $^
	@printf "\n$(COLOR_NOCOLOR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)"
