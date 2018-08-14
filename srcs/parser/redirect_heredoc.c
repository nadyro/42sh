/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 13:40:15 by arohani           #+#    #+#             */
/*   Updated: 2018/08/14 15:34:05 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "heredoc.h"
#include "builtins.h"
#include <stdio.h>

void	implement_heredoc(t_ast *cmd, int id)
{
	char		*heredoc;

	heredoc = NULL;
	if (cmd && id >= 0)
	{
		heredoc = heredoc_get(id);
		fprintf(stderr, "id = %d, heredoc = %s\n", id, heredoc);
		if (heredoc)
		{
			pipe(cmd->hfd);
			write(cmd->hfd[1], heredoc, ft_strlen(heredoc));
			close(cmd->hfd[1]);
			dup2(cmd->hfd[0], 0);
			close(cmd->hfd[0]);
		}
	}
}

int		last_heredoc_id(t_shell *shell, t_redirs *node)
{
	t_redirs	*tmp;
	int			id;

	tmp = node;
	id = (shell->last_hd < 0) ? -1 : 0;
	while (tmp && tmp->next_re != -1)
	{
		if (shell->tok[tmp->next_re] == TK_DLESS)
			id++;
		tmp = tmp->next;
	}
	shell->last_hd = (shell->last_hd < 0) ? id : (shell->last_hd + id);
	return (id);
}
