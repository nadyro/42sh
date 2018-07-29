/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:59:04 by arohani           #+#    #+#             */
/*   Updated: 2018/07/25 20:16:49 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>
#include "builtins.h"
#include <stdio.h>

/*
**	Basically, to perform > or >>, first close stdout, then open file to the
**	right of > or >>, then execute command to the left of > or >>, then close
**	the fd used for file on the right of > or >>. To preform <, do same as >,
**	except for 2 things: 1) close(0) instead of close(1) to obviously close
**	stdin instead of stdout, and 2) when opening file based on argument that
**	comes after "<", open as READONLY instead of WRITEONLY
*/

static void		handle_prefix_syntax(t_shell *shell, t_ast *cmd)
{
	t_redirs	*tmp = NULL;

	//for handling : > FILENAME CMD WORD WORD WORD into CMD WORD WORD WORD > FILENAME ..... IO
	tmp = cmd->redirs;
	if (tmp->next && (tmp->next->beg + 3) <= tmp->next->end)
	{
		/* here we presume that shell considers everything that follows FILENAME to be CMD + WORDS when written in prefix syntax */
		tmp->beg = tmp->next->beg + 3;
		tmp->end = tmp->next->end;
		tmp->next->end = tmp->next->beg;
		create_arg_table(shell, tmp->beg, tmp->end);
	}
	else
		shell->args = NULL;
}

static void		shell_args_from_redirs(t_shell *shell, t_ast *cmd)
{
	t_redirs	*tmp = NULL;
	int 		beg;

	tmp = cmd->redirs;
	beg = tmp->beg;
	if (tmp->beg == tmp->next_re)
	{
		handle_prefix_syntax(shell, cmd);
		ft_print_table(shell->args);
		return ;
	}
	while (beg <= tmp->end)
	{
		if (shell->tok[beg] == TK_IO_NUMBER)
		{
			tmp->ionum = beg;
			create_arg_table(shell, tmp->beg, tmp->ionum - 3);
			return ;
		}
		beg += 3;
	}
	create_arg_table(shell, tmp->beg, tmp->end);
}

void 		implement_redirs(t_shell *shell, t_ast *cmd)
{
	t_redirs	*tmp = NULL;
	int 		beg;
	char		*str = NULL;
	//int			ionum = -1;

	shell_args_from_redirs(shell, cmd);
	tmp = cmd->redirs;
	while (tmp)	//opens and closes respective fd before launching execution
	{
		if (tmp->prev && tmp->next)
			close(tmp->prev->new_fd);
		beg = tmp->beg;
		if (tmp->next)
		{
			if (shell->tok[tmp->next_re] == TK_LESS || shell->tok[tmp->next_re] == TK_DLESS ||
				shell->tok[tmp->next_re] == TK_LESSAND)
			{
				close (0);
				//(ionum != -1) ? close (ionum) : close (0);
				if (tmp->next)
				{
					str = ft_strndup(shell->line + shell->tok[tmp->next->beg + 1], shell->tok[tmp->next->beg + 2]);
					if ((tmp->new_fd = open(str, O_RDONLY)) < 0)
						printf("FD ERROR in < redirection, need to handle\n");
					ft_strdel(&str);
				}
			}
			else	//should be all non less-than redirections
			{
			//	(ionum != -1) ? close (ionum) : close (1);			
				close (1);
				if (tmp->next)
				{
					str = ft_strndup(shell->line + shell->tok[tmp->next->beg + 1], shell->tok[tmp->next->beg + 2]);
					if (shell->tok[tmp->next_re] == TK_GREAT || shell->tok[tmp->next_re] == TK_GREATAND)
						if ((tmp->new_fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 0)
							printf("FD ERROR in > redirection, need to handle\n");
					if (shell->tok[tmp->next_re] == TK_DGREAT)
						if ((tmp->new_fd = open(str, O_CREAT | O_APPEND | O_WRONLY, 0644)) < 0)
							printf("FD ERROR in >> redirection, need to handle\n");
				//	else
				//		printf("REDIRECTION #%d STILL NEEDS HANDLING\n", tmp->next_re), this is meant for letting other token squeek through;
					//dup2(tmp->new_fd, 1);
					ft_strdel(&str);
				}
			}
		}
		//still need to carefully test for how command return values work with redirections
		if (!(tmp->next))
			shell->new_fd = tmp->new_fd;
		tmp = tmp->next;	//if tmp->next, free list through tmp->prev
	}
	ast_execute(shell, cmd);
}

void		fill_redirs(t_shell *shell, t_ast *ast, int beg, int redir)
{
	t_redirs	*tmp;
	int 		ret;

	if (!(tmp = (t_redirs *)malloc(sizeof(t_redirs))))
		return ;
	ast->redirs = tmp;
	tmp->beg = beg;
	tmp->end = (beg != redir) ? redir - 3 : redir;
	tmp->ionum = -1;
	tmp->next_re = redir;
	tmp->prev = NULL;
	tmp->next = NULL;
	while ((ret = is_redirect(shell, ast, redir + 3, ast->end)) != -1)
	{
		if (!(tmp->next = (t_redirs *)malloc(sizeof(t_redirs))))
			return ;
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->beg = redir + 3;
		tmp->end = ret - 3;
		tmp->ionum = -1;
		tmp->next_re = ret;
		redir = ret;
		tmp->next = NULL;
	}
}

int			is_redirect(t_shell *shell, t_ast *ast, int beg, int end)
{
	t_redirs		*tmp = NULL;

	while (beg <= end)
	{
		if (shell->tok[beg] == TK_GREAT || shell->tok[beg] == TK_DGREAT ||
			shell->tok[beg] == TK_GREATAND || shell->tok[beg] == TK_LESS ||
			shell->tok[beg] == TK_DLESS || shell->tok[beg] == TK_LESSAND)
			return (beg);
		beg += 3;
	}
	if ((tmp = ast->redirs))
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_redirs *)malloc(sizeof(t_redirs))))
			return (-1);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->beg = tmp->prev->next_re + 3;
		tmp->end = ast->end;
		tmp->ionum = -1;
		tmp->next_re = -1;
		tmp->next = NULL;
	}
	return (-1);
}

int	        *redirect_check(t_shell *shell)
{	
	int		i;
	int		fd = -1;
	int		*result = (int *)malloc(sizeof(int) * 2);

	i = 0;
	while (shell->args && shell->args[i])
	{
		if (shell->args[i] && ((!(ft_strcmp(shell->args[i], ">")) 
			|| !(ft_strcmp(shell->args[i], "<")) || !(ft_strcmp(shell->args[i], ">>")))))
		{
			/* in this clause bc either > or >> or < exists. If <, close 0, else close 1 for other redirections */
			(ft_strcmp(shell->args[i], "<") == 0) ? close(0) : close(1);
			if (ft_strcmp(shell->args[i], "<") == 0)
				fd = open(shell->args[i + 1], O_RDONLY);
			else
				fd = (shell->args[i][1] && shell->args[i][1] == '>') ? open(shell->args[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0644)
				: open(shell->args[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd < 0)
			{
				printf("manage error opening file here\n");
				exit(EXIT_FAILURE);
			}
			shell->args[i] = 0;
			result[1] = i;
			result[0] = fd;
			return (result);
		}
		i++;
	}
	result[0] = 0;
	result[1] = 0;
	/* returns int table with tb[0] = the post-redirect fd,
	 ** tb[1] = index of redirection location in table (redirect is replaced with NULL) */
	return (result);
}
