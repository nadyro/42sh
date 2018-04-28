/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 07:13:47 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/05/01 15:21:18 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	y;
	char	*str_s;

	if (s != NULL)
	{
		i = 0;
		y = ft_strlen(s);
		if (!(str_s = ft_strnew(y)))
			return (NULL);
		while (i < y)
		{
			str_s[i] = f(s[i]);
			i++;
		}
		return (str_s);
	}
	return (NULL);
}
