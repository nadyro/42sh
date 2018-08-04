/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:53:44 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/05 00:58:22 by nsehnoun         ###   ########.fr       */
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
	hist_args->h = 0;
	hist_args->p = 0;
	hist_args->s = 0;
	hist_args->vide = 0;
	return (hist_args);
}

t_history	*check_history_args(t_shell *shell)
{
	int			i;
	t_history	*hist_args;

	i = 0;
	hist_args = init_hist_args();
	hist_args = check_if_flag(shell, hist_args);
	i = 0;
	while (shell->args && shell->args[++i])
		if (shell->args[i][0] == '-')
			hist_args = fill_hist_args(shell, hist_args, &i);
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
	if (hist_args->d == 1)
		dispatch_history_d(shell, hist_args);
	if (hist_args->r == 1)
		shell->history = append_history_to_mem(shell->history, shell);
	if (hist_args->a == 1)
		append_history_mem_to_file(shell);
	if (hist_args->w == 1)
		write_history_mem_to_file(shell);
	if (hist_args->h == 1)
		history_helper();
	if (hist_args->vide == 2)
		dispatch_history_print(shell);
	return (shell->history);
}

void		history_helper(void)
{
	ft_putendl("usage : history\n");
	ft_putendl("n : Writes the last 'n' lines written to history session.\n");
	ft_putendl("-w : Writes the history session to history file.\n");
	ft_putendl("-a : Appends the history session to history file.\n");
	ft_putendl("-r : Overwrite the history session with the history file.\n");
	ft_putendl("-c : Flushes history session.\n");
	ft_putendl("-d offset : Deletes offset line from history session.");
}
