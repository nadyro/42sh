/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windata.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 16:56:22 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/06/18 16:30:10 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

struct s_win	*init_windata(void)
{
	struct s_win	*sw;
	struct winsize	w;

	if (!(sw = malloc(sizeof(struct s_win))))
		return (NULL);
	if ((ioctl(0, TIOCGWINSZ, &w) != -1))
	{
		sw->win_col = w.ws_col;
		sw->win_row = w.ws_row;
		return (sw);
	}
	else
		return (NULL);
}
