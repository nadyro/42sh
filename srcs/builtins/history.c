/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 14:47:51 by arohani           #+#    #+#             */
/*   Updated: 2018/08/13 14:49:19 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		history_errors(t_history *hist_args)
{
	if (hist_args->vide == 1)
	{
		ft_putstr("Error : history: d : ");
		ft_putnbr(hist_args->d_arg);
		ft_putendl("out of range.");
	}
	if (hist_args->vide == 2)
		ft_putendl("Error : history: d : Undefined offset");
	if (hist_args->vide == 3)
	{
		ft_putstr("history : usage: ");
		ft_putstr("history [-c] [-d offset] [n] or history -awrn");
		ft_putendl(" or history -ps arg [arg...]");
	}
	if (hist_args->vide == 4)
		ft_putendl("Error : history: Use only one of -warn.");
	if (hist_args->vide == 5)
	{
		ft_putstr("Error : history: flag or ");
		ft_putendl("numeric argument required.");
	}
}

int			ash_history(t_shell *shell)
{
	int			i;
	t_history	*hist_args;

	i = 0;
	hist_args = check_history_args(shell);
	if (hist_args->vide == 0)
		shell->history = dispatch_history_queries(hist_args, shell);
	else
	{
		i = hist_args->vide;
		history_errors(hist_args);
		free(hist_args);
		return (i);
	}
	free(hist_args);
	return (1);
}
