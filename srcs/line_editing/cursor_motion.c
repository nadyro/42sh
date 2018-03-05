/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 02:23:25 by azybert           #+#    #+#             */
/*   Updated: 2018/03/04 22:41:15 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"

int			ft_putshit(int c)
{
	return (write(0, &c, 1));
}

void	ft_cursor_start(t_prompt *prompt)
{
	while (prompt->line_pos > 0)
		ft_cursor_left(prompt);
}

void	ft_cursor_end(t_prompt *prompt)
{
	while (prompt->line_pos < prompt->total)
		ft_cursor_right(prompt);
}

void	ft_cursor_left(t_prompt *prompt)
{
	tputs(tgetstr("le", NULL), 1, ft_putshit);
	if (prompt != NULL)
		prompt->line_pos--;
}

void	ft_cursor_right(t_prompt *prompt)
{
	tputs(tgetstr("nd", NULL), 1, ft_putshit);
	if (prompt != NULL)
		prompt->line_pos++;
}

/*void	ft_cursor_left(t_prompt *prompt)
{
	char	c[3];

	c[0] = 27;
	c[1] = 91;
	c[2] = 68;
	write(1, c, 3);
	if (prompt != NULL)
		prompt->line_pos--;
}

void	ft_cursor_right(t_prompt *prompt)
{
	char	c[3];

	c[0] = 27;
	c[1] = 91;
	c[2] = 67;
	write(1, c, 3);
	if (prompt != NULL)
		prompt->line_pos++ ;
}*/
