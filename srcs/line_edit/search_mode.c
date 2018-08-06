/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 06:09:10 by azybert           #+#    #+#             */
/*   Updated: 2018/08/06 06:38:20 by azybert          ###   ########.fr       */
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

static void	search_display(t_prompt *prompt, char *cmd_found)
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
	if (user_entry[0] == 27 || prompt->end == 1)
		return (-1);
	else if (user_entry[0] == 12)
	{
		tputs(tgetstr("cl", NULL), 0, ft_putshit);
		write(1, prompt->disp, ft_strlen(prompt->disp));
		prompt->origin->y = 0;
	}
	else if (user_entry[0] == 127 && prompt->total > 0)
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

static void	search_mode_aux(t_prompt *prompt, t_stat_data *stat_data)
{
	int		loop_state;
	char	*cmd_found;

	loop_state = 0;
	while (loop_state == 0)
	{
		cmd_found = find_in_history(prompt->line, prompt->history);
		search_display(prompt, cmd_found);
		loop_state = search_react(prompt);
	}
	free(prompt->line);
	prompt->line = NULL;
	move_cursor(prompt, 0, true);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	prompt->total = 0;
	secure_stock(prompt, (loop_state == 1 ? cmd_found : stat_data->old_line));
	free(stat_data->old_line);
	stat_data->old_line = NULL;
}

void		search_mode(t_prompt *prompt, t_stat_data *stat_data)
{
	ignore_handle();
	if (stat_data->old_line)
	{
		free(stat_data->old_line);
		stat_data->old_line = NULL;
	}
	stat_data->old_line = prompt->line;
	((prompt->line = ft_strdup("\0")) ? 0 : exit(1));
	search_mode_aux(prompt, stat_data);
	(prompt->end ? termanip(33) : 0);
	handle_sig();
	prompt->end = 0;
}
