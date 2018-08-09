/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit_main_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:28:12 by azybert           #+#    #+#             */
/*   Updated: 2018/08/08 23:37:45 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

static char	*overbuf(t_prompt *prompt, int nb_user_entry, char *user_entry)
{
	char	*to_return;

	to_return = NULL;
	((prompt->buf = ft_strdup(user_entry)) != NULL ? 0 : exit(1));
	if (nb_user_entry == 6)
		ft_flush(prompt);
	if (data_react(prompt))
		if (!(to_return = ft_strdup(prompt->line)))
			exit(0);
	return (to_return);
}

static char	*line_edit_main_loop_aux(t_prompt *prompt, t_stat_data *stat_data,
		char *to_return)
{
	char	user_entry[7];
	int		nb_user_entry;

	while (to_return == NULL)
		if (prompt->buf != NULL && data_react(prompt))
			((to_return = ft_strdup(prompt->line)) ? 0 : exit(0));
		else
		{
			(prompt->origin->y == 0xffffffffffffffff ? prompt_clean() : 0);
			ft_bzero(user_entry, 7);
			nb_user_entry = read(0, user_entry, 6);
			if (prompt->end == 1)
				return (NULL);
			if (user_entry[0] == 27 || user_entry[0] == 127
					|| user_entry[0] == 9)
				esc_react(prompt, nb_user_entry, user_entry, stat_data);
			else if (!ft_isprint(user_entry[0]) && user_entry[0] != '\n')
				sig_react(prompt, user_entry[0]);
			else
				to_return = overbuf(prompt, nb_user_entry, user_entry);
		}
	return (to_return);
}

char		*line_edit_main_loop(char *d_prompt, t_node *history)
{
	char				*to_return;
	static t_stat_data	*stat_data = NULL;

	termanip(0);
	stat_data = (stat_data ? stat_data : malloc_stat());
	prompt = malloc_prompt(prompt, stat_data, d_prompt);
	write(1, d_prompt, ft_strlen(d_prompt));
	prompt->history = history;
	handle_sig();
	prompt->origin->x = (ft_strlen(prompt->disp) > 10 ?
		ft_strlen(prompt->disp) - 9 : ft_strlen(prompt->disp));
	prompt->buf = stat_data->overage;
	to_return = NULL;
	to_return = line_edit_main_loop_aux(prompt, stat_data, to_return);
	stat_data->overage = (prompt->buf ? ft_strdup(prompt->buf) : NULL);
	reverse_handle();
	termanip(35);
	free_prompt(prompt);
	return (to_return);
}
