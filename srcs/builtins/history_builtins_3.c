/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 02:11:49 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/03 02:58:07 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		dispatch_history_d(t_shell *shell, t_history *hist_args)
{
	if (hist_args->d_arg > 0)
	{
		if (hist_args->d_arg <= shell->history_length - 1)
			delete_history_line(shell, hist_args->d_arg);
		else
		{
			ft_putstr("history: ");
			ft_putnbr(hist_args->d_arg);
			ft_putendl(": history position out of range.");
		}
	}
	else
		ft_putendl("Undefined offset.");
}

void		dispatch_history_print(t_shell *shell)
{
	int		conv;

	conv = 0;
	if (shell->args && shell->args[1])
	{
		conv = ft_atoi(shell->args[1]);
		if (conv <= shell->history_length)
			read_history(shell->history, conv);
		else
			read_history(shell->history, 0);
	}
	else if (shell->args)
		read_history(shell->history, 0);
}
