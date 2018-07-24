/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:20 by arohani           #+#    #+#             */
/*   Updated: 2018/07/23 18:46:20 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

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
	
	//printf("entered init_ast\n");
	if (!(head = (t_ast *)malloc(sizeof(t_ast))))
			return (NULL);	
	head->parent = NULL;
	head->split = 0;
	head->beg = 0;
	head->end = get_tk_end_pos(shell) - 3;
	//head->address = ft_strdup("P");
	//printf("tab[0] = %s\n", tab[0]);
	//head->arg = (argv) ? ft_strdup(argv) : NULL;
	//(head->arg) ? printf("ast initialized with arg = %s\n", head->arg) : printf("ast initialized with a NULL arg\n");
	//printf("head->arg initialised to : %s\n", head->arg);
	//head->tok = get_tokens(head->arg);
	//printf("initialised ast, with token table\n");
	//if (head->tok[0])
	//	printf("head->tok[0] = %d\n", head->tok[0]);
	head->left = NULL;
	head->right = NULL;	
	return (head);
}

void		create_arg_table(t_shell *shell, int beg, int end)
{
	int		i = beg;
	int		last = 0;
	char	*str = NULL;
	
	if ((end - beg) < 0)
	{
		shell->args = NULL;
		return ;
	}
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
			//printf("going to malloc for last = %d strings\n", last+1);
			//printf("trying to create table from start: %d, end: %d of :\n->%s<-\n", shell->tok[cmd->beg + 1], shell->tok[cmd->end + 1], shell->line);
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
					str = shell->line + shell->tok[i+1];
					//printf("before filling shell->args, str = %s\ni = %d\ntok[i] = %d\ntok[i+1] = %d\ntok[i+2] = %d\n", str, i, shell->tok[i], shell->tok[i+1], shell->tok[i+2]);
					shell->args[last++] = ft_strndup(str, shell->tok[i+2]);
					//printf("in shell->args table, args[%d] = %s\n", last - 1, shell->args[last-1]);
					i += 3;
				}
			//	printf("shell->args[%d] = %s\n", last - 1, shell->args[last - 1]);
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
	t_redirs	*tmp;

	if (ast == NULL)
	{
		//printf("error, AST is null, nothing to evaluate\n");
		return (0);
	}
	if (!(ast->left) && !(ast->right))
	{
		ast->cmd_ret = 0;
		ast->redirs = NULL;
		//printf("DEBUG 1 : GOING TO EXECUTE: %s, address = %s\n", ast->arg, ast->address);
		if ((ret = is_redirect(shell, ast, ast->beg, ast->end)))
		{
			//char *str = shell->line + shell->tok[ast->beg + 1];
			//while (*str != shell->line[shell->tok[ast->end - 3] + shell->tok[ast->end - 1]])
			//	ft_putchar(*str++);
			printf("filling redirs list\n");
			fill_redirs(shell, ast, ast->beg, ret);
			implement_redirs(shell, ast);
		}
		else
		{
			//char *str = shell->line + shell->tok[ast->beg + 1];
			//while (*str != shell->line[shell->tok[ast->end] + shell->tok[ast->end + 2]])
			//	ft_putchar(*str++);			
			create_arg_table(shell, ast->beg, ast->end);
			ast_execute(shell, ast, 0);
		}
		//printf("DEBUG 3, AFTER executing %s, cmd->ret = %d\n", ast->arg, ast->cmd_ret);
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
			printf("ERROR: cmd->cmd_ret = %d when cmd = \n", ast->cmd_ret);
			ft_print_table(shell->args);
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
			//	printf("v1 = %d\n, returning -1\n", v1);
				//free_ast(ast->right);
				return (-1);
			}
			else if (v1 == 0)
			{
			//	printf("left branch of ANDIF returned 0\n");
				v2 = ast_evaluate(ast->right, shell);
				if (v2 == 0)
				{
			//		printf("right branch RETURNING of ANDIF returned v2 = 0\n");
					return (0);
				}
				else
				{
			//		printf("right branch of ANDIF RETURNING v2 = %d\n", v2);
					return (-1);
				}
			}
		}
		else if (op == TK_OR_IF)
		{
		//	printf("ORIF found at : %s\n", ast->arg);
		//	printf("going to calculate v1 using %s\n", ast->left->arg);
			v1 = ast_evaluate(ast->left, shell);
			if (v1 == 0)
			{
			//	printf("ENTERED v1 = 0 clause of left side of OR_IF, should return %d\n", v1);
		//		printf("left branch of ORIF RETURNING 0\n");
			//	free_ast(ast->right);
				return (v1);
			}
			else
			{
		//		printf("left branch of ORIF did not return 0, v1 = %d\n, evaluate right branch\n", v1);
				v2 = ast_evaluate(ast->right, shell);
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
