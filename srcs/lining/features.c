/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:15:59 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/24 16:52:11 by nsehnoun         ###   ########.fr       */
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

void	manage_deletion(struct s_line_data *ld)
{
	int		i;
	int		y;
	char	*tmp;
	int		to_del;

	i = 0;
	y = 0;
	to_del = ld->cd->pos_x - 1;
	if (!(tmp = ft_strnew(ft_strlen(ld->buffer) - 1)))
		ft_exit(3);
	while (ld->buffer[y] != '\0')
	{
		(y == to_del ? y++ : y);
		tmp[i++] = ld->buffer[y++];
	}
	ft_bzero(ld->buffer, ft_strlen(ld->buffer));
	ft_strncpy(ld->buffer, tmp, ft_strlen(tmp));
	ld->current_size = ft_strlen(ld->buffer);
	ft_strdel(&tmp);
	if (ld->cd->pos_x - 1 >= 0)
		write_fromstart(ld, 1);
	cursor_pos(ld);
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
	char	*str_pos;
	int		i;

	str_pos = ft_strnew(20);
	i = 0;
	write(1, "\033[6n", 4);
	while (i < 20)
		str_pos[i++] = '\0';
	if ((read(1, str_pos, 20)) != -1)
	{
		ld->cd->pos_y = ft_atoi(&str_pos[2]) - 1;
		i = 0;
		while (str_pos[i] != '\0')
		{
			if (str_pos[i] == ';')
				break ;
			i++;
		}
		ld->cd->x = ft_atoi(&str_pos[i + 1]) - 1;
		ld->cd->pos_x = ld->cd->x - COLSTART;
		i = 0;
		while (i < 20)
			str_pos[i++] = '\0';
	}
	free(str_pos);
}
