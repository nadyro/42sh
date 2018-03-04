/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_stock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:36:42 by azybert           #+#    #+#             */
/*   Updated: 2018/03/04 17:36:42 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	ft_prompt_backdel(t_prompt *prompt)
{
	size_t	mem;

	prompt->total--;
	ft_memmove(&(prompt->line[prompt->line_pos]),
			&(prompt->line[prompt->line_pos + 1]),
			ft_strlen(&(prompt->line[prompt->line_pos])));
	write(1, &(prompt->line[prompt->line_pos]),
			mem = ft_strlen(&(prompt->line[prompt->line_pos])));
	write(1, " ", 1);
	mem++;
	while (mem-- > 0)
		ft_cursor_left(NULL);
}

void	ft_prompt_delete(t_prompt *prompt)
{
	size_t	mem;

	prompt->total--;
	ft_memmove(&(prompt->line[prompt->line_pos - 1]),
			&(prompt->line[prompt->line_pos]),
			ft_strlen(&(prompt->line[prompt->line_pos - 1])) + 1);
	prompt->line_pos--;
	ft_cursor_left(NULL);
	write(1, &(prompt->line[prompt->line_pos]),
			mem = ft_strlen(&(prompt->line[prompt->line_pos])));
	write(1, " ", 1);
	mem++;
	while (mem-- > 0)
		ft_cursor_left(NULL);
}

char	*ft_prompt_stock(t_prompt *prompt)
{
	char	*line;
	size_t	mem;

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
	ft_memmove(&(prompt->line[prompt->line_pos]) + 1, &(prompt->line[prompt->line_pos]),
			ft_strlen(&(prompt->line[prompt->line_pos])));
	prompt->line[prompt->line_pos] = prompt->c[0];
	//write(1, &(prompt->line[prompt->line_pos]),
	//		mem = ft_strlen(&(prompt->line[prompt->line_pos])));
	mem = prompt->line_pos;
	while (mem-- > 0)
		ft_cursor_left(NULL);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);
	write(1, prompt->line, prompt->total);
	prompt->line_pos++;
	mem = prompt->total - prompt->line_pos;
	while (mem-- > 0)
		ft_cursor_left(NULL);
	/*mem = ++prompt->line_pos;
	while (mem-- > 0)
		ft_cursor_right(NULL);*/
	//prompt->line_pos++;
	//while (--mem > 0)
	//	ft_cursor_left(NULL);
	return (prompt->line);
}
