/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 06:01:14 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/11/26 06:20:31 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words_c(char *str, char c)
{
	int i;

	i = 0;
	while (*str)
	{
		while (*str && (*str == c))
			str++;
		if (*str && *str != c)
		{
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	return (i);
}

char	*ft_strdupc(char *str, char c)
{
	int		i;
	int		y;
	char	*word;

	y = 0;
	while (str[y] != c && str[y])
	{
		y++;
	}
	if (!(word = (char*)malloc(sizeof(char) * (y + 1))))
		return (NULL);
	i = 0;
	while (i < y)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_splitchar(char *str, char c)
{
	int		i;
	int		y;
	char	**tab_str;

	i = ft_count_words_c(str, c);
	if (!(tab_str = (char**)malloc((i + 1) * sizeof(char*))))
		return (NULL);
	y = 0;
	while (*str)
	{
		while ((*str == c) && *str)
			str++;
		if (*str != c && *str)
		{
			tab_str[y] = ft_strdupc(str, c);
			y++;
		}
		while (*str != c && *str)
			str++;
		tab_str[i] = NULL;
	}
	return (tab_str);
}
