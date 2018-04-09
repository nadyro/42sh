/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 13:13:10 by antoipom          #+#    #+#             */
/*   Updated: 2018/04/09 15:55:27 by antoipom         ###   ########.fr       */
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

static void		token_loop(int *tk_tab, char *line)
{
	int i;
	int prev;
	int tk_index;

	i = 0;
	prev = 0;
	tk_index = 0;
	while (prev != 2)
	{
		(tk_tab[tk_index] == -1) ? tk_tab[tk_index] = 1 : 0;
		(tk_tab[tk_index] == 1) ? tk_tab[tk_index + 1] = i : 0;
		prev = tk_tab[tk_index];
		tk_tab[tk_index] = \
			g_tk_states[0][tk_tab[tk_index] - 1][chartype(line[i])];
		(g_tk_states[1][prev - 1][chartype(line[i])] == 1) ? i++ : 0;
		(tk_tab[tk_index] == 0) ? exit(1) : 0;//zero?
		if (tk_tab[tk_index] == 1)//i prob?
		{
			tk_tab[tk_index] = prev;
			tk_tab[tk_index + 2] = i - tk_tab[tk_index + 1];
			tk_index += 3;
		}
	}
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
	if (token == 3 || token == 5 || token == 7 || token == 13)
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

int				*get_tokens(char *line)
{
	int		*tk_tab;
	int		i;

	i = 0;
	tk_tab = (int*)malloc(sizeof(int) * TAB_SIZE); //realloc needed?
	(tk_tab == NULL) ? exit(1) : 0; //error handling?
	ft_memset(tk_tab, -1, TAB_SIZE);
	token_loop(tk_tab, line);
	while (tk_tab[i] != -1)
	{
		tk_tab[i] = apply_tokens(tk_tab[i]);
		i += 3;
	}
	return (tk_tab);
}

//main test
#include <stdio.h>
int				main(int argc, char **argv)
{
	int *tab;
	int i = 0;

	if (argc == 2)
	{
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
				/*case TK_SPACE:
					printf("SPACE ");
					break;*/
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
