/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 13:13:10 by antoipom          #+#    #+#             */
/*   Updated: 2018/05/01 17:05:42 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include <stdlib.h>

int			g_tk_states[2][25][15] = {
	{
		{3, 23, 23, 8, 4, 6, 11, 12, 14, 17, 20, 21, 22, 3, 2},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 3, 1},
		{4, 4, 4, 24, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 3, 1},
		{6, 6, 6, 25, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 0},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 3, 1},
		{9, 9, 9, 9, 9, 9, 10, 9, 9, 9, 9, 9, 9, 9, 0},
		{3, 1, 1, 8, 4, 6, 1, 3, 1, 1, 1, 1, 1, 3, 1},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0},
		{1, 1, 1, 1, 1, 1, 11, 1, 1, 1, 1, 1, 1, 1, 1},
		{3, 13, 13, 8, 4, 6, 13, 12, 1, 1, 13, 13, 13, 3, 13},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 15, 1, 1, 1, 1, 16, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 18, 1, 1, 1, 19, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{22, 22, 22, 22, 22, 22, 1, 22, 22, 22, 22, 22, 22, 22, 1},
		{1, 23, 23, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0},
		{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0},
	},
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
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

int				g_state_to_token[24] = {
	0, 0, TK_END, TK_WORD, 0, TK_WORD, 0, TK_WORD, 0, TK_WORD, 0, TK_NEWLINE,\
	TK_IO_NUMBER, TK_WORD, TK_GREAT, TK_DGREAT, TK_GREATAND, TK_LESS, TK_DLESS,\
	TK_LESSAND, TK_PIPE, TK_SEMI, TK_COMMENT, TK_SPACE
};

/*
static int		chartype(char c)
{
	int		type;

	type = -1;
	(c == ' ') ? type = SPACE : 0;
	(c == '\t') ? type = TAB : 0;
	(c == '\\') ? type = ESCAPE : 0;
	(c == '"') ? type = DQUOTE : 0;
	(c == '\'') ? type = QUOTE : 0;
	(c == '\n') ? type = NEWLINE : 0;
	(c >= '0' && c <= '9') ? type = IO_NUMBER : 0;
	(c == '>') ? type = GREAT : 0;
	(c == '<') ? type = LESS : 0;
	(c == '|') ? type = PIPE : 0;
	(c == ';') ? type = SEMI : 0;
	(c == '#') ? type = COMMENT : 0;
	(c == '&') ? type = AND : 0;
	(c == '\0') ? type = END : 0;
	(type == -1) ? type = ANY : 0;
	return (type);
}

static int		apply_tokens_next(int token)
{
	if (token == 22)
		return (TK_COMMENT);
	else if (token == 23)
		return (TK_SPACE);
	else
		return (TK_END);
}

static int		apply_tokens(int token)
{
	if (token == 3 || token == 5 || token == 7 || token == 9 || token == 13)
		return (TK_WORD);
	else if (token == 11)
		return (TK_NEWLINE);
	else if (token == 12)
		return (TK_IO_NUMBER);
	else if (token == 14)
		return (TK_GREAT);
	else if (token == 15)
		return (TK_DGREAT);
	else if (token == 16)
		return (TK_GREATAND);
	else if (token == 17)
		return (TK_LESS);
	else if (token == 18)
		return (TK_DLESS);
	else if (token == 19)
		return (TK_LESSAND);
	else if (token == 20)
		return (TK_PIPE);
	else if (token == 21)
		return (TK_SEMI);
	else
		return (apply_tokens_next(token));
}
*/

static int		*token_loop(int *tk_arr, char *line, int arr_size)
{
	int i;
	int prev;
	int tk_i;

	i = 0;
	prev = 0;
	tk_i = 0;
	while (prev != 2)
	{
		while (tk_i >= arr_size - 3)
			tk_arr = lexer_alloc(tk_arr, &arr_size);
		(tk_arr[tk_i] == -1) ? tk_arr[tk_i] = 1 : 0;
		(tk_arr[tk_i] == 1) ? tk_arr[tk_i + 1] = i : 0;
		prev = tk_arr[tk_i];
		//tk_arr[tk_i] = g_tk_states[0][tk_arr[tk_i] - 1][chartype(line[i])];
		tk_arr[tk_i] = g_tk_states[0][tk_arr[tk_i] - 1][g_ascii[(int)line[i]]];
		//(g_tk_states[1][prev - 1][chartype(line[i])] == 1) ? i++ : 0;
		(g_tk_states[1][prev - 1][g_ascii[(int)line[i]]] == 1) ? i++ : 0;
		(tk_arr[tk_i] == 0) ? exit(1) : 0;//zero?reopen line_editing
		if (tk_arr[tk_i] == 1)
		{
			tk_arr[tk_i] = prev;
			tk_arr[tk_i + 2] = i - tk_arr[tk_i + 1];
			tk_i += 3;
		}
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
	tk_arr = token_loop(tk_arr, line, arr_size);
	while (tk_arr[i] != -1)
	{
		//tk_arr[i] = apply_tokens(tk_arr[i]);
		tk_arr[i] = g_state_to_token[tk_arr[i]];
		i += 3;
	}
	return (tk_arr);
}

//main test
#include <stdio.h>
int				main(int argc, char **argv)
{
	int *tab;
	int i = 0;

	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		tab = get_tokens(argv[1]);
		while (tab[i] != -1)
		{
			switch(tab[i])
			{
				case TK_WORD:
					printf("WORD ");
					break;
				case TK_NEWLINE:
					printf("NEWLINE ");
					break;
				case TK_IO_NUMBER:
					printf("IO_NUMBER ");
					break;
				case TK_GREAT:
					printf("GREAT ");
					break;
				case TK_DGREAT:
					printf("DGREAT ");
					break;
				case TK_GREATAND:
					printf("GREATAND ");
					break;
				case TK_LESS:
					printf("LESS ");
					break;
				case TK_DLESS:
					printf("DLESS ");
					break;
				case TK_LESSAND:
					printf("LESSAND ");
					break;
				case TK_PIPE:
					printf("PIPE ");
					break;
				case TK_SEMI:
					printf("SEMI ");
					break;
				case TK_COMMENT:
					printf("COMMENT ");
					break;
				//case TK_SPACE:
				//	printf("SPACE ");
				//	break;
				case TK_END:
					printf("END ");
					break;
			}
			i += 3;
		}
		printf("\n");
	}
	return (0);
}
