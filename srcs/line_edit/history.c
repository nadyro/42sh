/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@stud.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:20:53 by azybert           #+#    #+#             */
/*   Updated: 2018/06/08 16:22:54 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

void	add_to_history(char *cmd, t_stat_data *stat_data)
{
	t_node	*new;

	if (!(new = malloc(sizeof(*new))))
		exit(1);
	new->cmd = ft_strdup(cmd);
	new->next = stat_data->history;
	new->prev = NULL;
	if (stat_data->history)
		stat_data->history->prev = new;
	stat_data->history = new;
}

void	history_next(t_prompt *prompt, t_stat_data *stat_data)
{
	if (stat_data->line_save == NULL && stat_data->history)
	{
		stat_data->line_save = prompt->line;
		stat_data->current = stat_data->history;
	}
	else if (stat_data->current->next != NULL)
		stat_data->current = stat_data->current->next;
	else
		return;
	prompt->line = ft_strdup(stat_data->current);
	move_cursor(prompt, 0, false);
	//revenir ce et write data
}

void	history_prev(t_prompt *prompt, t_stat_data *stat_data)
{
	if (prompt && stat_data)
		write(1, "k", 0);
}
