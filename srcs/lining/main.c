/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:19:24 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/15 20:04:11 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

void	manage_movement(char *t, struct s_line_data *ld)
{
	if (t[1] == 91)
	{
		if (t[2] == 68)
			move_left(ld);
		if (t[2] == 67)
			move_right(ld);
		if (t[2] == 66)
			move_down(ld);
	}
}

void	manage_validation(struct s_line_data *ld)
{
	char	*tmp_join;

	if (ld->old_content == NULL)
		ld->old_content = "";
	tmp_join = ft_strjoin(ld->old_content, ld->buffer);
	ld->content = ft_strdup(tmp_join);
	ft_strdel(&tmp_join);
	ld->length = ft_strlen(ld->content);
	ft_putchar('\n');
	ft_putendl("Final Result : ");
	ft_putchar('\n');
	print_line_data(ld);
	clean_linedata(ld);
	ft_putscolors("$> 42sh", BCYAN);
	ft_putscolors(" ~> ", MAGENTA);
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
	i = 0;
	while (i < 512)
		str_pos[i++] = '\0';
}

int		main(void)
{
	char				t[4];
	int					f;
	struct s_line_data	*ld;
	int					index;

	index = 0;
	get_infoterm();
	ld = init_linedata();
	while (1)
	{
		if ((f = read(1, t, 3)) != -1)
		{
			cursor_pos(ld);
			t[f] = '\0';
			if (t[0] == 27)
				manage_movement(t, ld);
			else if (t[0] == 10)
			{
				manage_validation(ld);
				index = 0;
			}
			else if (t[0] >= 1 && t[0] <= 31)
				manage_controls(t[0], ld, &index);
			else
				manage_buffer(ld, t, &index);
		}
	}
	return (0);
}
