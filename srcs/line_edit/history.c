/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@stud.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:20:53 by azybert           #+#    #+#             */
/*   Updated: 2018/06/14 16:33:21 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

void	add_to_history(char *cmd, t_stat_data *stat_data)
{
	t_node	*new;

	if (stat_data->line_save == 0)
	{
		if (!(new = malloc(sizeof(*new))))
			exit(1);
		new->cmd = ft_strdup(cmd);
		new->next = stat_data->history;
		new->prev = NULL;
		if (stat_data->history)
			stat_data->history->prev = new;
		stat_data->history = new;
	}
	else
	{
		free(stat_data->history->cmd);
		stat_data->history->cmd = ft_strdup(cmd);
		stat_data->line_save = 0;
	}
}

void	history_next(t_prompt *prompt, t_stat_data *stat_data)
{
	if (stat_data->history == NULL)
		return ;
	if (stat_data->line_save != 1)
	{
		stat_data->current = stat_data->history;
		if (stat_data->line_save == 2 && stat_data->current->next != NULL)
			stat_data->current = stat_data->current->next;
		add_to_history((prompt->line ? prompt->line : " \0"), stat_data);
		stat_data->line_save = 1;
	}
	else if (stat_data->current->next != NULL)
		stat_data->current = stat_data->current->next;
	free(prompt->line);
	prompt->line = ft_strdup(stat_data->current->cmd);
	if (ft_strrchr(prompt->line, '\n'))
		*(ft_strrchr(prompt->line, '\n')) = '\0';
	move_cursor(prompt, 0, false);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	prompt->total = ft_strlen(prompt->line);
	write_data(prompt, prompt->line, prompt->total);
	move_cursor(prompt, prompt->total, true);
}

void	history_prev(t_prompt *prompt, t_stat_data *stat_data)
{
	if (stat_data->current == NULL || stat_data->current->prev == NULL)
		return ;
	stat_data->current = stat_data->current->prev;
	if (stat_data->current->prev == NULL)
		stat_data->line_save = 2;
	free(prompt->line);
	prompt->line = ft_strdup(stat_data->current->cmd);
	if (ft_strrchr(prompt->line, '\n') != NULL)
		*(ft_strrchr(prompt->line, '\n')) = '\0';
	move_cursor(prompt, 0, false);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	prompt->total = ft_strlen(prompt->line);
	write_data(prompt, prompt->line, prompt->total);
	move_cursor(prompt, prompt->total, true);
}
