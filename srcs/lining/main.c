/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:19:24 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/29 23:46:00 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

int		dispatch_tasks(struct s_line_data *ld, char *t, int *index)
{
	if (t[0] == 59 && t[1] == 50)
	{
		if (t[2] == 67)
			skip_word_right(ld);
		if (t[2] == 68 && ld->c - 1 >= 0)
			skip_word_left(ld);
		if (t[2] == 66)
			write_history_file(ld->history);
	}
	else if (t[0] == 27)
		manage_movement(t, ld, index);
	else if ((t[0] >= 1 && t[0] <= 31) || t[0] == 127)
		manage_controls(t[0], ld, index);
	else
		manage_buffer(ld, t, index);
	return (0);
}

int		main(int argc, char **argv)
{
	char				t[4];
	int					f;
	struct s_line_data	*ld;
	int					index;
	t_list				*history;

	if (argc == 2)
		set_debug_tty(argv[1], -1);
	index = 0;
	get_infoterm();
	ld = init_linedata();
	history = NULL;
	cursor_pos(ld);
	while (1)
	{
		if ((f = read(1, t, 3)) != -1)
		{
			t[f] = '\0';
			if (t[0] == 27 && t[1] == 91 && t[2] == 49)
				continue ;
			if (t[0] == 10)
			{
				manage_validation(ld, &history);
				index = 0;
			}
			dispatch_tasks(ld, t, &index);
		}
	}
	return (0);
}
