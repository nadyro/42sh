/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:42:49 by arohani           #+#    #+#             */
/*   Updated: 2018/07/19 03:58:55 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char *str)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		if (str[i])
			n++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
	}
	return (n);
}

static int	ft_word_length(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	return (i);
}

static int	ft_word_transfer(char *str, char *word)
{
	int i;
	int j;

	i = 0;
	j = ft_word_length(str);
	while (i < j)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (i);
}

char		**ft_split_whitespaces(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**dest;

	i = 0;
	j = 0;
	k = ft_count_words(str);
	if (!(dest = malloc(sizeof(dest) * (k + 1))))
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		if (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			k = ft_word_length(str + i);
			if (!(dest[j] = malloc(sizeof(*dest) * (k + 1))))
				return (0);
			i = i + ft_word_transfer((str + i), dest[j]);
			j++;
		}
	}
	dest[j] = 0;
	return (dest);
}
