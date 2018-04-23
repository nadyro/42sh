/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:45:11 by kernel_pani       #+#    #+#             */
/*   Updated: 2018/04/21 23:00:03 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

int	fprint_char(int c)
{
	ft_putchar_fd(c, 2);
	return (0);
}

void	manage_movement(char *t, struct line_data *ld, int *index)
{
	if (t[1] == 91)
	{
		if (t[2] == 68)
			move_left(index, ld);
		if (t[2] == 67)
			move_right(index, ld);
	}
}

void	manage_validation(char *t, int *s, struct line_data *ld)
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

int	main(void)
{
	char	t[4];
	int	f;
	int	index;
	int	s;
	struct	line_data *ld;

	s = 0;
	index = 0;
	get_infoterm();
	ld = init_linedata(); 
	ft_putstr("$>");
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
				ft_putchar(t[0]);
			}
		}
	}
	return (0);
}
