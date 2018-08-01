/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:53:44 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/01 22:58:00 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node	*dispatch_history_queries(t_history *hist_args, t_shell *shell)
{
	int		i;
	int		conv;

	i = 0;
	conv = 0;
	if (hist_args->c == 1)
	{
		shell->history = clear_history_mem(shell->history);
		shell->history_length = 0;
	}
	else if (hist_args->d == 1)
	{
		if (hist_args->d_arg > 0 && hist_args->d_arg <= shell->history_length)
			delete_history_line(shell->history, hist_args->d_arg);
		else
		{
			ft_putstr("history: ");
			ft_putnbr(hist_args->d_arg);
			ft_putendl(": history position out of range.");
		}
	}
	else
	{
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
	/*if (hist_args->w == 1)
	  write_history_mem_to_file(history);*/
	return (shell->history);
}

t_node	*clear_history_mem(t_node *history)
{
	t_node		*tmp;
	t_node		*tmp_1;
	int			i;

	i = open(".history", O_TRUNC);
	if (i < 0)
		ft_putstr("Couldn't delete file. Check your rights.");
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
	ft_putstr("finished clear\n");
	return (history);
}

t_node	*delete_history_line(t_node *history, int to_del)
{
	t_node	*tmp_next;
	t_node	*tmp_prev;
	int		i;

	i = 1;
	tmp_next = NULL;
	tmp_prev = NULL;
	while (history->next != NULL)
		history = history->next;
	while (history != NULL)
	{
		if (i == to_del)
		{
			if (history->prev)
				tmp_next = history->prev;
			if (history->next)
				tmp_prev = history->next;
			if (history->prev)
				tmp_next->next = tmp_prev;
			if (history->next)
				tmp_prev->prev = tmp_next;
			free(history);
			break ;
		}
		history = history->prev;
		i++;
	}
	return (history);
}
