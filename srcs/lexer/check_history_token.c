/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_history_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 03:30:31 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/16 18:54:39 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include <stdio.h>

static void	shift_token(int *token, int shift)
{
	int		i;

	i = 0;
	while (token && token[i] != -1)
	{
		token[i + 1] += shift;
		i += 3;
	}
}

static int	event_not_exist(int *tk, char *line)
{
	ft_putstr("42sh: no such event: ");
	ft_putbyte(line + tk[1] + 1, tk[2] - 1);
	ft_putchar('\n');
	return (1);
}

static int	replace_token_history(int *token, char **line)
{
	int		tk[3];
	char	*hst;
	int		hlen;
	char	*new_line;

	history_get(tk, *line + token[1], token[2]);
	hst = history_research(tk, (*line) + token[1], history_m(1, NULL));
	if (!hst)
		return (event_not_exist(tk, *line + token[1]));
	hlen = ft_strlen(hst);
	if (!(new_line = (char*)ft_memalloc(ft_strlen(*line) + hlen - tk[2] + 1)))
		return (1);
	ft_memcpy(new_line, *line, token[1] + tk[1]);
	ft_memcpy(new_line + tk[1] + token[1], hst, hlen);
	ft_memcpy(new_line + tk[1] + token[1] + hlen,
			(*line) + token[1] + tk[1] + tk[2],
			ft_strlen(*line) - (token[1] + tk[1] + tk[2]));
	shift_token(token, hlen - tk[2]);
	free(*line);
	*line = new_line;
	return (0);
}

int			check_history_token(int *token, char **line)
{
	int		i;
	int		h;
	int		d;

	i = 0;
	h = 0;
	d = history_m(2, NULL) ? 1 : 0;
	while (token && token[i] != -1)
	{
		if (!d && token[i] == TK_HISTORY && ++h
				&& replace_token_history(&token[i], line))
			return (-1);
		else if (d && token[i] == TK_HISTORY)
			token[i] = TK_WORD;
		i += 3;
	}
	return (h);
}

int			precheck_history_token(int *tk_arr, char **line)
{
	int	r;

	if ((r = check_history_token(tk_arr, line)) > 0)
	{
		free(tk_arr);
		tk_arr = NULL;
		ft_putstr(*line);
		return (1);
	}
	else if (r == -1)
	{
		free(*line);
		*line = NULL;
		free(tk_arr);
		return (2);
	}
	return (0);
}
