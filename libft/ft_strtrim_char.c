/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 11:17:06 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/05/01 15:24:45 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim_char(char const *s, char c)
{
	size_t	i;
	size_t	y;
	char	*str_s;

	if (s != NULL && c)
	{
		i = 0;
		y = 0;
		while (s[i] == c && s[i])
			i++;
		y = i;
		i = ft_strlen(s) - 1;
		while ((s[i] == c))
			i--;
		if (!(str_s = ft_strsub(s, y, (i - y) + 1)))
			return (NULL);
		return (str_s);
	}
	return (NULL);
}
