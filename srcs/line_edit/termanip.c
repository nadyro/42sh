/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:21:10 by azybert           #+#    #+#             */
/*   Updated: 2018/07/07 05:02:21 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	termanip_aux(int sig, struct termios shell, struct termios old)
{
	if (sig == 3)
	{
		tcgetattr(0, &shell);
		shell.c_cc[VMIN] = (shell.c_cc[VMIN] == 1 ? 0 : 1);
		shell.c_cc[VTIME] = 0;
		tcsetattr(0, TCSADRAIN, &shell);
	}
	else if (sig == 4)
	{
		tcgetattr(0, &shell);
		shell.c_cc[VTIME] += 1;
		tcsetattr(0, TCSADRAIN, &shell);
	}
	else if (sig == 5)
	{
		tcsetattr(0, TCSADRAIN, &old);
	}
}

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
	else
	{
		termanip_aux(sig, shell, old);
	}
}
