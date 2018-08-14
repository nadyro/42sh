/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:01:35 by arohani           #+#    #+#             */
/*   Updated: 2018/08/14 15:40:29 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#define ARG shell->args[0]

void		restore_std_fds(t_shell *shell, t_ast *cmd, t_redirs *rd)
{
	t_redirs *tmp;

	tmp = rd;
	if (cmd->hd_check)
	{
		if (fcntl(cmd->hfd[0], F_GETFD) != -1)
			close(cmd->hfd[0]);
		if (fcntl(cmd->hfd[1], F_GETFD) != -1)
			close(cmd->hfd[1]);
	}
	while (tmp)
	{
		if (fcntl(tmp->new_fd, F_GETFD) != -1)
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

static void	launch_exec(t_shell *shell, char *full_path, t_ast *cmd)
{
	struct stat		tmp;

	if (execve(ARG, shell->args, shell->envv) == -1)
	{
		if (execve(full_path, shell->args, shell->envv) == -1)
		{
			ft_putstr_fd(ARG, 2);
			(full_path) ? stat(full_path, &tmp) : stat(ARG, &tmp);
			(S_ISDIR(tmp.st_mode)) ? ft_putstr_fd(": is a directory\n", 2) :
				ft_putstr_fd(": Permission denied\n", 2);
			cmd->cmd_ret = -1;
			exit(1);
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
		launch_exec(shell, shell->full_path, cmd);
	else if (pid < 0)
	{
		cmd->cmd_ret = -1;
		ft_putstr_fd("error pid less than 0 in lsh launch", 2);
	}
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		if (status)
			cmd->cmd_ret = -1;
		while (!WIFEXITED(status) && !WIFSIGNALED(status)
				&& !WIFSTOPPED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	if (shell->full_path)
		ft_strdel(&(shell->full_path));
}

static int	handle_arg_errors(t_shell *shell, t_ast *cmd)
{
	if ((ft_strcmp(ARG, ".") == 0 || ft_strcmp(ARG, "..") == 0))
	{
		ft_putstr_fd(ARG, 2);
		ft_putstr_fd(": Command not found.\n", 2);
		ft_bzero((void *)(ARG), ft_strlen(ARG));
		ft_strdel(&(shell->full_path));
		return (cmd->cmd_ret = -1);
	}
	else if (ft_strlen(ARG) && (ARG[0] == '/' ||
				(ARG[0] == '.' && ARG[1] == '/')) && access(ARG, F_OK))
	{
		ft_putstr_fd(ARG, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (cmd->cmd_ret = -1);
	}
	else if (!(ft_strlen(ARG)) ||
			(access(ARG, F_OK) && access(shell->full_path, F_OK)))
	{
		ft_putstr_fd(ARG, 2);
		(ARG[0] == '/' || (ARG[0] == '.' && ARG[1] == '/')) ?
			ft_putstr_fd(": No such file or directory\n", 2) :
			ft_putstr_fd(": Command not found.\n", 2);
		return (cmd->cmd_ret = -1);
	}
	return (0);
}

int			ast_execute(t_shell *shell, t_ast *cmd)
{
	if (shell && shell->args && ARG && shell->redir_error != 1)
	{
		if ((shell->bin_ret = builtin_check(shell)) != -1)
			cmd->cmd_ret = 0;
		else
		{
			shell->full_path = (ARG[0] != '/' &&
					has_paths(shell, 0) == 1) ? arg_full_path(shell) : NULL;
			if (handle_arg_errors(shell, cmd) == 0)
				ast_launch(shell, cmd);
		}
	}
	shell->redir_error = 0;
	shell->bin_ret = 0;
	return (cmd->cmd_ret);
}
