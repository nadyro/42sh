/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 13:42:15 by arohani           #+#    #+#             */
/*   Updated: 2018/08/16 19:14:48 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "heredoc.h"
#include "builtins.h"

static void	args_from_redirs(t_shell *shell, int beg)
{
	int		count;

	count = 0;
	while (shell->tok[beg] != TK_END)
	{
		if (shell->tok[beg] == TK_CMD || shell->tok[beg] == TK_WORD)
			count++;
		beg += 3;
	}
	if (count > 0)
	{
		if (!(shell->args = (char **)malloc(sizeof(char *) * (count + 1))))
			return ;
		shell->args[count--] = 0;
		while (beg >= 0)
		{
			if (shell->tok[beg] == TK_CMD || shell->tok[beg] == TK_WORD)
			{
				shell->args[count--] =
					token2str(&shell->tok[beg], shell->line, shell->envv);
			}
			beg -= 3;
		}
	}
}

static void	handle_prefix_syntax(t_shell *shell, t_ast *cmd)
{
	t_redirs	*tmp;

	tmp = cmd->redirs;
	if (tmp->next && (tmp->next->beg + 3) <= tmp->next->end)
	{
		tmp->beg = tmp->next->beg + 3;
		tmp->end = tmp->next->end;
		tmp->next->end = tmp->next->beg;
		args_from_redirs(shell, cmd->beg);
	}
	else
		shell->args = NULL;
}

void		shell_args_from_redirs(t_shell *shell, t_ast *cmd)
{
	t_redirs	*tmp;
	int			beg;

	tmp = cmd->redirs;
	beg = tmp->beg;
	if (tmp->beg == tmp->next_re)
	{
		handle_prefix_syntax(shell, cmd);
		return ;
	}
	while (beg <= tmp->end)
	{
		if (shell->tok[beg] == TK_IO_NUMBER)
		{
			tmp->ionum = beg;
			args_from_redirs(shell, cmd->beg);
			return ;
		}
		beg += 3;
	}
	args_from_redirs(shell, cmd->beg);
}

static void	fill_arg_table(t_shell *shell, int last, int beg, int end)
{
	if (last)
	{
		if (!(shell->args = (char **)malloc(sizeof(char *) * (last + 1))))
			return ;
		shell->args[last] = 0;
		last = 0;
		while (beg <= end)
		{
			while (shell->tok[beg] == TK_SPACE || shell->tok[beg] == TK_NEWLINE)
				beg += 3;
			if (shell->tok[beg] != TK_SPACE && shell->tok[beg] != TK_NEWLINE
					&& shell->tok[beg] != TK_END)
			{
				shell->args[last++] =
					token2str(&shell->tok[beg], shell->line, shell->envv);
				beg += 3;
			}
		}
	}
}

void		create_arg_table(t_shell *shell, int beg, int end)
{
	int		i;
	int		last;

	i = beg;
	last = 0;
	if (end < beg)
		shell->args = NULL;
	else
	{
		while (i <= end)
		{
			while (shell->tok[i] == TK_SPACE || shell->tok[i] == TK_NEWLINE)
				i += 3;
			if (shell->tok[i] != TK_END && shell->tok[i] != TK_SPACE
					&& shell->tok[i] != TK_NEWLINE)
				last++;
			if (shell->tok[i] != TK_END)
				i += 3;
		}
		fill_arg_table(shell, last, beg, end);
	}
}
