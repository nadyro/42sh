/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 02:11:49 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/04 05:58:51 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	dispatch_history_d(t_shell *shell, t_history *hist_args)
{
	if (hist_args->d_arg > 0)
	{
		if (hist_args->d_arg <= shell->history_length - 1)
			delete_history_line(shell, hist_args->d_arg);
		else
		{
			ft_putstr("history: ");
			ft_putnbr(hist_args->d_arg);
			ft_putendl(": history position out of range.");
		}
	}
	else
		ft_putendl("Undefined offset.");
}

void	dispatch_history_print(t_shell *shell)
{
	int		conv;

	conv = 0;
	if (shell->args && shell->args[1])
	{
		conv = ft_atoi(shell->args[1]);
		if (conv <= shell->history_length)
			read_history(shell->history, conv);
		else
			read_history(shell->history, 0);
	}
	else if (shell->args)
		read_history(shell->history, 0);
}

void	append_history_mem_to_file(t_shell *shell)
{
	int		i;
	int		y;
	t_node	*history;

	y = 0;
	ft_putnbr(shell->hl_append);
	ft_putchar('\n');
	ft_putnbr(shell->history_length);	
	ft_putchar('\n');
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
	while (history)
		history = history->next;
	history = fill_history_file(history, shell);
	return (history);
}
