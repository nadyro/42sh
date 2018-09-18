/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_le.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 03:46:15 by azybert           #+#    #+#             */
/*   Updated: 2018/08/16 21:47:19 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	reverse_handle(void)
{
	signal(SIGINT, sig_ignore);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGHUP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGILL, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	signal(SIGKILL, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGSTOP, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

void	term_clear(void)
{
	tputs(tgetstr("cl", NULL), 0, ft_putshit);
	get_cursor_pos(g_prpt->origin, g_prpt);
	write(1, g_prpt->disp, ft_strlen(g_prpt->disp));
	g_prpt->origin->x = (ft_strlen(g_prpt->disp) > 10 ?
			ft_strlen(g_prpt->disp) - 9 : ft_strlen(g_prpt->disp));
	write_data(g_prpt, g_prpt->line, g_prpt->total);
	move_cursor(g_prpt, g_prpt->pos, true);
}

void	handle_resize(int sig)
{
	struct winsize	w;

	UNUSED(sig);
	ioctl(0, TIOCGWINSZ, &w);
	g_prpt->size->x = w.ws_col;
	g_prpt->size->y = w.ws_row;
	term_clear();
}

void	handle_int(int sig)
{
	UNUSED(sig);
	if (g_prpt && g_prpt->size->y - 1 <= g_prpt->origin->y +
			(g_prpt->origin->x + ft_add_nl(g_prpt, g_prpt->total))
			/ g_prpt->size->x)
	{
		move_cursor(g_prpt, (g_prpt->size->y - g_prpt->origin->y) *
				g_prpt->size->x, false);
		tputs(tgetstr("sf", NULL), 1, ft_putshit);
	}
	move_cursor(g_prpt, g_prpt->total + g_prpt->size->x -
			(ft_add_nl(g_prpt, g_prpt->total +
				g_prpt->origin->x) % g_prpt->size->x), false);
	tputs(tgetstr("ce", NULL), 1, ft_putshit);
	g_prpt->end = 1;
	termanip(33);
}

void	handle_sig(void)
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
	signal(SIGTERM, sig_ignore);
	signal(SIGSTOP, termanip);
	signal(SIGTSTP, sig_ignore);
}
