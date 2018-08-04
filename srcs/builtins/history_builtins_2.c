/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 02:11:12 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/04 23:33:58 by nsehnoun         ###   ########.fr       */
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
