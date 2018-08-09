/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:01:35 by arohani           #+#    #+#             */
/*   Updated: 2018/08/08 17:03:09 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include "builtins.h"
#include <stdio.h>

void		restore_std_fds(t_shell *shell, t_redirs *rd)
{
	t_redirs *tmp = rd;

	dup2(shell->s_in, 0);	//essentially replaces fd 0 with fd shell->s_in
	close(shell->s_in);
	dup2(shell->s_out, 1);
	close(shell->s_out);
	dup2(shell->s_err, 2);
	close(shell->s_err);
	//close(shell->new_fd);
	while (tmp)
	{
		if (fcntl(tmp->new_fd, F_GETFD) != -1)	
			close(tmp->new_fd);
		if (tmp->next_re == TK_DLESS)		//closes pipe fd in parent node
		{
			if (fcntl(tmp->hfd[0], F_GETFD) != -1)
				close(tmp->hfd[0]);
			if (fcntl(tmp->hfd[1], F_GETFD) != -1)	
				close(tmp->hfd[1]);
		}
		tmp = tmp->next;
	}
}

static void	launch_exec(t_shell *shell, char *full_path, t_ast *cmd)
{
	struct 		stat tmp;

	if (execve(shell->args[0], shell->args, shell->envv) == -1)
	{
		if (execve(full_path, shell->args, shell->envv) == -1)
		{
			ft_putstr_fd(shell->args[0], 2);
			(full_path) ? stat(full_path, &tmp) : stat(shell->args[0], &tmp);
			(S_ISDIR(tmp.st_mode)) ? ft_putstr_fd(": is a directory\n", 2) : ft_putstr_fd(": Permission denied\n", 2);
			cmd->cmd_ret = -1;
			exit (1);
		}
	}
}

static void	ast_launch(t_shell *shell, t_ast *cmd)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		//printf("pid == 0 i.e. child process: %s\n", shell->args[0]);
	/*	if (shell->redir_error == 1)
		{
			restore_std_fds(shell, cmd->redirs);
			exit (1);
		}
	*/	launch_exec(shell, shell->full_path, cmd);
	}
	else if (pid < 0)
		ft_putstr_fd("error pid less than 0 in lsh launch", 2);
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		if (status)	//necessary as status !=0 means command return value was non-zero
			cmd->cmd_ret = -1;
		while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status))
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
		if (cmd->redirs)
			restore_std_fds(shell, cmd->redirs);
		//printf("should be returning from PARENT process, command = %s, pid = %d\n", shell->args[0], pid);
	}
	if (shell->full_path)
		ft_strdel(&(shell->full_path));
}

static void	handle_dotdot_error(t_shell *shell, t_ast *cmd)
{
		ft_putstr_fd(shell->args[0], 2);
		ft_putstr_fd(": Command not found.\n", 2);
		ft_bzero((void *)(shell->args[0]), ft_strlen(shell->args[0]));
		ft_strdel(&(shell->full_path));
		cmd->cmd_ret = -1;	
}

int			ast_execute(t_shell *shell, t_ast *cmd)
{
	if (shell && shell->args && shell->args[0] && shell->redir_error != 1)
	{
		shell->full_path = (shell->args[0][0] != '/' && has_paths(shell, 0) == 1) ? arg_full_path(shell) : NULL;
		if (ft_strcmp(shell->args[0], ".") == 0 || ft_strcmp(shell->args[0], "..") == 0)
			handle_dotdot_error(shell, cmd);
		else if (builtin_check(shell) != -1)
			cmd->cmd_ret = 0;
		else if (ft_strlen(shell->args[0]) != 0 && (shell->full_path || !(access(shell->args[0], F_OK))))	//if binary exists in PATH, fork and execute
			ast_launch(shell, cmd);
		else if (ft_strlen(shell->args[0]) == 0 || (shell->args[0][0] != '\0' && access(shell->args[0], F_OK)))
		{
			ft_putstr_fd(shell->args[0], 2);
			(shell->args[0][0] == '/') ? ft_putstr_fd(": No such file or directory\n", 2) :
			ft_putstr_fd(": Command not found.\n", 2);
			cmd->cmd_ret = -1;
		}
	}
	else if (shell->redir_error == 1)
		shell->redir_error = 0;
	if (cmd && cmd->redirs)
		restore_std_fds(shell, cmd->redirs);
	return (cmd->cmd_ret);
	//else
	//	return (0);		//ie if args table doesnt exist and command line is just spaces and tabs, return 0
}

void		ast_loop(t_shell *shell, t_ast *ast)
{
	int		status;

	status = 1;
	//printf("DEBUG 1: in ast_loop, shell->line = %s\n, shell->tok[0] = %d\n", shell->line, shell->tok[0]);
	if (ast)
	{
		//printf("DEBUG 2: entering ast_evaluate FROM ast_loop\n");
		ast_evaluate(ast, shell);
		free_ast(ast);
	//	printf("exiting ast_evaluate FROM ast_loop after completion\n");
	}
}
