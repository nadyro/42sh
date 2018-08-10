/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 01:45:43 by azybert           #+#    #+#             */
/*   Updated: 2018/08/10 16:50:35 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void		free_g_prpt(t_g_prpt *g_prpt)
{
	free(g_prpt->line);
	g_prpt->line = NULL;
	free(g_prpt->buf);
	g_prpt->buf = NULL;
	free(g_prpt->disp);
	g_prpt->disp = NULL;
	free(g_prpt->origin);
	g_prpt->origin = NULL;
	free(g_prpt->size);
	g_prpt->size = NULL;
	free(g_prpt);
	g_prpt = NULL;
}

static void	g_prpt_origin(t_g_prpt *g_prpt, t_stat_data *stat_data)
{
	long int	nbr;

	if (stat_data != NULL && stat_data->old_line != NULL)
	{
		nbr = atol(stat_data->old_line);
		g_prpt->origin->x = nbr % 100000;
		g_prpt->origin->y = nbr / 100000;
		g_prpt->origin->y += (g_prpt->origin->y == g_prpt->size->y ? -1 : 0);
		move_cursor(g_prpt, 0, true);
		free(stat_data->old_line);
		stat_data->old_line = NULL;
	}
	else
		get_cursor_pos(g_prpt->origin, g_prpt);
}

t_g_prpt	*malloc_g_prpt(t_g_prpt *g_prpt, t_stat_data *stat_data,
		char *d_g_prpt)
{
	struct winsize	w;

	if (!(g_prpt = malloc(sizeof(*g_prpt))))
		exit(1);
	if (!(g_prpt->origin = malloc(sizeof(t_coord))))
		exit(1);
	if (!(g_prpt->size = malloc(sizeof(t_coord))))
		exit(1);
	ioctl(0, TIOCGWINSZ, &w);
	if (!(g_prpt->line = ft_strdup("\0")))
		exit(1);
	if (!(g_prpt->disp = ft_strdup(d_g_prpt)))
		exit(1);
	g_prpt->buf = NULL;
	g_prpt->pos = 0;
	g_prpt->total = 0;
	g_prpt->size->x = w.ws_col;
	g_prpt->size->y = w.ws_row;
	g_prpt->end = 0;
	g_prpt->current = NULL;
	g_prpt_origin(g_prpt, stat_data);
	return (g_prpt);
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
