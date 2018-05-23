/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:26:10 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/23 17:57:47 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lining.h"
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>

struct termios t;

void	get_infoterm(void)
{
	struct termios terminal;

	if ((tgetent(NULL, getenv("TERM"))) == -1)
	{
		ft_putendl("Couldn't retrieve term data.");
		return ;
	}
	if (tcgetattr(0, &t) == -1)
	{
		ft_putendl("Couldn't retrieve term attributes.");
		return ;
	}
	terminal = t;
	terminal.c_lflag &= ~(ICANON);
	terminal.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSADRAIN, &terminal) == -1)
	{
		ft_putendl("Couldn't set new data.");
		return ;
	}
	else
		ft_putendl("<3");
	return ;
}

int		main(void)
{
	size_t		f;
	int			i;

	i = 0;
	f = 0;
	get_infoterm();
	while (read(0, &f, sizeof(f)))
	{
		printf("%zu\n", f);
		f = 0;
	}
	return (0);
}
