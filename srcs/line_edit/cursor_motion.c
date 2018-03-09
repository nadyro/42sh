/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 02:23:25 by azybert           #+#    #+#             */
/*   Updated: 2018/03/07 16:32:23 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/42sh_line_edit.h"

int			ft_putshit(int c)
{
	return (write(0, &c, 1));
}

/*void	ft_cursor_start(t_prompt *prompt)
{
	while (prompt->pos > 0)
		ft_cursor_left(prompt);
}

void	ft_cursor_end(t_prompt *prompt)
{
	while (prompt->pos < prompt->total)
		ft_cursor_right(prompt);
}*/

void	ft_cursor_left(t_prompt *prompt)
{
	if (prompt == NULL)
		tputs(tgetstr("le", NULL), 1, ft_putshit);
	else
	{
		prompt->pos--;
		move_cursor(prompt, -1, 0);
	}
}

void	ft_cursor_right(t_prompt *prompt)
{
	if (prompt == NULL)
		tputs(tgetstr("nd", NULL), 1, ft_putshit);
	else
	{
		prompt->pos++;
		move_cursor(prompt, 1, 0);
	}
}

void	move_cursor(t_prompt *prompt, size_t x, size_t y)
{
	char	*res;

	res = tgetstr("cm", NULL);
	//prompt->present->x += x;
	//prompt->present->y += y;
	y = 0;
	x = y;
	y = x;
	tputs(tgoto(res, prompt->pos, prompt->origin->y),
			1, ft_putshit);
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
