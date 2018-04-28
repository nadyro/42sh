/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 07:54:10 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/05/01 15:21:54 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			str_s[i] = f(i, s[i]);
			i++;
		}
		return (str_s);
	}
	return (NULL);
}
