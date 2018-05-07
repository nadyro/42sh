/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:53:33 by arohani           #+#    #+#             */
/*   Updated: 2017/04/26 19:02:33 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t		i;
	char		*fresh;

	i = 0;
	if (s)
	{
		if (!(fresh = (char *)malloc(sizeof(*fresh) *
						(ft_strlen((const char *)s) + 1))))
			return (NULL);
		while (*s != '\0')
		{
			fresh[i] = f(*s);
			s++;
			i++;
		}
		fresh[i] = '\0';
		return (fresh);
	}
	return (0);
}
