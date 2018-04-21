/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcare.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:20:41 by kernel_pani       #+#    #+#             */
/*   Updated: 2018/04/21 21:30:22 by kernel_pa        ###   ########.fr       */
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
