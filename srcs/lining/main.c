/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:19:24 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/04/23 15:40:52 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

int		fprint_char(int c)
{
	ft_putchar_fd(c, 2);
	return (0);
}

void	manage_movement(char *t, struct s_line_data *ld, int *index)
{
	if (t[1] == 91)
	{
		if (t[2] == 68)
			move_left(index, ld);
		if (t[2] == 67)
			move_right(index, ld);
	}
}

void	manage_validation(char *t, int *s, struct s_line_data *ld)
{
	char	*tmp_join;

	(void)t;
	if (ld->old_content == NULL)
		ld->old_content = "";
	ld->buffer[*s] = '\0';
	*s = 0;
	tmp_join = ft_strjoin(ld->old_content, ld->buffer);
	ld->content = ft_strdup(tmp_join);
	ft_strdel(&tmp_join);
	ld->length = ft_strlen(ld->content);
	ft_putchar('\n');
	ft_putendl("Final Result : ");
	print_line_data(ld);
}

int		main(void)
{
	char				t[4];
	int					f;
	int					index;
	int					s;
	struct s_line_data	*ld;

	s = 0;
	index = 0;
	get_infoterm();
	ld = init_linedata();
	ft_putstr("$>");
	tputs(tgetstr("cl", NULL), 1, fprint_char);
	while (1)
	{
		if ((f = read(1, t, 3)) != -1)
		{
			t[f] = '\0';
			if (t[0] == 27)
				manage_movement(t, ld, &index);
			else
			{
				if (t[0] == 10)
					manage_validation(t, &s, ld);
				s++;
				if (s >= BUFFER)
				{
					ld->buffer[s - 1] = '\0';
					reallocate_mem_line(&s, ld);
				}
				ld->buffer[s - 1] = t[0];
				index = ft_strlen(ld->buffer);
				++ld->cd->col;
				ft_putchar(t[0]);
			}
		}
	}
	return (0);
}
