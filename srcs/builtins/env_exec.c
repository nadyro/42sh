/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:00:45 by arohani           #+#    #+#             */
/*   Updated: 2018/08/14 17:33:24 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

static int	env_launch_exec(t_shell *shell, char **mod)
{
	char	*full_path;

	full_path = arg_full_path(shell);
	if (execve(shell->args[0], shell->args, mod) == -1)
	{
		if (execve(full_path, shell->args, mod) == -1)
		{
			ft_putstr_fd("env: ", 2);
			(!full_path) ? ft_putstr_fd(shell->args[0], 2) :
				ft_putstr_fd(full_path, 2);
			ft_putstr_fd(": Command not found.\n", 2);
			if (full_path && full_path[0])
				ft_strdel(&full_path);
			exit(EXIT_FAILURE);
		}
	}
	if (full_path && full_path[0])
		ft_strdel(&full_path);
	return (1);
}

static int	env_launch(t_shell *shell, char **mod)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		env_launch_exec(shell, mod);
	else if (pid < 0)
		ft_putstr_fd("error pid less than 0 in lsh launch", 2);
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

static char	**get_new_args(t_shell *shell)
{
	int		count;
	int		start;
	char	**args;

	args = NULL;
	start = shell->list->last;
	count = 0;
	while (shell->args && shell->args[start++])
		count++;
	if (count)
	{
		if (!(args = (char **)malloc(sizeof(char *) * (count + 1))))
			return (NULL);
	}
	count = 0;
	start = shell->list->last;
	while (shell->args && shell->args[start])
	{
		args[count++] = ft_strdup(shell->args[start++]);
	}
	if (count)
		args[count] = 0;
	if (shell->args && shell->args[0])
		free_table(shell->args);
	return (args);
}

int			ft_exec(t_shell *shell, char **env)
{
	if (shell->list->last == 0 && shell->args[1])
		shell->list->last = 1;
	if (shell->args[0] != NULL)
	{
		shell->args = get_new_args(shell);
		return (env_launch(shell, env));
	}
	return (0);
}
