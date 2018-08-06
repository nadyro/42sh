/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:20 by arohani           #+#    #+#             */
/*   Updated: 2018/08/01 15:02:30 by arohani          ###   ########.fr       */
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
	int 		counter = 0;

	next = NULL;
	tmp = list;
	while (tmp)
	{
		next = tmp->next;
		if (tmp)
		{
			counter++;
			free(tmp);
		}
		tmp = next;
	}
	tmp = NULL;
	printf("while freeing redirs, freed: %d nodes\n", counter);
}

/*static void		free_ast_elem(t_ast *node)
{
	if (node)
		free(node);
}*/

void			free_ast(t_ast *head)
{
	t_ast	*tmp = head;
	static int 	counter = 0;

	if (!tmp)
		return ;
	else if (!(tmp->left) && !(tmp->right))
	{
		printf("freeing ast node #%d\n", ++counter);
		free(tmp);
		return ;
	}
	else
	{
		if (tmp->left)
			free_ast(tmp->left);	
		if (tmp->right)
			free_ast(tmp->right);
		printf("freeing ast node #%d\n", ++counter);
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
	left->cmd_ret = 0;
	left->redirs = NULL;
	left->beg = parent->beg;
	left->end = parent->split - 3;
	left->left = NULL;
	left->right = NULL;
	//printf("in fill_LEFTast, beg = %d, end = %d\n", left->beg, left->end);
	return (left);
}

t_ast		*fill_rightast(t_ast *parent)
{
	t_ast	*right = NULL;

	if (!(right = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	right->parent = parent;
	right->split = 0;
	right->cmd_ret = 0;
	right->redirs = NULL;
	right->beg = parent->split + 3;
	right->end = parent->end;
	right->left = NULL;
	right->right = NULL;
	//printf("in fill_RIGHTast, beg = %d, end = %d\n", right->beg, right->end);
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
	head->cmd_ret = 0;
	head->redirs = NULL;
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
			while (shell->tok[i] == TK_SPACE || shell->tok[i] == TK_NEWLINE) //decide later if NEWLINE, TAB, or anything else should be skipped
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
		return (0);
	else if (!(ast->left) && !(ast->right))
	{
		if ((ret = is_redirect(shell, ast, ast->beg, ast->end)) != -1)
		{
			shell->redir_error = 0;
			fill_redirs(shell, ast, ast->beg, ret);
			shell->s_in = dup(0);
			shell->s_out = dup(1);
			shell->s_err = dup(2);
			implement_redirs(shell, ast);
			printf("about to free redirs\n");
			free_redirs(ast->redirs);
		}
		else
		{	
			create_arg_table(shell, ast->beg, ast->end);
			ast_execute(shell, ast);
		}
		if (shell->args)
			free_table(shell->args);
		//printf("DEBUG 4, ret = %d\n", ret);
	//	ret = ast->cmd_ret;
	//	printf("about to free ast command\n");
	//	free_ast_elem(ast);
		if (ast->cmd_ret == 0 || ast->cmd_ret == -1)
		{
		//	printf("DEBUG 5\n");
		//	printf("RETURNING 0 after command execution\n");
			return (ast->cmd_ret);
		}	
		else if (ast->cmd_ret < 0)
		{
			printf("ERROR: cmd->cmd_ret = %d when cmd = \n", ast->cmd_ret);
			return (-1);
		}
	}
	else if (ast)
	{
		op = shell->tok[ast->split];
		if (op == TK_AND_IF)
		{
			//printf("and if located while in %s\nSENDING left : %s to ast_evaluate\n", ast->arg, ast->left->arg);
			v1 = ast_evaluate(ast->left, shell);
			if (v1 != 0)
			{
	//			free_ast_elem(ast);
	//			printf("about to free ast node after handling token: %d\n", op);
				return (-1);
			}
			else if (v1 == 0)
			{
			//	printf("left branch of ANDIF returned 0\n");
				v2 = ast_evaluate(ast->right, shell);
	//			printf("about to free ast node after handling token: %d\n", op);
	//			free_ast_elem(ast);
				if (v2 == 0)
					return (0);
				else
					return (-1);
			}
		}
		else if (op == TK_OR_IF)
		{
		//	printf("ORIF found at : %s\n", ast->arg);
			v1 = ast_evaluate(ast->left, shell);
			if (v1 == 0)
			{
	//			printf("about to free ast node after handling token: %d\n", op);
	//			free_ast_elem(ast);
				return (v1);
			}
			else
			{
		//		printf("left branch of ORIF did not return 0, v1 = %d\n, evaluate right branch\n", v1);
				v2 = ast_evaluate(ast->right, shell);
	//			printf("about to free ast node after handling token: %d\n", op);
	//			free_ast_elem(ast);
				if (v2 == 0)
				{
		//			printf("right side of OR_IF RETURNING 0, v2 = %d\n", v2);
					return (0);
				}
				else
				{
		//			printf("right side of OR_IF RETURNING v2 = %d\n", v2);
					return (-1);
				}
			}
		}
		else if (op == TK_PIPE)
		{
			return (evaluate_pipe_node(shell, ast));
	//		printf("about to free ast node after handling token: %d\n", op);
	//		free_ast_elem(ast);
		}
		else if (op == TK_SEMI)
		{
			v1 = ast_evaluate(ast->left, shell);
			v2 = ast_evaluate(ast->right, shell);
	//		printf("about to free ast node after handling token: %d\n", op);
	//		free_ast_elem(ast);
			return (0);
		}
		//printf("LEAVING IF clause 3\n");
	}
	//printf("end of entire ast_evaluate function, tmp = %s\nv1 = %d\nv2 = %d\n", ast->arg, v1, v2);
	return (-10);
}
/*
static void		print_leaf_nodes(t_ast *head)
{
	t_ast	*tmp = head;
	static int	order = 1;
	static int	split_by = 0;
	t_ast	*parent = NULL;

	if (!tmp)
		return ;
	if (!(tmp->left) && !(tmp->right))
	{
		printf("EXECUTE CMD %d with depth %d: %s\n", order++, tmp->depth, tmp->arg);
		(tmp->parent->split_by == TK_SEMI) ? printf("process with semi\n") :
		(tmp->parent->split_by == TK_AND_IF) ? printf("process with AND_IF\n") :
		(tmp->parent->split_by == TK_OR_IF) ? printf("process with OR_IF\n") :
		(tmp->parent->split_by == TK_PIPE) ? printf("process with PIPE\n") :
		printf("\n");
		return ;
	}
	if (tmp->left)
		print_leaf_nodes(tmp->left);
	if (tmp->split_by == TK_AND_IF)
		printf("verify all previous commands returned 0 before continuing, else STOP\nAlso verify all following commands NOT split by SEMI execute successfully or else stop");
	else if (tmp->split_by == TK_OR_IF)
		printf("if previous command return value != 0, execute other OR_IF commands until success, else stop\n");		
	if (tmp->right)
		print_leaf_nodes(tmp->right);
}
*/
