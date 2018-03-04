/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:21:10 by azybert           #+#    #+#             */
/*   Updated: 2018/03/03 18:55:06 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void    termanip(int sig)
{
	static struct termios   shell;
	static struct termios   old;

	if (sig == 0)
	{
		tcgetattr(0, &shell);
		tcgetattr(0, &old);
		//shell.c_oflag &= ~(OPOST);
		shell.c_lflag &= ~(ICANON);
		shell.c_lflag &= ~(ECHO);
		shell.c_cc[VMIN] = 1;
		shell.c_cc[VTIME] = 0;
		tcsetattr(0, TCSADRAIN, &shell);
	}
	else
	{
		tcsetattr(0, TCSADRAIN, &old);
		exit(0);
	}
}
