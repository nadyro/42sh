/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 05:49:30 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/13 05:53:43 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "heredoc.h"
#include <stdlib.h>

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

void			get_tokens_loop(int *tk_arr, int i, char **line,
		int *state_to_token)
{
	while (tk_arr[i] != -1)
	{
		tk_arr[i] = state_to_token[tk_arr[i]];
		if (i > 2 && tk_arr[i] == TK_WORD && tk_arr[i - 3] == TK_DLESS)
			heredoc_add(&tk_arr[i], *line);
		i += 3;
	}
	tk_arr = check_filename_token(tk_arr);
	tk_arr = check_cmd_token(tk_arr);
}
