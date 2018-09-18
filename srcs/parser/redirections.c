/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:59:04 by arohani           #+#    #+#             */
/*   Updated: 2018/08/20 21:16:06 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "heredoc.h"
#include "builtins.h"

void		redir_error(t_shell *shell, char *filename, int new_fd)
{
	shell->redir_error = (new_fd < 0) ? 1 : 0;
	if (shell->redir_error == 1 && filename)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

static int	get_fd(t_shell *shell, t_redirs *node)
{
	t_redirs	*tmp;
	int			fd;
	char		*str;

	tmp = node;
	if (tmp->next_re >= 3 && shell->tok[tmp->next_re - 3] == TK_IO_NUMBER)
	{
		str = shell->line + shell->tok[tmp->next_re - 3 + 1];
		fd = is_fd(str, shell->tok[tmp->next_re - 3 + 2], shell);
	}
	else
		fd = (shell->tok[tmp->next_re] == TK_LESS ||
			shell->tok[tmp->next_re] == TK_LESSAND ||
			shell->tok[tmp->next_re] == TK_DLESS) ? 0 : 1;
	return (fd);
}

static void	analyze_redir_node(t_shell *shell, t_redirs *tmp, int fd)
{
	if (shell->tok[tmp->next_re] == TK_LESS)
		implement_less(shell, tmp, fd);
	else if (shell->tok[tmp->next_re] == TK_LESSAND)
		implement_lessand(shell, tmp, fd);
	else if (shell->tok[tmp->next_re] == TK_GREAT)
		implement_great(shell, tmp, fd);
	else if (shell->tok[tmp->next_re] == TK_GREATAND)
		implement_greatand(shell, tmp, fd);
	else if (shell->tok[tmp->next_re] == TK_DGREAT)
		implement_dgreat(shell, tmp, fd);
	else if (shell->tok[tmp->next_re] == TK_DLESS)
		tmp->new_fd = -1;
}

void		implement_redirs(t_shell *shell, t_ast *cmd)
{
	t_redirs	*tmp;
	int			fd;

	tmp = cmd->redirs;
	while (tmp->next && shell->redir_error != 1)
	{
		fd = get_fd(shell, tmp);
		if (shell->redir_error == 0)
		{
			analyze_redir_node(shell, tmp, fd);
			tmp = tmp->next;
		}
	}
	if (shell->last_id >= 0)
		implement_heredoc(cmd, shell->last_hd);
	if (shell->redir_error == 1)
		cmd->cmd_ret = -1;
}
