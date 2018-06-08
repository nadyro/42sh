/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:20:32 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/06/08 11:39:01 by kernel_pani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

struct s_line_data	*init_linedata(void)
{
	struct s_line_data	*ld;
	int					s;

	s = 0;
	if (!(ld = malloc(sizeof(struct s_line_data))))
		ft_exit(3);
	ld->old_content = NULL;
	ld->tmp = NULL;
	if (!(ld->buffer = ft_strnew(BUFFER)))
		ft_exit(3);
	ld->buff = NULL;
	s = 0;
	ld->length = 0;
	ld->current_size = 0;
	while (s < 512)
		ld->resize_history[s++] = -1;
	ld->nb_resize = 1;
	ld->history = NULL;
	ld->h_elem = 0;
	ld->cd = init_cursordata();
	ld->sw = init_windata();
	ft_putscolors("$> 42sh", BCYAN);
	ft_putscolors(" ~> ", MAGENTA);
	return (ld);
}

void				clean_linedata(struct s_line_data *ld)
{
	int		s;

	s = 0;
	if (ld->content != NULL)
		ft_bzero(ld->content, ft_strlen(ld->content));
	if (ld->old_content != NULL)
		ft_bzero(ld->old_content, ft_strlen(ld->old_content));
	if (ld->buffer != NULL)
		ft_bzero(ld->buffer, ft_strlen(ld->buffer));
	if (ld->buff != NULL)
		ft_bzero(ld->buff, ft_strlen(ld->buff));
	ld->current_size = 0;
	ld->length = 0;
	while (s < 512)
		ld->resize_history[s++] = -1;
	ld->nb_resize = 1;
}

void				reallocate_mem_line(struct s_line_data *ld)
{
	char	*join_tmp;

	ld->nb_resize++;
	ld->buff = ft_strdup(ld->buffer);
	if (ld->old_content == NULL)
		join_tmp = ft_strdup(ld->buff);
	else
		join_tmp = ft_strjoin(ld->old_content, ld->buff);
	ld->old_content = ft_strdup(join_tmp);
	if (ld->buffer != NULL)
		ft_strdel(&ld->buffer);
	if (!(ld->buffer = ft_strnew(BUFFER * ld->nb_resize)))
		ft_exit(3);
	ft_strncpy(ld->buffer, ld->buff, ft_strlen(ld->buff));
	ft_strdel(&join_tmp);
	ld->length = ft_strlen(ld->old_content);
	ld->resize_history[ld->nb_resize - 1] = ft_strlen(ld->buff);
	ft_strdel(&ld->buff);
}

int					manage_buffer(struct s_line_data *ld, char *t, int *index)
{
	char	*gt;
	int		i;

	i = *index;
	if (!(i < BUFFER * ld->nb_resize))
		reallocate_mem_line(ld);
	if (*index < BUFFER * ld->nb_resize && ft_strlen(ld->buffer) < 4096)
		ld->buffer[*index] = t[0];
	else
		return (1);
	ld->current_size = ft_strlen(ld->buffer);
	if ((ld->cd->pos_x + 1) < ld->current_size)
		update_linedata(t, ld);
	else
	{
		ft_putstr("\x1b[32m");
		ft_putchar(t[0]);
		ft_putstr("\x1b[0m");
	}
	i++;
	ld->cd->pos_x++;
	ld->cd->x++;
	gt = tgoto(tgetstr("cm", NULL), ld->cd->x, ld->cd->pos_y);
	tputs(gt, 1, fprint_char);
	*index = i;
	return (0);
}

void				update_linedata(char *t, struct s_line_data *ld)
{
	int		i;
	int		y;
	int		x;
	char	*tmp_buffer;

	if (ft_strlen(ld->buffer) < 4096)
	{
		if (!(tmp_buffer = ft_strnew(ft_strlen(ld->buffer))))
			ft_exit(3);
		y = 0;
		x = ft_strlen(t);
		i = ld->cd->pos_x;
		while (ld->buffer[i] != '\0')
			tmp_buffer[y++] = ld->buffer[i++];
		if (x == 1)
			manage_key_insertion(t, ld, tmp_buffer);
		else if (x > 1)
			manage_cp_pst(t, ld, tmp_buffer);
	}
	else
		write(1, "\a", 1);
}

void				print_line_data(struct s_line_data *ld, t_list *history)
{
	int		i;

	i = 0;
	while (history->previous != NULL)
		history = history->previous;
	ft_putendl("History : ");
	while (history != NULL)
	{
		ft_putendl(history->content);
		history = history->next;
	}
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
	ft_putnbr(ld->cd->x);
	ft_putchar('\n');
	ft_putstr("Rows : ");
	ft_putnbr(ld->cd->pos_y);
	ft_putchar('\n');
	ft_putstr("Line length : ");
	ft_putnbr(ld->cd->pos_x);
	ft_putchar('\n');
}
