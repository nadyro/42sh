/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_evaluate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:20 by arohani           #+#    #+#             */
/*   Updated: 2018/08/20 21:09:01 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

static void	evaluate_redirs(t_shell *shell, t_ast *cmd, int ret)
{
	shell->redir_error = 0;
	fill_redirs(shell, cmd, cmd->beg, ret);
	shell->last_id = (ft_strstr(shell->line, "<<")) ?
		last_heredoc_id(shell, cmd->redirs) : -1;
	cmd->hd_check = (shell->last_id >= 0) ? 1 : 0;
	shell_args_from_redirs(shell, cmd);
	ast_execute(shell, cmd, 0);
	shell->last_id = -1;
	free_redirs(cmd->redirs);
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
