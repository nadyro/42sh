/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:22:04 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/09 20:43:30 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

struct s_cursor_data	*init_cursordata(void)
{
	struct s_cursor_data	*cd;

	if (!(cd = malloc(sizeof(struct s_cursor_data))))
		ft_exit(3);
	cd->x = 0;
	cd->col = 0;
	cd->row = 0;
	cd->pos_x = 0;
	cd->pos_y = 0;
	return (cd);
}

void					move_left(struct s_line_data *ld)
{
	char	*go_to;

	go_to = NULL;
	cursor_pos(ld);
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
