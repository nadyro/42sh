/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 02:23:25 by azybert           #+#    #+#             */
/*   Updated: 2018/03/10 18:40:07 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

void	ft_cursor_start(t_prompt *prompt)
{
	move_cursor(prompt, prompt->origin->x, true);
}

void	ft_cursor_end(t_prompt *prompt)
{
	move_cursor(prompt, prompt->total, true);
}

void	ft_cursor_left(t_prompt *prompt)
{
	move_cursor(prompt, prompt->pos - 1, true);
}

void	ft_cursor_right(t_prompt *prompt)
{
	move_cursor(prompt, prompt->pos + 1, true);
}
