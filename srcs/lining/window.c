/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:36:46 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/06/07 20:43:02 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

struct s_window *init_window(void)
{
	struct winsize 	ws;
	struct s_window	*window;

	if (!(window = malloc(sizeof(struct s_window))))
		return (NULL);
	if ((ioctl(0, TIOCGWINSZ, &ws) != -1))
	{
		window->cols = ws.ws_col;
		ft_putnbr(window->cols);
		window->rows = ws.ws_row;
		return (window);
	}
	else
		return (NULL);
}
