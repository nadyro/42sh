/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_cursor_motion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 17:23:30 by azybert           #+#    #+#             */
/*   Updated: 2018/03/31 23:17:22 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

void	get_cursor_pos(t_coord *actualize, t_prompt *prompt)
{
	char	buf[100];
	int		loop;

	ft_flush(prompt);
	write(1, "\033[6n", 4);
	ft_bzero(buf, 100);
	read(1, buf, 100);
	actualize->y = ft_atol(&buf[2]) - 1;
	loop = 2;
	while (buf[loop] != ';')
		loop++;
	actualize->x = ft_atol(&buf[loop + 1]) - 1;
}

int		ft_putshit(int c)
{
	return (write(0, &c, 1));
}

void	move_cursor(t_prompt *prompt, size_t new_pos, bool save)
{
	size_t	x;
	size_t	y;

	x = (prompt->origin->x + new_pos) % prompt->size->x;
	y = prompt->origin->y + (prompt->origin->x + new_pos) / prompt->size->x;
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_putshit);
	if (save == true)
		prompt->pos = new_pos;
}
