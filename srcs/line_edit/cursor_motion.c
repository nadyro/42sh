/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_cursor_motion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 17:23:30 by azybert           #+#    #+#             */
/*   Updated: 2018/08/08 23:45:43 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	get_cursor_pos_aux(t_coord *actualize)
{
	actualize->x = 0;
	tputs(tgetstr("mr", NULL), 1, ft_putshit);
	write(1, "%", 1);
	tputs(tgetstr("me", NULL), 1, ft_putshit);
	actualize->y++;
	if (actualize->y >= prompt->size->y)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, prompt->size->y), 1, ft_putshit);
		tputs(tgetstr("sf", NULL), 1, ft_putshit);
		actualize->y--;
		tputs(tgoto(tgetstr("cm", NULL), 0, actualize->y), 1, ft_putshit);
	}
}

void	get_cursor_pos(t_coord *actualize, t_prompt *prompt)
{
	char	buf[80];
	int		loop;

	ft_bzero(buf, 80);
	while (buf[0] != 27)
	{
		ft_bzero(buf, 80);
		ft_flush(prompt);
		write(0, "\033[6n", 4);
		read(0, buf, 79);
	}
	actualize->y = ft_atol(&buf[2]) - 1;
	loop = 2;
	while (buf[loop] != '\0' && buf[loop] != ';')
		loop++;
	actualize->x = ft_atol(&buf[loop + 1]) - 1;
	if (actualize->x > prompt->size->x || actualize->y > prompt->size->y)
	{
		actualize->x = 0;
		actualize->y = 0;
	}
	if (actualize->x != 0)
		get_cursor_pos_aux(actualize);
	move_cursor(prompt, 0, true);
	tputs(tgetstr("cd", NULL), 0, ft_putshit);
}

int		ft_putshit(int c)
{
	return (write(0, &c, 1));
}

size_t	ft_add_nl(t_prompt *prompt, size_t new_pos)
{
	size_t loop;
	size_t to_add;

	loop = 0;
	to_add = 0;
	if (prompt->line == NULL)
		return (0);
	while (loop < new_pos)
	{
		if (loop < prompt->total && prompt->line[loop] == '\n')
		{
			to_add += prompt->size->x -
				((loop + to_add + prompt->origin->x) % prompt->size->x);
		}
		loop++;
	}
	if (to_add != 0)
		to_add--;
	return (new_pos + to_add);
}

void	move_cursor(t_prompt *prompt, size_t new_pos, bool save)
{
	size_t	x;
	size_t	y;

	if (save == true)
		prompt->pos = new_pos;
	if (prompt->line != NULL && ft_strchr(prompt->line, '\n') != NULL)
		new_pos = ft_add_nl(prompt, new_pos);
	x = (prompt->origin->x + new_pos) % prompt->size->x;
	y = prompt->origin->y + (prompt->origin->x + new_pos) / prompt->size->x;
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_putshit);
}
