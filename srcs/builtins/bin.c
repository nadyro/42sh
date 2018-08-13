/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:01:43 by arohani           #+#    #+#             */
/*   Updated: 2018/08/08 01:56:39 by nsehnoun         ###   ########.fr       */
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
	int			i;
	t_history	*hist_args;

	i = 0;
	hist_args = check_history_args(shell);
	if (hist_args->vide == 0)
		shell->history = dispatch_history_queries(hist_args, shell);
	else
	{
		i = hist_args->vide;
		history_errors(hist_args);
		free(hist_args);
		return (i);
	}
	free(hist_args);
	return (1);
}

void		history_errors(t_history *hist_args)
{
	if (hist_args->vide == 1)
	{
		ft_putstr("Error : history: d : ");
		ft_putnbr(hist_args->d_arg);
		ft_putendl("out of range.");
	}
	if (hist_args->vide == 2)
		ft_putendl("Error : history: d : Undefined offset");
	if (hist_args->vide == 3)
	{
		ft_putstr("history : usage: ");
		ft_putstr("history [-c] [-d offset] [n] or history -awrn");
		ft_putendl(" or history -ps arg [arg...]");
	}
	if (hist_args->vide == 4)
		ft_putendl("Error : history: Use only one of -warn.");
	if (hist_args->vide == 5)
	{
		ft_putstr("Error : history: flag or ");
		ft_putendl("numeric argument required.");
	}
}

int			ash_exit(t_shell *shell)
{
	write_history_file(shell, 0);
	if (shell)
		exit (0);
	return (1);
}
