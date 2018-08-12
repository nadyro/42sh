/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 15:18:03 by arohani           #+#    #+#             */
/*   Updated: 2018/08/12 15:21:23 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

void			free_redirs(t_redirs *list)
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
	t_ast	*tmp;

	tmp = head;
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
