/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 22:38:46 by azybert           #+#    #+#             */
/*   Updated: 2018/07/05 05:52:09 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	selection_write(t_prompt *prompt, size_t start_pos)
{
	size_t	mem_pos;
	size_t	size;

	mem_pos = prompt->pos;
	move_cursor(prompt, 0, true);
	tputs(tgetstr("cd", NULL), 1, ft_putshit);

	size = (start_pos > mem_pos ? mem_pos : start_pos);
	write_data(prompt, prompt->line, size);
	move_cursor(prompt, size, true);

	tputs(tgetstr("mr", NULL), 1, ft_putshit);
	write_data(prompt, prompt->line + prompt->pos,
			(start_pos > mem_pos ? start_pos - mem_pos + 1 : mem_pos - start_pos));

	tputs(tgetstr("me", NULL), 1, ft_putshit);
	move_cursor(prompt, (start_pos > mem_pos ? start_pos + 1 : mem_pos), true);
	size = prompt->total - prompt->pos;
	write_data(prompt, prompt->line + prompt->pos, size);

	move_cursor(prompt, mem_pos, true);
}

void	selection_mode(t_prompt *prompt, t_stat_data *stat_data)
{
	char	user_entry[7];
	size_t	start_pos;
	int		nb_user_entry;
	int		end;
	int		loop;

	if (!prompt->total)
		return ;
	if (prompt->pos == prompt->total)
		prompt->pos--;
	start_pos = prompt->pos;
	end = 0;
	while (end != 1)
	{
		selection_write(prompt, start_pos);
		ft_bzero(user_entry, 7);
		nb_user_entry = read(1, user_entry, 6);
		if (nb_user_entry == 6)
			ft_flush(prompt);

		if (nb_user_entry == 3 && user_entry[2] == 65)
			ft_cursor_up(prompt);
		else if (nb_user_entry == 3 && user_entry[2] == 66)
			ft_cursor_down(prompt);
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
		else if (nb_user_entry == 1 && user_entry[0] == 'c')
		{
			free(stat_data->copied);
			stat_data->copied = (start_pos > prompt->pos ?
					ft_strndup(prompt->line + prompt->pos, start_pos - prompt->pos + 1) :
					ft_strndup(prompt->line + start_pos, prompt->pos - start_pos + 1));
		}
		else if (nb_user_entry == 1 && user_entry[0] == 127)
		{
			if (start_pos > prompt->pos)
			{
				loop = start_pos - prompt->pos;
				while (loop--)
					prompt_backdel(prompt);
			}
			else
			{
				loop = prompt->pos - start_pos;
				if (loop)
					prompt_backdel(prompt);
				while (loop--)
					prompt_delete(prompt);
			}
		}
		else if (nb_user_entry == 1 && user_entry[0] == 27)
		{
			selection_write(prompt, prompt->pos);
			return ;
		}
	}
}
