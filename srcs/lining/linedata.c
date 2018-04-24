/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:20:32 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/04/24 16:41:00 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

struct s_line_data	*init_linedata(void)
{
	struct s_line_data	*ld;
	int					s;

	s = 0;
	if (!(ld = malloc(sizeof(struct s_line_data))))
		return (NULL);
	ld->nb_resize = 0;
	ld->content = NULL;
	ld->old_content = NULL;
	while (s < BUFFER)
		ld->buffer[s++] = '\0';
	s = 0;
	ld->length = 0;
	ld->current_size = 0;
	ld->edit_mode = 0;
	while (s < 512)
		ld->resize_history[s++] = -1;
	ld->nb_resize = 0;
	ld->cd = init_cursordata();
	return (ld);
}

void				reallocate_mem_line(int *s, struct s_line_data *ld)
{
	int		i;
	char	*join_tmp;

	i = 0;
	if (ld->nb_resize > 0)
		join_tmp = ft_strjoin(ld->old_content, ld->buffer);
	else
		join_tmp = ft_strdup(ld->buffer);
	ld->old_content = ft_strdup(join_tmp);
	ft_strdel(&join_tmp);
	ld->length = ft_strlen(ld->old_content);
	ld->resize_history[ld->nb_resize] = ft_strlen(ld->buffer);
	ld->nb_resize++;
	while (i < BUFFER)
		ld->buffer[i++] = '\0';
	*s = 0;
}

void				update_linedata(char t, struct s_line_data *ld)
{
	int		i;
	int		y;
	char		tmp_buffer[BUFFER];

	cursor_pos(ld);
	i = ld->cd->pos_x;
	y = 0;
	ft_bzero(tmp_buffer, BUFFER);
	while (ld->buffer[i] != '\0')
	{
		tmp_buffer[y] = ld->buffer[i];
		i++;
		y++;
	}
	ld->buffer[ld->cd->pos_x] = t;
	i = ld->cd->pos_x + 1;
	y = 0;
	while (ld->buffer[i] != '\0')
	{
		ld->buffer[i] = tmp_buffer[y];
		i++;
		y++;
	}
	ld->current_size = ft_strlen(ld->buffer);
	if (ld->cd->pos_x < ld->current_size)
		y = ld->cd->pos_x;
	tputs(tgetstr("ce", NULL), 1, fprint_char);
	ft_putstr("\x1B[31m");
	while (ld->buffer[y])
		ft_putchar(ld->buffer[y++]);
	ft_putstr("\x1B[0m");
	tputs(tgoto(tgetstr("cm", NULL), ++ld->cd->pos_x, ld->cd->pos_y), 1, fprint_char);
	ld->cd->col = ld->cd->pos_x;
	ld->cd->row = ld->cd->pos_y;
}

void				print_line_data(struct s_line_data *ld)
{
	int		i;

	i = 0;
	ft_putstr("Content : ");
	if (ld->content)
		ft_putendl(ld->content);
	ft_putstr("Length : ");
	ft_putnbr(ld->length);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("Old Content : ");
	if (ld->old_content)
		ft_putendl(ld->old_content);
	ft_putstr("Length : ");
	if (ld->old_content)
		ft_putnbr(ft_strlen(ld->old_content));
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("Buffer : ");
	if (ld->buffer[0])
		ft_putendl(ld->buffer);
	ft_putstr("Current Size : ");
	ft_putnbr(ld->current_size);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putendl("Resize History : ");
	while (ld->resize_history[i] != -1)
	{
		ft_putnbr(i);
		ft_putstr(" : ");
		ft_putnbr(ld->resize_history[i]);
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
	ft_putstr("Nb Resize : ");
	ft_putnbr(ld->nb_resize);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("Columns : ");
	ft_putnbr(ld->cd->col);
	ft_putchar('\n');
	ft_putstr("Rows : ");
	ft_putnbr(ld->cd->row);
	ft_putchar('\n');
}
