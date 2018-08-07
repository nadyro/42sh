/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 22:38:46 by azybert           #+#    #+#             */
/*   Updated: 2018/08/07 13:09:23 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static void	selection_delete(t_prompt *prompt, size_t start_pos)
{
	int	loop;

	if (start_pos > prompt->pos)
	{
		loop = start_pos - prompt->pos + 1;
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
	return ;
}

static void	selection_write(t_prompt *prompt, size_t start_pos)
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
			(start_pos > mem_pos ?
			start_pos - mem_pos + 1 : mem_pos - start_pos));
	tputs(tgetstr("me", NULL), 1, ft_putshit);
	move_cursor(prompt, (start_pos > mem_pos ? start_pos + 1 : mem_pos), true);
	size = prompt->total - prompt->pos;
	write_data(prompt, prompt->line + prompt->pos, size);
	move_cursor(prompt, mem_pos, true);
}

static int	selection_tree_aux(t_prompt *prompt, t_stat_data *stat_data,
		char *user_entry, size_t start_pos)
{
	if (user_entry[0] == 'c' || user_entry[0] == 'x')
	{
		free(stat_data->copied);
		stat_data->copied = (start_pos > prompt->pos ?
				ft_strndup(prompt->line + prompt->pos,
					start_pos - prompt->pos + 1) :
				ft_strndup(prompt->line + start_pos,
					prompt->pos - start_pos + 1));
		selection_write(prompt, prompt->pos);
		if (user_entry[0] == 'x')
			selection_delete(prompt, start_pos);
	}
	else if (user_entry[0] == 127)
		selection_delete(prompt, start_pos);
	else if (user_entry[0] == 27 || prompt->end == 1)
		selection_write(prompt, prompt->pos);
	else
		return (0);
	handle_sig();
	(prompt->end ? termanip(33) : 0);
	prompt->end = 0;
	return (1);
}

static int	selection_tree(t_prompt *prompt, int nb_user_entry,
		char *user_entry)
{
	if (nb_user_entry == 3 && user_entry[2] == 65)
		ft_cursor_up(prompt);
	else if (nb_user_entry == 3 && user_entry[2] == 66)
		ft_cursor_down(prompt);
	else if (nb_user_entry == 3 && user_entry[2] == 68)
		(prompt->pos > 0 ? move_cursor(prompt, prompt->pos - 1, true) : 0);
	else if (nb_user_entry == 3 && user_entry[2] == 67 &&
			prompt->pos < prompt->total)
		(prompt->pos < prompt->total - 1 ?
		move_cursor(prompt, prompt->pos + 1, true) : 0);
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
		return (1);
	return (0);
}

void		selection_mode(t_prompt *prompt, t_stat_data *stat_data)
{
	char	user_entry[7];
	size_t	start_pos;
	int		nb_user_entry;

	ignore_handle();
	prompt->pos += (prompt->pos == prompt->total ? -1 : 0);
	start_pos = prompt->pos;
	while (1)
	{
		selection_write(prompt, start_pos);
		ft_bzero(user_entry, 7);
		nb_user_entry = read(0, user_entry, 6);
		if (user_entry[0] == 12)
		{
			tputs(tgetstr("cl", NULL), 0, ft_putshit);
			write(1, prompt->disp, ft_strlen(prompt->disp));
			prompt->origin->y = 0;
		}
		(nb_user_entry == 6 ? ft_flush(prompt) : 0);
		(prompt->buf ? ft_strdel(&prompt->buf) : 0);
		if (selection_tree(prompt, nb_user_entry, user_entry))
			if (selection_tree_aux(prompt, stat_data, user_entry, start_pos))
				return ;
	}
}
