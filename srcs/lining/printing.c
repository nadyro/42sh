/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:27:29 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/09 20:48:40 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

void		ft_exit(int nb)
{
	if (nb == 3)
	{
		ft_putstr("Allocation error");
		exit(3);
	}
}

int		fprint_char(int c)
{
	ft_putchar_fd(c, 2);
	return (0);
}

void	ft_putscolors(char *str, char *color)
{
	ft_putstr(color);
	ft_putstr(str);
	ft_putstr(NORMAL);
}

void	write_change(struct s_line_data *ld)
{
	int		y;
	char	*go_to;

	y = 0;
	ld->current_size = ft_strlen(ld->buffer);
	if (ld->cd->pos_x < ld->current_size)
		y = ld->cd->pos_x;
	tputs(tgetstr("ce", NULL), 1, fprint_char);
	ft_putstr("\x1B[31m");
	while (ld->buffer[y])
		ft_putchar(ld->buffer[y++]);
	ft_putstr("\x1B[0m");
	go_to = tgoto(tgetstr("cm", NULL), ++ld->cd->x, ld->cd->pos_y);
	tputs(go_to, 1, fprint_char);
	ld->cd->col = ld->cd->pos_x;
	ld->cd->row = ld->cd->pos_y;
}
