/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_e_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 03:46:15 by azybert           #+#    #+#             */
/*   Updated: 2018/07/08 03:14:40 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	reverse_handle(void)
{
	signal(SIGINT, NULL);
	signal(SIGWINCH, NULL);
}

void	handle_resize(int sig)
{
	struct winsize	w;

	UNUSED(sig);
	tputs(tgetstr("cl", NULL), 0, ft_putshit);
	ioctl(0, TIOCGWINSZ, &w);
	prompt->size->x = w.ws_col;
	prompt->size->y = w.ws_row;
	write(1, "prompt> ", 8);
	get_cursor_pos(prompt->origin, prompt);
	write_data(prompt, prompt->line, prompt->total);
	move_cursor(prompt, prompt->pos, true);
}

void	handle_int(int sig)
{
	UNUSED(sig);
	if (prompt->size->y - 1 == prompt->origin->y +
			(prompt->origin->x + prompt->total) / prompt->size->x)
		tputs(tgetstr("sf", NULL), 1, ft_putshit);
	move_cursor(prompt, prompt->total + prompt->size->x -
			((prompt->total + prompt->origin->x) % prompt->size->x), false);
	write(1, "prompt> ", 8);
	get_cursor_pos(prompt->origin, prompt);
	free(prompt->line);
	if (!(prompt->line = ft_strdup("\0")))
		exit(1);
	free(prompt->buf);
	prompt->buf = NULL;
	prompt->total = 0;
	prompt->pos = 0;
}

void	handle_sig(void)
{
	signal(SIGINT, handle_int);
	signal(SIGWINCH, handle_resize);
}
