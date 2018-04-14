/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   react.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 13:39:16 by azybert           #+#    #+#             */
/*   Updated: 2018/03/30 20:31:09 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

int	data_react(t_prompt *prompt)
{
	int		mem;
	char	*to_free;

	mem = 0;
	while (ft_isprint(prompt->buf[mem]))
		prompt_stock(prompt, &prompt->buf[mem++]);
	if (prompt->buf[mem] == '\n')
	{
		move_cursor(prompt, prompt->total, true);
		prompt_stock(prompt, &prompt->buf[mem]);
		to_free = prompt->buf;
		prompt->buf = ft_strdup(&prompt->buf[mem + 1]);
		free(to_free);
		return (1);
	}
	free(prompt->buf);
	prompt->buf = NULL;
	return (0);
}

int	esc_react(t_prompt *prompt, int nb_user_entry, char *user_entry)
{
	if (nb_user_entry == 1 && user_entry[0] == 127 && prompt->pos > 0)
		prompt_delete(prompt);
	else if (nb_user_entry == 4 && user_entry[3] == 126 &&
			prompt->pos < prompt->total)
		prompt_backdel(prompt);
	/*else if (nb_user_entry == 3 && user_entry[2] == 65)
	 *      historique up;
	 *          else if (nb_user_entry == 3 && user_entry[2] == 66)
	 *              historique down;*/
	else if (nb_user_entry == 3 && user_entry[2] == 68 && prompt->pos > 0)
		move_cursor(prompt, prompt->pos - 1, true);
	else if (nb_user_entry == 3 && user_entry[2] == 67 &&
			prompt->pos < prompt->total)
		move_cursor(prompt, prompt->pos + 1, true);
	else if (nb_user_entry == 3 && user_entry[2] == 72)
		move_cursor(prompt, 0, true);
	else if (nb_user_entry == 3 && user_entry[2] == 70)
		move_cursor(prompt, prompt->total, true);
	else if (nb_user_entry == 6 && user_entry[5] == 68)
		ft_cursor_word_left(prompt);
	else if (nb_user_entry == 6 && user_entry[5] == 67)
		ft_cursor_word_right(prompt);
	else if (nb_user_entry == 6 && user_entry[5] == 65)
		ft_cursor_up(prompt);
	else if (nb_user_entry == 6 && user_entry[5] == 66)
		ft_cursor_down(prompt);
	return (0);
}
