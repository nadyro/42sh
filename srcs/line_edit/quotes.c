/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 15:43:54 by azybert           #+#    #+#             */
/*   Updated: 2018/04/03 21:21:20 by azybert          ###   ########.fr       */
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
		free(merge);
	}
	ioctl(0, TIOCGWINSZ, &w);
	free(prompt->line);
	prompt->line = NULL;
	prompt->pos = 0;
	prompt->total = 0;
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

static void		pair_quotes(t_prompt *prompt, char *loop)
{
	size_t	index;
	char	c[3];

	c[1] = '\'';
	c[2] = '"';
	while (loop && *loop)
	{
		index = (prompt->quotes == quotes ? 1 : 0);
		index = (prompt->quotes == dquotes ? 2 : index);
		while (*loop && index == 0)
			index = ft_is_quote(*(loop++));
		if (index != 0)
		{
			prompt->quotes = (index == 1 ? quotes : dquotes);
			loop = ft_strchr(loop, c[index]);
			if (loop != NULL)
			{
				prompt->quotes = none;
				loop++;
				index = 0;
			}
		}
	}
}

char			*quotes_managing(t_prompt *prompt, char *to_return)
{
	char	*loop;

	loop = prompt->line;
	pair_quotes(prompt, loop);
	prompt->origin->y += 1 +
		(prompt->total + prompt->origin->x) / prompt->size->x;
	move_cursor(prompt, -(prompt->origin->x), true);
	if (prompt->quotes == quotes)
		write(1, "quotes> ", 8);
	else if (prompt->quotes == dquotes)
		write(1, "dquotes> ", 9);
	get_cursor_pos(prompt->origin, prompt);
	return (stock_line(to_return, prompt));
}
