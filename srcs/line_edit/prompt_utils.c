/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_prpt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 07:30:34 by azybert           #+#    #+#             */
/*   Updated: 2018/08/10 16:50:35 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void	ft_flush(t_g_prpt *g_prpt)
{
	char	user_entry[4096];
	char	*to_free;

	ignore_handle();
	termanip(33);
	ft_bzero(user_entry, 4096);
	while (read(0, user_entry, 4095) > 0 && !(g_prpt->end))
	{
		to_free = g_prpt->buf;
		g_prpt->buf = ft_strjoin(g_prpt->buf, user_entry);
		if (g_prpt->buf == NULL)
		{
			g_prpt->buf = to_free;
			g_prpt->end = 1;
		}
		else
		{
			free(to_free);
			ft_bzero(user_entry, 4095);
			termanip(34);
		}
	}
	termanip(33);
	handle_sig();
}

void	g_prpt_clean(void)
{
	free(g_prpt->line);
	if (!(g_prpt->line = ft_strdup("\0")))
		exit(1);
	g_prpt->pos = 0;
	g_prpt->total = 0;
	g_prpt->current = NULL;
	term_clear();
}
