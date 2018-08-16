/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_le_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 06:10:10 by azybert           #+#    #+#             */
/*   Updated: 2018/08/16 21:46:22 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static void	ignore_sig(int sig)
{
	UNUSED(sig);
}

static void	quit_mode(int sig)
{
	UNUSED(sig);
	g_prpt->end = 1;
	termanip(33);
}

void		ignore_handle(void)
{
	signal(SIGINT, quit_mode);
	signal(SIGWINCH, ignore_sig);
}
