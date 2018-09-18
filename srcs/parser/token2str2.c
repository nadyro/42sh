/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <tcanaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:43:28 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/20 17:48:38 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

int			t2s_add(t_t2s *t2s, char *str, int cursor, char buffer)
{
	if (t2s->i[buffer - 'A'] + 1 > t2s->m[buffer - 'A'])
		if (t2s_realloc(t2s, buffer))
			return (1);
	t2s->buffer[buffer - 'A'][t2s->i[buffer - 'A']] = str[cursor];
	t2s->i[buffer - 'A'] += 1;
	return (0);
}

void		add_pwd(t_t2s *t2s, char **env)
{
	int		i;

	i = 5;
	while (env && *env != NULL)
	{
		if (ft_memcmp("HOME=", *env, 4) != 0)
		{
			(env)++;
			continue ;
		}
		while ((*env)[i] != '\0')
			t2s_add(t2s, *env, i++, 'A');
		return ;
	}
	t2s_add(t2s, "~", 0, 'A');
}
