/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:59:04 by arohani           #+#    #+#             */
/*   Updated: 2018/07/23 18:49:35 by arohani          ###   ########.fr       */
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

t_redirs	*init_redirs(t_shell *shell, t_ast *cmd, int redir)
{
	t_redirs	*head;
	int			end;
	int			beg;

	if (!(head = (t_redirs *)malloc(sizeof(t_redirs))))
		return (NULL);
	head->beg = cmd->beg;
	beg = head->beg;
	while (beg < cmd->end)
	{
		if (shell->tok[beg] == TK_GREAT || shell->tok[beg] == TK_DGREAT ||
			shell->tok[beg] == TK_GREATAND || shell->tok[beg] == TK_LESS ||
			shell->tok[beg] == TK_DLESS || shell->tok[beg] == TK_LESSAND)
			{
				head->end = beg - 3;

			}
	}
}

int			is_redirect(t_shell *shell, int beg, int end)
{
	while (beg <= end)
	{
		if (shell->tok[beg] == TK_GREAT || shell->tok[beg] == TK_DGREAT ||
			shell->tok[beg] == TK_GREATAND || shell->tok[beg] == TK_LESS ||
			shell->tok[beg] == TK_DLESS || shell->tok[beg] == TK_LESSAND)
			return (beg);
		beg += 3;
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

