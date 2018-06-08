/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellanious.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 17:49:29 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/06/08 16:47:44 by kernel_pani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

void	print_endslct(struct s_line_data *ld)
{
	char	*go_to;

	go_to = tgoto(tgetstr("cm", NULL), COLSTART, ld->cd->pos_y);
	tputs(go_to, 1, fprint_char);
	tputs(tgetstr("ce", NULL), 1, fprint_char);
	tputs(tgetstr("me", NULL), 1, fprint_char);
	ft_putscolors(ld->buffer, GREEN);
	go_to = tgoto(tgetstr("cm", NULL), ld->cd->x % ld->sw->win_col, ld->cd->pos_y);
	tputs(go_to, 1, fprint_char);
}
