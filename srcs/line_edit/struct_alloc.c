/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 01:45:43 by azybert           #+#    #+#             */
/*   Updated: 2018/07/07 05:10:34 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

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

void		prompt_origin(t_prompt *prompt, t_stat_data *stat_data)
{
	if (stat_data != NULL && stat_data->line_save >= 100000)
	{
		prompt->origin->x = stat_data->line_save % 100000;
		prompt->origin->y = stat_data->line_save / 100000;
		prompt->origin->y += (prompt->origin->y == prompt->size->y ? -1 : 0);
		move_cursor(prompt, 0, true);
		stat_data->line_save = 0;
	}
	else
		get_cursor_pos(prompt->origin, prompt);
}

t_prompt	*malloc_prompt(t_prompt *prompt, t_stat_data *stat_data)
{
	struct winsize	w;

	if (!(prompt = malloc(sizeof(*prompt))))
		exit(1);
	if (!(prompt->origin = malloc(sizeof(t_coord))))
		exit(1);
	if (!(prompt->size = malloc(sizeof(t_coord))))
		exit(1);
	ioctl(0, TIOCGWINSZ, &w);
	prompt->line = ft_strdup("\0");
	prompt->buf = NULL;
	prompt->pos = 0;
	prompt->total = 0;
	prompt->size->x = w.ws_col;
	prompt->size->y = w.ws_row;
	prompt_origin(prompt, stat_data);
	return (prompt);
}

t_stat_data	*malloc_stat(void)
{
	t_stat_data *stat_data;

	if (!(stat_data = malloc(sizeof(*stat_data))))
		exit(1);
	stat_data->overage = NULL;
	stat_data->old_line = NULL;
	stat_data->copied = NULL;
	stat_data->line_save = 0;
	stat_data->current = NULL;
	stat_data->history = NULL;
	return (stat_data);
}