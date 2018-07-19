/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 16:46:36 by azybert           #+#    #+#             */
/*   Updated: 2018/02/16 17:47:07 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_strsplit3(char **tab, char const *s, char c)
{
	int		l;
	size_t	size;

	l = -1;
	while (*s)
	{
		if (*s == c)
			while (*s == c)
				s++;
		size = 0;
		while (*(s + size) && *(s + size) != c)
			size++;
		if (size != 0)
		{
			if (!(tab[++l] = malloc(sizeof(char) * (size + 1))))
				return (NULL);
			ft_strncpy(tab[l], s, size);
			tab[l][size] = '\0';
			s = s + size;
		}
	}
	tab[++l] = NULL;
	return (tab);
}

static int	ft_strsplit2(char const *s, char c)
{
	int		i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			while (*s == c)
				s++;
		if (*s && *s != c)
		{
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	if (!(tab = malloc(sizeof(char *) * (ft_strsplit2(s, c) + 1))))
		return (NULL);
	tab = ft_strsplit3(tab, s, c);
	return (tab);
}
