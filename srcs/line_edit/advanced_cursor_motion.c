/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_cursor_motion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 21:42:41 by azybert           #+#    #+#             */
/*   Updated: 2018/03/04 18:46:01 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/42sh_line_edit.h"

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
