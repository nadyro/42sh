/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:23 by arohani           #+#    #+#             */
/*   Updated: 2018/08/12 16:20:55 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

static int		split_next_operator(t_shell *shell, t_ast *ast, int check_pipe)
{
	int		beg;
	int		end;

	beg = ast->beg;
	end = ast->end;
	while (end > beg)
	{
		if (shell->tok[end] == TK_PIPE && check_pipe == 1)
			return (1);
		else if ((shell->tok[end] == TK_AND_IF || shell->tok[end] == TK_OR_IF)
				&& check_pipe == 0)
			return (1);
		end -= 3;
	}
	return (0);
}

static void		send_to_next_split(t_shell *shell, t_ast *tmp, int from_semi)
{
	if (tmp && !(tmp->left) && !(tmp->right) &&
			tmp->parent && tmp == tmp->parent->left)
	{
		if (from_semi == 1 && split_next_operator(shell, tmp, 0) == 1)
			ast_loop_and_or(tmp, shell, 0);
		else
			ast_loop_pipe(tmp, shell, 0);
	}
}

void			ast_loop_pipe(t_ast *head, t_shell *shell, int i)
{
	if ((i = head->end) <= 0)
		return ;
	while (i > head->beg)
	{
		if (shell->tok[i] == TK_PIPE)
		{
			head->split = i;
			if (shell->tok[i] != TK_END && shell->tok[i] != -1)
				head->right = fill_rightast(head);
			if (head->split > 0)
			{
				head->left = fill_leftast(head);
				if (head->left)
					ast_loop_pipe(head->left, shell, 0);
				break ;
			}
		}
		else
			i -= 3;
	}
}

void			ast_loop_and_or(t_ast *head, t_shell *shell, int i)
{
	if ((i = head->end) <= 0)
		return ;
	while (i > head->beg)
	{
		if (shell->tok[i] == TK_AND_IF || shell->tok[i] == TK_OR_IF)
		{
			head->split = i;
			head->right = fill_rightast(head);
			if (split_next_operator(shell, head->right, 1) == 1)
				ast_loop_pipe(head->right, shell, 0);
			if (head->split > 0)
			{
				head->left = fill_leftast(head);
				if (head->left)
					ast_loop_and_or(head->left, shell, 0);
				break ;
			}
		}
		else
			i -= 3;
	}
	send_to_next_split(shell, head, 0);
}

void			ast_loop_semi(t_ast *head, t_shell *shell, int i)
{
	if ((i = head->end) <= 0)
		return ;
	while (i > head->beg)
	{
		if (shell->tok[i] == TK_SEMI)
		{
			head->split = i;
			head->right = fill_rightast(head);
			if (split_next_operator(shell, head->right, 0) == 1)
				ast_loop_and_or(head->right, shell, 0);
			else if (split_next_operator(shell, head->right, 1) == 1)
				ast_loop_pipe(head->right, shell, 0);
			if (head->split > 0)
			{
				head->left = fill_leftast(head);
				if (head->left)
					ast_loop_semi(head->left, shell, 0);
				break ;
			}
		}
		else
			i -= 3;
	}
	send_to_next_split(shell, head, 1);
}
