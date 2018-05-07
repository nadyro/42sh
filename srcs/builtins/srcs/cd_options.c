/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:16:39 by arohani           #+#    #+#             */
/*   Updated: 2018/04/19 15:19:09 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*void    handle_options(t_shell *shell)
{
    
}
*/
int		opt_check(t_shell *shell)
{
    int         i;
    int         j;

    i = 1;
    j = 1;
	shell->p = 0;
	shell->l = 0;
    while (shell->args && shell->args[i])
    {
        printf("shell->args[i] = %s\n", shell->args[i]);
        if (!ft_strcmp(shell->args[i], "--"))
            return (i + 1);
        else if (shell->args[i][0] == '-')
        {
            while (shell->args[i][j])
            {
                printf("at top of interior while loop, shell->args[i] = %s\n", shell->args[i]);
                if (shell->args[i][j] == 'P')
                    shell->p = 1;
                else if (shell->args[i][j] == 'L')
                    shell->l = 1;
                else if (shell->args[i][j] != '\0')
                {
                    ft_putstr_fd("cd: no such file or directory: ", 2);
                    ft_putendl_fd(shell->args[i], 2);
                    return (-1);
                }
                j++;
            }
        }
        else
            return (i);
        j = 1;
        i++;
    }
    return (i);
}