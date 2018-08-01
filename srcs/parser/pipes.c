/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 17:54:38 by arohani           #+#    #+#             */
/*   Updated: 2018/08/01 14:50:43 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

int        evaluate_pipe_node(t_shell *shell, t_ast *cmd)
{
    pid_t       pid;
    int         fd[2];
    t_ast       *ast = cmd;
	int			status = 0;

    pipe(fd);   //creates pipe read end (fd[0]) and write end (fd[1]), accessible by all children and parent
    pid = fork();
	if (pid == 0)	//first fork to execute left command in order to later read results by right command
	{
		dup2(fd[1], 1); // replaces stdout with pipe write end before executing child process 
		close(fd[0]);   //closes pipe read end in child process
		close(fd[1]);   //closes pipe write end in child process
		ast_evaluate(ast->left, shell);		
		(ast->left->cmd_ret == 0) ? exit (0) : exit(1);
	}
	else
	{
		pid = fork();	//second fork to execute right command and still return to ast
		if (pid == 0)
		{
			dup2(fd[0], 0);		//replaces stdin with read end of pipe in order to read from left process before executing right process
			close(fd[1]);
			close(fd[0]);
			ast_evaluate(ast->right, shell);
			(ast->right->cmd_ret == 0) ? exit (0) : exit (1);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(pid, &status, 0);
			if (status)
				return (-1);
			return (0);
		}
	}
}