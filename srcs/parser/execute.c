/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:01:35 by arohani           #+#    #+#             */
/*   Updated: 2018/08/20 16:43:13 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#define ARG shell->args[0]

void		restore_std_fds(t_shell *shell, t_ast *cmd, t_redirs *rd)
{
	t_redirs *tmp;

	tmp = rd;
	if (cmd->hd_check == 1)
	{
		if (fcntl(cmd->hfd[0], F_GETFD) != -1)
			close(cmd->hfd[0]);
		if (fcntl(cmd->hfd[1], F_GETFD) != -1)
			close(cmd->hfd[1]);
	}
	while (tmp)
	{
		if (tmp->new_fd >= 0 && fcntl(tmp->new_fd, F_GETFD) != -1)
			close(tmp->new_fd);
		tmp = tmp->next;
	}
	dup2(shell->s_in, 0);
	close(shell->s_in);
	dup2(shell->s_out, 1);
	close(shell->s_out);
	dup2(shell->s_err, 2);
	close(shell->s_err);
}

static void	launch_exec(t_shell *shell, char *full_path)
{
	if (full_path && (execve(full_path, shell->args, shell->envv) == -1))
		(execve(ARG, shell->args, shell->envv));
	else if (!(full_path))
		(execve(ARG, shell->args, shell->envv));
	exit(1);
}

static void	ast_launch(t_shell *shell, t_ast *cmd)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		launch_exec(shell, shell->full_path);
	else if (pid < 0)
	{
		cmd->cmd_ret = -1;
		ft_putstr_fd("error pid less than 0 in ast launch", 2);
	}
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		cmd->cmd_ret = (status) ? -1 : 0;
		while (!WIFEXITED(status) && !WIFSIGNALED(status)
				&& !WIFSTOPPED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	if (shell->full_path)
		ft_strdel(&(shell->full_path));
}

static void	execute_non_builtin(t_shell *shell, t_ast *cmd)
{
	struct stat	tmp;

	if (stat(ARG, &tmp) == 0 && (S_ISDIR(tmp.st_mode) ||
	!(tmp.st_mode & (S_IXUSR))))
	{
		if (!(tmp.st_mode & (S_IXUSR)))
		{
			if (!(shell->full_path) ||
			(shell->full_path && stat(shell->full_path, &tmp) == 0
			&& !(tmp.st_mode & (S_IXUSR))))
			{
				permission_denied(shell);
				cmd->cmd_ret = -1;
			}
			else
				ast_launch(shell, cmd);
		}
		else
		{
			executing_directory(shell);
			cmd->cmd_ret = -1;
		}
	}
	else
		ast_launch(shell, cmd);
}

int			ast_execute(t_shell *shell, t_ast *cmd, int env_ex)
{
	if (shell && shell->args && ARG && shell->redir_error != 1)
	{
		if (env_ex == 1 ||
						(cmd->cmd_ret = builtin_check(shell, cmd)) == -10)
		{
			shell->full_path = (ARG[0] != '/' &&
					has_paths(shell, 0) == 1) ?
					arg_full_path(shell) : NULL;
			if (handle_arg_errors(shell, cmd) == 0)
				execute_non_builtin(shell, cmd);
		}
	}
	shell->redir_error = 0;
	shell->bin_ret = 0;
	return (cmd->cmd_ret);
}
