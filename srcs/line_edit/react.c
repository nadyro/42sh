/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   react.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 13:39:16 by azybert           #+#    #+#             */
/*   Updated: 2018/07/21 15:19:39 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void		secure_stock(t_prompt *prompt, char *to_stock)
{
	int		mem;

	if (to_stock == NULL || to_stock[0] == '\0')
	{
		if (!(prompt->line = ft_strdup("\0")))
			exit(1);
		return ;
	}
	mem = 0;
	while (to_stock[mem])
		prompt_stock(prompt, &to_stock[mem++]);
}

int			data_react(t_prompt *prompt)
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
		if (!(prompt->buf = ft_strdup(&prompt->buf[mem + 1])))
			exit(1);
		free(to_free);
		tputs(tgetstr("ce", NULL), 1, ft_putshit);
		return (1);
	}
	(prompt->buf[0] == 4 && prompt->total == 0 ? termanip(42) : 0);
	free(prompt->buf);
	prompt->buf = NULL;
	return (0);
}

static void	esc_react_aux(t_prompt *prompt, int nb_user_entry, char *user_entry,
				t_stat_data *stat_data)
{
	if (nb_user_entry == 3 && user_entry[2] == 65)
		history_next(prompt, stat_data);
	else if (nb_user_entry == 3 && user_entry[2] == 66)
		history_prev(prompt, stat_data);
	else if (nb_user_entry == 2 && user_entry[0] == 27 &&
			user_entry[1] == 'S' && prompt->total > 0)
		selection_mode(prompt, stat_data);
	else if (nb_user_entry == 2 && user_entry[0] == 27 &&
			user_entry[1] == 'V' && stat_data->copied != NULL)
		secure_stock(prompt, stat_data->copied);
	else if (nb_user_entry == 2 && user_entry[0] == 27 &&
			user_entry[1] == 'R' && prompt->history)
		search_mode(prompt, stat_data);
}

void		esc_react(t_prompt *prompt, int nb_user_entry, char *user_entry,
				t_stat_data *stat_data)
{
	if (nb_user_entry == 1 && user_entry[0] == 127 && prompt->pos > 0)
		prompt_delete(prompt);
	else if (nb_user_entry == 4 && user_entry[3] == 126 &&
			prompt->pos < prompt->total)
		prompt_backdel(prompt);
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
	else
		esc_react_aux(prompt, nb_user_entry, user_entry, stat_data);
}
