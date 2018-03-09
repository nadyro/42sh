/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 22:39:02 by azybert           #+#    #+#             */
/*   Updated: 2018/03/09 16:00:50 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>

int         ft_putshit(int c)
{
	return (write(0, &c, 1));
}


void    termanip(int sig)
{
	static struct termios   shell;
	static struct termios   old;

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
		tcsetattr(0, TCSADRAIN, &old);
		exit(0);
	}
}

void	boucle()
{
	char buf[6];
	buf[5] = '\0';
	buf[2] = ';';
	int k = 0;
	while (k != 2)
		k += read(0, &buf[k], 2);
	k = 3;
	while (k != 5)
		k += read(0, &buf[k], 2);
	int x = atoi(&buf[0]);
	int y = atoi(&buf[3]);
	char *res;
	 
	res = tgetstr("cm", NULL);
	tputs(tgoto(res, x, y), 1, ft_putshit);
	printf("\033[6n");
	//read(1, buf, 6);
	//write(1, buf, 6);
	//read(0, buf, 1);
}

int	main()
{
	//char	*line;
	char	*name_term;

	if ((name_term = getenv("TERM")) == NULL)
	{
		write(2, "Please set the environment variable TERM\n", 41);
		return (-1);
	}
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	termanip(0);
	signal(SIGINT, termanip); //call signal functions later
	boucle();
	termanip(1);
	return (0);
}
