/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:20 by arohani           #+#    #+#             */
/*   Updated: 2018/06/08 18:42:21 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

t_ast		*fill_leftast(t_ast *parent, int size)
{
	t_ast	*left = NULL;

	if (!(left = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	left->parent = parent;
	left->depth = parent->depth + 1;
	left->address = ft_strjoin(left->parent->address, "L");
	left->arg = ft_strndup(parent->arg, size);
	left->split_by = 0;
	left->tok = get_tokens(left->arg);
	left->left = NULL;
	left->right = NULL;
	printf("in fill_leftast, left->arg = %s\nleft->address = %s\nparent operator = %d\n", left->arg, left->address, parent->split_by);
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
	right->address = ft_strjoin(right->parent->address, "R");
	right->arg = ft_strndup(str, size);
	right->split_by = 0;
	right->tok = get_tokens(right->arg);
	right->left = NULL;
	right->right = NULL;
	printf("in fill_rightast, right->arg = %s\nright->address = %s\nparent operator = %d\n", right->arg, right->address, parent->split_by);
	return (right);
}

t_ast		*init_ast(char ***argv)
{
	t_ast	*head;
	char	**tab = *argv;
	
	printf("entered init_ast\n");
	if (!(head = (t_ast *)malloc(sizeof(t_ast))))
			return (NULL);	
	head->parent = NULL;
	head->split_by = 0;
	head->address = ft_strdup("P");
	head->depth = 0;
	printf("tab[0] = %s\n", tab[0]);
	head->arg = (tab[1]) ? ft_strndup(tab[1], ft_strlen(tab[1])) : NULL;
	printf("head->arg initialised to : %s\n", head->arg);
	head->tok = get_tokens(head->arg);
	printf("initialised ast, with token table\n");
	if (head->tok[0])
		printf("head->tok[0] = %d\n", head->tok[0]);
	head->left = NULL;
	head->right = NULL;	
	return (head);
}

int         ast_evaluate(t_ast *ast)
{
	int		op;
	int		v1 = 0;
	int		v2 = 0;

	if (ast == NULL)
	{
		printf("ENTERED if clause 1\n");
		printf("error, AST is null, nothing to evaluate\n");
		return (-1);
	}
	if (!(ast->left) && !(ast->right))
	{
		printf("ENTERED if clause 2\n");
		printf("execute %s and do not take next command value into account\n", ast->arg);
		if (ast->arg[0] == 't')
			return (0);
		else if (ast->arg[0] == 'f')
			return (-1);
		else
			printf("error in leaf node execution of %s at depth of %d, v1 = %d, v2 = %d\nfirst char of arg = %c\n", ast->arg, ast->depth, v1, v2, ast->arg[0]);
	}
	else if (ast)
	{
		printf("ENTERED if clause 3\n");
		op = ast->split_by;
		if (op == TK_AND_IF)
		{
			v1 = ast_evaluate(ast->left);
			printf("in ANDIF, after evaluating left, left = %d\n", v1);
			if (v1 == 0)
			{
				printf("left branch of ANDIF returned 0\n");
				v2 = ast_evaluate(ast->right);
				if (v2 == 0)
				{
					printf("right branch returned of ANDIF returned 0\n");
					return (0);
				}
				else
				{
					printf("right branch of ANDIF returned %d\n", v2);
					return (-1);
				}
			}
			else
				return (-1);
		}
		else if (op == TK_OR_IF)
		{
			printf("ORIF found at : %s\n", ast->arg);
			printf("going to calculate v1 using %s\n", ast->left->arg);
			v1 = ast_evaluate(ast->left);
			if (v1 == 0)
			{
				printf("ENTERED v1 == 0 clause of left side of OR_IF, should return %d\n", v1);
				printf("left branch of ORIF returned 0\n");
				return v1;
			}
			else
			{
				printf("left branch of ORIF did not return 0, v1 = %d\n, evaluate right branch\n", v1);
				v2 = ast_evaluate(ast->right);
				if (v2 == 0)
				{
					printf("right side of OR_IF returned 0, v2 = %d\n", v2);
					return (0);
				}
				else
				{
					printf("right side of OR_IF did NOT return 0, returning v2 = %d\n", v2);
					return (-1);
				}
			}
		}
		else if (op == TK_PIPE)
		{
			printf("PIPE found at : %s\n", ast->arg);
			printf("use ft_pipe_execution\n");
			v1 = ast_evaluate(ast->left);
			v2 =ast_evaluate(ast->right);
			return (0);
		}
		else if (op == TK_SEMI)
		{
			printf("SEMI found at : %s\n", ast->arg);
			v1 = ast_evaluate(ast->left);
			v2 = ast_evaluate(ast->right);
			return (0);
		}
		printf("LEAVING IF clause 3\n");
	}
	printf("end of entire ast_evaluate function, tmp = %s\nv1 = %d\nv2 = %d\n", ast->arg, v1, v2);
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
