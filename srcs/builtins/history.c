/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:17:24 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/01 23:10:18 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node		*init_nonvoid_history(char *cmd, t_node *history)
{
	t_node	*new;

	if (!(new = malloc(sizeof(*new))))
		exit(1);
	if (!(new->cmd = ft_strdup(cmd)))
		exit(1);
	new->next = history;
	new->prev = NULL;
	free(cmd);
	cmd = NULL;
	if (history)
		history->prev = new;
	history = new;
	return (history);
}

t_node		*fill_history_file(t_node *history, t_shell *shell)
{
	int		i;
	char	*c;
	int		gnl;

	c = NULL;
	gnl = 0;
	i = open(".history", O_RDWR | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (i >= 0)
	{
		while ((gnl = get_next_line(i, &c)) == 1)
		{
			shell->history_length++;
			history = init_nonvoid_history(c, history);
		}
		close(i);
	}
	else
		return (NULL);
	return (history);
}

void		print_history(int *x, char **cmd, int to_free)
{
	int		i;

	i = *x;
	i = i + 1;
	*x = i;
	ft_putnbr(*x);
	ft_putchar(' ');
	ft_putendl(*cmd);
	if (to_free == 0)
	{
		free(*cmd);
		*cmd = NULL;
	}
}

t_node		*get_last_cmds(t_node *history, int nbr)
{
	int		i;
	char	**last_cmds;
	int		y;

	y = nbr;
	if (!(last_cmds = (char **)malloc(sizeof(char *) * (nbr + 1))))
		return (NULL);
	last_cmds[nbr] = NULL;
	while (history)
	{
		last_cmds[nbr - 1] = ft_strdup(history->cmd);
		history = history->next;
		nbr--;
		if (nbr == 0)
			break ;
	}
	i = 0;
	while (i < y)
		ft_putendl(last_cmds[i++]);
	clean_tabs(last_cmds, 0);
	return (history);
}

void		read_history(t_node *history, int nbr)
{
	char	*c;
	int		i;
	int		x;

	i = open(".history", O_RDONLY);
	c = NULL;
	x = 0;
	if (history)
	{
		if (nbr > 0)
			get_last_cmds(history, nbr);
		else
		{
			while (history->next != NULL)
				history = history->next;
			while (history)
			{
				print_history(&x, &history->cmd, 1);
				history = history->prev;
			}
		}
	}
	else
	{
		ft_putstr("History file error code : ");
		ft_putnbr(i);
	}
}

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

void		print_hist_args(t_history *hist_args)
{
	ft_putnbr(hist_args->c);
	ft_putchar('\n');
	ft_putnbr(hist_args->d);
	ft_putchar('\n');
	ft_putnbr(hist_args->d_arg);
	ft_putchar('\n');
	ft_putnbr(hist_args->a);
	ft_putchar('\n');
	ft_putnbr(hist_args->n);
	ft_putchar('\n');
	ft_putnbr(hist_args->r);
	ft_putchar('\n');
	ft_putnbr(hist_args->w);
	ft_putchar('\n');
	ft_putnbr(hist_args->p);
	ft_putchar('\n');
	ft_putnbr(hist_args->s);
	ft_putchar('\n');
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
			if (ft_strchr(shell->args[i], 'c') != NULL)
				hist_args->c = 1;
			if (ft_strchr(shell->args[i], 'd') != NULL)
			{
				hist_args->d = 1;
				if (shell->args[i + 1])
					hist_args->d_arg = ft_atoi(shell->args[i + 1]);
			}
			if (ft_strchr(shell->args[i], 'a') != NULL)
				hist_args->a = 1;
			if (ft_strchr(shell->args[i], 'n') != NULL)
				hist_args->n = 1;
			if (ft_strchr(shell->args[i], 'r') != NULL)
				hist_args->r = 1;
			if (ft_strchr(shell->args[i], 'w') != NULL)
				hist_args->w = 1;
			if (ft_strchr(shell->args[i], 'p') != NULL)
				hist_args->p = 1;
			if (ft_strchr(shell->args[i], 's') != NULL)
				hist_args->s = 1;
		}
		print_hist_args(hist_args);
	return (hist_args);
}
