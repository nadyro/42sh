/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:23 by arohani           #+#    #+#             */
/*   Updated: 2018/06/26 15:18:04 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

static int 		get_tk_end_pos(t_ast *tmp)
{
	int 	last = 0;

	while (tmp->tok[last] != -1)
	{
		if (tmp->tok[last] != TK_END && tmp->tok[last] != -1)
			last += 3;
		if (tmp->tok[last] == TK_END)
			return (last);
	}
	return (-1);
}

static void		ast_loop_pipe(t_ast *head)
{
	int		i;
	int 	op;
	t_ast	*tmp = head;

	//if (tmp && !(ft_strchr(tmp->arg, '|')))
	//	return ;
	if ((i = get_tk_end_pos(tmp)) < 1)
		return ;
	while (i >= 0)
	{
		if (tmp->tok[i] == TK_PIPE)
		{
			//printf("filling left from ast_loop_semi\n");
			tmp->split_by = TK_PIPE;
			op = i;
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] != TK_END && tmp->tok[i] != -1)
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1]);
			i = op;
			if (i > 0)
			{
				//printf("filling right from ast_loop_semi sending: %s to fill_right\n", tmp->arg);
				tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
				//printf("\nrecursively calling ast_loop_semi\n");
				if (tmp->left)
					ast_loop_pipe(tmp->left);
				break ;
			}
			//else
			//	tmp->right = NULL;
		}
		else
			i -= 3;
		//while (tmp->tok[i] == TK_SPACE)	//skips spaces in token table to find proper starting point before recreating another token table later
		//	i += 3;
	}
}

static void		ast_loop_and_or(t_ast *head)
{
	int		i = 0;
	int 	op;
	t_ast	*tmp = head;

	if ((i = get_tk_end_pos(tmp)) < 1)
		return ;
	while (i >= 0)
	{
		if (tmp->tok[i] == TK_AND_IF || tmp->tok[i] == TK_OR_IF)
		{
			//printf("filling left from ast_loop_semi\n");
			tmp->split_by = tmp->tok[i];
			op = i;
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] != TK_END && tmp->tok[i] != -1)
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1]);
			ast_loop_pipe(tmp->right);
			i = op;
			if (i > 0)
			{
				//printf("filling right from ast_loop_semi sending: %s to fill_right\n", tmp->arg);
				tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
				//printf("\nrecursively calling ast_loop_semi\n");
				if (tmp->left)
					ast_loop_and_or(tmp->left);
				break ;
			}
			//else
			//	tmp->right = NULL;
		}
		else
			i -= 3;
	}
//	if (!(tmp->left) && tmp->parent != NULL)
	//	ast_loop_pipe(tmp);
}

static void		ast_loop_semi(t_ast *head)
{
	int		i;
	int 	op;
	t_ast	*tmp = head;

	if ((i = get_tk_end_pos(tmp)) < 1)
		return ;
	while (i >= 0)
	{
		if (tmp->tok[i] == TK_SEMI)
		{
			//printf("filling left from ast_loop_semi\n");
			tmp->split_by = TK_SEMI;
			op = i;
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] != TK_END && tmp->tok[i] != -1)
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1]);
			ast_loop_and_or(tmp->right);
			i = op;
			if (i > 0)
			{
				//printf("filling right from ast_loop_semi sending: %s to fill_right\n", tmp->arg);
				tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
				//printf("\nrecursively calling ast_loop_semi\n");
				if (tmp->left)
					ast_loop_semi(tmp->left);
				break ;
			}
			//else
			//	tmp->right = NULL;
		}
		else
			i -= 3;
		//while (tmp->tok[i] == TK_SPACE)	//skips spaces in token table to find proper starting point before recreating another token table later
		//	i += 3;
	}
	//if (!(tmp->left) && tmp && !(ft_strchr(tmp->arg, ';')))	//so that first elements that were recursively filled don't add extra once branch is done
	//	ast_loop_and_or(tmp);
}

t_ast	    *get_ast(char **argv)
{
	t_ast	*head;
	t_ast	*tmp;
	char	*chr = NULL;	//for removing '\n' from line

	if ((chr = ft_strchr(*argv, '\n')))	//replaces '\n' from line editing with '\0'
		*chr = '\0';
	head = init_ast(argv);
	tmp = head;
	ast_loop_semi(tmp);
	return (head);
}
