/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:21:10 by azybert           #+#    #+#             */
/*   Updated: 2018/03/31 22:38:54 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh_line_edit.h"

/*void	handle_resize(int sig)
{
	struct winsize	w;
	
	tputs(tgetstr("cl", NULL), 0, ft_putshit);
	ioctl(0, TIOCGWINSZ, &w);
	prompt->size->x = w.ws_col;
	prompt->size->y = w.ws_row;
	write(1, "prompt> ", 8);
	get_cursor_pos(prompt->origin);
	write_data(prompt, prompt->line, prompt->total);
	move_cursor(prompt, prompt->pos, true);
	signal(sig, handle_resize);
}

void	handle_int(int sig)
{
	move_cursor(prompt, prompt->total + prompt->size->x -
			((prompt->total + prompt->origin->x) % prompt->size->x), false);
	write(1, "prompt> ", 8);
	free_prompt(prompt);
	malloc_prompt(prompt);
	signal(sig, handle_int);
}

void	handle_sig(void)
{
	signal(SIGINT, handle_int);
	signal(SIGWINCH, handle_resize);
}*/

void	termanip(int sig)
{
	static struct termios	shell;
	static struct termios	old;

	if (sig == 0)
	{
		tcgetattr(0, &shell);
		tcgetattr(0, &old);
		shell.c_oflag &= ~(OPOST);
		shell.c_lflag &= ~(ICANON);
		shell.c_lflag &= ~(ECHO);
		shell.c_cc[VMIN] = 1;
		shell.c_cc[VTIME] = 0;
		tcsetattr(0, TCSADRAIN, &shell);
	}
	else if (sig == 2)
	{
		tcsetattr(0, TCSADRAIN, &old);
		exit(0);
	}
	else if (sig == 3)
	{
		shell.c_cc[VMIN] = (shell.c_cc[VMIN] == 1 ? 0 : 1);
		shell.c_cc[VTIME] = 0;
		tcsetattr(0, TCSADRAIN, &shell);
	}
	else if (sig == 4)
	{
		shell.c_cc[VTIME] += 1;
		tcsetattr(0, TCSADRAIN, &shell);
	}
}
