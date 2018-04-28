/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 08:38:19 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/11/26 04:09:35 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	c;
	char	*str_sub;

	i = 0;
	c = -1;
	if (!(str_sub = ft_strnew(len)))
		return (NULL);
	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			if (i == start)
				while (++c < len)
				{
					str_sub[c] = s[i];
					i++;
				}
			if (c == len)
				return (str_sub);
			i++;
		}
		return (str_sub);
	}
	return (NULL);
}
