/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kernel_panic <kernel_panic@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:17:13 by kernel_pani       #+#    #+#             */
/*   Updated: 2018/04/21 22:05:22 by kernel_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

struct line_data *init_linedata(void)
{
	struct line_data	*ld;
	int			s;

	s = 0;
	if (!(ld = malloc(sizeof(struct line_data))))
		return (NULL);
	ld->nb_resize = 0;
	ld->content = NULL;
	ld->old_content = NULL;
	ft_bzero(ld->buffer, BUFFER);
	ld->length = 0;
	while (s < 512)
		ld->resize_history[s++] = -1;
	ld->nb_resize = 0;
	return (ld);
}

void	reallocate_mem_line(int *s, struct line_data *ld)
{
	int	i;
	char	*join_tmp;

	i = 0;
	if (ld->nb_resize > 0)
		join_tmp = ft_strjoin(ld->old_content, ld->buffer);
	else
		join_tmp = ft_strdup(ld->buffer);
	ld->old_content = ft_strdup(join_tmp);
	ft_strdel(&join_tmp);
	ld->resize_history[ld->nb_resize] = ft_strlen(ld->buffer); 
	ld->nb_resize++;
	ft_bzero(ld->buffer, ft_strlen(ld->buffer));
	*s = 1;
}

void	print_line_data(struct line_data *ld)
{
	int	i;

	i = 0;
	ft_putstr("Content : ");
	if (ld->content)
		ft_putendl(ld->content);
	ft_putchar('\n');
	ft_putstr("Old_Content : ");
	if (ld->old_content)
		ft_putendl(ld->old_content);
	ft_putchar('\n');
	ft_putstr("Buffer : ");
	if (ld->buffer[0])
		ft_putendl(ld->buffer);
	ft_putchar('\n');
	ft_putstr("Length : ");
	ft_putnbr(ld->length);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putendl("Resize History : ");
	while (ld->resize_history[i] != -1)
	{
		ft_putnbr(i);
		ft_putstr(" : ");
		ft_putnbr(ld->resize_history[i]);
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
	ft_putstr("Nb Resize : ");
	ft_putnbr(ld->nb_resize);
	ft_putchar('\n');
}