/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:20:53 by azybert           #+#    #+#             */
/*   Updated: 2018/07/28 18:14:07 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

t_node		*add_to_history(char *cmd, t_node *history)
{
	t_node	*new;
	char	*check;

	check = NULL;
	if (cmd == NULL || ft_strlen((check = ft_strtrim(cmd))) == 0)
	{
		free(check);
		return (history);
	}
	free(check);
	if (!(new = malloc(sizeof(*new))))
		exit(1);
	if (!(new->cmd = ft_strdup(cmd)))
		exit(1);
	new->next = history;
	new->prev = NULL;
	if (history)
		history->prev = new;
	history = new;
	if (*(ft_strrchr(history->cmd, '\n') + 1) == '\0')
		*(ft_strrchr(history->cmd, '\n')) = '\0';
	return (history);
}

static void	ft_norme(t_prompt *prompt)
{
	free(prompt->line);
	prompt->line = NULL;
	prompt->total = 0;
	move_cursor(prompt, 0, true);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
}

void		history_next(t_prompt *prompt, t_stat_data *stat_data)
{
	if (prompt->history == NULL)
		return ;
	if (prompt->current == NULL)
	{
		prompt->current = prompt->history;
		if (ft_strlen(prompt->line))
		{
			free(stat_data->old_line);
			((stat_data->old_line = ft_strdup(prompt->line)) ? 0 : exit(0));
		}
	}
	else if (prompt->current->next != NULL)
	{
		if (ft_strcmp(prompt->line, prompt->current->cmd))
		{
			free(stat_data->old_line);
			((stat_data->old_line = ft_strdup(prompt->line)) ? 0 : exit(0));
		}
		prompt->current = prompt->current->next;
	}
	else
		return ;
	ft_norme(prompt);
	secure_stock(prompt, prompt->current->cmd);
}

void		history_prev(t_prompt *prompt, t_stat_data *stat_data)
{
	if (prompt->current == NULL)
		return ;
	if (ft_strcmp(prompt->line, prompt->current->cmd))
	{
		free(stat_data->old_line);
		((stat_data->old_line = ft_strdup(prompt->line)) ? 0 : exit(0));
	}
	prompt->current = prompt->current->prev;
	ft_norme(prompt);
	if (prompt->current)
		secure_stock(prompt, prompt->current->cmd);
	else
	{
		secure_stock(prompt, stat_data->old_line);
		free(stat_data->old_line);
		stat_data->old_line = NULL;
	}
}

void		write_history_file(t_node *history)
{
	int		i;

	while (history->next != NULL)
		history = history->next;
	if ((i = open(".history",
		O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) != -1)
		while (history)
		{
			ft_putendl_fd(history->cmd, i);
			history = history->prev;
		}
	if (i < 0)
	{
		ft_putstr("Error");
		exit(0);
	}
	else
		close(i);
}
