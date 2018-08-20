/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 13:58:28 by arohani           #+#    #+#             */
/*   Updated: 2018/08/20 16:23:33 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#define ARG shell->args[0]

int			handle_arg_errors(t_shell *shell, t_ast *cmd)
{
	if ((ft_strcmp(ARG, ".") == 0 || ft_strcmp(ARG, "..") == 0))
	{
		ft_putstr_fd(ARG, 2);
		ft_putstr_fd(": Command not found.\n", 2);
		ft_bzero((void *)(ARG), ft_strlen(ARG));
		ft_strdel(&(shell->full_path));
		return (cmd->cmd_ret = -1);
	}
	else if (ARG && ft_strlen(ARG) && (ARG[0] == '/' ||
				(ARG[0] == '.' && ARG[1] == '/')) && access(ARG, F_OK))
	{
		ft_putstr_fd(ARG, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (cmd->cmd_ret = -1);
	}
	else if (!(ft_strlen(ARG)) || (ARG && access(ARG, F_OK) &&
			(shell->full_path == NULL || access(shell->full_path, F_OK))))
	{
		ft_putstr_fd(ARG, 2);
		(ARG[0] == '/' || (ARG[0] == '.' && ARG[1] == '/')) ?
			ft_putstr_fd(": No such file or directory\n", 2) :
			ft_putstr_fd(": Command not found.\n", 2);
		return (cmd->cmd_ret = -1);
	}
	return (0);
}
