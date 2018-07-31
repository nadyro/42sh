/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 17:54:38 by arohani           #+#    #+#             */
/*   Updated: 2018/07/31 18:59:15 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

void        evaluate_pipe_node(t_shell *shell, t_ast *cmd)
{
    pid_t       pid;
    int         fd[2];
    t_ast       *ast = cmd;

    pipe(fd);   //creates pipe read end (fd[0]) and write end (fd[1]), accessible by all children and parent
    pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1); // child found, replaces stdout with pipe write end 
		close(fd[0]);   //closes pipe read end
		close(fd[1]);   //closes pipe write end
		ast_evaluate(ast->left, shell);
		exit(1);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[0], 0);
			close(fd[1]);
			close(fd[0]);
			ast_evaluate(ast->right, shell);		
			exit (1);
		}
		else
		{
			int		status;
			close(fd[0]);
			close(fd[1]);
			waitpid(pid, &status, 0);
		}
	}
}