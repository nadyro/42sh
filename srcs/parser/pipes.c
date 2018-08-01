/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 17:54:38 by arohani           #+#    #+#             */
/*   Updated: 2018/08/01 14:45:03 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>
/*
void        evaluate_pipe_node(t_shell *shell, t_ast *cmd)
{
    pid_t       pid;
    pid_t		wpid;
	int         fd[2];
    t_ast       *ast = cmd;
	int			status = 0;

    pipe(fd);   //creates pipe read end (fd[0]) and write end (fd[1]), accessible by all children and parent
    pid = fork();
	if (pid < 0)
		ft_putstr_fd("error piping: pid is less than 0\n", 2);
	else if (pid == 0)
	{
		dup2(fd[1], 1); // child found, replaces stdout with pipe write end 
		close(fd[0]);   //closes pipe read end
		close(fd[1]);   //closes pipe write end
		ast_evaluate(ast->left, shell);
		printf("should only appear here if LEFT command failed to execute\n");
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
			printf("should only appear here if RIGHT command failed to execute, left_ret = %d, right_ret = %d\n", ast->left->cmd_ret, ast->right->cmd_ret);
			exit(1);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			wpid = waitpid(pid, &status, WUNTRACED);
			printf("in PIPE, status = %d\n", status);
		}
	}
}
*/
int        evaluate_pipe_node(t_shell *shell, t_ast *cmd)
{
    pid_t       pid;
    int         fd[2];
    t_ast       *ast = cmd;
	int			status = 0;

    pipe(fd);   //creates pipe read end (fd[0]) and write end (fd[1]), accessible by all children and parent
    pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1); // child found, replaces stdout with pipe write end 
		close(fd[0]);   //closes pipe read end
		close(fd[1]);   //closes pipe write end
		ast_evaluate(ast->left, shell);		
		(ast->left->cmd_ret == 0) ? exit (0) : exit(1);
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