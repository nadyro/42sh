/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 02:11:49 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/21 13:58:23 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_node	*l_a_hst(int *index, int fd, t_shell *shell, t_node *history)
{
	char	*tmp;
	int		y;

	y = *index;
	tmp = NULL;
	if (y++ >= shell->o_history)
	{
		ft_putendl_fd(history->cmd, fd);
		tmp = ft_strdup(history->cmd);
		shell->appnd_hst = init_nonvoid_history(tmp, shell->appnd_hst);
	}
	*index = y;
	return (shell->appnd_hst);
}

void			dispatch_history_d(t_shell *shell, t_history *hist_args)
{
	if (hist_args->d_arg > 0)
	{
		if (hist_args->d_arg <= shell->history_length)
		{
			hist_args->no_write = 1;
			delete_history_line(shell, hist_args->d_arg);
		}
		else
		{
			ft_putstr_fd("history: ", 2);
			ft_putnbr_fd(hist_args->d_arg, 2);
			ft_putendl_fd(": history position out of range.", 2);
			hist_args->vide = 1;
		}
	}
	else
	{
		ft_putendl_fd("Undefined offset.", 2);
		hist_args->vide = 2;
	}
}

void			dispatch_history_print(t_shell *shell)
{
	int		conv;

	signal_history_static(1);
	signal(SIGINT, sign_history);
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
	reverse_handle();
}

void			append_history_mem_to_file(t_shell *shell)
{
	int		i;
	int		y;
	t_node	*history;

	y = 0;
	history = shell->history;
	i = open(shell->home_env, O_APPEND | O_RDWR);
	if (i > 0)
	{
		while (history && history->next != NULL)
			history = history->next;
		while (history != NULL)
		{
			shell->appnd_hst = l_a_hst(&y, i, shell, history);
			history = history->prev;
		}
		shell->o_history += shell->to_add;
		shell->is_a = 1;
		shell->to_add = 0;
		close(i);
	}
}

t_node			*append_h_to_mem(t_node *history, t_shell *shell, int to_f)
{
	t_node	*tmp;
	t_node	*tmp_1;

	tmp = history;
	while (tmp)
	{
		tmp_1 = tmp;
		tmp = tmp_1->next;
		free(tmp_1->cmd);
		free(tmp_1);
		tmp_1 = NULL;
	}
	history = NULL;
	shell->history_length = 0;
	shell->to_add = 0;
	if (to_f == 0)
		history = fill_history_file(history, shell);
	else
		history = fill_arg_file(history, shell);
	return (history);
}
