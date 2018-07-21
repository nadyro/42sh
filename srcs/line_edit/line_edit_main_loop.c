/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit_main_loop.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:28:12 by azybert           #+#    #+#             */
/*   Updated: 2018/07/21 15:18:39 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_line_edit.h"

void		ft_flush(t_prompt *prompt)
{
	char	user_entry[4096];
	char	*to_free;

	termanip(3);
	ft_bzero(user_entry, 4096);
	while (read(1, user_entry, 4095) > 0)
	{
		to_free = prompt->buf;
		prompt->buf = ft_strjoin(prompt->buf, user_entry);
		free(to_free);
		ft_bzero(user_entry, 4095);
		termanip(4);
	}
	termanip(3);
}

char		*line_edit_main_loop_aux(t_prompt *prompt, t_stat_data *stat_data,
		char *to_return)
{
	char	user_entry[7];
	int		nb_user_entry;
	t_node	*matches;
	char	**matches_tab;
	int		i;

	matches = NULL;
	matches_tab = NULL;
	i = 0;
	while (to_return == NULL)
	{
		if (prompt->buf != NULL && data_react(prompt))
			to_return = quotes_managing(prompt, to_return);
		else
		{
			ft_bzero(user_entry, 7);
			nb_user_entry = read(1, user_entry, 6);
			if (user_entry[0] == 27 || user_entry[0] == 127)
				esc_react(prompt, nb_user_entry, user_entry, stat_data);
			else if (user_entry[0] == 9)
			{
				matches = fetch_names(prompt->line);
				while (matches && matches->prev != NULL)
					matches = matches->prev;
				matches_tab = lst_to_array(matches);
				while (matches_tab[i])
				ft_putendl(matches_tab[i++]);
				i = 0;
			}
			else
			{
				((prompt->buf = ft_strdup(user_entry)) != NULL ? 0 : exit(1));
				if (nb_user_entry == 6)
					ft_flush(prompt);
				if (data_react(prompt))
					to_return = quotes_managing(prompt, to_return);
			}
		}
	}
	return (to_return);
}

char		*line_edit_main_loop(char *d_prompt)
{
	char				*to_return;
	static t_stat_data	*stat_data = NULL;

	termanip(0);
	write(1, d_prompt, ft_strlen(d_prompt));
	stat_data = (stat_data ? stat_data : malloc_stat());
	prompt = malloc_prompt(prompt, stat_data, d_prompt);
	handle_sig();
	prompt->buf = stat_data->overage;
	to_return = NULL;
	to_return = line_edit_main_loop_aux(prompt, stat_data, to_return);
	stat_data->overage = (prompt->buf ? ft_strdup(prompt->buf) : NULL);
	free(stat_data->old_line);
	stat_data->old_line = NULL;
	if (to_return[0] != '\n' || to_return[1] != '\0')
		add_to_history(to_return, stat_data);
	else
		stat_data->old_line =
			ft_itoa(prompt->origin->x + (prompt->origin->y + 1) * 100000);
	stat_data->current = stat_data->history;
	free_prompt(prompt);
	reverse_handle();
	termanip(5);
	return (to_return);
}
