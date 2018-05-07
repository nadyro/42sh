/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:33:56 by arohani           #+#    #+#             */
/*   Updated: 2017/04/26 19:01:52 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*fresh;
	unsigned int	len;

	if (s && f)
	{
		len = (unsigned int)ft_strlen((const char *)s);
		i = 0;
		if (!(fresh = (char *)malloc(sizeof(*fresh) *
						(len + 1))))
			return (NULL);
		while (s[i] != '\0')
		{
			fresh[i] = f(i, s[i]);
			i++;
		}
		fresh[i] = '\0';
		return (fresh);
	}
	return (0);
}
