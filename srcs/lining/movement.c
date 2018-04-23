/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:22:04 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/04/23 15:40:57 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lining.h"

struct s_cursor_data	*init_cursordata(void)
{
	struct s_cursor_data	*cd;
	int						i;

	i = 0;
	if (!(cd = malloc(sizeof(struct s_cursor_data))))
		return (NULL);
	cd->pos = 0;
	cd->col = 0;
	cd->row = 0;
	ft_bzero(cd->buffer, BUFFER);
	return (cd);
}

void	move_left(int *index, struct s_line_data *ld)
{
	int		i;

	i = *index;
	if (ld->cd->col - 1 >= 0)
		tputs(tgoto(tgetstr("cm", NULL), --ld->cd->col, ld->cd->row), 1, fprint_char);
	*index = i;
}

void	move_right(int *index, struct s_line_data *ld)
{
	int						i;

	i = *index;
	tputs(tgoto(tgetstr("cm", NULL), ++ld->cd->col, ld->cd->row), 1, fprint_char);
	*index = i;
}
