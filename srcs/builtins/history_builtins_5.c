/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 18:27:37 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/08 01:52:47 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node	*write_history_to_mem(t_node *history, t_shell *shell)
{
	int		i;
	t_node	*a;
	t_node	*tmp;

	i = 0;
	tmp = NULL;
	a = shell->appnd_hst;
	while (shell->appnd_hst && shell->appnd_hst->next != NULL)
		shell->appnd_hst = shell->appnd_hst->next;
	while (shell->appnd_hst)
	{
		history = init_nonvoid_history(shell->appnd_hst->cmd, history);
		shell->history_length++;
		shell->appnd_hst = shell->appnd_hst->prev;
	}
	while (a)
	{
		tmp = a;
		a = tmp->next;
		free(tmp);
		tmp = NULL;
	}
	return (history);
}

void	write_arg_p(t_shell *shell)
{
	int		i;

	i = 2;
	while (shell->args && shell->args[i])
	{
		if (shell->args[1] && ft_strchr(shell->args[1], 's') == NULL)
			ft_putendl(shell->args[i]);
		i++;
	}
	delete_history_line(shell, shell->history_length);
}

void	write_arg_s(t_shell *shell)
{
	int		i;
	char	*tmp;
	t_node	*history;

	i = 2;
	tmp = NULL;
	history = NULL;
	delete_history_line(shell, shell->history_length);
	while (shell->args && shell->args[i] != NULL)
	{
		tmp = ft_strdup(shell->args[i]);
		shell->history_length++;
		shell->history = init_nonvoid_history(tmp, shell->history);
		i++;
	}
}
