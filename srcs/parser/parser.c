/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 14:07:50 by antoipom          #+#    #+#             */
/*   Updated: 2018/06/01 16:36:31 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				g_parser_states[10][17] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{3, 0, 3, 3, 6, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 1},
	{3, 3, 3, 3, 4, 5, 5, 5, 5, 5, 5, 8, 2, 9, 9, 0, 1},
	{0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0},
	{0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0},
	{0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0},
	{0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0},
	{3, 0, 3, 3, 6, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0},
	{3, 3, 3, 3, 6, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0}
};

static int		convert_token(int token)
{
	int result;

	result = 0;
	(token == TK_CMD) ? result = 0 : 0;
	(token == TK_WORD) ? result = 1 : 0;
	(token == TK_QUOTED_WORD) ? result = 2 : 0;
	(token == TK_DQUOTED_WORD) ? result = 3 : 0;
	(token == TK_IO_NUMBER) ? result = 4 : 0;
	(token == TK_GREAT) ? result = 5 : 0;
	(token == TK_DGREAT) ? result = 6 : 0;
	(token == TK_GREATAND) ? result = 7 : 0;
	(token == TK_LESS) ? result = 8 : 0;
	(token == TK_DLESS) ? result = 9 : 0;
	(token == TK_LESSAND) ? result = 10 : 0;
	(token == TK_PIPE) ? result = 11 : 0;
	(token == TK_SEMI) ? result = 12 : 0;
	(token == TK_AND_IF) ? result = 13 : 0;
	(token == TK_OR_IF) ? result = 14 : 0;
	(token == TK_FILENAME) ? result = 15 : 0;
	(token == TK_END) ? result = 16 : 0;
	return (result);
};

int				parser_validation(int *tk_arr)
{
	int i;
	int state;

	i = 0;
	state = 2;
	while (state != 1 && state != 0)
	{
		state = g_parser_states[state][convert_token(tk_arr[i])];
		if (state != 1 && state != 0)
			i += 3;
		else if (tk_arr[i] == TK_END)
			i -= 3;
	}
	if (state == 1)
		return (-1);
	else
		return (i); //
}
