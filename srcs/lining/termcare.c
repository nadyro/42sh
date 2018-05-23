/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcare.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:22:39 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/23 23:04:05 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

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
	terminal.c_cc[VMIN] = 1;
	terminal.c_cc[VTIME] = 1;
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
