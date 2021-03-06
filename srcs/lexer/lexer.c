/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 13:13:10 by antoipom          #+#    #+#             */
/*   Updated: 2018/08/21 14:15:22 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "heredoc.h"
#include "builtins.h"
#include <stdlib.h>

int				g_tk_states[2][39][16] = {
	{
		{3, 23, 23, 8, 4, 6, 11, 12, 14, 17, 20, 21, 22, 27, 2, 29},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 26, 1, 29},
		{4, 4, 4, 24, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 30},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 1, 1, 29},
		{6, 6, 6, 25, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 1, 1, 29},
		{9, 9, 9, 9, 9, 9, 10, 9, 9, 9, 9, 9, 9, 9, 0, 9},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 3, 1, 37},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9},
		{1, 1, 1, 1, 1, 1, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{3, 13, 13, 8, 4, 6, 13, 12, 1, 1, 13, 13, 13, 1, 13, 29},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 15, 1, 1, 1, 1, 16, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 18, 1, 1, 1, 19, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 28, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{22, 22, 22, 22, 22, 22, 1, 22, 22, 22, 22, 22, 22, 22, 1, 22},
		{1, 23, 23, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4},
		{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 33},
		{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 29},
		{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 29},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{29, 1, 1, 36, 30, 33, 1, 29, 1, 1, 1, 1, 1, 39, 1, 29},
		{30, 30, 30, 24, 32, 30, 30, 30, 30, 30, 30, 30, 30, 30, 0, 30},
		{30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 0, 30},
		{29, 1, 1, 36, 30, 33, 1, 29, 1, 1, 1, 1, 1, 1, 1, 29},
		{33, 33, 33, 34, 33, 35, 33, 33, 33, 33, 33, 33, 33, 33, 0, 33},
		{33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 0, 33},
		{29, 1, 1, 36, 30, 33, 1, 29, 1, 1, 1, 1, 1, 1, 1, 29},
		{37, 37, 37, 37, 37, 37, 10, 37, 37, 37, 37, 37, 37, 37, 0, 37},
		{29, 1, 1, 36, 30, 33, 1, 29, 1, 1, 1, 1, 1, 29, 1, 29},
		{37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 0, 37},
		{29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 1, 29, 29}
	},
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0}
	}
};

int				g_ascii[128] = {
	END, 0, 0, 0, 0, 0, 0, 0, 0, TAB, NEWLINE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, SPACE, BANG, DQUOTE, COMMENT, ANY, ANY, AND,
	QUOTE, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, IO_NUMBER, IO_NUMBER,
	IO_NUMBER, IO_NUMBER, IO_NUMBER, IO_NUMBER, IO_NUMBER, IO_NUMBER,
	IO_NUMBER, IO_NUMBER, ANY, SEMI, LESS, ANY, GREAT, ANY, ANY, ANY, ANY, ANY,
	ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY,
	ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ESCAPE, ANY, ANY, ANY, ANY,
	ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY,
	ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY, PIPE, ANY, ANY,
	ANY
};

int				g_state_to_token[40] = {
	0, 0, TK_END, TK_WORD, 0, TK_WORD, 0, TK_WORD, 0, TK_WORD,
	0, TK_NEWLINE, TK_IO_NUMBER, TK_WORD, TK_GREAT, TK_DGREAT, TK_GREATAND,
	TK_LESS, TK_DLESS, TK_LESSAND, TK_PIPE, TK_SEMI, TK_COMMENT, TK_SPACE, 0,
	0, TK_WORD, TK_AND_IF, TK_OR_IF, TK_HISTORY, 0, 0, TK_HISTORY, 0, 0,
	TK_HISTORY, 0, TK_HISTORY, 0, TK_HISTORY
};

static int		*lexer_alloc(int *tk_arr, int *arr_size)
{
	int		*new;
	int		i;

	i = 0;
	*arr_size = *arr_size * 2;
	new = (int*)malloc(sizeof(int) * (*arr_size));
	(new == NULL) ? sh_close(1, "") : 0;
	ft_memset(new, -1, *arr_size * sizeof(int));
	while (tk_arr[i] != -1)
	{
		new[i] = tk_arr[i];
		i++;
	}
	free(tk_arr);
	return (new);
}

static void		*free_arr_and_line(int **tk_arr, char **line)
{
	free(*tk_arr);
	*tk_arr = NULL;
	free(*line);
	*line = NULL;
	return (NULL);
}

static void		token_adj(int *tk_arr, int *tk_i, int i, int prev)
{
	tk_arr[*tk_i] = prev;
	tk_arr[(*tk_i) + 2] = i - tk_arr[(*tk_i) + 1];
	(*tk_i) += 3;
}

static int		*token_loop(int *tk_arr, char **line, int arr_size, int i)
{
	int prev;
	int tk_i;

	prev = 0;
	tk_i = 0;
	while (prev != 2 && tk_arr[tk_i] != 0)
	{
		if ((*line)[i] < 0 || (*line)[i] > 127)
			return (free_arr_and_line(&tk_arr, line));
		while (tk_i >= arr_size - 3)
			tk_arr = lexer_alloc(tk_arr, &arr_size);
		(tk_arr[tk_i] == -1) ? tk_arr[tk_i] = 1 : 0;
		(tk_arr[tk_i] == 1) ? tk_arr[tk_i + 1] = i : 0;
		prev = tk_arr[tk_i];
		tk_arr[tk_i] = g_tk_states[0][tk_arr[tk_i] - 1]
			[g_ascii[(int)(*line)[i]]];
		i += (g_tk_states[1][prev - 1][g_ascii[(int)(*line)[i]]]);
		if (tk_arr[tk_i] == 1 && prev != 22 && prev != 23)
			token_adj(tk_arr, &tk_i, i, prev);
	}
	tk_arr[tk_i] == 0 ? ft_ptrclear((void*)&tk_arr) : 0;
	return (tk_arr);
}

int				*get_tokens(char **line)
{
	int		arr_size;
	int		*tk_arr;
	int		i;
	int		r;

	i = 0;
	arr_size = 1024;
	tk_arr = (int*)malloc(sizeof(int) * arr_size);
	(tk_arr == NULL || !line || !(*line))
		? sh_close(1, "") : heredoc_manager(0);
	memset(tk_arr, -1, arr_size * sizeof(int));
	tk_arr = token_loop(tk_arr, line, arr_size, 0);
	if (tk_arr != NULL)
		get_tokens_loop(tk_arr, i, line, g_state_to_token);
	else
		return (NULL);
	if ((r = precheck_history_token(tk_arr, line)) == 1)
		return (get_tokens(line));
	else if (r == 2)
		return (NULL);
	if (heredoc_manager(1) && heredoc_fill() != 0)
		return (free_arr_and_line(&tk_arr, line));
	return (tk_arr);
}
