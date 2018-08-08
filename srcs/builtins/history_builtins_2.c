/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 02:11:12 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/08 01:06:09 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node	*get_last_cmds(t_node *history, int nbr)
{
	int		i;
	char	**last_cmds;
	int		y;

	y = nbr;
	if (!(last_cmds = (char **)malloc(sizeof(char *) * (nbr + 1))))
		return (NULL);
	last_cmds[nbr] = NULL;
	while (history)
	{
		last_cmds[nbr - 1] = ft_strdup(history->cmd);
		history = history->next;
		nbr--;
		if (nbr == 0)
			break ;
	}
	i = 0;
	while (i < y)
		ft_putendl(last_cmds[i++]);
	clean_tabs(last_cmds, 0);
	return (history);
}

void	free_after_del(t_node *to_free, t_shell *shell)
{
	free(to_free->cmd);
	free(to_free);
	shell->history_length--;
	shell->o_history--;
}

t_node	*fill_arg_file(t_node *history, t_shell *shell)
{
	int		i;
	char	*c;

	c = NULL;
	i = 0;
	if (shell->args[2])
		i = open(shell->args[2], O_RDWR | S_IRUSR
		| S_IWUSR | S_IRGRP | S_IROTH);
	if (i >= 0)
	{
		while ((get_next_line(i, &c)) == 1)
		{
			shell->history_length++;
			history = init_nonvoid_history(c, history);
		}
		shell->o_history = shell->history_length;
		close(i);
	}
	else
		ft_putendl("Couldn't open file. Check your rights.");
	return (history);
}

void	append_history_mem_to_arg(t_shell *shell)
{
	int		i;
	int		y;
	t_node	*history;

	y = 0;
	i = 0;
	history = shell->history;
	if (shell->args[2] != NULL)
		i = open(shell->args[2], O_CREAT | O_APPEND |
		O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (i > 0)
	{
		while (history && history->next != NULL)
			history = history->next;
		while (history != NULL)
		{
			if (y >= shell->o_history)
				ft_putendl_fd(history->cmd, i);
			history = history->prev;
			y++;
		}
		shell->o_history += shell->to_add;
		shell->to_add = 0;
		close(i);
	}
}

void	write_history_mem_to_arg(t_shell *shell)
{
	int		i;

	i = 0;
	if (shell->args[2] != NULL)
		i = open(shell->args[2], O_TRUNC);
	if (i < 0)
	{
		write_history_file(shell, 1);
		return ;
	}
	else
		write_history_file(shell, 1);
}
