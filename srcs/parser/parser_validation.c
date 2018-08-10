/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 12:45:57 by antoipom          #+#    #+#             */
/*   Updated: 2018/08/02 16:39:49 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <unistd.h>

int				g_parser_states[11][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{3, 3, 6, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 2, 1},
	{3, 3, 4, 5, 5, 5, 5, 5, 5, 8, 2, 9, 9, 0, 3, 1},
	{0, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0},
	{0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
	{0, 0, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0},
	{0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0},
	{3, 3, 6, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 8, -1},
	{3, 3, 6, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 9, -1},
	{3, 3, 6, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0}
};

int				g_convert_token[18] = {
	1, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -1, 11, 12, 15, 0, 13
};

static void		parsing_error(int *tk_arr, int i, char *line)
{
	ft_putstr_fd("parse error near '", 2);
	if (tk_arr[i] == TK_NEWLINE)
		ft_putstr_fd("\\n", 2); 
	else 
		write(2, line + tk_arr[i + 1], tk_arr[i + 2]); 
	write(2, "'\n", 2);
}

int				parser_validation(int *tk_arr, char *line)
{
	int i;
	int state;

	i = 0;
	state = 2;
	while (state != 1 && state != 0 && state != -1)
	{
		state = g_parser_states[state][g_convert_token[tk_arr[i]]];
		if (state != 1 && state != 0)
			i += 3;
		else if (tk_arr[i] == TK_END)
			i -= 3;
	}
	if (state == -1)
		return (-1);
	else if (state == 0)
	{
		parsing_error(tk_arr, i, line);
		return (0);
	}
	return (1);
}
