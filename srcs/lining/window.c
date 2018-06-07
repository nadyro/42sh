/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:36:46 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/31 17:50:55 by nsehnoun         ###   ########.fr       */
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
		window->rows = ws.ws_row;
		return (window);
	}
	else
		return (NULL);
}
