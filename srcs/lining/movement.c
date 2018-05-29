/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:22:04 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/29 21:59:06 by nsehnoun         ###   ########.fr       */
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
	cd->pos_x = 0;
	cd->pos_y = 0;
	cd->o_pos_x = 0;
	cd->o_pos_y = 0;
	return (cd);
}

void					move_left(struct s_line_data *ld)
{
	char	*go_to;

	go_to = NULL;
	if (ld->cd->cp_active == 1)
	{
		tputs(tgetstr("mr", NULL), 1, fprint_char);
		ft_putchar(ld->buffer[ld->c]);
	}
	if (ld->c - 1 >= 0)
	{
		go_to = tgoto(tgetstr("cm", NULL), --ld->c + COLSTART, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
	}
	--ld->cd->x;
	ld->cd->pos_x = ld->cd->x - COLSTART;
}

void					move_right(struct s_line_data *ld)
{
	char	*go_to;

	go_to = NULL;
	if (ld->cd->cp_active == 1)
	{
		tputs(tgetstr("mr", NULL), 1, fprint_char);
		ft_putchar(ld->buffer[ld->c]);
	}
	if (ld->c < ld->current_size)
	{
		go_to = tgoto(tgetstr("cm", NULL), ++ld->c + COLSTART, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
	}
	++ld->cd->x;
	ld->cd->pos_x = ld->cd->x - COLSTART;
}

void					move_up(struct s_line_data *ld)
{
	char	*go_to;

	go_to = NULL;
	if (ld->cd->row - 1 >= 0)
	{
		go_to = tgoto(tgetstr("cm", NULL), ld->c + COLSTART, --ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
	}
}

void					move_down(struct s_line_data *ld)
{
	char	*go_to;

	go_to = NULL;
	go_to = tgoto(tgetstr("cm", NULL), ld->c + COLSTART, ++ld->cd->pos_y);
	tputs(go_to, 1, fprint_char);
}
