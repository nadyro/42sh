/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 06:42:51 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/07 06:49:03 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_history	*check_d_arg(int y, t_shell *shell, t_history *hist_args)
{
	char	*arg_d;

	if (ft_strchr(shell->args[y], 'd') != NULL)
	{
		arg_d = ft_strchr(shell->args[y], 'd');
		if (arg_d[1] && arg_d[1] >= '1' && arg_d[1] <= '9')
			hist_args->d_arg = ft_atoi(&arg_d[1]);
		else if (shell->args[y + 1])
			hist_args->d_arg = ft_atoi(shell->args[y + 1]);
		if (hist_args->d_arg < 0)
		{
			hist_args->vide = 2;
			return (hist_args);
		}
		else if (hist_args->d_arg > shell->history_length)
		{
			hist_args->vide = 1;
			return (hist_args);
		}
	}
	return (hist_args);
}

int			check_warn_w(t_history *hist_args, t_shell *shell, int y)
{
	int		x;

	x = 0;
	if (ft_strchr(shell->args[y], 'w') != NULL)
	{
		x = 1;
		while (shell->args && shell->args[x] && shell->args[x][0] == '-')
		{
			if (ft_strchr(shell->args[x], 'a') != NULL
			|| ft_strchr(shell->args[x], 'r') != NULL
			|| ft_strchr(shell->args[x], 'n') != NULL)
			{
				hist_args->vide = 4;
				return (hist_args->vide);
			}
			x++;
		}
	}
	return (hist_args->vide);
}

int			check_warn_a(t_history *hist_args, t_shell *shell, int y)
{
	int		x;

	x = 0;
	if (ft_strchr(shell->args[y], 'a') != NULL)
	{
		x = 1;
		while (shell->args && shell->args[x] && shell->args[x][0] == '-')
		{
			if (ft_strchr(shell->args[x], 'w') != NULL
			|| ft_strchr(shell->args[x], 'r') != NULL
			|| ft_strchr(shell->args[x], 'n') != NULL)
			{
				hist_args->vide = 4;
				return (hist_args->vide);
			}
			x++;
		}
	}
	return (hist_args->vide);
}

int			check_warn_r(t_history *hist_args, t_shell *shell, int y)
{
	int		x;

	x = 0;
	if (ft_strchr(shell->args[y], 'r') != NULL)
	{
		x = 1;
		while (shell->args && shell->args[x] && shell->args[x][0] == '-')
		{
			if (ft_strchr(shell->args[x], 'a') != NULL
			|| ft_strchr(shell->args[x], 'w') != NULL
			|| ft_strchr(shell->args[x], 'n') != NULL)
			{
				hist_args->vide = 4;
				return (hist_args->vide);
			}
			x++;
		}
	}
	return (hist_args->vide);
}

int			check_warn_n(t_history *hist_args, t_shell *shell, int y)
{
	int		x;

	x = 0;
	if (ft_strchr(shell->args[y], 'n') != NULL)
	{
		x = 1;
		while (shell->args && shell->args[x] && shell->args[x][0] == '-')
		{
			if (ft_strchr(shell->args[x], 'a') != NULL
			|| ft_strchr(shell->args[x], 'r') != NULL
			|| ft_strchr(shell->args[x], 'w') != NULL)
			{
				hist_args->vide = 4;
				return (hist_args->vide);
			}
			x++;
		}
	}
	return (hist_args->vide);
}
