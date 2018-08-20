/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_implementation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 13:31:39 by arohani           #+#    #+#             */
/*   Updated: 2018/08/20 14:23:10 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "heredoc.h"
#include "builtins.h"

void	implement_great(t_shell *shell, t_redirs *node, int fd)
{
	char		*str;

	str = shell->line + shell->tok[node->next_re + 3 + 1];
	if ((node->new_fd = is_fd(str, shell->tok[node->next_re + 5], shell)) > 0)
		dup2(node->new_fd, fd);
	else if (node->new_fd == 0)
	{
		str = ft_strndup(shell->line + shell->tok[node->next->beg + 1],
				shell->tok[node->next->beg + 2]);
		node->new_fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		redir_error(shell, str, node->new_fd);
		ft_strdel(&str);
		if (shell->redir_error == 1)
			return ;
		else
			dup2(node->new_fd, fd);
	}
}

void	implement_dgreat(t_shell *shell, t_redirs *node, int fd)
{
	char		*str;

	str = shell->line + shell->tok[node->next_re + 3 + 1];
	if ((node->new_fd = is_fd(str, shell->tok[node->next_re + 5], shell)) > 0)
		dup2(node->new_fd, fd);
	else if (node->new_fd == 0)
	{
		str = ft_strndup(shell->line + shell->tok[node->next->beg + 1],
				shell->tok[node->next->beg + 2]);
		node->new_fd = open(str, O_CREAT | O_APPEND | O_WRONLY, 0666);
		redir_error(shell, str, node->new_fd);
		ft_strdel(&str);
		if (shell->redir_error == 1)
			return ;
		else
			dup2(node->new_fd, fd);
	}
}

void	implement_greatand(t_shell *shell, t_redirs *node, int fd)
{
	char		*str;

	str = shell->line + shell->tok[node->next_re + 3 + 1];
	if (shell->line[shell->tok[node->next_re + 3 + 1]] == '-')
	{
		close(fd);
		return ;
	}
	if ((node->new_fd = is_fd(str, shell->tok[node->next_re + 5], shell)) > 0)
		dup2(node->new_fd, fd);
	else if (node->new_fd == 0)
	{
		str = ft_strndup(shell->line + shell->tok[node->next->beg + 1],
				shell->tok[node->next->beg + 2]);
		node->new_fd = open(str, O_CREAT | O_APPEND | O_WRONLY, 0666);
		redir_error(shell, str, node->new_fd);
		ft_strdel(&str);
		if (shell->redir_error == 1)
			return ;
		else
			dup2(node->new_fd, fd);
	}
}

void	implement_less(t_shell *shell, t_redirs *node, int fd)
{
	char		*str;

	str = shell->line + shell->tok[node->next_re + 3 + 1];
	if ((node->new_fd = is_fd(str, shell->tok[node->next_re + 5], shell)) > 0)
		dup2(node->new_fd, fd);
	else if (node->new_fd == 0)
	{
		str = ft_strndup(shell->line + shell->tok[node->next->beg + 1],
				shell->tok[node->next->beg + 2]);
		node->new_fd = open(str, O_RDONLY);
		redir_error(shell, str, node->new_fd);
		ft_strdel(&str);
		if (shell->redir_error == 1)
			return ;
		else
			dup2(node->new_fd, fd);
	}
}

void	implement_lessand(t_shell *shell, t_redirs *node, int fd)
{
	char		*str;

	str = shell->line + shell->tok[node->next_re + 3 + 1];
	if (shell->line[shell->tok[node->next_re + 3 + 1]] == '-')
	{
		close(fd);
		return ;
	}
	if ((node->new_fd = is_fd(str, shell->tok[node->next_re + 5], shell)) > 0)
		dup2(node->new_fd, fd);
	else if (node->new_fd == 0)
	{
		str = ft_strndup(shell->line + shell->tok[node->next->beg + 1],
				shell->tok[node->next->beg + 2]);
		node->new_fd = open(str, O_RDONLY);
		redir_error(shell, str, node->new_fd);
		ft_strdel(&str);
		if (shell->redir_error == 1)
			return ;
		else
			dup2(node->new_fd, fd);
	}
}
