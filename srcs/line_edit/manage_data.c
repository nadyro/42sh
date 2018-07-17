/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_stock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:36:42 by azybert           #+#    #+#             */
/*   Updated: 2018/07/17 05:47:26 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static void	ft_writenl(char *to_display, size_t tmp)
{
	size_t	k;
	size_t	sp;

	k = 0;
	sp = 0;
	while (sp + k < tmp)
	{
		if (to_display[sp + k] == '\n')
		{
			write(1, &to_display[sp], k + 1);
			write(1, "\r", 1);
			sp = sp + k + 1;
			k = 0;
		}
		else
			k++;
	}
	write(1, &to_display[sp], k + 1);
	write(1, "\r", 1);
}

void		write_data(t_prompt *prompt, char *to_display, size_t size)
{
	size_t	tmp;
	size_t	displayed;

	move_cursor(prompt, prompt->pos, true);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	displayed = prompt->total - ft_strlen(to_display);
	while (size != 0)
	{
		if (prompt->size->y <= prompt->origin->y +
				(prompt->origin->x + ft_add_nl(prompt, displayed) + 1) / prompt->size->x)
		{
			if ((prompt->origin->x + ft_add_nl(prompt, prompt->pos) + 1) % prompt->size->x == 0)
			{
				move_cursor(prompt, prompt->size->y - prompt->origin->y, false);
				tputs(tgetstr("sf", NULL), 1, ft_putshit);
			}
			prompt->origin->y--;
		}
		move_cursor(prompt, displayed, false);
		tmp = prompt->size->x - (ft_add_nl(prompt, displayed) + prompt->origin->x) % prompt->size->x;
		tmp = ((tmp > size) ? size : tmp);
		ft_writenl(to_display, tmp);
		displayed = displayed + tmp;
		to_display += tmp;
		size -= tmp;
	}
}

void		prompt_backdel(t_prompt *prompt)
{
	ft_memmove(&(prompt->line[prompt->pos]),
			&(prompt->line[prompt->pos + 1]),
			ft_strlen(&(prompt->line[prompt->pos])));
	write_data(prompt, &(prompt->line[prompt->pos]),
			ft_strlen(&(prompt->line[prompt->pos])));
	*(ft_strrchr(prompt->line, 32)) = '\0';
	prompt->total--;
	move_cursor(prompt, prompt->pos, true);
}

void		prompt_delete(t_prompt *prompt)
{
	ft_memmove(&(prompt->line[prompt->pos - 1]),
			&(prompt->line[prompt->pos]),
			ft_strlen(&(prompt->line[prompt->pos])) + 1);
	move_cursor(prompt, prompt->pos - 1, true);
	strcat(prompt->line, " ");
	write_data(prompt, &(prompt->line[prompt->pos]),
			ft_strlen(&(prompt->line[prompt->pos])));
	*(ft_strrchr(prompt->line, ' ')) = '\0';
	prompt->total--;
	move_cursor(prompt, prompt->pos, true);
}

char		*prompt_stock(t_prompt *prompt, char *user_entry)
{
	char	*line;

	if (prompt->total++ % BUFFER == 0)
	{
		if (!(line = ft_memalloc(sizeof(char) *
						(prompt->total + BUFFER + 1))))
			exit(1);
		if (prompt->line != NULL)
		{
			ft_strcpy(line, prompt->line);
			free(prompt->line);
			prompt->line = NULL;
		}
		prompt->line = line;
	}
	ft_memmove(&(prompt->line[prompt->pos]) + 1, &(prompt->line[prompt->pos]),
			ft_strlen(&(prompt->line[prompt->pos])));
	prompt->line[prompt->pos] = user_entry[0];
	write_data(prompt, &(prompt->line[prompt->pos]),
			ft_strlen(&(prompt->line[prompt->pos])));
	move_cursor(prompt, prompt->pos + 1, true);
	return (prompt->line);
}
