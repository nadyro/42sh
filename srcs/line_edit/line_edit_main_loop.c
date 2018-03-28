/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:28:12 by azybert           #+#    #+#             */
/*   Updated: 2018/03/28 22:52:57 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

void		free_prompt(t_prompt *prompt)
{
	free(prompt->line);
	prompt->line = NULL;
	free(prompt->buf);
	prompt->buf = NULL;
	free(prompt->origin);
	prompt->origin = NULL;
	free(prompt->size);
	prompt->size = NULL;
	free(prompt);
	prompt = NULL;
}

t_prompt	*malloc_prompt(t_prompt *prompt)
{
	struct winsize	w;

	if (!(prompt = malloc(sizeof(*prompt))))
		exit(1);
	if (!(prompt->origin = malloc(sizeof(t_coord))))
		exit(1);
	if (!(prompt->size = malloc(sizeof(t_coord))))
		exit(1);
	ioctl(0, TIOCGWINSZ, &w);
	prompt->line = NULL;
	prompt->buf = NULL;
	prompt->pos = 0;
	prompt->total = 0;
	get_cursor_pos(prompt->origin);
	prompt->size->x = w.ws_col;
	prompt->size->y = w.ws_row;
	prompt->quotes = none;
	return (prompt);
}

char			*line_edit_main_loop(void)
{
	char		user_entry[7];
	char		*to_return;
	int			nb_user_entry;
	static char	*overload = NULL;

	write(1, "prompt> ", 8);
	prompt = malloc_prompt(prompt);
	prompt->buf = overload ? ft_strdup(overload) : NULL;
	to_return = NULL;
	while (to_return == NULL || prompt->quotes != none)
	{
		if (prompt->buf != NULL)
		{
			if (data_react(prompt))
				to_return = check_quotes(prompt, to_return);
		}
		else
		{
			ft_bzero(user_entry, 7);
			nb_user_entry = read(1, user_entry, 6);
			if (user_entry[0] == 27 || user_entry[0] == 127)
				esc_react(prompt, nb_user_entry, user_entry);
			else
			{
				prompt->buf = ft_strdup(user_entry);
				if (nb_user_entry == 6)
				{
					termanip(1);
					while (read(1, user_entry, 6))
					{
						prompt->buf = ft_strjoin(prompt->buf, user_entry);
						ft_bzero(user_entry, 6);
					}
					termanip(1);
				}
				if (data_react(prompt))
					to_return = check_quotes(prompt, to_return);
			}
		}
	}
	overload = (ft_strlen(prompt->buf) > 0 ? ft_strdup(prompt->buf) : NULL);
	free_prompt(prompt);
	return (to_return);
}
