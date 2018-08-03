/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:53:44 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/03 05:29:37 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_history	*init_hist_args(void)
{
	t_history	*hist_args;

	if (!(hist_args = (t_history *)malloc(sizeof(t_history))))
		return (NULL);
	hist_args->c = 0;
	hist_args->d = 0;
	hist_args->d_arg = 0;
	hist_args->a = 0;
	hist_args->n = 0;
	hist_args->r = 0;
	hist_args->w = 0;
	hist_args->p = 0;
	hist_args->s = 0;
	return (hist_args);
}

t_history	*check_history_args(t_shell *shell)
{
	int			i;
	t_history	*hist_args;

	i = 0;
	hist_args = init_hist_args();
	while (shell->args && shell->args[++i])
		if (shell->args[i][0] == '-')
		{
			if (ft_strchr(shell->args[i], 'd') != NULL)
			{
				hist_args->d = 1;
				hist_args->d_arg = (shell->args[i + 1])
				? ft_atoi(shell->args[i + 1]) : -1;
			}
			hist_args->c = (ft_strchr(shell->args[i], 'c') != NULL) ? 1 : 0;
			hist_args->a = (ft_strchr(shell->args[i], 'a') != NULL) ? 1 : 0;
			hist_args->n = (ft_strchr(shell->args[i], 'n') != NULL) ? 1 : 0;
			hist_args->r = (ft_strchr(shell->args[i], 'r') != NULL) ? 1 : 0;
			hist_args->w = (ft_strchr(shell->args[i], 'w') != NULL) ? 1 : 0;
			hist_args->p = (ft_strchr(shell->args[i], 'p') != NULL) ? 1 : 0;
			hist_args->s = (ft_strchr(shell->args[i], 's') != NULL) ? 1 : 0;
		}
	return (hist_args);
}

t_node		*dispatch_history_queries(t_history *hist_args, t_shell *shell)
{
	int		i;
	int		conv;

	i = 0;
	conv = 0;
	if (hist_args->c == 1)
		shell->history = clear_history_mem(shell);
	else if (hist_args->d == 1)
		dispatch_history_d(shell, hist_args);
	else if (hist_args->w == 1)
		write_history_mem_to_file(shell);
	else if (hist_args->a == 1)
		append_history_mem_to_file(shell);
	else if (hist_args->r == 1)
		shell->history = append_history_file_to_mem_1(shell->history, shell);
	else
		dispatch_history_print(shell);
	return (shell->history);
}
