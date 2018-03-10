/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 02:23:25 by azybert           #+#    #+#             */
/*   Updated: 2018/03/10 17:40:18 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

void	ft_cursor_start(t_prompt *prompt)
{
	prompt->pos = 0;
	move_cursor(prompt->pos % prompt->size->x,
			prompt->origin->y + prompt->pos / prompt->size->x);
}

void	ft_cursor_end(t_prompt *prompt)
{
	prompt->pos = prompt->total;
	move_cursor(prompt->pos % prompt->size->x,
			prompt->origin->y + prompt->pos / prompt->size->x);
}

void	ft_cursor_left(t_prompt *prompt)
{
	if (prompt != NULL)
		prompt->pos--;
	move_cursor(prompt->pos % prompt->size->x,
			prompt->origin->y + prompt->pos / prompt->size->x);
}

void	ft_cursor_right(t_prompt *prompt)
{
	if (prompt != NULL)
		prompt->pos++;
	move_cursor(prompt->pos % prompt->size->x,
			prompt->origin->y + prompt->pos / prompt->size->x);
}
