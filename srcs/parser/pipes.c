/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 17:54:38 by arohani           #+#    #+#             */
/*   Updated: 2018/08/12 13:28:21 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

static void	evaluate_pipe_left(t_shell *shell, t_ast *cmd, pid_t pid, int fd[2])
{
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		ast_evaluate(cmd->left, shell);
		(cmd->left->cmd_ret == 0) ? exit(0) : exit(1);
	}
	else if (pid < 0)
		exit(1);
}

static void	evaluate_pipe_right(t_shell *shell, t_ast *cmd, int fd[2])
{
	int			pfd[2];

	pfd[0] = dup(0);
	pfd[1] = dup(1);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	dup2(pfd[1], 1);
	close(pfd[1]);
	ast_evaluate(cmd->right, shell);
	dup2(pfd[0], 0);
	close(pfd[0]);
}

int			evaluate_pipe_node(t_shell *shell, t_ast *cmd)
{
	pid_t		pid;
	pid_t		wpid;
	int			fd[2];
	int			status;

	status = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0 || pid < 0)
		evaluate_pipe_left(shell, cmd, pid, fd);
	else
	{
		evaluate_pipe_right(shell, cmd, fd);
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status)
				&& !WIFSTOPPED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
		if (cmd->right->cmd_ret == -1)
			return (-1);
		return (0);
	}
	return (0);
}
