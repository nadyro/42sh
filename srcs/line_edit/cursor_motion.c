/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 02:23:25 by azybert           #+#    #+#             */
/*   Updated: 2018/03/09 18:01:58 by azybert          ###   ########.fr       */
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
	if (prompt != NULL)
		prompt->pos--;
	tputs(tgetstr("le", NULL), 1, ft_putshit);
	//	move_cursor(prompt, --prompt->pos,
	//			prompt->origin->y + prompt->pos / prompt->size->x);
}

void	ft_cursor_right(t_prompt *prompt)
{
	if (prompt != NULL)
		prompt->pos++;
	if (prompt->pos % prompt->size->x == 0)
		move_cursor(prompt, 0,
				prompt->origin->y + prompt->pos / prompt->size->x);
	else
		move_cursor(prompt, prompt->pos % prompt->size->x,
				prompt->origin->y + prompt->pos / prompt->size->x);
}

void	move_cursor(t_prompt *prompt, size_t x, size_t y)
{
	if (prompt == NULL)
		;
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
