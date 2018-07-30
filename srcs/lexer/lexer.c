/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <antoipom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 13:13:10 by antoipom          #+#    #+#             */
/*   Updated: 2018/07/19 16:13:28 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include <stdlib.h>

int				g_tk_states[2][28][15] = {
	{
		{3, 23, 23, 8, 4, 6, 11, 12, 14, 17, 20, 21, 22, 27, 2},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 26, 1},
		{4, 4, 4, 24, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 1, 1},
		{6, 6, 6, 25, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 0},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 1, 1},
		{9, 9, 9, 9, 9, 9, 10, 9, 9, 9, 9, 9, 9, 9, 0},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 3, 1},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0},
		{1, 1, 1, 1, 1, 1, 11, 1, 1, 1, 1, 1, 1, 1, 1},
		{3, 13, 13, 8, 4, 6, 13, 12, 1, 1, 13, 13, 13, 1, 13},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 15, 1, 1, 1, 1, 16, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 18, 1, 1, 1, 19, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 28, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{22, 22, 22, 22, 22, 22, 1, 22, 22, 22, 22, 22, 22, 22, 1},
		{1, 23, 23, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0},
		{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0},
		{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3},
		{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	},
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	}
};

int				g_ascii[128] = {
	END, 0, 0, 0, 0, 0, 0, 0, 0, TAB, NEWLINE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SPACE, ANY, DQUOTE, COMMENT, ANY, ANY, AND,\
	QUOTE, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, IO_NUMBER, IO_NUMBER,\
	IO_NUMBER, IO_NUMBER, IO_NUMBER, IO_NUMBER, IO_NUMBER, IO_NUMBER,\
	IO_NUMBER, IO_NUMBER, ANY, SEMI, LESS, ANY, GREAT, ANY, ANY, ANY, ANY, ANY,\
	ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY,\
	ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ESCAPE, ANY, ANY, ANY, ANY,\
	ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY,\
	ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, PIPE, ANY, ANY,\
	ANY
};

int				g_state_to_token[29] = {
	0, 0, TK_END, TK_WORD, 0, TK_WORD, 0, TK_WORD, 0, TK_WORD, \
	0, TK_NEWLINE, TK_IO_NUMBER, TK_WORD, TK_GREAT, TK_DGREAT, TK_GREATAND, \
	TK_LESS, TK_DLESS, TK_LESSAND, TK_PIPE, TK_SEMI, TK_COMMENT, TK_SPACE, 0, \
	0, TK_WORD, TK_AND_IF, TK_OR_IF
};

static int		*lexer_alloc(int *tk_arr, int *arr_size)
{
	int		*new;
	int		i;

	i = 0;
	*arr_size = *arr_size * 2;
	new = (int*)malloc(sizeof(int) * (*arr_size));
	(new == NULL) ? exit(1) : 0; //error handling?
	ft_memset(new, -1, *arr_size * sizeof(int));
	while (tk_arr[i] != -1)
	{
		new[i] = tk_arr[i];
		i++;
	}
	free(tk_arr);
	return (new);
}

static int		*token_loop(int *tk_arr, char *line, int arr_size, int i)
{
	int prev;
	int tk_i;

	prev = 0;
	tk_i = 0;
	while (prev != 2 && tk_arr[tk_i] != 0)
	{
		while (tk_i >= arr_size - 3)
			tk_arr = lexer_alloc(tk_arr, &arr_size);
		(tk_arr[tk_i] == -1) ? tk_arr[tk_i] = 1 : 0;
		(tk_arr[tk_i] == 1) ? tk_arr[tk_i + 1] = i : 0;
		prev = tk_arr[tk_i];
		tk_arr[tk_i] = g_tk_states[0][tk_arr[tk_i] - 1][g_ascii[(int)line[i]]];
		i += (g_tk_states[1][prev - 1][g_ascii[(int)line[i]]]);
//		(tk_arr[tk_i] == 0) ? main_loop(line) : 0; //////////////
		if (tk_arr[tk_i] == 1 && prev != 22 && prev != 23)
		{
			tk_arr[tk_i] = prev;
			tk_arr[tk_i + 2] = i - tk_arr[tk_i + 1];
			tk_i += 3;
		}
	}
	if (tk_arr[tk_i] == 0)
	{
		free(tk_arr);
		tk_arr = NULL;
	}
	return (tk_arr);
}

static int		*check_filename_token(int *tk_arr)
{
	int i;
	int is_file;

	i = 0;
	is_file = 0;
	while (tk_arr[i] != -1)
	{
		if (tk_arr[i] == TK_WORD && is_file == 1)
		{
			tk_arr[i] = TK_FILENAME;
			is_file = 0;
		}
		else if (is_file == 0 && (tk_arr[i] == TK_GREAT || \
					tk_arr[i] == TK_DGREAT || tk_arr[i] == TK_GREATAND || \
					tk_arr[i] == TK_LESS || tk_arr[i] == TK_DLESS || \
					tk_arr[i] == TK_LESSAND))
			is_file = 1;
		i += 3;
	}
	return (tk_arr);
}

static int		*check_cmd_token(int *tk_arr)
{
	int i;
	int	is_first_word;

	i = 0;
	is_first_word = 1;
	while (tk_arr[i] != -1)
	{
		if (tk_arr[i] == TK_WORD && is_first_word == 1)
		{
			tk_arr[i] = TK_CMD;
			is_first_word = 0;
		}
		else if (is_first_word == 0 && (tk_arr[i] == TK_PIPE || \
				tk_arr[i] == TK_SEMI || tk_arr[i] == TK_AND_IF || \
				tk_arr[i] == TK_OR_IF || tk_arr[i] == TK_NEWLINE))
			is_first_word = 1;
		i += 3;
	}
	return (tk_arr);
}

int				*get_tokens(char *line)
{
	int		arr_size;
	int		*tk_arr;
	int		i;

	i = 0;
	arr_size = 1024;
	tk_arr = (int*)malloc(sizeof(int) * arr_size);
	(tk_arr == NULL) ? exit(1) : 0; //error handling?
	memset(tk_arr, -1, arr_size * sizeof(int));
	tk_arr = token_loop(tk_arr, line, arr_size, 0);
	if (tk_arr != NULL)
	{
		while (tk_arr[i] != -1)
		{
			tk_arr[i] = g_state_to_token[tk_arr[i]];
			i += 3;
		}
		tk_arr = check_filename_token(tk_arr);
		tk_arr = check_cmd_token(tk_arr);
	}
	return (tk_arr);
}
