/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_stock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:36:42 by azybert           #+#    #+#             */
/*   Updated: 2018/03/15 15:43:09 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

void		write_data(t_prompt *prompt, char *display, size_t size)
{
	size_t	mem;
	size_t	tmp;
	size_t	displayed;

	mem = size;
	while (size != 0)
	{
		displayed = prompt->total - ft_strlen(display);
		if (displayed % prompt->size->x == 0)
			move_cursor(prompt, displayed, false);
		tmp = prompt->size->x - displayed % prompt->size->x;
		tmp = ((tmp > size) ? size : tmp);
		write(1, display, tmp);
		display += tmp;
		size -= tmp;
	}
}

void		prompt_backdel(t_prompt *prompt)
{
	ft_memmove(&(prompt->line[prompt->pos]),
			&(prompt->line[prompt->pos + 1]),
			ft_strlen(&(prompt->line[prompt->pos])));
	strcat(prompt->line, " ");
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
			ft_strlen(&(prompt->line[prompt->pos - 1])) + 1);
	move_cursor(prompt, prompt->pos - 1, true);
	strcat(prompt->line, " ");
	write_data(prompt, &(prompt->line[prompt->pos]),
			ft_strlen(&(prompt->line[prompt->pos])));
	*(ft_strrchr(prompt->line, 32)) = '\0';
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
	//check if need to scroll??;
	write_data(prompt, &(prompt->line[prompt->pos]),
			ft_strlen(&(prompt->line[prompt->pos])));
	move_cursor(prompt, prompt->pos + 1, true);
	return (prompt->line);
}
