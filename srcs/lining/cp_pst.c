/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cp_pst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:18:03 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/29 21:33:46 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

void	manage_key_insertion(char *t, struct s_line_data *ld, char *tmp_buffer)
{
	int		i;
	int		y;

	y = 0;
	ld->buffer[ld->c] = t[0];
	i = ld->c + 1;
	while (ld->buffer[i] != '\0')
		ld->buffer[i++] = tmp_buffer[y++];
	ft_strdel(&tmp_buffer);
	write_change(ld, 0);
}

void	manage_cp_pst(char *t, struct s_line_data *ld, char *tmp_buffer)
{
	int		y;
	int		x;
	int		i;

	i = ld->c;
	x = ft_strlen(t);
	y = 0;
	while (y < x)
		ld->buffer[i++] = t[y++];
	i = ld->c + ft_strlen(t);
	y = i;
	x = ft_strlen(t) + ft_strlen(tmp_buffer) + ld->c;
	while (i < x && i < BUFFER * ld->nb_resize)
		ld->buffer[i++] = '\0';
	i = y;
	y = 0;
	while (i < x && i < BUFFER * ld->nb_resize)
		ld->buffer[i++] = tmp_buffer[y++];
	ft_strdel(&tmp_buffer);
	write_change(ld, 1);
}

void	manage_controls(char t, struct s_line_data *ld, int *index)
{
	if (t == 1 || t == 5 || t == 127)
		gt_start_end_del(ld, t, index);
	if (t == 11)
		cp_cut(ld, index, t);
	if (t == 12)
		cp_copy_select_cp(ld, t);
	if (t == 20 && ld->cd->cp_active == 0)
		cp_copy_select_cp(ld, t);
	else if (t == 20 && ld->cd->cp_active == 1)
		cp_end_select_cp(ld, t);
	if (t == 16 && ld->tmp != NULL && ld->cd->cp_state == 1)
		cp_paste(ld, t, index);
}

void	skip_word_right(struct s_line_data *ld)
{
	int		i;
	int		y;
	char	*go_to;

	i = ld->c;
	y = 0;
	while (ld->buffer[i] != '\0')
	{
		while (ld->buffer[i] && (ld->buffer[i] == ' '
					|| ld->buffer[i] == '\n' || ld->buffer[i] == '\t'))
			i++;
		while (ld->buffer[i] && ld->buffer[i] != ' '
				&& ld->buffer[i] != '\n' && ld->buffer[i] != '\t')
			i++;
		y = 1;
		break ;
		i++;
	}
	if (y == 1)
	{
		ld->c = i;
		go_to = tgoto(tgetstr("cm", NULL), COLSTART + i, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		ld->cd->x = COLSTART + i;
		ld->cd->pos_x = ld->cd->x - COLSTART;
	}
}

void	skip_word_left(struct s_line_data *ld)
{
	int		i;
	int		y;
	char	*go_to;

	i = ld->c;
	y = 0;
	while (i != 0)
	{
		while (i > 0 && (ld->buffer[i] == ' '
					|| ld->buffer[i] == '\n' || ld->buffer[i] == '\t'))
			i--;
		while (i > 0 && ld->buffer[i] != ' '
				&& ld->buffer[i] != '\n' && ld->buffer[i] != '\t')
			i--;
		y = 1;
		break ;
		i--;
	}
	if (y == 1)
	{
		ld->c = i;
		go_to = tgoto(tgetstr("cm", NULL), (COLSTART) + i, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		ld->cd->x = COLSTART + i;
		ld->cd->pos_x = ld->cd->x - COLSTART;
	}
}
