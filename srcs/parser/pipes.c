/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 17:54:38 by arohani           #+#    #+#             */
/*   Updated: 2018/08/08 18:27:07 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

int        evaluate_pipe_node(t_shell *shell, t_ast *cmd)
{
    pid_t       pid;
	pid_t		wpid;
    int         fd[2];
	int			status = 0;
	int 		pfd[2];

    pfd[0] = dup(0);
	pfd[1] = dup(1);
	pipe(fd);   //creates pipe read end (fd[0]) and write end (fd[1]), accessible by all children and parent
    pid = fork();
	if (pid == 0)	//first fork to execute left command in order to later read results by right command
	{
		dup2(fd[1], 1); // replaces stdout with pipe write end before executing child process 
		close(fd[0]);   //closes pipe read end in child process
		close(fd[1]);   //closes pipe write end in child process
		ast_evaluate(cmd->left, shell);
		//fprintf(stderr, "printed after evaluating left node of pipe node\n");
		(cmd->left->cmd_ret == 0) ? exit(0) : exit(1);
	}
	else if (pid < 0)
		exit (1);
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		ast_evaluate(cmd->right, shell);
		dup2(pfd[0], 0);
		close(pfd[0]);
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status) && !WIFSTOPPED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
		if (cmd->right->cmd_ret == -1)
			return (-1);
		return (0);
	}
	return (0);
}
