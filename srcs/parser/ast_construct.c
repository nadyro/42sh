/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 15:11:52 by arohani           #+#    #+#             */
/*   Updated: 2018/08/12 15:16:41 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

t_ast		*fill_leftast(t_ast *parent)
{
	t_ast	*left;

	if (!(left = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	left->parent = parent;
	left->split = 0;
	left->beg = parent->beg;
	left->end = parent->split - 3;
	left->left = NULL;
	left->right = NULL;
	return (left);
}

t_ast		*fill_rightast(t_ast *parent)
{
	t_ast	*right;

	if (!(right = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	right->parent = parent;
	right->split = 0;
	right->beg = parent->split + 3;
	right->end = parent->end;
	right->left = NULL;
	right->right = NULL;
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
	head->left = NULL;
	head->right = NULL;
	return (head);
}
