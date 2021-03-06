/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termanip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:21:10 by azybert           #+#    #+#             */
/*   Updated: 2018/08/16 18:59:17 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"
#include "builtins.h"

static void	termanip_aux(int sig, struct termios shell, struct termios old)
{
	if (sig == 33)
	{
		tcgetattr(0, &shell);
		shell.c_cc[VMIN] = (shell.c_cc[VMIN] == 1 ? 0 : 1);
		shell.c_cc[VTIME] = 0;
		tcsetattr(0, TCSANOW, &shell);
	}
	else if (sig == 34)
	{
		tcgetattr(0, &shell);
		shell.c_cc[VTIME] += (shell.c_cc[VTIME] == 24 ? 0 : 2);
		tcsetattr(0, TCSANOW, &shell);
	}
	else if (sig == 35)
		tcsetattr(0, TCSANOW, &old);
	else
		tcsetattr(0, TCSANOW, &old);
}

void		termanip(int sig)
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
		tcsetattr(0, TCSANOW, &shell);
	}
	else if (sig == -1)
	{
		tcsetattr(0, TCSANOW, &old);
		sh_close(0, "");
	}
	else
	{
		termanip_aux(sig, shell, old);
	}
}
