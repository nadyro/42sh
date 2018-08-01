/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:53:44 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/07/31 17:03:55 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node  *dispatch_history_queries(t_history *hist_args, t_node *history)
{
    int     i;

    i = 0;
    if (hist_args->c == 1)
       history = clear_history_mem(history);
    /*if (hist_args->d == 1)
        delete_history_line(history);
    if (hist_args->w == 1)
        write_history_mem_to_file(history);*/
    return (history);
}

t_node  *clear_history_mem(t_node *history)
{
    t_node *tmp;
    t_node *tmp_1;

    tmp = history;
    while (tmp)
    {
        tmp_1 = tmp;
        tmp = tmp_1->next;
        ft_bzero(tmp_1->cmd, ft_strlen(tmp_1->cmd));
        free(tmp_1->cmd);
        free(tmp_1);
    }
    history = NULL;
    ft_putstr("finished clear\n");
    return (history);
}