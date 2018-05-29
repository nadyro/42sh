/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 17:01:52 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/29 21:29:26 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

void	gt_start_end_del(struct s_line_data *ld, char t, int *index)
{
	char	*go_to;

	go_to = NULL;
	if (t == 1)
	{
		ld->c = 0;
		go_to = tgoto(tgetstr("cm", NULL), ld->c + COLSTART, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		ld->cd->x = COLSTART;
		ld->cd->pos_x = ld->cd->x - COLSTART;
	}
	if (t == 5)
	{
		ld->c = ld->current_size;
		go_to = tgoto(tgetstr("cm", NULL),
				COLSTART + ld->c, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		ld->cd->x = COLSTART + ld->current_size;
		ld->cd->pos_x = ld->cd->x - COLSTART;
	}
	if (t == 127)
	{
		if (*index - 1 >= 0)
			*index -= 1;
		if (ld->buffer[0] != '\0')
			manage_deletion(ld);
	}
}

void	cp_cut(struct s_line_data *ld, int *index, char t)
{
	char	*go_to;
	int		i;
	int		y;

	y = 0;
	i = 1024 * ld->nb_resize;
	go_to = NULL;
	if (t == 11)
	{
		ld->cd->cp_state = 1;
		go_to = tgoto(tgetstr("cm", NULL), COLSTART, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		ld->cd->x = COLSTART;
		ld->cd->pos_x = ld->cd->x - COLSTART;
		tputs(tgetstr("ce", NULL), 1, fprint_char);
		if (ld->tmp == NULL)
			ld->tmp = ft_strdup(ld->buffer);
		else
		{
			ft_strdel(&ld->tmp);
			ld->tmp = ft_strdup(ld->buffer);
		}
		*index = 0;
		ld->c = 0;
		while (y < i)
			ld->buffer[y++] = '\0';
	}
}

void	cp_copy_select_cp(struct s_line_data *ld, char t)
{
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
	if (t == 20 && ld->cd->cp_active == 0)
	{
		ld->cd->cp_state = 1;
		ld->cd->cp_active = 1;
		ld->cd->cp_start = ld->c;
	}
}

void	cp_paste(struct s_line_data *ld, char t, int *index)
{
	if (t == 16 && ld->tmp != NULL && ld->cd->cp_state == 1)
	{
		if (ld->tmp[0] == '\0')
			ld->cd->cp_state = 0;
		update_linedata(ld->tmp, ld);
		ld->c += ft_strlen(ld->tmp);
		*index += ft_strlen(ld->tmp);
	}
}

void	cp_end_select_cp(struct s_line_data *ld, char t)
{
	char	*go_to;
	int		i;

	go_to = NULL;
	i = 0;
	if (t == 20 && ld->cd->cp_active == 1)
	{
		ld->cd->cp_active = 0;
		print_endslct(ld);
		ld->cd->cp_end = ld->c;
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
