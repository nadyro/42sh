/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 14:53:44 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/21 13:58:42 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_history	*init_hist_args(void)
{
	t_history	*hist_args;

	if (!(hist_args = (t_history *)malloc(sizeof(t_history))))
		return (NULL);
	hist_args->c = 0;
	hist_args->d = 0;
	hist_args->d_arg = 0;
	hist_args->a = 0;
	hist_args->a_to_f = 0;
	hist_args->n = 0;
	hist_args->n_to_f = 0;
	hist_args->r = 0;
	hist_args->r_to_f = 0;
	hist_args->w = 0;
	hist_args->w_to_f = 0;
	hist_args->h = 0;
	hist_args->p = 0;
	hist_args->s = 0;
	hist_args->vide = 0;
	hist_args->no_write = 0;
	return (hist_args);
}

static void			history_helper(void)
{
	ft_putendl("usage : history\n");
	ft_putendl("n : Writes the last 'n' lines written to history session.\n");
	ft_putendl("-w : Writes the history session to history file.\n");
	ft_putendl("-a : Appends the history session to history file.\n");
	ft_putendl("-r : Overwrite the history session with the history file.\n");
	ft_putendl("-c : Flushes history session.\n");
	ft_putendl("-d offset : Deletes offset line from history session.\n");
	ft_putendl("-n : Appends the last appended lines to the history file.\n");
	ft_putstr("-p : Prints history arguments to stdout ");
	ft_putendl("without storing it to history file.\n");
	ft_putendl("-s : Saves the history args to the history session.");
}

static void			lighten_dispatching(t_history *hist_args, t_shell *shell)
{
	if (hist_args->a == 1 && hist_args->a_to_f != 1)
		append_history_mem_to_file(shell);
	else if (hist_args->a == 1 && hist_args->a_to_f == 1)
		append_history_mem_to_arg(shell);
	else if (hist_args->w == 1 && hist_args->w_to_f != 1)
		write_history_mem_to_file(shell);
	else if (hist_args->w == 1 && hist_args->w_to_f == 1)
		write_history_mem_to_arg(shell);
	if (hist_args->p == 1)
		write_arg_p(shell);
	if (hist_args->s == 1)
		write_arg_s(shell);
	else if (hist_args->h == 1)
		history_helper();
	else if (hist_args->no_write != 1)
		dispatch_history_print(shell);
}

t_history			*check_history_args(t_shell *shell)
{
	int			i;
	t_history	*hist_args;

	i = 0;
	hist_args = init_hist_args();
	hist_args = check_if_flag(shell, hist_args);
	if (hist_args->vide >= 1)
		return (hist_args);
	while (shell->args && shell->args[++i])
		if (shell->args[i][0] == '-')
			hist_args = fill_args(shell, hist_args, &i);
	return (hist_args);
}

t_node				*dispatch_h_q(t_history *hist_args, t_shell *shell)
{
	int		i;
	int		conv;

	i = 0;
	conv = 0;
	if (hist_args->c == 1)
		shell->history = clear_history_mem(shell);
	if (hist_args->d == 1)
		dispatch_history_d(shell, hist_args);
	if (hist_args->r == 1 && hist_args->r_to_f != 1)
		shell->history = append_h_to_mem(shell->history, shell, 0);
	else if (hist_args->r == 1 && hist_args->r_to_f == 1)
		shell->history = append_h_to_mem(shell->history, shell, 1);
	else if (hist_args->n == 1 && shell->is_a == 1)
		shell->history = write_history_to_mem(shell->history, shell);
	lighten_dispatching(hist_args, shell);
	return (shell->history);
}
