/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ash_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 14:24:51 by arohani           #+#    #+#             */
/*   Updated: 2018/06/15 14:50:52 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

static void	launch_exec(t_shell *shell, char *full_path)
{
	shell->error = 0;
	
	if (execve(shell->args[0], shell->args, shell->envv) == -1)
	{
		if (execve(full_path, shell->args, shell->envv) == -1)
		{
			(!full_path) ? ft_putstr_fd(shell->args[0], 2) :
			ft_putstr_fd(full_path, 2);
			ft_putstr_fd(": Command not found.\n", 2);
			shell->error = -1;
			printf("shell->error = %d\n", shell->error);
			//exit(EXIT_FAILURE);
		}
	}
}

/*
**	Basically, to perform > or >>, first close stdout, then open file to the
**	right of > or >>, then execute command to the left of > or >>, then close
**	the fd used for file on the right of > or >>. To preform <, do same as >,
**	except for 2 things: 1) close(0) instead of close(1) to obviously close
**	stdin instead of stdout, and 2) when opening file based on argument that
**	comes after "<", open as READONLY instead of writeonly
*/

static int	*redirect_check(t_shell *shell)
{	
	int		i;
	int		fd = -1;
	int		*result = (int *)malloc(sizeof(int) * 2);

	i = 0;
	while (shell->args && shell->args[i])
	{
		if (shell->args[i] && ((!(ft_strcmp(shell->args[i], ">")) 
			|| !(ft_strcmp(shell->args[i], "<")) || !(ft_strcmp(shell->args[i], ">>")))))
		{
			(ft_strcmp(shell->args[i], "<") == 0) ? close(0) : close(1);
			if (ft_strcmp(shell->args[i], "<") == 0)
				fd = open(shell->args[i + 1], O_RDONLY);
			else
				fd = (shell->args[i][1] && shell->args[i][1] == '>') ? open(shell->args[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0644)
				: open(shell->args[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd < 0)
			{
				printf("manage error opening file here\n");
				exit(EXIT_FAILURE);
			}
			shell->args[i] = 0;
			result[1] = i;
			result[0] = fd;
			return (result);
		}
		i++;
	}
	result[0] = 0;
	result[1] = 0;
	return (result);
}

static int	ash_launch(t_shell *shell)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	*full_path;
	int		*fd_changed;

	printf("entered ash_launch\n");
	full_path = NULL;
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		fd_changed = redirect_check(shell);
		full_path = (has_paths(shell, 0) == 1) ? arg_full_path(shell) : NULL;
		launch_exec(shell, full_path);
		printf("after launch_exec call, shell->error = %d\n", shell->error);
		if (fd_changed[1])
		{
			close(fd_changed[0]);
		}
	}
	else if (pid < 0)
		ft_putstr_fd("error pid less than 0 in lsh launch", 2);
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	if (full_path && full_path[0])
		ft_strdel(&full_path);
	if (shell->error == -1)
	{
		printf("SHELL ERROR  FOUND IN COMMAND EXECUTION, returning -1\n");
		shell->error = 0;
		return (-1);
	}
	else
		return (1);
}

int			ash_execute(t_shell *shell)
{
	int		ret;

	ret = 0; 
	if (shell->args[0] == NULL)
		return (1);
	if ((ret = builtin_check(shell)) != -1)
		return (ret);
	else
		return (ash_launch(shell));
}
