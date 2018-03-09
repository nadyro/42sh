/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_cursor_motion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 21:42:41 by azybert           #+#    #+#             */
/*   Updated: 2018/03/09 22:43:51 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

void	ft_cursor_up(t_prompt *prompt)
{
	size_t	tmp;

	tmp = prompt->pos - prompt->size->x;
	prompt->pos = ((tmp > prompt->pos) ? prompt->pos : tmp);
	move_cursor(prompt->pos % prompt->size->x,
			prompt->origin->y + prompt->pos / prompt->size->x);
}

void	ft_cursor_down(t_prompt *prompt)
{
	size_t	tmp;

	tmp = prompt->pos + prompt->size->x;
	prompt->pos = ((tmp > prompt->total) ? prompt->pos : tmp);
	move_cursor(prompt->pos % prompt->size->x,
			prompt->origin->y + prompt->pos / prompt->size->x);
}

void	cursor_word_left(t_prompt *prompt)
{
	if (prompt->pos != prompt->total ||
			ft_isspace(prompt->line[prompt->pos - 1]))
		while (prompt->pos > 0 &&
				!(ft_isspace(prompt->line[prompt->pos])))
			ft_cursor_left(prompt);
	while (prompt->pos > 0 &&
			ft_isspace(prompt->line[prompt->pos]))
		ft_cursor_left(prompt);
	while (prompt->pos > 0 &&
			!(ft_isspace(prompt->line[prompt->pos])))
		ft_cursor_left(prompt);
	if (prompt->pos != 0)
		ft_cursor_right(prompt);
}

void	cursor_word_right(t_prompt *prompt)
{
	while (prompt->pos < prompt->total &&
			!(ft_isspace(prompt->line[prompt->pos])))
		ft_cursor_right(prompt);
	while (prompt->pos < prompt->total &&
			ft_isspace(prompt->line[prompt->pos]))
		ft_cursor_right(prompt);
}
