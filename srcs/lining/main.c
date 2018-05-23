/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:19:24 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/23 21:34:07 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

void	skip_word_right(struct s_line_data *ld)
{
	int		i;
	int		y;
	char	*go_to;

	i = ld->cd->pos_x;
	y = 0;
	while (ld->buffer[i] != '\0')
	{
		while (ld->buffer[i] && (ld->buffer[i] == ' ' || ld->buffer[i] == '\n' || ld->buffer[i] == '\t'))
			i++;
		while (ld->buffer[i] && ld->buffer[i] != ' ' && ld->buffer[i] != '\n' && ld->buffer[i] != '\t')
			i++;
			y = 1;
			break ;
		i++;
	}
	if (y == 1)
	{
		go_to = tgoto(tgetstr("cm", NULL), COLSTART + i, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		cursor_pos(ld);
	}
}

void	skip_word_left(struct s_line_data *ld)
{
	int		i;
	int		y;
	char	*go_to;

	i = ld->cd->pos_x;
	y = 0;
	while (i != COLSTART)
	{
		while (i >= COLSTART && (ld->buffer[i] == ' ' || ld->buffer[i] == '\n' || ld->buffer[i] == '\t'))
			i--;
		while (i >= COLSTART && ld->buffer[i] != ' ' && ld->buffer[i] != '\n' && ld->buffer[i] != '\t')
			i--;
		y = 1;
		break ;
		i--;
	}
	if (y == 1)
	{
		go_to = tgoto(tgetstr("cm", NULL), COLSTART + i, ld->cd->pos_y);
		tputs(go_to, 1, fprint_char);
		cursor_pos(ld);
	}
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
		if((f = read(1, t, 3)) != -1)
		{
			t[f] = '\0';
			if (t[0] == 27 && t[1] == 91 && t[2] == 49)
				continue ;
			cursor_pos(ld);
			if (t[0] == 59 && t[1] == 50)
			{
				if (t[2] == 67)
					skip_word_right(ld);
				if (t[2] == 68)
					skip_word_left(ld);
			}
			else if (t[0] == 27)
				manage_movement(t, ld);
			else if (t[0] == 10)
			{
				manage_validation(ld);
				index = 0;
			}
			else if ((t[0] >= 1 && t[0]<= 31) || t[0] == 127)
				manage_controls(t[0], ld, &index);
			else
			{
				manage_buffer(ld, t, &index);
			}
		}
		else
			exit(0);
	}
	return (0);
}
