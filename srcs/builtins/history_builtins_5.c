/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 18:27:37 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/06 03:46:56 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node	*write_history_to_mem(t_node *history, t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->appnd_hst && shell->appnd_hst->next != NULL)
		shell->appnd_hst = shell->appnd_hst->next;
	while (shell->appnd_hst)
	{
		history = init_nonvoid_history(shell->appnd_hst->cmd, history);
		shell->history_length++;
		shell->appnd_hst = shell->appnd_hst->prev;
	}
	return (history);
}

void	write_arg_p(t_shell *shell)
{
	if (shell->args[2] != NULL)
	{
		ft_putendl(shell->args[2]);
		shell->history = delete_history_line(shell, shell->history_length);
	}
}