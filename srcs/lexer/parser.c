/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:24:23 by arohani           #+#    #+#             */
/*   Updated: 2018/06/07 15:32:53 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

static void		ast_loop_pipe(t_ast *head)
{
	int		i = 0;
	t_ast	*tmp = head;
	char	*str = tmp->arg;
	static int	order = 1;

	while (tmp->tok[i] != -1)
	{
		if (tmp->tok[i] == TK_PIPE)
		{
			tmp->split_by = tmp->tok[i];
			//printf("filling left from ast_loop_pipe\n");
			tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
			i += 3;
			//while (tmp->tok[i] == TK_SPACE)
			//	i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != TK_END)
			{
				//printf("filling right from ast_loop_pipe with:\ntmp->arg = %s\n", tmp->arg);
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1]);
				//printf("\nrecursively calling ast_loop_PIPE\n");
				ast_loop_pipe(tmp->right);
				break ;
			}
			else
				tmp->right = NULL;
		}
		else
			i += 3;
		//while (tmp->tok[i] == TK_SPACE)	//skips spaces in token table to find proper starting point before recreating another token table later
		//	i += 3;
	}
}

static void		ast_loop_and_or(t_ast *head)
{
	int		i = 0;
	t_ast	*tmp = head;
	char	*str = tmp->arg;

	if (tmp && !(ft_strstr(tmp->arg, "&&") && !(ft_strstr(tmp->arg, "||"))))
		ast_loop_pipe(tmp);
	while (tmp->tok[i] != -1)
	{
		if (tmp->tok[i] == TK_AND_IF || tmp->tok[i] == TK_OR_IF)
		{
			tmp->split_by = tmp->tok[i];
			//printf("filling left from ast_loop_and_or\n");
			tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
			ast_loop_pipe(tmp->left);
			i += 3;
			//while (tmp->tok[i] == TK_SPACE)
			//	i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != TK_END)
			{
				//printf("filling right from ast_loop_and_or\n");
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1]);
				//printf("\nrecursively calling ast_loop_and_or\n");
				ast_loop_and_or(tmp->right);
				break ;
			}
			else
				tmp->right = NULL;
		}
		else
			i += 3;
		//while (tmp->tok[i] == TK_SPACE)	//skips spaces in token table to find proper starting point before recreating another token table later
		//	i += 3;
	}
//	if (!(tmp->left) && tmp->parent != NULL)
	//	ast_loop_pipe(tmp);
}

static void		ast_loop_semi(t_ast *head)
{
	int		i = 0;
	t_ast	*tmp = head;
	char	*str = tmp->arg;

	if (tmp && !(ft_strchr(tmp->arg, ';')))
		ast_loop_and_or(tmp);
	while (tmp->tok[i] != -1)
	{
		if (tmp->tok[i] == TK_SEMI)
		{
			//printf("filling left from ast_loop_semi\n");
			tmp->split_by = TK_SEMI;
			tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
			ast_loop_and_or(tmp->left);
			i += 3;
			//while (tmp->tok[i] == TK_SPACE)
			//	i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != 16)
			{
				//printf("filling right from ast_loop_semi sending: %s to fill_right\n", tmp->arg);
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1]);
				//printf("\nrecursively calling ast_loop_semi\n");
				if (tmp->right)
					ast_loop_semi(tmp->right);
				break ;
			}
			else
				tmp->right = NULL;
		}
		else
			i += 3;
		//while (tmp->tok[i] == TK_SPACE)	//skips spaces in token table to find proper starting point before recreating another token table later
		//	i += 3;
	}
	//if (!(tmp->left) && tmp->parent != NULL)	//so that first elements that were recursively filled don't add extra once branch is done
	//	ast_loop_and_or(tmp);
}

t_ast	    *get_ast(int **tab, char ***argv)
{
	char	*str = NULL;
	t_ast	*head;
	t_ast	*tmp;

	head = (*tab[0] && *tab[0] != 16) ? init_ast(argv) : NULL;
	tmp = head;
	ast_loop_semi(tmp);
	return (head);
}
