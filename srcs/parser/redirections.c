/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:59:04 by arohani           #+#    #+#             */
/*   Updated: 2018/07/25 18:50:14 by arohani          ###   ########.fr       */
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

void 		implement_redirs(t_shell *shell, t_ast *cmd)
{
	t_redirs	*tmp = NULL;
	int 		beg;
	char		*str = NULL;
	int			ionum = -1;

	printf("DEBUG implement 1\n");
	tmp = cmd->redirs;
	printf("DEBUG implement 2\n");
	while (tmp)	//creates argument table, opens and closes respective fd before launching execution then freeing table and t_redirs before & after redirection
	{
		if (tmp->prev && tmp->next)
			close(tmp->prev->new_fd);
		printf("DEBUG implement 3\n");
		beg = tmp->beg;
		//end = tmp->end;
		//should consider a clause for create arg table to handle prefix, ie if end < beg, means redir was first item, ie handle as prefix
//		create_arg_table(shell, tmp->beg, tmp->end);
		while (beg <= tmp->end)
		{
			printf("DEBUG implement 4\n");
			if (shell->tok[beg] == TK_IO_NUMBER)
			{
				printf("DEBUG implement 5\n");
				str = ft_strndup(shell->line + shell->tok[beg + 1], shell->tok[beg + 2]);
				ionum = ft_atoi(str);
				ft_strdel(&str);
				printf("DEBUG implement 6, ionum = %d\n", ionum);
				if (!(shell->args))
					create_arg_table(shell, tmp->beg, beg - 3);
			}
			else
				beg += 3;
			printf("DEBUG implement 7\n");
		}
		beg = tmp->beg;
		printf("DEBUG implement 8\n");
		if (ionum == -1 && !(shell->args))
			create_arg_table(shell, tmp->beg, tmp->end);
		printf("DEBUG implement 9\n");
		if (tmp->next_re != -1)
		{
			if (shell->tok[tmp->next_re] == TK_LESS || shell->tok[tmp->next_re] == TK_DLESS ||
				shell->tok[tmp->next_re] == TK_LESSAND)
			{
				printf("DEBUG implement 10, next_re = %d\n", tmp->next_re);
				(ionum != -1) ? close (ionum) : close (0);
				printf("DEBUG implement 11, CLOSED 0\n");
				if (tmp->next)
				{	
					printf("DEBUG implement 12\n");
					str = ft_strndup(shell->line + shell->tok[tmp->next->beg + 1], shell->tok[tmp->next->beg + 2]);
					tmp->new_fd = open(str, O_RDONLY);
					ft_strdel(&str);
					printf("DEBUG implement 13, OPENED %d\n", tmp->new_fd);
				}
			}
			else
			{
				printf("DEBUG implement 14, ionum = %d\n", ionum);
			//	(ionum != -1) ? close (ionum) : close (1);
				if (ionum != -1)
					close (1);
					//printf("should close 1 here, but need to debug\n");
				else
					close (ionum);				
				printf("DEBUG implement 15, CLOSED 1\n");
				if (tmp->next)
				{
					str = ft_strndup(shell->line + shell->tok[tmp->next->beg + 1], shell->tok[tmp->next->beg + 2]);
					if (shell->tok[tmp->next_re] == TK_GREAT || shell->tok[tmp->next_re] == TK_GREATAND)
						tmp->new_fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
					else if (shell->tok[tmp->next_re] == TK_DGREAT)
						tmp->new_fd = open(str, O_CREAT | O_APPEND | O_WRONLY, 0644);
					else
						printf("REDIRECTION #%d STILL NEEDS HANDLING\n", tmp->next_re);
					printf("DEBUG implement 16, OPENED %d\n", tmp->new_fd);
					ft_strdel(&str);
				}
			}
		}
		//still need to carefully test for how command return values work with redirections
		printf("DEBUG implement 17\n");
		if (!(tmp->next))
			shell->new_fd = (tmp->next_re == -1) ? tmp->prev->new_fd : tmp->new_fd;
		tmp = tmp->next;	//if tmp->next, free list through tmp->prev
		if (!tmp)
			printf("DEBUG implement 19, tmp is NULL\n");
	}
	printf("DEBUG implement 20, shell->new_fd = %d\n", shell->new_fd);
	ast_execute(shell, cmd);
}

void		fill_redirs(t_shell *shell, t_ast *ast, int beg, int redir)
{
	t_redirs	*tmp;
	int 		ret;

	printf("DEBUG 1, initial redir pos = %d\n", redir);
	if (!(tmp = (t_redirs *)malloc(sizeof(t_redirs))))
		return ;
	printf("DEBUG 2\n");
	ast->redirs = tmp;
	tmp->beg = beg;
	tmp->end = redir - 3;
	tmp->next_re = redir;
	printf("DEBUG 3\n");
	tmp->handled = 0;
	tmp->prev = NULL;
	tmp->next = NULL;
	while ((ret = is_redirect(shell, ast, redir + 3, ast->end)))
	{
		printf("returned %d from is_direct check in fill_redirs\n", ret);
		if (!(tmp->next = (t_redirs *)malloc(sizeof(t_redirs))))
			return ;
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->beg = redir + 3;
		tmp->end = ret - 3;
		tmp->handled = 0;
		tmp->next_re = ret;
		redir = ret;
		tmp->next = NULL;
	}
	printf("DEBUG 4, ret = %d\n", ret);
}

static void	display_redir_list(t_shell *shell, t_ast *ast)
{
	t_redirs	*tmp;
	char		*str;
	int			i = 1;

	tmp = ast->redirs;
	while (tmp->next)
	{
		str = ft_strndup(shell->line + shell->tok[tmp->beg + 1], shell->tok[tmp->beg + 2]);
		printf("redir list item %d = %s\n", i++, str);;
		ft_strdel(&str);
		tmp = tmp->next;
	}
	printf("now displaying backwards navigation of redir list\n");
	while (tmp)
	{
		str = ft_strndup(shell->line + shell->tok[tmp->beg + 1], shell->tok[tmp->beg + 2]);
		printf("redir list item %d = %s\n", i++, str);;
		ft_strdel(&str);
		tmp = tmp->prev;
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
		tmp->next_re = -1;
		tmp->handled = 0;
		tmp->next = NULL;
		printf("t_redirs is officially completed, now sending to TEST DISPLAY function\n");
		display_redir_list(shell, ast);
	}
	return (0);

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

