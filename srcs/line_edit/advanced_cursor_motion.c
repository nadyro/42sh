/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_cursor_motion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 21:42:41 by azybert           #+#    #+#             */
/*   Updated: 2018/06/17 22:00:26 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

void	ft_cursor_up(t_prompt *prompt)
{
	size_t	tmp;
	size_t	tmp2;
	size_t	loop;

	if (ft_strchr(prompt->line, '\n'))
	{
		loop = 0;
		while (loop < prompt->size->x && loop != prompt->pos)
		{
			if (prompt->line[prompt->pos - loop] == '\n')
			{
				tmp = (ft_add_nl(prompt, prompt->pos - loop) + prompt->origin->x) % prompt->size->x;
				tmp = prompt->pos - tmp - 1;
				/*if (loop == 0)
				{
					while ()
						loop < prompt->size->x && loop != prompt->pos;
					tmp2 = (ft_add_nl(prompt, prompt->pos - loop) + prompt->origin->x) % prompt->size->x;
					tmp2 = prompt->pos - tmp - 1;
				}*/
				loop = prompt->size->x;
			}
			loop++;
		}
	}
	else
		tmp = prompt->pos + prompt->size->x;
	if (tmp < prompt->pos)
		move_cursor(prompt, tmp, true);
}

void	ft_cursor_down(t_prompt *prompt)
{
	size_t	tmp;
	size_t	loop;

	if (ft_strchr(prompt->line, '\n'))
	{
		loop = 0;
		while (loop < prompt->size->x && prompt->line[prompt->pos + loop])
		{
			if (prompt->line[prompt->pos + loop] == '\n')
			{
				tmp = prompt->pos + loop + 1 + ((ft_add_nl(prompt, prompt->pos) + prompt->origin->x)
					% prompt->size->x);
				if ((prompt->origin->y + (prompt->origin->x + ft_add_nl(prompt, tmp)) / prompt->size->x) - 1 !=
					(prompt->origin->y + (prompt->origin->x + ft_add_nl(prompt, prompt->pos)) / prompt->size->x))
					tmp = ft_strchr(&prompt->line[prompt->pos + loop + 1], '\n') - &prompt->line[0];
				loop = prompt->size->x;
			}
			loop++;
		}
	}
	else
		tmp = prompt->pos + prompt->size->x;
	if (tmp <= prompt->total)
		move_cursor(prompt, tmp, true);
}

void	ft_cursor_word_left(t_prompt *prompt)
{
	if (prompt->pos != prompt->total ||
			ft_isspace(prompt->line[prompt->pos - 1]))
		while (prompt->pos > 0 &&
				!(ft_isspace(prompt->line[prompt->pos])))
			prompt->pos--;
	while (prompt->pos > 0 &&
			ft_isspace(prompt->line[prompt->pos]))
		prompt->pos--;
	while (prompt->pos > 0 &&
			!(ft_isspace(prompt->line[prompt->pos])))
		prompt->pos--;
	if (prompt->pos != 0)
		prompt->pos++;
	move_cursor(prompt, prompt->pos, true);
}

void	ft_cursor_word_right(t_prompt *prompt)
{
	while (prompt->pos < prompt->total &&
			!(ft_isspace(prompt->line[prompt->pos])))
		prompt->pos++;
	while (prompt->pos < prompt->total &&
			ft_isspace(prompt->line[prompt->pos]))
		prompt->pos++;
	move_cursor(prompt, prompt->pos, true);
}
