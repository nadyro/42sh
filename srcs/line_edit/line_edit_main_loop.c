/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:28:12 by azybert           #+#    #+#             */
/*   Updated: 2018/06/10 13:59:42 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

void		free_prompt(t_prompt *prompt)
{
	free(prompt->line);
	free(prompt->buf);
	free(prompt->origin);
	free(prompt->size);
	free(prompt);
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
	prompt->size->x = w.ws_col;
	prompt->size->y = w.ws_row;
	prompt->quotes = none;
	get_cursor_pos(prompt->origin, prompt);
	return (prompt);
}

t_stat_data	*malloc_stat()
{
	t_stat_data *stat_data;

	if (!(stat_data = malloc(sizeof(*stat_data))))
		exit(1);
	stat_data->overage = NULL;
	stat_data->line_save = 0;
	stat_data->current = NULL;
	stat_data->history = NULL;
	return (stat_data);
}

void		ft_flush(t_prompt *prompt)
{
	char	user_entry[512];
	char	*to_free;

	termanip(3);
	ft_bzero(user_entry, 512);
	while (read(1, user_entry, 511) > 0)
	{
		to_free = prompt->buf;
		prompt->buf = ft_strjoin(prompt->buf, user_entry);
		free(to_free);
		ft_bzero(user_entry, 511);
		termanip(4);
	}
	termanip(3);
}

char		*line_edit_main_loop(void)
{
	char				user_entry[7];
	char				*to_return;
	int					nb_user_entry;
	static t_stat_data	*stat_data = NULL;

	write(1, "prompt> ", 8);
	prompt = malloc_prompt(prompt);
	stat_data = (stat_data ? stat_data : malloc_stat());
	prompt->buf = stat_data->overage;
	to_return = NULL;
	while (to_return == NULL || prompt->quotes != none)
	{
		if (prompt->buf != NULL)
		{
			if (data_react(prompt))
				to_return = quotes_managing(prompt, to_return);
		}
		else
		{
			ft_bzero(user_entry, 7);
			nb_user_entry = read(1, user_entry, 6);
			if (user_entry[0] == 27 || user_entry[0] == 127)
				esc_react(prompt, nb_user_entry, user_entry, stat_data);
			else
			{
				prompt->buf = ft_strdup(user_entry);
				if (nb_user_entry == 6)
					ft_flush(prompt);
				if (data_react(prompt))
					to_return = quotes_managing(prompt, to_return);
			}
		}
	}
	stat_data->overage = (prompt->buf ? ft_strdup(prompt->buf) : NULL);
	//if (prompt->total > 0)
		add_to_history(to_return, stat_data);
	free_prompt(prompt);
	return (to_return);
}