/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_complet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 03:07:12 by azybert           #+#    #+#             */
/*   Updated: 2018/07/27 07:51:02 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	final_display(t_prompt *prompt, char *to_display)
{
	size_t	rpos;
	char	*rline;

	rpos = prompt->pos;
	move_cursor(prompt, 0, true);
	rline = prompt->line;
	prompt->line = to_display;
	prompt->total = ft_strlen(prompt->line);
    write_data(prompt, prompt->line, prompt->total);
	prompt->line = rline;
	prompt->total = ft_strlen(prompt->line);
	move_cursor(prompt, rpos, true);
}

void	completion_display_aux(t_prompt *prompt, t_node *complete, int nb, int max)
{
	t_node	*loop;
	char	*to_display;
	char	*spn;
	int		count;

	if (!(to_display = ft_memalloc(sizeof(char) * nb * max + 1 + prompt->total + 1)))
		exit(1);
	ft_strcat(to_display, prompt->line);
	ft_strcat(to_display, "\n");
	loop = complete;
	count = 0;
	while (loop)
	{
		ft_strcat(to_display, loop->cmd);
		spn = ft_strchr(to_display, '\0');
		if (++count % (prompt->size->x / max) == 0)
			ft_strcat(to_display, "\n");
		else
			ft_memset(spn, ' ', max - ft_strlen(loop->cmd));
		loop = loop->next;
	}
	final_display(prompt, to_display);
	free(to_display);
}

void	completion_display(t_prompt *prompt, t_node *complete)
{
	t_node	*loop;
	size_t	max;
	int		nb;

	loop = complete;
	nb = 0;
	max = 0;
	while (loop != NULL)
	{
		max = (ft_strlen(loop->cmd) > max ? ft_strlen(loop->cmd) : max);
		nb++;
		loop = loop->next;
	}
	max++;
	completion_display_aux(prompt, complete, nb, max);
}

void	auto_complete(t_prompt *prompt)
{
	t_node	*complete;
	
	complete = prompt->current;					//ft_nadir;
	if (complete == NULL)
		return ;
	else if (complete->next == NULL)
	{
		secure_stock(prompt, complete->cmd);
	}
	else
		completion_display(prompt, complete);
}
