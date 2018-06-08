/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windata.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 16:56:22 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/24 16:56:28 by nsehnoun         ###   ########.fr       */
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