/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:01:35 by arohani           #+#    #+#             */
/*   Updated: 2018/07/19 13:04:22 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include "builtins.h"
#include <stdio.h>

static void	launch_exec(t_shell *shell, char *full_path, t_ast *cmd)
{
	//printf("before executing commands, here is the table of arguments:\n");
	//ßft_print_table(shell->args);
	if (execve(shell->args[0], shell->args, shell->envv) == -1)
	{
		if (execve(full_path, shell->args, shell->envv) == -1)
		{
			printf("both execve calls didn't work properly!!!!\n");
			cmd->cmd_ret = -1;
			//exit(EXIT_FAILURE);
		}
	}
}

static void	ast_launch(t_shell *shell, t_ast *cmd)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	int		*fd_changed;

//	printf("entered ast_launch\n");
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		//printf("pid == 0 i.e. child process: %s\n", shell->args[0]);
		fd_changed = redirect_check(shell);
		launch_exec(shell, shell->full_path, cmd);
	//	printf("after launch_exec call, shell->error = %d\n", shell->error);
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
		//printf("should be returning from PARENT process, command = %s, pid = %d\n", shell->args[0], pid);
	}
	if (shell->full_path)
		ft_strdel(&(shell->full_path));
	/*if (shell->error == -1)
	{
	//	printf("SHELL ERROR  FOUND IN COMMAND EXECUTION, returning -1\n");
		shell->error = 0;
		return (-1);
	}
	else
		return (1);*/
}

int			ast_execute(t_shell *shell, t_ast *cmd)
{
	if (shell && shell->args && shell->args[0])
	{
		shell->full_path = (has_paths(shell, 0) == 1) ? arg_full_path(shell) : NULL;
		if (builtin_check(shell) != -1)
			cmd->cmd_ret = 0;
		else if (shell->full_path || !(access(shell->args[0], F_OK)))	//if binary exists in PATH, fork and execute
		{
			ast_launch(shell, cmd);
			//printf("launched fork, returning : cmd_ret = %d\n", cmd->cmd_ret);
			return (cmd->cmd_ret);
		}
		else
		{
			ft_putstr_fd(shell->args[0], 2);
			ft_putstr_fd(": Command not found.\n", 2);
			cmd->cmd_ret = -1;			
		}
	}
	//printf("about to return ast_execute: cmd_ret = %d\n", cmd->cmd_ret);
	return (cmd->cmd_ret);
	//else
	//	return (0);		//ie if args table doesnt exist and command line is just spaces and tabs, return 0
}

void		ast_loop(t_shell *shell, t_ast *ast)
{
	int		status;

	status = 1;
	//printf("DEBUG 1: in ast_loop, ast->arg = %s\n, first char = %d\nsecond char = %d\n", ast->arg, ast->arg[0], ast->arg[1]);
	if (ast && ast->arg[0])
	{
		//printf("DEBUG 2: entering ast_evaluate FROM ast_loop\n");
		status = ast_evaluate(ast, shell);
	//	printf("exiting ast_evaluate FROM ast_loop after completion\n");
	}
}