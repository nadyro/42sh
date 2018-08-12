/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 15:11:52 by arohani           #+#    #+#             */
/*   Updated: 2018/08/12 16:22:16 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

int			get_tk_end_pos(t_shell *shell)
{
	int		last;

	last = 0;
	while (shell->tok[last] != -1 && shell->tok[last] != TK_END)
	{
		if (shell->tok[last] != TK_END && shell->tok[last] != -1)
			last += 3;
		if (shell->tok[last] == TK_END)
		{
			if (shell->tok[last - 3] == TK_NEWLINE)
			{
				shell->tok[last - 3] = TK_END;
				return (last - 3);
			}
			return (last);
		}
	}
	ft_putstr_fd("Error : No end token found\n", 2);
	return (-1);
}

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

t_ast		*get_ast(t_shell *shell)
{
	t_ast	*head;
	t_ast	*tmp;

	if (shell->line[ft_strlen(shell->line) - 1] == '\n')
		shell->line[ft_strlen(shell->line) - 1] = '\0';
	head = init_ast(shell);
	tmp = head;
	if (ft_strchr(shell->line, ';'))
		ast_loop_semi(tmp, shell, 0);
	else if (ft_strstr(shell->line, "&&") || ft_strstr(shell->line, "||"))
		ast_loop_and_or(tmp, shell, 0);
	else if (ft_strchr(shell->line, '|'))
		ast_loop_pipe(tmp, shell, 0);
	return (head);
}
