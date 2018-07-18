/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:20 by arohani           #+#    #+#             */
/*   Updated: 2018/07/18 14:56:55 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

void		free_ast(t_ast *ast)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*tmp;

	left = NULL;
	right = NULL;
	tmp = ast;
	if (!tmp)
		return ;
	else
	{
		left = tmp->left;
		right = tmp->right;
		free(tmp->tok);
		free(tmp->address);
		free(tmp->arg);
		free(tmp);
		free_ast(left);
		free_ast(right);
	}
}

t_ast		*fill_leftast(t_ast *parent, int size)
{
	t_ast	*left = NULL;

	if (!(left = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	left->parent = parent;
	left->depth = parent->depth + 1;
	//left->address = ft_strjoin(left->parent->address, "L");
	left->arg = ft_strndup(parent->arg, size);	//size indicates position of operator, here we duplicate up to, not including, the operator
	left->split_by = 0;
	left->tok = get_tokens(left->arg);
	left->left = NULL;
	left->right = NULL;
	//printf("in fill_leftast, left->arg = %s\naddress = %s\nparent operator = %d\n", left->arg, left->address, parent->split_by);
	return (left);
}

t_ast		*fill_rightast(t_ast *parent, int start, int size)
{
	t_ast	*right = NULL;
	char	*str;

	if (!(right = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	right->parent = parent;
	str = parent->arg + start;
	right->depth = parent->depth + 1;
	//right->address = ft_strjoin(right->parent->address, "R");
	right->arg = ft_strndup(str, size);
	right->split_by = 0;
	right->tok = get_tokens(right->arg);
	right->left = NULL;
	right->right = NULL;
	//printf("in fill_rightast, right->arg = %s\naddress = %s\nparent operator = %d\n", right->arg, right->address, parent->split_by);
	return (right);
}

t_ast		*init_ast(char **argv)
{
	t_ast	*head;
	
	//printf("entered init_ast\n");
	if (!(head = (t_ast *)malloc(sizeof(t_ast))))
			return (NULL);	
	head->parent = NULL;
	head->split_by = 0;
	head->address = ft_strdup("P");
	head->depth = 0;
	//printf("tab[0] = %s\n", tab[0]);
	head->arg = (*argv) ? ft_strdup(*argv) : NULL;
	//printf("head->arg initialised to : %s\n", head->arg);
	head->tok = get_tokens(head->arg);
	//printf("initialised ast, with token table\n");
	//if (head->tok[0])
	//	printf("head->tok[0] = %d\n", head->tok[0]);
	head->left = NULL;
	head->right = NULL;	
	return (head);
}

void		create_arg_table(t_ast *cmd, t_shell *shell)
{
	int		i = 0;
	int		last = 0;
	char	*str = NULL;
	
	if (!(cmd->arg))
	{
		shell->args = NULL;
		return ;
	}
	else
	{
		while (cmd->tok[i] != -1 && cmd->tok[i] != TK_END)
		{
			while (cmd->tok[i] == TK_SPACE) //decide later if NEWLINE, TAB, or anything else should be skipped
				i += 3;
			if (cmd->tok[i] != -1 && cmd->tok[i] != TK_SPACE)
				last++;
			if (cmd->tok[i] != -1)
				i += 3;
		}
		if (last)
		{
			//printf("going to malloc for last = %d strings from %s\n", last+1, cmd->arg);
			if (!(shell->args = (char **)malloc(sizeof(char *) * (last + 1))))
				return ;
			shell->args[last] = 0;
			last = 0;
			i = 0;
			while (cmd->tok[i] != -1 && cmd->tok[i] != TK_END)
			{
				while (cmd->tok[i] == SPACE)
					i += 3;
				if (cmd->tok[i] != -1 && cmd->tok[i] != SPACE)
				{
					str = cmd->arg + cmd->tok[i+1];
					//printf("before filling shell->args, str = %s\ni = %d\ntok[i] = %d\ntok[i+1] = %d\ntok[i+2] = %d\n", str, i, cmd->tok[i], cmd->tok[i+1], cmd->tok[i+2]);
					shell->args[last++] = ft_strndup(str, cmd->tok[i+2]);
					//printf("in shell->args table, args[%d] = %s\n", last - 1, shell->args[last-1]);
					i += 3;
				}
			}
		}
	}
	//printf("printing arg table if exists\n");
	//if (shell->args && shell->args[0])
	//	ft_print_table(shell->args);
}

int         ast_evaluate(t_ast *ast, t_shell *shell)
{
	int		op;
	//int		ret = 0;
	int		v1 = 0;
	int		v2 = 0;

	//printf("ENTERED ast_evaluate with ast = %s\n", ast->arg);
	if (ast == NULL)
	{
		//printf("error, AST is null, nothing to evaluate\n");
		return (-1);
	}
/*	printf("ast = %s\n", ast->arg);
	if (ast->left)
		printf("left = %s\n", ast->left->arg);
	if (ast->right)
		printf("right = %s\n", ast->right->arg); 
*/	if (!(ast->left) && !(ast->right))
	{
		//printf("DEBUG 1 : GOING TO EXECUTE: %s, address = %s\n", ast->arg, ast->address);
		create_arg_table(ast, shell);
		//printf("DEBUG 2\n");
		ast_execute(shell, ast);
		//printf("DEBUG 3, address of %s : %s\n", ast->arg, ast->address);
		if (shell->args)
			free_table(shell->args);
		//printf("DEBUG 4, ret = %d\n", ret);
		if (ast->cmd_ret == 0 || ast->cmd_ret == -1)
		{
		//	printf("DEBUG 5\n");
		//	printf("RETURNING 0 after command execution\n");
		//	printf("DEBUG 6\n");
			return (ast->cmd_ret);
		}	
		else if (ast->cmd_ret < 0)
		{
		//	printf("DEBUG 7\n");
			printf("ERROR: cmd->cmd_ret = %d when cmd = %s\n", ast->cmd_ret, ast->arg);
			return (-1);
		}
		//else
		//	printf("error in leaf node execution of %s at depth of %d, v1 = %d, v2 = %d\nfirst char of arg = %c\n", ast->arg, ast->depth, v1, v2, ast->arg[0]);
		//printf("DEBUG 8\n");	
	}
	else if (ast)
	{
		op = ast->split_by;
		if (op == TK_AND_IF)
		{
			//printf("and if located while in %s\nSENDING left : %s to ast_evaluate\n", ast->arg, ast->left->arg);
			v1 = ast_evaluate(ast->left, shell);
			if (v1 != 0)
			{
			//	printf("v1 = %d\n, returning -1\n", v1);
				//free_ast(ast->right);
				return (-1);
			}
			else if (v1 == 0)
			{
				//printf("left branch of ANDIF returned 0\n");
				v2 = ast_evaluate(ast->right, shell);
				if (v2 == 0)
				{
				//	printf("right branch RETURNING of ANDIF returned v2 = 0\n");
					return (0);
				}
				else
				{
				//	printf("right branch of ANDIF RETURNING v2 = %d\n", v2);
					return (-1);
				}
			}
		}
		else if (op == TK_OR_IF)
		{
			//printf("ORIF found at : %s\n", ast->arg);
			//printf("going to calculate v1 using %s\n", ast->left->arg);
			v1 = ast_evaluate(ast->left, shell);
			if (v1 == 0)
			{
			//	printf("ENTERED v1 = 0 clause of left side of OR_IF, should return %d\n", v1);
			//	printf("left branch of ORIF RETURNING 0\n");
			//	free_ast(ast->right);
				return (v1);
			}
			else
			{
			//	printf("left branch of ORIF did not return 0, v1 = %d\n, evaluate right branch\n", v1);
				v2 = ast_evaluate(ast->right, shell);
				if (v2 == 0)
				{
			//		printf("right side of OR_IF RETURNING 0, v2 = %d\n", v2);
					return (0);
				}
				else
				{
			//		printf("right side of OR_IF RETURNING v2 = %d\n", v2);
					return (-1);
				}
			}
		}
		else if (op == TK_PIPE)
		{
			//printf("PIPE found at : %s\n", ast->arg);
			//printf("use ft_pipe_execution\n");
			v1 = ast_evaluate(ast->left, shell);
			v2 =ast_evaluate(ast->right, shell);
			//printf("PIPE RETURNING 0\n");
			return (0);
		}
		else if (op == TK_SEMI)
		{
			//printf("SEMI found at %s\nevaluating left node\n", ast->arg);
			v1 = ast_evaluate(ast->left, shell);
			//printf("SEMI found at %s\nevaluating right node\n", ast->arg);
			v2 = ast_evaluate(ast->right, shell);
			//printf("SEMI COMPLETELY PROCESSED, v1 = %d\nv2 = %d\nRETURNING 0\n", v1, v2);
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
