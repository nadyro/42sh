/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:22:04 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/06/08 10:50:20 by kernel_pani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

struct s_cursor_data	*init_cursordata(void)
{
	struct s_cursor_data	*cd;

	if (!(cd = malloc(sizeof(struct s_cursor_data))))
		ft_exit(3);
	cd->x = 0;
	cd->cp_state = 0;
	cd->cp_start = 0;
	cd->cp_end = 0;
	cd->cp_front = 1;
	cd->cp_active = 0;
	cd->avg_cp = 0;
	cd->col = 0;
	cd->row = 0;
	cd->o_pos_x = 0;
	cd->o_pos_y = 0;
	cd->pos_x = 0;
	cd->pos_y = 0;
	return (cd);
}

void					move_left(struct s_line_data *ld)
{
	char	*go_to;

	go_to = NULL;
	cursor_pos(ld);
	if (ld->cd->cp_active == 1)
	{
		tputs(tgetstr("mr", NULL), 1, fprint_char);
		ft_putchar(ld->buffer[ld->cd->pos_x]);
	}
	if (ld->cd->pos_x - 1 >= 0)
	{
		go_to = tgoto(tgetstr("cm", NULL), --ld->cd->x, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
	}
	ld->cd->col = ld->cd->pos_x;
	ld->cd->row = ld->cd->pos_y;
}

void					move_right(struct s_line_data *ld)
{
	char	*go_to;

	go_to = NULL;
	cursor_pos(ld);
	if (ld->cd->cp_active == 1)
	{
		tputs(tgetstr("mr", NULL), 1, fprint_char);
		ft_putchar(ld->buffer[ld->cd->pos_x]);
	}
	if (ld->cd->pos_x < ld->current_size)
	{
		go_to = tgoto(tgetstr("cm", NULL), ++ld->cd->x, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
	}
	ld->cd->col = ld->cd->pos_x;
	ld->cd->row = ld->cd->pos_y;
}

void					move_up(struct s_line_data *ld)
{
	char	*go_to;

	go_to = NULL;
	cursor_pos(ld);
	if (ld->cd->row - 1 >= 0)
	{
		go_to = tgoto(tgetstr("cm", NULL), ld->cd->x, --ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
	}
	ld->cd->col = ld->cd->pos_x;
	ld->cd->row = ld->cd->pos_y;
}

void					move_down(struct s_line_data *ld)
{
	char	*go_to;

	go_to = NULL;
	go_to = tgoto(tgetstr("cm", NULL), ld->cd->x, ++ld->cd->pos_y);
	cursor_pos(ld);
	tputs(go_to, 1, fprint_char);
	ld->cd->col = ld->cd->pos_x;
	ld->cd->row = ld->cd->pos_y;
}
