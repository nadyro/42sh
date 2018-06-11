/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 12:45:57 by antoipom          #+#    #+#             */
/*   Updated: 2018/06/11 14:37:53 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				g_parser_states[10][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{3, 3, 6, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 2, 1},
	{3, 3, 4, 5, 5, 5, 5, 5, 5, 8, 2, 9, 9, 0, 3, 1},
	{0, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0},
	{0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
	{0, 0, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0},
	{0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
	{3, 3, 6, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 8, 0},
	{3, 3, 6, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 9, 0}
};

static int		convert_token(int token)
{
	int result;

	result = 0;
	(token == TK_CMD) ? result = 0 : 0;
	(token == TK_WORD) ? result = 1 : 0;
	(token == TK_IO_NUMBER) ? result = 2 : 0;
	(token == TK_GREAT) ? result = 3 : 0;
	(token == TK_DGREAT) ? result = 4 : 0;
	(token == TK_GREATAND) ? result = 5 : 0;
	(token == TK_LESS) ? result = 6 : 0;
	(token == TK_DLESS) ? result = 7 : 0;
	(token == TK_LESSAND) ? result = 8 : 0;
	(token == TK_PIPE) ? result = 9 : 0;
	(token == TK_SEMI) ? result = 10 : 0;
	(token == TK_AND_IF) ? result = 11 : 0;
	(token == TK_OR_IF) ? result = 12 : 0;
	(token == TK_FILENAME) ? result = 13 : 0;
	(token == TK_NEWLINE) ? result = 14 : 0;
	(token == TK_END) ? result = 15 : 0;
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
		return (-1);//-1 actually means OK
	else
		return (i);
}
