/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 01:45:43 by azybert           #+#    #+#             */
/*   Updated: 2018/08/09 08:41:30 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void		free_prompt(t_prompt *prompt)
{
	free(prompt->line);
	prompt->line = NULL;
	free(prompt->buf);
	prompt->buf = NULL;
	free(prompt->disp);
	prompt->disp = NULL;
	free(prompt->origin);
	prompt->origin = NULL;
	free(prompt->size);
	prompt->size = NULL;
	free(prompt);
	prompt = NULL;
}

static void	prompt_origin(t_prompt *prompt, t_stat_data *stat_data)
{
	long int	nbr;

	if (stat_data != NULL && stat_data->old_line != NULL)
	{
		nbr = atol(stat_data->old_line);
		prompt->origin->x = nbr % 100000;
		prompt->origin->y = nbr / 100000;
		prompt->origin->y += (prompt->origin->y == prompt->size->y ? -1 : 0);
		move_cursor(prompt, 0, true);
		free(stat_data->old_line);
		stat_data->old_line = NULL;
	}
	else
		get_cursor_pos(prompt->origin, prompt);
}

t_prompt	*malloc_prompt(t_prompt *prompt, t_stat_data *stat_data,
		char *d_prompt)
{
	struct winsize	w;

	if (!(prompt = malloc(sizeof(*prompt))))
		exit(1);
	if (!(prompt->origin = malloc(sizeof(t_coord))))
		exit(1);
	if (!(prompt->size = malloc(sizeof(t_coord))))
		exit(1);
	ioctl(0, TIOCGWINSZ, &w);
	if (!(prompt->line = ft_strdup("\0")))
		exit(1);
	if (!(prompt->disp = ft_strdup(d_prompt)))
		exit(1);
	prompt->buf = NULL;
	prompt->pos = 0;
	prompt->total = 0;
	prompt->size->x = w.ws_col;
	prompt->size->y = w.ws_row;
	prompt->end = 0;
	prompt->current = NULL;
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
	return (stat_data);
}
