/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windata.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 20:32:22 by kernel_pani       #+#    #+#             */
/*   Updated: 2018/05/11 12:31:10 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

struct s_win	*init_windata(void)
{
	struct s_win	*sw;
	struct winsize	w;

	if (!(sw = malloc(sizeof(struct s_win))))
		ft_exit(3);
	ioctl(2, TIOCGWINSZ, &w);
	sw->win_col = w.ws_col;
	sw->win_row = w.ws_row;
	return (sw);
}
