/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2str_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 05:32:12 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/13 05:33:37 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

int		t2s_init(t_t2s **t2s)
{
	if ((*t2s = (t_t2s*)malloc(sizeof(t_t2s))) == NULL)
		return (1);
	(*t2s)->buffer[0] = 0;
	if (((*t2s)->buffer[0] = (char*)malloc(T2S_BLOCK)) == NULL)
	{
		free(*t2s);
		return (1);
	}
	if (((*t2s)->buffer[1] = (char*)malloc(T2S_BLOCK)) == NULL)
	{
		free((*t2s)->buffer[0]);
		free(*t2s);
		return (1);
	}
	(*t2s)->i[0] = 0;
	(*t2s)->i[1] = 0;
	(*t2s)->m[0] = T2S_BLOCK;
	(*t2s)->m[1] = T2S_BLOCK;
	(*t2s)->cursor[0] = 0;
	(*t2s)->cursor[1] = 0;
	(*t2s)->stat[0] = 0;
	(*t2s)->stat[1] = 0;
	bzero((*t2s)->buffer[0], (*t2s)->m[0]);
	bzero((*t2s)->buffer[1], (*t2s)->m[1]);
	return (0);
}

int		t2s_realloc(t_t2s *t2s, char buffer)
{
	char	*buff;
	int		x;

	if ((buff = (char*)malloc(t2s->m[buffer - 'A'] + T2S_BLOCK)) == NULL)
		return (1);
	t2s->m[buffer - 'A'] += T2S_BLOCK;
	bzero(buff, t2s->m[buffer - 'A']);
	x = -1;
	while (++x < t2s->i[buffer - 'A'])
		buff[x] = t2s->buffer[buffer - 'A'][x];
	free(t2s->buffer[buffer - 'A']);
	t2s->buffer[buffer - 'A'] = buff;
	return (0);
}

int		t2s_init_b(t_t2s *t2s)
{
	free(t2s->buffer[1]);
	if ((t2s->buffer[1] = (char*)malloc(t2s->m[1])) == NULL)
		return (1);
	bzero(t2s->buffer[1], t2s->m[1]);
	t2s->i[1] = 0;
	return (0);
}
