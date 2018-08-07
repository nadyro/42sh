/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_le_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 06:10:10 by azybert           #+#    #+#             */
/*   Updated: 2018/08/06 06:19:50 by azybert          ###   ########.fr       */
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
	prompt->end = 1;
	termanip(33);
}

void		ignore_handle(void)
{
	signal(SIGINT, quit_mode);
	signal(SIGWINCH, ignore_sig);
}
