/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_stock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:36:42 by azybert           #+#    #+#             */
/*   Updated: 2018/03/09 19:02:21 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/42sh_line_edit.h"

void	ft_write_data(t_prompt *prompt, char *display, size_t size)
{
	size_t	mem;
	size_t	tmp;
	size_t	displayed;

	mem = size;
	while (size != 0)
	{
		displayed = prompt->total - ft_strlen(display);
		if (displayed % prompt->size->x == 0)
			move_cursor(prompt, 0,
					prompt->origin->y + displayed / prompt->size->x);
		tmp = prompt->size->x - displayed % prompt->size->x;
		tmp = ((tmp > size) ? size : tmp);
		write(1, display, tmp);
		display += tmp;
		size -= tmp;
	}
	prompt->pos++;
	move_cursor(prompt, prompt->pos % prompt->size->x,
			prompt->origin->y + prompt->pos / prompt->size->x);
}

/*void	ft_prompt_backdel(t_prompt *prompt)
{
	size_t	mem;

	prompt->total--;
	ft_memmove(&(prompt->line[prompt->pos]),
			&(prompt->line[prompt->pos + 1]),
			ft_strlen(&(prompt->line[prompt->pos])));
	write(1, &(prompt->line[prompt->pos]),
			mem = ft_strlen(&(prompt->line[prompt->pos])));
	write(1, " ", 1);
	mem++;
	while (mem-- > 0)
		ft_cursor_left(NULL);
}*/

void	ft_prompt_delete(t_prompt *prompt)
{
	size_t	mem;

	prompt->total--;
	ft_memmove(&(prompt->line[prompt->pos - 1]),
			&(prompt->line[prompt->pos]),
			ft_strlen(&(prompt->line[prompt->pos - 1])) + 1);
	prompt->pos--;
	ft_cursor_left(NULL);
	strcat(prompt->line, " ");
	write(1, &(prompt->line[prompt->pos]),
			mem = ft_strlen(&(prompt->line[prompt->pos])));
	*(ft_strrchr(prompt->line, 32)) = '\0';
	//write(1, " ", 1);
	//mem++a;
	while (mem-- > 0)
		ft_cursor_left(NULL);
}

char	*ft_prompt_stock(t_prompt *prompt)
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
	prompt->line[prompt->pos] = prompt->c[0];
	ft_write_data(prompt, &(prompt->line[prompt->pos]),
			ft_strlen(&(prompt->line[prompt->pos])));
	return (prompt->line);
}
