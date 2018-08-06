/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 18:27:37 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/06 00:26:31 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node	*write_history_to_mem(t_node *history, t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->appnd_hst->next != NULL)
		shell->appnd_hst = shell->appnd_hst->next;
	while (shell->appnd_hst)
	{
		history = init_nonvoid_history(shell->appnd_hst->cmd, history);
		shell->history_length++;
		shell->appnd_hst = shell->appnd_hst->prev;
	}
	return (history);
}
