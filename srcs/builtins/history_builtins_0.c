/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins_0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:17:24 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/08/05 22:33:34 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		write_history_file(t_shell *shell, int to_f)
{
	int		i;
	t_node	*history;

	i = 0;
	history = shell->history;
	while (history && history->next != NULL)
		history = history->next;
	if (to_f == 1 && shell->args[2] != NULL)
		i = open(shell->args[2], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR
		| S_IRGRP | S_IROTH);
	else
		i = open(shell->home_env, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR
		| S_IRGRP | S_IROTH);
	if (i > 0)
		while (history)
		{
			ft_putendl_fd(history->cmd, i);
			history = history->prev;
		}
	if (i < 0)
		ft_putstr("Error. Couldn't write into file. Check your rights. \n");
	else
		close(i);
}

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

	c = NULL;
	i = open(shell->home_env, O_RDWR | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (i >= 0)
	{
		while ((get_next_line(i, &c)) == 1)
		{
			shell->history_length++;
			history = init_nonvoid_history(c, history);
		}
		shell->o_history = shell->history_length;
		close(i);
	}
	else
		ft_putendl("Couldn't open file. Check your rights.");
	return (history);
}

void		read_history(t_node *history, int nbr)
{
	char	*c;
	int		x;

	c = NULL;
	x = 0;
	if (history)
	{
		if (nbr > 0)
			get_last_cmds(history, nbr);
		else
		{
			while (history && history->next != NULL)
				history = history->next;
			while (history)
			{
				print_history(&x, &history->cmd, 1);
				history = history->prev;
			}
		}
	}
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
