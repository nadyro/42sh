/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:20 by arohani           #+#    #+#             */
/*   Updated: 2018/08/07 15:52:55 by arohani          ###   ########.fr       */
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
	
	if (!(head = (t_ast *)malloc(sizeof(t_ast))))
			return (NULL);	
	head->parent = NULL;
	head->split = 0;
	head->beg = 0;
	head->end = get_tk_end_pos(shell) - 3;
	//printf("in PARENT, beg = %d, end = %d\n", head->beg, head->end);
	head->left = NULL;
	head->right = NULL;	
	return (head);
}

void		create_arg_table(t_shell *shell, int beg, int end)
{
	int		i = beg;
	int		last = 0;
	
	if (end < beg)
	{
		//printf("end is less than big in create arg table, setting shell->args to NULL\n");
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
					//str = shell->line + shell->tok[i+1];			remove for thibaud feature
					//shell->args[last++] = ft_strndup(str, shell->tok[i+2]);	remove for thibaud feature
					shell->args[last++] = token2str(&shell->tok[i], shell->line, shell->envv);
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
		if ((ret = is_redirect(shell, ast, ast->beg, ast->end)) != -1)
		{
			shell->redir_error = 0;
			fill_redirs(shell, ast, ast->beg, ret);
			shell->s_in = dup(0);
			shell->s_out = dup(1);
			shell->s_err = dup(2);
			implement_redirs(shell, ast);
			free_redirs(ast->redirs);
		}
		else
		{	
			create_arg_table(shell, ast->beg, ast->end);
			ast_execute(shell, ast);
		}
		if (shell->args)
			free_table(shell->args);
		if (ast->cmd_ret == 0 || ast->cmd_ret == -1)
		{
			return (ast->cmd_ret);
		}	
		else if (ast->cmd_ret < 0)
		{
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
				return (ast->cmd_ret = -1);
			else if (v1 == 0)
			{
			//	printf("left branch of ANDIF returned 0\n");
				v2 = ast_evaluate(ast->right, shell);
				if (v2 == 0)
					return (ast->cmd_ret = 0);
				else
					return (ast->cmd_ret = -1);
			}
		}
		else if (op == TK_OR_IF)
		{
		//	printf("ORIF found at : %s\n", ast->arg);
			v1 = ast_evaluate(ast->left, shell);
			if (v1 == 0)
				return (ast->cmd_ret = v1);
			else
			{
		//		printf("left branch of ORIF did not return 0, v1 = %d\n, evaluate right branch\n", v1);
				v2 = ast_evaluate(ast->right, shell);
				if (v2 == 0)
				{
		//			printf("right side of OR_IF RETURNING 0, v2 = %d\n", v2);
					return (ast->cmd_ret = 0);
				}
				else
				{
		//			printf("right side of OR_IF RETURNING v2 = %d\n", v2);
					return (ast->cmd_ret = -1);
				}
			}
		}
		else if (op == TK_PIPE)
		{
			return (evaluate_pipe_node(shell, ast));
		}
		else if (op == TK_SEMI)
		{
			ft_putstr_fd("about to evaluate left node of semi\n", 1);
			v1 = ast_evaluate(ast->left, shell);
			ft_putstr_fd("just executed left node, about to evaluate right node\n", 1);
			v2 = ast_evaluate(ast->right, shell);
			ft_putstr_fd("finished evaluating right node, returning from ast_evaluate\n", 1);
			return (0);
		}
		//printf("LEAVING IF clause 3\n");
	}
	ft_putstr_fd("finished evaluating entire ast, returning to ast_loop\n", 1);
	return (-10);
}
