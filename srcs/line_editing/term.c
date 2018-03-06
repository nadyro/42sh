/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:21:10 by azybert           #+#    #+#             */
<<<<<<< HEAD:line_editing/term.c
/*   Updated: 2018/03/04 22:58:42 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"
=======
/*   Updated: 2018/03/04 22:41:52 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/21sh.h"
>>>>>>> a2e53d1e55ba2763625a0d94c0adc5e4cb0e80a7:srcs/line_editing/term.c

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
