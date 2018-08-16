/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:16:39 by pbie              #+#    #+#             */
/*   Updated: 2018/08/16 12:56:45 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#define ARG shell->args[shell->st]

void	cd_not_dir(char *str)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Not a directory\n", 2);
}

void	executing_directory(t_shell *shell)
{
	ft_putstr_fd(shell->args[0], 2);
	ft_putstr_fd(": is a directory\n", 2);
}

int		cd_error_mgmt(char *operand)
{
	struct stat		tmp;
	
	if (stat(operand, &tmp) == 0 && (S_ISDIR(tmp.st_mode) & (tmp.st_mode & S_IXUSR)))
		return (0);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(operand, 2);
	if (lstat(operand, &tmp) == 0 && (S_ISLNK(tmp.st_mode)))
		ft_putendl_fd(": Too many levels of symbolic links.", 2);		
	else if (stat(operand, &tmp) == 0 && !(S_ISDIR(tmp.st_mode)))
		ft_putendl_fd(": Not a directory.", 2);
	else if (lstat(operand, &tmp) == 0 && !(tmp.st_mode & S_IXUSR))
		ft_putendl_fd(": Permission denied.", 2);
	else if (access(operand, F_OK))
		ft_putendl_fd(": No such file or directory.", 2);		
	return (-1);
}