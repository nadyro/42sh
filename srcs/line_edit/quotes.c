/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 15:43:54 by azybert           #+#    #+#             */
/*   Updated: 2018/07/08 02:14:09 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static char		*stock_line(char *to_return, t_prompt *prompt)
{
	char			**merge;
	char			*to_free;
	struct winsize	w;

	if (to_return == NULL)
	{
		if (!(to_return = ft_strdup(prompt->line)))
			exit(1);
	}
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

char			*quotes_managing(t_prompt *prompt, char *to_return)
{
	if (prompt->origin->y > prompt->size->y)
		prompt->origin->y = prompt->size->y;
	return (stock_line(to_return, prompt));
}
