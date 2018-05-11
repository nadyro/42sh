/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_pst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:18:03 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/11 18:26:51 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

void	manage_controls(char t, struct s_line_data *ld, int *index)
{
	char	*go_to;
	int		i;
	int		y;

	go_to = NULL;
	i = 1024 * ld->nb_resize;
	y = 0;
	if (t == 1)
	{
		go_to = tgoto(tgetstr("cm", NULL), COLSTART, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
	}
	if (t == 5)
	{
		go_to = tgoto(tgetstr("cm", NULL), COLSTART + ld->current_size, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
	}
	if (t == 11)
	{
		go_to = tgoto(tgetstr("cm", NULL), COLSTART, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		cursor_pos(ld);
		tputs(tgetstr("ce", NULL), 1, fprint_char);
		ld->tmp = ft_strdup(ld->buffer);
		*index = 0;
		while (y < i)
			ld->buffer[y++] = '\0';
	}
	if (t == 16 && ld->tmp != NULL)
	{
		//to continue
		update_linedata(ld->tmp[0], ld);
		*index += ft_strlen(ld->tmp);
	}
}
