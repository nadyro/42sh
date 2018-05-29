/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:27:29 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/29 22:44:23 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

void	ft_exit(int nb)
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

void	write_change(struct s_line_data *ld, int is_rewrite)
{
	int		y;
	char	*go_to;

	y = 0;
	ld->current_size = ft_strlen(ld->buffer);
	if (ld->c < ld->current_size)
		y = ld->c;
	else
	{
		ft_putnbr(ld->c);
		sleep(2);
	}
	tputs(tgetstr("ce", NULL), 1, fprint_char);
	ft_putstr("\x1B[31m");
	while (ld->buffer[y])
		ft_putchar(ld->buffer[y++]);
	ft_putstr("\x1B[0m");
	if (is_rewrite == 0)
	{
		go_to = tgoto(tgetstr("cm", NULL), ++ld->c + COLSTART, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		++ld->cd->x;
		ld->cd->pos_x = ld->cd->x - COLSTART;
	}
	else if (ld->tmp != NULL)
	{
		ld->cd->x += ft_strlen(ld->tmp);
		go_to = tgoto(tgetstr("cm", NULL), ld->cd->x, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		ld->cd->pos_x = ld->cd->x - COLSTART;
	}
}

void	write_fromstart(struct s_line_data *ld, int is_todel)
{
	char	*go_to;

	/*ft_putnbr(ld->cd->o_pos_y);
	ft_putchar('-');
	ft_putnbr(ld->cd->pos_y);
	ft_putchar('-');
	ft_putnbr(ld->nb_lines);
	sleep(2);*/
	go_to = tgoto(tgetstr("cm", NULL), ld->cd->o_pos_x + COLSTART, ld->cd->o_pos_y - ld->nb_lines);
	tputs(go_to, 1, fprint_char);
	tputs(tgetstr("ce", NULL), 1, fprint_char);
	ft_putstr(ld->buffer);
	if (is_todel == 1)
		go_to = tgoto(tgetstr("cm", NULL), (ld->c - 1) + COLSTART, ld->cd->pos_y);
	else
		go_to = tgoto(tgetstr("cm", NULL), ld->c + COLSTART, ld->cd->pos_y);
	tputs(go_to, 1, fprint_char);
}
