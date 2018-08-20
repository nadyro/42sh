/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_evaluate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:20 by arohani           #+#    #+#             */
/*   Updated: 2018/08/20 15:41:46 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

static void	evaluate_redirs(t_shell *shell, t_ast *ast, int ret)
{
	shell->redir_error = 0;
	fill_redirs(shell, ast, ast->beg, ret);
	shell->s_in = dup(0);
	shell->s_out = dup(1);
	shell->s_err = dup(2);
	implement_redirs(shell, ast);
	if (ast && ast->redirs)
		restore_std_fds(shell, ast, ast->redirs);
	free_redirs(ast->redirs);
}

static int	evaluate_leaf_node(t_ast *ast, t_shell *shell)
{
	int			ret;

	ret = 0;
	ast->cmd_ret = 0;
	ast->redirs = NULL;
	if ((ret = is_redirect(shell, ast, ast->beg, ast->end)) != -1)
		evaluate_redirs(shell, ast, ret);
	else
	{
		create_arg_table(shell, ast->beg, ast->end);
		ast_execute(shell, ast, 0);
	}
	if (shell->args)
		free_table(shell->args);
	return (ast->cmd_ret);
}

static int	evaluate_and_or(t_ast *ast, t_shell *shell, int op)
{
	int		v1;
	int		v2;

	v1 = ast_evaluate(ast->left, shell);
	if (op == TK_AND_IF)
	{
		if (v1 != 0)
			ast->cmd_ret = -1;
		else if (v1 == 0)
		{
			v2 = ast_evaluate(ast->right, shell);
			ast->cmd_ret = (v2 == 0) ? 0 : 1;
		}
	}
	else if (op == TK_OR_IF)
	{
		if (v1 == 0)
			ast->cmd_ret = 0;
		else
		{
			v2 = ast_evaluate(ast->right, shell);
			ast->cmd_ret = (v2 == 0) ? 0 : -1;
		}
	}
	return (ast->cmd_ret);
}

int			ast_evaluate(t_ast *ast, t_shell *shell)
{
	int			op;
	int			v1;
	int			v2;

	v1 = 0;
	v2 = 0;
	if (ast == NULL)
		return (0);
	else if (!(ast->left) && !(ast->right))
		return (evaluate_leaf_node(ast, shell));
	else if (ast)
	{
		op = shell->tok[ast->split];
		if (op == TK_AND_IF || op == TK_OR_IF)
			return (evaluate_and_or(ast, shell, op));
		else if (op == TK_PIPE)
			return (evaluate_pipe_node(shell, ast));
		else if (op == TK_SEMI)
		{
			v1 = ast_evaluate(ast->left, shell);
			v2 = ast_evaluate(ast->right, shell);
		}
	}
	return (0);
}
