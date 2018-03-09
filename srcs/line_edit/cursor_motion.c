/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 02:23:25 by azybert           #+#    #+#             */
/*   Updated: 2018/03/09 22:44:14 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

int			ft_putshit(int c)
{
	return (write(0, &c, 1));
}

void	ft_cursor_start(t_prompt *prompt)
{
	prompt->pos = 0;
	move_cursor(prompt->pos % prompt->size->x,
			prompt->origin->y + prompt->pos / prompt->size->x);
}

void	ft_cursor_end(t_prompt *prompt)
{
	prompt->pos = prompt->total;
	move_cursor(prompt->pos % prompt->size->x,
			prompt->origin->y + prompt->pos / prompt->size->x);
}

void	ft_cursor_left(t_prompt *prompt)
{
	if (prompt != NULL)
		prompt->pos--;
	move_cursor(prompt->pos % prompt->size->x,
			prompt->origin->y + prompt->pos / prompt->size->x);
}

void	ft_cursor_right(t_prompt *prompt)
{
	if (prompt != NULL)
		prompt->pos++;
	move_cursor(prompt->pos % prompt->size->x,
			prompt->origin->y + prompt->pos / prompt->size->x);
}

void	move_cursor(size_t x, size_t y)
{
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ft_putshit);
}

/*void	ft_cursor_left(t_prompt *prompt)
{
	char	c[3];

	c[0] = 27;
	c[1] = 91;
	c[2] = 68;
	write(1, c, 3);
	if (prompt != NULL)
		prompt->pos--;
}

void	ft_cursor_right(t_prompt *prompt)
{
	char	c[3];

	c[0] = 27;
	c[1] = 91;
	c[2] = 67;
	write(1, c, 3);
	if (prompt != NULL)
		prompt->pos++ ;
}*/
