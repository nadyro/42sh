/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_construct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 13:38:32 by arohani           #+#    #+#             */
/*   Updated: 2018/08/12 13:39:01 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "heredoc.h"
#include "builtins.h"

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
