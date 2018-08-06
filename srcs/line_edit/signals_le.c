/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_e_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 03:46:15 by azybert           #+#    #+#             */
/*   Updated: 2018/08/06 03:17:23 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void		reverse_handle(void)
{
	signal(SIGINT, NULL);
	signal(SIGWINCH, NULL);
	signal(SIGHUP, NULL);
	signal(SIGQUIT, NULL);
	signal(SIGILL, NULL);
	signal(SIGABRT, NULL);
	signal(SIGKILL, NULL);
	signal(SIGSEGV, NULL);
	signal(SIGPIPE, NULL);
	signal(SIGTERM, NULL);
	signal(SIGSTOP, NULL);
}

void		term_clear(void)
{
	tputs(tgetstr("cl", NULL), 0, ft_putshit);
	write(1, prompt->disp, ft_strlen(prompt->disp));
	get_cursor_pos(prompt->origin, prompt);
	write_data(prompt, prompt->line, prompt->total);
	move_cursor(prompt, prompt->pos, true);
}

static void	handle_resize(int sig)
{
	struct winsize	w;

	UNUSED(sig);
	ioctl(0, TIOCGWINSZ, &w);
	prompt->size->x = w.ws_col;
	prompt->size->y = w.ws_row;
	term_clear();
}

void	handle_int(int sig)
{
	UNUSED(sig);
	if (prompt->size->y - 1 <= prompt->origin->y +
			(prompt->origin->x + ft_add_nl(prompt, prompt->total))
			/ prompt->size->x)
	{
		move_cursor(prompt, (prompt->size->y - prompt->origin->y) *
				prompt->size->x, false);
		tputs(tgetstr("sf", NULL), 1, ft_putshit);
	}
	move_cursor(prompt, prompt->total + prompt->size->x -
			(ft_add_nl(prompt, prompt->total +
			prompt->origin->x) % prompt->size->x), false);
	tputs(tgetstr("ce", NULL), 1, ft_putshit);
	prompt->end = 1;
	termanip(33);
}

void		handle_sig(void)
{
	signal(SIGINT, handle_int);
	signal(SIGWINCH, handle_resize);
	signal(SIGHUP, termanip);
	signal(SIGQUIT, termanip);
	signal(SIGILL, termanip);
	signal(SIGABRT, termanip);
	signal(SIGKILL, termanip);
	signal(SIGSEGV, termanip);
	signal(SIGPIPE, termanip);
	signal(SIGTERM, termanip);
	signal(SIGSTOP, termanip);
}
