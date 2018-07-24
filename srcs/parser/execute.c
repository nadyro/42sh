/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 15:01:35 by arohani           #+#    #+#             */
/*   Updated: 2018/07/23 18:16:28 by arohani          ###   ########.fr       */
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
	if (execve(shell->args[0], shell->args, shell->envv) == -1)
	{
		if (execve(full_path, shell->args, shell->envv) == -1)
		{
			printf("both execve calls didn't work properly!!!!\n");
			cmd->cmd_ret = -1;
		}
	}
}

static void	ast_launch(t_shell *shell, t_ast *cmd, int redirs)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
//IMPORTANT	int		*fd_changed;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		//printf("pid == 0 i.e. child process: %s\n", shell->args[0]);
//IMPORTANT		fd_changed = redirect_check(shell);
		launch_exec(shell, shell->full_path, cmd);
//		if (fd_changed[1])
//		{
//			close(fd_changed[0]);
//		}
	}
	else if (pid < 0)
		ft_putstr_fd("error pid less than 0 in lsh launch", 2);
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		if (status)	//necessary as status !=0 means command return value was non-zero
			cmd->cmd_ret = -1;
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
		//printf("should be returning from PARENT process, command = %s, pid = %d\n", shell->args[0], pid);
	}
	if (shell->full_path)
		ft_strdel(&(shell->full_path));
}

int 		implement_redirs(t_shell *shell, t_ast *cmd)
{
	t_redirs	*tmp = NULL;
	int 		beg;
	int 		i = 0;
	char		**next;

	tmp = cmd->redirs;
	next = (tmp && tmp->next) ? create_arg_table(shell, tmp->next->beg, tmp->next->end);
	while (tmp)	//creates argument table, opens and closes respective fd before launching execution then freeing table and t_redirs before & after redirection
	{
		//beg = tmp->beg;
		//end = tmp->end;
		create_arg_table(shell, tmp->beg, tmp->end);
		if (shell->tok[tmp->next_re] == TK_LESS || shell->tok[tmp->next_re] == TK_DLESS ||
			shell->tok[tmp->next_re] == TK_LESSAND)
		{
			close (0);
			tmp->new_fd = open(shell->args[i + 1], O_RDONLY);
		}
		else
		{
			close (1);
			if (shell->tok[tmp->next_re] == TK_GREAT || shell->tok[tmp->next_re] == TK_GREATAND)
				tmp->new_fd = open(shell->args[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
			else if (shell->tok[tmp->next_re] == TK_DGREAT)
				tmp->new_fd = open(shell->args[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
			else
				printf("REDIRECTION #%d STILL NEEDS HANDLING\n", tmp->next_re);
		}
		//still need to carefully test for how command return values work with redirections
		ast_execute(shell, cmd, 1);
	}
}

int			ast_execute(t_shell *shell, t_ast *cmd, int redirs)
{
	if (shell && shell->args && shell->args[0])
	{
		shell->full_path = (has_paths(shell, 0) == 1) ? arg_full_path(shell) : NULL;
		if (builtin_check(shell) != -1)
			cmd->cmd_ret = 0;
		else if (shell->full_path || !(access(shell->args[0], F_OK)))	//if binary exists in PATH, fork and execute
		{
			ast_launch(shell, cmd, 0);
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
	//printf("DEBUG 1: in ast_loop, shell->line = %s\n, shell->tok[0] = %d\n", shell->line, shell->tok[0]);
	if (ast)
	{
		//printf("DEBUG 2: entering ast_evaluate FROM ast_loop\n");
		ast_evaluate(ast, shell);
	//	printf("exiting ast_evaluate FROM ast_loop after completion\n");
	}
}