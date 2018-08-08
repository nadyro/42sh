/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 15:00:16 by arohani           #+#    #+#             */
/*   Updated: 2018/08/08 20:40:58 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include <stdio.h>

static unsigned char	g_otm[12][6][3] = {
	{
		{0, 1, 'A'},
		{1, 1, 0}, {4, 1, 0}, {7, 1, 0}, {8, 1, 0},
		{0, 1, 'A'}
	},{
		{1, 1, 'A'},
		{0, 1, 0}, {1, 1, 'A'}, {2, 1, 0}, {10, 1, 0},
		{1, 1, 'A'}
	},{
		{3, -1, 0},
		{1, 1, 'A'}, {3, -1, 0}, {3, -1, 0}, {1, 1, 'A'},
		{3, -1, 0}
	},{
		{1, 1, 'A'},
		{1, 1, 'A'}, {1, 1, 'A'}, {1, 1, 'A'}, {1, 1, 'A'},
		{1, 1, 'A'}
	},{
		{4, 1, 'A'},
		{4, 1, 'A'}, {0, 1, 0}, {5, 1, 0}, {4, 1, 'A'},
		{4, 1, 'A'}
	},{
		{6, -1, 0},
			{6, -1, 0}, {4, 1, 'A'}, {6, -1, 0}, {6, -1, 0},
			{6, -1, 0}
	},{
		{4, 1, 'A'},
			{4, 1, 'A'}, {4, 1, 'A'}, {4, 1, 'A'}, {4, 1, 'A'},
			{4, 1, 'A'}
	},{
		{0, 1, 'A'},
			{0, 1, 'A'}, {0, 1, 'A'}, {0, 1, 'A'}, {0, 1, 'A'},
			{0, 1, 'A'}
	},{
		{8, 1, 'B'},
			{9, 0, 0}, {9, 0, 0}, {9, 0, 0}, {9, 0, 0},
			{9, 0, 0}
	},{
		{0, 0, 0},
			{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
			{0, 0, 0}
	},{
		{10, 1, 'B'},
			{11, 0, 0}, {11, 0, 0}, {11, 0, 0}, {11, 0, 0},
			{11, 0, 0}
	},{
		{1, 0, 0},
			{1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
			{1, 0, 0}
	}
};
 static unsigned int	g_grp[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 5, 0, 1, 0, 4,
	0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0
};
 int		t2s_init(t_t2s  **t2s)
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
 int		t2s_add(t_t2s *t2s, char *str, int cursor, char buffer)
{
	if (t2s->i[buffer - 'A'] + 1 > t2s->m[buffer - 'A'])
		if (t2s_realloc(t2s, buffer))
			return (1);
	t2s->buffer[buffer - 'A'][t2s->i[buffer - 'A']] = str[cursor];
	t2s->i[buffer - 'A'] += 1;
	return (0);
}
 void	t2s_free(t_t2s *t2s)
{
	free(t2s->buffer[0]);
	free(t2s->buffer[1]);
	free(t2s);
}
 int	check_variable(t_t2s *t2s, char **env)
{
	void		*ptr;
	size_t		x;
 	while (*env != NULL)
	{
		if ((ptr = ft_memchr(*env, '=', ft_strlen(*env))) == NULL && env++)
			continue ;
		if ((size_t)ptr - (size_t)*env != (size_t)t2s->i[1] && env++)
			continue ;
		if (ft_memcmp(*env, t2s->buffer[1],
					(size_t)ptr - (size_t)*env) != 0 && env++)
			continue ;
		x = 1;
		while (x < ft_strlen(*env) - ((size_t)ptr - (size_t)*env))
			t2s_add(t2s, *env, (size_t)ptr - (size_t)*env + x++, 'A');
		return (t2s_init_b(t2s));
	}
	x = 0;
	t2s_add(t2s, "$", 0, 'A');
	while (x < (size_t)t2s->i[1])
		t2s_add(t2s, t2s->buffer[1], x++, 'A');
	return (t2s_init_b(t2s));
}
 char	*buffa2str(t_t2s *t2s)
{
	char	*str;
 	if ((str = (char*)malloc(t2s->i[0] + 1)) == NULL)
		return (NULL);
	ft_memcpy(str, t2s->buffer[0], t2s->i[0]);
	str[t2s->i[0]] = 0;
	return (str);
}
 char	*token2str(int *token, char *str, char **env)
{
	char	*ret;
	t_t2s	*t2s;
 	t2s_init(&t2s);
	while (t2s != NULL && t2s->cursor[T2S_CUR] < token[2])
	{
		t2s->stat[T2S_OLD] = t2s->stat[T2S_CUR];
		t2s->cursor[T2S_OLD] = t2s->cursor[T2S_CUR];
		t2s->stat[T2S_CUR] = g_otm[t2s->stat[T2S_OLD]]
			[g_grp[(int)*(str + token[1] + t2s->cursor[T2S_OLD])]][0];
		t2s->cursor[T2S_CUR] += (char)g_otm[t2s->stat[T2S_OLD]]
			[g_grp[(int)*(str + token[1] + t2s->cursor[T2S_OLD])]][1];
		if (g_otm[t2s->stat[T2S_OLD]]
				[g_grp[(int)*(str + token[1] + t2s->cursor[T2S_OLD])]][2] != 0)
			t2s_add(t2s, str + token[1], t2s->cursor[T2S_OLD],
					g_otm[t2s->stat[T2S_OLD]]
					[g_grp[(int)*(str + token[1] + t2s->cursor[T2S_OLD])]][2]);
		if (t2s->stat[T2S_CUR] == 9 || t2s->stat[T2S_CUR] == 11)
			check_variable(t2s, env);
	}
	if (t2s->stat[T2S_CUR] == 8)
		check_variable(t2s, env);
	ret = buffa2str(t2s);
	t2s_free(t2s);
	return (ret);
}

