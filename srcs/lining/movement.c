/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 22:18:35 by kernel_pani       #+#    #+#             */
/*   Updated: 2018/04/21 22:43:38 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

void	move_left(int *index, struct line_data *ld)
{
	int	x;
	int	i;

	x = 0;
	i = *index;
	tputs(tgetstr("cl", NULL), 1, fprint_char);
	if (i - 1 >= 0)
		i--;
	while (ld->buffer[x] != '\0')
	{
		if (x == i)
		{
			tputs(tgetstr("mr", NULL), 1, fprint_char);
			ft_putchar(ld->buffer[x]);
			tputs(tgetstr("me", NULL), 1, fprint_char);
		}
		else
			ft_putchar(ld->buffer[x]);
		x++;
	}
	*index = i;

}

void	move_right(int *index, struct line_data *ld)
{
	int	i;
	int	x;

	i = *index;
	x = 0;
	tputs(tgetstr("cl", NULL), 1, fprint_char);
	if ((unsigned long)(i + 1) <= ft_strlen(ld->buffer))
		i++;
	while (ld->buffer[x] != '\0')
	{
		if (x == i)
		{
			tputs(tgetstr("mr", NULL), 1, fprint_char);
			ft_putchar(ld->buffer[x]);
			tputs(tgetstr("me", NULL), 1, fprint_char);
		}
		else
			ft_putchar(ld->buffer[x]);
		x++;
	}
	*index = i;
}
