/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 06:09:10 by azybert           #+#    #+#             */
/*   Updated: 2018/07/10 06:21:06 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static char	*find_in_history(char *cmd, t_node *history)
{
	if (history == NULL)
		return (NULL);
	else if (strstr(history->cmd, cmd) != NULL)
		return (history->cmd);
	else
		return (find_in_history(cmd, history->next));
}

void	search_display(t_prompt *prompt, char *cmd_found)
{
	char	*to_display;
	char	*to_free;
	char	*cmd_search;

	to_display = NULL;
	move_cursor(prompt, 0, true);
	to_display = ft_strjoin(prompt->line, "\nHistory: ");
	to_free = to_display;
	to_display = (cmd_found ? ft_strjoin(to_display, cmd_found) : to_display);
	cmd_search = prompt->line;
	prompt->line = to_display;
	prompt->total = ft_strlen(prompt->line);
	write_data(prompt, prompt->line, prompt->total);
	free(to_free);
	to_free = NULL;
	if (cmd_found)
		free(to_display);
	prompt->line = cmd_search;
	prompt->total = ft_strlen(prompt->line);
	move_cursor(prompt, prompt->total, true);
}

static int	search_react(t_prompt *prompt)
{
	char	user_entry[7];
	int		nb_user_entry;

	ft_bzero(user_entry, 7);
	nb_user_entry = read(1, user_entry, 6);
	if (user_entry[0] == 27)
		return (-1);
	else if (user_entry[0] == 127)
		prompt_delete(prompt);
	else
	{
		((prompt->buf = ft_strdup(user_entry)) != NULL ? 0 : exit(1));
		if (nb_user_entry == 6)
			ft_flush(prompt);
		if (data_react(prompt))
			return (1);
	}
	return (0);
}

void	search_mode(t_prompt *prompt, t_stat_data *stat_data)
{
	char	*cmd_found;
	int		loop_state;

	cmd_found = NULL;
	loop_state = 0;
	ignore_handle();
	if (stat_data->old_line)
	{
		free(stat_data->old_line);
		stat_data->old_line = NULL;
	}
	stat_data->old_line = prompt->line;
	((prompt->line = ft_strdup("\0")) ? 0 : exit(1));
	while (loop_state == 0)
	{
		cmd_found = find_in_history(prompt->line, stat_data->history);
		search_display(prompt, cmd_found);
		loop_state = search_react(prompt);
		if (loop_state == 1)
		{
			free(prompt->line);
			prompt->line = NULL;
			prompt->pos = 0;
			prompt->total = 0;
			secure_stock(prompt, cmd_found);
			free(stat_data->old_line);
		}
		else if (loop_state == -1)
		{
			free(prompt->line);
			prompt->line = stat_data->old_line;
		}
		stat_data->old_line = NULL;
	}
	handle_sig();
}
