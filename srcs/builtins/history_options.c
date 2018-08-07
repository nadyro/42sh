/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 02:13:00 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/07 07:05:10 by nsehnoun         ###   ########.fr       */
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
	shell->o_history = 0;
	shell->to_add = 0;
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
	t_node	*to_free;
	int		i;

	i = 1;
	to_free = NULL;
	history = shell->history;
	while (history && history->next != NULL)
		history = history->next;
	while (history != NULL)
	{
		if (i == to_del)
		{
			to_free = history;
			history = switch_history_cmds(history);
			if (shell->history == to_free)
				shell->history = shell->history->next;
			free_after_del(to_free, shell);
			break ;
		}
		history = history->prev;
		i++;
	}
	return (history);
}

void	write_history_mem_to_file(t_shell *shell)
{
	int		i;

	i = open(shell->home_env, O_TRUNC);
	if (i < 0)
	{
		write_history_file(shell, 0);
		return ;
	}
	else
		write_history_file(shell, 0);
}

int		check_warn(t_shell *shell, t_history *hist_args, int y)
{
	int		x;

	x = 0;
	if ((x = check_warn_w(hist_args, shell, y)) >= 1)
		return (x);
	else if ((x = check_warn_a(hist_args, shell, y)) >= 1)
		return (x);
	else if ((x = check_warn_r(hist_args, shell, y)) >= 1)
		return (x);
	else if ((x = check_warn_n(hist_args, shell, y)) >= 1)
		return (x);
	return (x);
}
