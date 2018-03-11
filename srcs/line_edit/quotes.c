/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 15:43:54 by azybert           #+#    #+#             */
/*   Updated: 2018/03/11 22:23:21 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

static char		*stock_line(char *to_return, t_prompt *prompt)
{
	char			**merge;
	char			*to_free;
	struct winsize	w;

	if (to_return == NULL)
		to_return = ft_strdup(prompt->line);
	else
	{
		if (!(merge = malloc(sizeof(char *) * 3)))
			exit(1);
		merge[2] = NULL;
		merge[1] = prompt->line;
		merge[0] = to_return;
		to_free = to_return;
		to_return = ft_strmerge(merge);
		free(to_free);
	}
	ioctl(0, TIOCGWINSZ, &w);
	free(prompt->line);
	prompt->line = NULL;
	move_cursor(prompt, 0, true);
	prompt->total = 0;
	get_cursor_pos(prompt->origin);
	prompt->size->x = w.ws_col;
	prompt->size->y = w.ws_row;
	return (to_return);
}

static size_t	ft_is_quote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (2);
	return (0);
}

char			*check_quotes(t_prompt *prompt, char *to_return)
{
	char	c[3];
	char	*loop;
	size_t	index;

	c[1] = '\'';
	c[2] = '"';
	loop = prompt->line;
	while (loop && *loop)
	{
		index = (prompt->quotes == quotes ? 1 : 0);
		index = (prompt->quotes == dquotes ? 2 : index);
		while (*loop && index == 0)
		{
			index = ft_is_quote(*loop);
			loop++;
		}
		if (index > 0)
		{
			loop = ft_strchr(loop, c[index]);
			if (loop == NULL)
				prompt->quotes = (prompt->quotes == none ? index : none);
			else
				loop++;
		}
	}
	//if quotes, disply prompt;
	//if (prompt->quotes != none)
	prompt->origin->y += 1;
	return(stock_line(to_return, prompt));
}
