/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 18:27:07 by arohani           #+#    #+#             */
/*   Updated: 2017/04/29 13:14:33 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_words(char const *str, char c)
{
	static int i;
	static int n;

	i = 0;
	n = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			n++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (n);
}

static int		ft_word_length(char const *str, char c)
{
	static int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int		ft_word_transfer(char const *str, char *tab, char c)
{
	static int i;
	static int j;

	i = 0;
	j = ft_word_length(str, c);
	while (i < j)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = 0;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	int		j;
	char	**tab;

	if (s)
	{
		j = 0;
		if (!(tab = (char **)malloc(sizeof(tab) * (ft_count_words(s, c) + 1))))
			return (NULL);
		while (*s != '\0')
		{
			while (*s == c)
				s++;
			if (*s && *s != c)
			{
				if (!(tab[j] = malloc(sizeof(*tab) *
								(ft_word_length(s, c) + 1))))
					return (NULL);
				s = s + ft_word_transfer(s, tab[j], c);
				j++;
			}
		}
		tab[j] = 0;
		return (tab);
	}
	return (NULL);
}
