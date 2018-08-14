/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:16:39 by pbie              #+#    #+#             */
/*   Updated: 2018/08/14 15:55:28 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
