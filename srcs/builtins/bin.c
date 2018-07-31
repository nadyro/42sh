/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:01:43 by arohani           #+#    #+#             */
/*   Updated: 2018/07/30 22:21:53 by kernel_pani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			builtin_check(t_shell *shell)
{
	if (shell && shell->args && shell->args[0])
	{
		if (ft_strcmp(shell->args[0], "echo") == 0)
			return (ash_echo(shell));
		else if (ft_strcmp(shell->args[0], "cd") == 0)
			return (ash_cd(shell));
		else if (ft_strcmp(shell->args[0], "setenv") == 0)
			return (ash_setenv(shell));
		else if (ft_strcmp(shell->args[0], "unsetenv") == 0)
			return (ash_unsetenv(shell));
		else if (ft_strcmp(shell->args[0], "env") == 0)
			return (ash_env(shell));
		else if (ft_strcmp(shell->args[0], "exit") == 0)
			return (ash_exit(shell));
		else if (ft_strcmp(shell->args[0], "history") == 0)
			return (ash_history(shell));
	}
	return (-1);
}

int			if_opt_n(t_shell *shell)
{
	int		i;

	i = (shell->args && shell->args[1] && !ft_strcmp(shell->args[1], "-n"))
	? 2 : 1;
	if (shell->args[i] == NULL && i == 1)
		ft_putchar('\n');
	return (i);
}

int			ash_echo(t_shell *shell)
{
	int		i;

	i = if_opt_n(shell);
	if (shell->args && shell->args[i])
	{
		while (shell->args && shell->args[i])
		{
			if (i == 1 && shell->args[i][0] == '-')
				i++;
			if (!(shell->args[i + 1]))
			{
				(!(ft_strcmp(shell->args[1], "-n"))) ?
					ft_putstr(shell->args[i]) : ft_putendl(shell->args[i]);
				return (1);
			}
			ft_putstr(shell->args[i++]);
			(shell->args[i]) ? ft_putchar(' ') : ft_putchar('\n');
		}
		return (1);
	}
	return (1);
}

int			ash_history(t_shell *shell)
{
	int		i;
	int		conv;

	i = 0;
	conv = 0;
	check_history_args(shell);
	if (shell->args && shell->args[1])
	{
		conv = ft_atoi(shell->args[1]);
		if (conv <= shell->history_length)
			read_history(shell->history, conv);
		else
			read_history(shell->history, 0);
		return (1);
	}
	else if (shell->args)
		read_history(shell->history, 0);
	return (1);
}

int			ash_exit(t_shell *shell)
{
	write_history_file(shell->history);
	if (shell)
		exit (0);
	return (1);
}
