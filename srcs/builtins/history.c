/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 14:47:51 by arohani           #+#    #+#             */
/*   Updated: 2018/08/20 22:11:29 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		history_errors(t_history *hist_args)
{
	if (hist_args->vide == 1)
	{
		ft_putstr_fd("Error : history: d : ", 2);
		ft_putnbr_fd(hist_args->d_arg, 2);
		ft_putendl_fd(" out of range.", 2);
	}
	if (hist_args->vide == 2)
		ft_putendl_fd("Error : history: d : Undefined offset", 2);
	if (hist_args->vide == 3)
	{
		ft_putstr_fd("history : usage: ", 2);
		ft_putstr_fd("history [-c] [-d offset] [n] or history -awrn", 2);
		ft_putendl_fd(" or history -ps arg [arg...]", 2);
	}
	if (hist_args->vide == 4)
		ft_putendl_fd("Error : history: Use only one of -warn.", 2);
	if (hist_args->vide == 5)
	{
		ft_putstr_fd("Error : history: flag or ", 2);
		ft_putendl_fd("numeric argument required.", 2);
	}
}

int			signal_history_static(int x)
{
	static int		sign = 1;

	if (x >= 0)
		sign = x;
	return (sign);
}

void		sign_history(int sig)
{
	signal_history_static(0);
	signal(sig, sign_history);
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
		return (-1);
	}
	free(hist_args);
	return (0);
}
