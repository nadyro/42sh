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
#include <stdio.h>

static int 		get_tk_end_pos(t_ast *tmp)
{
	int 	last = 0;

	while (tmp && tmp->tok[last] != -1)
	{
		if (tmp->tok[last] != TK_END && tmp->tok[last] != -1)
			last += 3;
		if (tmp->tok[last] == TK_END)
			return (last);
	}
	ft_putstr_fd("Error : No end token found\n", 2);
	return (-1);
}

static void		ast_loop_pipe(t_ast *head)
{
	int		i;
	int 	op;
	t_ast	*tmp = head;

	if ((i = get_tk_end_pos(tmp)) < 1)
		return ;
	while (i >= 0)
	{
		if (tmp->tok[i] == TK_PIPE)
		{
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
				tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
				if (tmp->left)
					ast_loop_pipe(tmp->left);
				break ;
			}
		}
		else
			i -= 3;
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
			tmp->split_by = tmp->tok[i];
			op = i;
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] != TK_END && tmp->tok[i] != -1)
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1]);
			if (tmp->right && ft_strchr(tmp->right->arg, '|'))
				ast_loop_pipe(tmp->right);
			i = op;
			if (i > 0)
			{
				tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
				if (tmp->left)
					ast_loop_and_or(tmp->left);
				break ;
			}
		}
		else
			i -= 3;
	}
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
			tmp->split_by = TK_SEMI;
			op = i;
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] != TK_END && tmp->tok[i] != -1)
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1]);
			if (tmp->right && (ft_strstr(tmp->right->arg, "&&") || ft_strstr(tmp->right->arg, "||")))
				ast_loop_and_or(tmp->right);
			else if (tmp->right && ft_strchr(tmp->right->arg, '|'))
				ast_loop_pipe(tmp->right);	
			i = op;
			if (i > 0)
			{
				tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
				if (tmp->left)
					ast_loop_semi(tmp->left);
				break ;
			}
		}
		else
			i -= 3;
	}
}

t_ast	    *get_ast(char *argv)
{
	t_ast	*head;
	t_ast	*tmp;

	if (argv[ft_strlen(argv) - 1] == '\n')	//replaces '\n' from line editing with '\0'
		argv[ft_strlen(argv) - 1] = '\0';
	head = init_ast(argv);
	tmp = head;
	if (ft_strchr(tmp->arg, ';'))
		ast_loop_semi(tmp);
	else if (ft_strstr(tmp->arg, "&&") || ft_strstr(tmp->arg, "||"))
		ast_loop_and_or(tmp);
	else if (ft_strchr(tmp->arg, '|'))
		ast_loop_pipe(tmp);
	return (head);
}
