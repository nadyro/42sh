/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@stud.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:20:53 by azybert           #+#    #+#             */
/*   Updated: 2018/06/29 20:02:30 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	add_to_history(char *cmd, t_stat_data *stat_data)
{
	t_node	*new;

	if (cmd == NULL)
		return ;
	if (!(new = malloc(sizeof(*new))))
		exit(1);
	new->cmd = ft_strdup(cmd);
	new->next = stat_data->history;
	new->prev = NULL;
	if (stat_data->history)
		stat_data->history->prev = new;
	stat_data->history = new;
	if (ft_strrchr(stat_data->history->cmd, '\n'))
		*(ft_strrchr(stat_data->history->cmd, '\n')) = '\0';
}

void	history_next(t_prompt *prompt, t_stat_data *stat_data)
{
	if (stat_data->history == NULL)
		return ;
	if (stat_data->line_save == 0)
	{
		stat_data->current = stat_data->history;
		free(stat_data->old_line);
		if (prompt->line != NULL)
			stat_data->old_line = ft_strdup(prompt->line);
		else
			stat_data->old_line = NULL;
		stat_data->line_save = 1;
	}
	else if (stat_data->current->next != NULL)
		stat_data->current = stat_data->current->next;
	free(prompt->line);
	prompt->line = NULL;
	prompt->total = 0;
	move_cursor(prompt, 0, true);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	secure_stock(prompt, stat_data->current->cmd);
}

void	history_prev(t_prompt *prompt, t_stat_data *stat_data)
{
	if (stat_data->current == NULL)
		return ;
	stat_data->current = stat_data->current->prev;
	if (stat_data->current == NULL)
		stat_data->line_save = 0;
	free(prompt->line);
	prompt->line = NULL;
	prompt->total = 0;
	move_cursor(prompt, 0, true);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	if (stat_data->current)
		secure_stock(prompt, stat_data->current->cmd);
	else if (stat_data->old_line)
		secure_stock(prompt, stat_data->old_line);
}
