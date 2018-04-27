/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:19:24 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/04/26 11:55:27 by kernel_pa        ###   ########.fr       */
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
		if (t[2] == 65)
			move_up(index, ld);
		if (t[2] == 66)
			move_down(index, ld);
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
	++ld->cd->row;
	ft_putchar('\n');
	ft_putendl("Final Result : ");
	ft_putchar('\n');
	print_line_data(ld);
	clean_linedata(ld);
	ft_putstr("\x1B[96m");
	ft_putstr("$> 42sh ~ ");
	ft_putstr("\x1B[0m");
}

void	cursor_pos(struct s_line_data *ld)
{
	char	str_pos[512];
	int		i;

	i = 0;
	write(1, "\033[6n", 4);
	while (i < 512)
		str_pos[i++] = '\0';
	read(1, str_pos, 512);
	ld->cd->pos_y = ft_atoi(&str_pos[2]) - 1;
	i = 0;
	while (str_pos[i] != ';')
		i++;
	ld->cd->x = ft_atoi(&str_pos[i + 1]) - 1;
	ld->cd->pos_x = ld->cd->x - COLSTART;
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
	ft_putstr("\x1B[96m");
	ft_putstr("$> 42sh ~ ");
	ft_putstr("\x1B[0m");
	while (1)
	{
		if ((f = read(1, t, 3)) != -1)
		{
			cursor_pos(ld);
			t[f] = '\0';
			if (t[0] == 27)
				manage_movement(t, ld, &index);
			else
			{
				if (t[0] == 10)
					manage_validation(t, &s, ld);
				else
				{
					cursor_pos(ld);
					tputs(tgoto(tgetstr("cm", NULL), ld->cd->x, ld->cd->pos_y), 1, fprint_char);
					if (s == BUFFER - 1)
					{
						ld->buffer[s] = '\0';
						reallocate_mem_line(&s, ld);
					}
					ld->buffer[s] = t[0];
					ld->current_size = ft_strlen(ld->buffer);
					index = ft_strlen(ld->buffer);
					if ((ld->cd->pos_x + 1) < ld->current_size)
						update_linedata(t[0], ld);
					else
					{
						ft_putstr("\x1B[32m");
						ft_putchar(t[0]);
						ft_putstr("\x1B[0m");
					}
					s++;
				}
			}
		}
	}
	return (0);
}
