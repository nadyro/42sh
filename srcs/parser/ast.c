/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:20 by arohani           #+#    #+#             */
/*   Updated: 2018/08/11 19:01:54 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

static void		free_redirs(t_redirs *list)
{
	t_redirs	*next;
	t_redirs	*tmp;
 	next = NULL;
	tmp = list;
	while (tmp)
	{
		next = tmp->next;
		if (tmp)
			free(tmp);
		tmp = next;
	}
	tmp = NULL;
}

void			free_ast(t_ast *head)
{
	t_ast	*tmp = head;
 	if (!tmp)
		return ;
	else if (!(tmp->left) && !(tmp->right))
	{
		free(tmp);
		return ;
	}
	else
	{
		if (tmp->left)
			free_ast(tmp->left);	
		if (tmp->right)
			free_ast(tmp->right);
		free(tmp);
	}
}

t_ast		*fill_leftast(t_ast *parent)
{
	t_ast	*left = NULL;

	if (!(left = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	left->parent = parent;
	left->split = 0;
	left->beg = parent->beg;
	left->end = parent->split - 3;
	left->left = NULL;
	left->right = NULL;
	return (left);
}

t_ast		*fill_rightast(t_ast *parent)
{
	t_ast	*right = NULL;

	if (!(right = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	right->parent = parent;
	right->split = 0;
	right->beg = parent->split + 3;
	right->end = parent->end;
	right->left = NULL;
	right->right = NULL;
	return (right);
}

t_ast		*init_ast(t_shell *shell)
{
	t_ast	*head;

	if (!(head = (t_ast *)malloc(sizeof(t_ast))))
			return (NULL);	
	head->parent = NULL;
	head->split = 0;
	head->beg = 0;
	head->end = get_tk_end_pos(shell) - 3;
	head->left = NULL;
	head->right = NULL;	
	return (head);
}

void		create_arg_table(t_shell *shell, int beg, int end)
{
	int		i = beg;
	int		last = 0;
	
	if (end < beg)
		shell->args = NULL;
	else
	{
		while (i <= end)
		{
			while (shell->tok[i] == TK_SPACE || shell->tok[i] == TK_NEWLINE)
				i += 3;
			if (shell->tok[i] != TK_END && shell->tok[i] != TK_SPACE && shell->tok[i] != TK_NEWLINE)
				last++;
			if (shell->tok[i] != TK_END)
				i += 3;
		}
		if (last)
		{
			if (!(shell->args = (char **)malloc(sizeof(char *) * (last + 1))))
				return ;
			shell->args[last] = 0;
			last = 0;
			i = beg;
			while (i <= end)
			{
				while (shell->tok[i] == TK_SPACE || shell->tok[i] == TK_NEWLINE)
					i += 3;
				if (shell->tok[i] != TK_SPACE && shell->tok[i] != TK_NEWLINE && shell->tok[i] != TK_END)
				{
					shell->args[last++] = token2str(&shell->tok[i], shell->line, shell->envv);
					i += 3;
				}
			}
		}
	}
}

int         ast_evaluate(t_ast *ast, t_shell *shell)
{
	int			op;
	int			v1 = 0;
	int			v2 = 0;
	int 		ret = 0;

	if (ast == NULL)
	{
		return (0);
	}
	else if (!(ast->left) && !(ast->right))
	{
		fprintf(stderr, "ast_evaluate DEBUG 1\n");
		ast->cmd_ret = 0;
		ast->redirs = NULL;
		fprintf(stderr, "ast_evaluate DEBUG 2\n");
		if ((ret = is_redirect(shell, ast, ast->beg, ast->end)) != -1)
		{
			fprintf(stderr, "ast_evaluate DEBUG 3\n");
			shell->redir_error = 0;
			fprintf(stderr, "ast_evaluate DEBUG 4\n");
			fill_redirs(shell, ast, ast->beg, ret);
			fprintf(stderr, "ast_evaluate DEBUG 5\n");
			shell->s_in = dup(0);
			shell->s_out = dup(1);
			shell->s_err = dup(2);
			fprintf(stderr, "ast_evaluate DEBUG 6\n");
			implement_redirs(shell, ast);
			fprintf(stderr, "ast_evaluate DEBUG 7\n");
			free_redirs(ast->redirs);
			fprintf(stderr, "ast_evaluate DEBUG 8\n");
		}
		else
		{
			create_arg_table(shell, ast->beg, ast->end);
			ast_execute(shell, ast);
		}
		fprintf(stderr, "ast_evaluate DEBUG 9\n");
		if (shell->args)
		{
			fprintf(stderr, "ast_evaluate DEBUG 10\n");
			free_table(shell->args);
		}
		if (ast->cmd_ret == 0 || ast->cmd_ret == -1)
		{
			fprintf(stderr, "ast_evaluate DEBUG 11\n");
			return (ast->cmd_ret);
		}
	}
	else if (ast)
	{
		op = shell->tok[ast->split];
		if (op == TK_AND_IF)
		{
			v1 = ast_evaluate(ast->left, shell);
			if (v1 != 0)
				return (ast->cmd_ret = -1);
			else if (v1 == 0)
			{
				v2 = ast_evaluate(ast->right, shell);
				ast->cmd_ret = (v2 == 0) ? 0 : 1;
				return (ast->cmd_ret);
			}
		}
		else if (op == TK_OR_IF)
		{
			v1 = ast_evaluate(ast->left, shell);
			if (v1 == 0)
				return (ast->cmd_ret = v1);
			else
			{
				v2 = ast_evaluate(ast->right, shell);
				if (v2 == 0)
					return (ast->cmd_ret = 0);
				else
					return (ast->cmd_ret = -1);
			}
		}
		else if (op == TK_PIPE)
		{
			return (evaluate_pipe_node(shell, ast));
		}
		else if (op == TK_SEMI)
		{
			v1 = ast_evaluate(ast->left, shell);
			v2 = ast_evaluate(ast->right, shell);
		}
	}
	return (0);
}
