/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:20:32 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/29 23:46:27 by nsehnoun         ###   ########.fr       */
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
	ld->nb_resize = 1;
	ld->history = NULL;
	ld->h_elem = 0;
	ld->nb_lines = 0;
	ld->last_line = 0;
	ld->c = 0;
	ld->d = 0;
	ld->cd = init_cursordata();
	ld->sw = init_windata();
	ft_putscolors("$> 42sh", BCYAN);
	ft_putscolors(" ~> ", MAGENTA);
	return (ld);
}

void				clean_linedata(struct s_line_data *ld)
{
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
	ft_strdel(&ld->buff);
}

int					manage_buffer(struct s_line_data *ld, char *t, int *index)
{
	char	*gt;
	int		i;

	i = *index;
	if (!(i < BUFFER * ld->nb_resize))
		reallocate_mem_line(ld);
		gt = tgoto(tgetstr("cm", NULL), ld->c + COLSTART, ld->cd->pos_y);
		tputs(gt, 1, fprint_char);
	if (*index < BUFFER * ld->nb_resize && ft_strlen(ld->buffer) < 4096)
		ld->buffer[*index] = t[0];
	else
		return (1);
	ld->current_size = ft_strlen(ld->buffer);
	if ((ld->c + 1) < ld->current_size)
		update_linedata(t, ld);
	else
	{
		ld->c++;
		ld->cd->x++;
		ld->cd->pos_x = ld->cd->x - COLSTART;
		ft_putstr("\x1b[32m");
		ft_putchar(t[0]);
		ft_putstr("\x1b[0m");
	}
	i++;
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
		i = ld->c;
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
  
	debug("ld->c : \n", 1);
	debug_custom(&ld->c, sizeof(int), 1);
  debug("\nHistory : ", 1);
	while (history != NULL)
	{
		debug(history->content, 1);
		debug("\n", 1);
		history = history->next;
	}
	debug("Buffer : ", 1);
	if (ld->buffer[0])
		debug(ld->buffer, 1);
	debug("Current Size : ", 1);
	debug_custom(&ld->current_size, sizeof(int), 1);
	debug("\n\nResize History : \n", 1);
	while (ld->resize_history[i] != -1)
	{
		debug_custom(&i, sizeof(int), 1);
		debug(" : ", 1);
		debug_custom(&ld->resize_history[i], sizeof(int), 1);
		debug("\n", 1);
		i++;
	}
	debug("\nNb Resize : ", 1);
	debug_custom(&ld->nb_resize, sizeof(int), 1);
	debug("\n\nColumns : ", 1);
	debug_custom(&ld->cd->x, sizeof(int), 1);
	debug("\nRows : ", 1);
	debug_custom(&ld->cd->pos_y, sizeof(int), 1);
	debug("\nLine length : ", 1);
	debug_custom(&ld->cd->pos_x, sizeof(int), 1);
	debug("\n", 1);
	ft_putchar('\n');
}
