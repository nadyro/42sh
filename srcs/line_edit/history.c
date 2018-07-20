/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@stud.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:20:53 by azybert           #+#    #+#             */
/*   Updated: 2018/07/20 08:07:44 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	add_to_history(char *cmd, t_stat_data *stat_data)
{
	t_node	*new;
	char	*check;

	check = NULL;
	if (cmd == NULL || ft_strlen((check = ft_strtrim(cmd))) == 0)
	{
		free(check);
		return ;
	}
	if (!(new = malloc(sizeof(*new))))
		exit(1);
	if (!(new->cmd = ft_strdup(cmd)))
		exit(1);
	new->next = stat_data->history;
	new->prev = NULL;
	if (stat_data->history)
		stat_data->history->prev = new;
	stat_data->history = new;
	if (*(ft_strrchr(stat_data->history->cmd, '\n') + 1) == '\0')
		*(ft_strrchr(stat_data->history->cmd, '\n')) = '\0';
}

void	history_next(t_prompt *prompt, t_stat_data *stat_data)
{
	if (stat_data->history == NULL)
		return ;
	if (stat_data->old_line == NULL)
	{
		stat_data->current = stat_data->history;
		if (!(stat_data->old_line = ft_strdup(prompt->line)))
			exit(1);
	}
	else if (stat_data->current->next != NULL)
		stat_data->current = stat_data->current->next;
	else
		return ;
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
	free(prompt->line);
	prompt->line = NULL;
	prompt->total = 0;
	move_cursor(prompt, 0, true);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	if (stat_data->current)
		secure_stock(prompt, stat_data->current->cmd);
	else
	{
		secure_stock(prompt, stat_data->old_line);
		free(stat_data->old_line);
		stat_data->old_line = NULL;
	}
}
