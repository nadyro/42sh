/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:43:42 by arohani           #+#    #+#             */
/*   Updated: 2017/04/25 16:22:14 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*start;

	ch = c;
	start = (char *)s;
	s = s + ft_strlen((char *)s);
	while ((char *)s >= start)
	{
		if (*(char *)s == ch)
			return ((char *)s);
		s--;
	}
	return (NULL);
}
