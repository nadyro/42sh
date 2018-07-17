/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_le_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 06:10:10 by azybert           #+#    #+#             */
/*   Updated: 2018/07/17 22:48:39 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	ignore_sig(int sig)
{
	UNUSED(sig);
}

void	ignore_handle(void)
{
	signal(SIGINT, ignore_sig);
	signal(SIGWINCH, ignore_sig);
}
