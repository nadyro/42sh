/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 05:28:42 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/20 17:51:43 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

static unsigned char	g_otm[14][8][3] = {
	{
		{0, 1, 'A'}, {1, 1, 0}, {4, 1, 0}, {7, 1, 0}, {8, 1, 0},
		{0, 1, 'A'}, {0, 1, 'A'}, {12, 1, 0}
	},
	{
		{1, 1, 'A'}, {0, 1, 0}, {1, 1, 'A'}, {2, 1, 0}, {10, 1, 0},
		{1, 1, 'A'}, {1, 1, 'A'}, {1, 1, 'A'}
	},
	{
		{3, -1, 0}, {1, 1, 'A'}, {3, -1, 0}, {3, -1, 0}, {1, 1, 'A'},
		{3, -1, 0}, {3, 1, 0}, {3, -1, 0}
	},
	{
		{1, 1, 'A'}, {1, 1, 'A'}, {1, 1, 'A'}, {1, 1, 'A'}, {1, 1, 'A'},
		{1, 1, 'A'}, {1, 1, 'A'}, {1, 1, 'A'}
	},
	{
		{4, 1, 'A'}, {4, 1, 'A'}, {0, 1, 0}, {5, 1, 0}, {4, 1, 'A'},
		{4, 1, 'A'}, {4, 1, 'A'}, {4, 1, 'A'}
	},
	{
		{6, -1, 0}, {6, -1, 0}, {4, 1, 'A'}, {6, -1, 0}, {6, -1, 0},
		{6, -1, 0}, {6, -1, 0}, {6, -1, 0}
	},
	{
		{4, 1, 'A'}, {4, 1, 'A'}, {4, 1, 'A'}, {4, 1, 'A'}, {4, 1, 'A'},
		{4, 1, 'A'}, {4, 1, 'A'}, {4, 1, 'A'}
	},
	{
		{0, 1, 'A'}, {0, 1, 'A'}, {0, 1, 'A'}, {0, 1, 'A'}, {0, 1, 'A'},
		{0, 1, 'A'}, {0, 1, 0}, {0, 1, 'A'}
	},
	{
		{8, 1, 'B'}, {9, 0, 0}, {9, 0, 0}, {9, 0, 0}, {9, 0, 0},
		{9, 0, 0}, {8, 1, 'B'}, {8, 1, 'B'}
	},
	{
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}
	},
	{
		{10, 1, 'B'}, {11, 0, 0}, {11, 0, 0}, {11, 0, 0}, {11, 0, 0},
		{11, 0, 0}, {10, 1, 'B'}, {10, 1, 'B'}
	},
	{
		{1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0}, {1, 0, 0},
		{1, 0, 0}, {1, 0, 0}, {1, 0, 0}
	},
	{
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
		{0, 0, 0}, {0, 0, 0}, {13, -1, 0}
	},
	{
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
		{0, 0, 0}, {0, 0, 0}, {13, 1, 'A'}
	}
};

static unsigned int	g_grp[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 5, 0, 1, 0, 4,
	0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0,
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

static void		t2s_free(t_t2s *t2s)
{
	free(t2s->buffer[0]);
	free(t2s->buffer[1]);
	free(t2s);
}

static int		check_variable(t_t2s *t2s, char **env)
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

static char		*buffa2str(t_t2s *t2s)
{
	char	*str;

	if ((str = (char*)malloc(t2s->i[0] + 1)) == NULL)
		return (NULL);
	ft_memcpy(str, t2s->buffer[0], t2s->i[0]);
	str[t2s->i[0]] = 0;
	return (str);
}

static void		one_round(t_t2s *t2s, int *token, char *str)
{
	t2s->stat[T2S_OLD] = t2s->stat[T2S_CUR];
	t2s->cursor[T2S_OLD] = t2s->cursor[T2S_CUR];
	t2s->stat[T2S_CUR] = g_otm[t2s->stat[T2S_OLD]]
		[g_grp[(int)*(str + token[1] + t2s->cursor[T2S_OLD])]][0];
	t2s->cursor[T2S_CUR] += (char)g_otm[t2s->stat[T2S_OLD]]
		[g_grp[(int)*(str + token[1] + t2s->cursor[T2S_OLD])]][1];
}

char			*token2str(int *token, char *str, char **env)
{
	char	*ret;
	t_t2s	*t2s;

	t2s_init(&t2s);
	while (t2s != NULL && t2s->cursor[T2S_CUR] < token[2])
	{
		one_round(t2s, token, str);
		if (g_otm[t2s->stat[T2S_OLD]]
				[g_grp[(int)*(str + token[1] + t2s->cursor[T2S_OLD])]][2] != 0)
			t2s_add(t2s, str + token[1], t2s->cursor[T2S_OLD],
					g_otm[t2s->stat[T2S_OLD]]
					[g_grp[(int)*(str + token[1] + t2s->cursor[T2S_OLD])]][2]);
		if (t2s->stat[T2S_CUR] == 9 || t2s->stat[T2S_CUR] == 11)
			check_variable(t2s, env);
		if (t2s->stat[T2S_OLD] == 12 && t2s->stat[T2S_CUR] == 0)
			add_pwd(t2s, env);
	}
	if (t2s->stat[T2S_CUR] == 8)
		check_variable(t2s, env);
	if (t2s->stat[T2S_CUR] == 12)
		add_pwd(t2s, env);
	ret = buffa2str(t2s);
	t2s_free(t2s);
	return (ret);
}
