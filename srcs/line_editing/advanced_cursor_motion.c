/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_cursor_motion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 21:42:41 by azybert           #+#    #+#             */
<<<<<<< HEAD:line_editing/advanced_cursor_motion.c
/*   Updated: 2018/03/04 18:46:01 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
=======
/*   Updated: 2018/03/04 22:41:16 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"
>>>>>>> a2e53d1e55ba2763625a0d94c0adc5e4cb0e80a7:srcs/line_editing/advanced_cursor_motion.c

void	cursor_word_left(t_prompt *prompt)
{
	if (prompt->line_pos != prompt->total ||
			ft_isspace(prompt->line[prompt->line_pos - 1]))
		while (prompt->line_pos > 0 &&
				!(ft_isspace(prompt->line[prompt->line_pos])))
			ft_cursor_left(prompt);
	while (prompt->line_pos > 0 &&
			ft_isspace(prompt->line[prompt->line_pos]))
		ft_cursor_left(prompt);
	while (prompt->line_pos > 0 &&
			!(ft_isspace(prompt->line[prompt->line_pos])))
		ft_cursor_left(prompt);
	if (prompt->line_pos != 0)
		ft_cursor_right(prompt);
}

void	cursor_word_right(t_prompt *prompt)
{
	while (prompt->line_pos < prompt->total &&
			!(ft_isspace(prompt->line[prompt->line_pos])))
		ft_cursor_right(prompt);
	while (prompt->line_pos < prompt->total &&
			ft_isspace(prompt->line[prompt->line_pos]))
		ft_cursor_right(prompt);
}
