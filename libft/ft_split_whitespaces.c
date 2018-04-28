/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 22:10:26 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/11/27 01:54:58 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_count_words(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
			str++;
		if (*str && *str != ' ' && *str != '\t' && *str != '\n')
		{
			i++;
			while ((*str && *str != ' ' && *str != '\t') && *str != '\n')
				str++;
		}
	}
	return (i);
}

char	*ft_strdups(char *str)
{
	int		i;
	int		y;
	char	*word;

	y = 0;
	while (str[y] != ' ' && str[y] != '\t' && str[y] != '\n' && str[y])
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

char	**ft_split_whitespaces(char *str)
{
	int		i;
	int		y;
	char	**tab_str;

	i = ft_count_words(str);
	if (!(tab_str = (char**)malloc((i + 1) * sizeof(char*))))
		return (NULL);
	y = 0;
	while (*str)
	{
		while ((*str == ' ' || *str == '\t' || *str == '\n') && *str)
			str++;
		if (*str != ' ' && *str != '\t' && *str != '\n' && *str)
		{
			tab_str[y] = ft_strdups(str);
			y++;
		}
		while (*str != ' ' && *str != '\t' && *str != '\n' && *str)
			str++;
		tab_str[i] = NULL;
	}
	return (tab_str);
}
