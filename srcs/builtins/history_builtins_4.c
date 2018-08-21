/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 22:41:58 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/21 13:57:55 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int			checkarg(t_history *hist_args, t_shell *shell, int y, int i)
{
	if (shell->args[y][0] == '-')
	{
		if (hist_args->d_arg == 0 && shell->args[y][i] != 'c'
		&& shell->args[y][i] != 'a' && shell->args[y][i] != 'n'
		&& shell->args[y][i] != 'r' && shell->args[y][i] != 'w'
		&& shell->args[y][i] != 'p' && shell->args[y][i] != 's'
		&& shell->args[y][i] != 'h')
		{
			hist_args->vide = 3;
			return (hist_args->vide);
		}
	}
	return (hist_args->vide);
}

static t_history	*check_flag_2(t_shell *shell, t_history *hist_args)
{
	int		i;
	int		y;
	int		x;

	y = 1;
	i = 0;
	x = hist_args->vide;
	while (shell->args && shell->args[y])
	{
		while (shell->args[y][++i] != '\0')
		{
			hist_args = check_d_arg(y, shell, hist_args);
			if (hist_args->vide >= 1)
				return (hist_args);
			if ((x = checkarg(hist_args, shell, y, i)) >= 1)
				return (hist_args);
			if (check_warn(shell, hist_args, y) >= 1)
				return (hist_args);
		}
		i = 0;
		y++;
	}
	return (hist_args);
}

static t_history	*h_args(t_history *hist_args, t_shell *shell, int *i)
{
	if (ft_strchr(shell->args[*i], 'a') != NULL)
	{
		hist_args->a = 1;
		hist_args->no_write = 1;
		hist_args->a_to_f = (shell->args[*i + 1] != NULL) ? 1 : 0;
	}
	if (ft_strchr(shell->args[*i], 'n') != NULL)
	{
		hist_args->n = 1;
		hist_args->no_write = 1;
		hist_args->n_to_f = (shell->args[*i + 1] != NULL) ? 1 : 0;
	}
	if (ft_strchr(shell->args[*i], 'r') != NULL)
	{
		hist_args->r = 1;
		hist_args->no_write = 1;
		hist_args->r_to_f = (shell->args[*i + 1] != NULL) ? 1 : 0;
	}
	if (ft_strchr(shell->args[*i], 'w') != NULL)
	{
		hist_args->w = 1;
		hist_args->no_write = 1;
		hist_args->w_to_f = (shell->args[*i + 1] != NULL) ? 1 : 0;
	}
	return (hist_args);
}

t_history			*check_if_flag(t_shell *shell, t_history *hist_args)
{
	int			i;
	int			y;

	i = 0;
	y = 1;
	if (shell->args[y])
	{
		if (shell->args[y][i] == '-' && shell->args[y][i + 1] == '\0')
			hist_args->vide = 5;
		else if (shell->args[y][i] != '-')
		{
			if (ft_atoi(shell->args[y]) == 0)
				hist_args->vide = 5;
		}
		else
			hist_args = check_flag_2(shell, hist_args);
	}
	return (hist_args);
}

t_history			*fill_args(t_shell *shell, t_history *hist_args, int *i)
{
	char	*arg_d;

	arg_d = NULL;
	if (ft_strchr(shell->args[*i], 'd') != NULL)
	{
		hist_args->d = 1;
		arg_d = ft_strchr(shell->args[*i], 'd');
		if (arg_d[1] && arg_d[1] >= '1' && arg_d[1] <= '9')
			hist_args->d_arg = ft_atoi(&arg_d[1]);
		else if (shell->args[*i + 1])
			hist_args->d_arg = ft_atoi(shell->args[*i + 1]);
	}
	hist_args = h_args(hist_args, shell, i);
	hist_args->c = (ft_strchr(shell->args[*i], 'c') != NULL) ? 1 : 0;
	hist_args->p = (ft_strchr(shell->args[*i], 'p') != NULL) ? 1 : 0;
	if (hist_args->p == 1)
		hist_args->no_write = 1;
	hist_args->h = (ft_strchr(shell->args[*i], 'h') != NULL) ? 1 : 0;
	if (ft_strchr(shell->args[*i], 's') != NULL)
		hist_args->s = 1;
	if (hist_args->s == 1)
		hist_args->no_write = 1;
	return (hist_args);
}
