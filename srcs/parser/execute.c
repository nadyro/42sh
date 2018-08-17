/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:01:35 by arohani           #+#    #+#             */
/*   Updated: 2018/08/17 16:34:41 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#define ARG shell->args[0]
#include <stdio.h>
extern int errno;

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

static void	launch_exec(t_shell *shell, char *full_path)
{
	ft_putstr_fd("REMOVE THIS: entered launch exec\n", 2);
	if (ARG && (!full_path || (full_path && execve(full_path, shell->args, shell->envv) == -1)))
	{
		ft_putstr_fd("failed execution of full_path = ", 2);
		ft_putendl_fd(full_path, 2);
		if ((execve(ARG, shell->args, shell->envv) == -1))
		{
			fprintf(stderr, "Here is the error message :\n%s\n", strerror(errno));
			int i = 0;
	//		ft_putstr_fd("failed 2nd attempt, searching in current directory with : ", 2);
	//		ft_putendl_fd(ARG, 2);
	//		ft_putstr_fd(ARG, 2);
	//		ft_putstr_fd(": Permission denied\n", 2);
		}
	}
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

static void	pre_exec_check(t_shell *shell, t_ast *cmd)
{
	struct stat	tmp;

	fprintf(stderr, "DEBUG 1, ARG = %s\n", ARG);
	if (stat(ARG, &tmp) == 0 && ((!(tmp.st_mode & (S_IXUSR))) || S_ISDIR(tmp.st_mode)))
	{
		fprintf(stderr, "DEBUG 2, ARG = %s\n", ARG);
		if ((!(tmp.st_mode & (S_IXUSR))))
		{
			fprintf(stderr, "DEBUG 3\n");
			if (!shell->full_path || (shell->full_path &&
				stat(shell->full_path, &tmp) == 0 && (!(tmp.st_mode & (S_IXUSR)))))
			{
				fprintf(stderr, "DEBUG 4, full_path = %s\n", shell->full_path);
				permission_denied(shell);
				cmd->cmd_ret = -1;
				return ;
			}
			fprintf(stderr, "DEBUG 5\n");
		}
		else
		{
			fprintf(stderr, "DEBUG 6\n");
			executing_directory(shell);
			cmd->cmd_ret = -1;
			fprintf(stderr, "DEBUG 7\n");
			return ;
		}
		fprintf(stderr, "DEBUG 8\n");
	}
	fprintf(stderr, "DEBUG 9, ARG = %s\n", ARG);
	ast_launch(shell, cmd);	
}

int			ast_execute(t_shell *shell, t_ast *cmd, int env_ex)
{
	if (shell && shell->args && ARG && shell->redir_error != 1)
	{
		if (env_ex == 1 || ((cmd->cmd_ret = builtin_check(shell, cmd)) == -10))
		{
			shell->full_path = (ARG[0] != '/' &&
					has_paths(shell, 0) == 1) ? arg_full_path(shell) : NULL;
			if (handle_arg_errors(shell, cmd) == 0)
			{
				fprintf(stderr, "about to send to pre_exec_check after no errors found\n");
				pre_exec_check(shell, cmd);
			}
		}
	}
	shell->redir_error = 0;
	shell->bin_ret = 0;
	return (cmd->cmd_ret);
}
