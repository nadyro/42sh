/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_cursor_motion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 17:23:30 by azybert           #+#    #+#             */
/*   Updated: 2018/08/10 16:50:35 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static void	get_cursor_pos_aux(t_coord *actualize, t_g_prpt *g_prpt)
{
	actualize->x = 0;
	tputs(tgetstr("mr", NULL), 1, ft_putshit);
	write(1, "%", 1);
	tputs(tgetstr("me", NULL), 1, ft_putshit);
	actualize->y = actualize->y + 1;
	if (actualize->y >= g_prpt->size->y)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, g_prpt->size->y), 1, ft_putshit);
		tputs(tgetstr("sf", NULL), 1, ft_putshit);
		actualize->y--;
		tputs(tgoto(tgetstr("cm", NULL), 0, actualize->y), 1, ft_putshit);
	}
}

void		get_cursor_pos(t_coord *actualize, t_g_prpt *g_prpt)
{
	char	buf[80];
	int		loop;

	ft_bzero(buf, 80);
	while (buf[0] != 27)
	{
		ft_bzero(buf, 80);
		ft_flush(g_prpt);
		write(0, "\033[6n", 4);
		read(0, buf, 79);
	}
	actualize->y = ft_atol(&buf[2]) - 1;
	loop = 2;
	while (buf[loop] != '\0' && buf[loop] != ';')
		loop++;
	actualize->x = ft_atol(&buf[loop + 1]) - 1;
	if (actualize->x > g_prpt->size->x || actualize->y > g_prpt->size->y)
	{
		actualize->x = 0;
		actualize->y = 0;
	}
	if (actualize->x != 0)
		get_cursor_pos_aux(actualize, g_prpt);
	move_cursor(g_prpt, 0, true);
	tputs(tgetstr("cd", NULL), 0, ft_putshit);
}

int			ft_putshit(int c)
{
	return (write(0, &c, 1));
}

size_t		ft_add_nl(t_g_prpt *g_prpt, size_t new_pos)
{
	size_t loop;
	size_t to_add;

	loop = 0;
	to_add = 0;
	if (g_prpt->line == NULL)
		return (0);
	while (loop < new_pos)
	{
		if (loop < g_prpt->total && g_prpt->line[loop] == '\n')
		{
			to_add += g_prpt->size->x -
				((loop + to_add + g_prpt->origin->x) % g_prpt->size->x);
		}
		loop++;
	}
	if (to_add != 0)
		to_add--;
	return (new_pos + to_add);
}

void		move_cursor(t_g_prpt *g_prpt, size_t new_pos, bool save)
{
	size_t	x;
	size_t	y;

	if (save == true)
		g_prpt->pos = new_pos;
	if (g_prpt->line != NULL && ft_strchr(g_prpt->line, '\n') != NULL)
		new_pos = ft_add_nl(g_prpt, new_pos);
	x = (g_prpt->origin->x + new_pos) % g_prpt->size->x;
	y = g_prpt->origin->y + (g_prpt->origin->x + new_pos) / g_prpt->size->x;
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_putshit);
}
