/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 12:39:54 by arohani           #+#    #+#             */
/*   Updated: 2017/04/27 15:22:55 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*fresh;
	size_t	i;

	i = 0;
	if (s)
	{
		if (!(fresh = (char *)malloc(sizeof(*fresh) * (len + 1))))
			return (NULL);
		while (len > 0)
		{
			fresh[i] = (char)(s[start]);
			i++;
			start++;
			len--;
		}
		fresh[i] = '\0';
		return (fresh);
	}
	return (0);
}
