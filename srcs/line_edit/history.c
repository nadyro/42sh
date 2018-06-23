/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@stud.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:20:53 by azybert           #+#    #+#             */
/*   Updated: 2018/06/23 18:29:48 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

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
	if (ft_strrchr(stat_data->history->cmd, '\n'))
		*(ft_strrchr(stat_data->history->cmd, '\n')) = '\0';
}

void	history_next(t_prompt *prompt, t_stat_data *stat_data)
{
	int	loop;

	if (stat_data->history == NULL || stat_data->history->next == NULL)
		return ;
	if (stat_data->line_save != 1)
	{
		stat_data->current = stat_data->history;
		if (stat_data->line_save == 2 && stat_data->current->next != NULL)
			stat_data->current = stat_data->current->next;
		add_to_history((prompt->line ? prompt->line : "\0"), stat_data);
		stat_data->line_save = 1;
	}
	else if (stat_data->current->next != NULL)
		stat_data->current = stat_data->current->next;
	free(prompt->line);
	prompt->line = NULL;
	prompt->total = 0;
	move_cursor(prompt, 0, true);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	loop = 0;
	while (stat_data->current->cmd[loop] != '\0')
	{
		prompt_stock(prompt, &(stat_data->current->cmd[loop]));
		loop++;
	}
}

void	history_prev(t_prompt *prompt, t_stat_data *stat_data)
{
	int	loop;

	if (stat_data->current == NULL || stat_data->current->prev == NULL)
		return ;
	stat_data->current = stat_data->current->prev;
	if (stat_data->current->prev == NULL)
		stat_data->line_save = 2;
	free(prompt->line);
	prompt->line = NULL;
	prompt->total = 0;
	move_cursor(prompt, 0, true);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	loop = 0;
	while (stat_data->current->cmd[loop] != '\0')
	{
		prompt_stock(prompt, &(stat_data->current->cmd[loop]));
		loop++;
	}
}
