/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_pst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:18:03 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/18 19:51:45 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

void	manage_cp_pst(char *t, struct s_line_data *ld, char *tmp_buffer)
{
	int		y;
	int		x;
	int		i;

	i = ld->cd->pos_x;
	x = ft_strlen(t);
	y = 0;
	while (y < x)
		ld->buffer[i++] = t[y++];
	i = ld->cd->pos_x + ft_strlen(t);
	y = i;
	x = ft_strlen(t) + ft_strlen(tmp_buffer) + ld->cd->pos_x;
	while (i < x)
		ld->buffer[i++] = '\0';
	i = y;
	y = 0;
	while (i < x)
		ld->buffer[i++] = tmp_buffer[y++];
	ft_strdel(&tmp_buffer);
	write_change(ld, 1);

}

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
		ld->cd->cp_state = 1;
		go_to = tgoto(tgetstr("cm", NULL), COLSTART, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		cursor_pos(ld);
		tputs(tgetstr("ce", NULL), 1, fprint_char);
		if (ld->tmp == NULL)
			ld->tmp = ft_strdup(ld->buffer);
		else
		{
			ft_strdel(&ld->tmp);
			ld->tmp = ft_strdup(ld->buffer);
		}
		*index = 0;
		while (y < i)
			ld->buffer[y++] = '\0';
	}
	if (t == 12)
	{
		ld->cd->cp_state = 1;
		if (ld->tmp == NULL)
			ld->tmp = ft_strdup(ld->buffer);
		else
		{
			ft_strdel(&ld->tmp);
			ld->tmp = ft_strdup(ld->buffer);
		}
	}
	if (t == 16 && ld->tmp != NULL && ld->cd->cp_state == 1)
	{
		if (ld->tmp[0] == '\0')
			ld->cd->cp_state = 0;
		update_linedata(ld->tmp, ld);
		*index += ft_strlen(ld->tmp);
	}
	if (t == 20 && ld->cd->cp_active == 0)
	{
		ld->cd->cp_state = 1;
		ld->cd->cp_active = 1;
		ld->cd->cp_start = ld->cd->pos_x;
	}
	else if(t == 20 && ld->cd->cp_active == 1)
	{
		ld->cd->cp_active = 0;
		go_to = tgoto(tgetstr("cm", NULL), COLSTART, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		tputs(tgetstr("ce", NULL), 1, fprint_char);
		tputs(tgetstr("me", NULL), 1, fprint_char);
		ft_putscolors(ld->buffer, GREEN);
		go_to = tgoto(tgetstr("cm", NULL), ld->cd->x, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		ld->cd->cp_end = ld->cd->pos_x;
		if (ld->cd->cp_end < ld->cd->cp_start)
		{
			i = ld->cd->cp_start - ld->cd->cp_end;
			ld->tmp = ft_strsub(ld->buffer, ld->cd->cp_end, ++i);
		}
		else
		{
			i = ld->cd->cp_end - ld->cd->cp_start;
			ld->tmp = ft_strsub(ld->buffer, ld->cd->cp_start, ++i);
		}
	}
}
