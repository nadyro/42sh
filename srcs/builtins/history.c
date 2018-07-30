/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:17:24 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/07/30 18:03:32 by kernel_pani      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node    *init_nonvoid_history(char *cmd, t_node *history) 
{ 
  t_node  *new; 
 
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

t_node    *fill_history_file(t_node *history, t_shell *shell) 
{ 
  int    i; 
  char  *c; 
  int    gnl; 
 
  c = NULL; 
  gnl = 0; 
  i = open(".history", O_RDWR | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 
  if (i >= 0) 
  while ((gnl = get_next_line(i, &c)) == 1)
  {
	  shell->history_length++; 
      history = init_nonvoid_history(c, history);
  }
  close(i);
  return (history);
}

void	print_history(int *x, char **cmd, int to_free)
{
    int     i;

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

t_node	*get_last_cmds(t_node *history, int nbr)
{
    int     i;
    char    **last_cmds;
    int     y;
        
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
            break;
    }
    i = 0;
    while (i < y)
        ft_putendl(last_cmds[i++]);
	return (history);
}

void	read_history(t_node *history, int nbr)
{
	char	*c;
	int		i;
	int		x;

	i = open(".history", O_RDONLY);
	c = NULL;
	x = 0;
	if (i >= 0)
	{
        if (nbr > 0)
			get_last_cmds(history, nbr);		
		else
		{
            while (history->next != NULL)
			history = history->next;
			while (get_next_line(i, &c) == 1)
			{
				print_history(&x, &c, 0);
				if (history)
					history = history->prev;
			}
			while (history)
			{
				print_history(&x, &history->cmd, 1);
				history = history->prev;
			}
		}
	}
}
