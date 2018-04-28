/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 14:32:20 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/11/26 02:59:55 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_count_words(char const *str, char c)
{
	int i;
	int y;

	i = 0;
	y = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i])
		{
			y++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (y);
}

static char		**ft_fillwords(int y, int z, char const *s, char c)
{
	int		i;
	int		x;
	char	**str_s;

	i = 0;
	x = 0;
	if (!(str_s = (char **)malloc(sizeof(char *) * (y + 1))))
		return (NULL);
	while (y-- > 0)
	{
		i = z;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] != '\0' && s[i] != c)
			i++;
		if (!(str_s[x] = ft_strsub(s, z, (i - z) + 1)))
			return (NULL);
		z = i + 1;
		x++;
	}
	str_s[x] = NULL;
	return (str_s);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		y;
	int		z;
	char	**str_s;

	if (s != NULL)
	{
		i = 0;
		y = ft_count_words(s, c);
		while (s[i] == c && s[i])
			i++;
		z = i;
		if (!(str_s = ft_fillwords(y, z, s, c)))
			return (NULL);
		y = 0;
		while (str_s[y])
		{
			if (!(str_s[y] = ft_strtrim_char(str_s[y], c)))
				return (NULL);
			else
				y++;
		}
		return (str_s);
	}
	return (NULL);
}
