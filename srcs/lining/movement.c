/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:22:04 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/04/23 23:43:12 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

struct s_cursor_data	*init_cursordata(void)
{
	struct s_cursor_data	*cd;
	int						i;

	i = 0;
	if (!(cd = malloc(sizeof(struct s_cursor_data))))
		return (NULL);
	cd->pos_x = 0;
	cd->pos_y = 0;
	cd->col = 0;
	cd->row = 0;
	ft_bzero(cd->buffer, BUFFER);
	return (cd);
}

void	move_left(int *index, struct s_line_data *ld)
{
	int		i;

	i = *index;
	cursor_pos(ld);
	if (ld->cd->pos_x - 1 >= 0)
	{
		ld->edit_mode = 1;
		tputs(tgoto(tgetstr("cm", NULL), --ld->cd->pos_x, ld->cd->pos_y), 1, fprint_char);
	}
	else
		ld->edit_mode = 0;
	ld->cd->col = ld->cd->pos_x;
	ld->cd->row = ld->cd->pos_y;
	*index = i;
}

void	move_right(int *index, struct s_line_data *ld)
{
	int						i;

	i = *index;
	cursor_pos(ld);
	if (ld->cd->pos_x < ld->current_size)
	{
		ld->edit_mode = 1;
		tputs(tgoto(tgetstr("cm", NULL), ++ld->cd->pos_x, ld->cd->pos_y), 1, fprint_char);
	}
	else
		ld->edit_mode = 0;
	ld->cd->col = ld->cd->pos_x;
	ld->cd->row = ld->cd->pos_y;
	*index = i;
}

void	move_up(int *index, struct s_line_data *ld)
{
	int		i;

	i = *index;
	cursor_pos(ld);
	if (ld->cd->row - 1 >= 0)
		tputs(tgoto(tgetstr("cm", NULL), ld->cd->pos_x, --ld->cd->pos_y), 1, fprint_char);
	ld->cd->col = ld->cd->pos_x;
	ld->cd->row = ld->cd->pos_y;
	*index = i;
}

void	move_down(int *index, struct s_line_data *ld)
{
	int		i;

	i = *index;
	cursor_pos(ld);
	tputs(tgoto(tgetstr("cm", NULL), ld->cd->pos_x, ++ld->cd->pos_y), 1, fprint_char);
	ld->cd->col = ld->cd->pos_x;
	ld->cd->row = ld->cd->pos_y;
	*index = i;
}
