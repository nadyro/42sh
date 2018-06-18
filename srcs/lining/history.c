/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:35:14 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/06/08 16:59:14 by kernel_pani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

t_list		*write_history(struct s_line_data *ld, t_list **history)
{
	t_list *head;
	t_list *node;

	head = *history;
	node = NULL;
	if (!(node = (t_list *)malloc(sizeof(t_list))))
		ft_exit(3);
	node->content = ft_strdup(ld->buffer);
	node->content_size = ld->current_size;
	node->next = NULL;
	ld->h_elem++;
	if (*history == NULL)
	{
		node->previous = NULL;
		*history = node;
		return (*history);
	}
	while (head->next != NULL)
		head = head->next;
	head->next = node;
	node->previous = head;
	return (head);
}

void	write_history_file(t_list *history)
{
	int		i;

	while (history->previous != NULL)
		history = history->previous;
	if ((i = open(".history", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
		while (history != NULL)
		{
			ft_putendl_fd(history->content, i);
			history = history->next;
		}
	if (i < 0)
	{
		ft_putstr("Error");
		exit(0);
	}
}

void        browse_history_up(struct s_line_data *ld, int *index)
{
	char    *go_to;

	if (ld->history)
	{
		if (ld->history->previous != NULL)
			ld->history = ld->history->previous;
		ft_bzero(ld->buffer, ft_strlen(ld->buffer));
		ft_strncpy(ld->buffer, ld->history->content,
				ft_strlen(ld->history->content));
		go_to = tgoto(tgetstr("cm", NULL), COLSTART, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		tputs(tgetstr("ce", NULL), 1, fprint_char);
		ft_putstr(ld->buffer);
		*index = ft_strlen(ld->buffer);
		ld->current_size = ft_strlen(ld->buffer);
		ld->cd->x = ft_strlen(ld->buffer) + COLSTART;
		go_to = tgoto(tgetstr("cm", NULL), (ld->cd->x - 1) % ld->sw->win_col, ld->cd->pos_y);
	}
}

void        browse_history_down(struct s_line_data *ld, int *index)
{
	char    *go_to;

	if (ld->history)
	{
		if (ld->history->next != NULL)
			ld->history = ld->history->next;
		ft_bzero(ld->buffer, ft_strlen(ld->buffer));
		ft_strncpy(ld->buffer, ld->history->content,
				ft_strlen(ld->history->content));
		go_to = tgoto(tgetstr("cm", NULL), COLSTART, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		tputs(tgetstr("ce", NULL), 1, fprint_char);
		ft_putstr(ld->buffer);
		go_to = tgoto(tgetstr("cm", NULL), (ld->cd->x - 1) % ld->sw->win_col, ld->cd->pos_y);
		*index = ft_strlen(ld->buffer);
		ld->cd->x = ft_strlen(ld->buffer) + COLSTART;		
		ld->current_size = ft_strlen(ld->buffer);
	}
}
