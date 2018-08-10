/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit_main_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:28:12 by azybert           #+#    #+#             */
/*   Updated: 2018/08/10 16:50:35 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

t_g_prpt	*g_prpt;

static char	*overbuf(t_g_prpt *g_prpt, int nb_user_entry, char *user_entry)
{
	char	*to_return;

	to_return = NULL;
	((g_prpt->buf = ft_strdup(user_entry)) != NULL ? 0 : exit(1));
	if (nb_user_entry == 6)
		ft_flush(g_prpt);
	if (data_react(g_prpt))
		if (!(to_return = ft_strdup(g_prpt->line)))
			exit(0);
	return (to_return);
}

static char	*line_edit_main_loop_aux(t_g_prpt *g_prpt, t_stat_data *stat_data,
		char *to_return)
{
	char	user_entry[7];
	int		nb_user_entry;

	while (to_return == NULL)
		if (g_prpt->buf != NULL && data_react(g_prpt))
			((to_return = ft_strdup(g_prpt->line)) ? 0 : exit(0));
		else
		{
			(g_prpt->origin->y == 0xffffffffffffffff ? g_prpt_clean() : 0);
			ft_bzero(user_entry, 7);
			nb_user_entry = read(0, user_entry, 6);
			if (g_prpt->end == 1)
				return (NULL);
			if (user_entry[0] == 27 || user_entry[0] == 127
					|| user_entry[0] == 9)
				esc_react(g_prpt, nb_user_entry, user_entry, stat_data);
			else if (!ft_isprint(user_entry[0]) && user_entry[0] != '\n')
				sig_react(g_prpt, user_entry[0]);
			else
				to_return = overbuf(g_prpt, nb_user_entry, user_entry);
		}
	return (to_return);
}

char		*line_edit_main_loop(char *d_g_prpt, t_node *history)
{
	char				*to_return;
	static t_stat_data	*stat_data = NULL;

	termanip(0);
	stat_data = (stat_data ? stat_data : malloc_stat());
	g_prpt = malloc_g_prpt(g_prpt, stat_data, d_g_prpt);
	write(1, d_g_prpt, ft_strlen(d_g_prpt));
	g_prpt->history = history;
	handle_sig();
	g_prpt->origin->x = (ft_strlen(g_prpt->disp) > 10 ?
		ft_strlen(g_prpt->disp) - 9 : ft_strlen(g_prpt->disp));
	g_prpt->buf = stat_data->overage;
	to_return = NULL;
	to_return = line_edit_main_loop_aux(g_prpt, stat_data, to_return);
	stat_data->overage = (g_prpt->buf ? ft_strdup(g_prpt->buf) : NULL);
	reverse_handle();
	termanip(35);
	free_g_prpt(g_prpt);
	return (to_return);
}
