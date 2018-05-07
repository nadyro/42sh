/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:08:20 by arohani           #+#    #+#             */
/*   Updated: 2018/02/16 16:30:33 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char ch;

	ch = c;
	while (*(char *)s != '\0')
	{
		if (*(char *)s == ch)
			return ((char *)s);
		s++;
	}
	if (*(char *)s == ch)
		return ((char *)s);
	return (NULL);
}
