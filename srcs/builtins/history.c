/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:17:24 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/07/29 18:58:54 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    read_history(t_node *history)
{
    char    *c;
    int     i;
    int     x;
    int     j;
    int     k;

    i = open(".history", O_RDONLY);
    c = NULL;
    x = 1;
    k = 0;
    j = 0;
    if (i >= 0)
    {
        while (get_next_line(i, &c) == 1)
        {
            x++;
            j++;
            k++;
            //ft_putnbr(x++);
            //ft_putchar(' ');
            //ft_putendl(c);
            history = history->next;
        }        
    }
    while (history->next != NULL)
    {
        k++;
        history = history->next;
    }
    
    while (history)
    {
        ft_putchar(' ');
        ft_putendl(history->cmd);
        k--;
        history = history->prev;
        if (k == j)
            break;
    }
}