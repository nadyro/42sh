/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 12:59:04 by arohani           #+#    #+#             */
/*   Updated: 2018/08/11 18:21:00 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "heredoc.h"
#include "builtins.h"

static void		redir_error(t_shell *shell, char *filename, int new_fd)
{
	shell->redir_error = (new_fd < 0) ? 1 : 0;
	if (shell->redir_error == 1 && filename)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

static void		handle_prefix_syntax(t_shell *shell, t_ast *cmd)
{
	t_redirs	*tmp = NULL;

	tmp = cmd->redirs;
	if (tmp->next && (tmp->next->beg + 3) <= tmp->next->end)
	{
		tmp->beg = tmp->next->beg + 3;
		tmp->end = tmp->next->end;
		tmp->next->end = tmp->next->beg;
		create_arg_table(shell, tmp->beg, tmp->end);
	}
	else
		shell->args = NULL;
}

static void		shell_args_from_redirs(t_shell *shell, t_ast *cmd)
{
	t_redirs	*tmp = NULL;
	int 		beg;

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
			create_arg_table(shell, tmp->beg, tmp->ionum - 3);
			return ;
		}
		beg += 3;
	}
	create_arg_table(shell, tmp->beg, tmp->end);
}

static int 	get_fd(t_shell *shell, t_redirs *node)
{
	t_redirs	*tmp = node;
	int 		fd;
	char		*str;

	if (tmp->next_re >= 3 && shell->tok[tmp->next_re - 3] == TK_IO_NUMBER)
	{
		str = shell->line + shell->tok[tmp->next_re - 3 + 1];
		fd = is_fd(str, shell->tok[tmp->next_re - 3 + 2]);
	}
	else
		fd = (shell->tok[tmp->next_re] == TK_LESS ||
			shell->tok[tmp->next_re] == TK_LESSAND ||
			shell->tok[tmp->next_re] == TK_DLESS) ? 0 : 1;
	return (fd);
}

static void	implement_great(t_shell *shell, t_redirs *node, int fd)
{
	t_redirs	*tmp = node;
	char		*str;

	str = shell->line + shell->tok[tmp->next_re + 3 + 1];
	if ((tmp->new_fd = is_fd(str, shell->tok[tmp->next_re + 3 + 2])) > 0)
		dup2(tmp->new_fd, fd);
	else if (tmp->new_fd == 0)
	{
		str = ft_strndup(shell->line + shell->tok[tmp->next->beg + 1], shell->tok[tmp->next->beg + 2]);
		tmp->new_fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		redir_error(shell, str, tmp->new_fd);
		ft_strdel(&str);
		if (shell->redir_error == 1)
			return ;
		else
			dup2(tmp->new_fd, fd);
	}
}

static void	implement_dgreat(t_shell *shell, t_redirs *node, int fd)
{
	t_redirs	*tmp = node;
	char		*str;

	str = shell->line + shell->tok[tmp->next_re + 3 + 1];
	if ((tmp->new_fd = is_fd(str, shell->tok[tmp->next_re + 3 + 2])) > 0)
		dup2(tmp->new_fd, fd);
	else if (tmp->new_fd == 0)
	{
		str = ft_strndup(shell->line + shell->tok[tmp->next->beg + 1], shell->tok[tmp->next->beg + 2]);
		tmp->new_fd = open(str, O_CREAT | O_APPEND | O_WRONLY, 0666);
		redir_error(shell, str, tmp->new_fd);
		ft_strdel(&str);
		if (shell->redir_error == 1)
			return ;
		else
			dup2(tmp->new_fd, fd);
	}
}

static void	implement_greatand(t_shell *shell, t_redirs *node, int fd)
{
	t_redirs	*tmp = node;
	char		*str;

	str = shell->line + shell->tok[tmp->next_re + 3 + 1];
	if (shell->line[shell->tok[tmp->next_re + 3 + 1]] == '-')
	{
		close (fd);
		return ;
	}
	if ((tmp->new_fd = is_fd(str, shell->tok[tmp->next_re + 3 + 2])) > 0)
		dup2(tmp->new_fd, fd);
	else if (tmp->new_fd == 0)
	{
		str = ft_strndup(shell->line + shell->tok[tmp->next->beg + 1], shell->tok[tmp->next->beg + 2]);
		tmp->new_fd = open(str, O_CREAT | O_APPEND | O_WRONLY, 0666);
		redir_error(shell, str, tmp->new_fd);
		ft_strdel(&str);
		if (shell->redir_error == 1)
			return ;
		else
			dup2(tmp->new_fd, fd);
	}
}

static void	implement_less(t_shell *shell, t_redirs *node, int fd)
{
	t_redirs	*tmp = node;
	char		*str;

	str = shell->line + shell->tok[tmp->next_re + 3 + 1];
	if ((tmp->new_fd = is_fd(str, shell->tok[tmp->next_re + 3 + 2])) > 0)
		dup2(tmp->new_fd, fd);
	else if (tmp->new_fd == 0)
	{
		str = ft_strndup(shell->line + shell->tok[tmp->next->beg + 1], shell->tok[tmp->next->beg + 2]);
		tmp->new_fd = open(str, O_RDONLY);
		redir_error(shell, str, tmp->new_fd);
		ft_strdel(&str);
		if (shell->redir_error == 1)
			return ;
		else
			dup2(tmp->new_fd, fd);
	}
}

static void	implement_lessand(t_shell *shell, t_redirs *node, int fd)
{
	t_redirs	*tmp = node;
	char		*str;

	str = shell->line + shell->tok[tmp->next_re + 3 + 1];
	if (shell->line[shell->tok[tmp->next_re + 3 + 1]] == '-')
	{
		close (fd);
		return ;
	}
	if ((tmp->new_fd = is_fd(str, shell->tok[tmp->next_re + 3 + 2])) > 0)
		dup2(tmp->new_fd, fd);
	else if (tmp->new_fd == 0)
	{
		str = ft_strndup(shell->line + shell->tok[tmp->next->beg + 1], shell->tok[tmp->next->beg + 2]);
		tmp->new_fd = open(str, O_RDONLY);
		redir_error(shell, str, tmp->new_fd);
		ft_strdel(&str);
		if (shell->redir_error == 1)
			return ;
		else
			dup2(tmp->new_fd, fd);
	}
}


static void	implement_heredoc(t_ast *cmd, int id)
{
	char		*heredoc = NULL;

	if (cmd && id >= 0)
	{
		heredoc = heredoc_get(id);
		if (heredoc)
		{
			pipe(cmd->hfd);
			write(cmd->hfd[1], heredoc, ft_strlen(heredoc));
			close(cmd->hfd[1]);
			dup2(cmd->hfd[0], 0);
			close(cmd->hfd[0]);
		}
	}
}

static int	last_heredoc_id(t_shell *shell, t_redirs *node)
{
	t_redirs	*tmp;
	int			id;

	tmp = node;
	id = (shell->last_hd < 0) ? -1 : 0;
	while (tmp)
	{
		if (shell->tok[tmp->next_re] == TK_DLESS)
			id++;
		tmp = tmp->next;
	}
	shell->last_hd = (shell->last_hd < 0) ? id : shell->last_hd + id;
	return (id);
}

void 		implement_redirs(t_shell *shell, t_ast *cmd)
{
	t_redirs	*tmp = NULL;
	int 		fd;
	int			last_id;

	last_id = last_heredoc_id(shell, cmd->redirs);
	cmd->hd_check = (last_id >= 0) ? 1 : 0;
	shell_args_from_redirs(shell, cmd);
	tmp = cmd->redirs;
	while (tmp->next && shell->redir_error != 1)
	{	
		fd = get_fd(shell, tmp);
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
	//	else if (shell->tok[tmp->next_re] == TK_DLESS)
	//		implement_heredoc(tmp, counter++);
		tmp = tmp->next;
	}
	if (last_id >= 0)
		implement_heredoc(cmd, shell->last_hd);
	if (shell->redir_error == 1)
		cmd->cmd_ret = -1;
	ast_execute(shell, cmd);
}

void		fill_redirs(t_shell *shell, t_ast *ast, int beg, int redir)
{
	t_redirs	*tmp;
	int 		ret;

	if (!(tmp = (t_redirs *)malloc(sizeof(t_redirs))))
		return ;
	ast->redirs = tmp;
	tmp->beg = beg;
	tmp->end = (beg != redir) ? redir - 3 : redir;
	tmp->ionum = -1;
	tmp->next_re = redir;
	tmp->prev = NULL;
	tmp->next = NULL;
	while ((ret = is_redirect(shell, ast, redir + 3, ast->end)) != -1)
	{
		if (!(tmp->next = (t_redirs *)malloc(sizeof(t_redirs))))
			return ;
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->beg = redir + 3;
		tmp->end = ret - 3;
		tmp->ionum = -1;
		tmp->next_re = ret;
		redir = ret;
		tmp->next = NULL;
	}
}

int			is_redirect(t_shell *shell, t_ast *ast, int beg, int end)
{
	t_redirs		*tmp = NULL;

	while (beg <= end)
	{
		if (shell->tok[beg] == TK_GREAT || shell->tok[beg] == TK_DGREAT ||
			shell->tok[beg] == TK_GREATAND || shell->tok[beg] == TK_LESS ||
			shell->tok[beg] == TK_DLESS || shell->tok[beg] == TK_LESSAND)
			return (beg);
		beg += 3;
	}
	if ((tmp = ast->redirs))
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_redirs *)malloc(sizeof(t_redirs))))
			return (-1);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->beg = tmp->prev->next_re + 3;
		tmp->end = ast->end;
		tmp->ionum = -1;
		tmp->next_re = -1;
		tmp->next = NULL;
	}
	return (-1);
}
