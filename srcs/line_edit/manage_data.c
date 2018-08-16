/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_g_prpt_stock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:36:42 by azybert           #+#    #+#             */
/*   Updated: 2018/08/16 18:41:40 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"
#include "builtins.h"

void		g_prpt_backdel(t_g_prpt *g_prpt)
{
	ft_memmove(&(g_prpt->line[g_prpt->pos]),
			&(g_prpt->line[g_prpt->pos + 1]),
			ft_strlen(&(g_prpt->line[g_prpt->pos])));
	strcat(g_prpt->line, " ");
	write_data(g_prpt, &(g_prpt->line[g_prpt->pos]),
			ft_strlen(&(g_prpt->line[g_prpt->pos])));
	*(ft_strrchr(g_prpt->line, 32)) = '\0';
	g_prpt->total--;
	move_cursor(g_prpt, g_prpt->pos, true);
}

void		g_prpt_delete(t_g_prpt *g_prpt)
{
	ft_memmove(&(g_prpt->line[g_prpt->pos - 1]),
			&(g_prpt->line[g_prpt->pos]),
			ft_strlen(&(g_prpt->line[g_prpt->pos])) + 1);
	move_cursor(g_prpt, g_prpt->pos - 1, true);
	strcat(g_prpt->line, " ");
	write_data(g_prpt, &(g_prpt->line[g_prpt->pos]),
			ft_strlen(&(g_prpt->line[g_prpt->pos])));
	*(ft_strrchr(g_prpt->line, ' ')) = '\0';
	g_prpt->total--;
	move_cursor(g_prpt, g_prpt->pos, true);
}

char		*g_prpt_stock(t_g_prpt *g_prpt, char *user_entry)
{
	char	*line;

	if (g_prpt->total++ % BUFFER == 0)
	{
		if (!(line = ft_memalloc(sizeof(char) *
						(g_prpt->total + BUFFER + 1))))
			sh_close(1, "");
		if (g_prpt->line != NULL)
		{
			ft_strcpy(line, g_prpt->line);
			free(g_prpt->line);
			g_prpt->line = NULL;
		}
		g_prpt->line = line;
	}
	ft_memmove(&(g_prpt->line[g_prpt->pos]) + 1, &(g_prpt->line[g_prpt->pos]),
			ft_strlen(&(g_prpt->line[g_prpt->pos])));
	g_prpt->line[g_prpt->pos] = user_entry[0];
	write_data(g_prpt, &(g_prpt->line[g_prpt->pos]),
			ft_strlen(&(g_prpt->line[g_prpt->pos])));
	move_cursor(g_prpt, g_prpt->pos + 1, true);
	return (g_prpt->line);
}
