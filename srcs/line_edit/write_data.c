/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 17:19:56 by azybert           #+#    #+#             */
/*   Updated: 2018/08/07 10:15:59 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static void	ft_writenl(char *to_display, size_t tmp)
{
	size_t	k;
	size_t	sp;

	k = 0;
	sp = 0;
	while (sp + k < tmp)
	{
		if (to_display[sp + k] == '\n')
		{
			write(1, &to_display[sp], k + 1);
			write(1, "\r", 1);
			sp = sp + k + 1;
			k = 0;
		}
		else
			k++;
	}
	write(1, &to_display[sp], k + 1);
	write(1, "\r", 1);
}

static void	write_data_aux(t_prompt *prompt, char *to_display, size_t size)
{
	size_t	tmp;
	size_t	displayed;

	displayed = prompt->total - ft_strlen(to_display);
	while (size != 0)
	{
		move_cursor(prompt, displayed, false);
		tputs(tgetstr("ce", NULL), 1, ft_putshit);
		tmp = prompt->size->x - (ft_add_nl(prompt, displayed) +
				prompt->origin->x) % prompt->size->x;
		tmp = ((tmp > size) ? size : tmp);
		ft_writenl(to_display, tmp);
		displayed = displayed + tmp;
		to_display += tmp;
		size -= tmp;
	}
}

void		write_data(t_prompt *prompt, char *to_display, size_t size)
{
	if (prompt->origin->y == 0xffffffffffffffff)
		return ;
	move_cursor(prompt, prompt->pos, true);
	while (prompt->size->y <= prompt->origin->y + (prompt->origin->x +
				ft_add_nl(prompt, prompt->pos + size)) / prompt->size->x)
	{
		move_cursor(prompt, (prompt->size->y - prompt->origin->y) *
				prompt->size->x, false);
		tputs(tgetstr("sf", NULL), 1, ft_putshit);
		prompt->origin->y--;
	}
	if (prompt->origin->y == 0xffffffffffffffff)
		return ;
	write_data_aux(prompt, to_display, size);
}
