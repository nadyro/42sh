/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 02:13:00 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/03 05:29:31 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node	*clear_history_mem(t_shell *shell)
{
	t_node		*tmp;
	t_node		*tmp_1;
	t_node		*history;

	history = shell->history;
	tmp = history;
	while (tmp)
	{
		tmp_1 = tmp;
		tmp = tmp_1->next;
		ft_bzero(tmp_1->cmd, ft_strlen(tmp_1->cmd));
		free(tmp_1->cmd);
		free(tmp_1);
		tmp_1 = NULL;
	}
	history = NULL;
	shell->history_length = 0;
	shell->hl_append = 0;
	ft_putstr("finished clear\n");
	return (history);
}

t_node	*switch_history_cmds(t_node *history)
{
	t_node	*tmp_next;
	t_node	*tmp_prev;

	tmp_next = NULL;
	tmp_prev = NULL;
	if (history->prev)
		tmp_next = history->prev;
	if (history->next)
		tmp_prev = history->next;
	if (history->prev)
		tmp_next->next = tmp_prev;
	if (history->next)
		tmp_prev->prev = tmp_next;
	return (history);
}

t_node	*delete_history_line(t_shell *shell, int to_del)
{
	t_node	*history;
	int		i;

	i = 1;
	history = shell->history;
	while (history->next != NULL)
		history = history->next;
	while (history != NULL)
	{
		if (i == to_del)
		{
			history = switch_history_cmds(history);
			ft_bzero(history->cmd, ft_strlen(history->cmd));
			free(history->cmd);
			free(history);
			break ;
		}
		history = history->prev;
		i++;
	}
	shell->history_length--;
	return (history);
}

void	write_history_mem_to_file(t_shell *shell)
{
	int		i;

	i = open(shell->home_env, O_TRUNC);
	if (i < 0)
	{
		write_history_file(shell);
		return ;
	}
	else
		write_history_file(shell);
}

void	append_history_mem_to_file(t_shell *shell)
{
	int		i;
	int		y;
	t_node	*history;

	y = 0;
	history = shell->history;
	i = open(shell->home_env, O_APPEND | O_RDWR);
	if (i > 0)
	{
		while (history->next != NULL)
			history = history->next;
		while (history != NULL)
		{
			if (y >= shell->hl_append)
				ft_putendl_fd(history->cmd, i);
			history = history->prev;
			y++;
		}
	}
}

t_node	*append_history_file_to_mem_1(t_node *history, t_shell *shell)
{
	while (history->next != NULL)
		history = history->next;
	history = fill_history_file(history, shell);
	return (history);
}