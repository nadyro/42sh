/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 11:06:40 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/05/01 15:25:24 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strrev(const char *s)
{
	int		i;
	int		y;
	char	*str_rev;

	if (s != NULL)
	{
		i = 0;
		y = ft_strlen(s) - 1;
		if (!(str_rev = ft_strnew(y + 1)))
			return (NULL);
		while (y >= 0)
		{
			str_rev[i] = s[y];
			i++;
			y--;
		}
		str_rev[i] = '\0';
		return (str_rev);
	}
	return (NULL);
}
