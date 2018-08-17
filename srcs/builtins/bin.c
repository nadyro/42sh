/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:01:43 by arohani           #+#    #+#             */
/*   Updated: 2018/08/16 21:25:22 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			builtin_check(t_shell *shell, t_ast *cmd, int env)
{
	if (shell && shell->args && shell->args[0])
	{
		if (ft_strcmp(shell->args[0], "echo") == 0)
			return (ash_echo(shell));
		else if (ft_strcmp(shell->args[0], "cd") == 0)
			return (ash_cd(shell, env));
		else if (ft_strcmp(shell->args[0], "setenv") == 0)
			return (ash_setenv(shell));
		else if (ft_strcmp(shell->args[0], "unsetenv") == 0)
			return (ash_unsetenv(shell));
		else if (ft_strcmp(shell->args[0], "env") == 0)
		{
			ash_env(shell, cmd);
			return (cmd->cmd_ret);
		}
		else if (ft_strcmp(shell->args[0], "exit") == 0)
			return (ash_exit(shell));
		else if (ft_strcmp(shell->args[0], "history") == 0)
			return (ash_history(shell));
	}
	return (-10);
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
	int		n;

	i = if_opt_n(shell);
	n = (i == 2) ? 1 : 0;
	if (shell->args && shell->args[i])
	{
		while (shell->args && shell->args[i])
		{
			if (!(shell->args[i + 1]))
			{
				(n == 1) ? ft_putstr(shell->args[i]) :
					ft_putendl(shell->args[i]);
				return (0);
			}
			ft_putstr(shell->args[i++]);
			(shell->args[i]) ? ft_putchar(' ') : ft_putchar('\n');
		}
		return (0);
	}
	return (0);
}

int			ash_exit(t_shell *shell)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (shell && shell->args && shell->args[1] && shell->args[2])
	{
		ft_putstr_fd("42sh: exit: too many arguments\n", 2);
		return (-1);
	}
	else if (shell && shell->args && shell->args[1])
		n = ft_atoi(shell->args[1]);
	write_history_file(shell, 0);
	if (shell)
		sh_close(n, "");
	return (-1);
}
