/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:23 by arohani           #+#    #+#             */
/*   Updated: 2018/07/19 16:39:16 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

int 			get_tk_end_pos(t_shell *shell)
{
	int 	last = 0;

	while (shell->tok[last] != -1 && shell->tok[last] != TK_END)
	{
		if (shell->tok[last] != TK_END && shell->tok[last] != -1)
			last += 3;
		if (shell->tok[last] == TK_END)
		{
			if (shell->tok[last-3] == TK_NEWLINE)
			{	
				shell->tok[last-3] = TK_END;
				return (last - 3);
			}
			return (last);
		}
	}
	ft_putstr_fd("Error : No end token found\n", 2);
	return (-1);
}

static int 		split_next_operator(t_shell *shell, t_ast *ast, int check_pipe)
{
	int 	beg = ast->beg;
	int 	end = ast->end;

	while (end > beg)
	{
		if (shell->tok[end] == TK_PIPE && check_pipe == 1)
			return (1);
		else if ((shell->tok[end] == TK_AND_IF || shell->tok[end] == TK_OR_IF)
			&& check_pipe == 0)
			return (1);
		end -= 3;
	};
	return (0);
}

static void		ast_loop_pipe(t_ast *head, t_shell *shell)
{
	int		i;
	t_ast	*tmp = head;

	if ((i = tmp->end) <= 0)
		return ;
	while (i > tmp->beg)
	{
		if (shell->tok[i] == TK_PIPE)
		{
			tmp->split = i;
			if (shell->tok[i] != TK_END && shell->tok[i] != -1)
				tmp->right = fill_rightast(tmp);
			if (tmp->split > 0)
			{
				tmp->left = fill_leftast(tmp);
				if (tmp->left)
					ast_loop_pipe(tmp->left, shell);
				break ;
			}
		}
		else
			i -= 3;
	}
}

static void		ast_loop_and_or(t_ast *head, t_shell *shell)
{
	int		i = 0;
	t_ast	*tmp = head;

	if ((i = tmp->end) <= 0)
		return ;
	while (i > tmp->beg)
	{
		if (shell->tok[i] == TK_AND_IF || shell->tok[i] == TK_OR_IF)
		{
			tmp->split = i;
			tmp->right = fill_rightast(tmp);
			if (split_next_operator(shell, tmp->right, 1) == 1)
				ast_loop_pipe(tmp->right, shell);
			if (tmp->split > 0)
			{
				tmp->left = fill_leftast(tmp);
				if (tmp->left)
					ast_loop_and_or(tmp->left, shell);
				break ;
			}
		}
		else
			i -= 3;
	}
	if (tmp && !(tmp->left) && !(tmp->right) && tmp->parent && tmp == tmp->parent->left)
		ast_loop_pipe(tmp, shell);
}

static void		ast_loop_semi(t_ast *head, t_shell *shell)
{
	int		i;
	t_ast	*tmp = head;

	if ((i = tmp->end) <= 0)
		return ;
	while (i > tmp->beg)
	{
		if (shell->tok[i] == TK_SEMI)
		{
			tmp->split = i;
			tmp->right = fill_rightast(tmp);
			if (split_next_operator(shell, tmp->right, 0) == 1)
				ast_loop_and_or(tmp->right, shell);
			else if (split_next_operator(shell, tmp->right, 1) == 1)
				ast_loop_pipe(tmp->right, shell);
			if (tmp->split > 0)
			{
				tmp->left = fill_leftast(tmp);
				if (tmp->left)
					ast_loop_semi(tmp->left, shell);
				break ;
			}
		}
		else
			i -= 3;
	}
	if (tmp && !(tmp->left) && !(tmp->right) && tmp->parent && tmp == tmp->parent->left)
	{
		if (split_next_operator(shell, tmp, 0) == 1)
			ast_loop_and_or(tmp, shell);
		else
			ast_loop_pipe(tmp, shell);
	}
}

t_ast	    *get_ast(t_shell *shell)
{
	t_ast	*head;
	t_ast	*tmp;

	if (shell->line[ft_strlen(shell->line) - 1] == '\n')	//replaces '\n' from line editing with '\0'
		shell->line[ft_strlen(shell->line) - 1] = '\0';
	head = init_ast(shell);
	tmp = head;
	if (ft_strchr(shell->line, ';'))
		ast_loop_semi(tmp, shell);
	else if (ft_strstr(shell->line, "&&") || ft_strstr(shell->line, "||"))
		ast_loop_and_or(tmp, shell);
	else if (ft_strchr(shell->line, '|'))
		ast_loop_pipe(tmp, shell);
	return (head);
}
