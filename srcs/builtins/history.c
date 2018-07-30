/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:17:24 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/07/29 23:24:33 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_history(int *x, char **cmd, int to_free)
{
    int     i;

    i = *x;
    i = i + 1;
    *x = i;
	ft_putnbr(*x);
	ft_putchar(' ');
	ft_putendl(*cmd);
	if (to_free == 0)
	{
		free(*cmd);
		*cmd = NULL;
	}
}

t_node	*get_last_cmds(t_node *history, int nbr)
{
    int     i;
    char    **last_cmds;
    int     y;
        
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
            break;
    }
    i = 0;
    while (i < y)
        ft_putendl(last_cmds[i++]);
	return (history);
}

void	read_history(t_node *history, int nbr)
{
	char	*c;
	int		i;
	int		x;

	i = open(".history", O_RDONLY);
	c = NULL;
	x = 0;
	if (i >= 0)
	{
        if (nbr > 0)
			get_last_cmds(history, nbr);		
		else
		{
            while (history->next != NULL)
			history = history->next;
			while (get_next_line(i, &c) == 1)
			{
				print_history(&x, &c, 0);
				if (history)
					history = history->prev;
			}
			while (history)
			{
				print_history(&x, &history->cmd, 1);
				history = history->prev;
			}
		}
	}
}
